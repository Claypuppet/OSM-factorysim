//
// Created by hqnders on 09/05/18.
//
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "../test_helpers/MockNetwork.h"

#include <models/Machine.h>

BOOST_AUTO_TEST_SUITE(NetworkTests)

BOOST_AUTO_TEST_CASE(TestMessageSerialization) {

  models::MachinePtr machine = std::make_shared<models::Machine>(1, "zaag");

  BOOST_CHECK_EQUAL(machine->getName(), "zaag");
  BOOST_CHECK_EQUAL(machine->getId(), 1);

  network::Message msg;

  BOOST_CHECK(msg.length() == 0);
  BOOST_CHECK_NO_THROW(msg.setBodyObject<models::MachinePtr>(machine));
  BOOST_CHECK(msg.length() > 0);

  auto deserializedMachine = msg.getBodyObject<models::MachinePtr>();

  BOOST_CHECK_EQUAL(deserializedMachine->getName(), "zaag");
  BOOST_CHECK_EQUAL(deserializedMachine->getId(), 1);
}

BOOST_AUTO_TEST_CASE(TestMessageTime){
  
  auto mcMock = std::make_shared<testutils::MockNetwork>();
  auto pcMock = std::make_shared<testutils::MockNetwork>();
  
  testutils::OnMessageFn onMessageFn = [](network::Message& aMessage){
    BOOST_CHECK(aMessage.getTime() == 56789);
    BOOST_CHECK(aMessage.getBody() == "test");
    BOOST_CHECK(aMessage.getMessageType() == 12);
  };
  
  network::Message message;
  message.setTime(56789);
  message.setBody("test");
  message.setMessageType(12);
  
  pcMock->setOnMessageFn(onMessageFn);
  
  BOOST_REQUIRE_NO_THROW(pcMock->startMockPCServerApplication());
  BOOST_REQUIRE_NO_THROW(mcMock->startMockMCClientApplication());
  
  pcMock->awaitConnection();
  
  BOOST_REQUIRE_NO_THROW(mcMock->sendMessage(message));
  
  pcMock->awaitMessageReceived();
  
  mcMock->stop();
  pcMock->stop();
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()