#include "pch.h"
#include "OdDbObjectId.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <ctime>
#include <string>


std::set<std::string> OdDbObjectId::allocatedIds;
std::mutex OdDbObjectId::mutex;

const OdDbObjectId OdDbObjectId::kNull = OdDbObjectId(0);

unsigned int OdDbObjectId::GetObjectId() const
{
	return m_Id;
}
unsigned int OdDbObjectId::GenerateShortId()
{
    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<unsigned int> dist(0, 0xFFFFFFFF);

    return dist(rng);
}

unsigned int OdDbObjectId::GenerateUniqueId()
{
    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<unsigned int> dist(0, 0xFFFFFFFF);

    std::string result;
    unsigned int uniqueId;

    std::unique_lock<std::mutex> lock(mutex);

    do {
        uniqueId = dist(rng);
        result = std::to_string(uniqueId);
    } while (allocatedIds.find(result) != allocatedIds.end());

    allocatedIds.insert(result);
    return uniqueId;
}


bool OdDbObjectId::isNull() const
{
	return m_Id == 0;
}

void OdDbObjectId::setNull()
{
	m_Id = 0;
}

bool OdDbObjectId::isValid() const
{
	return m_Id != 0;
}

OdDbObjectId& OdDbObjectId::operator=(unsigned int objectId)
{
	m_Id = objectId;
	return *this;
}

bool OdDbObjectId::operator==(const OdDbObjectId& objectId) const
{
	return m_Id == objectId.m_Id;
}

bool OdDbObjectId::operator!=(const OdDbObjectId& objectId) const
{
	return m_Id != objectId.m_Id;
}

bool OdDbObjectId::operator<(const OdDbObjectId& other) const
{
	return m_Id < other.m_Id;
}
