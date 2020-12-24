# RotaryEncoder library New Generation

A library for the Arduino environment for using a rotary encoder as an input.

Here you can find an Arduino compatible library for using rotary encoders.

I was using the Mathertel library but didn't convice, so I've decided to create my own with my wanted requirements. The start point was the Mathertel library, so this one is fully compatible with the projects made using its library, although I have rewritten the whole library.

It supports the type of rotary encoder that has a phase change on both input signals when rotating one `notch`.

I'll add a post talking about this library on my site in the future:

<https://www.electrosoftcloud.com>

## Changelog

### 1.0.0
* First version
* Made and tested in the ALPSALPINE EC11E15244G1 rotary encoder
* Detects the direction using the pin states
* Added a "Direction Debounce" option to avoid false direction changes. The dissavantage is that needs two ticks to change the direction when activated.
* Can use the analog pins
* The acceleration example is now part of the library, so you can set the acceleration using the set function instead calculate it.