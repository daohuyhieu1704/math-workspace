#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include "OdDbObjectId.h"

class OdBaseObject;

class OdBaseObjectPtr {
protected:
    OdBaseObject* m_pObject = nullptr;
    unsigned* ref_count = nullptr;

public:
    OdBaseObjectPtr() : m_pObject(nullptr), ref_count(new unsigned(1)) {}

    explicit OdBaseObjectPtr(OdBaseObject* pSource) : m_pObject(pSource), ref_count(new unsigned(1)) {}

    OdBaseObjectPtr(const OdBaseObjectPtr& other) : m_pObject(other.m_pObject), ref_count(other.ref_count) {
        addRef();
    }

    OdBaseObjectPtr(OdBaseObjectPtr&& other) noexcept : m_pObject(other.m_pObject), ref_count(other.ref_count) {
        other.m_pObject = nullptr;
        other.ref_count = nullptr;
    }

    ~OdBaseObjectPtr() {
        release();
    }

    OdBaseObject* operator->() const {
        return static_cast<OdBaseObject*>(m_pObject);
    }

    OdBaseObjectPtr& operator=(const OdBaseObjectPtr& other) {
        if (this != &other) {
            release();
            m_pObject = other.m_pObject;
            ref_count = other.ref_count;
            addRef();
        }
        return *this;
    }

    OdBaseObjectPtr& operator=(OdBaseObjectPtr&& other) noexcept {
        if (this != &other) {
            release();
            m_pObject = other.m_pObject;
            ref_count = other.ref_count;
            other.m_pObject = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    bool operator==(const OdBaseObjectPtr& other) const {
        return m_pObject == other.m_pObject;
    }

    bool operator!=(const OdBaseObjectPtr& other) const {
        return m_pObject != other.m_pObject;
    }

    OdBaseObject* get() const { return m_pObject; }
    bool isNull() const { return m_pObject == nullptr; }
	int getRefCount() const { return ref_count ? *ref_count : 0; }
protected:
    void addRef() {
        if (ref_count) {
            ++(*ref_count);
        }
    }

    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete m_pObject;
            delete ref_count;
        }
        m_pObject = nullptr;
        ref_count = nullptr;
    }
};


template <class T>
class OdSmartPtr : public OdBaseObjectPtr {
public:
    OdSmartPtr() : OdBaseObjectPtr(new T()) {}

    OdSmartPtr(T* rawPtr) : OdBaseObjectPtr(rawPtr) {}

    OdSmartPtr(const OdSmartPtr<T>& sp) : OdBaseObjectPtr(sp) {}

    OdSmartPtr(OdSmartPtr<T>&& sp) noexcept : OdBaseObjectPtr(std::move(sp)) {}

    OdSmartPtr<T>& operator=(const OdSmartPtr<T>& sp) {
        OdBaseObjectPtr::operator=(sp);
        return *this;
    }

    OdSmartPtr<T>& operator=(OdSmartPtr<T>&& sp) noexcept {
        OdBaseObjectPtr::operator=(std::move(sp));
        return *this;
    }

    T& operator*() const {
        return *static_cast<T*>(m_pObject);
    }

    T* operator->() const {
        return static_cast<T*>(m_pObject);
    }
};

class OdBaseObject {
protected:
    OdDbObjectId m_id = OdDbObjectId::kNull;

public:
    OdBaseObject() : m_id(OdDbObjectId()) {}
    OdDbObjectId getObjectId() const;
    virtual ~OdBaseObject() = default;

    bool operator==(const OdBaseObject& other) const {
        return m_id == other.m_id;
    }

    bool operator!=(const OdBaseObject& other) const {
        return m_id != other.m_id;
    }


    virtual std::string getClassName() const = 0;
    virtual bool isKindOf(const std::string& className) const = 0;

    virtual OdBaseObjectPtr Clone() = 0;
};

#define OD_RTTI_DECLARE_ABSTRACT(ClassName, BaseClassName) \
public: \
    static std::string desc() { return #ClassName; } \
    static std::string baseClassName() { return #BaseClassName; } \
    virtual std::string getClassName() const override { return ClassName::desc(); } \
    inline virtual bool isKindOf(const std::string& desc) const override;

#define OD_RTTI_DECLARE(ClassName, BaseClassName) \
public: \
    static std::string desc() { return #ClassName; } \
    static std::string baseClassName() { return #BaseClassName; } \
    virtual std::string getClassName() const override { return ClassName::desc(); } \
    inline virtual bool isKindOf(const std::string& desc) const override; \
    static OdSmartPtr<ClassName> createObject(); \
    static OdSmartPtr<ClassName> cast(const OdSmartPtr<BaseClassName>& obj); \
    static OdSmartPtr<ClassName> cast(const OdBaseObjectPtr& obj);

#define OD_RTTI_DEFINE_ABSTRACT(ClassName, BaseClassName) \
    inline bool ClassName::isKindOf(const std::string& desc) const { \
        const OdBaseObject* current = this; \
        while (current) { \
            if (desc == current->getClassName()) { \
                return true; \
            } \
            current = dynamic_cast<const BaseClassName*>(current); \
        } \
        return false; \
    }

#define OD_RTTI_DEFINE(ClassName, BaseClassName) \
    inline bool ClassName::isKindOf(const std::string& desc) const { \
        const OdBaseObject* current = this; \
        while (current) { \
            if (desc == current->getClassName()) { \
                return true; \
            } \
            current = dynamic_cast<const BaseClassName*>(current); \
        } \
        return false; \
    } \
    inline OdSmartPtr<ClassName> ClassName::createObject() { \
        return OdSmartPtr<ClassName>(new ClassName()); \
    } \
    inline OdSmartPtr<ClassName> ClassName::cast(const OdSmartPtr<BaseClassName>& obj) { \
        if (!obj.isNull() && obj->isKindOf(ClassName::desc())) { \
            return OdSmartPtr<ClassName>(dynamic_cast<ClassName*>(obj.get())); \
        } \
        return nullptr; \
    } \
    inline OdSmartPtr<ClassName> ClassName::cast(const OdBaseObjectPtr& obj) { \
        if (!obj.isNull() && obj.get()->isKindOf(ClassName::desc())) { \
            return OdSmartPtr<ClassName>(dynamic_cast<ClassName*>(obj.get())); \
        } \
        return nullptr; \
    }

#define OD_RTTI_SINGLETON_DECLARE(ClassName) \
private: \
    static OdSmartPtr<ClassName> m_instance; \
public: \
    static OdSmartPtr<ClassName>& R();

#define OD_RTTI_SINGLETON_DEFINE(ClassName) \
OdSmartPtr<ClassName> ClassName::m_instance; \
OdSmartPtr<ClassName>& ClassName::R() \
{ \
    if (m_instance.isNull()) \
    { \
        m_instance = ClassName::createObject(); \
    } \
    return m_instance; \
}

template<typename T>
OdSmartPtr<T> static_pointer_cast(const OdBaseObjectPtr& basePtr) {
    T* derivedPtr = dynamic_cast<T*>(basePtr.get());
    if (derivedPtr) {
        return OdSmartPtr<T>(basePtr); // Calls copy constructor
    }
    else {
        return OdSmartPtr<T>(); // Returns a null smart pointer
    }
}
