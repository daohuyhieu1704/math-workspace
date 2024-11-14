#pragma once
#include "OdResult.h"
#include <string>
class OdError
{
    OdResult m_code;           // Error code
    std::string m_message;     // Error message

public:
    explicit OdError(OdResult code);
    OdError(OdResult code, const std::string& message);
    OdError(const OdError& other);

    ~OdError();

    OdResult code() const;
    std::string description() const;

    OdError& operator=(const OdError& other);
};

