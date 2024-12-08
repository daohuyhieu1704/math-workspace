#include "pch.h"
#include "MathViewport.h"
#include <iostream>
#include <cmath>
#include "OdMathCircle.h"
#include "MathPolyline.h"
#include "OdMathPlane.h"
#include "OdDrawingManager.h"
#include "OdSelectionPrompt.h"

OD_RTTI_DEFINE(MathViewport, OdGiDrawable)
OD_RTTI_SINGLETON_DEFINE(MathViewport)

//extern "C" __declspec(dllexport) void NotifyMouseClick(int x, int y);

OdMathPolylinePtr polyline = OdMathPolyline::createObject();

MathViewport::MathViewport() {
}

void MathViewport::applyCameraAndProjection()
{
    glViewport(0, 0, win_width, win_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)win_width / (float)win_height;
    gluPerspective(45.0, aspect, 0.5, 5000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2],
        cameraTarget[0], cameraTarget[1], cameraTarget[2],
        cameraUp[0], cameraUp[1], cameraUp[2]);
}

void MathViewport::idle() {
    glutPostRedisplay();
}

void MathViewport::display() {
    drawScene();
}

void MathViewport::drawScene() {
    float lpos[] = { -1, 2, 3, 0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply camera & projection here
    applyCameraAndProjection();

    drawAxis();
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    drawInfiniteGrid(10.0f, 50);
    OdDrawingManager::R()->renderAll();
    glutSwapBuffers();
    nframes++;
}

void MathViewport::motionHandler(int x, int y)
{
    int dx = x - mouse_x; // horizontal mouse movement
    int dy = y - mouse_y; // vertical mouse movement

    // Update stored mouse position
    mouse_x = x;
    mouse_y = y;

    // If no movement, do nothing
    if (!(dx || dy)) return;

    // bnstate[0] = left mouse: rotate
    // bnstate[1] = middle mouse: pan
    // bnstate[2] = right mouse: zoom

    double cpx = cameraPos[0];
    double cpy = cameraPos[1];
    double cpz = cameraPos[2];
    double tx = cameraTarget[0];
    double ty = cameraTarget[1];
    double tz = cameraTarget[2];

    // Vector from target to camera
    double vx = cpx - tx;
    double vy = cpy - ty;
    double vz = cpz - tz;
    double dist = std::sqrt(vx * vx + vy * vy + vz * vz);
    if (dist < 1e-9) dist = 1e-9;

    if (bnstate[0]) {
        // Rotate camera around target
        double rotateSpeed = 0.2;
        double r = dist;
        double yaw = std::atan2(vy, vx);
        double pitch = std::acos(vz / r);

        yaw -= dx * rotateSpeed * OdPI / 180.0;
        pitch -= dy * rotateSpeed * OdPI / 180.0;

        if (pitch < 0.1) pitch = 0.1;
        if (pitch > OdPI - 0.1) pitch = OdPI - 0.1;

        double sinPitch = std::sin(pitch);
        vx = r * std::cos(yaw) * sinPitch;
        vy = r * std::sin(yaw) * sinPitch;
        vz = r * std::cos(pitch);

        cameraPos[0] = tx + vx;
        cameraPos[1] = ty + vy;
        cameraPos[2] = tz + vz;
    }

    if (bnstate[1]) {
        // Pan camera: shift camera and target
        double panSpeed = 0.05;
        double upVec[3] = { 0.0, 0.0, 1.0 };

        double cx = tx - cpx;
        double cy = ty - cpy;
        double cz = tz - cpz;
        double len = std::sqrt(cx * cx + cy * cy + cz * cz);
        if (len < 1e-9) len = 1e-9;
        cx /= len; cy /= len; cz /= len; // direction from camera to target

        // right = direction ~ up
        double rx = cy * upVec[2] - cz * upVec[1];
        double ry = cz * upVec[0] - cx * upVec[2];
        double rz = cx * upVec[1] - cy * upVec[0];
        double rl = std::sqrt(rx * rx + ry * ry + rz * rz);
        if (rl > 1e-9) {
            rx /= rl; ry /= rl; rz /= rl;
        }
        else {
            rx = 1; ry = 0; rz = 0;
        }

        // newUp = right ~ direction
        double ux = ry * cz - rz * cy;
        double uy = rz * cx - rx * cz;
        double uz = rx * cy - ry * cx;
        double ul = std::sqrt(ux * ux + uy * uy + uz * uz);
        if (ul > 1e-9) {
            ux /= ul; uy /= ul; uz /= ul;
        }
        else {
            ux = 0; uy = 1; uz = 0;
        }

        double moveX = -dx * panSpeed;
        double moveY = dy * panSpeed;

        cameraPos[0] += rx * moveX + ux * moveY;
        cameraPos[1] += ry * moveX + uy * moveY;
        cameraPos[2] += rz * moveX + uz * moveY;

        cameraTarget[0] += rx * moveX + ux * moveY;
        cameraTarget[1] += ry * moveX + uy * moveY;
        cameraTarget[2] += rz * moveX + uz * moveY;
    }

    if (bnstate[2]) {
        // Zoom camera: move closer/farther along view direction
        double zoomSpeed = 0.1;
        double zoomAmount = dy * zoomSpeed;
        double cx = tx - cpx;
        double cy = ty - cpy;
        double cz = tz - cpz;
        double length = std::sqrt(cx * cx + cy * cy + cz * cz);
        if (length < 1e-9) length = 1e-9;

        cx /= length; cy /= length; cz /= length;
        double newDist = length - zoomAmount;
        if (newDist < 0.1) newDist = 0.1;
        cameraPos[0] = tx - cx * newDist;
        cameraPos[1] = ty - cy * newDist;
        cameraPos[2] = tz - cz * newDist;
    }

    glutPostRedisplay();
}

void MathViewport::drawGridXY(float size, float step) {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);

    glColor4f(0.5f, 0.5f, 0.5f, 0.5f);

    for (float i = step; i <= size; i += step) {
        glVertex3f(-size, i, 0);
        glVertex3f(size, i, 0);
        glVertex3f(-size, -i, 0);
        glVertex3f(size, -i, 0);

        glVertex3f(i, -size, 0);
        glVertex3f(i, size, 0);
        glVertex3f(-i, -size, 0);
        glVertex3f(-i, size, 0);
    }

    glColor3f(1, 0, 0);
    glVertex3f(-size, 0, 0);
    glVertex3f(size, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, -size, 0);
    glVertex3f(0, size, 0);

    glEnd();

    glEnable(GL_LIGHTING);
}

static void renderText(const char* text, float x, float y, float z) {
    glRasterPos3f(x, y, z);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void MathViewport::drawInfiniteGrid(float spacing, int halfSize) const {
    glLineWidth(1.0f);       // Set grid line width
    glColor3f(0.5f, 0.5f, 0.5f); // Grid color (gray)

    glBegin(GL_LINES);
    // Convert spherical coordinates to Cartesian
    float cam_x = cam_dist * cosf(cam_phi * OdPI / 180.0f) * sinf(cam_theta * OdPI / 180.0f);
    float cam_y = cam_dist * sinf(cam_phi * OdPI / 180.0f);

    // Dynamic grid offset based on camera position
    float offsetX = cam_x - fmod(cam_x, spacing);
    float offsetY = cam_y - fmod(cam_y, spacing);

    // Draw lines parallel to the X-axis
    for (int i = -halfSize; i <= halfSize; ++i) {
        float y = (i * spacing) + offsetY;
        glVertex3f(-halfSize * spacing + offsetX, y, 0.0f); // Start point
        glVertex3f(halfSize * spacing + offsetX, y, 0.0f);  // End point
    }

    // Draw lines parallel to the Y-axis
    for (int i = -halfSize; i <= halfSize; ++i) {
        float x = (i * spacing) + offsetX;
        glVertex3f(x, -halfSize * spacing + offsetY, 0.0f); // Start point
        glVertex3f(x, halfSize * spacing + offsetY, 0.0f);  // End point
    }

    glEnd();
}

void MathViewport::drawAxis(float size) {
    glDisable(GL_LIGHTING);
    glLineWidth(2.0f); // Set line width

    glBegin(GL_LINES);

    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glVertex3f(-1.0f, 0.0f, 0.0f); // Negative X
    glVertex3f(1.0f, 0.0f, 0.0f);  // Positive X

    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glVertex3f(0.0f, -1.0f, 0.0f); // Negative Y
    glVertex3f(0.0f, 1.0f, 0.0f);  // Positive Y

    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glVertex3f(0.0f, 0.0f, -1.0f); // Negative Z
    glVertex3f(0.0f, 0.0f, 1.0f);  // Positive Z

    glEnd();

    // Add labels to the axes
    glColor3f(1.0f, 0.0f, 0.0f); // Red for X
    renderText("X", 1.1f, 0.0f, 0.0f); // Slightly beyond the positive X-axis

    glColor3f(0.0f, 1.0f, 0.0f); // Green for Y
    renderText("Y", 0.0f, 1.1f, 0.0f); // Slightly beyond the positive Y-axis

    glColor3f(0.0f, 0.0f, 1.0f); // Blue for Z
    renderText("Z", 0.0f, 0.0f, 1.1f); // Slightly beyond the positive Z-axis
    glEnable(GL_LIGHTING);
}

void MathViewport::print_help() {
    const char* helpprompt[] = {
        "Press F1 for help",
        nullptr
    };

    const char* helptext[] = {
        "Rotate: left mouse drag",
        "Scale: right mouse drag up/down",
        "Pan: middle mouse drag",
        "",
        "Toggle fullscreen: f",
        "Toggle animation: space",
        "Reset camera: r",
        "Quit: escape or q",
        nullptr
    };

    const char** text = help ? helptext : helpprompt;

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, win_width, 0, win_height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    int line = 0;
    for (const char** lineText = text; *lineText != nullptr; ++lineText, ++line) {
        // Shadow
        glColor3f(0.0f, 0.1f, 0.0f);
        glRasterPos2f(7, win_height - (line + 1) * 20 - 2);
        for (const char* c = *lineText; *c; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        }

        // Foreground
        glColor3f(0.0f, 0.9f, 0.0f);
        glRasterPos2f(5, win_height - (line + 1) * 20);
        for (const char* c = *lineText; *c; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        }
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}


void MathViewport::reshape(int x, int y) {
    if (y == 0) y = 1;
    win_width = x;
    win_height = y;
}

void MathViewport::keypress(unsigned char key, int x, int y) {
    static int fullscreen = 0;
    static int prev_width, prev_height;

    switch (key) {
    case 27: // Escape
    case 'q':
        std::cout << "Quitting application..." << std::endl;
        exit(0);
        break;

    case ' ':
        anim ^= 1;
        glutIdleFunc(anim ? [](void) { R()->idle(); } : nullptr);
        glutPostRedisplay();

        if (anim) {
            anim_start = glutGet(GLUT_ELAPSED_TIME);
            nframes = 0;
        }
        else {
            long elapsed_time = glutGet(GLUT_ELAPSED_TIME) - anim_start;
            long fps = (nframes * 100000) / elapsed_time;
            std::cout << "Framerate: " << fps / 100 << "." << fps % 100 << " fps" << std::endl;
        }
        break;

    case 'f':
        fullscreen ^= 1;
        if (fullscreen) {
            prev_width = glutGet(GLUT_WINDOW_WIDTH);
            prev_height = glutGet(GLUT_WINDOW_HEIGHT);
            glutFullScreen();
        }
        else {
            glutReshapeWindow(prev_width, prev_height);
        }
        break;

    case 'r':
        // Reset camera to default
        cameraPos[0] = 0.0; cameraPos[1] = 0.0; cameraPos[2] = 100.0;
        cameraTarget[0] = 0.0; cameraTarget[1] = 0.0; cameraTarget[2] = 0.0;
        cameraUp[0] = 0.0; cameraUp[1] = 0.0; cameraUp[2] = 1.0;
        std::cout << "Camera reset to default position." << std::endl;
        glutPostRedisplay();
        break;

    default:
        std::cout << "Key pressed: " << key << std::endl;
        break;
    }
}

void MathViewport::skeypress(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1: // Toggle help display
        help ^= 1; // Flip the `help` flag (on/off)
        glutPostRedisplay(); // Request a redraw to update the help display
        break;

    case GLUT_KEY_UP: // Example: Handle "up arrow" key
        cam_phi -= 5.0f; // Adjust vertical angle
        if (cam_phi < -90.0f) cam_phi = -90.0f;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN: // Example: Handle "down arrow" key
        cam_phi += 5.0f;
        if (cam_phi > 90.0f) cam_phi = 90.0f;
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT: // Example: Handle "left arrow" key
        cam_theta -= 5.0f; // Adjust horizontal angle
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT: // Example: Handle "right arrow" key
        cam_theta += 5.0f;
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

void MathViewport::mouse(int bn, int st, int x, int y) {
    int bidx = bn - GLUT_LEFT_BUTTON;
    if (bidx >= 0 && bidx < 3) {
        bnstate[bidx] = (st == GLUT_DOWN);
    }

    mouse_x = x;
    mouse_y = y;

    if (bn == GLUT_LEFT_BUTTON && st == GLUT_DOWN) {
        OdSelectionPrompt::pickObjects(x, y);
        OdSelectionPrompt::resetWorldMouse(x, y);
    }

    glutPostRedisplay();
}


void MathViewport::motion(int x, int y) {
    motionHandler(x, y);
}

void MathViewport::setColorID(int id) {
    GLubyte r = id & 0xFF;
    GLubyte g = (id >> 8) & 0xFF;
    GLubyte b = (id >> 16) & 0xFF;
    glColor3ub(r, g, b);
}


void MathViewport::pickObject(int x, int y) {
    // Get window dimensions
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Convert mouse coordinates to Normalized Device Coordinates (NDC)
    float ndcX = (2.0f * x) / windowWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * y) / windowHeight; // Flip Y-axis for OpenGL coordinates

    // Convert NDC to clip space
    glm::vec4 rayClip = glm::vec4(ndcX, ndcY, -1.0f, 1.0f);

    // Convert clip space to eye space
    glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f); // Set w = 0 for a direction vector

    // Convert eye space to world space
    glm::vec3 rayWorld = glm::normalize(glm::vec3(glm::inverse(viewMatrix) * rayEye));

    // Define ray origin (camera position) and direction
    glm::vec3 rayOrigin = cameraPosition;
    glm::vec3 rayDirection = rayWorld;

    // Object picking logic
    float closestDistance = FLT_MAX; // Track the closest object
    int pickedObjectID = -1;         // ID of the picked object
    //// Iterate through all objects (this assumes a list of objects with bounding spheres)
    //for (const auto& object : sceneObjects) { // `sceneObjects` contains objects with bounding spheres
    //    float t; // Distance to intersection

    //    // Check if the ray intersects the object's bounding sphere
    //    if (rayIntersectsSphere(rayOrigin, rayDirection, object.position, object.boundingRadius, t)) {
    //        if (t < closestDistance) { // Find the closest intersected object
    //            closestDistance = t;
    //            pickedObjectID = object.id;
    //        }
    //    }
    //}

    //// Update the selected object
    //if (pickedObjectID != -1) {
    //    std::cout << "Picked object ID: " << pickedObjectID << std::endl;
    //    selectedObjectID = pickedObjectID; // Save the selected object ID
    //}
    //else {
    //    std::cout << "No object selected." << std::endl;
    //    selectedObjectID = -1; // No object selected
    //}

    glutPostRedisplay(); // Redraw the screen to reflect the selection
}

void MathViewport::setCamera() {
    glTranslatef(0, 0, -cam_dist);
    glRotatef(cam_phi, 1, 0, 0);
    glRotatef(cam_theta, 0, 1, 0);
    glTranslatef(cam_pan[0], cam_pan[1], cam_pan[2]);
    glutPostRedisplay();
}

// Viewport preset methods: set cameraPos and cameraTarget directly
// Example: TLViewport places camera top-left. Adjust as needed.
void MathViewport::TLViewport() {
    // Example: place camera at top-left angle above the target
    cameraTarget[0] = 0.0; cameraTarget[1] = 0.0; cameraTarget[2] = 0.0;
    // Place camera at 45‹ above and -45‹ yaw, distance 100
    double r = 100.0;
    double yaw = -45.0 * OdPI / 180.0;
    double pitch = 45.0 * OdPI / 180.0;
    cameraPos[0] = cameraTarget[0] + r * std::cos(yaw) * std::cos(pitch);
    cameraPos[1] = cameraTarget[1] + r * std::sin(yaw) * std::cos(pitch);
    cameraPos[2] = cameraTarget[2] + r * std::sin(pitch);
    glutPostRedisplay();
}

// Similarly implement other viewport preset methods...
void MathViewport::TMViewport() {
    // Just place camera directly above target (top-middle)
    cameraTarget[0] = 0; cameraTarget[1] = 0; cameraTarget[2] = 0;
    cameraPos[0] = 0; cameraPos[1] = 0; cameraPos[2] = 100;
    glutPostRedisplay();
}

void MathViewport::TRViewport()
{
	cam_phi = 45.0f;
	cam_theta = 45.0f;
	cam_pan[0] = 10.0f;
	cam_pan[1] = 10.0f;
	cam_pan[2] = 0.0f;
	setCamera();
}

void MathViewport::MLViewport()
{
	cam_phi = 45.0f;
	cam_theta = -90.0f;
	cam_pan[0] = -10.0f;
	cam_pan[1] = 0.0f;
	cam_pan[2] = 0.0f;
	setCamera();
}

void MathViewport::TMMViewport()
{
	cam_phi = 45.0f;
	cam_theta = 0.0f;
	cam_pan[0] = 0.0f;
	cam_pan[1] = 0.0f;
	cam_pan[2] = 0.0f;
	setCamera();
}

void MathViewport::BMMViewport()
{
	cam_phi = -45.0f;
	cam_theta = 0.0f;
	cam_pan[0] = 0.0f;
	cam_pan[1] = 0.0f;
	cam_pan[2] = 0.0f;
	setCamera();
}

void MathViewport::MRViewport()
{
	cam_phi = 45.0f;
	cam_theta = 90.0f;
	cam_pan[0] = 10.0f;
	cam_pan[1] = 0.0f;
	cam_pan[2] = 0.0f;
	setCamera();
}

void MathViewport::BLViewport()
{
	cam_phi = -45.0f;
	cam_theta = -90.0f;
	cam_pan[0] = -10.0f;
	cam_pan[1] = -10.0f;
	cam_pan[2] = 0.0f;
	setCamera();
}

void MathViewport::BMViewport()
{
	cam_phi = -45.0f;
	cam_theta = 0.0f;
	cam_pan[0] = 0.0f;
	cam_pan[1] = -10.0f;
	cam_pan[2] = 0.0f;
	setCamera();
}

void MathViewport::BRViewport()
{
	cam_phi = -45.0f;
	cam_theta = 45.0f;
	cam_pan[0] = 10.0f;
	cam_pan[1] = -10.0f;
	cam_pan[2] = 0.0f;
	setCamera();
}


OdBaseObjectPtr MathViewport::Clone()
{
    MathViewportPtr clone = MathViewport::createObject();
    return clone;
}

OdResult MathViewport::draw() 
{
    return OdResult();
}
