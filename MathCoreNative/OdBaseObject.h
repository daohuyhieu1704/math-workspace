#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <atomic>
#include "OdDbObjectId.h"
#include <unordered_map>

class OdBaseObject;

class OdBaseObjectPtr {
protected:
    OdBaseObject* m_pObject = nullptr;
    std::atomic<unsigned>* ref_count = nullptr;

public:
    // Default constructor
    OdBaseObjectPtr() noexcept : m_pObject(nullptr), ref_count(nullptr) {}

    // Constructor from raw pointer
    explicit OdBaseObjectPtr(OdBaseObject* pSource) : m_pObject(pSource), ref_count(new std::atomic<unsigned>(1)) {}

    // Copy constructor
    OdBaseObjectPtr(const OdBaseObjectPtr& other) noexcept : m_pObject(other.m_pObject), ref_count(other.ref_count) {
        addRef();
    }

    // Move constructor
    OdBaseObjectPtr(OdBaseObjectPtr&& other) noexcept : m_pObject(other.m_pObject), ref_count(other.ref_count) {
        other.m_pObject = nullptr;
        other.ref_count = nullptr;
    }

    // Destructor
    ~OdBaseObjectPtr() {
        release();
    }

    // Copy assignment operator
    OdBaseObjectPtr& operator=(const OdBaseObjectPtr& other) noexcept {
        if (this != &other) {
            release();
            m_pObject = other.m_pObject;
            ref_count = other.ref_count;
            addRef();
        }
        return *this;
    }

    // Move assignment operator
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

    // Reset the pointer to nullptr
    void reset() noexcept {
        release();
    }

    // Reset the pointer to a new object
    void reset(OdBaseObject* pSource) {
        if (m_pObject != pSource) {
            release();
            if (pSource) {
                m_pObject = pSource;
                ref_count = new std::atomic<unsigned>(1);
            }
        }
    }

    // Swap with another pointer
    void swap(OdBaseObjectPtr& other) noexcept {
        std::swap(m_pObject, other.m_pObject);
        std::swap(ref_count, other.ref_count);
    }

    // Get the raw pointer
    OdBaseObject* get() const noexcept {
        return m_pObject;
    }

    // Use count
    unsigned use_count() const noexcept {
        return ref_count ? ref_count->load(std::memory_order_relaxed) : 0;
    }

    // Check if unique
    bool unique() const noexcept {
        return use_count() == 1;
    }

    // Bool conversion
    explicit operator bool() const noexcept {
        return m_pObject != nullptr;
    }

    // Operator->
    OdBaseObject* operator->() const noexcept {
        return m_pObject;
    }

    // Operator*
    OdBaseObject& operator*() const {
        return *m_pObject;
    }

    // Comparison operators
    bool operator==(const OdBaseObjectPtr& other) const noexcept {
        return m_pObject == other.m_pObject;
    }

    bool operator!=(const OdBaseObjectPtr& other) const noexcept {
        return m_pObject != other.m_pObject;
    }

protected:
    void addRef() {
        if (ref_count) {
            ref_count->fetch_add(1, std::memory_order_relaxed);
        }
    }

    /// <summary>
    /// Do not set m_pObject and ref_count to nullptr if the reference count is not zero
    /// </summary>
    void release() {
        if (ref_count) {
            if (ref_count->fetch_sub(1, std::memory_order_acq_rel) == 1) {
                delete m_pObject;
                delete ref_count;
                m_pObject = nullptr;
                ref_count = nullptr;
            }
        }
    }

};



class OdObjectFactory {
public:
    using CreateFunction = OdBaseObject * (*)();

private:
    static std::unordered_map<std::string, CreateFunction> m_registry;

public:
    static void registerClass(std::string className, CreateFunction createFn) {
        m_registry[className] = createFn;
    }

    static OdBaseObjectPtr createObject(std::string className) {
        auto it = m_registry.find(className);
        if (it != m_registry.end()) {
            return OdBaseObjectPtr(it->second());
        }
        return OdBaseObjectPtr();
    }
};

// OdSmartPtr implementation
template <class T>
class OdSmartPtr : public OdBaseObjectPtr {
public:
    // Default constructor
    OdSmartPtr() noexcept : OdBaseObjectPtr() {}

    // Constructor from raw pointer
    explicit OdSmartPtr(T* rawPtr) : OdBaseObjectPtr(rawPtr) {}

    // Copy constructor
    OdSmartPtr(const OdSmartPtr<T>& sp) noexcept : OdBaseObjectPtr(sp) {}

    // Move constructor
    OdSmartPtr(OdSmartPtr<T>&& sp) noexcept : OdBaseObjectPtr(std::move(sp)) {}

    // Constructor from OdBaseObjectPtr
    OdSmartPtr(const OdBaseObjectPtr& basePtr) noexcept : OdBaseObjectPtr(basePtr) {}

    // Copy assignment operator
    OdSmartPtr<T>& operator=(const OdSmartPtr<T>& sp) noexcept {
        OdBaseObjectPtr::operator=(sp);
        return *this;
    }

    // Move assignment operator
    OdSmartPtr<T>& operator=(OdSmartPtr<T>&& sp) noexcept {
        OdBaseObjectPtr::operator=(std::move(sp));
        return *this;
    }

    // Reset the pointer
    void reset() noexcept {
        OdBaseObjectPtr::reset();
    }

    void reset(T* rawPtr) {
        OdBaseObjectPtr::reset(rawPtr);
    }

    // Swap function
    void swap(OdSmartPtr<T>& other) noexcept {
        OdBaseObjectPtr::swap(other);
    }

    // Operator->
    T* operator->() const noexcept {
        return static_cast<T*>(m_pObject);
    }

    // Operator*
    T& operator*() const {
        return *static_cast<T*>(m_pObject);
    }

    // Get the raw pointer
    T* get() const noexcept {
        return static_cast<T*>(m_pObject);
    }
};

// OdBaseObject definition remains the same
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
    virtual bool isKindOf(std::string className) const = 0;

    virtual OdBaseObjectPtr Clone() = 0;
};

// RTTI macros remain the same, but you can adjust them if needed

#define OD_RTTI_DECLARE_ABSTRACT(ClassName, BaseClassName) \
public: \
    static std::string desc() { return #ClassName; } \
    static std::string baseClassName() { return #BaseClassName; } \
    virtual std::string getClassName() const override { return ClassName::desc(); } \
    inline virtual bool isKindOf(std::string desc) const override;

#define OD_RTTI_DECLARE(ClassName, BaseClassName) \
public: \
    static std::string desc() { return #ClassName; } \
    static std::string baseClassName() { return #BaseClassName; } \
    virtual std::string getClassName() const override { return ClassName::desc(); } \
    inline virtual bool isKindOf(std::string desc) const override; \
    static OdSmartPtr<ClassName> createObject(); \
    static OdBaseObjectPtr createObject(std::string className); \
    static OdSmartPtr<ClassName> cast(const OdSmartPtr<BaseClassName>& obj); \
    static OdSmartPtr<ClassName> cast(const OdBaseObjectPtr& obj); \
    static OdSmartPtr<ClassName> cast(OdBaseObject* obj);

#define OD_RTTI_DEFINE_ABSTRACT(ClassName, BaseClassName) \
    inline bool ClassName::isKindOf(std::string desc) const { \
        if (desc == getClassName()) { \
            return true; \
        } \
        const BaseClassName* basePtr = static_cast<const BaseClassName*>(this); \
        if (basePtr) { \
            return basePtr->isKindOf(desc); \
        } \
        else { \
            return false; \
        } \
    }

#define OD_RTTI_DEFINE(ClassName, BaseClassName) \
    inline bool ClassName::isKindOf(std::string desc) const { \
        if (desc == getClassName()) { \
            return true; \
        } \
        const BaseClassName* basePtr = static_cast<const BaseClassName*>(this); \
        if (basePtr) { \
            return basePtr->isKindOf(desc); \
        } else { \
            return false; \
        } \
    } \
    inline OdSmartPtr<ClassName> ClassName::createObject() { \
        return OdSmartPtr<ClassName>(new ClassName()); \
    } \
    inline OdBaseObjectPtr ClassName::createObject(std::string className) { \
        return OdObjectFactory::createObject(className); \
    } \
    inline OdSmartPtr<ClassName> ClassName::cast(const OdSmartPtr<BaseClassName>& obj) { \
        if (obj && obj->isKindOf(ClassName::desc())) { \
            return OdSmartPtr<ClassName>(obj); \
        } \
        return OdSmartPtr<ClassName>(); \
    } \
    inline OdSmartPtr<ClassName> ClassName::cast(const OdBaseObjectPtr& obj) { \
        if (obj && obj->isKindOf(ClassName::desc())) { \
            return OdSmartPtr<ClassName>(obj); \
        } \
        return OdSmartPtr<ClassName>(); \
    }

#define OD_RTTI_REGISTER_CLASS(ClassName) \
    static OdBaseObject* createInstance() { return new ClassName(); } \
    static void registerClass() { \
        OdObjectFactory::registerClass(ClassName::desc(), &ClassName::createInstance); \
    } \
    static struct ClassName##FactoryRegistrar { \
        ClassName##FactoryRegistrar() { \
            ClassName::registerClass(); \
        } \
    } s_##ClassName##FactoryRegistrar;


#define OD_RTTI_SINGLETON_DECLARE(ClassName) \
private: \
    static OdSmartPtr<ClassName> m_instance; \
public: \
    static OdSmartPtr<ClassName>& R();

#define OD_RTTI_SINGLETON_DEFINE(ClassName) \
OdSmartPtr<ClassName> ClassName::m_instance; \
OdSmartPtr<ClassName>& ClassName::R() \
{ \
    if (!m_instance) \
    { \
        m_instance = ClassName::createObject(); \
    } \
    return m_instance; \
}

template<typename T>
OdSmartPtr<T> static_pointer_cast(const OdBaseObjectPtr& basePtr) {
    T* derivedPtr = dynamic_cast<T*>(basePtr.get());
    if (derivedPtr) {
        return OdSmartPtr<T>(basePtr);
    }
    else {
        return OdSmartPtr<T>();
    }
}
