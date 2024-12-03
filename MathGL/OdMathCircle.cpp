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

OdBaseObjectPtr OdMathCircle::Clone()
{
	OdMathCirclePtr clone = OdMathCircle::createObject();
	clone->setCenter(getCenter());
	clone->setRadius(getRadius());
    return clone;
}

OdResult OdMathCircle::draw() 
{
	glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
	getExtents().reset();
	std::vector<int> face;
    for (int i = 0; i < m_segments; i++) {
        float angle = 2.0f * OdPI * i / m_segments;
        float x = getCenter().x + getRadius() * cos(angle);
        float y = getCenter().y + getRadius() * sin(angle);
		OdGePoint3d transformPnt = (OdGePoint3d(x, y, getCenter().z) * m_scale) * m_transform;
		getExtents().appendPoint_s(transformPnt);
		face.push_back(i);
        glVertex3f(transformPnt.x, transformPnt.y, transformPnt.z);
    }
	getExtents().appendFace(face);
    glEnd();
	return OdResult::eOk;
}
