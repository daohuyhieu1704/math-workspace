#include "pch.h"
#include "OdBaseObject.h"
#include <gtest/gtest.h>

typedef OdSmartPtr<class TestObject> TestObjectPtr;
class TestObject : public OdBaseObject {
    OD_RTTI_DECLARE(TestObject, OdBaseObject)
public:
    int value;

    TestObject() : value(0) {}
    TestObject(int v) : value(v) {}

    OdBaseObjectPtr Clone() override
    {
		TestObjectPtr clone = TestObject::createObject();
		clone->value = value;
        return clone;
    }
};
OD_RTTI_DEFINE(TestObject, OdBaseObject)

class OdSmartPtrTest : public ::testing::Test {
protected:
    TestObjectPtr ptr1;
    TestObjectPtr ptr2;

    // Setup runs before each test case
    virtual void SetUp() override {
        ptr1 = TestObject::createObject();
        ptr2 = TestObject::createObject();
		ptr1->isKindOf(TestObject::desc());
    }
};

/// <summary>
/// DefaultConstructor test verifies that the default constructor initializes an object with a reference count of 1.
/// </summary>
TEST_F(OdSmartPtrTest, DefaultConstructor) {
    TestObjectPtr ptr;
    EXPECT_EQ(ptr.getRefCount(), 1);
    EXPECT_EQ(ptr->value, 0);
}

/// <summary>
/// ParameterizedConstructor test verifies that the constructor accepts a raw pointer and initializes correctly.
/// </summary>
/// <param name="ptr">OdSmartPtr with initial value set.</param>
TEST_F(OdSmartPtrTest, ParameterizedConstructor) {
    TestObjectPtr ptr(new TestObject(5));
    EXPECT_EQ(ptr.getRefCount(), 1);
    EXPECT_EQ(ptr->value, 5);
}

/// <summary>
/// CopyConstructor test checks if the copy constructor increments the reference count of the original object.
/// </summary>
/// <param name="ptr1">First OdSmartPtr instance.</param>
/// <param name="ptr2">Copied OdSmartPtr instance with incremented reference count.</param>
TEST_F(OdSmartPtrTest, CopyConstructor) {
    ptr1->value = 10;
    TestObjectPtr ptr2(ptr1);
    EXPECT_EQ(ptr1.getRefCount(), 2);
    EXPECT_EQ(ptr2.getRefCount(), 2);
    EXPECT_EQ(ptr1->value, 10);
    EXPECT_EQ(ptr2->value, 10);
}

/// <summary>
/// AssignmentOperator test verifies that the assignment operator correctly increments the reference count when assigned.
/// </summary>
/// <param name="ptr1">OdSmartPtr instance being assigned.</param>
/// <param name="ptr2">OdSmartPtr instance after assignment.</param>
TEST_F(OdSmartPtrTest, AssignmentOperator) {
    ptr1->value = 20;
    ptr2 = ptr1;
    EXPECT_EQ(ptr1.getRefCount(), 2);
    EXPECT_EQ(ptr2.getRefCount(), 2);
    EXPECT_EQ(ptr1->value, 20);
    EXPECT_EQ(ptr2->value, 20);
}

/// <summary>
/// SelfAssignment test ensures that self-assignment does not change the reference count or modify the objectÅfs state.
/// </summary>
/// <param name="ptr">OdSmartPtr instance assigned to itself.</param>
TEST_F(OdSmartPtrTest, SelfAssignment) {
    ptr1->value = 30;
    ptr1 = ptr1;
    EXPECT_EQ(ptr1.getRefCount(), 1);
    EXPECT_EQ(ptr1->value, 30);
}

/// <summary>
/// DestructorDeletesWhenRefCountIsZero test checks if the object is deleted when the reference count reaches zero.
/// </summary>
/// <param name="ptr1">First OdSmartPtr instance.</param>
/// <param name="ptr2">Second OdSmartPtr instance pointing to the same object as ptr1.</param>
TEST_F(OdSmartPtrTest, DestructorDeletesWhenRefCountIsZero) {
    ptr1->value = 40;

    // Create a copy of ptr1, which increments the reference count
    OdSmartPtr<TestObject> ptr2(ptr1);
    EXPECT_EQ(ptr1.getRefCount(), 2);
    EXPECT_EQ(ptr2.getRefCount(), 2);

    // Simulate deletion by setting ptr1 to nullptr, decreasing the reference count
    ptr1 = nullptr;

    // Check that ptr2 still has a reference count of 1 and retains the value
    EXPECT_EQ(ptr2.getRefCount(), 1);
    EXPECT_EQ(ptr2->value, 40);
}

/// <summary>
/// DereferenceOperator test checks if the dereference operator correctly accesses the object's data.
/// </summary>
/// <param name="ptr1">OdSmartPtr instance dereferenced to access data.</param>
TEST_F(OdSmartPtrTest, DereferenceOperator) {
    ptr1->value = 50;
    EXPECT_EQ((*ptr1).value, 50);
}

/// <summary>
/// ArrowOperator test ensures that the arrow operator correctly accesses the object's member variables.
/// </summary>
/// <param name="ptr1">OdSmartPtr instance accessed with the arrow operator.</param>
TEST_F(OdSmartPtrTest, ArrowOperator) {
    ptr1->value = 60;
    EXPECT_EQ(ptr1->value, 60);
}
