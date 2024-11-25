#pragma once
#include <OdJig.h>
#include "OdMathCircle.h"

class MathCircleJig :
    public OdJig
{
	OD_RTTI_DECLARE(MathCircleJig, OdJig)
public:
    MathCircleJig(OdGePoint3d center) : MathCircleJig()
    {
        m_Circle->setCenter(center);
    }
    MathCircleJig() : m_Circle() {}
    virtual ~MathCircleJig() = default;

    // Inherited via OdJig
    OdBaseObjectPtr entity() const override;
    DragStatus sampler() override;
    bool update() override;
    bool Preview() override;
    DragStatus AcquirePoint(OdGePoint3d point) override;

private:
    OdMathCirclePtr m_Circle;

    // Inherited via OdJig
    OdBaseObjectPtr Clone() override;
};

OD_RTTI_DEFINE(MathCircleJig, OdJig)

