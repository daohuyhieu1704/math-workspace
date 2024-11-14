#pragma once
#include "OdError.h"

class OdClassBase;

class OdError_NotThatKindOfClass :
    public OdError
{
private:
    std::string m_fromClassName;
    std::string m_toClassName;

public:
    OdError_NotThatKindOfClass(const OdClassBase* fromClass, const OdClassBase* toClass);
    OdError_NotThatKindOfClass(const std::string& fromClass, const std::string& toClass);
    OdError_NotThatKindOfClass(const OdError_NotThatKindOfClass& other);

    ~OdError_NotThatKindOfClass();

    std::string fromClassName() const;
    std::string toClassName() const;
};

