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
 * Pins descriptions for Sok M4 Advance board
 */

//TCC0 IOSET 6
//TCC1 IOSET 1
//TC0 IOSET 1
//TC1 IOSET 1
//TC2 IOSET 2
//TC3 IOSET 1
//TC4 IOSET 1
const PinDescription g_APinDescription[]=
{
/*
 * | PORT | PIN | PIN_TYPE    | PIN_ATTRIBUTES                                                     | ADC_CHANNEL   | PWM_CHANNEL | TIMER_CHANNEL | EXT. INTERRUPT |
 */

  // 0...13 - Digital pins
  // ----------------------
  // 0/1 - SERCOM/UART (Serial1)
  { PORTA,  4, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),        ADC_Channel4,  TCC0_CH0,   TCC0_CH0,     EXTERNAL_INT_4 },    //  0 D0  ALT_SERCOM0_PAD[0] / AIN[4]  /     TCC0_WO[0] / INT_4  / (Serial1_TX)
  { PORTA,  5, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),        ADC_Channel5,  TCC0_CH1,   TCC0_CH1,     EXTERNAL_INT_5 },    //  1 D1  ALT_SERCOM0_PAD[1] / AIN[5]  /     TCC0_WO[1] / INT_5  / (Serial1_RX) / DAC1 / VOUT1


  // 2...13
  // Digital Low
  { PORTA,  6, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),        ADC_Channel6,  TCC1_CH0,   TCC1_CH0,     EXTERNAL_INT_6   },  //  2 D2  ALT_SERCOM0_PAD[2] / AIN[6]  /     TCC1_WO[1] / INT_6 
  { PORTA, 11, PIO_SERCOM,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_G|PIN_ATTR_TIMER_ALT),    ADC_Channel11, TCC1_CH7,   TCC1_CH7,     EXTERNAL_INT_11  },  //  3 D3      SERCOM0_PAD[3] / AIN[11] / ALT_TCC1_WO[7] / INT_11  / (I2S_SDO)
  { PORTA, 10, PIO_SERCOM,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_G|PIN_ATTR_TIMER_ALT),    ADC_Channel10, TCC1_CH6,   TCC1_CH6,     EXTERNAL_INT_10  },  //  4 D4      SERCOM0_PAD[2] / AIN[10] / ALT_TCC1_WO[6] / INT_10  / (I2S_SCK[0])
  { PORTA,  9, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                                      ADC_Channel9,  TCC1_CH3,   TCC1_CH3,     EXTERNAL_INT_9   },  //  5 D5                     / AIN[9]  /    TCC1_WO[3]  / INT_9*  / (I2S_FS[0])
  { PORTB, 10, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM_F|PIN_ATTR_TIMER_ALT),                 No_ADC_Channel,   TCC0_CH4,   TCC0_CH4,     EXTERNAL_INT_10  },  //  6 D6  ALT_SERCOM4_PAD[2] /         / ALT_TCC0_WO[4] / INT_10* / (I2S_SDI)
  { PORTB, 13, PIO_SERCOM,      (                PIN_ATTR_DIGITAL|PIN_ATTR_PWM_F|PIN_ATTR_TIMER_ALT), No_ADC_Channel,   TC3_CH1,    TC3_CH1,      EXTERNAL_INT_13  },  //  7 D7      SERCOM4_PAD[1] /         /      TC3_WO[0] / INT_13*                                       
  
 
  // Digital High
  { PORTB, 12, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM_F|PIN_ATTR_TIMER_ALT),                No_ADC_Channel,  TC3_CH0,   TC3_CH0,      EXTERNAL_INT_12 },    //  8 D8       SERCOM4_PAD[0] /         /      TC3_WO[0] / INT 12*
  { PORTB, 11, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM_F|PIN_ATTR_TIMER_ALT),                No_ADC_Channel,  TCC0_CH5,  TCC0_CH5,     EXTERNAL_INT_11 },    //  9 D9   ALT_SERCOM4/PAD[3] /         / ALT_TCC0_WO[5] / INT_11*
  { PORTA,  7, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),       ADC_Channel7, TCC1_CH1,  TCC1_CH1,     EXTERNAL_INT_7  },    // 10 D10  ALT_SERCOM0_PAD[3] / AIN[7]  /     TCC1_WO[1] / INT_7
  { PORTB, 14, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),                    No_ADC_Channel,  TC5_CH0,   TC5_CH0,      EXTERNAL_INT_14 },    // 11 D11     SERCOM4_PAD[2] /         /      TC5_WO[0] / INT_14*                                  
  { PORTB, 15, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),                    No_ADC_Channel,  TC5_CH1,   TC5_CH1,      EXTERNAL_INT_15 },    // 12 D12     SERCOM4_PAD[3] /         /      TC5_WO[1] / INT_15*
  { PORTA, 14, PIO_SERCOM,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM_F|PIN_ATTR_TIMER_ALT),                No_ADC_Channel,  TC2_CH0,   TC2_CH0,      EXTERNAL_INT_14 },    // 13 D13     SERCOM2_PAD[2] /         / ALT_TC2_WO[0]  / INT_14

 
  // 14...24 - Extra Digital Pins!
  // --------------------  
  { PORTA, 19, PIO_OUTPUT,      (PIN_ATTR_DIGITAL|PIN_ATTR_PWM_G|PIN_ATTR_TIMER),                  No_ADC_Channel, TCC0_CH7,   TCC0_CH7,     EXTERNAL_INT_3  },     // 14 D14                      /         / ALT_TCC0_WO[7] / INT_3  / (lED_BUILTIN)
  { PORTA, 27, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },     // 15 D15                      /         /                / INT_15 / (BLE_RESET)    
  { PORTB, 22, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6  },     // 16 D16                      /         /                / INT_6  / (BLE_ENABLE)   
  { PORTB, 31, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },     // 17 D17                      /         /                / INT_15 / (BLE_CONFIG)      
  { PORTB, 30, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14 },     // 18 D18                      /         /                / INT_14 / (BLE_MSTR_SLV) 
  { PORTB, 17, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1  },     // 19 D19                      /         /                / INT_1  / (BLE_STATE)    
  { PORTA, 22, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6  },     // 20 D20                      /         /                / INT_6  / (I2S_SDI)
  { PORTB, 16, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0  },     // 21 D21                      /         /                / INT_0  / (I2S_SCK0)
  { PORTA, 20, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4  },     // 22 D22                      /         /                / INT_4  / (I2S_FS0)
  { PORTA, 18, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2  },     // 23 D23                      /         /                / INT_2  / (NC)
  { PORTA, 21, PIO_OUTPUT,      (PIN_ATTR_DIGITAL),                                                No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5  },     // 24 D24                      /         /                / INT_5  / (NC) 
 

  // 25...44 - Analog pins (digitals hidden also)
  // --------------------
  { PORTB,  0, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel12, TC7_CH0,    TC7_CH0,      EXTERNAL_INT_0    },  // 25 A0                       / AIN[12] /     TC7/WO[0]  / INT_0*
  { PORTB,  1, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel13, TC7_CH1,    TC7_CH1,      EXTERNAL_INT_1    },  // 26 A1                       / AIN[13] /     TC7/WO[1]  / INT_1* 
  { PORTB,  2, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel14, TC6_CH0,    TC6_CH0,      EXTERNAL_INT_2    },  // 27 A2                       / AIN[14] /     TC6/WO[0]  / INT_2*
  { PORTB,  3, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel15, TC6_CH1,    TC6_CH1,      EXTERNAL_INT_3    },  // 28 A3                       / AIN[15] /     TC6/WO[1]  / INT_3*
  { PORTA,  2, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                                   ADC_Channel0,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2    },  // 29 A4                       / AIN[0]  /                / INT_2 / DAC0 / VOUT0
  { PORTB,  4, PIO_ANALOG,      (PIN_ATTR_ANALOG_ALT|PIN_ATTR_DIGITAL),                               ADC_Channel6,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4    },  // 30 A5                       / AIN[6]  /                / INT_4*
  { PORTB,  5, PIO_ANALOG,      (PIN_ATTR_ANALOG_ALT|PIN_ATTR_DIGITAL),                               ADC_Channel7,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5    },  // 31 A6                       / AIN[7]  /                / INT_5*
  { PORTA,  8, PIO_SERCOM,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_G|PIN_ATTR_TIMER_ALT), ADC_Channel8,  TCC1_CH4,   TCC1_CH4,     EXTERNAL_INT_NONE },  // 32 A7       SERCOM0_PAD[0]  / AIN[8]  / ALT_TCC1_WO[4] / NMI
  { PORTB,  6, PIO_ANALOG,      (PIN_ATTR_ANALOG_ALT|PIN_ATTR_DIGITAL),                               ADC_Channel8,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6    },  // 33 A8                       / AIN[8]  /                / INT_6*
  { PORTB,  7, PIO_ANALOG,      (PIN_ATTR_ANALOG_ALT|PIN_ATTR_DIGITAL),                               ADC_Channel9,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7    },  // 34 A9                       / AIN[9]  /                / INT_7*
  { PORTA,  4, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel4,  TCC0_CH0,   TCC0_CH0,     EXTERNAL_INT_4    },  // 35 A10  ALT_SERCOM0_PAD[0]  / AIN[4]  /     TCC0_WO[0] / INT_4  / (D0, Serial_TX)
  { PORTA,  5, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel5,  TCC0_CH1,   TCC0_CH1,     EXTERNAL_INT_5    },  // 36 A11  ALT_SERCOM0_PAD[1]  / AIN[5]  /     TCC0_WO[1] / INT_5  / (D1, Serial_RX) / DAC1 / VOUT1
  { PORTA,  6, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel6,  TCC1_CH0,   TCC1_CH0,     EXTERNAL_INT_6    },  // 37 A12  ALT_SERCOM0_PAD[0]  / AIN[6]  /     TCC1_WO[1] / INT_6  / (D2)
  { PORTA, 11, PIO_SERCOM,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_G|PIN_ATTR_TIMER_ALT), ADC_Channel11, TCC1_CH7,   TCC1_CH7,     EXTERNAL_INT_11   },  // 38 A16      SERCOM0_PAD[3]  / AIN[11] / ALT_TCC1_WO[7] / INT_11 / (D3)
  { PORTA, 10, PIO_SERCOM,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_G|PIN_ATTR_TIMER_ALT), ADC_Channel10, TCC1_CH6,   TCC1_CH6,     EXTERNAL_INT_10   },  // 39 A14      SERCOM0_PAD[2]  / AIN[10] / ALT_TCC1_WO[6] / INT_10 / (D4)
  { PORTA,  9, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                                   ADC_Channel9,  TCC1_CH3,   TCC1_CH3,     EXTERNAL_INT_9    },  // 40 A15                      / AIN[9]  /    TCC1_WO[3]  / INT_9* / (D5, I2S_FS[0])
  { PORTA,  7, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel7,  TCC1_CH1,   TCC1_CH1,     EXTERNAL_INT_7    },  // 41 A16  ALT_SERCOM0_PAD[1]  / AIN[7]  /     TCC1_WO[1] / INT_7  / (D10)
  { PORTB,  8, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel2,  TC4_CH0,    TC4_CH0,      EXTERNAL_INT_8    },  // 42 A17  ALT_SERCOM4_PAD[0]  / AIN[2]  /     TC4_WO[0]  / INT_8* / (I2C_SDA, EXTERNAL)
  { PORTB,  9, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel3,  TC4_CH1,    TC4_CH1,      EXTERNAL_INT_9    },  // 43 A18  ALT_SERCOM4_PAD[1]  / AIN[3]  /     TC4_WO[1]  / INT_9  / (I2C_SCL, EXTERNAL)
  { PORTA,  3, PIO_ANALOG,      (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL),                                   ADC_Channel1,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3    },  // 44 A19                      / AIN[1]  /                / INT_3  / (SOK, SOK_SELECTOR)


  // 45...46 Primary I2C pins (EXTERNAL I2C: SDA, SCL)
  // ----------------------
  { PORTB,  8, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel2,    TC4_CH0,      TC4_CH0, EXTERNAL_INT_8 },     // 45 SDA   ALT_SERCOM4_PAD[0]  / AIN[2]  /     TC4_WO[0]  / INT_8* / (I2C_SDA, EXTERNAL)
  { PORTB,  9, PIO_SERCOM_ALT,  (PIN_ATTR_ANALOG|PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),     ADC_Channel3,    TC4_CH1,      TC4_CH1, EXTERNAL_INT_9 },     // 46 SCL   ALT_SERCOM4_PAD[1]  / AIN[3]  /     TC4_WO[1]  / INT_9  / (I2C_SCL, EXTERNAL)
  

  // 47...48 Secondary I2C pins (INTERNAL I2C: SDA1, SCL1)
  // ----------------------
  { PORTA, 17, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM_E|PIN_ATTR_TIMER),                   No_ADC_Channel,   TCC2_CH1,     TCC2_CH1, EXTERNAL_INT_1 },     // 47 SDA1  ALT_SERCOM3/PAD[0]  /         /    TCC2_WO[1]  / INT_1  / (I2C_SCL1, INTERNAL)       
  { PORTA, 16, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0 },     // 48 SCL1  ALT_SERCOM3/PAD[1]  /         /                / INT_0  / (I2C_SDA1, INTERNAL)
 

  // 49...51 Primary SPI pins (EXTERNAL SPI: MOSI, SCK, MISO)
  // ----------------------
  { PORTA, 31, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 },    // 49 MOSI  ALT_SERCOM1/PAD[2]  /         /                / INT_10 / (SPI_MOSI, EXTERNAL) 
  { PORTA,  1, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1  },    // 50 SCK   ALT_SERCOM1/PAD[1]  /         /                / INT_1  / (SPI_SCK,  EXTERNAL)
  { PORTA, 30, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 },    // 51 MISO  ALT_SERCOM1/PAD[3]  /         /                / INT_11 / (SPI_SCK,  EXTERNAL)


  // 52...54 Secondary SPI pins (INTERNAL SPI1: MOSI1, SCK1, MISO1)
  // ----------------------
  { PORTA, 15, PIO_SERCOM,      (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },    // 52 MOSI1     SERCOM2/PAD[3]  /         /                / INT_15 / (SPI_MOSI1, INTERNAL)
  { PORTA, 13, PIO_SERCOM,      (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 },    // 53 SCK1      SERCOM2/PAD[1]  /         /                / INT_13 / (SPI_SCK1,  INTERNAL)
  { PORTA, 12, PIO_SERCOM,      (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12 },    // 54 MISO1     SERCOM2/PAD[0]  /         /                / INT_12 / (SPI_MISO1, INTERNAL)                         


  // 55...56 - USB D-/D+
  // --------------------
  { PORTA, 24, PIO_COM,         (PIN_ATTR_NONE),                                                    No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 55 USB/DM    (Serial)
  { PORTA, 25, PIO_COM,         (PIN_ATTR_NONE),                                                    No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 56 USB/DP    (Serial)   


  // 57...58 UART Serial2 TX/RX (BLE Communication)
  // --------------------
  { PORTA, 23, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 },     // 57 TX    ALT_SERCOM5/PAD[0]  /         /                / INT_7  / (Serial2_TX, SAM_TX_BLE_RX) 
  { PORTB, 23, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL),                                                 No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 },     // 58 RX    ALT_SERCOM5/PAD[3]  /         /                / INT_7  / (Serial2_RX, SAM_RX_BLE_TX)               
 

  // 59 - Alternative use of PA03 (AREF)
  // ----------------------
  { PORTA,  3, PIO_ANALOG,      (PIN_ATTR_ANALOG),                                                  No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // 59 AREF


  // 60 - Not connected pin
  // ----------------------
  { NOT_A_PORT, PIN_NOT_A_PIN, PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },  // USB Host enable DOES NOT EXIST ON THIS BOARD
 
 
  // 61..66 QSPI (SCK, CS, IO0, IO1, IO2, IO3)
  // ----------------------
  { PORTB, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTB, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 8,  PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 9,  PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },


  // 67..68 32.768kHz clock pins
  // ----------------------
  { PORTA,  0, PIO_OUTPUT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0 },      // 67 XIN21   / INT_0 / (INT_APDS)
  { PORTA,  1, PIO_OUTPUT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1 },      // 68 XOUT32 (USED AS SCJ SPI)

} ;


const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5, } ;
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM+TC_INST_NUM] = { TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TCC3_GCLK_ID, TCC4_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID, TC4_GCLK_ID, TC5_GCLK_ID,  } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;


Uart Serial1   ( &sercom0, PIN_SERIAL1_RX,   PIN_SERIAL1_TX,   PAD_SERIAL1_RX,   PAD_SERIAL1_TX );
Uart Serial2   ( &sercom5, PIN_SERIAL2_RX,   PIN_SERIAL2_TX,   PAD_SERIAL2_RX,   PAD_SERIAL2_TX );
Uart SerialSOK ( &sercom4, PIN_SERIALSOK_RX, PIN_SERIALSOK_TX, PAD_SERIALSOK_RX, PAD_SERIALSOK_TX ); // Alternative use of SERCOM 4


// SERCOM 0
void SERCOM0_0_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM0_1_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM0_2_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM0_3_Handler()
{
  Serial1.IrqHandler();
}

// SERCOM 4
#if defined(USE_SERIAL_SOK)
#warning External Wire I2C interface won't be available meanwhile you use SerialSOK
void SERCOM4_0_Handler()
{
  SerialSOK.IrqHandler();
}
void SERCOM4_1_Handler()
{
  SerialSOK.IrqHandler();
}
void SERCOM4_2_Handler()
{
  SerialSOK.IrqHandler();
}
void SERCOM4_3_Handler()
{
  SerialSOK.IrqHandler();
}
#endif

// SERCOM 5
void SERCOM5_0_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM5_1_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM5_2_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM5_3_Handler()
{
  Serial2.IrqHandler();
}