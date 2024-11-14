#include "pch.h"
#include "OdError_NotThatKindOfClass.h"
#include "OdBaseObject.h"

OdError_NotThatKindOfClass::OdError_NotThatKindOfClass(const OdClassBase* fromClass, const OdClassBase* toClass)
	: OdError(OdResult::eInvalidInput)
{
	m_fromClassName = "null";
	m_toClassName = "null";
}

OdError_NotThatKindOfClass::OdError_NotThatKindOfClass(const std::string& fromClass, const std::string& toClass)
    : OdError(OdResult::eInvalidInput), m_fromClassName(fromClass), m_toClassName(toClass) {}

OdError_NotThatKindOfClass::OdError_NotThatKindOfClass(const OdError_NotThatKindOfClass& other)
    : OdError(other), m_fromClassName(other.m_fromClassName), m_toClassName(other.m_toClassName) {}

OdError_NotThatKindOfClass::~OdError_NotThatKindOfClass() {
}

std::string OdError_NotThatKindOfClass::fromClassName() const {
    return m_fromClassName;
}

std::string OdError_NotThatKindOfClass::toClassName() const {
    return m_toClassName;
}