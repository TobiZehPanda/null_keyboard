/*
Copyright 2017 Yuki Sakatoi A.K.A. [null] <null.bin.pc@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef CONFIG_H
#define CONFIG_H


// USB Device descriptor parameter
#define VENDOR_ID       0x2761
#define PRODUCT_ID      0x1ee1
#define DEVICE_VER      0x0001
#define MANUFACTURER    [null]
#define PRODUCT         Tobi Keypad
#define DESCRIPTION     Tobi Keypad

// matrix size 
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

// define if matrix has ghost
//#define MATRIX_HAS_GHOST

// Set tap speed in ms 
#define TAPPING_TERM 100

// Set number of taps required to toggle a key, 1=2 
#define TAPPING_TOGGLE 1

// Set 0 if debouncing isn't needed 
#define DEBOUNCE    5

// Lock layers, actions, macros, or custom functions behind global PIN/passcode. Configure in "pin.h"
//#define PIN_LOCK_ENABLE

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap 
//#define LOCKING_SUPPORT_ENABLE

// Locking resynchronize hack
//#define LOCKING_RESYNC_ENABLE

// key combination for command
#define IS_COMMAND() ( \
keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT)) \
)

// Enable action debug
#define DEBUG_ACTION



// Feature disable options ------------------------------------------------------------------------------------------

// disable debug print
    //#define NO_DEBUG

// disable print
    //#define NO_PRINT

// disable action features 
    //#define NO_ACTION_LAYER
    //#define NO_ACTION_TAPPING
    //#define NO_ACTION_ONESHOT
    //#define NO_ACTION_MACRO
    //#define NO_ACTION_FUNCTION



#endif
