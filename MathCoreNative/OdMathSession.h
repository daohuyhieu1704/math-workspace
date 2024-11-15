#pragma once
#include "OdBaseObject.h"
#include <chrono>
#include <queue>
#include <set>
#include <any>
#include <unordered_map>

typedef OdSmartPtr<class OdMathSession> OdMathSessionPtr;
class OdMathSession :
    public OdBaseObject
{
    OD_RTTI_DECLARE(OdMathSession, OdBaseObject)
public:
    OdBaseObjectPtr Clone() override;
    OdMathSession();
    // Getters and setters for session attributes
    void setLastAccessTime() { lastAccessTime = std::chrono::system_clock::now(); }
    void addCommand(const std::string& command) { commands.push(command); }
    bool getIsModified() const { return isModified; }
    void setIsModified(bool modified) { isModified = modified; }
private:
    std::chrono::time_point<std::chrono::system_clock> creationTime;
    std::chrono::time_point<std::chrono::system_clock> lastAccessTime;
    enum class SessionState { ACTIVE, INACTIVE, CLOSED } sessionState;
    std::queue<std::string> commands;
    std::unordered_map<std::string, OdBaseObjectPtr> contextData;
    std::set<std::string> permissions;
    bool isModified;
	std::string m_fileName = "Untitled";
};