#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define CRYSTALLESS 1

#define VENDOR_NAME "NeKuNeKo Inc."
#define PRODUCT_NAME "Kitten Syringe (SAMD21E18A)"
#define VOLUME_LABEL "KSYRNG-BOOT"
#define INDEX_URL "https://github.com/nekuneko/"
#define BOARD_ID "SAMD21E18A-Kitten-Syringe"

#define USB_VID 0x1993
#define USB_PID 0xB002

#define LED_PIN PIN_PA16

#define BOARD_NEOPIXEL_PIN PIN_PA18
#define BOARD_NEOPIXEL_COUNT 1

// SerialSOK on Wire Interface (Serial Over I2C)
#define BOOT_USART_MODULE SERCOM3
#define BOOT_USART_PAD_SETTINGS UART_RX_PAD1_TX_PAD0
#define BOOT_USART_PAD3 PINMUX_UNUSED
#define BOOT_USART_PAD2 PINMUX_UNUSED
#define BOOT_USART_PAD1 PINMUX_PA23C_SERCOM3_PAD1
#define BOOT_USART_PAD0 PINMUX_PA22C_SERCOM3_PAD0

#endif // BOARD_CONFIG_H
