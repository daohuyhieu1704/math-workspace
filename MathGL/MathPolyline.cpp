#include "pch.h"
#include "MathPolyline.h"

MathPolyline::MathPolyline()
{
}

void MathPolyline::drawArc(const OdGePoint3d& start, const OdGePoint3d& end, double bulge) const {
    if (bulge == 0.0) {
        glVertex2d(start.x, start.y);
        glVertex2d(end.x, end.y);
        return;
    }

    double dx = end.x - start.x;
    double dy = end.y - start.y;
    double chordLength = sqrt(dx * dx + dy * dy);

    double sagitta = bulge * chordLength / 2.0;
    double radius = (chordLength * chordLength / (8.0 * fabs(sagitta))) + fabs(sagitta);

    double cx, cy;
    double midX = (start.x + end.x) / 2.0;
    double midY = (start.y + end.y) / 2.0;
    double offsetX = -dy * sagitta / fabs(sagitta) * (radius - fabs(sagitta)) / chordLength;
    double offsetY = dx * sagitta / fabs(sagitta) * (radius - fabs(sagitta)) / chordLength;
    cx = midX + offsetX;
    cy = midY + offsetY;

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
        glVertex2d(x, y);
    }
}

OdResult MathPolyline::draw() const
{
    if (numVertices() == 0) {
        return eInvalidInput;
    }

    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_LINE_STRIP);
    int numVert = numVertices();
    for (size_t i = 0; i < numVert - 1; ++i) {
        const OdGePoint3d& current = getVertexAt(i);
        const OdGePoint3d& next = getVertexAt(i + 1);
        double bulge = getBulgeAt(i);
        drawArc(current, next, bulge);
    }

    glEnd();

    glPopMatrix();

    return eOk;
}
