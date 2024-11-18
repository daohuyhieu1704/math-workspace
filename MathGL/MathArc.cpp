#include "pch.h"
#include "MathArc.h"

MathArc::MathArc()
{
}

MathArc::MathArc(OdGePoint3d startPnt, double bulge)
{
	setStartPoint(startPnt);
	setBulge(bulge);
}

double calculateAngleFromBulge(double bulge) {
	return atan(bulge) * 4;
}

OdResult MathArc::draw() const
{
	double bulge = getBulge();
	OdGePoint3d startPnt = getStartPoint();

    if ( std::abs(bulge) < FLT_EPSILON)
        return OdResult::eInvalidInput;

    double angle = calculateAngleFromBulge(bulge);

    double radius = 1.0;

    double startAngle = 0.0;
    double endAngle = startAngle + angle;

    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= m_segments; ++i) {
        double t = static_cast<double>(i) / m_segments;
        double currentAngle = startAngle + t * (endAngle - startAngle);

        double x = startPnt.x + radius * cos(currentAngle);
        double y = startPnt.y + radius * sin(currentAngle);

        glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y), static_cast<GLfloat>(startPnt.z));
    }

    glEnd();

    return OdResult::eOk;
}
