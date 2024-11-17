#pragma once
#include "OdMathSession.h"

typedef OdSmartPtr<class OdHostAppService> OdHostAppServicePtr;
class OdHostAppService :
    public OdBaseObject
{
	OD_RTTI_DECLARE(OdHostAppService, OdBaseObject)
public:
	
	static OdHostAppServicePtr getInstance();
	OdMathSessionPtr createSession(const std::string& sessionId) {
		if (m_sessions.find(sessionId) != m_sessions.end()) {
			return m_sessions[sessionId];
		}
		auto session = OdMathSessionPtr();
		m_sessions[sessionId] = session;
		currentSessionId = sessionId;
		return session;
	}

	OdMathSessionPtr getSession(const std::string& sessionId) {
		if (m_sessions.find(sessionId) != m_sessions.end()) {
			return m_sessions[sessionId];
		}
		return OdMathSessionPtr();
	}

	void ChangeCurrSession(const std::string filePath) {
		if (m_sessions.find(filePath) != m_sessions.end()) {
			currentSessionId = filePath;
		}
	}
	void removeSession(const std::string& sessionId) {
		m_sessions.erase(sessionId);
	}

	OdMathSessionPtr getCurrentSession() {
		return getSession(currentSessionId);
	}

	void ExecuteAllPrompts() {
		// getCurrentSession()->ExecuteAllPrompts();
	}
	// Inherited via OdBaseObject
	OdBaseObjectPtr Clone() override;
	OdHostAppService();
private:
	static OdHostAppServicePtr m_instance;
	~OdHostAppService() = default;
	OdHostAppService(const OdHostAppService&) = delete;
	OdHostAppService& operator=(const OdHostAppService&) = delete;
	std::unordered_map<std::string, OdMathSessionPtr> m_sessions;
	std::string currentSessionId;
};