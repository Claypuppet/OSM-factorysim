
#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H

#include <cstdint>

#include <network/Connection.h>
#include <models/Machine.h>

#include "Buffer.h"

namespace core {

typedef std::map<uint16_t, BufferList> InputBuffersMap;
typedef std::map<uint16_t, BufferPtr> OutputBuffersMap;

/**
 * Machine contains the connection to the machine control to send instructions.
 */
class Machine : public models::Machine, public std::enable_shared_from_this<Machine> {
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
  void setConnection(const network::ConnectionPtr &aConnection);

  /**
   * Sends a message to the machine to start processing a product
   */
  void sendStartProcessMessage();

  /**
   * Send message to machine to (re)configure.
   * @param configureId : configuration id
   */
  void sendConfigureMessage(uint32_t configureId);

  // Input buffer getters
  const BufferList &getInputBuffers(uint16_t productId) const;
  const BufferList &getCurrentInputBuffers() const;
  const InputBuffersMap &getInputBuffers() const;

  // Output buffer getters
  const BufferPtr &getOutputBuffer(uint16_t productId) const;
  const BufferPtr &getCurrentOutputBuffer() const;
  const OutputBuffersMap &getOutputBuffers() const;

  /**
   * Set output buffer for specific configuration id
   * @param productId : id of product
   * @param outputBuffer : buffer for the product
   */
  void addInputBuffer(uint16_t productId, BufferPtr outputBuffer);

  /**
   * Use a specific input buffer, should be called after (re)configuring.
   * @param productId : id of configuration
   */
  void setCurrentConfig(uint16_t configureId);

  /**
   * Get the previous machines for this machine, by given config id
   * @param configureId : config id (production line)
   * @return : ids of next machine in production line
   */
  const std::vector<models::PreviousMachine> &getPreviousMachines(uint16_t configureId);

  /**
   * Get the previous machines for this machine for current config
   * @return : ids of next machine in production line
   */
  const std::vector<models::PreviousMachine> &getPreviousMachines();

  /**
   * Create the initial input and output buffers for this machine
   */
  void createInitialBuffers();

  /**
   * Check if this machine can do an action. must be idle and be able to take products from previous buffers.
   * @param configureId : can make product for given config id
   */
  virtual bool canDoAction();

  void setStatus(MachineStatus newStatus);
  MachineStatus getStatus();

 private:

  /**
  * A function to send a message to this machine
  * @param msg : The message to send to this machine
  */
  void sendMessage(network::Message &message);

  /**
   * Take products from previous buffers
   */
  void takeProductsFromBuffers();

  /**
   * Place products in output buffer
   */
  void placeProductsInBuffer();

  MachineStatus status;
  bool awaitingResponse;
  network::ConnectionPtr connection;
  ProductPtr processedProduct;

  uint16_t currentConfigId;
  // Maps with the different buffers a machine can have. the uint16_t is the configuration id (different production line)
  std::map<uint16_t, std::vector<BufferPtr>> inputBuffers;
  std::map<uint16_t, BufferPtr> outputBuffers;
};

typedef std::shared_ptr<Machine> MachinePtr;

}

#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
