#include "pch.h"
#include "OdError.h"

OdError::OdError(OdResult code)
    : m_code(code), m_message("No description provided") {}

OdError::OdError(OdResult code, const std::string& message)
    : m_code(code), m_message(message) {}

OdError::OdError(const OdError& other)
    : m_code(other.m_code), m_message(other.m_message) {}

OdError::~OdError() {
}

OdResult OdError::code() const {
    return m_code;
}

std::string OdError::description() const {
    return m_message;
}

OdError& OdError::operator=(const OdError& other) {
    if (this != &other) {
        m_code = other.m_code;
        m_message = other.m_message;
    }
    return *this;
}