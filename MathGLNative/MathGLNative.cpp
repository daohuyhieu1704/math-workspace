// MathGLNative.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MathGLNative.h"
#include <stdio.h>
#include <string>
#include <math.h>
#include <GL/freeglut.h>
#include <vector>

#define MAX_LOADSTRING 100

#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4305 4244)
#endif

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
void print_help(void);
void reshape(int x, int y);
void keypress(unsigned char key, int x, int y);
void skeypress(int key, int x, int y);
void mouse(int bn, int st, int x, int y);
void motion(int x, int y);

int win_width, win_height;
float cam_theta, cam_phi = 25, cam_dist = 8;
float cam_pan[3];
int mouse_x, mouse_y;
int bnstate[8];
int anim, help;
long anim_start;
long nframes;

#ifndef GL_FRAMEBUFFER_SRGB
#define GL_FRAMEBUFFER_SRGB	0x8db9
#endif

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809d
#endif

std::vector<char*> ConvertLPWSTRToArgv(LPWSTR lpCmdLine, int& argc)
{
	std::vector<char*> argv;
	std::wstring ws(lpCmdLine);
	std::string cmd(ws.begin(), ws.end());

	// Simple split by space (for demonstration; consider edge cases)
	std::string arg;
	for (auto c : cmd)
	{
		if (c == ' ')
		{
			if (!arg.empty())
			{
				argv.push_back(_strdup(arg.c_str()));
				arg.clear();
			}
		}
		else
		{
			arg += c;
		}
	}
	if (!arg.empty())
	{
		argv.push_back(_strdup(arg.c_str()));
	}

	argc = static_cast<int>(argv.size());
	return argv;
}

void initializeOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set up lighting parameters
	GLfloat lightPos[] = { 0.0f, 0.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// Additional OpenGL initialization as needed
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MATHGLNATIVE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Convert command-line arguments
	int argc;
	std::vector<char*> argv = ConvertLPWSTRToArgv(lpCmdLine, argc);

	// Initialize GLUT
	glutInit(&argc, argv.data());
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MathGLNative Application");

	// Initialize OpenGL states
	initializeOpenGL();

	// Register GLUT callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keypress);
	glutSpecialFunc(skeypress);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	// Perform application initialization
	if (!InitInstance(hInstance, nCmdShow))
	{
		// Free allocated resources
		for (auto arg : argv) {
			free(arg);
		}
		return -1;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MATHGLNATIVE));

	// Enter the main loop
	glutMainLoop();

	// Free allocated resources (if glutMainLoop ever exits, which it typically doesn't)
	for (auto arg : argv) {
		free(arg);
	}

	return 0;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MATHGLNATIVE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MATHGLNATIVE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void idle(void)
{
	glutPostRedisplay();
}

void display(void)
{
	long tm;
	float lpos[] = { -1, 2, 3, 0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -cam_dist);
	glRotatef(cam_phi, 1, 0, 0);
	glRotatef(cam_theta, 0, 1, 0);
	glTranslatef(cam_pan[0], cam_pan[1], cam_pan[2]);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);

	glPushMatrix();
	if (anim) {
		tm = glutGet(GLUT_ELAPSED_TIME) - anim_start;
		glRotatef(tm / 10.0f, 1, 0, 0);
		glRotatef(tm / 10.0f, 0, 1, 0);
	}
	glutSolidTorus(0.3, 1, 16, 24);
	glPopMatrix();

	glutSolidSphere(0.4, 16, 8);

	glPushMatrix();
	glTranslatef(-2.5, 0, 0);
	glutSolidCube(1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, -1, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1.1, 2, 16, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.5, 2.5);
	glFrontFace(GL_CW);
	glutSolidTeapot(1.0);
	glFrontFace(GL_CCW);
	glPopMatrix();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-5, -1.3, 5);
	glVertex3f(5, -1.3, 5);
	glVertex3f(5, -1.3, -5);
	glVertex3f(-5, -1.3, -5);
	glEnd();

	print_help();

	glutSwapBuffers();
	nframes++;
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
	glOrtho(0, win_width, 0, win_height, -1, 1);

	text = help ? helptext : helpprompt;

	for (i = 0; text[i]; i++) {
		glColor3f(0, 0.1, 0);
		glRasterPos2f(7, win_height - (i + 1) * 20 - 2);
		s = text[i];
		while (*s) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *s++);
		}
		glColor3f(0, 0.9, 0);
		glRasterPos2f(5, win_height - (i + 1) * 20);
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
	win_width = x;
	win_height = y;

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
	bnstate[bidx] = st == GLUT_DOWN;
	mouse_x = x;
	mouse_y = y;
}

void motion(int x, int y)
{
	int dx = x - mouse_x;
	int dy = y - mouse_y;
	mouse_x = x;
	mouse_y = y;

	if (!(dx | dy)) return;

	if (bnstate[0]) {
		cam_theta += dx * 0.5;
		cam_phi += dy * 0.5;
		if (cam_phi < -90) cam_phi = -90;
		if (cam_phi > 90) cam_phi = 90;
		glutPostRedisplay();
	}
	if (bnstate[1]) {
		float up[3], right[3];
		float theta = cam_theta * M_PI / 180.0f;
		float phi = cam_phi * M_PI / 180.0f;

		up[0] = -sin(theta) * sin(phi);
		up[1] = -cos(phi);
		up[2] = cos(theta) * sin(phi);
		right[0] = cos(theta);
		right[1] = 0;
		right[2] = sin(theta);

		cam_pan[0] += (right[0] * dx + up[0] * dy) * 0.01;
		cam_pan[1] += up[1] * dy * 0.01;
		cam_pan[2] += (right[2] * dx + up[2] * dy) * 0.01;
		glutPostRedisplay();
	}
	if (bnstate[2]) {
		cam_dist += dy * 0.1;
		if (cam_dist < 0) cam_dist = 0;
		glutPostRedisplay();
	}
}