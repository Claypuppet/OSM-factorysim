//
// Created by don on 15-5-18.
//

#include <boost/test/unit_test.hpp>

#include <models/Configuration.h>

#include "../test_helpers/MockNetwork.h"
#include "../../src/machine_control/Application.h"
#include "../test_helpers/MockNetwork.h"
#include "../test_helpers/MockObserver.h"
#include "../machine_control/SimulationController.h"
#include "../../src/machine_control/states_application/ConnectState.h"
#include "../../src/machine_control/states_application/ReceiveConfig.h"
#include "../../src/machine_control/states_application/Inititalization/ConfigureState.h"
#include "../../src/machine_control/states_application/InOperation/IdleState.h"
#include "../../src/machine_control/states_application/Inititalization/SelfTestState.h"
#include "../../src/machine_control/states_application/InOperation/ProcessProduct/TakeProductState.h"
#include "../../src/machine_control/states_application/InOperation/ProcessProduct/ProcessProductState.h"
#include "../../src/machine_control/states_application/InOperation/ProcessProduct/TakeOutProductState.h"

BOOST_AUTO_TEST_SUITE(MachineControlApplicationTests)

BOOST_AUTO_TEST_CASE(MachineControlConnectToReceiveConfigState) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  machinecore::Application application(1);
  BOOST_CHECK_NO_THROW(application.setStartState());

  auto event = std::make_shared<productionstates::Event>(productionstates::kEventTypeConnected);

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::ConnectState>(application.getCurrentState()), true);

  BOOST_CHECK_NO_THROW(application.scheduleEvent(event));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::ReceiveConfig>(application.getCurrentState()), true);

  application.stop();
  mockNetwork->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlConnectToReceiveConfigToConfig) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();


  // 1: make application context
  machinecore::Application application(1);

  BOOST_CHECK_NO_THROW(application.setupNetwork());

  // 2. create state sets application to that state
  auto state = std::make_shared<productionstates::ReceiveConfig>(productionstates::ReceiveConfig(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  //3. checks if in the right state
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::ReceiveConfig>(application.getCurrentState()), true);

  //4. makes vector and makes machineConfig
  std::vector<models::MachineConfiguration> confVector;
  models::MachineConfiguration config0 = models::MachineConfiguration(0);
  confVector.push_back(config0);
  BOOST_CHECK_NO_THROW(application.setConfigurations(confVector));

  //6. schedules switchEvent with right confignumber(0)
  auto event = std::make_shared<patterns::statemachine::Event>(productionstates::kEventTypeReceivedConfig);
  BOOST_CHECK_NO_THROW(event->setArgument<uint32_t>(0));
  BOOST_CHECK_NO_THROW(application.scheduleEvent(event));
  BOOST_CHECK_NO_THROW(application.run());

  //7. checks if in the right state
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::SelfTestState>(application.getCurrentState()), true);

  application.stop();
  mockNetwork->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlConfigureToIdleState) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  // 1: make application context
  simulator::SimulationApplication application(1);

  BOOST_CHECK_NO_THROW(application.setupNetwork());

  //2. makes vector and makes machineConfig
  std::vector<models::MachineConfiguration> confVector;
  models::MachineConfiguration config0 = models::MachineConfiguration(0);
  confVector.push_back(config0);
  BOOST_CHECK_NO_THROW(application.setConfigurations(confVector));

  //3. checks if sets currentConfigId
  BOOST_CHECK_EQUAL(application.setCurrentConfigId(0), true);

  // 4. create state sets application to that state
  auto state = std::make_shared<productionstates::ConfigureState>(productionstates::ConfigureState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  //5. checks if in the right state
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::ConfigureState>(application.getCurrentState()), true);
  BOOST_CHECK_NO_THROW(application.run());

  //6. checks if in the Idle State
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::IdleState>(application.getCurrentState()), true);

  application.stop();
  mockNetwork->stop();
}

BOOST_AUTO_TEST_CASE(MachineControlSelfTestToIdle) {
  simulator::SimulationApplication application(1);

  auto state = std::make_shared<productionstates::SelfTestState>(productionstates::SelfTestState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::IdleState>(application.getCurrentState()), true);
}

BOOST_AUTO_TEST_CASE(MachineControlRunCycle) {
  simulator::SimulationApplication application(1);

  auto state = std::make_shared<productionstates::IdleState>(productionstates::IdleState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  patterns::notifyobserver::NotifyEvent event(machinecore::NotifyEventType::kNotifyEventTypeStartProcess);
  BOOST_CHECK_NO_THROW(application.handleNotification(event));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::IdleState>(application.getCurrentState()),
                    true);
}

BOOST_AUTO_TEST_CASE(MachineControlConfigCycle) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();

  simulator::SimulationApplication application(1);
  BOOST_CHECK_NO_THROW(application.setupNetwork());

  auto state = std::make_shared<productionstates::IdleState>(productionstates::IdleState(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  std::vector<models::MachineConfiguration> confVector;
  models::MachineConfiguration config0 = models::MachineConfiguration(0);
  confVector.push_back(config0);
  BOOST_CHECK_NO_THROW(application.setConfigurations(confVector));

  patterns::notifyobserver::NotifyEvent
      notification(machinecore::NotifyEventType::kNotifyEventTypeMachineConfigReceived);
  BOOST_CHECK_NO_THROW(notification.setArgument(0, (uint32_t)0));

  BOOST_CHECK_NO_THROW(application.handleNotification(notification));

  BOOST_CHECK_NO_THROW(application.run());

  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::IdleState>(application.getCurrentState()), true);

  application.stop();
  mockNetwork->stop();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MachineControlProductionNetworkTests)

BOOST_AUTO_TEST_CASE(MachineControlSendMachineUpdates) {
  // Create server and client
  auto machineEndpoint = std::make_shared<testutils::MockNetwork>();
  auto productionServer = std::make_shared<testutils::MockNetwork>();

  auto machineNetwork = std::make_shared<Communication::NetworkComponent>();
  machineEndpoint->setConnectionHandler(machineNetwork);

  // Start server, start client, wait for connection on server
  productionServer->startMockPCServerApplication();
  machineEndpoint->startMockMCClientApplication();
  productionServer->awaitClientConnecting();

  // prepare test on machine control when message will receive: kAppMessageTypeOK
  testutils::OnMessageFn callback = [](network::Message &message) {
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kAppMessageTypeOK);
    BOOST_CHECK_EQUAL(message.getBodyObject<models::Machine::MachineStatus>(), models::Machine::kMachineStatusSelftesting);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendStatusUpdate(models::Machine::kMachineStatusSelftesting);
  productionServer->awaitMessageReceived();

  // prepare test on machine control when message will receive: kAppMessageTypeNOK
  callback = [](network::Message &message) {
    BOOST_CHECK_EQUAL(message.getMessageType(), network::Protocol::kAppMessageTypeNOK);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendResponseNOK(0);
  productionServer->awaitMessageReceived();


}

BOOST_AUTO_TEST_CASE(MachineControlHandleStartProcess) {
  // Deze moet opnieuw ivm gebruik van manager en client. hiervoor kan mocknetwork gebruikt worden.
  testutils::MockObserver mockObserver;

  testutils::NotificationHandlerFn notificationHandler = [](const patterns::notifyobserver::NotifyEvent &event) {
    BOOST_CHECK(event.getEventId() == machinecore::kNotifyEventTypeStartProcess);
  };

  mockObserver.setHandleNotificationFn(notificationHandler);

  auto networkComponent = std::make_shared<Communication::NetworkComponent>();
  networkComponent->addObserver(mockObserver);

  auto pcMock = std::make_shared<testutils::MockNetwork>();

  network::Manager manager;
  manager.setRemotePort(network::Protocol::PORT_PRODUCTION_COMMUNICATION);

  auto clientThread = manager.runServiceThread();
  auto client = manager.createClient(networkComponent);

  BOOST_REQUIRE_NO_THROW(pcMock->startMockPCServerApplication());

  client->start();
  pcMock->awaitConnection();
  network::Message message(network::Protocol::kAppMessageTypeStartProcess);

  BOOST_REQUIRE_NO_THROW(pcMock->sendMessage(message));

  mockObserver.awaitNotificationReceived();

  pcMock->stop();
  manager.stop();
  clientThread->join();
}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()