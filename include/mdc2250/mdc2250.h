/*!
 * \file mdc2250/mdc2250.h
 * \author William Woodall <wjwwood@gmail.com>
 * \version 0.1
 *
 * \section LICENSE
 *
 * The BSD License
 *
 * Copyright (c) 2011 William Woodall
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 * \section DESCRIPTION
 *
 * This provides a cross platform interface for the Roboteq MDC2250 Motor 
 * Controller.
 * 
 * This library depends on CMake-2.4.6 or later: http://www.cmake.org/
 * 
 */

#ifndef MDC2250_H
#define MDC2250_H

// Standard Library Headers
#include <map>
#include <string>
#include <sstream>

// Boost Headers (system or from vender/*)
#include "boost/function.hpp"

// Roboteq API Headers
#include "roboteq_api/ErrorCodes.h"
#include "roboteq_api/RoboteqDevice.h"

// Library Headers
#include "mdc2250_types.h"

namespace mdc2250 {

/***** Function Typedefs *****/
typedef boost::function<void(const std::exception&)> ExceptionCallback;

/*!
 * Represents an MDC2250 Device and provides and interface to it.
 */
class MDC2250 {
public:
  /*!
   * Constructs the MDC2250 object.
   */
  MDC2250();
  virtual ~MDC2250();

  /*!
   * Connects to the MDC2250 motor controller given a serial port.
   * 
   * \param port Defines which serial port to connect to in serial mode.
   * Examples: Linux - "/dev/ttyS0" Windows - "COM1"
   * 
   * \throws ConnectionFailedException connection attempt failed.
   * \throws UnknownErrorCodeException unknown error code returned.
   */
  void connect(std::string port);

  /*!
   * Disconnects from the MDC2250 motor controller given a serial port.
   */
  void disconnect();

  /*!
   * Sets a configuration on the MDC2250 device.
   * 
   * \param cfg The configuration item that needs to be changed.
   * \param value The new config item value.
   * \param index Used to select one of the configuration item in
   * multi-channel configurations. When accessing a configuration
   * parameter that is not part of an array, the index value 1
   * must be used. Details on the various configurations items,
   * their effects and acceptable values can be found in the
   * Controller's User Manual. If the index is omitted, it is
   * supposed to be 0.
   * 
   * \throws ConfigurationException configuration change attempt failed.
   * \throws UnknownErrorCodeException unknown error code returned.
   */
  void setConfig(configitem::ConfigItem cfg, int value, int index = 0);

  /*!
   * Gets a configuration on the MDC2250 device.
   * 
   * \param cfg The configuration item that is being requested.
   * \param value The config item value.
   * \param index Used to select one of the configuration item in
   * multi-channel configurations. When accessing a configuration
   * parameter that is not part of an array, the index value 1
   * must be used. Details on the various configurations items,
   * their effects and acceptable values can be found in the
   * Controller's User Manual. If the index is omitted, it is
   * supposed to be 0.
   * 
   * \throws ConfigurationException configuration change attempt failed.
   * \throws UnknownErrorCodeException unknown error code returned.
   */
  void getConfig(configitem::ConfigItem cfg, int &result, int index = 0);

  /*!
   * Sets a command on the MDC2250 device.
   * 
   * \param cmd The command item that needs to be set.
   * \param value The new command item value.
   * \param index Used to select one of the command channel in multichannel
   * commands. Details on the various commands, their effects and acceptable
   * ranges can be found in the Controller's User Manual. If the index is
   * omitted, it is supposed to be 0.
   * 
   * \throws CommandException configuration change attempt failed.
   * \throws UnknownErrorCodeException unknown error code returned.
   */
  void setCommand(commanditem::CommandItem cmd, int value, int index = 0);

  /*!
   * Gets an operating item from the MDC2250 device.
   * 
   * \param cfg The operating item that is being requested.
   * \param value The operating item value.
   * \param index Used to select one of the operating item in multi-­‐channel 
   * configurations. When accessing operating parameter that is not part of an 
   * array, the index value 1 must be used. Details on the various operating 
   * items, can be found in the Controller's User Manual. If the index is 
   * omitted, it is supposed to be 0.
   * 
   * \throws GetValueException configuration change attempt failed.
   * \throws UnknownErrorCodeException unknown error code returned.
   */
  void getValue(operatingitem::OperatingItem cfg, int &result, int index = 0);

private:
  ExceptionCallback handle_exc;
  
  RoboteqDevice roboteq_device;
  std::string port;
};

class GetValueException : public std::exception {
  const operatingitem::OperatingItem op;
  const int index;
  const char * e_what;
public:
  GetValueException(const operatingitem::OperatingItem op, const int index,
                    const char * e_what)
                    : op(op), index(index) {
    this->e_what = e_what;
  }

  virtual const char* what() const throw() {
    std::stringstream ss;
    ss << "Error getting value " << OperatingItemNames[this->op];
    ss << " at index " << this->index;
    ss << " from the MDC2250: " << this->e_what;
    return ss.str().c_str();
  }
};

class CommandException : public std::exception {
  const commanditem::CommandItem cmd;
  const int index, value;
  const char * e_what;
public:
  CommandException(const commanditem::CommandItem cmd, const int index,
                   const int value, const char * e_what) 
                   : cmd(cmd), index(index), value(value) {
    this->e_what = e_what;
  }

  virtual const char* what() const throw() {
    std::stringstream ss;
    ss << "Error setting command " << CommandItemNames[this->cmd];
    ss << " at index " << this->index << " to " << this->value;
    ss << " on the MDC2250: " << this->e_what;
    return ss.str().c_str();
  }
};

class GetConfigurationException : public std::exception {
  const configitem::ConfigItem cfg;
  const int index;
  const char * e_what;
public:
  GetConfigurationException(const configitem::ConfigItem cfg, const int index,
                            const char * e_what)
                            : cfg(cfg), index(index) {
    this->e_what = e_what;
  }

  virtual const char* what() const throw() {
    std::stringstream ss;
    ss << "Error getting " << ConfigItemNames[this->cfg];
    ss << " at index " << this->index;
    ss << " from the MDC2250: " << this->e_what;
    return ss.str().c_str();
  }
};

class ConfigurationException : public std::exception {
  const configitem::ConfigItem cfg;
  const int index, value;
  const char * e_what;
public:
  ConfigurationException(const configitem::ConfigItem cfg, const int index,
                         const int value, const char * e_what)
                         : cfg(cfg), index(index), value(value) {
    this->e_what = e_what;
  }

  virtual const char* what() const throw() {
    std::stringstream ss;
    ss << "Error setting " << ConfigItemNames[this->cfg];
    ss << " at index " << this->index << " to " << this->value;
    ss << " on the MDC2250: " << this->e_what;
    return ss.str().c_str();
  }
};

class UnknownErrorCodeException : public std::exception {
  const int status;
public:
  UnknownErrorCodeException(const int status) : status(status) {}

  virtual const char* what() const throw() {
    std::stringstream ss;
    ss << "Unknown error code from the MDC2250: " << this->status;
    return ss.str().c_str();
  }
};

class ConnectionFailedException : public std::exception {
  const char * e_what;
public:
  ConnectionFailedException(const char * e_what) {this->e_what = e_what;}

  virtual const char* what() const throw() {
    std::stringstream ss;
    ss << "Error connecting to the MDC2250: " << this->e_what;
    return ss.str().c_str();
  }
};

}

#endif
