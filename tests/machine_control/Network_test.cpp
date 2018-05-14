#include <boost/test/unit_test.hpp>
#include <network/Protocol.h>
#include "network/Client.h"
#include "../test_helpers/MockNetwork.h"
#include "../../src/machine_control/Application.h"
#include "../../src/machine_control/SimulationNetworkComponent.h"

BOOST_AUTO_TEST_SUITE(MachineControlNetworkTestSuite)

BOOST_AUTO_TEST_CASE(RegisterMachine)
{
  // TODO fix errors in this test case
//  Network::Manager manager;
//  manager.setRemotePort(Network::Protocol::kPortProductionCommunication);
//  auto pcMock = std::make_shared<testUtils::MockNetwork>();
//
//  SimulationCommunication::SimulationNetworkComponent networkComponent;
//  auto client = manager.createClient(std::make_shared<Communication::NetworkComponent>(networkComponent));
//
//  pcMock->startMockPCServerController();
//  client->start();
//
//  std::shared_ptr<Network::Message> msgPtr = nullptr;
//
//  std::function<void(const Network::Message&)> onMessageFn = [msgPtr](const Network::Message& msg){
//    msgPtr = std::make_shared<Network::Message>(msg);
//  };
//
//  pcMock->setOnMessageFn(onMessageFn);
//  pcMock->awaitConnection();
//
//  networkComponent.sendRegisterMessage(5);
//
//  BOOST_REQUIRE(msgPtr != nullptr);
//  BOOST_CHECK(msgPtr->getBody() == "5");
//  BOOST_CHECK(msgPtr->getMessageType() == Network::Protocol::SimMessageType::kSimMessageTypeRegister);
}

BOOST_AUTO_TEST_SUITE_END()