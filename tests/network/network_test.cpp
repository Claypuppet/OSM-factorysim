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

  Network::Message msg;

  BOOST_CHECK(msg.length() == 0);
  BOOST_CHECK_NO_THROW(msg.setBodyObject<models::MachinePtr>(machine));
  BOOST_CHECK(msg.length() > 0);

  auto deserializedMachine = msg.getBodyObject<models::MachinePtr>();

  BOOST_CHECK_EQUAL(deserializedMachine->getName(), "zaag");
  BOOST_CHECK_EQUAL(deserializedMachine->getId(), 1);
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()