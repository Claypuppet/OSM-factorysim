//
// Created by don on 19-4-18.
//

#include "AppConnectionHandler.h"
#include "network/Protocol.h"
#include "NotificationTypes.h"

/**
 * The constructor (Set temp application pointer till observer - notifier pattern implementation)
 * @param app
 */

core::AppConnectionHandler::AppConnectionHandler() {}

/**
 * A handler for when a connection fails
 * @param connection
 * @param error
 */

void core::AppConnectionHandler::onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) {
    Network::IConnectionHandler::onConnectionFailed(connection, error);
    std::cout << "Connection failed!" << std::endl;
}

/**
 * A handler for when a connection is established
 * @param connection
 */

void core::AppConnectionHandler::onConnectionEstablished(Network::ConnectionPtr connection) {
    //std::cout << "test" << std::endl;
}

/**
 * A handler for when a connection disconnects
 * @param connection
 * @param error
 */

void core::AppConnectionHandler::onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) {
    std::cout << "Disconnected!" << std::endl;
}

/**
 * A handler for when a message is received
 * @param connection
 * @param message
 */

void core::AppConnectionHandler::onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) {
    std::cout << "Received a message!" << std::endl;
    uint8_t messageType = message.getMessageType();
    switch(messageType)
    {
        case Network::Protocol::kAppMessageTypeRegisterMachine:
            handleRegisterMachine(connection, message);
            break;
        case Network::Protocol::kAppMessageTypeInitialConfigure:
            handleStartInit(message);
            break;
        case Network::Protocol::kAppMessageTypeOK:
            handleOK(message);
            break;
        case Network::Protocol::kAppMessageTypeNOK:
            handleNOK(message);
            break;
        case Network::Protocol::kAppMessageTypeDoneProcessing:
            handleDoneProcessing(message);
            break;
        case Network::Protocol::kAppMessageTypeStartedProcessing:
            handleStartProcessing(message);
            break;
        case Network::Protocol::kAppMessageTypeReady:
            handleMachineReady(message);
            break;
        default:
            break;
    }
}

/**
 * A handler for when a message is sent
 * @param connection
 * @param message
 */

void core::AppConnectionHandler::onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) {
    Network::IConnectionHandler::onConnectionMessageSent(connection, message);
    std::cout << "Message sent!" << std::endl;
}

void core::AppConnectionHandler::handleRegisterMachine(Network::ConnectionPtr connection, Network::Message &message) {
    auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationRegisterMachine);
    auto machineId = static_cast<uint16_t >(std::strtoul(message.getBody().c_str(), nullptr, 10));

    notification.setArgument(0, machineId);
    notification.setArgument(1, connection);

    notifyObservers(notification);
}

void core::AppConnectionHandler::handleMachineReady(Network::Message &message) {
    auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationMachineReady);
    auto machineId = static_cast<uint16_t>(std::strtoul(message.getBody().c_str(), nullptr, 10));

    notification.setArgument(0, machineId);

    notifyObservers(notification);
}

void core::AppConnectionHandler::handleStartInit(Network::Message &message) {
    auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationStartInit);
    auto machineId = static_cast<uint16_t>(std::strtoul(message.getBody().c_str(), nullptr, 10));

    notification.setArgument(0, machineId);

    notifyObservers(notification);
}

void core::AppConnectionHandler::handleStartProcessing(Network::Message &message) {
    auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationStartProcessing);
    auto machineId = static_cast<uint16_t>(std::strtoul(message.getBody().c_str(), nullptr, 10));

    notification.setArgument(0, machineId);

    notifyObservers(notification);
}

void core::AppConnectionHandler::handleDoneProcessing(Network::Message &message) {
    auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationDoneProcessing);
    auto machineId = static_cast<uint16_t >(std::strtoul(message.getBody().c_str(), nullptr, 10));

    notification.setArgument(0, machineId);

    notifyObservers(notification);
}

void core::AppConnectionHandler::handleOK(Network::Message &message) {
    auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationOK);
    auto machineId = static_cast<uint16_t >(std::strtoul(message.getBody().c_str(), nullptr, 10));

    notification.setArgument(0, machineId);

    notifyObservers(notification);
}

void core::AppConnectionHandler::handleNOK(Network::Message &message) {
    auto notification = makeNotifcation(Patterns::NotifyObserver::NotifyTrigger(), NotifyEventIds::eApplicationNOK);
    auto machineId = static_cast<uint16_t >(std::strtoul(message.getBody().c_str(), nullptr, 10));

    notification.setArgument(0, machineId);

    notifyObservers(notification);
}
