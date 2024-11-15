#include "pch.h"
#include "MathCircle.h"

MathCircle::MathCircle() : OdDbCircle()
{
}

MathCircle::MathCircle(OdGePoint3d center, double radius) : OdDbCircle()
{
	setCenter(center);
	setRadius(radius);
}

OdResult MathCircle::draw() const
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < m_segments; i++) {
        float angle = 2.0f * OdPI * i / m_segments;
        float x = getCenter().x + getRadius() * cos(angle);
        float y = getCenter().y + getRadius() * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
	return OdResult::eOk;
}
