
#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H

#include <cstdint>

#include <network/Connection.h>
#include <models/Machine.h>

#include "Buffer.h"

namespace core {
enum MachineStatus {
  kMachineStatusReady
};

class Machine : public models::Machine {
 public:

  /**
   * Constructs a machine from existing machine information
   * @param aMachine : A machine model
   */
  explicit Machine(const models::Machine &aMachine);

  /**
  * Copy constructor
  * @param aMachine : The machine to copy
  */
  Machine(const Machine &aMachine);

  /**
  * Assignment operator
  * @param rhs : The machine to copy
  * @return The new machine
  */
  Machine &operator=(const Machine &rhs);

  virtual ~Machine() = default;

  /**
  * A function to check if a connection is established with the machine
  * @return True if theres a connection establised with the machine
  */
  bool isConnected() const;

  /**
  * A function that sets the connection with this machine
  * @param aConnection : The connection with this machine
  */
  void setConnection(const Network::ConnectionPtr &aConnection);

  /**
   * Sends a message to the machine to start processing a product
   */
  void sendStartProcessMessage();

  /**
   * Send message to machine to (re)configure.
   * @param configureId : configuration id
   */
  void sendConfigureMessage(uint32_t configureId);


  // Buffer getters
  const BufferPtr &getCurrentInputBuffer() const;
  const BufferPtr &getCurrentOutputBuffer() const;
  const std::map<uint16_t, BufferPtr> &getInputBuffers() const;
  const std::map<uint16_t, BufferPtr> &getOutputBuffers() const;

  void setInputBuffers(const std::map<uint16_t, BufferPtr> &inputBuffers);


 private:

  /**
  * A function to send a message to this machine
  * @param msg : The message to send to this machine
  */
  void sendMessage(const Network::Message &message);

  /**
   * Create the output buffers for this machine
   */
  void createBuffers();

  MachineStatus status;
  Network::ConnectionPtr connection;

  BufferPtr currentInputBuffer;
  BufferPtr currentOutputBuffer;

  // Maps with the different buffers a machine can have. the uint16_t is the product id (different production line)
  std::map<uint16_t, BufferPtr> inputBuffers;
  std::map<uint16_t, BufferPtr> outputBuffers;
};

typedef std::shared_ptr<Machine> MachinePtr;

}

#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
