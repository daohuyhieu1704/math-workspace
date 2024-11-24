#pragma once
#include "OdBaseObject.h"
#include "OdResult.h"

struct ColorRGB {
	double r = 0.5;
	double g = 0.5;
	double b = 0.5;
	ColorRGB() = default;
	ColorRGB(double r, double g, double b) : r(r), g(g), b(b) {}
};

class OdGiDrawable : public OdBaseObject {
    OD_RTTI_DECLARE_ABSTRACT(OdGiDrawable, OdBaseObject)
public:
    virtual ~OdGiDrawable() = default;
    virtual OdResult draw() const = 0;
	virtual void setColor(const ColorRGB& color) { m_color = color; }
	virtual ColorRGB getColor() const { return m_color; }
private:
    ColorRGB m_color;
};

OD_RTTI_DEFINE_ABSTRACT(OdGiDrawable, OdBaseObject)