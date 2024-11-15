#pragma once
#include <OdGePoint3d.h>
#include "OdBaseObject.h"

using namespace GeometryNative;

enum DragStatus {
    kNormal = 0,
    kCancel = 1,
    kOther = 2,
    kNoChange = 3
};

class OdJig :
    public OdBaseObject
{
	OD_RTTI_DECLARE_ABSTRACT(OdJig, OdBaseObject)
public:
    virtual ~OdJig() {}
    virtual OdBaseObjectPtr entity() const = 0;
    virtual DragStatus sampler() = 0;
    virtual bool update() = 0;
    virtual bool Preview() = 0;
    virtual DragStatus AcquirePoint(OdGePoint3d point) = 0;
};

OD_RTTI_DEFINE_ABSTRACT(OdJig, OdBaseObject)

