#include <boost/test/unit_test.hpp>
#include <network/Protocol.h>
#include "network/Client.h"
#include "../test_helpers/MockNetwork.h"
#include "../../src/machine_control/Application.h"

BOOST_AUTO_TEST_SUITE(MachineControlNetworkTestSuite)

BOOST_AUTO_TEST_CASE(RegisterMachine)
{
  Network::Manager manager;
  manager.setRemotePort(Network::Protocol::kPortProductionCommunication);
  auto pcMock = std::make_shared<testUtils::MockNetwork>();

  Communication::NetworkComponent networkComponent;
  auto client = manager.createClient(std::make_shared<Communication::NetworkComponent>(networkComponent));

  pcMock->startMockPCServerController();
  client->start();

  std::shared_ptr<Network::Message> msgPtr;

  //TODO check if message is received
//  pcMock->setOnMessageFn([msgPtr](const Network::Message& msg){
//    msgPtr = std::make_shared<Network::Message>(msg);
//  });
//  pcMock->awaitConnection();
//
//  networkComponent.sendRegisterMessage(5);

}

BOOST_AUTO_TEST_SUITE_END()