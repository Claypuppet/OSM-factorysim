//
// Created by hqnders on 09/05/18.
//
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "../test_helpers/MockNetwork.h"

#include "../machine_control/SimulationController.h"
#include "../../src/machine_control/states_production/ConnectState.h"
#include "../../src/machine_control/states_production/ReceiveConfig.h"

BOOST_AUTO_TEST_SUITE(MachineControlProductionStateTests)

BOOST_AUTO_TEST_CASE(MachineControlConnectToReceiveConfigState) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  machinecore::Application application(1);
  BOOST_CHECK_NO_THROW(application.setStartState());

  auto switchevent = std::make_shared<productionstates::Event>(productionstates::kEventTypeConnected);

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::ConnectState>(application.getCurrentState()), true);

  BOOST_CHECK_NO_THROW(application.scheduleEvent(switchevent));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::ReceiveConfig>(application.getCurrentState()), true);

  application.stop();
  mockNetwork->stop();
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()