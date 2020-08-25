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
 * Pins descriptions for Kitten Syringe / Display
 * 
 */
const PinDescription g_APinDescription[]=
{
/*
 * | PORT | PIN | PIN_TYPE    | PIN_ATTRIBUTES                                  | ADC_CHANNEL   | PWM_CHANNEL | TIMER_CHANNEL | EXT. INTERRUPT |
 */

 
  // 0...13 - Digital pins
  // ----------------------
  // 0/1 - SERCOM/UART (Serial1) - SERCOM3
  { PORTA, 30, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM1_CH0,   TCC1_CH0,     EXTERNAL_INT_10 },   //  0 D0   ALT_SERCOM1/PAD[2] /         /     TCC1_WO[0]* / INT_10* / (SPI_MISO) *Same timer as A2
  { PORTA, 31, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM1_CH1,   TCC1_CH1,     EXTERNAL_INT_11 },   //  1 D1   ALT_SERCOM1/PAD[3] /         /     TCC1_WO[1]* / INT_11* / (SPI_MOSI) *Same timer as A3

  // Digital Low - 2...7  
  { PORTA, 22, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM4_CH0,   TC4_CH0,      EXTERNAL_INT_6  },   //  2 D2       SERCOM3_PAD[0] /         /     TC4_WO[0]   / INT_6   / (I2C_SDA1, Serial1_TX)
  { PORTA, 23, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM4_CH1,   TC4_CH1,      EXTERNAL_INT_7  },   //  3 D3       SERCOM3_PAD[1] /         /     TC4_WO[1]   / INT_7   / (I2C_SCL1, Serial1_RX)
  { PORTA, 14, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),             No_ADC_Channel,   PWM0_CH4,   TCC0_CH4,     EXTERNAL_INT_14 },   //  4 D4       SERCOM2_PAD[2] /         / ALT_TCC0_WO[4]  / INT_14
  { PORTA, 15, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),             No_ADC_Channel,   PWM0_CH5,   TCC0_CH5,     EXTERNAL_INT_15 },   //  5 D5       SERCOM2_PAD[3] /         / ALT_TCC0_WO[5]  / INT_15*
  { PORTA, 16, PIO_TIMER_ALT,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),             No_ADC_Channel,   PWM0_CH6,   TCC0_CH6,     EXTERNAL_INT_0  },   //  6 D6                      /         / ALT_TCC0_WO[6]  / INT_0*  
  { PORTA, 17, PIO_TIMER_ALT,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),             No_ADC_Channel,   PWM0_CH7,   TCC0_CH7,     EXTERNAL_INT_1  },   //  7 D7                      /         / ALT_TCC0_WO[7]  / INT_1*  

  // Digital High - 8...13
  { PORTA, 18, PIO_TIMER,       (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM3_CH0,   TC3_CH0,      EXTERNAL_INT_2  },   //  8 D8                      /         /     TC3_WO[0]   / INT_2*  
  { PORTA, 19, PIO_TIMER,       (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM3_CH1,   TC3_CH1,      EXTERNAL_INT_3  },   //  9 D9                      /         /     TC3_WO[1]   / INT_3   / (I2S_SD[0])
  { PORTA,  0, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM2_CH0,   TCC2_CH0,     EXTERNAL_INT_0  },   // 10 D10  ALT_SERCOM1/PAD[0] /         /     TCC2_WO[0]  / INT_0   / XIN32
  { PORTA,  1, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM2_CH1,   TCC2_CH1,     EXTERNAL_INT_1  },   // 11 D11  ALT_SERCOM1/PAD[1] /         /     TCC2_WO[1]  / INT_1   / XOUT32
  { PORTA, 28, PIO_DIGITAL,     (PIN_ATTR_DIGITAL),                                             No_ADC_Channel,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8  },   // 13 D13                     /         /                 / INT_8   / (LED_BUILTIN) 
  { PORTA, 27, PIO_DIGITAL,     (PIN_ATTR_DIGITAL),                                             No_ADC_Channel,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },   // 12 D12                     /         /                 / INT_15         


  // 14...23 - Analog pins (digitals hidden also)
  // --------------------
  { PORTA,  4, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),    ADC_Channel4,  PWM0_CH0,   TCC0_CH0,     EXTERNAL_INT_4  },   // 14 A0   ALT_SERCOM0_PAD[0] / AIN[4]  /     TCC0_WO[0]  / INT_4  
  { PORTA,  5, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),    ADC_Channel5,  PWM0_CH1,   TCC0_CH1,     EXTERNAL_INT_5  },   // 15 A1   ALT_SERCOM0_PAD[1] / AIN[5]  /     TCC0_WO[1]  / INT_5  / (SPI_SCK1)
  { PORTA,  6, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),    ADC_Channel6,  PWM1_CH0,   TCC1_CH0,     EXTERNAL_INT_6  },   // 16 A2   ALT_SERCOM0_PAD[2] / AIN[6]  /     TCC1_WO[0]  / INT_6* / (SPI_MISO1)
  { PORTA,  7, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),    ADC_Channel7,  PWM1_CH1,   TCC1_CH1,     EXTERNAL_INT_7  },   // 17 A3   ALT_SERCOM0_PAD[1] / AIN[7]  /     TCC1_WO[1]  / INT_7* / (SPI_MOSI1)
  { PORTA,  8, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),ADC_Channel16, PWM1_CH2,   TCC1_CH2,     EXTERNAL_INT_NONE }, // 18 A4   ALT_SERCOM2_PAD[0] / AIN[16] / ALT_TCC1_WO[2]  / NMI    / (I2C_SDA, Serial2)
  { PORTA,  9, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),ADC_Channel17, PWM1_CH3,   TCC1_CH3,     EXTERNAL_INT_9  },   // 19 A5   ALT_SERCOM2_PAD[1] / AIN[17] / ALT_TCC1_WO[3]  / INT_9  / (I2C_SCL, Serial2)
  { PORTA, 10, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),ADC_Channel18, PWM0_CH2,   TCC0_CH2,     EXTERNAL_INT_10 },   // 20 A6   ALT_SERCOM2_PAD[2] / AIN[18] / ALT_TCC0_WO[2]  / INT_10 
  { PORTA, 11, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),ADC_Channel19, PWM0_CH3,   TCC0_CH3,     EXTERNAL_INT_11 },   // 21 A7   ALT_SERCOM2_PAD[3] / AIN[19] / ALT_TCC0_WO[3]  / INT_11 
  { PORTA,  2, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                                ADC_Channel0,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2  },   // 22 A8                      / AIN[0]  /                 / INT_2  / (DAC)
  { PORTA,  3, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                                ADC_Channel1,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3  },   // 23 A9                      / AIN[1]  /                 / INT_3* / (SOK, AREF)


  // 24...25 Primary I2C pins (SDA, SCL) - SERCOM2
  // ----------------------
  { PORTA,  8, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),ADC_Channel16, PWM1_CH2,   TCC1_CH2,     EXTERNAL_INT_NONE }, // 24 SDA  ALT_SERCOM2_PAD[0] / AIN[16] / ALT_TCC1_WO[2]  / NMI    / (I2C_SDA, Serial2)
  { PORTA,  9, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT),ADC_Channel17, PWM1_CH3,   TCC1_CH3,     EXTERNAL_INT_9  },   // 25 SCL  ALT_SERCOM2_PAD[1] / AIN[17] / ALT_TCC1_WO[3]  / INT_9  / (I2C_SCL, Serial2)


  // 26...27 Secondary I2C pins (SDA1, SCL1) - SERCOM3
  // ----------------------
  { PORTA, 22, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM4_CH0,   TC4_CH0,      EXTERNAL_INT_6  },   // 26 SDA1     SERCOM3_PAD[0] /         /     TC4_WO[0]   / INT_6  / (I2C_SDA1, Serial1_TX) / D2
  { PORTA, 23, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM4_CH1,   TC4_CH1,      EXTERNAL_INT_7  },   // 27 SCL1     SERCOM3_PAD[1] /         /     TC4_WO[1]   / INT_7  / (I2C_SCL1, Serial1_RX) / D3


  // 28...30 Primary SPI pins (MOSI, SCK, MISO) - SERCOM1
  // ----------------------
  { PORTA, 31, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM1_CH1,   TCC1_CH1,     EXTERNAL_INT_11 },   // 28 MOSI ALT_SERCOM1/PAD[3] /         /     TCC1_WO[1]* / INT_11*/ (SPI_MOSI) *Same timer as A3
  { PORTA,  1, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM2_CH1,   TCC2_CH1,     EXTERNAL_INT_1  },   // 29 SCK  ALT_SERCOM1/PAD[1] /         /     TCC2_WO[1]  / INT_1  / (SPI_SCK)  *Same as D11
  { PORTA, 30, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),                 No_ADC_Channel,   PWM1_CH0,   TCC1_CH0,     EXTERNAL_INT_10 },   // 30 MISO ALT_SERCOM1/PAD[2] /         /     TCC1_WO[0]* / INT_10*/ (SPI_MISO) *Same timer as A2


  // 31...33 Secondary SPI1 pins (MOSI1, SCK1, MISO1) - SERCOM0
  // ----------------------
  { PORTA,  7, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),    ADC_Channel7,  PWM1_CH1,   TCC1_CH1,     EXTERNAL_INT_7  },   // 31 MOSI1  ALT_SERCOM0_PAD[3] / AIN[7]  /  TCC1_WO[1] / INT_7* / (SPI1_MOSI1)
  { PORTA,  5, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),    ADC_Channel5,  PWM0_CH1,   TCC0_CH1,     EXTERNAL_INT_5  },   // 32 SCK1   ALT_SERCOM0_PAD[1] / AIN[5]  /  TCC0_WO[1] / INT_5  / (SPI1_SCK1)
  { PORTA,  6, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER),    ADC_Channel6,  PWM1_CH0,   TCC1_CH0,     EXTERNAL_INT_6  },   // 33 MISO1  ALT_SERCOM0_PAD[2] / AIN[6]  /  TCC1_WO[0] / INT_6* / (SPI1_MISO1)


  // 34...35 - USB D-/D+
  // --------------------
  { PORTA, 24, PIO_COM,         (PIN_ATTR_NONE),                                                No_ADC_Channel,   PWM5_CH0,   TC5_CH0,      EXTERNAL_INT_12 },   // 34 USB/DM    (Serial)
  { PORTA, 25, PIO_COM,         (PIN_ATTR_NONE),                                                No_ADC_Channel,   PWM5_CH1,   TC5_CH1,      EXTERNAL_INT_13 },   // 35 USB/DP    (Serial)   


  // 36 - Alternative use of PA03 (AREF)
  // ----------------------
  { PORTA,  3, PIO_ANALOG,      (PIN_ATTR_ANALOG),                                              No_ADC_Channel,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 36 AREF


  // 37 - Not connected pin
  // ----------------------
  { NOT_A_PORT, PIN_NOT_A_PIN, PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB Host enable DOES NOT EXIST ON THIS BOARD

} ;


const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;


// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ; // SPI1
SERCOM sercom1( SERCOM1 ) ; // SPI   / Serial1 (DO/D1)
SERCOM sercom2( SERCOM2 ) ; // Wire  / SerialSOK (Display) - Wire1 (Syringe)
SERCOM sercom3( SERCOM3 ) ; // Wire1 (Display)             - Wire  / SerialSOK (Syringe)


Uart Serial1   ( &sercom1, PIN_SERIAL1_RX,   PIN_SERIAL1_TX,   PAD_SERIAL1_RX,   PAD_SERIAL1_TX   ); // Alternative use of SERCOM 1
#if defined (NEKUNEKO_KITTEN_SYRINGE)
Uart SerialSOK ( &sercom3, PIN_SERIALSOK_RX, PIN_SERIALSOK_TX, PAD_SERIALSOK_RX, PAD_SERIALSOK_TX ); // Alternative use of SERCOM 3
#elif defined (NEKUNEKO_KITTEN_DISPLAY)
Uart SerialSOK ( &sercom2, PIN_SERIALSOK_RX, PIN_SERIALSOK_TX, PAD_SERIALSOK_RX, PAD_SERIALSOK_TX ); // Alternative use of SERCOM 2
#endif


// SERCOM 0 - SPI1

// SERCOM 1 - SPI - Serial1
#if defined (USE_SERIAL_OVER_SPI)
  #warning SPI interface won't be available meanwhile you use Serial1 (Serial Over SPI)

  void SERCOM1_Handler()
  {
    Serial1.IrqHandler();
  }
#endif

// SERCOM 2 - Wire1 (Syringe)
// SERCOM 3 - Wire1 (Display) 

#if defined (USE_SERIAL_OVER_I2C)
  #warning Wire/Wire1 I2C/I2C1 interfaces won't be available meanwhile you use SerialSOK (Serial Over I2C)

  // SERCOM 3 - SPI - Wire1 (Syringe)
  #if defined (NEKUNEKO_KITTEN_SYRINGE)
    void SERCOM3_Handler()
    {
      SerialSOK.IrqHandler();
    } 

  // SERCOM 2 - Wire  / SerialSOK (Display)
  #elif defined (NEKUNEKO_KITTEN_DISPLAY)
    void SERCOM2_Handler()
    {
      SerialSOK.IrqHandler();
    }
  #endif
#endif




