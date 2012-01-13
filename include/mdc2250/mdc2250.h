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
// #include <map>
// #include <string>
// #include <sstream>

// Boost Headers
// #include "boost/function.hpp"
// #include "boost/assign.hpp"

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

private:
  ExceptionCallback handle_exc;

  std::string port;
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
