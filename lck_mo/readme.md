# lck75

A 75% keyboard that can be assembled with only through hole components, including usb type-c

* Keyboard Maintainer: [Lyso1](https://github.com/lyso1)
* Hardware Supported: LCK75, atmega32
* Hardware Availability: [GitHub](https://github.com/lyso1)

Make example for this keyboard (after setting up your build environment):

    make lyso1/lck75:default

Flashing example for this keyboard:

    make lyso1/lck75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).



Added : 
- Two new animations OLED LCD Animations.
   -  Monty Python's French Taunting
   - One Piece Ship
   - Nami One Piece Oled Animation
- Hotkeys to swap between them
   - Mod + PAGE_UP => view next animation
   - Mod + PAGE_DOWN => view previous animation

LCK75R2 Fixed : 
 - Rotary Encoder Volume won't stop going up on mac / linux
 - Rotary Encoder won't control volume
 - Caps Lock doesn't work without modifier key
