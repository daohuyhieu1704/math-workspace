#pragma once
#include <glm/glm.hpp>
#include <OdGiDrawable.h>
#include <OdGePoint2d.h>
#include <OdGePoint3d.h>

using namespace GeometryNative;

#define ZNEAR	0.5f

#define OBJ_TORUS 1
#define OBJ_SPHERE 2
#define OBJ_CUBE 3
#define OBJ_CONE 4
#define OBJ_TEAPOT 5
#define OBJ_PLANE 6
#define OBJ_AXIS 7
#define OBJ_GRID 8

typedef OdSmartPtr<class MathViewport> MathViewportPtr;
class MathViewport : public OdGiDrawable {
    OD_RTTI_DECLARE(MathViewport, OdGiDrawable)
        OD_RTTI_SINGLETON_DECLARE(MathViewport)
public:
    // Constructor
    MathViewport();
    virtual ~MathViewport() = default;

    // Member variables
    double cameraPos[3] = { 0.0, 0.0, 50.0 };
    double cameraTarget[3] = { 0.0, 0.0, 0.0 };
    double cameraUp[3] = { 0.0, 0.0, 1.0 };
    void applyCameraAndProjection();
    void setCameraPosition(double x, double y, double z) {
        cameraPos[0] = x; cameraPos[1] = y; cameraPos[2] = z;
    }
    void setCameraTarget(double x, double y, double z) {
        cameraTarget[0] = x; cameraTarget[1] = y; cameraTarget[2] = z;
    }
    void setCameraUp(double x, double y, double z) {
        cameraUp[0] = x; cameraUp[1] = y; cameraUp[2] = z;
    }

    int win_width = 800, win_height = 600;
    float cam_theta = 0, cam_phi = 0, cam_dist = 100;
    float cam_pan[3] = { 0.0f, 0.0f, 0.0f };
    int mouse_x = 0, mouse_y = 0;
    int bnstate[8] = { 0 };
    int anim = 0, help = 0;
    long anim_start = 0;
    long nframes = 0;

    // Matrices and camera properties
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 cameraPosition;

    // Member functions
    void idle();
    void display();
    void drawScene();
    void print_help();
    void reshape(int x, int y);
    void keypress(unsigned char key, int x, int y);
    void skeypress(int key, int x, int y);
    void mouse(int bn, int st, int x, int y);
    void motion(int x, int y);
    void setColorID(int id);
    void setButtonState(int idx, bool state) { bnstate[idx] = state; }
    void setMouseX(int x) { mouse_x = x; }
    void setMouseY(int y) { mouse_y = y; }
    void motionHandler(int x, int y);
    void drawGridXY(float size = 10.0f, float step = 1.0f);
    void drawAxis(float size = 2.5f);
    void pickObject(int x, int y);
    void drawInfiniteGrid(float spacing = 1.0f, int halfSize = 50) const;
    void setCamera();

    void TLViewport();
    void TMViewport();
    void TRViewport();
    void MLViewport();
    void TMMViewport();
    void BMMViewport();
    void MRViewport();
    void BLViewport();
    void BMViewport();
    void BRViewport();

    // Inherited via OdGiDrawable
    OdBaseObjectPtr Clone() override;
    OdResult draw() override;
	void setParentHwnd(HWND hwnd) { m_parentHwnd = hwnd; }
private:
    HWND m_parentHwnd;
};
