#include "pch.h"
#include "OdMath3dSolid.h"
#include "OdDrawingManager.h"
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include "DrawingManager.h"
#include <string>
#include <map>
#include <iostream>
#include "OdMathCircle.h"
#include "OdMathLine.h"
#include "MathViewport.h"
#include "LineCmd.h"
#include "MathArc.h"
#include "OdMathPlane.h"
#include "OdMathPolyline.h"
#include <MathLog.h>

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

MathViewportPtr viewport = MathViewport::R();

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

int MathGL::DrawingManager::exitGLUT()
{
	exit(0);
	return 0;
}

void MathGL::DrawingManager::TLViewport()
{
	viewport->TLViewport();
}

void MathGL::DrawingManager::TMViewport()
{
	viewport->TMViewport();
}

void MathGL::DrawingManager::TRViewport()
{
	viewport->TRViewport();
}

void MathGL::DrawingManager::MLViewport()
{
	viewport->MLViewport();
}

void MathGL::DrawingManager::TMMViewport()
{
	viewport->TMMViewport();
}

void MathGL::DrawingManager::BMMViewport()
{
	viewport->BMMViewport();
}

void MathGL::DrawingManager::MRViewport()
{
	viewport->MRViewport();
}

void MathGL::DrawingManager::BLViewport()
{
	viewport->BLViewport();
}

void MathGL::DrawingManager::BMViewport()
{
	viewport->BMViewport();
}

void MathGL::DrawingManager::BRViewport()
{
	viewport->BRViewport();
}

List<String^>^ MathGL::DrawingManager::GetAllEntityJsons()
{
	if (!OdHostAppService::R()->getCurrentSession()) return nullptr;
	const auto& ents = OdHostAppService::R()->getCurrentSession()->getEntities();
	List<String^>^ retVal = gcnew List<String^>(ents.size());
	for (const auto& ent : ents)
	{
		OdDbEntity* entity = static_cast<OdDbEntity*>(ent.get());
		if (entity)
		{
			retVal->Add(gcnew String(static_cast<OdDbEntity*>(ent.get())->toJson().dump().c_str()));
		}
	}
	return retVal;
}

void MathGL::DrawingManager::createSession(String^ fileName)
{
	OdHostAppService::R()->createSession();
	std::string name = UtilCLI::convertToStdString(fileName);
	OdHostAppService::R()->getCurrentSession()->setFileName(name);
}

void MathGL::DrawingManager::changeSession(unsigned int sessionId)
{
	OdHostAppService::R()->ChangeCurrSession(sessionId);
}

void MathGL::DrawingManager::appendPrompt(String^ prompt)
{
	if (!OdHostAppService::R()->getCurrentSession()) return;
	std::string promptStr = UtilCLI::convertToStdString(prompt);
	OdHostAppService::R()->getCurrentSession()->getPrompts()->appendPrompt(promptStr);
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

	viewport->setParentHwnd(parentHwnd);
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
	//OdMath3dSolidPtr solid = OdMath3dSolid::createObject();
	//solid->setType(SolidType::Box);
	//OdDrawingManager::R()->appendEntity(solid);
	//OdMathPlanePtr plane = OdMathPlane::createObject();
	//plane->setOrigin(OdGePoint3d(0, 0, 0));
	//plane->setNormal(OdGeVector3d(0, 0, 1));
	//OdDrawingManager::R()->appendEntity(plane);
	return hwnd;
}

OdBaseObjectPtr OdDrawingManager::Clone()
{
	return OdDrawingManagerPtr();
}

void OdDrawingManager::InitFactory()
{
	OdMathLine::registerClass();
	OdMathCircle::registerClass();
	OdMathArc::registerClass();
	OdMathPolyline::registerClass();
	OdMathPlane::registerClass();
	OdMath3dSolid::registerClass();
}

void OdDrawingManager::CreateSession(std::string fileName)
{
	OdHostAppService::R()->createSession();
	OdHostAppService::R()->getCurrentSession()->setFileName(fileName);
}

void OdDrawingManager::ChangeSession(unsigned int sessionId)
{
	OdHostAppService::R()->ChangeCurrSession(sessionId);
}

void OdDrawingManager::AppendCommand(const std::string command)
{
	if (!OdHostAppService::R()->getCurrentSession()) return;
	OdHostAppService::R()->getCurrentSession()->getPrompts()->appendCommand(command);
}

void OdDrawingManager::AppendPrompt(const std::string prompt)
{
	if (!OdHostAppService::R()->getCurrentSession()) return;
	OdHostAppService::R()->getCurrentSession()->getPrompts()->appendPrompt(prompt);
}

void OdDrawingManager::renderAll()
{
	if (OdHostAppService::R()->getCurrentSession())
	{
		const auto& entities = OdHostAppService::R()->getCurrentSession()->getEntities();
		for (const auto& entity : entities)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			OdDbEntity* objRaw = static_cast<OdDbEntity*>(entity.get());
			if (objRaw)
			{
				glLoadName(objRaw->id());
				if (objRaw->isSelected())
				{
					glColor3f(1.0f, 0.0f, 0.0f);
				}
				else
				{
					float color[3] = { objRaw->getColor().r, objRaw->getColor().g, objRaw->getColor().b };
					glColor3f(color[0], color[1], color[2]);
				}
				objRaw->draw();
				// std::string jsonString = objRaw->toJson().dump();
				// MathLog::LogFunction("Entity json: " + jsonString);
				// drawBoundingBox(objRaw->getExtents());
			}
		}
	}
}

void OdDrawingManager::SetPointPickedCallback(PointPickedCallback callback)
{
	pointPickedCallback = callback;
}

void OdDrawingManager::TriggerPointPicked(std::vector<OdGePoint3d> resPnt)
{
	if (pointPickedCallback) {
		pointPickedCallback(resPnt);
	}
}

void OdDrawingManager::SetEntityPickedCallback(EntityPickedCallback callback)
{
	entityPickedCallback = callback;
}

void OdDrawingManager::TriggerEntityPicked(const std::vector<OdDbObjectId>& resId) {
	if (entityPickedCallback) {
		entityPickedCallback(resId);
	}
}

void OdDrawingManager::drawBoundingBox(const OdGeExtents3d& extents) {
	// Extract min and max points
	OdGePoint3d minPnt = extents.GetMinPnt();
	OdGePoint3d maxPnt = extents.GetMaxPnt();

	// Calculate all 8 corners of the box
	OdGePoint3d corners[8] = {
		{minPnt.x, minPnt.y, minPnt.z}, // Bottom-left-front
		{maxPnt.x, minPnt.y, minPnt.z}, // Bottom-right-front
		{maxPnt.x, maxPnt.y, minPnt.z}, // Bottom-right-back
		{minPnt.x, maxPnt.y, minPnt.z}, // Bottom-left-back
		{minPnt.x, minPnt.y, maxPnt.z}, // Top-left-front
		{maxPnt.x, minPnt.y, maxPnt.z}, // Top-right-front
		{maxPnt.x, maxPnt.y, maxPnt.z}, // Top-right-back
		{minPnt.x, maxPnt.y, maxPnt.z}  // Top-left-back
	};

	// Set line color to green
	glColor3f(0.0f, 1.0f, 0.0f);
	// Draw edges of the bounding box
	glBegin(GL_LINES);
	// Bottom face
	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[1].x, corners[1].y, corners[1].z);

	glVertex3f(corners[1].x, corners[1].y, corners[1].z);
	glVertex3f(corners[2].x, corners[2].y, corners[2].z);

	glVertex3f(corners[2].x, corners[2].y, corners[2].z);
	glVertex3f(corners[3].x, corners[3].y, corners[3].z);

	glVertex3f(corners[3].x, corners[3].y, corners[3].z);
	glVertex3f(corners[0].x, corners[0].y, corners[0].z);

	// Top face
	glVertex3f(corners[4].x, corners[4].y, corners[4].z);
	glVertex3f(corners[5].x, corners[5].y, corners[5].z);

	glVertex3f(corners[5].x, corners[5].y, corners[5].z);
	glVertex3f(corners[6].x, corners[6].y, corners[6].z);

	glVertex3f(corners[6].x, corners[6].y, corners[6].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	glVertex3f(corners[7].x, corners[7].y, corners[7].z);
	glVertex3f(corners[4].x, corners[4].y, corners[4].z);

	// Vertical edges
	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[4].x, corners[4].y, corners[4].z);

	glVertex3f(corners[1].x, corners[1].y, corners[1].z);
	glVertex3f(corners[5].x, corners[5].y, corners[5].z);

	glVertex3f(corners[2].x, corners[2].y, corners[2].z);
	glVertex3f(corners[6].x, corners[6].y, corners[6].z);

	glVertex3f(corners[3].x, corners[3].y, corners[3].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);
	glEnd();
}
