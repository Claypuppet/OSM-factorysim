//
// Created by don on 15-5-18.
//

#include <boost/test/unit_test.hpp>
#include "../../src/machine_control/Application.h"

BOOST_AUTO_TEST_SUITE(MachineControlApplicationTests)

BOOST_AUTO_TEST_CASE(MachineControlHandleStartProcess)
{
  machinecore::Application app(5);

  app.setupNetwork();
  //TODO finish unit test to check if the state swicthes correctly
  //TODO wait until the states are implemented
  //app.setCurrentState();
}

BOOST_AUTO_TEST_SUITE_END()