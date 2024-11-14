#pragma once
#include "OdGiDrawable.h"
#include <nlohmann/json.hpp> 
#include <string>

using json = nlohmann::json;


#define PROPERTY_TO_JSON(property) j[#property] = obj.property;

class OdDbObject : public OdGiDrawable
{
};

