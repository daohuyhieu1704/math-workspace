#include "pch.h"
#include "OdMathPlane.h"

OdMathPlane::OdMathPlane()
{
}

OdResult OdMathPlane::draw() 
{
    const double planeSize = 5.0;
    OdGeVector3d normal = getNormal().normalize();
    OdGeVector3d u = normal.perpendicular().normalize() * planeSize;
    OdGeVector3d v = normal.crossProduct(u).normalize() * planeSize;
    OdGePoint3d origin = getOrigin() * m_transform;
    OdGePoint3d p1 = (origin - u - v) * m_transform;
    OdGePoint3d p2 = (origin + u - v) * m_transform;
    OdGePoint3d p3 = (origin + u + v) * m_transform;
    OdGePoint3d p4 = (origin - u + v) * m_transform;
    getExtents().reset();
    glBegin(GL_QUADS);
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p4.x, p4.y, p4.z);
	getExtents().appendPoint_s(p1);
	getExtents().appendPoint_s(p2);
	getExtents().appendPoint_s(p3);
	getExtents().appendPoint_s(p4);
	getExtents().appendFace({ 0, 1, 2, 3 });
    glEnd();
    // drawNormalVector(origin, normal, u, v, planeSize);
    return eOk;
}

OdBaseObjectPtr OdMathPlane::Clone()
{
	OdMathPlanePtr clone = OdMathPlane::createObject();
	clone->setOrigin(getOrigin());
	clone->setNormal(getNormal());
	return clone;
}

void OdMathPlane::drawNormalVector(OdGePoint3d origin, OdGeVector3d normal, OdGeVector3d u, OdGeVector3d v, double planeSize) const
{   
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the normal vector

    // Draw the normal vector as a line
    OdGePoint3d arrowBase = origin + normal * planeSize * 0.2; // Base of the arrow
    OdGePoint3d arrowTip = origin + normal * planeSize * 0.4;  // Tip of the arrow

    glBegin(GL_LINES);
    glVertex3f(arrowBase.x, arrowBase.y, arrowBase.z); // Start of the line
    glVertex3f(arrowTip.x, arrowTip.y, arrowTip.z);    // End of the line
    glEnd();

    glBegin(GL_TRIANGLES);

    OdGeVector3d arrowSide1 = u.normalize() * (planeSize * 0.1); // Arrowhead side vector 1
    OdGeVector3d arrowSide2 = v.normalize() * (planeSize * 0.1); // Arrowhead side vector 2

    OdGePoint3d arrowLeft = arrowTip - arrowSide1; // Left vertex of the arrowhead
    OdGePoint3d arrowRight = arrowTip - arrowSide2; // Right vertex of the arrowhead

    glVertex3f(arrowTip.x, arrowTip.y, arrowTip.z);     // Tip of the arrowhead
    glVertex3f(arrowLeft.x, arrowLeft.y, arrowLeft.z);  // Left base
    glVertex3f(arrowRight.x, arrowRight.y, arrowRight.z); // Right base

    glEnd();
}

