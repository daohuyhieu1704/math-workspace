#include "pch.h"
#include "MathArc.h"

OdMathArc::OdMathArc()
{
}

OdMathArc::OdMathArc(OdGePoint3d startPnt, OdGePoint3d endPnt, double bulge)
{
	setStartPoint(startPnt);
	setEndPoint(endPnt);
	setBulge(bulge);
}

double calculateAngleFromBulge(double bulge) {
	return atan(bulge) * 4;
}

OdResult OdMathArc::draw() const
{
	glDisable(GL_LIGHTING);

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
	glEnable(GL_LIGHTING);

    return OdResult::eOk;
}

OdBaseObjectPtr OdMathArc::Clone()
{
	MathArcPtr clone = OdMathArc::createObject();
	clone->setStartPoint(getStartPoint());
	clone->setEndPoint(getEndPoint());
	clone->setBulge(getBulge());
	return clone;
}

void OdMathArc::calculateCircleFrom3Points(const OdGePoint3d& p1, const OdGePoint3d& p2, const OdGePoint3d& p3, OdGePoint3d& center, double& radius)
{
    OdGeVector3d v1 = p2 - p1;
    OdGeVector3d v2 = p3 - p2;

    OdGePoint3d mid1 = p1 + v1 * 0.5;
    OdGePoint3d mid2 = p2 + v2 * 0.5;

    OdGeVector3d normal1 = OdGeVector3d(-v1.y, v1.x, 0);
    OdGeVector3d normal2 = OdGeVector3d(-v2.y, v2.x, 0);

    double denominator = normal1.x * normal2.y - normal1.y * normal2.x;
    if (std::abs(denominator) < 1e-10) {
        throw std::runtime_error("The points are collinear; no circle can be formed.");
    }

    double t = ((mid2.x - mid1.x) * normal2.y - (mid2.y - mid1.y) * normal2.x) / denominator;

    center = mid1 + normal1 * t;

    radius = center.DistanceTo(p1);
}

double OdMathArc::calculateBulge(const OdGePoint3d& center, const OdGePoint3d& p1, const OdGePoint3d& p2)
{
    OdGeVector3d v1 = p1 - center;
    OdGeVector3d v2 = p2 - center;

    double angle = std::acos(v1.dotProduct(v2) / (v1.Length() * v2.Length()));

    if (v1.crossProduct(v2).z < 0) {
        angle = 2 * OdPI - angle;
    }

    return std::tan(angle / 4.0);
}
