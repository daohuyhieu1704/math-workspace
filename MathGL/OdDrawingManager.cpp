#include "pch.h"
#include "OdDrawingManager.h"
#include "pch.h"
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include "DrawingManager.h"
#include <string>
#include <map>
#include <iostream>
#include "MathCircle.h"
#include "MathViewport.h"
#include "LineCmd.h"

OD_RTTI_SINGLETON_DEFINE(OdDrawingManager)

std::map<int, std::string> objectMap;

int argc = 1;
char* argv[] = { (char*)"MathWorkspace" };

int selectedObjectID = -1; // -1 means no object is selected
#ifdef _MSC_VER

#pragma warning (disable: 4305 4244)
#endif

static const char* helpprompt[] = { "Press F1 for help", 0 };
static const char* helptext[] = {
	"Rotate: left mouse drag",
	" Scale: right mouse drag up/down",
	"   Pan: middle mouse drag",
	"",
	"Toggle fullscreen: f",
	"Toggle animation: space",
	"Quit: escape",
	0
};

void idle(void);
void display(void);
void drawScene(bool picking = false);
void print_help(void);
void reshape(int x, int y);
void keypress(unsigned char key, int x, int y);
void skeypress(int key, int x, int y);
void mouse(int bn, int st, int x, int y);
void motion(int x, int y);
void pickObject(int x, int y);
void setColorID(int id);

int anim, help;
long anim_start;
long nframes;

#ifndef GL_FRAMEBUFFER_SRGB
#define GL_FRAMEBUFFER_SRGB	0x8db9
#endif

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809d
#endif

// Define object IDs
#define OBJ_TORUS 1
#define OBJ_SPHERE 2
#define OBJ_CUBE 3
#define OBJ_CONE 4
#define OBJ_TEAPOT 5
#define OBJ_PLANE 6
#define OBJ_AXIS 7
#define OBJ_GRID 8

MathViewportPtr viewport;

HWND GetGLUTWindowHandle()
{
	// Get the title of the current GLUT window
	char title[256];
	GetWindowTextA(GetForegroundWindow(), title, sizeof(title));

	// Find the window handle based on the title
	HWND hwnd = FindWindowA(NULL, title);

	return hwnd;
}

void drawGridXY(bool picking = false, float size = 10.0f, float step = 1.0f)
{
	if (picking)
	{
		setColorID(OBJ_GRID);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}

	glBegin(GL_LINES);

	if (!picking)
		glColor4f(0.5f, 0.5f, 0.5f, 0.5f);

	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	for (float i = step; i <= size; i += step)
	{
		glVertex3f(-size, i, 0);
		glVertex3f(size, i, 0);
		glVertex3f(-size, -i, 0);
		glVertex3f(size, -i, 0);

		glVertex3f(i, -size, 0);
		glVertex3f(i, size, 0);
		glVertex3f(-i, -size, 0);
		glVertex3f(-i, size, 0);
	}
	if (!picking)
	{
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


void drawAxis(bool picking = false, float size = 2.5f)
{
	glLineWidth(2.0f);

	if (picking)
	{
		setColorID(OBJ_AXIS);
		glBegin(GL_LINES);
		// Draw X-axis
		glVertex3f(0.0f, 0.0f, 0.0f); // Origin
		glVertex3f(10.0f, 0.0f, 0.0f); // Point on X-axis
		// Draw Y-axis
		glVertex3f(0.0f, 0.0f, 0.0f); // Origin
		glVertex3f(0.0f, 10.0f, 0.0f); // Point on Y-axis
		glEnd();
	}
	else
	{
		// Draw X-axis in red
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f(0.0f, 0.0f, 0.0f); // Origin
		glVertex3f(10.0f, 0.0f, 0.0f); // Point on X-axis
		glEnd();

		// Draw Y-axis in green
		glBegin(GL_LINES);
		glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex3f(0.0f, 0.0f, 0.0f); // Origin
		glVertex3f(0.0f, 10.0f, 0.0f); // Point on Y-axis
		glEnd();

		// Draw the origin point
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(0.0f, 0.0f, 0.0f); // Origin
		glEnd();
	}
}

int MathGL::DrawingManager::ProcessGLUTEvents()
{
	glutMainLoop();
	return 0;
}

void idle(void)
{
	glutPostRedisplay();
}

void display(void)
{
	drawScene(false); // Regular rendering
}

void drawScene(bool picking)
{
	long tm;
	float lpos[] = { -1, 2, 3, 0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	viewport->draw();

	if (!picking)
	{
		glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}

	MathCirclePtr circle = MathCircle::createObject();
	circle->setCenter(OdGePoint3d(0, 0, 0));
	circle->setRadius(50.0);
	circle->draw();

	// Draw Axis and Grid
	drawAxis(picking);
	drawGridXY(picking);

	if (!picking)
	{
		print_help();
		glutSwapBuffers();
		nframes++;
	}
}

void print_help(void)
{
	int i;
	const char* s, ** text;

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, viewport->getWidth(), 0, viewport->getHeight(), -1, 1);

	text = help ? helptext : helpprompt;

	for (i = 0; text[i]; i++) {
		glColor3f(0, 0.1, 0);
		glRasterPos2f(7, viewport->getHeight() - (i + 1) * 20 - 2);
		s = text[i];
		while (*s) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *s++);
		}
		glColor3f(0, 0.9, 0);
		glRasterPos2f(5, viewport->getHeight() - (i + 1) * 20);
		s = text[i];
		while (*s) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *s++);
		}
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPopAttrib();
}

#define ZNEAR	0.5f
void reshape(int x, int y)
{
	float vsz, aspect = (float)x / (float)y;
	viewport->setWidth(x);
	viewport->setHeight(y);
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	vsz = 0.4663f * ZNEAR;
	glFrustum(-aspect * vsz, aspect * vsz, -vsz, vsz, 0.5, 500.0);
}

void keypress(unsigned char key, int x, int y)
{
	static int fullscr;
	static int prev_xsz, prev_ysz;

	switch (key) {
	case 27:
	case 'q':
		exit(0);
		break;

	case ' ':
		anim ^= 1;
		glutIdleFunc(anim ? idle : 0);
		glutPostRedisplay();

		if (anim) {
			anim_start = glutGet(GLUT_ELAPSED_TIME);
			nframes = 0;
		}
		else {
			long tm = glutGet(GLUT_ELAPSED_TIME) - anim_start;
			long fps = (nframes * 100000) / tm;
			printf("framerate: %ld.%ld fps\n", fps / 100, fps % 100);
		}
		break;

	case '\n':
	case '\r':
		if (!(glutGetModifiers() & GLUT_ACTIVE_ALT)) {
			break;
		}
	case 'f':
		fullscr ^= 1;
		if (fullscr) {
			prev_xsz = glutGet(GLUT_WINDOW_WIDTH);
			prev_ysz = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();
		}
		else {
			glutReshapeWindow(prev_xsz, prev_ysz);
		}
		break;
	}
}

void skeypress(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_F1:
		help ^= 1;
		glutPostRedisplay();

	default:
		break;
	}
}

void mouse(int bn, int st, int x, int y)
{
	int bidx = bn - GLUT_LEFT_BUTTON;
	viewport->setButtonState(bidx, st == GLUT_DOWN);
	viewport->setMouseX(x);
	viewport->setMouseY(y);
	if (bn == GLUT_LEFT_BUTTON && st == GLUT_DOWN)
	{
		pickObject(x, y);
	}
}

void motion(int x, int y)
{
	viewport->motion(x, y);
}

// Function to set unique color ID
void setColorID(int id)
{
	GLubyte r = id & 0xFF;
	GLubyte g = (id >> 8) & 0xFF;
	GLubyte b = (id >> 16) & 0xFF;
	glColor3ub(r, g, b);
}

// Picking function
void pickObject(int x, int y)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// Set up off-screen rendering for picking
	glReadBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScene(true); // Render with unique colors for picking

	// Read the color at the clicked position
	GLubyte pixel[3];
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

	int colorID = (pixel[0]) | (pixel[1] << 8) | (pixel[2] << 16);
	auto it = objectMap.find(colorID);
	if (it != objectMap.end())
	{
		selectedObjectID = colorID; // Set selected object ID
		std::cout << "Selected object: " << it->second << std::endl;
	}
	else
	{
		selectedObjectID = -1; // No object selected
		std::cout << "No object selected." << std::endl;
	}

	// Restore normal rendering
	glutPostRedisplay();
}

HWND OdDrawingManager::InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("freeglut 3D view demo");

	HWND hwnd = GetGLUTWindowHandle();

	SetParent(hwnd, parentHwnd);

	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style = (style & ~(WS_CAPTION | WS_POPUP)) | WS_CHILD;
	SetWindowLong(hwnd, GWL_STYLE, style);

	SetWindowPos(hwnd, nullptr, 0, 0, 800, 600, SWP_FRAMECHANGED | SWP_SHOWWINDOW);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keypress);
	glutSpecialFunc(skeypress);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	return hwnd;
}

OdBaseObjectPtr OdDrawingManager::Clone()
{
	return OdDrawingManagerPtr();
}

void OdDrawingManager::CreateSession(std::string fileName)
{
	OdHostAppService::R()->createSession(fileName);
	RegisterCommandPattern();
}

void OdDrawingManager::ChangeSession(std::string filePath)
{
	OdHostAppService::R()->ChangeCurrSession(filePath);
	m_entities.clear();
	OdHostAppService::R()->getCurrentSession()->ExecuteAllPrompts();
}

void OdDrawingManager::AppendCommand(const std::string command)
{
	OdHostAppService::R()->getCurrentSession()->getPrompts()->appendCommand(command);
}

void OdDrawingManager::AppendPrompt(const std::string prompt)
{
	OdHostAppService::R()->getCurrentSession()->getPrompts()->appendPrompt(prompt);
}

void OdDrawingManager::RegisterCommandPattern()
{
	//LineCmdPtr lineCmd = LineCmd::createObject();
	//OdHostAppService::R()->getCurrentSession()->getPrompts()->registerCommand("LINE", dynamic_cast<IActionCmd*>(lineCmd.get()));
}
