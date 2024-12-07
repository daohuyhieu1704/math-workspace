#include "pch.h"
#include "OdHostAppService.h"
#include <gtest/gtest.h>

/// <summary>
/// Test fixture for OdHostAppService
/// </summary>
class OdHostAppServiceTest : public ::testing::Test {
protected:
    OdHostAppServicePtr hostAppService;

    // Setup runs before each test case
    virtual void SetUp() override {
        hostAppService = OdHostAppService::R();
    }
};

/// <summary>
/// SingletonInstance test ensures that only one instance of OdHostAppService exists.
/// </summary>
TEST_F(OdHostAppServiceTest, SingletonInstance) {
    auto& instance1 = OdHostAppService::R();
    auto& instance2 = OdHostAppService::R();

    // Verify that both instances are the same
    EXPECT_EQ(instance1.get(), instance2.get()) << "Singleton instances should be the same.";

    // Ensure the instance is not null
    EXPECT_NE(instance1.get(), nullptr) << "Singleton instance should not be null.";
}
//
///// <summary>
///// CreateSession test verifies that a new session is created successfully and can be retrieved.
///// </summary>
//TEST_F(OdHostAppServiceTest, CreateSession) {
//    std::string sessionId = "Session1";
//    auto session = hostAppService->createSession(sessionId);
//
//    // Ensure the session is created successfully
//    EXPECT_NE(session.get(), nullptr) << "Session should be created successfully.";
//
//    // Verify the session can be retrieved
//    auto retrievedSession = hostAppService->getSession(sessionId);
//    EXPECT_EQ(session.get(), retrievedSession.get()) << "Retrieved session should match the created session.";
//}
//
///// <summary>
///// ChangeCurrSession test verifies that the current session can be changed successfully.
///// </summary>
//TEST_F(OdHostAppServiceTest, ChangeCurrSession) {
//    std::string sessionId1 = "Session1";
//    std::string sessionId2 = "Session2";
//
//    // Create two sessions
//    hostAppService->createSession(sessionId1);
//    hostAppService->createSession(sessionId2);
//
//    // Change the current session
//    hostAppService->ChangeCurrSession(sessionId1);
//    auto currentSession = hostAppService->getCurrentSession();
//
//    // Verify the current session is updated
//    EXPECT_NE(currentSession.get(), nullptr) << "Current session should not be null.";
//    EXPECT_EQ(currentSession, hostAppService->getSession(sessionId1)) << "Current session should match Session1.";
//}
//
///// <summary>
///// RemoveSession test verifies that a session can be removed successfully.
///// </summary>
//TEST_F(OdHostAppServiceTest, RemoveSession) {
//    std::string sessionId = "SessionToRemove";
//
//    // Create a session
//    auto session = hostAppService->createSession(sessionId);
//    EXPECT_NE(session.get(), nullptr) << "Session should be created successfully.";
//
//    // Remove the session
//    hostAppService->removeSession(sessionId);
//
//    // Verify the session is removed
//    auto retrievedSession = hostAppService->getSession(sessionId);
//    EXPECT_EQ(retrievedSession.get(), nullptr) << "Session should be removed successfully.";
//}
//
///// <summary>
///// ExecuteAllPrompts test ensures that the function can execute all prompts in the current session.
///// </summary>
//TEST_F(OdHostAppServiceTest, ExecuteAllPrompts) {
//    std::string sessionId = "SessionWithPrompts";
//
//    // Create a session and set it as current
//    hostAppService->createSession(sessionId);
//    hostAppService->ChangeCurrSession(sessionId);
//
//    // Execute all prompts (mocked behavior)
//    EXPECT_NO_THROW(hostAppService->ExecuteAllPrompts()) << "ExecuteAllPrompts should not throw an exception.";
//}
//
///// <summary>
///// RetrieveNonExistentSession test verifies that retrieving a non-existent session returns null.
///// </summary>
//TEST_F(OdHostAppServiceTest, RetrieveNonExistentSession) {
//    std::string invalidSessionId = "InvalidSession";
//
//    // Attempt to retrieve a non-existent session
//    auto session = hostAppService->getSession(invalidSessionId);
//
//    // Verify that the session is null
//    EXPECT_EQ(session.get(), nullptr) << "Retrieving a non-existent session should return null.";
//}
//
///// <summary>
///// ChangeInvalidCurrentSession test ensures that attempting to change to a non-existent session does not affect the current session.
///// </summary>
//TEST_F(OdHostAppServiceTest, ChangeInvalidCurrentSession) {
//    std::string validSessionId = "ValidSession";
//    std::string invalidSessionId = "InvalidSession";
//
//    // Create a valid session and set it as current
//    hostAppService->createSession(validSessionId);
//    hostAppService->ChangeCurrSession(validSessionId);
//
//    // Attempt to change to an invalid session
//    hostAppService->ChangeCurrSession(invalidSessionId);
//
//    // Verify that the current session remains unchanged
//    auto currentSession = hostAppService->getCurrentSession();
//    EXPECT_EQ(currentSession, hostAppService->getSession(validSessionId)) << "Current session should remain unchanged.";
//}
