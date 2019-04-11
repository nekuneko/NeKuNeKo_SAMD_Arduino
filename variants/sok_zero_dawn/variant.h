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

#ifndef _VARIANT_SOK_ZERO_DAWN_
#define _VARIANT_SOK_ZERO_DAWN_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK			  (48000000ul)

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
#define PINS_COUNT           (44u)
#define NUM_DIGITAL_PINS     (24u)
#define NUM_ANALOG_INPUTS    (20u)
#define NUM_ANALOG_OUTPUTS   (1u)
#define analogInputToDigitalPin(p)  ((p < 20u) ? (p) + 25u : -1) 

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

// BLE control pins
#define BLE_RESET    (15u)
#define BLE_ENABLE   (16u)
#define BLE_CONFIG   (17u)
#define BLE_MSTR_SLV (18u)
#define BLE_STATE    (19u)
#define BLE_CONFIG   (20u)

#define PIN_NOT_CONNECTED (24u)
// LEDs
#define PIN_LED_13           (14u)
#define PIN_LED_RXL          PIN_NOT_CONNECTED // -- unused
#define PIN_LED_TXL          PIN_NOT_CONNECTED // -- unused
#define PIN_LED              PIN_LED_13
#define PIN_LED2             PIN_LED_RXL
#define PIN_LED3             PIN_LED_TXL
#define LED_BUILTIN          PIN_LED_13

/*
 * Analog pins
 */
#define PIN_A0               (25ul)
#define PIN_A1               (PIN_A0 + 1)
#define PIN_A2               (PIN_A0 + 2)
#define PIN_A3               (PIN_A0 + 3)
#define PIN_A4               (PIN_A0 + 4)   
#define PIN_A5               (PIN_A0 + 5)   
#define PIN_A6               (PIN_A0 + 6)
#define PIN_A7               (PIN_A0 + 7)
#define PIN_A8               (PIN_A0 + 8)
#define PIN_A9               (PIN_A0 + 9)
#define PIN_A10              (PIN_A0 + 10)
#define PIN_A11              (PIN_A0 + 11)
#define PIN_A12              (PIN_A0 + 12)
#define PIN_A13              (PIN_A0 + 13)
#define PIN_A14              (PIN_A0 + 14)
#define PIN_A15              (PIN_A0 + 15)
#define PIN_A16              (PIN_A0 + 16)
#define PIN_A17              (PIN_A0 + 17)
#define PIN_A18              (PIN_A0 + 18)
#define PIN_A19              (PIN_A0 + 19)
#define PIN_DAC0             (60u)

static const uint8_t A0   = PIN_A0;
static const uint8_t A1   = PIN_A1;
static const uint8_t A2   = PIN_A2;
static const uint8_t A3   = PIN_A3;
static const uint8_t A4   = PIN_A4;
static const uint8_t A5   = PIN_A5;
static const uint8_t A6   = PIN_A6;
static const uint8_t A7   = PIN_A7;
static const uint8_t A8   = PIN_A8;
static const uint8_t A9   = PIN_A9;
static const uint8_t A10  = PIN_A10;
static const uint8_t A11  = PIN_A11;
static const uint8_t A12  = PIN_A12;
static const uint8_t A13  = PIN_A13;
static const uint8_t A14  = PIN_A14;
static const uint8_t A15  = PIN_A15;
static const uint8_t A16  = PIN_A16;
static const uint8_t A17  = PIN_A17;
static const uint8_t A18  = PIN_A18;
static const uint8_t A19  = PIN_A19;
static const uint8_t SOK  = PIN_A19; // SOK SELECTOR / AREF

static const uint8_t DAC0 = PIN_DAC0;

#define ADC_RESOLUTION		12

// Other pins
#define PIN_ATN             PIN_NOT_CONNECTED   // -- unsed, arduino zero default is on 38ul, PA13
static const uint8_t ATN =  PIN_ATN;

#define PIN_USB_HOST_ENABLE PIN_NOT_CONNECTED   // -- unused

/*
 * Serial interfaces
 */
// Serial1 (D0/D1)
#define PIN_SERIAL1_TX       (0ul)
#define PIN_SERIAL1_RX       (1ul)
#define PAD_SERIAL1_TX       (UART_TX_PAD_0)
#define PAD_SERIAL1_RX       (SERCOM_RX_PAD_1)

// SerialBLE (BLE_HJ580XP)
#define PIN_SERIAL_BLE_TX    (45ul)
#define PIN_SERIAL_BLE_RX    (46ul)
#define PAD_SERIAL_BLE_TX    (UART_TX_PAD_2)
#define PAD_SERIAL_BLE_RX    (SERCOM_RX_PAD_3)

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 2

// Primary SPI pins (SPI, EXTERNAL)
#define PIN_SPI_MOSI         (49u)
#define PIN_SPI_SCK          (50u)
#define PIN_SPI_MISO         (51u)
#define PIN_SPI_SS           PIN_NOT_CONNECTED // NC, UNDEFINED
#define PERIPH_SPI           sercom1
#define PAD_SPI_TX           SPI_PAD_2_SCK_3
#define PAD_SPI_RX           SERCOM_RX_PAD_0

static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t SCK  = PIN_SPI_SCK  ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SS   = PIN_SPI_SS   ;  // HW SS isn't used. Set here only for reference.


// Secondary SPI pins (SPI1, INTERNAL): Connected to microSD reader
#define PIN_SPI1_MOSI        (52u)
#define PIN_SPI1_SCK         (53u)
#define PIN_SPI1_MISO        (54u)
#define PIN_SPI1_SS          PIN_NOT_CONNECTED // NC, UNDEFINED
#define PERIPH_SPI1          sercom2
#define PAD_SPI1_TX          SPI_PAD_3_SCK_1
#define PAD_SPI1_RX          SERCOM_RX_PAD_0

static const uint8_t MOSI1 = PIN_SPI1_MOSI ;
static const uint8_t SCK1  = PIN_SPI1_SCK  ;
static const uint8_t MISO1 = PIN_SPI1_MISO ;
static const uint8_t SS1   = PIN_SPI1_SS   ;  // HW SS isn't used. Set here only for reference.

// Needed for SD library, taken from MKRZero variant.h file
#define SDCARD_SPI      SPI1
#define SDCARD_MOSI_PIN PIN_SPI1_MOSI
#define SDCARD_SCK_PIN  PIN_SPI1_SCK
#define SDCARD_MISO_PIN PIN_SPI1_MISO
#define SDCARD_SS_PIN   PIN_SPI1_SS


/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

// Primary I2S pins (I2C, EXTERNAL)
#define PIN_WIRE_SDA         (45u)
#define PIN_WIRE_SCL         (46u)
#define PERIPH_WIRE          sercom4
#define WIRE_IT_HANDLER      SERCOM4_Handler

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;


// Secondary I2S pins (I2C1, INTERNAL)
#define PIN_WIRE1_SDA         (47u)
#define PIN_WIRE1_SCL         (48u)
#define PERIPH_WIRE1          sercom3
#define WIRE1_IT_HANDLER      SERCOM3_Handler 

static const uint8_t SDA1 = PIN_WIRE1_SDA;
static const uint8_t SCL1 = PIN_WIRE1_SCL;


/*
 * USB
 */
#define PIN_USB_DM          (55ul)
#define PIN_USB_DP          (56ul)


/*
 * I2S Interfaces
 */
#define I2S_INTERFACES_COUNT 1

#define I2S_DEVICE          0
#define I2S_CLOCK_GENERATOR 3
#define PIN_I2S_SD          (20u)    // D20 PA19 (I2S_SD[0])
#define PIN_I2S_SCK         (21u)    // D21 PA20 (I2S_SCK[0])
#define PIN_I2S_FS          (22u)    // D22 PA21 (I2S_FS[0])

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
extern SERCOM sercom4;
extern SERCOM sercom5;

extern Uart Serial1;
extern Uart SerialBLE;

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

#define SERIAL_PORT_HARDWARE        SerialBLE
#define SERIAL_PORT_HARDWARE_OPEN   Serial1



#endif /* _VARIANT_SOK_ZERO_DAWN_ */

