
#include <boost/test/unit_test.hpp>

#include <models/Configuration.h>
#include <utils/time/Time.h>

#include "../test_helpers/MockNetwork.h"
#include "../../src/machine_control/Application.h"
#include "../test_helpers/MockObserver.h"
#include "../machine_control/SimulationController.h"
#include "state_inclusions.h"
#include "../test_helpers/HelperFunctions.h"

BOOST_AUTO_TEST_SUITE(MachineControlMachineTests)

BOOST_AUTO_TEST_CASE(MachineControlTestPostProcess) {
  testutils::MockObserver mockObserver;
  simulator::SimulationMachine::setCanBreak(false);

  // Reset time
  const uint64_t START = 100000;
  auto &time = utils::Time::getInstance();
  time.setType(utils::TimeType::customTime);
  time.reset();
  time.syncTime(START); // nice start time!

  // Create some models used by the machine in this test
  std::vector<models::PreviousMachinePtr> prevs = {models::PreviousMachinePtr()};
  auto configuration = std::make_shared<models::MachineConfiguration>(1, 1, prevs);
  auto postProcess = std::make_shared<models::PostProcessInfo>(120 /* 2 min delay */, 30 /* 30 min duration */);

  std::vector<models::MachineConfigurationPtr> confVector = {configuration};
  models::Machine modelMachine(1, 50, 10, 1, 300, postProcess, "", confVector);
  auto machine = std::make_shared<simulator::SimulationMachine>(modelMachine);
  machine->setCurrentConfiguration(configuration);

  machine->addObserver(mockObserver);

  // Set some usable vars
  auto startTime = time.getCurrentTime();
  uint64_t offset = (postProcess->getInputDelayInMillis() - configuration->getProcessTime()); // Offset if starting process again right away

  typedef std::pair<uint64_t, patterns::notifyobserver::NotifyEvent> eventOnMoment;
  std::vector<eventOnMoment> events; // To check at the end

  testutils::NotificationHandlerFn notificationHandler = [&startTime, &configuration, &postProcess, &machine, &events](const patterns::notifyobserver::NotifyEvent &event) {
    auto currentTime = utils::Time::getInstance().getCurrentTime();
    switch(event.getEventId()){
      case machinecore::kNotifyEventTypeProductTakenFromBuffer:{
        BOOST_CHECK_EQUAL(startTime, currentTime);
        break;
      }
      case machinecore::kNotifyEventTypeMachineFinishedProcess:{
        BOOST_CHECK_EQUAL(startTime + configuration->getProcessTime(), currentTime);
        break;
      }
      case machinecore::kNotifyEventTypeProductAddedToBuffer:{
        BOOST_CHECK_EQUAL(startTime + configuration->getProcessTime() + postProcess->getPostProcessDurationInMillis(), currentTime);
        break;
      }
      default:
        BOOST_FAIL("Unhandled event!");
    }
    events.emplace_back(eventOnMoment(currentTime, event));
  };

  mockObserver.setHandleNotificationFn(notificationHandler);

  machine->setInOperationStartState();
  machine->run(); // take product
  machine->run(); // process
  machine->run(); // take out

  BOOST_CHECK_EQUAL(time.getCurrentTime(), startTime + configuration->getProcessTime());
  startTime = time.getCurrentTime();

  // Now we will have to check with the delay
  notificationHandler = [&startTime, &configuration, &postProcess, &machine, offset, &events](const patterns::notifyobserver::NotifyEvent &event) {
    auto currentTime = utils::Time::getInstance().getCurrentTime();
    switch(event.getEventId()){
      case machinecore::kNotifyEventTypeProductTakenFromBuffer:{
        BOOST_CHECK_EQUAL(startTime, currentTime);
        break;
      }
      case machinecore::kNotifyEventTypeMachineFinishedProcess:{
        uint64_t expectedTime = startTime + configuration->getProcessTime();
        BOOST_CHECK_EQUAL(expectedTime + offset, currentTime);
        break;
      }
      case machinecore::kNotifyEventTypeProductAddedToBuffer:{
        uint64_t expectedTime = startTime + configuration->getProcessTime() + postProcess->getPostProcessDurationInMillis();
        BOOST_CHECK_EQUAL(expectedTime + offset, currentTime);
        break;
      }
      default:
        BOOST_FAIL("Unhandled event!");
    }
    events.emplace_back(eventOnMoment(currentTime, event));
  };

  mockObserver.setHandleNotificationFn(notificationHandler);

  machine->setInOperationStartState();
  machine->run(); // take product
  machine->run(); // process
  machine->run(); // take out

  BOOST_CHECK_EQUAL(time.getCurrentTime(), startTime + configuration->getProcessTime() + offset);
  startTime = time.getCurrentTime();

  machine->setInOperationStartState();
  machine->run(); // take product
  machine->run(); // process
  machine->run(); // take out

  BOOST_CHECK_EQUAL(time.getCurrentTime(), startTime + configuration->getProcessTime() + offset);
  startTime = time.getCurrentTime();

  machine->setInOperationStartState();
  machine->run(); // take product
  machine->run(); // process
  machine->run(); // take out

  // Check all event times
  BOOST_REQUIRE_EQUAL(events.size(), 12);
  BOOST_CHECK_EQUAL(events[0].second.getEventId(), machinecore::kNotifyEventTypeProductTakenFromBuffer);
  BOOST_CHECK_EQUAL(events[0].first, START); // product taken from buffer
  BOOST_CHECK_EQUAL(events[1].second.getEventId(), machinecore::kNotifyEventTypeProductAddedToBuffer);
  BOOST_CHECK_EQUAL(events[1].first, START + configuration->getProcessTime() + postProcess->getPostProcessDurationInMillis()); // product placed in buffer
  BOOST_CHECK_EQUAL(events[2].second.getEventId(), machinecore::kNotifyEventTypeMachineFinishedProcess);
  BOOST_CHECK_EQUAL(events[2].first, START + configuration->getProcessTime()); // done process cycle

}

BOOST_AUTO_TEST_SUITE_END()

