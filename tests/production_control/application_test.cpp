//
// Created by don on 15-5-18.
//

#include <boost/test/unit_test.hpp>
#include "../../src/production_control/Application.h"
#include "../test_helpers/MockNetwork.h"

BOOST_AUTO_TEST_SUITE(ProductionControlApplicationNetworkTests)

BOOST_AUTO_TEST_CASE(ProductionControlSendStartProcess)
{
  core::Application app;
  models::Machine machine(12, "test_machine");

  BOOST_REQUIRE_NO_THROW(app.addMachine(core::Machine(machine)));

  auto machineMock = std::make_shared<testutils::MockNetwork>();

  testutils::OnMessageFn onMessageFn =[](const Network::Message& message){
    BOOST_CHECK(message.getMessageType() == Network::Protocol::kAppMessageTypeStartProcess);
  };

  BOOST_REQUIRE_NO_THROW(machineMock->setOnMessageFn(onMessageFn));

  app.setupNetwork();
  app.startServer();

  while(!app.isServerRunning());

  machineMock->startMockMCClientApplication();

  Network::Message message(Network::Protocol::kAppMessageTypeRegisterMachine, "12");
  machineMock->awaitConnection();

  BOOST_REQUIRE_NO_THROW(machineMock->sendMessage(message));

  //Wait until machine is registered
  while(!app.getMachine(12));

  while(!app.getMachine(12)->isConnected());

  std::cout << "Machine connected" << std::endl;

  BOOST_REQUIRE_NO_THROW(app.sendStartProcessing(12));

  machineMock->awaitMessageReceived();

  machineMock->stop();
  app.stopServer();

}

BOOST_AUTO_TEST_SUITE_END()