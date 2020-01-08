/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_KITTEN_SYRINGE_
#define _VARIANT_KITTEN_SYRINGE_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK	(F_CPU)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT           (26u)
#define NUM_DIGITAL_PINS     (16u)
#define NUM_ANALOG_INPUTS    (10u)
#define NUM_ANALOG_OUTPUTS   (1u)
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? PIN_A0 + (p) : -1)

#define digitalPinToPort(P)        ( &(PORT->Group[g_APinDescription[P].ulPort]) )
#define digitalPinToBitMask(P)     ( 1 << g_APinDescription[P].ulPin )
//#define analogInPinToBit(P)        ( )
#define portOutputRegister(port)   ( &(port->OUT.reg) )
#define portInputRegister(port)    ( &(port->IN.reg) )
#define portModeRegister(port)     ( &(port->DIR.reg) )
#define digitalPinHasPWM(P)        ( g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER )

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)


// Pin not defined
#define NOT_CONNECTED_PIN   (39u)

// LEDs
#define PIN_LED_13           (14u)
#define PIN_LED              PIN_LED_13
#define LED_BUILTIN          PIN_LED_13


/*
 * Digital pins
 */
static const uint8_t D0   = 0;
static const uint8_t D1   = 1;
static const uint8_t D2   = 2;
static const uint8_t D3   = 3;
static const uint8_t D4   = 4;
static const uint8_t D5   = 5;
static const uint8_t D6   = 6;
static const uint8_t D7   = 7;
static const uint8_t D8   = 8;
static const uint8_t D9   = 9;
static const uint8_t D10  = 10;
static const uint8_t D11  = 11;
static const uint8_t D12  = 12;
static const uint8_t D13  = 13;
static const uint8_t D14  = 14; // LED_BUILTIN
static const uint8_t D15  = 15; // NC, NOT CONNECTED PIN
static const uint8_t D36  = 36; // PA00 (XIN32)
static const uint8_t D37  = 37; // PA01 (XOUT32)


/*
 * Analog pins
 */
#define PIN_A0               (16ul)
#define PIN_A1               (PIN_A0 + 1)
#define PIN_A2               (PIN_A0 + 2)
#define PIN_A3               (PIN_A0 + 3)
#define PIN_A4               (PIN_A0 + 4)   
#define PIN_A5               (PIN_A0 + 5)   
#define PIN_A6               (PIN_A0 + 6)
#define PIN_A7               (PIN_A0 + 7)
#define PIN_A8               (PIN_A0 + 8)
#define PIN_A9               (PIN_A0 + 9)

#define PIN_DAC0             PIN_A8

static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;
static const uint8_t A4  = PIN_A4;
static const uint8_t A5  = PIN_A5;
static const uint8_t A6  = PIN_A6;
static const uint8_t A7  = PIN_A7;
static const uint8_t A8  = PIN_A8;
static const uint8_t A9  = PIN_A9;
static const uint8_t SOK = PIN_A9; // SOK SELECTOR / AREF

static const uint8_t DAC0 = PIN_DAC0;

#define ADC_RESOLUTION		12

// Other pins
#define PIN_ATN             NOT_CONNECTED_PIN   // -- unsed, arduino zero default is on 38ul, PA13
static const uint8_t ATN =  PIN_ATN;


/*
 * Serial interfaces
 */

// Serial1 (D0/D1) - SERCOM0
#define PIN_SERIAL1_TX      (0ul)
#define PIN_SERIAL1_RX      (1ul)
#define PAD_SERIAL1_TX      (UART_TX_PAD_0)
#define PAD_SERIAL1_RX      (SERCOM_RX_PAD_1)

// SerialSOK (Alternate use of SERCOM3-I2C, TX-SDA, RX-SCL)
#define PIN_SERIALSOK_TX    (26ul)
#define PIN_SERIALSOK_RX    (27ul)
#define PAD_SERIALSOK_TX    (UART_TX_PAD_0)
#define PAD_SERIALSOK_RX    (SERCOM_RX_PAD_1)


/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

// Primary SPI pins (SPI) - SERCOM1
#define PIN_SPI_MOSI         (28u)
#define PIN_SPI_SCK          (29u)
#define PIN_SPI_MISO         (30u)
#define PIN_SPI_SS           (3u)       // D3
#define PERIPH_SPI           sercom1
#define PAD_SPI_TX           SPI_PAD_3_SCK_1
#define PAD_SPI_RX           SERCOM_RX_PAD_2

static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t SCK  = PIN_SPI_SCK  ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SS   = PIN_SPI_SS   ;  

// Secondary SPI pins (SPI1) - SERCOM2
#define PIN_SPI1_MOSI        (31u)
#define PIN_SPI1_SCK         (32u)
#define PIN_SPI1_MISO        (33u)
#define PIN_SPI1_SS          NOT_CONNECTED_PIN // NC, UNDEFINED
#define PERIPH_SPI1          sercom2
#define PAD_SPI1_TX          SPI_PAD_3_SCK_1
#define PAD_SPI1_RX          SERCOM_RX_PAD_2

static const uint8_t MOSI1 = PIN_SPI1_MOSI ;
static const uint8_t SCK1  = PIN_SPI1_SCK  ;
static const uint8_t MISO1 = PIN_SPI1_MISO ;
static const uint8_t SS1   = PIN_SPI1_SS   ;  // HW SS isn't used. Set here only for reference.


// Needed for SD library, taken from MKRZero variant.h file
#if defined(USE_PRIMARY_SPI) // Primary SPI as SDCARD  (default)
  #define SDCARD_SPI      SPI
  #define SDCARD_MOSI_PIN PIN_SPI_MOSI
  #define SDCARD_SCK_PIN  PIN_SPI_SCK
  #define SDCARD_MISO_PIN PIN_SPI_MISO
  #define SDCARD_SS_PIN   PIN_SPI_SS  
#else // Secondary SPI1 as SDCARD  
  #define SDCARD_SPI      SPI1
  #define SDCARD_MOSI_PIN PIN_SPI1_MOSI
  #define SDCARD_SCK_PIN  PIN_SPI1_SCK
  #define SDCARD_MISO_PIN PIN_SPI1_MISO
  #define SDCARD_SS_PIN   PIN_SPI1_SS 
#endif


/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

// Primary I2C pins (I2C) - SERCOM3
#define PIN_WIRE_SDA         (26u)
#define PIN_WIRE_SCL         (27u)
#define PERIPH_WIRE          sercom3
#define WIRE_IT_HANDLER      SERCOM3_Handler 

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;


/*
 * USB
 */
#define PIN_USB_HOST_ENABLE   NOT_CONNECTED_PIN
#define PIN_USB_DM            (34ul)
#define PIN_USB_DP            (35ul)


/*
 * I2S Interfaces
 */
#define I2S_INTERFACES_COUNT 1

#define I2S_DEVICE          0
#define I2S_CLOCK_GENERATOR 3
#define PIN_I2S_SD          (3u)  // D3
#define PIN_I2S_SCK         (4u)  // D4
#define PIN_I2S_FS          (5u)  // D5 

#ifdef __cplusplus
}
#endif


/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
*/
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;

extern Uart Serial1;
extern Uart SerialSOK;

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      Serial
#define SERIAL_PORT_MONITOR         Serial
// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   SerialSOK

#endif /* _VARIANT_KITTEN_SYRINGE_ */

