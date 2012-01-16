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
 * This provides an interface for the Roboteq MDC2250 Motor Controller.
 * 
 * This library depends on CMake-2.4.6 or later: http://www.cmake.org/
 * This library depends on Serial: https://github.com/wjwwood/serial
 * 
 */

#ifndef MDC2250_H
#define MDC2250_H

// Standard Library Headers
#include <string>
#include <sstream>

// Boost Headers
#include "boost/function.hpp"

// Serial Headers
#include "serial/serial.h"
#include "serial/serial_listener.h"

namespace mdc2250 {

/*!
 * This function type describes the prototype for the logging callbacks.
 * 
 * The function takes a std::string reference and returns nothing.  It is 
 * called from the library when a logging message occurs.  This 
 * allows the library user to hook into this and integrate it with their own 
 * logging system.  It can be set with any of the set<log level>Handler 
 * functions.
 * 
 * \see SerialListener::setInfoHandler, SerialListener::setDebugHandler, 
 * SerialListener::setWarningHandler
 */
typedef boost::function<void(const std::string&)> LoggingCallback;

/*!
 * This function type describes the prototype for the exception callback.
 * 
 * The function takes a std::exception reference and returns nothing.  It is 
 * called from the library when an exception occurs in a library thread.
 * This exposes these exceptions to the user so they can to error handling.
 * 
 * \see SerialListener::setExceptionHandler
 */
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
   * Takes a std::string query, a Comparator to match the response, a 
   * std::string response for storing the response, a std::string for storing 
   * the reason of a failure, and returns true for success and false for a 
   * failure.
   * 
   * \param query string to send to the mdc2250 (no return carriage needed)
   * \param comparator a comparator function for matching the command 
   * response.
   * \param response response from the device, matched by the comparator.
   * \param failure_reason the reason for a failure, empty if there was no 
   * failure.
   * 
   * \return bool true for success, false for failure.
   */
  bool issueQuery(const std::string &query,
                  serial::ComparatorType comparator, std::string &response,
                  std::string &failure_reason);

  /*!
   * Takes a std::string command, a std::string for storing the reason of a 
   * failure, and returns true for success and false for a failure.
   * 
   * \param query string to send to the mdc2250 (no return carriage needed)
   * \param failure_reason the reason for a failure, empty if there was no 
   * failure.
   * 
   * \return bool true for success, false for failure.
   */
  bool issueCommand(const std::string &command, std::string &failure_reason);

  /*!
   * Sends an ASCII QRY to the controller to check for its presence.
   * 
   * \return bool true for success, false for failure.
   */
  bool ping();

  /*!
   * Sets the function to be called when an info logging message occurs.
   * 
   * This allows you to hook into the message reporting of the library and use
   * your own logging facilities.
   * 
   * The provided function must follow this prototype:
   * <pre>
   *    void yourInfoCallback(const std::string &msg)
   * </pre>
   * Here is an example:
   * <pre>
   *    void yourInfoCallback(const std::string &msg) {
   *        std::cout << "MDC2250 Info: " << msg << std::endl;
   *    }
   * </pre>
   * And the resulting call to make it the callback:
   * <pre>
   *    Object my_object;
   *    my_object.setInfoCallback(yourInfoCallback);
   * </pre>
   * Alternatively you can use a class method as a callback using boost::bind:
   * <pre>
   *    #include <boost/bind.hpp>
   *    
   *    #include "object.h"
   *    
   *    class MyClass
   *    {
   *    public:
   *     MyClass () {
   *      my_object.setInfoHandler(
   *          boost::bind(&MyClass::handleInfo, this, _1));
   *     }
   *    
   *     void handleInfo(const std::string &msg) {
   *       std::cout << "MyClass Info: " << msg << std::endl;
   *     }
   *    
   *    private:
   *     Object object;
   *    };
   * </pre>
   * 
   * \param info_handler A function pointer to the callback to handle new 
   * Info messages.
   * 
   * \see serial::LoggingCallback
   */
  void setInfoHandler(LoggingCallback info_handler) {
    this->info = info_handler;
  }

  /*!
   * Sets the function to be called when an exception occurs internally.
   * 
   * This allows you to hook into the exceptions that occur in threads inside
   * the library.
   * 
   * \param exception_handler A function pointer to the callback to handle new 
   * interal exceptions.
   * 
   * \see mdc2250::ExceptionCallback, MDC2250::setInfoHandler
   */
  void
  setExceptionHandler (ExceptionCallback exception_handler) {
    this->handle_exc = exception_handler;
  }

private:
  // Implementation of _issueCommand, used by issueQuery too
  bool _issueCommand(const std::string &command, std::string &failure_reason,
    const std::string &cmd_type);
  // Function to setup commonly used, persistent filters
  void setupFilters();

  // Time to wait for responses from the device
  size_t cmd_time;

  // Exception callback handle
  ExceptionCallback handle_exc;
  LoggingCallback info;

  // Serial port name
  std::string port_;

  // Serial port and listener
  serial::Serial         serial_port_;
  serial::SerialListener listener_;

  // Fitlers
  serial::BufferedFilterPtr ack_filter;
  serial::BufferedFilterPtr nak_filter;
  serial::BufferedFilterPtr ping_filter;
};

/*!
 * Exception called when a connection to the mdc2250 fails for some reason.
 */
class ConnectionFailedException : public std::exception {
  const std::string e_what_;
  int error_type_;
public:
  ConnectionFailedException(const std::string &e_what, int error_type = 0)
  : e_what_(e_what), error_type_(error_type) {}
  ~ConnectionFailedException() throw() {}

  int error_type() {return error_type_;}

  virtual const char * what() const throw() {
    std::stringstream ss;
    ss << "Connecting to the MDC2250: " << this->e_what_;
    return ss.str().c_str();
  }
};

}

#endif
