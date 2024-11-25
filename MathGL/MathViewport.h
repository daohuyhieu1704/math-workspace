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
    int win_width = 800, win_height = 600;
    float cam_theta = 0, cam_phi = 25, cam_dist = 8;
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
    void drawScene(bool picking = false);
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
    void drawGridXY(bool picking = false, float size = 10.0f, float step = 1.0f);
    void drawAxis(bool picking = false, float size = 2.5f);
    void pickObject(int x, int y);
    void drawInfiniteGrid(float spacing = 1.0f, int halfSize = 50) const;
    void setCamera();
    // Inherited via OdGiDrawable
    OdBaseObjectPtr Clone() override;
    OdResult draw() const override;
};
