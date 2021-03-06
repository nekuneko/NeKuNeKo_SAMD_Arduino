#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define CRYSTALLESS    1

#define VENDOR_NAME "NeKuNeKo Inc."
#define PRODUCT_NAME "Game SoK Mini (SAMD51)"
#define VOLUME_LABEL "GAMESOKMINI"
#define INDEX_URL "https://github.com/nekuneko/"
#define BOARD_ID "SAMD51J19A-GAME-SOK-MINI"


#define USB_VID 0x1993
#define USB_PID 0x0226

#define LED_PIN PIN_PA19

#define BOARD_NEOPIXEL_PIN PIN_PB12
#define BOARD_NEOPIXEL_COUNT 5

#define BOARD_SCREEN 1

#define BOOT_USART_MODULE SERCOM0
#define BOOT_USART_MASK APBAMASK
#define BOOT_USART_BUS_CLOCK_INDEX MCLK_APBAMASK_SERCOM0
#define BOOT_USART_PAD_SETTINGS UART_RX_PAD2_TX_PAD0
#define BOOT_USART_PAD3 PINMUX_UNUSED
#define BOOT_USART_PAD2 PINMUX_PA06D_SERCOM0_PAD2
#define BOOT_USART_PAD1 PINMUX_UNUSED
#define BOOT_USART_PAD0 PINMUX_PA04D_SERCOM0_PAD0
#define BOOT_GCLK_ID_CORE SERCOM0_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW SERCOM0_GCLK_ID_SLOW


#define HAS_CONFIG_DATA 1


// This configuration data should be edited at https://microsoft.github.io/uf2/patcher/
// Just drop this file there.
// Alternatively, it can be also binary edited there after the bootloader is compiled.

#ifdef DEFINE_CONFIG_DATA
const uint32_t config_data[] = {
    /* CF2 START */
    513675505, 539130489, // magic
    75, 100,  // used entries, total entries
    1, 0x2f, // PIN_ACCELEROMETER_INT = PIN_D12
    2, 0x29, // PIN_ACCELEROMETER_SCL = PIN_SCL
    3, 0x28, // PIN_ACCELEROMETER_SDA = PIN_SDA
    4, 0x3e8, // PIN_BTN_A = P_1000
    5, 0x3e9, // PIN_BTN_B = P_1001
    10, 0xc, // PIN_FLASH_MISO = PIN_MISO
    11, 0xf, // PIN_FLASH_MOSI = PIN_MOSI
    12, 0xd, // PIN_FLASH_SCK = PIN_SCK
    13, 0x13, // PIN_LED = PIN_D14
    14, 0x24, // PIN_LIGHT = PIN_A5
    18, 0xc, // PIN_MISO = PA12
    19, 0xf, // PIN_MOSI = PA15
    20, 0x2c, // PIN_NEOPIXEL = PIN_D8
    21, 0x6, // PIN_RX = PA06
    23, 0xd, // PIN_SCK = PA13
    24, 0x29, // PIN_SCL = PB09
    25, 0x28, // PIN_SDA = PB08
    26, 0x2e, // PIN_SPEAKER_AMP = PIN_D11
    28, 0x4, // PIN_TX = PA04
    32, 0x1, // PIN_DISPLAY_SCK = PA01
    33, 0x1e, // PIN_DISPLAY_MISO = PA30
    34, 0x1f, // PIN_DISPLAY_MOSI = PA31
    35, 0x20, // PIN_DISPLAY_CS = PIN_A0
    36, 0x21, // PIN_DISPLAY_DC = PIN_A1
    37, 0xa0, // DISPLAY_WIDTH = 160
    38, 0x80, // DISPLAY_HEIGHT = 128
    39, 0x80, // DISPLAY_CFG0 = 0x80
    40, 0x12c2d, // DISPLAY_CFG1 = 0x12c2d
    41, 0x18, // DISPLAY_CFG2 = 0x18
    43, 0x23, // PIN_DISPLAY_RST = PIN_A3
    44, 0x22, // PIN_DISPLAY_BL = PIN_A2
    47, 0x3ec, // PIN_BTN_LEFT = P_1004
    48, 0x3ee, // PIN_BTN_RIGHT = P_1006
    49, 0x3ef, // PIN_BTN_UP = P_1007
    50, 0x3ed, // PIN_BTN_DOWN = P_1005
    51, 0x3ea, // PIN_BTN_MENU = P_1002
    59, 0x40, // SPEAKER_VOLUME = 64
    69, 0x3eb, // PIN_BTN_SOFT_RESET = P_1003
    70, 0x32, // ACCELEROMETER_TYPE = LIS3DH
    71, 0x26, // PIN_BTNMX_LATCH = PIN_A8
    72, 0x7, // PIN_BTNMX_CLOCK = PIN_D2
    73, 0x27, // PIN_BTNMX_DATA = PIN_A9
    74, 0x23, // PIN_BTN_MENU2 = PIN_A3
    75, 0x25, // PIN_BATTSENSE = PIN_A6
    100, 0x20, // PIN_A0 = PB00
    101, 0x21, // PIN_A1 = PB01
    102, 0x22, // PIN_A2 = PB02
    103, 0x23, // PIN_A3 = PB03
    104, 0x2, // PIN_A4 = PA02
    105, 0x24, // PIN_A5 = PB04
    106, 0x25, // PIN_A6 = PB05
    107, 0x8, // PIN_A7 = PA08
    108, 0x26, // PIN_A8 = PB06
    109, 0x27, // PIN_A9 = PB07
    150, 0x4, // PIN_D0 = PA04
    151, 0x6, // PIN_D1 = PA06
    152, 0x7, // PIN_D2 = PA07
    153, 0xb, // PIN_D3 = PA11
    154, 0xa, // PIN_D4 = PA10
    155, 0x9, // PIN_D5 = PA09
    156, 0x2a, // PIN_D6 = PB10
    157, 0x2d, // PIN_D7 = PB13
    158, 0x2c, // PIN_D8 = PB12
    159, 0x2b, // PIN_D9 = PB11
    160, 0x5, // PIN_D10 = PA05
    161, 0x2e, // PIN_D11 = PB14
    162, 0x2f, // PIN_D12 = PB15
    163, 0xe, // PIN_D13 = PA14
    164, 0x13, // PIN_D14 = PA19
    200, 0x5, // NUM_NEOPIXELS = 5
    204, 0x80000, // FLASH_BYTES = 0x80000
    205, 0x30000, // RAM_BYTES = 0x30000
    208, 0x19930226, // BOOTLOADER_BOARD_ID = 0x19930226
    209, 0x55114460, // UF2_FAMILY = ATSAMD51
    210, 0x20, // PINS_PORT_SIZE = PA_32
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* CF2 END */
};
#endif
#endif









