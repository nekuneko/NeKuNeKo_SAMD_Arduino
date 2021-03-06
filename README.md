# Arduino Core for NeKuNeKo's SAMD21 and SAMD51 MCU boards based on Adafruit SAMD21 & SAMD51 Boards

This repository contains the source code and configuration files of the Arduino Core
for Atmel's SAMD21 and SAMD51 processor (used on the Arduino/Genuino Zero, MKR1000 and MKRZero boards).

## Supported boards

* SoK Zero Dawn (ATSAMD21J18A)
* SoK M4 Advance (ATSAMD51J20A)
* Kitten Syringe (ATSAMD21E18A)
* Kitten Display (ATSAMD21E18A)

## Installation on Arduino IDE

To add board support, start Arduino and open the Preferences window (**File** > **Preferences**). Now copy and paste the following URL into the 'Additional Boards Manager URLs' input field:

    https://nekuneko.github.io/arduino-board-index/package_nekuneko_index.json

If there is already an URL from another manufacturer in that field, click the button at the right end of the field. This will open an editing window allowing you to plaste the above URL onto a new line.

After that, this core will be available as a package in the Arduino IDE cores manager.
Just open the (**Tools** > **Board** > **Boards Manager**) and install the package called:

**NekuNeko SAMD Boards (32-bit ARM Cortex-M0+)**



## Support

There is a dedicated section of the Arduino Forum for general discussion and project assistance:

http://forum.arduino.cc/index.php?board=98.0

## Bugs or Issues

* AREF must be tied to 3.3V for dac to work. This is a bug in the SAMD51 silicon.
* USB host mode doesn't work yet


If you find a bug you can submit an issue here on github:

https://github.com/nekuneko/NekuNeko_Arduino_Boards/issues

Before posting a new issue, please check if the same problem has been already reported by someone else
to avoid duplicates.

## Contributions

Contributions are always welcome. The preferred way to receive code cotribution is by submitting a 
Pull Request on github.

## License and credits

This core has been developed by Arduino LLC in collaboration with Atmel.

```
  Copyright (c) 2015 Arduino LLC.  All right reserved.

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
```
