// OdTransaction.h

#pragma once
#include "OdBaseObject.h"
#include <vector>

typedef OdSmartPtr<class OdTransaction> OdTransactionPtr;
typedef OdSmartPtr<class OdDatabase> OdDatabasePtr;
class OdTransaction : public OdBaseObject {
    OD_RTTI_DECLARE(OdTransaction, OdBaseObject)
public:
    OdTransaction(){}

	void assignDatabase(const OdDatabasePtr& database);

    void begin();

    void commit();

    void abort();

    void addEntity(const OdBaseObjectPtr& entity);

    void removeEntity(const OdBaseObjectPtr& entity);

    // OdBaseObject overrides
    OdBaseObjectPtr Clone() override;
private:
    OdDatabasePtr m_database;
    std::vector<OdBaseObjectPtr> m_addedEntities;
    std::vector<OdBaseObjectPtr> m_removedEntities;
};

OD_RTTI_DEFINE(OdTransaction, OdBaseObject)
