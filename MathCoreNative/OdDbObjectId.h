#pragma once
#include <string>
#include <set>
#include <mutex>

class OdDatabase;
class OdDbObject;

template <class T> class OdSmartPtr;
typedef OdSmartPtr<OdDbObject> OdDbObjectPtr;


namespace OdDb
{
    enum OpenMode
    {
        kNotOpen = -1,  // Object is not open.
        kForRead = 0,   // Object is open for reading.
        kForWrite = 1,   // Object is open for reading and/or writing.
    };
}

/// <summary>
/// This class implements memory-resident ObjectId objects for OdDbDatabase objects.  
/// 
/// Database objects reference
/// other database objects using ObjectId objects, and a database object pointer
/// can always be obtained from a valid ObjectId objects.The effect of this mechanism is
/// that database objects do not have to reside in memory unless they are explicitly
/// being examined or modified by the user.
/// 
/// The user must explicitly open an object
/// before reading or writing to it, and should release it when the operation
/// is completed.This functionality allows the Drawings to support partial loading of
/// a database, where ObjectId objects exist for all objects in the database, but
/// the actual database objects need not be loaded until they are accessed.
/// It also allows database objects that are not in use to be swapped out of memory,
/// and loaded back in when they are accessed.ObjectId objects are not written out to a
/// file. If a reference must be preserved to a database object that has been
/// serialized, the object's database handle (OdDbHandle) should be used.
/// </summary>
class OdDbObjectId
{
    static std::set<std::string> allocatedIds;
    static std::mutex mutex;
	OdDbObjectId(unsigned int i) : m_Id(i) {}
    static unsigned int GenerateShortId();
    static unsigned int GenerateUniqueId();
public:
    unsigned int GetObjectId() const;

    /// <summary>
    /// This function guarantees that isNull() will, return true if it is the first operation applied to this instance.
    /// </summary>
    OdDbObjectId() : m_Id(GenerateShortId()) { }

    static const OdDbObjectId kNull;

    /// <summary>
    /// Returns true and only if this ObjectId object is null.
    /// </summary>
    /// <returns></returns>
    bool isNull() const;

    /// <summary>
    /// Sets this Object ID to null.
    /// </summary>
    void setNull();

    /// <summary>
    /// Returns true and only if this ObjectId object references a valid object.
    /// </summary>
    /// <returns></returns>
    bool isValid() const;

    /// <summary>
    /// VS2015 requires to create copy constructor explicity
    /// </summary>
    /// <param m_name="objectId"></param>
    OdDbObjectId(const OdDbObjectId& objectId) = default;
    OdDbObjectId& operator = (const OdDbObjectId& objectId) = default;

    OdDbObjectId& operator=(unsigned int  objectId);
    bool operator == (
        const OdDbObjectId& objectId) const;
	bool operator != (
		const OdDbObjectId& objectId) const;

    bool operator<(const OdDbObjectId& other) const;
	std::string toString() const {
		return std::to_string(m_Id);
	}
protected:
    unsigned int m_Id = 0;
};

