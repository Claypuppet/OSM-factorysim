
#ifndef PRODUCTION_LINE_CONTROL_MACHINE_H
#define PRODUCTION_LINE_CONTROL_MACHINE_H

#include <cstdint>

#include <network/Connection.h>
#include <models/Machine.h>
#include <models/MachineStatistics.h>
#include <models/MachineFinalStatistics.h>

#include "Buffer.h"

namespace core {

typedef std::map<uint16_t, BufferPtr> InputBuffersPerMachineMap;
typedef std::map<uint16_t, InputBuffersPerMachineMap> InputBuffersPerConfigMap;
typedef std::map<uint16_t, BufferPtr> OutputBuffersPerConfigMap;

/**
 * Machine contains the connection to the machine control to send instructions.
 */
class Machine : public models::Machine, public std::enable_shared_from_this<Machine> {
 public:

  /**
   * Next action types
   */
  enum NextActionType {
    kNextActionTypeIdle,
    kNextActionTypeReconfigure,
    kNextActionTypeProcessProduct,
    kNextActionTypeProcessProductBeforeReconfigure
  };

  /**
   * Constructs a machine from existing machine information
   * @param aMachine : A machine model
   */
  explicit Machine(const models::Machine &aMachine);

  /**
   * Copy constructor
   * @param aMachine : The machine to copy
   */

  virtual ~Machine() = default;

  /**
   * A function to check if a connection is established with the machine
   * @return True if theres a connection establised with the machine
   */
  virtual bool isConnected() const;

  /**
   * A function that sets the connection with this machine
   * @param aConnection : The connection with this machine
   */
  virtual void setConnection(const network::ConnectionPtr &aConnection);

  /**
   * Sends a message to the machine to start processing a product
   */
  virtual void sendStartProcessMessage();

  /**
   * Send message to machine to (re)configure.
   * @param configureId : configuration id
   */
  virtual void sendConfigureMessage(uint16_t configureId);

  /**
   * Next action will be reconfigure
   * @param configureId : configuration id
   */
  void prepareReconfigure(uint16_t configureId, bool firstTime = false);

  /**
   * Set output buffer for specific configuration id
   * @param productId : id of product
   * @param outputBuffer : buffer for the product
   */
  void setOutputBuffer(uint16_t productId, BufferPtr outputBuffer);

  /**
   * Get the previous machines for this machine, by given config id
   * @param configureId : config id (production line)
   * @return : ids of next machine in production line
   */
  const std::vector<models::PreviousMachinePtr> &getPreviousMachines(uint16_t configureId);

  /**
   * Get the previous machines for this machine for current config
   * @return : ids of next machine in production line
   */
  const std::vector<models::PreviousMachinePtr> &getPreviousMachines();

  /**
   * Create the initial input and output buffers for this machine
   */
  void createInitialBuffers();

  /**
   * Take products from previous buffers
   */
  void takeProductsFromInputBuffers();

  /**
   * Place products in output buffer
   */
  void placeProductsInOutputBuffer();

  /**
   * Executes the next action, based on next action type
   */
  virtual void doNextAction();

  /**
   * Sets the next machine action to idle, so it wont process any more products
   */
  void youreDoneForToday();

  /**
   *
   * Get the amount of processed products by this machine for product id
   * @param productId : id of product
   * @return : amount of products created by this machines
   */
  uint64_t getAmountProcessed(uint16_t productId);

  /**
   * Checks if this machine is last in its production line
   * @param productId : for this product id
   * @return : true if this machine is last
   */
  bool isLastInLine(uint16_t productId);

  /**
   * Creates a machineStatistics object with the statistic variables and adds it to weeklyStatistics
   * also resets the statistic variables
   */
  models::MachineStatisticsPtr getStatistics();

  /**
   * checks if machine is idle, or even COMPLETELY idle...
   * @param completelyIdle : if true, also checks if the input/output buffers are empty
   * @return : true if (completely) idle
   */
  virtual bool isIdle(bool completelyIdle);

  // Getters and setters
  void setStatus(MachineStatus newStatus);
  MachineStatus getStatus();
  virtual bool isWaitingForResponse();
  uint16_t getCurrentConfigId() const;

  // Input buffer getters
  const InputBuffersPerMachineMap &getInputBuffers(uint16_t productId) const;
  const InputBuffersPerMachineMap &getCurrentInputBuffers() const;
  const InputBuffersPerConfigMap &getInputBuffers() const;

  // Output buffer getters
  const BufferPtr &getOutputBuffer(uint16_t productId) const;
  const BufferPtr &getCurrentOutputBuffer() const;
  const OutputBuffersPerConfigMap &getOutputBuffers() const;

  // MachineStatistics getters
  const std::map<uint16_t, std::map<MachineStatus, uint32_t>> &getTimeSpendInState() const;
  uint16_t getTimesBroken() const;

  /**
   * Calculate the MTBF of the machine
   * @return : the MTBF in hours
   */
  uint16_t calculateMTBF();

 protected:
  /**
   * Check if this machine can do an action. must be idle and be able to take products from previous buffers.
   */
  virtual bool canDoActionProcessProduct();

  /**
   * Check if this machine can do the reconfigure action. must be idle or initializing
   */
  virtual bool canDoActionReconfigure();

  /**
  * A function to send a message to this machine
  * @param msg : The message to send to this machine
  */
  virtual void sendMessage(network::Message &message);

  /**
   * handle a machine breaking.
   */
  virtual void handleBreak();

  MachineStatus status;
  bool awaitingResponse;
  network::ConnectionPtr connection;

  std::queue<ProductPtr> productInProcess;

  uint16_t prepareConfigureId;
  uint16_t currentConfigId;
  uint16_t productionConfigId; // Currently produced by application
  NextActionType nextAction;

  //statistics
  uint64_t lastStatusChange;

  /**
   * productId, amount of produced products
   */
  std::map<uint16_t, uint16_t> producedProducts;
  /**
   * ProductId, amount of lost products
   */
  std::map<uint16_t, uint16_t> lostProducts;
  std::map<uint16_t ,std::map<models::Machine::MachineStatus, uint32_t>> timeSpendInState;
  uint16_t timesBroken;

  // Maps with the different buffers a machine can have. the uint16_t is the configuration id (different production line)
  InputBuffersPerConfigMap inputBuffers;
  OutputBuffersPerConfigMap outputBuffers;
  void handleDoneReconfigure();
};

typedef std::shared_ptr<Machine> MachinePtr;

}

#endif //PRODUCTION_LINE_CONTROL_MACHINE_H
