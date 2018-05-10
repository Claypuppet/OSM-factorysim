//
// Created by don on 20-4-18.
//

#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H


#include <network/Connection.h>
#include <models/Machine.h>
#include "Machine.h"

namespace simulation {

	/**
	 * Machine used in simulations, adds a simulation connection.
	 * Inherits Core::Machine : Core machine is used in the application, this simualtion class adds sim connection
	 */
    class SimulationMachine : public core::Machine {
    public:

        /**
         * Constructs a machine with existing machine information (Models::Machine)
         * @param aMachine : A machine model
         */
		SimulationMachine(const Models::Machine &aMachine);

        /**
        * Copy constructor
        * @param aMachine : The machine to copy
        */
		SimulationMachine(const SimulationMachine &aMachine);

        /**
        * Assignment operator
        * @param rhs : The machine to copy
        * @return The new machine
        */
		SimulationMachine &operator=(const SimulationMachine &rhs);

		/**
		 * Destruct
		 */
        virtual ~SimulationMachine() = default;

        /**
        * A function to send a message to this machine
        * @param msg : The message to send to this machine
        */
        void sendSimulationMessage(Network::Message &msg);

        /**
        * A function to check if a connection is established with the machine
        * @return True if theres a connection establised with the machine
        */
        bool isSimulationConnected();

        /**
        * A function that sets the connection with this machine
        * @param aConnection : The connection with this machine
        */
        void setSimulationConnection(Network::ConnectionPtr &aConnection);


		/**
		* @param m : Id of given machine
		* @param connection : Connectionpointer to connection.
		* @return  : Pointer of requested machine
		*/
		void sendSimulationConfiguration();


    private:
        Network::ConnectionPtr simConnection;
    };

    typedef std::shared_ptr<SimulationMachine> SimulationMachinePtr;
}


#endif //PRODUCTION_LINE_CONTROL_SIMULATIONMACHINE_H
