// OdDatabase.cpp
#include "pch.h"
#include "OdDatabase.h"

OdTransactionPtr OdDatabase::startTransaction() {
    if (!m_currentTransaction.isNull()) {
        // Handle error: transaction already in progress
        return nullptr;
    }
	OdTransactionPtr transaction = OdTransactionPtr(m_currentTransaction);
    return transaction;
}

void OdDatabase::commitTransaction() {
    if (!m_currentTransaction.isNull()) {
        m_currentTransaction->commit();
        m_currentTransaction = nullptr;
    }
    else {
        // Handle error: no active transaction to commit
    }
}

void OdDatabase::abortTransaction() {
    if (!m_currentTransaction.isNull()) {
        m_currentTransaction->abort();
        m_currentTransaction = nullptr;
    }
    else {
        // Handle error: no active transaction to abort
    }
}

void OdDatabase::appendEntity(const OdBaseObjectPtr& entity) {
    if (!m_currentTransaction.isNull()) {
        m_currentTransaction->addEntity(entity);
    }
    else {
        m_records.back()->getSession()->appendEntity(entity);
    }
}

void OdDatabase::removeEntity(const OdBaseObjectPtr& entity) {
    if (!m_currentTransaction.isNull()) {
        m_currentTransaction->removeEntity(entity);
    }
    else {
        m_records.back()->getSession()->removeEntity(entity);
    }
}

void OdDatabase::addRecord(const OdDataTableRecordPtr& record) {
    m_records.push_back(record);
}

void OdDatabase::removeRecord(std::string sessionId) {
    m_records.erase(std::remove_if(m_records.begin(), m_records.end(),
        [&sessionId](const OdDataTableRecordPtr& record) {
            return record->getSessionId() == sessionId;
        }), m_records.end());
}

OdDataTableRecordPtr OdDatabase::getRecord(std::string sessionId) const {
    auto it = std::find_if(m_records.begin(), m_records.end(),
        [&sessionId](const OdDataTableRecordPtr& record) {
            return record->getSessionId() == sessionId;
        });
    return (it != m_records.end()) ? *it : OdDataTableRecordPtr();
}

const std::vector<OdDataTableRecordPtr>& OdDatabase::getRecords() const {
    return m_records;
}

OdBaseObjectPtr OdDatabase::Clone() {
    // Deep copy the database and its records
	OdDatabasePtr clonedDb = OdDatabase::createObject();
    return clonedDb;
}
