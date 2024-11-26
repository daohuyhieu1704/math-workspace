#include "pch.h"
#include "MathPolyline.h"

OdMathPolyline::OdMathPolyline()
{
}

void OdMathPolyline::drawArc(const OdGePoint3d& start, const OdGePoint3d& end, double bulge) const {
    if (bulge == 0.0) {
        // Straight line segment
        glVertex3d(start.x, start.y, start.z);
        glVertex3d(end.x, end.y, end.z);
        return;
    }

    double dx = end.x - start.x;
    double dy = end.y - start.y;
    double chordLength = sqrt(dx * dx + dy * dy);

    // Calculate the included angle using bulge
    double includedAngle = 4 * atan(fabs(bulge));
    double radius = chordLength / (2 * sin(includedAngle / 2.0));

    // Determine arc center
    double sagitta = radius * (1 - cos(includedAngle / 2.0));
    double cx, cy;

    if (bulge > 0.0) {
        cx = (start.x + end.x) / 2.0 - dy * sagitta / chordLength;
        cy = (start.y + end.y) / 2.0 + dx * sagitta / chordLength;
    }
    else {
        cx = (start.x + end.x) / 2.0 + dy * sagitta / chordLength;
        cy = (start.y + end.y) / 2.0 - dx * sagitta / chordLength;
    }

    double startAngle = atan2(start.y - cy, start.x - cx);
    double endAngle = atan2(end.y - cy, end.x - cx);

    if (bulge < 0.0 && endAngle > startAngle) {
        endAngle -= 2 * OdPI;
    }
    else if (bulge > 0.0 && endAngle < startAngle) {
        endAngle += 2 * OdPI;
    }

    double angleStep = (endAngle - startAngle) / m_segments;

    for (int i = 0; i <= m_segments; ++i) {
        double angle = startAngle + i * angleStep;
        double x = cx + radius * cos(angle);
        double y = cy + radius * sin(angle);
        glVertex3d(x, y, start.z); // Use z-coordinate from the start point
    }
}

OdBaseObjectPtr OdMathPolyline::Clone()
{
	OdMathPolylinePtr clone = OdMathPolyline::createObject();
	clone->setSegments(getSegments());
	clone->setClosed(isClosed());
	for (int i = 0; i < numVertices(); i++)
	{
		clone->addVertex(getVertexAt(i), getBulgeAt(i));
	}
	return clone;
}

OdResult OdMathPolyline::draw()  {
    if (numVertices() < 2) {
        return eInvalidInput;
    }

	glDisable(GL_LIGHTING);
	glLoadName(id());
    if (isSelected())
    {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    else
    {
        float color[3] = { getColor().r, getColor().g, getColor().b };
        glColor3f(color[0], color[1], color[2]);
    }
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    int numVert = numVertices();
    std::vector<int> face;
    for (int i = 0; i < numVert - 1; ++i) {
        OdGePoint3d current = getVertexAt(i);
        OdGePoint3d next = getVertexAt(i + 1);
        getExtents().appendPoint_s(current);
		face.push_back(i);
        double bulge = getBulgeAt(i);
        drawArc(current, next, bulge);
    }
    getExtents().appendPoint_s(getVertexAt(numVert - 1));
    face.push_back(numVert - 1);

    if (isClosed() && numVert > 2) {
        const OdGePoint3d& first = getVertexAt(0);
        const OdGePoint3d& last = getVertexAt(numVert - 1);
        double bulge = getBulgeAt(numVert - 1);
        drawArc(last, first, bulge);
    }

    glEnd();

	getExtents().appendFace(face);

    glPopMatrix();
	glEnable(GL_LIGHTING);

    return eOk;
}

