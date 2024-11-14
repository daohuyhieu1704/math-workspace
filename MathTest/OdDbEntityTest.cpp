#include "pch.h"
#include "OdDbEntity.h"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef OdSmartPtr<class OdDbEntityDerived> OdDbEntityDerivedPtr;

class OdDbEntityDerived : public OdDbEntity {
    OD_RTTI_DECLARE(OdDbEntityDerived, OdDbEntity);
public:
    OdDbEntityDerived() = default;
    OdGeExtents3d boundingBox() const override { return getExtents(); }
    OdResult worldDraw() const override { return eOk; }

    OdBaseObjectPtr Clone() const override {
        OdDbEntityDerivedPtr pClone = OdDbEntityDerived::createObject();
        pClone->setScale(getScale());
        pClone->setPosition(getPosition());
        pClone->setXDir(getXDir());
        pClone->setYDir(getYDir());
        pClone->setZDir(getZDir());
        pClone->setExtents(getExtents());
        return pClone;
    }

    OdResult draw() const override {
        return OdResult::eOk;
    }
};
OD_RTTI_DEFINE(OdDbEntityDerived, OdDbEntity)

class OdDbEntityTest : public ::testing::Test {
protected:
    OdDbEntityDerivedPtr entity;

    // Set up runs before each test case
    virtual void SetUp() override {
		entity = OdDbEntityDerived::createObject();
        // Set initial values for entity's fields using setters
        entity->setScale(OdGeScale3d(1.0, 2.0, 3.0));
        entity->setPosition(OdGePoint3d(10.0, 20.0, 30.0));
        entity->setXDir(OdGeVector3d(1.0, 0.0, 0.0));
        entity->setYDir(OdGeVector3d(0.0, 1.0, 0.0));
        entity->setZDir(OdGeVector3d(0.0, 0.0, 1.0));
        entity->setExtents(OdGeExtents3d(OdGePoint3d(5.0, 5.0, 5.0), OdGePoint3d(15.0, 15.0, 15.0)));
    }

    // Tear down runs after each test case
    virtual void TearDown() override {
        // No special cleanup required
    }
};

/// <summary>
/// Test toJson verifies that the toJson method correctly serializes the entity's fields into JSON format.
/// </summary>
/// <param name="entity">An OdDbEntity object to serialize.</param>
TEST_F(OdDbEntityTest, toJson) {
    json expectedJson = {
        {"scale", { {"x", 1.0}, {"y", 2.0}, {"z", 3.0} }},
        {"position", { {"x", 10.0}, {"y", 20.0}, {"z", 30.0} }},
        {"xDir", { {"x", 1.0}, {"y", 0.0}, {"z", 0.0} }},
        {"yDir", { {"x", 0.0}, {"y", 1.0}, {"z", 0.0} }},
        {"zDir", { {"x", 0.0}, {"y", 0.0}, {"z", 1.0} }},
        {"extents", {
            {"min", { {"x", 5.0}, {"y", 5.0}, {"z", 5.0} }},
            {"max", { {"x", 15.0}, {"y", 15.0}, {"z", 15.0} }}
        }}
    };
	json actualJson = entity->toJson();
    EXPECT_EQ(actualJson, expectedJson);
}

/// <summary>
/// Test fromJson verifies that the fromJson method correctly deserializes JSON data into the entity's fields.
/// </summary>
/// <param name="entity">An OdDbEntity object to deserialize into.</param>
/// <param name="jsonData">JSON data to deserialize.</param>
TEST_F(OdDbEntityTest, fromJson) {
    json jsonData = {
        {"scale", { {"x", 2.0}, {"y", 4.0}, {"z", 6.0} }},
        {"position", { {"x", 20.0}, {"y", 30.0}, {"z", 40.0} }},
        {"xDir", { {"x", 0.0}, {"y", 1.0}, {"z", 0.0} }},
        {"yDir", { {"x", 0.0}, {"y", 0.0}, {"z", 1.0} }},
        {"zDir", { {"x", 1.0}, {"y", 0.0}, {"z", 0.0} }},
        {"extents", {
            {"min", { {"x", 10.0}, {"y", 10.0}, {"z", 10.0} }},
            {"max", { {"x", 20.0}, {"y", 20.0}, {"z", 20.0} }}
        }}
    };

    // Deserialize the JSON data into the entity object
    entity->fromJson(jsonData);

    // Validate the deserialized values using getters
    EXPECT_EQ(entity->getScale().sx, 2.0);
	EXPECT_EQ(entity->getScale().sy, 4.0);
	EXPECT_EQ(entity->getScale().sz, 6.0);
	EXPECT_EQ(entity->getPosition().x, 20.0);
	EXPECT_EQ(entity->getPosition().y, 30.0);
	EXPECT_EQ(entity->getPosition().z, 40.0);
	EXPECT_EQ(entity->getXDir().x, 0.0);
	EXPECT_EQ(entity->getXDir().y, 1.0);
	EXPECT_EQ(entity->getXDir().z, 0.0);
	EXPECT_EQ(entity->getYDir().x, 0.0);
	EXPECT_EQ(entity->getYDir().y, 0.0);
	EXPECT_EQ(entity->getYDir().z, 1.0);
	EXPECT_EQ(entity->getZDir().x, 1.0);
	EXPECT_EQ(entity->getZDir().y, 0.0);
	EXPECT_EQ(entity->getZDir().z, 0.0);
	EXPECT_EQ(entity->getExtents().GetMinPnt().x, 10.0);
	EXPECT_EQ(entity->getExtents().GetMinPnt().y, 10.0);
	EXPECT_EQ(entity->getExtents().GetMinPnt().z, 10.0);
	EXPECT_EQ(entity->getExtents().GetMaxPnt().x, 20.0);
	EXPECT_EQ(entity->getExtents().GetMaxPnt().y, 20.0);
	EXPECT_EQ(entity->getExtents().GetMaxPnt().z, 20.0);
}

