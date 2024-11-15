#pragma once
#include <OdGiDrawable.h>
#include <OdGePoint2d.h>
#include <OdGePoint3d.h>

using namespace GeometryNative;

typedef OdSmartPtr<class MathViewport> MathViewportPtr;
class MathViewport : public OdGiDrawable {
    OD_RTTI_DECLARE(MathViewport, OdGiDrawable);
public:
    MathViewport();

#pragma region Properties
	int getWidth() const { return win_width; }
	void setWidth(int width) { win_width = width; }
	int getHeight() const { return win_height; }
	void setHeight(int height) { win_height = height; }
	float getTheta() const { return rotateY; }
	void setTheta(float theta) { rotateY = theta; }
	float getPhi() const { return rotateX; }
	void setPhi(float phi) { rotateX = phi; }
	float getDistance() const { return cam_dist; }
	void setDistance(float distance) { cam_dist = distance; }
	float* getPan() { return cam_pan; }
	void setPan(float x, float y, float z) { cam_pan[0] = x; cam_pan[1] = y; cam_pan[2] = z; }
	int getMouseX() const { return mouse_x; }
	void setMouseX(int x) { mouse_x = x; }
	int getMouseY() const { return mouse_y; }
	void setMouseY(int y) { mouse_y = y; }
	int* getButtonState() { return bnstate; }
	void setButtonState(int idx, int state) { bnstate[idx] = state; }
#pragma endregion
    OdBaseObjectPtr Clone() override;
    OdResult draw() const override;
	void motion(int x, int y);
private:
	int win_width, win_height;
	float rotateY, rotateX = 25, cam_dist = 8;
	float cam_pan[3];
	int mouse_x, mouse_y;
	int bnstate[8];
};

OD_RTTI_DEFINE(MathViewport, OdGiDrawable)