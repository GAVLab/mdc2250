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
#include <cstdlib>

// Boost headers
#include <boost/algorithm/string.hpp>

namespace mdc2250 {

namespace responses {
  /* 
   * This is an enumeration of the possible types of response from queries.
   * 
   * These are listed in the order that they appear in the manual, starting on 
   * page 99.
   */
  typedef enum {
    motor_amps,
    analog_input,
    battery_amps,
    brushless_motor_speed_rpm,
    brushless_motor_speed_percent,
    encoder_count_absolute,
    brushless_encoder_count_absolute,
    brushless_encoder_count_relative,
    internal_analog,
    internal_pulse,
    internal_serial,
    encoder_count_relative,
    digital_inputs,
    individual_digital_inputs,
    digital_output_status,
    closed_loop_error,
    feedback_in,
    fault_flag,
    firmware_id,
    status_flag,
    lock_status,
    motor_command_applied,
    motor_power_output_applied,
    pulse_input,
    encoder_speed_rpm,
    encoder_speed_relative,
    temperature,
    read_time,
    control_unit_type_and_controller_model,
    volts,
    user_variable,
    unknown
  } ResponseType;
} // responses namespace

using responses;

bool
starts_with(const std::string str, const std::string prefix) {
  return str.substr(0,prefix.length()) == prefix;
}

bool
contains(const std::string str, const std::string substr) {
  return str.find(substr) != std::string::npos;
}

void
split(const std::string str, const std::string &delimeter, 
      std::vector<std::string> &strs)
{
  boost::split(strs, str, delimeter);
}

responses::ResponseType
detect_response_type(const std::string &raw) {
  switch(raw[0]) {
    case 'A':
      if (starts_with(raw, "A=")) return motor_amps;
      if (starts_with(raw, "AI=")) return analog_input;
      break;
    case 'B':
      if (starts_with(raw, "BA=")) return battery_amps;
      if (starts_with(raw, "BS=")) return brushless_motor_speed_rpm;
      if (starts_with(raw, "BSR=")) return brushless_motor_speed_percent;
      break;
    case 'C':
      if (starts_with(raw, "C=")) return encoder_count_absolute;
      if (starts_with(raw, "CB=")) return brushless_encoder_count_absolute;
      if (starts_with(raw, "CBR=")) return brushless_encoder_count_relative;
      if (starts_with(raw, "CIA=")) return internal_analog;
      if (starts_with(raw, "CIP=")) return internal_pulse;
      if (starts_with(raw, "CIS=")) return internal_serial;
      if (starts_with(raw, "CR=")) return encoder_count_relative;
      break;
    case 'D':
      if (starts_with(raw, "D=")) return digital_inputs;
      if (starts_with(raw, "DI=")) return individual_digital_inputs;
      if (starts_with(raw, "DO=")) return digital_output_status;
      break;
    case 'E':
      if (starts_with(raw, "E=")) return closed_loop_error;
      break;
    case 'F':
      if (starts_with(raw, "F=")) return feedback_in;
      if (starts_with(raw, "FF=")) return fault_flag;
      if (starts_with(raw, "FID=")) return firmware_id;
      if (starts_with(raw, "FS=")) return status_flag;
      break;
    case 'L':
      if (starts_with(raw, "LK=")) return lock_status;
      break;
    case 'M':
      if (starts_with(raw, "M=")) return motor_command_applied;
      break;
    case 'P':
      if (starts_with(raw, "P=")) return motor_power_output_applied;
      if (starts_with(raw, "PI=")) return pulse_input;
      break;
    case 'S':
      if (starts_with(raw, "S=")) return encoder_speed_rpm;
      if (starts_with(raw, "SR=")) return encoder_speed_relative;
      break;
    case 'T':
      if (starts_with(raw, "T=")) return temperature;
      if (starts_with(raw, "TM=")) return read_time;
      if (starts_with(raw, "TRN=")) {
        return control_unit_type_and_controller_model;
      }
      break;
    case 'V':
      if (starts_with(raw, "V=")) return volts;
      if (starts_with(raw, "VAR=")) return user_variable;
      break;
    default:
      break;
  }
  return unknown;
}

size_t
decode_two_channel_long(const std::string &raw, long &channel1,
                        long &channel2, responses::ResponseType res)
{
  if (detect_response_type(raw) != res) {
    throw(DecodingException("incorrect response type", raw, res));
  }
  std::vector<std::string> strs;
  boost::split(strs, raw, boost::is_any_of("=:"));
  if (strs.size() < 2 || strs.size() > 3) {
    throw(DecodingException("the format is invalid", raw, res));
  }
  channel1 = atol(strs[1].c_str());
  if (strs.size() == 3) { // There was two channels
    channel2 = atol(strs[2].c_str());
    return 2;
  } else {
    channel2 = 0;
    return 1;
  }
}

void
decode_one_channel_long(const std::string &raw, long &channel1,
                        responses::ResponseType res)
{
  if (detect_response_type(raw) != res) {
    throw(DecodingException("incorrect response type", raw, res));
  }
  std::vector<std::string> strs;
  boost::split(strs, raw, boost::is_any_of("=:"));
  if (strs.size() < 2) {
    throw(DecodingException("the format is invalid", raw, res));
  }
  channel1 = atol(strs[1].c_str());
}

size_t
decode_generic_response(const std::string &raw, std::vector<long> &channels) {
  responses::ResponseType res = detect_response_type(raw);
  if (res == unknown) {
    throw(DecodingException("unknown response type", raw, res));
  }
  std::vector<std::string> strs;
  boost::split(strs, raw, boost::is_any_of("=:"));
  if (strs.size() < 2) {
    throw(DecodingException("the format is invalid", raw, res));
  }
  strs.erase(0); // Erase the stuff before the '='
  std::vector<std::string>::iterator it;
  for (it = strs.begin(); it != strs.end(); ++it) {
    channels.push_back(atol((*it).c_str()));
  }
  return channels.size();
}

/*
 * Decodes a motor amps response.
 * 
 * \params raw string of raw data from the motor controller.
 * \params channel1 value of channel 1
 * \params channel2 value of channel 2
 * 
 * \returns size_t 2 if two channels, 1 if one channel
 */
size_t
decode_motor_amps(const std::string &raw, long &channel1, long &channel2) {
  responses::ResponseType res = motor_amps;
  return decode_two_channel_long(raw, channel1, channel2, res);
}

/*
 * Decodes a analog input response.
 * 
 * \params raw string of raw data from the motor controller.
 * \params channels std::vector<long> of analog input values for each channel
 */
void
decode_analog_input(const std::string &raw, std::vector<long> &channels) {
  responses::ResponseType res = analog_input;
  if (detect_response_type(raw) != res) {
    throw(DecodingException("incorrect response type", raw, res));
  }
  std::vector<std::string> strs;
  boost::split(strs, raw, boost::is_any_of("=:"));
  if (strs.size() < 2) {
    throw(DecodingException("the format is invalid", raw, res));
  }
  strs.erase(0); // Erase the stuff before the '='
  std::vector<std::string>::iterator it;
  for (it = strs.begin(); it != strs.end(); ++it) {
    channels.push_back(atol((*it).c_str()));
  }
}

/*
 * Decodes a battery amps response.
 * 
 * \params raw string of raw data from the motor controller.
 * \params channel1 value of channel 1
 * \params channel2 value of channel 2
 * 
 * \returns size_t 2 if two channels, 1 if one channel
 */
size_t
decode_battery_amps(const std::string &raw, long &channel1, long &channel2) {
  responses::ResponseType res = battery_amps;
  return decode_two_channel_long(raw, channel1, channel2, res);
}

void
decode_brushless_motor_speed_rpm(const std::string &raw, long &channel) {
  responses::ResponseType res = brushless_motor_speed_rpm;
  decode_one_channel_long(raw, channel, res);
}

void
decode_brushless_motor_speed_percent(const std::string &raw, long &channel) {
  responses::ResponseType res = brushless_motor_speed_percent;
  decode_one_channel_long(raw, channel, res);
}

size_t
decode_encoder_count_absolute(const std::string &raw, long &channel1,
                              long &channel2)
{
  responses::ResponseType res = encoder_count_absolute;
  return decode_two_channel_long(raw, channel1, channel2, res);
}

void
decode_brushless_encoder_count_absolute(const std::string &raw, long &channel)
{
  responses::ResponseType res = brushless_encoder_count_absolute;
  decode_one_channel_long(raw, channel, res);
}

void
decode_brushless_encoder_count_relative(const std::string &raw, long &channel)
{
  responses::ResponseType res = brushless_encoder_count_relative;
  decode_one_channel_long(raw, channel, res);
}

void
decode_internal_analog(const std::string &raw) {
  responses::ResponseType res = internal_analog;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_internal_pulse(const std::string &raw) {
  responses::ResponseType res = internal_pulse;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_internal_serial(const std::string &raw) {
  responses::ResponseType res = internal_serial;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_encoder_count_relative(const std::string &raw) {
  responses::ResponseType res = encoder_count_relative;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_digital_inputs(const std::string &raw) {
  responses::ResponseType res = digital_inputs;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_individual_digital_inputs(const std::string &raw) {
  responses::ResponseType res = individual_digital_inputs;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_digital_output_status(const std::string &raw) {
  responses::ResponseType res = digital_output_status;
  throw(DecodingException("not implemented yet", raw, res));
  
}

void
decode_closed_loop_error(const std::string &raw) {
  responses::ResponseType res = closed_loop_error;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_feedback_in(const std::string &raw) {
  responses::ResponseType res = feedback_in;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_fault_flag(const std::string &raw) {
  responses::ResponseType res = fault_flag;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_firmware_id(const std::string &raw) {
  responses::ResponseType res = firmware_id;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_status_flag(const std::string &raw) {
  responses::ResponseType res = status_flag;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_lock_status(const std::string &raw) {
  responses::ResponseType res = lock_status;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_motor_command_applied(const std::string &raw) {
  responses::ResponseType res = motor_command_applied;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_motor_power_output_applied(const std::string &raw) {
  responses::ResponseType res = motor_power_output_applied;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_pulse_input(const std::string &raw) {
  responses::ResponseType res = pulse_input;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_encoder_speed_rpm(const std::string &raw) {
  responses::ResponseType res = encoder_speed_rpm;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_encoder_speed_relative(const std::string &raw) {
  responses::ResponseType res = encoder_speed_relative;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_temperature(const std::string &raw) {
  responses::ResponseType res = temperature;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_read_time(const std::string &raw) {
  responses::ResponseType res = read_time;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_control_unit_type_and_controller_model(const std::string &raw) {
  responses::ResponseType res = control_unit_type_and_controller_model;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_volts(const std::string &raw) {
  responses::ResponseType res = volts;
  throw(DecodingException("not implemented yet", raw, res));
}

void
decode_user_variable(const std::string &raw) {
  responses::ResponseType res = user_variable;
  throw(DecodingException("not implemented yet", raw, res));
}

} // mdc2250 namespace

#endif
