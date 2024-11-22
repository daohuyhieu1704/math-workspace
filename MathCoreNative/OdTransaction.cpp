// OdTransaction.cpp
#include "pch.h"
#include "OdTransaction.h"
#include "OdDatabase.h"

void OdTransaction::assignDatabase(const OdDatabasePtr& database)
{
	m_database = database;
}

void OdTransaction::begin() {
    // Initialize or reset change tracking containers
    m_addedEntities.clear();
    m_removedEntities.clear();
}

void OdTransaction::commit() {
    // Apply all additions
    for (const auto& entity : m_addedEntities) {
        m_database->appendEntity(entity);
    }

    // Apply all removals
    for (const auto& entity : m_removedEntities) {
        m_database->removeEntity(entity);
    }

    // Clear change tracking after commit
    m_addedEntities.clear();
    m_removedEntities.clear();
}

void OdTransaction::abort() {
    // Discard all tracked changes
    m_addedEntities.clear();
    m_removedEntities.clear();
}

void OdTransaction::addEntity(const OdBaseObjectPtr& entity) {
    m_addedEntities.push_back(entity);
}

void OdTransaction::removeEntity(const OdBaseObjectPtr& entity) {
    m_removedEntities.push_back(entity);
}

OdBaseObjectPtr OdTransaction::Clone() {
    // Implement cloning if necessary
    return OdTransactionPtr(new OdTransaction(*this));
}