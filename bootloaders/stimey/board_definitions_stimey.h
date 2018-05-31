/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Atmel Corporation/Thibaut VIARD.  All right reserved.

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

#ifndef _BOARD_DEFINITIONS_H_
#define _BOARD_DEFINITIONS_H_

/*
 * USB device definitions
 */
#define STRING_PRODUCT "Stimey SAMD21G18A (Bootloader Mode)"
#define USB_VID_HIGH   0x19
#define USB_VID_LOW    0x93
#define USB_PID_HIGH   0x00
#define USB_PID_LOW    0x0B

/*
 * If BOOT_DOUBLE_TAP_ADDRESS is defined the bootloader is started by
 * quickly tapping two times on the reset button.
 * BOOT_DOUBLE_TAP_ADDRESS must point to a free SRAM cell that must not
 * be touched from the loaded application.
 */
#define BOOT_DOUBLE_TAP_ADDRESS           (0x20007FFCul)
#define BOOT_DOUBLE_TAP_DATA              (*((volatile uint32_t *) BOOT_DOUBLE_TAP_ADDRESS))

/*
 * If BOOT_LOAD_PIN is defined the bootloader is started if the selected
 * pin is tied LOW.
 */
//#define BOOT_LOAD_PIN                     PIN_PA21 // Pin 7
//#define BOOT_LOAD_PIN                     PIN_PA15 // Pin 5

// - Import from arduino mkrzero
#define BOOT_USART_MODULE                 SERCOM5
#define BOOT_USART_BUS_CLOCK_INDEX        PM_APBCMASK_SERCOM5
#define BOOT_USART_PER_CLOCK_INDEX        GCLK_CLKCTRL_ID_SERCOM5_CORE_Val
#define BOOT_USART_PAD_SETTINGS           UART_RX_PAD3_TX_PAD2
#define BOOT_USART_PAD3                   PINMUX_PB23D_SERCOM5_PAD3
#define BOOT_USART_PAD2                   PINMUX_PB22D_SERCOM5_PAD2
#define BOOT_USART_PAD1                   PINMUX_UNUSED
#define BOOT_USART_PAD0                   PINMUX_UNUSED
// - End import 

/* Master clock frequency */
#define CPU_FREQUENCY                     (48000000ul)
#define VARIANT_MCK                       CPU_FREQUENCY

/* Frequency of the board main oscillator */
#define VARIANT_MAINOSC                   (32768ul)

/* Calibration values for DFLL48 pll */
#define NVM_SW_CALIB_DFLL48M_COARSE_VAL   (58)
#define NVM_SW_CALIB_DFLL48M_FINE_VAL     (64)

/*
 * LEDs definitions
 */
// LED_BUILTIN PORT0.PIN5 = PA05 = A4 = Pinout 26
#define BOARD_LED_PORT                    (0)
#define BOARD_LED_PIN                     (5)

// LED_RX PORT1.3 = PB03 = Pinout 48
#define BOARD_LEDRX_PORT                  (1)
#define BOARD_LEDRX_PIN                   (3)

// LED_TX PORT0.27 = PA27 = Pinout 39 
#define BOARD_LEDTX_PORT                  (0)
#define BOARD_LEDTX_PIN                   (27)

#endif // _BOARD_DEFINITIONS_H_
