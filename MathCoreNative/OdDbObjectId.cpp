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

std::string OdDbObjectId::GetObjectId() const
{
	return m_Id;
}
std::string OdDbObjectId::GenerateShortId()
{
    std::time_t t = std::time(nullptr);
    std::mt19937 rng(static_cast<unsigned int>(t));
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 15);

    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << (t & 0xFFFFFFF);

    for (int i = 0; i < 2; ++i) {
        ss << std::hex << dist(rng);
    }

    return ss.str().substr(0, 8);
}

std::string OdDbObjectId::GenerateUniqueId()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::string newId;
    do
    {
        newId = GenerateShortId(); // Use any unique ID generator
    } while (allocatedIds.find(newId) != allocatedIds.end());

    allocatedIds.insert(newId);
    return newId;
}

bool OdDbObjectId::isNull() const
{
	return m_Id == "0";
}

void OdDbObjectId::setNull()
{
	m_Id = "0";
}

bool OdDbObjectId::isValid() const
{
	return m_Id != "0";
}

OdDbObjectId& OdDbObjectId::operator=(std::string objectId)
{
	m_Id = objectId;
	return *this;
}

bool OdDbObjectId::operator==(const OdDbObjectId& objectId) const
{
	return m_Id == objectId.m_Id;
}
