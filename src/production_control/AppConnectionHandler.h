//
// Created by don on 19-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_COMMNET_H
#define PRODUCTION_LINE_CONTROL_COMMNET_H

#include <patterns/notifyobserver/Notifier.hpp>
#include "network/Connection.h"
#include "Application.h"
#include "NetworkMapper.h"

namespace core {
    class AppConnectionHandler :
        public Network::IConnectionHandler,
        public Patterns::NotifyObserver::Notifier,
        public NetworkMapper{
    public:
        AppConnectionHandler();

        virtual ~AppConnectionHandler() = default;

    private:

        void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

        void onConnectionEstablished(Network::ConnectionPtr connection) override;

        void
        onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

        /**
         * Handles incoming messages
         * @param connection : The connection that send the message
         * @param message The : incoming message
         */
        void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

        void onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) override;

        /**
         * Make notification for registering a machine
         * @param connection : The connection of the machine
         * @param message : The incoming message
         */
        void handleRegisterMachine(Network::ConnectionPtr connection, Network::Message &message);

        /**
         * Makes notification to indicate a machine is ready for production
         * @param message : The incoming message
         */
        void handleMachineReady(Network::Message &message);

        /**
         * Makes notification to indicate a machine started initialising
         * @param message : The incoming message
         */
        void handleStartInit(Network::Message& message);

        /**
         * Makes notification to indicate a machine started processing a product
         * @param message : The incoming message
         */
        void handleStartProcessing(Network::Message& message);

        /**
         * Makes notification to indicate a machine is done processing a product
         * @param message : The incoming message
         */
        void handleDoneProcessing(Network::Message& message);

        /**
         * Makes a notification to indicate a machine send an OK message
         * @param message : The incoming message
         */
        void handleOK(Network::Message& message);

        /**
         * Makes a notification to indicate a machine send a NOK message
         * @param message : The incoming message
         */
        void handleNOK(Network::Message& message);
    };
}


#endif //PRODUCTION_LINE_CONTROL_COMMNET_H
