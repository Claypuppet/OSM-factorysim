//
// Created by hqnders on 09/05/18.
//
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <models/Configuration.h>

#include "../test_helpers/MockNetwork.h"

#include "../machine_control/SimulationController.h"
#include "../../src/machine_control/states_production/ConnectState.h"
#include "../../src/machine_control/states_production/ReceiveConfig.h"
#include "../../src/machine_control/states_production/Inititalization/ConfigureState.h"
#include "../../src/machine_control/states_production/InOperation/IdleState.h"
#include "../../src/machine_control/states_production/Inititalization/SelfTestState.h"

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

BOOST_AUTO_TEST_CASE(MachineControlConnectToReceiveConfigToConfig) {
  auto mockNetwork = std::make_shared<testutils::MockNetwork>();
  mockNetwork->startMockPCServerApplication();


  // 1: make application context
  machinecore::Application application(1);

  // 2. create state sets application to that state
  auto state = std::make_shared<productionstates::ReceiveConfig>(productionstates::ReceiveConfig(application));
  BOOST_CHECK_NO_THROW(application.setCurrentState(state));

  //3. checks if in the right state
  BOOST_CHECK_EQUAL(!!std::dynamic_pointer_cast<productionstates::ReceiveConfig>(application.getCurrentState()), true);

  //4. makes vector and makes machineConfig
  std::vector<models::MachineConfiguration> confVector;
  models::MachineConfiguration config0  = models::MachineConfiguration(0);
  confVector.push_back(config0);
  application.setConfigurations(confVector);


  //5. checks if configcheck works
  BOOST_CHECK_EQUAL(application.setCurrentConfigId(0), true);

  //6. schedules switchEvent with right confignumber(0)
  auto switchEvent1 = std::make_shared<productionstates::Event>(productionstates::kEventTypeReceivedConfig);
  switchEvent1->setArgument<uint32_t>(0);
  BOOST_CHECK_NO_THROW(application.scheduleEvent(switchEvent1));
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


  //2. makes vector and makes machineConfig
  std::vector<models::MachineConfiguration> confVector;
  models::MachineConfiguration config0  = models::MachineConfiguration(0);
  confVector.push_back(config0);
  application.setConfigurations(confVector);

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

// Einde public method tests
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
  testutils::OnMessageFn callback = [](const Network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), Network::Protocol::kAppMessageTypeOK);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendResponseOK();
  productionServer->awaitMessageReceived();

  // prepare test on machine control when message will receive: kAppMessageTypeNOK
  callback = [](const Network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), Network::Protocol::kAppMessageTypeNOK);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendResponseNOK(0);
  productionServer->awaitMessageReceived();

  // prepare test on machine control when message will receive: kAppMessageTypeDoneProcessing
  callback = [](const Network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), Network::Protocol::kAppMessageTypeDoneProcessing);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendStatusUpdateDone();
  productionServer->awaitMessageReceived();

  // prepare test on machine control when message will receive: kAppMessageTypeReady
  callback = [](const Network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), Network::Protocol::kAppMessageTypeReady);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendStatusUpdateReady();
  productionServer->awaitMessageReceived();

  // prepare test on machine control when message will receive: kAppMessageTypeStartedProcessing
  callback = [](const Network::Message &message){
    BOOST_CHECK_EQUAL(message.getMessageType(), Network::Protocol::kAppMessageTypeStartedProcessing);
  };
  productionServer->setOnMessageFn(callback);
  machineNetwork->sendStatusUpdateStarted();
  productionServer->awaitMessageReceived();


}

// Einde public method tests
BOOST_AUTO_TEST_SUITE_END()
