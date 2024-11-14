#pragma once
#include "OdBaseObject.h"
#include "OdResult.h"

class OdGiDrawable : public OdBaseObject {
public:
	OdGiDrawable() = default;
    virtual ~OdGiDrawable() = default;
    virtual OdResult draw() const = 0;
    // virtual GeometryNative::OdGeScale3d boundingBox() const = 0;
    std::string getClassName() const override {
        return "OdGiDrawable";
    }

    // Inherited via OdBaseObject
    bool isKindOf(const std::string desc) const override;
};