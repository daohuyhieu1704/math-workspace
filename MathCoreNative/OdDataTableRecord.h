// OdDataTableRecord.h

#pragma once
#include "OdBaseObject.h"
#include "OdMathSession.h"
#include <string>

typedef OdSmartPtr<class OdDataTableRecord> OdDataTableRecordPtr;

class OdDataTableRecord : public OdBaseObject {
    OD_RTTI_DECLARE(OdDataTableRecord, OdBaseObject)

public:
    OdDataTableRecord(){}

	void assignSession(const OdMathSessionPtr& session) {
		m_sessionId = session->getObjectId().GetObjectId();
		m_session = session;
	}

    // Accessors
    std::string getSessionId() const { return m_sessionId; }
    OdMathSessionPtr getSession() const { return m_session; }

    // OdBaseObject overrides
    OdBaseObjectPtr Clone() override {
		OdMathSessionPtr clonedSession = OdMathSession::createObject();
        return clonedSession;
    }

private:
    std::string m_sessionId;
    OdMathSessionPtr m_session;
};

OD_RTTI_DEFINE(OdDataTableRecord, OdBaseObject)