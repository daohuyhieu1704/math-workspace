#pragma once
#include "OdBaseObject.h"
#include <string>
#include <vector>

class IActionCmd : public OdBaseObject
{
	OD_RTTI_DECLARE_ABSTRACT(IActionCmd, OdBaseObject)
public:
	IActionCmd(){}
	virtual ~IActionCmd() = default;
	virtual bool execute() = 0;
	virtual bool serialize(const std::vector<std::string>& strData) = 0;
	std::string m_commandName;
};

OD_RTTI_DEFINE_ABSTRACT(IActionCmd, OdBaseObject)