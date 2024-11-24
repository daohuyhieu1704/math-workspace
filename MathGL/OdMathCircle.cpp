#include "pch.h"
#include "OdMathCircle.h"

OdMathCircle::OdMathCircle() : OdDbCircle()
{
}

OdMathCircle::OdMathCircle(OdGePoint3d center, double radius) : OdDbCircle()
{
	setCenter(center);
	setRadius(radius);
}

OdResult OdMathCircle::draw() const
{
	glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < m_segments; i++) {
        float angle = 2.0f * OdPI * i / m_segments;
        float x = getCenter().x + getRadius() * cos(angle);
        float y = getCenter().y + getRadius() * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
	glEnable(GL_LIGHTING);
	return OdResult::eOk;
}
