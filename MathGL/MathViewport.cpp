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

OdMathPolylinePtr polyline = OdMathPolyline::createObject();

MathViewport::MathViewport() {
}
// Member function implementations
void MathViewport::idle() {
    glutPostRedisplay();
}

void MathViewport::display() {
    drawScene(false);
}

void MathViewport::drawScene(bool picking) {
    long tm;
    float lpos[] = { -1, 2, 3, 0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera transformations
    setCamera();

    if (!picking) {
        glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    }
    else {
        glDisable(GL_LIGHTING);
    }

    // Draw Axis and Grid
    drawAxis(picking);
	drawInfiniteGrid(1.0f, 50);
    OdDrawingManager::R()->renderAll();

    if (!picking) {
        print_help();
        glutSwapBuffers();
        nframes++;
    }
}

void MathViewport::motionHandler(int x, int y)
{
    int dx = x - mouse_x; // Calculate the horizontal movement
    int dy = y - mouse_y; // Calculate the vertical movement

    // Update mouse position
    mouse_x = x;
    mouse_y = y;

    // If no movement, do nothing
    if (!(dx | dy)) return;

    if (bnstate[0]) { // Left button pressed: Rotate
        cam_theta += dx * 0.5f; // Adjust horizontal rotation
        cam_phi += dy * 0.5f;   // Adjust vertical rotation

        // Clamp vertical rotation to avoid flipping
        if (cam_phi < -90.0f) cam_phi = -90.0f;
        if (cam_phi > 90.0f) cam_phi = 90.0f;

        glutPostRedisplay(); // Trigger a redraw
    }

    if (bnstate[1]) { // Middle button pressed: Pan
        float up[3], right[3];
        float theta = cam_theta * static_cast<float>(OdPI) / 180.0f; // Convert to radians
        float phi = cam_phi * static_cast<float>(OdPI) / 180.0f;

        // Calculate the up vector
        up[0] = -sin(theta) * sin(phi);
        up[1] = -cos(phi);
        up[2] = cos(theta) * sin(phi);

        // Calculate the right vector
        right[0] = cos(theta);
        right[1] = 0.0f;
        right[2] = sin(theta);

        // Adjust pan based on mouse movement
        cam_pan[0] += (right[0] * dx + up[0] * dy) * 0.01f;
        cam_pan[1] += up[1] * dy * 0.01f;
        cam_pan[2] += (right[2] * dx + up[2] * dy) * 0.01f;

        glutPostRedisplay(); // Trigger a redraw
    }

    if (bnstate[2]) { // Right button pressed: Zoom
        cam_dist += dy * 0.1f; // Adjust zoom based on vertical movement
        if (cam_dist < 0.1f) cam_dist = 0.1f; // Clamp zoom to avoid negative distance

        glutPostRedisplay(); // Trigger a redraw
    }
}

void MathViewport::drawGridXY(bool picking, float size, float step) {
    if (picking) {
        setColorID(OBJ_GRID);
    }
    else {
        glDisable(GL_LIGHTING);
    }

    glBegin(GL_LINES);

    if (!picking)
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
    if (!picking) {
        glColor3f(1, 0, 0);
        glVertex3f(-size, 0, 0);
        glVertex3f(size, 0, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, -size, 0);
        glVertex3f(0, size, 0);
    }

    glEnd();

    if (!picking)
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

void MathViewport::drawAxis(bool picking, float size) {
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
        " Scale: right mouse drag up/down",
        "   Pan: middle mouse drag",
        "",
        "Toggle fullscreen: f",
        "Toggle animation: space",
        "Reset camera: r",
        "Quit: escape or q",
        nullptr
    };

    // Decide which text to show (brief or detailed)
    const char** text = help ? helptext : helpprompt;

    // Disable lighting and depth testing to ensure text is drawn correctly
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // Set up 2D orthographic projection for text rendering
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, win_width, 0, win_height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render each line of text
    int line = 0;
    for (const char** lineText = text; *lineText != nullptr; ++lineText, ++line) {
        // Shadow text (slightly offset and darker)
        glColor3f(0.0f, 0.1f, 0.0f); // Dark green
        glRasterPos2f(7, win_height - (line + 1) * 20 - 2);
        for (const char* c = *lineText; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        }

        // Foreground text
        glColor3f(0.0f, 0.9f, 0.0f); // Bright green
        glRasterPos2f(5, win_height - (line + 1) * 20);
        for (const char* c = *lineText; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        }
    }

    // Restore previous state
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}


void MathViewport::reshape(int x, int y) {
    float vsz, aspect = static_cast<float>(x) / static_cast<float>(y);
    win_width = x;
    win_height = y;
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    vsz = 0.4663f * 0.5f;
    glFrustum(-aspect * vsz, aspect * vsz, -vsz, vsz, 0.5, 500.0);
}

void MathViewport::keypress(unsigned char key, int x, int y) {
    static int fullscreen = 0; // To track fullscreen toggle state
    static int prev_width, prev_height; // To store previous window size

    switch (key) {
    case 27: // Escape key
    case 'q': // Quit application
        std::cout << "Quitting application..." << std::endl;
        exit(0);
        break;

    case ' ': // Toggle animation
        anim ^= 1;
        glutIdleFunc(anim ? [](void) { R()->idle(); } : nullptr); // Set idle callback for animation
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

    case 'f': // Toggle fullscreen mode
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

    case 'r': // Reset camera position
        cam_theta = 0;
        cam_phi = 25;
        cam_dist = 8;
        cam_pan[0] = cam_pan[1] = cam_pan[2] = 0;
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

    if (bn == GLUT_LEFT_BUTTON)
    {
        if (st == GLUT_DOWN) {
            OdSelectionPrompt::pickObjects(x, y);
            OdSelectionPrompt::resetWorldMouse(x, y);
        }
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

//bool MathViewport::rayIntersectsSphere(
//    const glm::vec3& rayOrigin,
//    const glm::vec3& rayDirection,
//    const glm::vec3& sphereCenter,
//    float sphereRadius,
//    float& t) {
//    // Vector from ray origin to sphere center
//    glm::vec3 L = sphereCenter - rayOrigin;
//
//    // Project L onto the ray direction
//    float tca = glm::dot(L, rayDirection);
//
//    // Compute the squared distance from the sphere center to the ray
//    float d2 = glm::dot(L, L) - tca * tca;
//    float radius2 = sphereRadius * sphereRadius;
//
//    // If d^2 > r^2, the ray does not intersect the sphere
//    if (d2 > radius2) return false;
//
//    // Compute distance from tca to the intersection points
//    float thc = sqrt(radius2 - d2);
//
//    // Calculate the two intersection distances
//    float t0 = tca - thc;
//    float t1 = tca + thc;
//
//    // Ensure t0 is the closest intersection
//    if (t0 > t1) std::swap(t0, t1);
//
//    // If both intersections are behind the ray origin, no intersection
//    if (t1 < 0) return false;
//
//    // If t0 is negative, use t1 instead
//    t = (t0 < 0) ? t1 : t0;
//
//    return true;
//}


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
}


OdBaseObjectPtr MathViewport::Clone()
{
    MathViewportPtr clone = MathViewport::createObject();
    return clone;
}

OdResult MathViewport::draw() const
{
    return OdResult();
}
