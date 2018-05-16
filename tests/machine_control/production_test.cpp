//
// Created by hqnders on 09/05/18.
//
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "../test_helpers/MockNetwork.h"

#include "../machine_control/SimulationController.h"
#include "../../src/machine_control/NetworkComponent.h"
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
