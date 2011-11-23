/*!
 * \file mdc2250/mdc2250_types.h
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
 * This provides data structures for the mdc2250 library.
 * 
 * This library depends on CMake-2.4.6 or later: http://www.cmake.org/
 * 
 */

#ifndef MDC2250_TYPES_H
#define MDC2250_TYPES_H

namespace mdc2250 {

using namespace mdc2250;

/*!
 * Defines the possible Configuration Items.
 * 
 * More information about these configurations can be found
 * in the Controller's User Manual.
 */
namespace configitem {
  typedef enum {
    _CAD = 1,     /*!< Undocumented */
    _OVL = 2,     /*!< Undocumented */
    _UVL = 3,     /*!< Undocumented */
    _THLD = 4,    /*!< Undocumented */
    _MXMD = 5,    /*!< Undocumented */
    _PWMF = 6,    /*!< Undocumented */
    _CPRI = 7,    /*!< Undocumented */
    _RWD = 8,     /*!< RS232 Watchdog (0 to disable) */
    _ECHOF = 9,   /*!< Disable/Enabe RS232 & USB Echo */
    _PMS = 10,    /*!< Enable Pulse Min/Max safety */
    _ACS = 11,    /*!< Enable Ana Center Safety */
    _AMS = 12,    /*!< Enable Ana Min/Max Safety */
    _CLIN = 13,   /*!< Command Linearity */
    _DFC = 14,    /*!< Default Command value */
    _DINA = 15,   /*!< Digital Input Action */
    _DINL = 16,   /*!< Read Digital Inputs */
    _DOA = 17,    /*!< Digital Output Action */
    _DOL = 18,    /*!< Digital Output Action */
    _AMOD = 19,   /*!< Analog Input Mode */
    _AMIN = 20,   /*!< Analog Min */
    _AMAX = 21,   /*!< Analog Max */
    _ACTR = 22,   /*!< Analog Center */
    _ADB = 23,    /*!< Analog Deadband */
    _ALIN = 24,   /*!< Analog Linearity */
    _AINA = 25,   /*!< Analog Input Actions */
    _AMINA = 26,  /*!< Action on Analog Input Min */
    _AMAXA = 27,  /*!< Action on Analog Input Max */
    _APOL = 28,   /*!< Analog Input Polarity */
    _PMOD = 29,   /*!< Pulse Input Mode */
    _PMIN = 30,   /*!< Pulse Min */
    _PMAX = 31,   /*!< Pulse Max */
    _PCTR = 32,   /*!< Pulse Center */
    _PDB = 33,    /*!< Pulse Deadband */
    _PLIN = 34,   /*!< Pulse Linearity */
    _PINA = 35,   /*!< Pulse Input Actions */
    _PMINA = 36,  /*!< Action on Pulse Input Min */
    _PMAXA = 37,  /*!< Action on Pulse Input Max */
    _PPOL = 38,   /*!< Pulse Input Polarity */
    _MMOD = 39,   /*!< Motor Operating Mode */
    _MXPF = 40,   /*!< Motor Max Power */
    _MXPR = 41,   /*!< Motor Max Power */
    _ALIM = 42,   /*!< Motor Amps Limit */
    _ATRIG = 43,  /*!< Amps Trigger Value */
    _ATGA = 44,   /*!< Amps Trigger Action */
    _ATGD = 45,   /*!< Amps Trigger Delay */
    _KP = 46,     /*!< Set PID Proportional Gain */
    _KI = 47,     /*!< Set PID Integral Gain */
    _KD = 48,     /*!< Set PID Differential Gain */
    _PIDM = 49,   /*!< Set PID Options */
    _ICAP = 50,   /*!< Motor(s) Int Cap */
    _MAC = 51,    /*!< Motor(s) Desired Acceleration */
    _MDEC = 52,   /*!< Motor(s) Desired Deceleration */
    _MVEL = 53,   /*!< Motor(s) Default Position Velocity */
    _MXRPM = 54,  /*!< Motor RPM at 100% */
    _MXTRN = 54,  /*!< Number of Motor Turns between Limits */
    _CLERD = 55,  /*!< Close Loop Error Detection */
    _BPOL = 56,   /*!< Number of Poles of BL Motor */
    _BLSTD = 57,  /*!< BL Stall Detection */
    _BLFB = 58,   /*!< Speed and Position sensor feedback */
    _BHOME = 59,  /*!< Brushless Counter Load at Home Position */
    _BLL = 60,    /*!< Encoder Low Limit */
    _BHL = 61,    /*!< Encoder High Limit */
    _BLLA = 62,   /*!< Encoder Low Limit Action */
    _BHLA = 63,   /*!< Encoder High Limit Action */
    _SXC = 64,    /*!< Sepex Curve Points */
    _SXM = 65,    /*!< Minimum Field Current */
    _EMOD = 72,   /*!< Encoder Operating Mode */
    _EPPR = 73,   /*!< Encoder PPR */
    _ELL = 74,    /*!< Encoder Low Limit */
    _EHL = 75,    /*!< Encoder High Limit */
    _ELLA = 76,   /*!< Encoder Low Limit Action */
    _EHLA = 77,   /*!< Encoder High Limit Action */
    _KPC1 = 78,   /*!< KP Curve Points for Motor1 */
    _KPC2 = 79,   /*!< KP Curve Points for Motor2 */
    _KIC1 = 80,   /*!< KI Curve Points for Motor1 */
    _KIC2 = 81,   /*!< KI Curve Points for Motor2 */
    _KDC1 = 82,   /*!< KD Curve Points for Motor1 */
    _KDC2 = 83,   /*!< KD Curve Points for Motor2 */
    _EHOME = 84   /*!< Encoder Counter Load at Home Position */
  } ConfigItem;
}

// Reverse enum map for error reporting
std::map<int, std::string> create_config_names() {
  std::map<int, std::string> m;
  m[1] = "_CAD";
  m[2] = "_OVL";
  m[3] = "_UVL";
  m[4] = "_THLD";
  m[5] = "_MXMD";
  m[6] = "_PWMF";
  m[7] = "_CPRI";
  m[8] = "_RWD";
  m[9] = "_ECHOF";
  m[10] = "_PMS";
  m[11] = "_ACS";
  m[12] = "_AMS";
  m[13] = "_CLIN";
  m[14] = "_DFC";
  m[15] = "_DINA";
  m[16] = "_DINL";
  m[17] = "_DOA";
  m[18] = "_DOL";
  m[19] = "_AMOD";
  m[20] = "_AMIN";
  m[21] = "_AMAX";
  m[22] = "_ACTR";
  m[23] = "_ADB";
  m[24] = "_ALIN";
  m[25] = "_AINA";
  m[26] = "_AMINA";
  m[27] = "_AMAXA";
  m[28] = "_APOL";
  m[29] = "_PMOD";
  m[30] = "_PMIN";
  m[31] = "_PMAX";
  m[32] = "_PCTR";
  m[33] = "_PDB";
  m[34] = "_PLIN";
  m[35] = "_PINA";
  m[36] = "_PMINA";
  m[37] = "_PMAXA";
  m[38] = "_PPOL";
  m[39] = "_MMOD";
  m[40] = "_MXPF";
  m[41] = "_MXPR";
  m[42] = "_ALIM";
  m[43] = "_ATRIG";
  m[44] = "_ATGA";
  m[45] = "_ATGD";
  m[46] = "_KP";
  m[47] = "_KI";
  m[48] = "_KD";
  m[49] = "_PIDM";
  m[50] = "_ICAP";
  m[51] = "_MAC";
  m[52] = "_MDEC";
  m[53] = "_MVEL";
  m[54] = "_MXRPM";
  m[54] = "_MXTRN";
  m[55] = "_CLERD";
  m[56] = "_BPOL";
  m[57] = "_BLSTD";
  m[58] = "_BLFB";
  m[59] = "_BHOME";
  m[60] = "_BLL";
  m[61] = "_BHL";
  m[62] = "_BLLA";
  m[63] = "_BHLA";
  m[64] = "_SXC";
  m[65] = "_SXM";
  m[72] = "_EMOD";
  m[73] = "_EPPR";
  m[74] = "_ELL";
  m[75] = "_EHL";
  m[76] = "_ELLA";
  m[77] = "_EHLA";
  m[78] = "_KPC1";
  m[79] = "_KPC2";
  m[80] = "_KIC1";
  m[81] = "_KIC2";
  m[82] = "_KDC1";
  m[83] = "_KDC2";
  m[84] = "_EHOME";
  return m;
}
std::map<int, std::string> ConfigItemNames = create_config_names();

namespace commanditem {
  /*!
   * Defines the possible Command Items.
   * 
   * More information about these commands can be found
   * in the Controller's User Manual.
   */
  typedef enum {
    _GO = 0,      /*!< Set Motor1 Command */
    _MOTCMD = 1,  /*!< Undocumented */
    _MOTPOS = 2,  /*!< Undocumented */
    _MOTVEL = 3,  /*!< Undocumented */
    _SENCNTR = 4, /*!< Undocumented */
    _SBLCNTR = 5, /*!< Undocumented */
    _VAR = 6,     /*!< Undocumented */
    _ACCEL = 7,   /*!< Set Acceleration */
    _DECEL = 8,   /*!< Set Deceleration */
    _DOUT = 9,    /*!< Set all Digital Out bits */
    _DSET = 10,   /*!< Set Individual Digital Out bits */
    _DRES = 11,   /*!< Reset Individual Digital Out bits */
    _HOME = 13,   /*!< Load Home counter */
    _ESTOP = 14,  /*!< Undocumented */
    _MGO = 15     /*!< Undocumented */
  } CommandItem;
}
// Reverse enum map for error reporting
std::map<int, std::string> create_command_names() {
  std::map<int, std::string> m;
  m[0] = "_GO";
  m[1] = "_MOTCMD";
  m[2] = "_MOTPOS";
  m[3] = "_MOTVEL";
  m[4] = "_SENCNTR";
  m[5] = "_SBLCNTR";
  m[6] = "_VAR";
  m[7] = "_ACCEL";
  m[8] = "_DECEL";
  m[9] = "_DOUT";
  m[10] = "_DSET";
  m[11] = "_DRES";
  m[13] = "_HOME";
  m[14] = "_ESTOP";
  m[15] = "_MGO";
  return m;
}
std::map<int, std::string> CommandItemNames = create_command_names();

namespace operatingitem {
  /*!
   * Defines the possible Operating Items.
   * 
   * More information about these operating items can be found
   * in the Controller's User Manual.
   */
  typedef enum {
    _INVALID = -1,
    _MOTAMPS = 0,   /*!< Motor Amps */
    _MOTCMD = 1,    /*!< Actual Motor Command */
    _MOTPWR = 2,    /*!< Applied Power Level */
    _ABSPEED = 3,   /*!< Encoder Motor Speed in RPM */
    _ABCNTR = 4,    /*!< Absolute Encoder Count */
    _BLCNTR = 5,    /*!< Absolute Brushless Counter */
    _VAR = 6,       /*!< User Variable */
    _RELSPEED = 7,  /*!< Encoder Motor Speed as 1/1000 of Max */
    _RELCNTR = 8,   /*!< Encoder Count Relative */
    _BLRCNTR = 9,   /*!< Brushless Count Relative */
    _BLSPEED = 10,  /*!< BL Motor Speed in RPM */
    _BLRSPEED = 11, /*!< BL Motor Speed as 1/1000 of Max */
    _BATAMPS = 12,  /*!< Battery Amps */
    _VOLTS = 13,    /*!< Internal Voltages */
    _DIGIN = 14,    /*!< All Digital Inputs */
    _DIN = 15,      /*!< Individual Digital Inputs */
    _ANAIN = 16,    /*!< Analog Inputs */
    _PLSIN = 17,    /*!< Pulse Inputs */
    _TEMP = 18,     /*!< Case & Internal Temperatures */
    _FEEDBK = 19,   /*!< Feedback */
    _STFLAG = 20,   /*!< Status Flags */
    _FLTFLAG = 21,  /*!< Fault Flags */
    _DIGOUT = 23,   /*!< Current Digital Outputs */
    _LPERR = 24,    /*!< Closed Loop Error */
    _CMDSER = 25,   /*!< Internal Serial Command */
    _CMDANA = 26,   /*!< Internal Analog Command */
    _CMDPLS = 27,   /*!< Internal Pulse Command */
    _TIME = 28,     /*!< Time */
    _LOCKED = 29    /*!< Lock status */
  } OperatingItem;
}
// Reverse enum map for error reporting
std::map<int, std::string> create_operating_names() {
  std::map<int, std::string> m;
  m[0] = "_MOTAMPS";
  m[1] = "_MOTCMD";
  m[2] = "_MOTPWR";
  m[3] = "_ABSPEED";
  m[4] = "_ABCNTR";
  m[5] = "_BLCNTR";
  m[6] = "_VAR";
  m[7] = "_RELSPEED";
  m[8] = "_RELCNTR";
  m[9] = "_BLRCNTR";
  m[10] = "_BLSPEED";
  m[11] = "_BLRSPEED";
  m[13] = "_BATAMPS";
  m[14] = "_VOLTS";
  m[15] = "_DIGIN";
  m[16] = "_DIN";
  m[17] = "_ANAIN";
  m[18] = "_PLSIN";
  m[19] = "_TEMP";
  m[20] = "_FEEDBK";
  m[21] = "_STFLAG";
  m[22] = "_FLTFLAG";
  m[23] = "_DIGOUT";
  m[24] = "_LPERR";
  m[25] = "_CMDSER";
  m[26] = "_CMDANA";
  m[27] = "_CMDPLS";
  m[28] = "_TIME";
  m[29] = "_LOCKED";
  return m;
}
std::map<int, std::string> OperatingItemNames = create_operating_names();

}

#endif