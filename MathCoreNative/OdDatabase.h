// OdDatabase.h

#pragma once
#include "OdBaseObject.h"
#include "OdDataTableRecord.h"
#include "OdTransaction.h"
#include <vector>

class OdDatabase : public OdBaseObject {
    OD_RTTI_DECLARE(OdDatabase, OdBaseObject)
public:
    OdDatabase() = default;

    // Transaction Management
    OdTransactionPtr startTransaction();
    void commitTransaction();
    void abortTransaction();

    // Entity Management
    void appendEntity(const OdBaseObjectPtr& entity);
    void removeEntity(const OdBaseObjectPtr& entity);

    // Session Management
    void addRecord(const OdDataTableRecordPtr& record);
    void removeRecord(std::string sessionId);
    OdDataTableRecordPtr getRecord(std::string sessionId) const;

    // Get all records
    const std::vector<OdDataTableRecordPtr>& getRecords() const;

    // OdBaseObject overrides
    OdBaseObjectPtr Clone() override;

private:
    std::vector<OdDataTableRecordPtr> m_records;

    // Current active transaction
    OdTransactionPtr m_currentTransaction;
};

OD_RTTI_DEFINE(OdDatabase, OdBaseObject)
