// Stimey SAMD21G18A Variant
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


#include "variant.h"

/*
 * Pins descriptions for Gontak Sok Zero
 * 
 */
const PinDescription g_APinDescription[]=
{
/*
 * | PORT | PIN | PIN_TYPE    | PIN_ATTRIBUTES                                  | ADC_CHANNEL   | PWM_CHANNEL | TIMER_CHANNEL | EXT. INTERRUPT |
 */

  // 0...13 - Digital pins
  // ----------------------
  // 0/1 - SERCOM/UART (Serial1)
  { PORTB,  8, PIO_SERCOM_ALT, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),      ADC_Channel2, PWM4_CH0, TC4_CH0, EXTERNAL_INT_8 },      // D0  TX: ALT_SERCOM4/PAD[0] / ADC/AIN[2] / TC4/WO[0] / INT_8
  { PORTB,  9, PIO_SERCOM_ALT, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),      ADC_Channel3, PWM4_CH1, TC4_CH1, EXTERNAL_INT_9 },      // D1  RX: ALT_SERCOM4/PAD[1] / ADC/AIN[3] / TC4/WO[1] / INT_9

  // 2...14
  // Digital Low
  { PORTA,  4, PIO_SERCOM_ALT, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),      ADC_Channel4, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_4 },     // D2  ALT_SERCOM0/PAD[0] / ADC/AIN[4]  / TCC0/WO[0] / INT_4 
  { PORTA,  5, PIO_SERCOM_ALT, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),      ADC_Channel5, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_5 },     // D3  ALT_SERCOM0/PAD[1] / ADC/AIN[5]  / TCC0/WO[1] / INT_5
  { PORTA,  6, PIO_SERCOM_ALT, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),      ADC_Channel6, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_6 },     // D4  ALT_SERCOM0/PAD[2] / ADC/AIN[6]  / TCC1/WO[0] / INT_6
  { PORTA,  7, PIO_SERCOM_ALT, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),      ADC_Channel7, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_7 },     // D5  ALT_SERCOM0/PAD[3] / ADC/AIN[7]  / TCC1/WO[1] / INT_7
  { PORTA,  8, PIO_SERCOM,     (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), ADC_Channel16, PWM1_CH2, TCC1_CH2, EXTERNAL_INT_NONE },  // D6  SERCOM0/PAD[0]     / ADC/AIN[16] / TCC1/WO[2] / NMI
  { PORTA,  9, PIO_SERCOM,     (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), ADC_Channel17, PWM1_CH3, TCC1_CH3, EXTERNAL_INT_NONE },  // D7  SERCOM0/PAD[1]     / ADC/AIN[17] / TCC1/WO[3]               // INT_9 removed, REPETIDA CON D1!
 
  // Digital High
  { PORTA, 10, PIO_SERCOM,     (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), ADC_Channel18, PWM0_CH2, TCC0_CH2, EXTERNAL_INT_NONE },  // D8  SERCOM0/PAD[2]     / ADC/AIN[18] / TCC0/WO[2]               // INT_10 removed
  { PORTA, 11, PIO_SERCOM,     (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), ADC_Channel19, PWM0_CH3, TCC0_CH3, EXTERNAL_INT_NONE },  // D9  SERCOM0/PAD[3]     / ADC/AIN[19] / TCC0/WO[3]               // INT 11 removed
  { PORTB, 10, PIO_TIMER_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),                No_ADC_Channel, PWM0_CH4, TCC0_CH4, EXTERNAL_INT_10 },    // D10 TCC0/WO[4] / INT_10                                         // TC5_CH0 removed
  { PORTB, 11, PIO_TIMER_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),                No_ADC_Channel, PWM0_CH5, TCC0_CH5, EXTERNAL_INT_11 },    // D11 TCC0/WO[5] / INT_11                                         // TC5_CH1 removed       
  { PORTB, 12, PIO_TIMER_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),                No_ADC_Channel, PWM0_CH6, TCC0_CH6, EXTERNAL_INT_12 },    // D12 TCC0/WO[6] / INT_12
  { PORTB, 13, PIO_TIMER_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),                No_ADC_Channel, PWM0_CH7, TCC0_CH7, EXTERNAL_INT_13 },    // D13 TCC0/WO[7] / INT_13
  { PORTB, 14, PIO_TIMER,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                    No_ADC_Channel, PWM5_CH0, TC5_CH0,  EXTERNAL_INT_14 },    // D14 TC5/WO[0]  / INT_14  

 
  // 15...18 - Extra Digital Pins!
  // --------------------  
  { PORTB, 15, PIO_TIMER,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel, PWM5_CH1, TC5_CH1, EXTERNAL_INT_NONE },         // D15 (BUZZER)  TC5/WO[1]                
  { PORTB, 17, PIO_OUTPUT, (PIN_ATTR_DIGITAL),                                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // D16 (BLE_RESET)      
  { PORTA, 23, PIO_OUTPUT, (PIN_ATTR_DIGITAL),                                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // D17 (BLE_CONFIG)            
  { PORTA, 27, PIO_OUTPUT, (PIN_ATTR_DIGITAL),                                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // D18 (Unused)              


  // 19...27 - Analog pins
  // --------------------
  { PORTB,  0, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),  ADC_Channel8, PWM7_CH0, TC7_CH0, EXTERNAL_INT_0 },            // 19 A0 ADC/AIN[8]  / TC7/WO[0] / INT_0
  { PORTB,  1, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),  ADC_Channel9, PWM7_CH1, TC7_CH1, EXTERNAL_INT_1 },            // 20 A1 ADC/AIN[9]  / TC7/WO[1] / INT_1
  { PORTB,  2, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel10, PWM6_CH0, TC6_CH0, EXTERNAL_INT_2 },            // 21 A2 ADC/AIN[10] / TC6/WO[0] / INT_2
  { PORTB,  3, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel11, PWM6_CH1, TC6_CH1, EXTERNAL_INT_3 },            // 22 A3 ADC/AIN[11] / TC6/WO[1] / INT_3
  { PORTA,  2, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                              ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 23 A4 ADC/AIN[0]
  { PORTB,  4, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                             ADC_Channel12, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 24 A5 ADC/AIN[12]
  { PORTB,  5, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                             ADC_Channel13, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 25 A6 ADC/AIN[13]
  { PORTB,  6, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                             ADC_Channel14, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 26 A7 ADC/AIN[14]
  { PORTB,  7, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                             ADC_Channel15, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 27 A8 ADC/AIN[15]


  // 28...29 Primary I2C pins (EXTERNAL I2C SDA/SCL)
  // ----------------------
  { PORTA, 12, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH0, TCC2_CH0, EXTERNAL_INT_NONE },        // 28 SDA (I2C_EXT_SDA):  SERCOM2/PAD[0] / TCC2/WO[0]
  { PORTA, 13, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH1, TCC2_CH1, EXTERNAL_INT_NONE },        // 29 SCL (I2C_EXT_SCL):  SERCOM2/PAD[1] / TCC2/WO[1]
  

  // 30...31 Secondary I2C pins (INTERNAL I2C SDA1/SCL1)
  // ----------------------
  { PORTA, 16, PIO_SERCOM, (PIN_ATTR_DIGITAL),                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 30 SDA1 (I2C_INT_SDA): SERCOM1/PAD[0]
  { PORTA, 17, PIO_SERCOM, (PIN_ATTR_DIGITAL),                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 31 SCL1 (I2C_INT_SCL): SERCOM1/PAD[1] 


  // 32...34 Primary SPI pins (EXTERNAL SPI: MOSI, SCK, MISO)
  // ----------------------
  { PORTB, 30, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL),                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 32 MOSI  (SPI_EXT_MOSI):  SERCOM5/PAD[0]
  { PORTB, 23, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL),                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 33 SCK   (SPI_EXT_SCK):   SERCOM5/PAD[3]
  { PORTB, 31, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL),                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 34 MISO  (SPI_EXT_MISO):  SERCOM5/PAD[1] / INT_15


  // 35 Primary SPI SS pin (EXTERNAL)
  // ----------------------
  { PORTA, 28, PIO_OUTPUT, (PIN_ATTR_DIGITAL),                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 35 SS (SPI_EXT_CS)               


  // 36...38 Secondary SPI pins (INTERNAL SPI1: MOSI1, SCK1, MISO1)
  // ----------------------
  { PORTA, 20, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL),                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 36 MOSI1 (SPI_INT_MOSI): SERCOM3/PAD[2]
  { PORTA, 21, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL),                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 37 SCK1  (SPI_INT_SCK):  SERCOM3/PAD[3]
  { PORTA, 22, PIO_SERCOM,     (PIN_ATTR_DIGITAL),                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 38 MISO1 (SPI_INT_MISO): SERCOM3/PAD[0]                


  // 39 Secondary SPI1 SS1 pin (INTERNAL)
  // ----------------------
  { PORTB, 16, PIO_OUTPUT, (PIN_ATTR_DIGITAL),                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 39 SS1 (SPI_INT_CS)                  


  // 40...41 - RX/TX LEDS (PA14/PA15)  -- unused 
  // ----------------------
  { PORTA, 14, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH0, TC3_CH0, EXTERNAL_INT_NONE },         // 40 (BUILTIN_LED): SERCOM2/PAD[2] / TC3/WO[0]    -- used as output only
  { PORTA, 15, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH0, TC3_CH1, EXTERNAL_INT_NONE },         // 41 (BLE_LED):     SERCOM2/PAD[3] / TC3/WO[1]    -- used as output only

  
  // 42...43 - USB
  // --------------------
  { PORTA, 24, PIO_COM, (PIN_ATTR_NONE),                                   No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 43 USB/DM
  { PORTA, 25, PIO_COM, (PIN_ATTR_NONE),                                   No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 44 USB/DP

  // 44 - Unused PB44 Alternative MISO 
  { PORTB, 22, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL),                         No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 42 (Alternative MISO): SERCOM5/PAD[2]                

  // 45...46 UART Serial TX/RX (BLE Communication)
  // --------------------
  { PORTA, 18, PIO_SERCOM, (PIN_ATTR_DIGITAL),                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 45 (SAMD_TX_BLE_RX): SERCOM1/PAD[2]
  { PORTA, 19, PIO_SERCOM, (PIN_ATTR_DIGITAL),                             No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 46 (SAMD_RX_BLE_TX): SERCOM1/PAD[3]                  


  // 47 - Alternate use of PA03 A5 (AREF)
  // ----------------------
  { PORTA, 3, PIO_ANALOG, PIN_ATTR_ANALOG,                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 47 DAC/VREFP


  // 48 - Alternate use of PA02 A4 (DAC output)
  // ----------------------
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG,                                DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },       // 48 DAC/VOUT


} ;


const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5, TC6, TC7 } ;


// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;


Uart Serial1  ( &sercom4, PIN_SERIAL1_RX,    PIN_SERIAL1_TX,    PAD_SERIAL1_RX,    PAD_SERIAL1_TX    ) ;
Uart SerialBLE( &sercom1, PIN_SERIAL_BLE_RX, PIN_SERIAL_BLE_TX, PAD_SERIAL_BLE_RX, PAD_SERIAL_BLE_TX ) ;


//TwoWire Wire(&PERIPH_WIRE, PIN_WIRE_SDA, PIN_WIRE_SCL);
//TwoWire Wire1(&PERIPH_WIRE1, PIN_WIRE1_SDA, PIN_WIRE1_SCL);


void SERCOM1_Handler()
{
  SerialBLE.IrqHandler();
 // Wire1.onService();
}


void SERCOM4_Handler()
{
  Serial1.IrqHandler();
}
