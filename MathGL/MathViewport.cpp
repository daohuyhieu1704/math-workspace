#include "pch.h"
#include "MathViewport.h"

MathViewport::MathViewport() :
	cam_dist(10),
	cam_phi(0),
	cam_theta(0),
	cam_pan{ 0, 0, 0 }
{
}

OdBaseObjectPtr MathViewport::Clone()
{
	return MathViewportPtr();
}

OdResult MathViewport::draw() const
{
    try
    {
        glTranslatef(0, 0, -cam_dist);
        glRotatef(cam_phi, 1, 0, 0);
        glRotatef(cam_theta, 0, 1, 0);
        glTranslatef(cam_pan[0], cam_pan[1], cam_pan[2]);
        return eOk;
    }
    catch (const std::exception&)
    {
        return OdResult::eInvalidDrawing;
    }
}

void MathViewport::motion(int x, int y)
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
		float theta = cam_theta * OdPI / 180.0f;
		float phi = cam_phi * OdPI / 180.0f;

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