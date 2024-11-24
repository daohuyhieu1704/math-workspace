#pragma once
#include "OdGiDrawable.h"
#include <nlohmann/json.hpp> 
#include <string>

using json = nlohmann::json;

#define PROPERTY_TO_JSON(prop) j[#prop] = this->prop;

class OdDbObject : public OdGiDrawable
{
	OD_RTTI_DECLARE_ABSTRACT(OdDbObject, OdGiDrawable);
public:
	unsigned int id() const;
	virtual ~OdDbObject() = default;
	virtual json toJson() const;
	virtual void fromJson(const json& j);
};

OD_RTTI_DEFINE_ABSTRACT(OdDbObject, OdGiDrawable)