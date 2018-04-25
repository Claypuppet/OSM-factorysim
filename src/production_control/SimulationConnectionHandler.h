//
// Created by don on 24-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H

#include <network/Connection.h>
#include <patterns/notifyobserver/Notifier.hpp>

namespace Core {
    class SimulationConnectionHandler : public Network::IConnectionHandler, public Patterns::NotifyObserver::Notifier {
    public:
        SimulationConnectionHandler() = default;

        virtual ~SimulationConnectionHandler() = default;

        void onConnectionFailed(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

        void onConnectionEstablished(Network::ConnectionPtr connection) override;

        void
        onConnectionDisconnected(Network::ConnectionPtr connection, const boost::system::error_code &error) override;

        void onConnectionMessageReceived(Network::ConnectionPtr connection, Network::Message &message) override;

        void onConnectionMessageSent(Network::ConnectionPtr connection, Network::Message &message) override;
    private:
        void handleConfigMessage(const std::string& msgBody, Network::ConnectionPtr connection);
    };
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONCONNECTIONHANDLER_H
