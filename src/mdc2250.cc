#include "mdc2250/mdc2250.h"

#include <iostream>

/***** Inline Functions *****/

inline void defaultInfoCallback(const std::string &msg) {
  std::cout << "MDC2250 Info: " << msg << std::endl;
}

inline void defaultExceptionCallback(const std::exception &error) {
  std::cerr << "MDC2250 Unhandled Exception: " << error.what();
  std::cerr << std::endl;
  throw(error);
}

using namespace mdc2250;
using namespace serial;

/***** MDC2250 Class Functions *****/

MDC2250::MDC2250() {
  // Set default callbacks
  this->handle_exc = defaultExceptionCallback;
  this->info = defaultInfoCallback;
  cmd_time = 15; // Default to 15 ms
}

MDC2250::~MDC2250() {
  this->disconnect();
}

void MDC2250::connect(std::string port) {
  // Set the port
  this->port_ = port;

  try {
    // Setup and open serial port
    this->serial_port_.setPort(port_);
    this->serial_port_.setBaudrate(115200);
    this->serial_port_.open();

    // Setup filters
    this->setupFilters();

    // Setup and start serial listener
    listener_.startListening(this->serial_port_);
  } catch (std::exception &e) {
    throw(ConnectionFailedException(e.what()));
  }

  // Ping the controller for presence
  if (!this->ping()) {
    // We didn't receive a ping from the device
    throw(ConnectionFailedException("Failed to get a response from ping.",1));
  }

  // Get the device version
  std::string res, fail_why, cmd;
  cmd = "?$1E";
  if (!this->issueQuery(cmd, SerialListener::exactly(cmd), res, fail_why))
    throw(ConnectionFailedException(fail_why));
  // Parse the response
  // TODO: Parse the response
  std::string dev_string = res;

  // Get the control unit type and controller model
  res = "";
  fail_why = "";
  cmd = "?TRN";
  if (!this->issueQuery(cmd, SerialListener::exactly(cmd), res, fail_why))
    throw(ConnectionFailedException(fail_why));
  // Parse the response
  size_t trn = res.find("TRN=");
  size_t colon = res.find(":");
  if (trn == std::string::npos || colon == std::string::npos) {
    std::stringstream ss;
    ss << "Invalid ?TRN query response: " << res;
    throw(ConnectionFailedException(ss.str()));
  }
  // Report device info
  trn += 4;
  std::stringstream ss;
  ss << "Connected to device " << res << " with control unit ";
  ss << res.substr(trn, colon-(trn)) << " and controller model ";
  ss << res.substr(colon-1, res.length()-colon-2);
  this->info(ss.str());
}

void MDC2250::disconnect() {
  
}

bool MDC2250::issueQuery(const std::string &query,
                         serial::ComparatorType comparator,
                         std::string &response, std::string &failure_reason)
{
  // BufferedFilter for response
  BufferedFilterPtr r = this->listener_.createBufferedFilter(comparator);
  // Issue command
  if (!this->_issueCommand(query,failure_reason,"query"))
    return false;
  // If that succeeded, get the response
  response = r->wait(cmd_time);
  if (response == "") {
    // This means we didn't get a response
    std::stringstream error;
    error << "Failed to receive a response for query " << query << ".";
    failure_reason = error.str();
    return false;
  }
  return true;
}

bool MDC2250::issueCommand(const std::string &command,
                           std::string &failure_reason)
{
  if (!this->_issueCommand(command,failure_reason,"command"))
    return false;
  if (ack_filter->wait(cmd_time) == "") {
    // This means we didn't get an ack ('+')
    if (nak_filter->wait(cmd_time) == "") {
      // This means we didn't get a nak either ('-')
      std::stringstream error;
      error << "Command " << command << " received a non-acknowledgement";
      error << " ('-'), which means there was an error with the command";
      error << ".";
      failure_reason = error.str();
      return false;
    }
    std::stringstream error;
    error << "Failed to receive any acknowledgement from the device ";
    error << "for command " << command << ".";
    failure_reason = error.str();
    return false;
  }
  return true;
}

bool MDC2250::ping() {
  this->serial_port_.write("\x05");
  // If the wait command == "", then no response was heard
  return this->ping_filter->wait(cmd_time) != "";
}

bool MDC2250::_issueCommand(const std::string &command,
                            std::string &failure_reason,
                            const std::string &cmd_type)
{
  // BufferedFilter for echo of command
  BufferedFilterPtr e =
    this->listener_.createBufferedFilter(SerialListener::exactly(command));
  // Send the command
  this->serial_port_.write(command+"\r");
  // Wait for the echo of the command
  if (e->wait(cmd_time) == "") {
    // This means we didn't see it
    std::stringstream error;
    error << "Failed to get " << command << " " << cmd_type << " echo.";
    failure_reason = error.str();
    return false;
  }
  return true;
}

void MDC2250::setupFilters() {
  this->ack_filter =
    this->listener_.createBufferedFilter(SerialListener::exactly("+"));
  this->nak_filter =
    this->listener_.createBufferedFilter(SerialListener::exactly("-"));
  this->ping_filter =
    this->listener_.createBufferedFilter(SerialListener::exactly("\x06"));
}

