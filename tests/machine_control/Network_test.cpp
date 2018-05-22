#include <boost/test/unit_test.hpp>
#include <functional>
#include <network/Protocol.h>
#include "network/Client.h"
#include "../test_helpers/MockNetwork.h"
#include "../../src/machine_control/Application.h"
#include "../../src/machine_control/SimulationNetworkComponent.h"

BOOST_AUTO_TEST_SUITE(MachineControlNetworkTestSuite)

BOOST_AUTO_TEST_CASE(RegisterMachine) {
  network::Manager manager;
  manager.setRemotePort(network::Protocol::PORT_SIMULATION_COMMUNICATION);
  auto pcMock = std::make_shared<testutils::MockNetwork>();

  std::shared_ptr<SimulationCommunication::SimulationNetworkComponent>
      networkComponent = std::make_shared<SimulationCommunication::SimulationNetworkComponent>();

  testutils::OnMessageFn onMessageFn = [](network::Message &message) {
    BOOST_CHECK(message.getBodyObject<std::uint16_t>() == 5);
    BOOST_CHECK(message.getMessageType() == network::Protocol::SimMessageType::kSimMessageTypeRegister);
  };

  BOOST_REQUIRE_NO_THROW(pcMock->setOnMessageFn(onMessageFn));
  pcMock->startMockPCServerController();

  auto thread = manager.runServiceThread();
  auto client =
      manager.createClient(networkComponent);
  BOOST_REQUIRE_NO_THROW(client->start());

  pcMock->awaitClientConnecting();

  BOOST_REQUIRE_NO_THROW(networkComponent->sendRegisterMessage(5));

  pcMock->awaitMessageReceived();

  client->stop();
  manager.stop();
  thread->join();
  pcMock->stop();
}

BOOST_AUTO_TEST_SUITE_END()