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
#include "MathArc.h"

OD_RTTI_SINGLETON_DEFINE(OdDrawingManager)

std::map<int, std::string> objectMap;

int argc = 1;
char* argv[] = { (char*)"MathWorkspace" };

int selectedObjectID = -1; // -1 means no object is selected
#ifdef _MSC_VER

#pragma warning (disable: 4305 4244)
#endif

#ifndef GL_FRAMEBUFFER_SRGB
#define GL_FRAMEBUFFER_SRGB	0x8db9
#endif

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809d
#endif

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

int MathGL::DrawingManager::ProcessGLUTEvents()
{
	glutMainLoop();
	return 0;
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

	glutDisplayFunc([]() { viewport->display(); });
	glutReshapeFunc([](int x, int y) { viewport->reshape(x, y); });
	glutKeyboardFunc([](unsigned char key, int x, int y) { viewport->keypress(key, x, y); });
	glutSpecialFunc([](int key, int x, int y) { viewport->skeypress(key, x, y); });
	glutMouseFunc([](int bn, int st, int x, int y) { viewport->mouse(bn, st, x, y); });
	glutMotionFunc([](int x, int y) { viewport->motion(x, y); });

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
