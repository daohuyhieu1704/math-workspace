#include "pch.h"
#include "MathCircleJig.h"
#include "OdDrawingManager.h"

MathCircleJig::~MathCircleJig()
{
}

OdBaseObjectPtr MathCircleJig::entity() const
{
	OdMathCirclePtr circle = OdMathCircle::createObject();
	circle->setCenter(m_Circle->getCenter());
	circle->setRadius(m_Circle->getRadius());
    return circle;
}

DragStatus MathCircleJig::sampler()
{
    if (m_Circle->getRadius() < FLT_EPSILON)
    {
        return kCancel;
    }
    return kNormal;
}

bool MathCircleJig::update()
{
    return false;
}

bool MathCircleJig::Preview()
{
    // OdDrawingManager::R()->ji.push_back(&m_Circle);
    return true;
}

DragStatus MathCircleJig::AcquirePoint(OdGePoint3d point)
{
    m_Circle->setRadius(point.DistanceTo(m_Circle->getCenter()));
    return kNormal;
}

OdBaseObjectPtr MathCircleJig::Clone()
{
    return OdBaseObjectPtr();
}
