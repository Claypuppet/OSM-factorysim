//
// Created by don on 15-5-18.
//

#include <boost/test/unit_test.hpp>
#include "../../src/machine_control/Application.h"
#include "../../src/machine_control/states_production/InOperation/IdleState.h"
#include "../test_helpers/MockNetwork.h"
#include "../test_helpers/MockObserver.h"

BOOST_AUTO_TEST_SUITE(MachineControlApplicationTests)

BOOST_AUTO_TEST_CASE(MachineControlHandleStartProcess)
{

  // Deze moet opnieuw ivm gebruik van manager en client. hiervoor kan mocknetwork gebruikt worden.

  testutils::MockObserver mockObserver;

  testutils::NotificationHandlerFn notificationHandler = [](const patterns::NotifyObserver::NotifyEvent& event){
	BOOST_CHECK(event.getEventId() == machinecore::kNotifyEventTypeStartProcess);
  };

  mockObserver.setHandleNotificationFn(notificationHandler);

  auto networkComponent = std::make_shared<Communication::NetworkComponent>();
  networkComponent->addObserver(mockObserver);

  auto pcMock = std::make_shared<testutils::MockNetwork>();

  Network::Manager manager;
  manager.setRemotePort(Network::Protocol::PORT_PRODUCTION_COMMUNICATION);

  auto clientThread = manager.runServiceThread();
  auto client = manager.createClient(networkComponent);

  BOOST_REQUIRE_NO_THROW(pcMock->startMockPCServerApplication());

  client->start();
  pcMock->awaitConnection();
  Network::Message message(Network::Protocol::kAppMessageTypeStartProcess);

  BOOST_REQUIRE_NO_THROW(pcMock->sendMessage(message));

  mockObserver.awaitNotificationReceived();

  pcMock->stop();
  manager.stop();
  clientThread->join();
}

BOOST_AUTO_TEST_SUITE_END()