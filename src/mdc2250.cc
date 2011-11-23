#include "mdc2250/mdc2250.h"

/***** Inline Functions *****/

inline void defaultExceptionCallback(const std::exception &error) {
  std::cerr << "MDC2250 Unhandled Exception: " << error.what();
  std::cerr << std::endl;
  throw(error);
}

void mdc2250::sleep_ms(int milliseconds) {
  sleepms(milliseconds);
}

using namespace mdc2250;
using namespace configitem;
using namespace commanditem;
using namespace operatingitem;

/***** MDC2250 Class Functions *****/

MDC2250::MDC2250() {
  // Set default callbacks
  this->handle_exc = defaultExceptionCallback;
}

MDC2250::~MDC2250() {
  this->disconnect();
}

void MDC2250::connect(std::string port) {
  this->port = port;
  int status = roboteq_device.Connect(this->port);

  // Check connection result
  switch (status) {
    case RQ_SUCCESS:
      break; // Successful do nothing
    case RQ_ERR_OPEN_PORT:
      handle_exc(ConnectionFailedException(
       "Error occurred while trying to open the communication port."));
      break;
    case RQ_UNRECOGNIZED_DEVICE:
      handle_exc(ConnectionFailedException(
       "The device is not recognized."));
      break;
    case RQ_UNRECOGNIZED_VERSION:
      handle_exc(ConnectionFailedException(
       "Invalid device version."));
      break;
    default:
      handle_exc(UnknownErrorCodeException(status));
      break;
  }
}

void MDC2250::disconnect() {
  roboteq_device.Disconnect();
}

void MDC2250::setConfig(ConfigItem cfg, int value, int index) {
  int status = roboteq_device.SetConfig(cfg, index, value);

  // Check the configuration result
  switch (status) {
    case RQ_SUCCESS:
      break; // Successful do nothing
    case RQ_ERR_NOT_CONNECTED:
      handle_exc(ConfigurationException(cfg,index,value,
       "The device is not connected, you should call the \
Connect function and insure that the device connection succeeded."));
      break;
    case RQ_ERR_TRANSMIT_FAILED:
      handle_exc(ConfigurationException(cfg,index,value,
       "Error occurred while transmitting data to device."));
      break;
    case RQ_ERR_SERIAL_IO:
      handle_exc(ConfigurationException(cfg,index,value,
       "Error occurred to serial communication."));
      break;
    case RQ_ERR_SERIAL_RECEIVE:
      handle_exc(ConfigurationException(cfg,index,value,
       "Error occurred while transmitting data from device."));
      break;
    case RQ_INVALID_RESPONSE:
      handle_exc(ConfigurationException(cfg,index,value,
       "Invalid response to the issued command."));
      break;
    case RQ_INVALID_CONFIG_ITEM:
      handle_exc(ConfigurationException(cfg,index,value,
       "Invalid configuration item, it should be in the range [0, 255]."));
      break;
    case RQ_INDEX_OUT_RANGE:
      handle_exc(ConfigurationException(cfg,index,value,
       "The item index is out of range."));
      break;
    case RQ_SET_CONFIG_FAILED:
      handle_exc(ConfigurationException(cfg,index,value,
       "Failed to set device configuration."));
      break;
    default:
      handle_exc(UnknownErrorCodeException(status));
      break;
  }
}

void MDC2250::getConfig(ConfigItem cfg, int &result, int index) {
  int status = roboteq_device.GetConfig(cfg,index,result);
  
  // Check the configuration result
  switch (status) {
    case RQ_SUCCESS:
      break; // Successful do nothing
    case RQ_ERR_NOT_CONNECTED:
      handle_exc(GetConfigurationException(cfg,index,
        "The device is not connected, you should call the \
Connect function and insure that the device connection succeeded."));
      break;
    case RQ_ERR_TRANSMIT_FAILED:
      handle_exc(GetConfigurationException(cfg,index,
       "Error occurred while transmitting data to device."));
      break;
    case RQ_ERR_SERIAL_IO:
      handle_exc(GetConfigurationException(cfg,index,
       "Error occurred to serial communication."));
      break;
    case RQ_ERR_SERIAL_RECEIVE:
      handle_exc(GetConfigurationException(cfg,index,
       "Error occurred while transmitting data from device."));
      break;
    case RQ_INVALID_RESPONSE:
      handle_exc(GetConfigurationException(cfg,index,
       "Invalid response to the issued command."));
      break;
    case RQ_INVALID_CONFIG_ITEM:
      handle_exc(GetConfigurationException(cfg,index,
       "Invalid configuration item, it should be in the range [0, 255]."));
      break;
    case RQ_INDEX_OUT_RANGE:
      handle_exc(GetConfigurationException(cfg,index,
       "The item index is out of range."));
      break;
    case RQ_SET_CONFIG_FAILED:
      handle_exc(GetConfigurationException(cfg,index,
       "Failed to set device configuration."));
      break;
    default:
      handle_exc(UnknownErrorCodeException(status));
      break;
  }
}

void MDC2250::setCommand(CommandItem cmd, int value, int index) {
  int status = roboteq_device.SetCommand(cmd, index, value);
  
  switch (status) {
    case RQ_SUCCESS:
      break; // Successful do nothing
    case RQ_ERR_NOT_CONNECTED:
      handle_exc(CommandException(cmd,index,value,
        "The device is not connected, you should call the \
Connect function and insure that the device connection succeeded."));
      break;
    case RQ_ERR_TRANSMIT_FAILED:
      handle_exc(CommandException(cmd,index,value,
       "Error occurred while transmitting data to device."));
      break;
    case RQ_ERR_SERIAL_IO:
      handle_exc(CommandException(cmd,index,value,
       "Error occurred to serial communication."));
      break;
    case RQ_ERR_SERIAL_RECEIVE:
      handle_exc(CommandException(cmd,index,value,
       "Error occurred while transmitting data from device."));
      break;
    case RQ_INVALID_RESPONSE:
      handle_exc(CommandException(cmd,index,value,
       "Invalid response to the issued command."));
      break;
    case RQ_INVALID_COMMAND_ITEM:
      handle_exc(CommandException(cmd,index,value,
       "Invalid command item, it should be in the range [0, 255]."));
      break;
    case RQ_INDEX_OUT_RANGE:
      handle_exc(CommandException(cmd,index,value,
       "The item index is out of range."));
      break;
    case RQ_SET_COMMAND_FAILED:
      handle_exc(CommandException(cmd,index,value,
       "Failed to set device command."));
      break;
    default:
      handle_exc(UnknownErrorCodeException(status));
      break;
  }
}

void MDC2250::getValue(OperatingItem op, int &result, int index) {
  int status = roboteq_device.SetCommand(op,index,result);
  
  
}

