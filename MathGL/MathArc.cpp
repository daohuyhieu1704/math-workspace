#include "pch.h"
#include "MathArc.h"

MathArc::MathArc()
{
}

MathArc::MathArc(OdGePoint3d startPnt, OdGePoint3d endPnt, double bulge)
{
	setStartPoint(startPnt);
	setEndPoint(endPnt);
	setBulge(bulge);
}

double calculateAngleFromBulge(double bulge) {
	return atan(bulge) * 4;
}

OdResult MathArc::draw() const
{
    double bulge = getBulge();
    OdGePoint3d startPnt = getStartPoint();
    OdGePoint3d endPnt = getEndPoint();

    if (std::abs(bulge) < FLT_EPSILON || startPnt.isEqual(endPnt))
        return OdResult::eInvalidInput;

    OdGeVector3d chordVec = endPnt - startPnt;
    double chordLength = chordVec.Length();

    double sagitta = std::abs(bulge) * chordLength / 2.0;

    double radius = (chordLength * chordLength) / (8.0 * sagitta) + sagitta / 2.0;

    OdGePoint3d midPnt = startPnt + chordVec / 2.0;

    OdGeVector3d normalVec = chordVec.crossProduct(OdGeVector3d::kZAxis).normalize();

    if (bulge < 0)
        normalVec = -normalVec;

    OdGePoint3d center = midPnt + normalVec * std::sqrt(radius * radius - (chordLength * chordLength) / 4.0);

    OdGeVector3d startVec = startPnt - center;
    OdGeVector3d endVec = endPnt - center;

    double startAngle = atan2(startVec.y, startVec.x);
    double endAngle = atan2(endVec.y, endVec.x);

    if (bulge < 0 && endAngle > startAngle)
        endAngle -= 2 * OdPI;
    else if (bulge > 0 && endAngle < startAngle)
        endAngle += 2 * OdPI;

    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= m_segments; ++i) {
        double t = static_cast<double>(i) / m_segments;
        double currentAngle = startAngle + t * (endAngle - startAngle);

        double x = center.x + radius * cos(currentAngle);
        double y = center.y + radius * sin(currentAngle);

        glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y), static_cast<GLfloat>(startPnt.z));
    }

    glEnd();

    return OdResult::eOk;
}
