#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include "OdDbObjectId.h"

class OdBaseObject;

class OdBaseObjectPtr
{
protected:
    OdBaseObject* m_pObject = nullptr;

    OdBaseObjectPtr() : m_pObject(0) {}
    explicit OdBaseObjectPtr(const OdBaseObject* pSource) : m_pObject(const_cast<OdBaseObject*>(pSource)) {}
public:
    OdBaseObjectPtr(OdBaseObjectPtr&& pObject) noexcept : m_pObject(pObject.m_pObject)
    {
        pObject.m_pObject = nullptr;
    }

    OdBaseObjectPtr& operator = (OdBaseObjectPtr&& pObject) noexcept
    {
        std::swap(m_pObject, pObject.m_pObject);
        return *this;
    }
    OdBaseObject* get() const { return m_pObject; }
    bool isNull() const { return m_pObject == 0; }
};

template <class T>
class OdSmartPtr : public OdBaseObjectPtr {
private:
    unsigned* ref_count;

public:
    OdSmartPtr() : OdBaseObjectPtr(new T()), ref_count(new unsigned(1)) {}

    OdSmartPtr(T* rawPtr) : OdBaseObjectPtr(rawPtr), ref_count(new unsigned(1)) {
        if (!m_pObject) {
            m_pObject = new T();
        }
    }

    OdSmartPtr(const OdSmartPtr<T>& sp) : OdBaseObjectPtr(sp.m_pObject), ref_count(sp.ref_count) {
        addRef();
    }

    OdSmartPtr(OdSmartPtr<T>&& sp) noexcept : OdBaseObjectPtr(std::move(sp)), ref_count(sp.ref_count) {
        sp.ref_count = nullptr;
    }

    ~OdSmartPtr() {
        release();
    }

    OdSmartPtr<T>& operator=(const OdSmartPtr<T>& sp) {
        if (this != &sp) {
            release();
            m_pObject = sp.m_pObject;
            ref_count = sp.ref_count;
            addRef();
        }
        return *this;
    }

    OdSmartPtr<T>& operator=(OdSmartPtr<T>&& sp) noexcept {
        if (this != &sp) {
            release();
            OdBaseObjectPtr::operator=(std::move(sp));
            ref_count = sp.ref_count;
            sp.ref_count = nullptr;
        }
        return *this;
    }

    OdSmartPtr<T>& operator=(std::nullptr_t) {
        release();
        m_pObject = nullptr;
        ref_count = nullptr;
        return *this;
    }

    T& operator*() const {
        return *dynamic_cast<T*>(m_pObject);
    }

    unsigned getRefCount() const {
        return ref_count ? *ref_count : 0;
    }

	T* operator->() const {
		return dynamic_cast<T*>(m_pObject);
	}

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

class OdBaseObject {
protected:
    OdDbObjectId m_id = OdDbObjectId::kNull;

public:
    OdBaseObject() : m_id(OdDbObjectId()) {}
    OdDbObjectId getObjectId() const;
    virtual ~OdBaseObject() = default;

    virtual std::string getClassName() const = 0;
    virtual bool isKindOf(const std::string& className) const = 0;

    virtual OdBaseObjectPtr Clone() = 0;
};

#define OD_RTTI_DECLARE_ABSTRACT(ClassName, BaseClassName) \
public: \
    static std::string desc() { return #ClassName; } \
    static std::string baseClassName() { return #BaseClassName; } \
    virtual std::string getClassName() const override { return ClassName::desc(); } \
    inline virtual bool isKindOf(const std::string& desc) const override; \

#define OD_RTTI_DECLARE(ClassName, BaseClassName) \
public: \
    static std::string desc() { return #ClassName; } \
    static std::string baseClassName() { return #BaseClassName; } \
    virtual std::string getClassName() const override { return ClassName::desc(); } \
    inline virtual bool isKindOf(const std::string& desc) const override; \
    static OdSmartPtr<ClassName> createObject(); \
    static OdSmartPtr<ClassName> cast(const OdSmartPtr<BaseClassName>& obj);

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
    }
