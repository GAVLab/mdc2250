/*!
 * \file mdc2250/fault_flags.h
 * \author Chris Collins <chris.collins@is4s.com>
 * \version 0.1
 *
 * \section LICENSE
 *
 * The BSD License
 *
 * Copyright (c) 2011 Chris Collins
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

#ifndef MDC2250_FAULT_FLAGS_H
#define MDC2250_FAULT_FLAGS_H

// Standard Library Headers
#include <string>
#include <cstdlib>

// Boost headers
#include <boost/algorithm/string.hpp>

namespace mdc2250 {

/* 
 * This is an enumeration of the possible types of response from fault flags query.
 * 
 * These are listed in page 249 of the manual.
 */
namespace fault_flags {
  typedef enum {
    OverHeat              = 0b00000001,
    OverVoltage           = 0b00000010,
    UnderVoltage          = 0b00000100,
    ShortCircuit          = 0b00001000,
    EmergencyStop         = 0b00010000,
    BrushlessSensorFault  = 0b00100000,
    MosfetFailure         = 0b01000000
  } FaultFlag;
}
/*!
 * Returns the corresponding std::string given a FaultFlag type.
 */
std::string
fault_flag_to_string(fault_flags::FaultFlag flag) 
{
  switch (flag) 
  {
    case fault_flags::OverHeat: return "Over heat";
    case fault_flags::OverVoltage: return "Over voltage";
    case fault_flags::UnderVoltage: return "Under voltage";
    case fault_flags::ShortCircuit: return "Short circuit";
    case fault_flags::EmergencyStop: return "Emergency stop";
    case fault_flags::BrushlessSensorFault: return "Brushless sensor fault";
    case fault_flags::MosfetFailure: return "Mosfet failure";
    default: break;
  }
  return "";
}

} // mdc2250 namespace

#endif