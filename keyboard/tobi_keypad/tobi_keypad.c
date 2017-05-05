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

 

#include "actionmap.h"
#include "action_code.h"
#include "keymap.h"
#include "tobi_keypad.h"
#include "action_layer.h"
#include <string.h>
#include "debug.h"
#include "report.h"
#include "host.h"
#include "wait.h"
#include "print.h"

// ACTION DEFINITIONS ----------------------------------------------------------------------------------------

//	#define ACTION_KEY_2	
	#define AC_LAY0		ACTION_LAYER_SET_CLEAR(0)
	#define AC_JPKP		ACTION_LAYER_TOGGLE(1)
	#define AC_ENKP		ACTION_LAYER_TOGGLE(2)
	#define AC_GAMW		ACTION_LAYER_SET_CLEAR(28)
	#define AC_GAMA		ACTION_LAYER_SET_CLEAR(29)
	#define AC_LAYR		ACTION_LAYER_MOMENTARY(30)	
	#define AC_MAGI		ACTION_LAYER_TAP_KEY(31, KC_PENT)	
	#define AC_MAKI		ACTION_MODS(MOD_LALT | MOD_LSFT)	

	#define AC_FPSC		ACTION_FUNCTION(FPSC)
	#define AC_FPBK		ACTION_FUNCTION(FPBK)
	#define AC_FPSF		ACTION_FUNCTION(FPSF)
	#define AC_FPEN		ACTION_FUNCTION(FPEN)
	#define AC_ENK1		ACTION_FUNCTION(ENK1)
	#define AC_ENK2		ACTION_FUNCTION(ENK2)
	#define AC_ENK3		ACTION_FUNCTION(ENK3)
	#define AC_ENK4		ACTION_FUNCTION(ENK4)
	#define AC_ENK5		ACTION_FUNCTION(ENK5)
	#define AC_ENK6		ACTION_FUNCTION(ENK6)
	#define AC_ENK7		ACTION_FUNCTION(ENK7)
	#define AC_ENK8		ACTION_FUNCTION(ENK8)
	#define AC_ENK9		ACTION_FUNCTION(ENK9)

int global_prev = 999;
int global_tap_count = 0;
FPKPSC[] =	{KC_SPACE};
FPKPBK[] =	{KC_BSPACE};
FPKPSF[] =	{KC_LSFT};
FPKPEN[] =	{KC_ENTER};
ENKP1[] =	{};
ENKP2[] =	{KC_A, KC_B, KC_C};
ENKP3[] =	{KC_D, KC_E, KC_F};
ENKP4[] =	{KC_G, KC_H, KC_I};
ENKP5[] =	{KC_J, KC_K, KC_L};
ENKP6[] =	{KC_M, KC_N, KC_O};
ENKP7[] =	{KC_P, KC_Q, KC_R, KC_S};
ENKP8[] =	{KC_T, KC_U, KC_V};
ENKP9[] =	{KC_W, KC_X, KC_Y, KC_Z};
// SET FUNCTION IDs ------------------------------------------------------------------------------------------

enum fucntion_id{
	FPSC, FPBK, FPSF, FPEN,			\
	ENK1, ENK2, ENK3,			\
	ENK4, ENK5, ENK6,			\
	ENK7, ENK8, ENK9,			\
};

// FUNCTION DEFINITIONS --------------------------------------------------------------------------------------

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	dprintf("id = %d", id);
	if (id == FPSC){
		flipprev(FPSC);
		global_tap_count = 0;
		flipkey(record, FPKPSC);
	} 
	else if (id == FPBK){
		flipprev(FPBK);
		global_tap_count = 0;
		flipkey(record, FPKPBK);
	} 
	else if (id == FPSF){
		flipprev(FPSF);
		global_tap_count = 0;
		flipkey(record, FPKPSF);
	} 
	else if (id == FPEN){
		flipprev(FPEN);
		global_tap_count = 0;
		flipkey(record, FPKPEN);
	} 
	else if (id == ENK1){
		flipprev(ENK1);
		flipkey(record, ENKP1);
	} 
	else if (id == ENK2){
		flipprev(ENK2);
		flipkey(record, ENKP2);
	} 
	else if (id == ENK3){
		flipprev(ENK3);
		flipkey(record, ENKP3);
	} 
	else if (id == ENK4){
		flipprev(ENK4);
		flipkey(record, ENKP4);
	} 
	else if (id == ENK5){
		flipprev(ENK5);
		flipkey(record, ENKP5);
	} 
	else if (id == ENK6){
		flipprev(ENK6);
		flipkey(record, ENKP6);
	} 
	else if (id == ENK7){
		flipprev(ENK7);
		flipkey(record, ENKP7);
	} 
	else if (id == ENK8){
		flipprev(ENK8);
		flipkey(record, ENKP8);
	} 
	else if (id == ENK9){
		flipprev(ENK9);
		flipkey(record, ENKP9);
	} 

};

void flipprev(int current){
	dprintf("global: %d, current: %d \n", global_prev, current);
	if (global_prev == 999){
		global_prev = current;
	}
	else if (global_prev != current)
	{
		global_prev = current;
		global_tap_count = 0;
	}
	dprintf("global: %d, current: %d \n", global_prev, current);
}

void flipkey(keyrecord_t *record, int arr[]){
	if (record->event.pressed){
		dprintf("%d\n%d\n",global_tap_count, sizeof(arr));
		if (global_tap_count > sizeof(arr))
		{
			
			add_key(KC_BSPACE);
			send_keyboard_report();
			del_key(KC_BSPACE);
			send_keyboard_report();
			global_tap_count = 0;
			dprintf("globalcount: %d", global_tap_count);
			
		}
		if (global_tap_count == 0){
			
			add_key(arr[global_tap_count]);
			send_keyboard_report();
			del_key(arr[global_tap_count]);
			send_keyboard_report();
			
		}
		else
		{
			add_key(KC_BSPACE);
			add_key(arr[global_tap_count]);
			send_keyboard_report();
			del_key(KC_BSPACE);
			del_key(arr[global_tap_count]);
			send_keyboard_report();

		}

		if (global_tap_count <= sizeof(arr))
		{
			global_tap_count++;
		}
	}

}

// KEYBOARD ACTION MAP LAYERS --------------------------------------------------------------------------------


const action_t PROGMEM actionmaps[][MATRIX_ROWS][MATRIX_COLS] = {

// LAYER 0: ---------------------\
      ,-------------------.      \
      |                   |      \
      |                   |      \
      | ,---------------. |      \
      | |NUM| / | * | - | |      \
      | |---------------| |      \
      | | 7 | 8 | 9 | + | |      \
      | |---------------| |      \
      | | 4 | 5 | 6 |PGU| |      \
      | |---------------| |      \
      | | 1 | 2 | 3 |PGD| |      \
      | |---------------| |      \
      | | 0 |BS | . |ENT| |      \
      | `---------------' |      \
      `-------------------'      \
                                  
  [0] = ACTIONMAP_tobi_keypad(   \
    NLCK,PSLS,PAST,PMNS,         \
    P7,  P8,  P9,  PPLS,         \
    P4,  P5,  P6,  ENKP,         \
    P1,  P2,  P3,  LAYR,         \
    P0,  BSPC,PDOT,MAGI),        

// LAYER 1: ---------------------\
      ,-------------------.      \
      |                   |      \
      |                   |      \
      | ,---------------. |      \
      | |NUM| / | * | - | |      \
      | |---------------| |      \
      | | 7 | 8 | 9 | + | |      \
      | |---------------| |      \
      | | 4 | 5 | 6 |PGU| |      \
      | |---------------| |      \
      | | 1 | 2 | 3 |PGD| |      \
      | |---------------| |      \
      | | 0 |BS | . |ENT| |      \
      | `---------------' |      \
      `-------------------'      \
                                  
  [1] = ACTIONMAP_tobi_keypad(   \
    NLCK,PSLS,PAST,PMNS,         \
    P7,  P8,  P9,  PPLS,         \
    P4,  P5,  P6,  TRNS,         \
    P1,  P2,  P3,  PGDN,         \
    FPSC,FPBK,PDOT,PENT),        

// LAYER 2: ---------------------\
      ,-------------------.      \
      |                   |      \
      |                   |      \
      | ,---------------. |      \
      | |NUM| / | * | - | |      \
      | |---------------| |      \
      | | 7 | 8 | 9 | + | |      \
      | |---------------| |      \
      | | 4 | 5 | 6 |PGU| |      \
      | |---------------| |      \
      | | 1 | 2 | 3 |PGD| |      \
      | |---------------| |      \
      | | 0 |BS | . |ENT| |      \
      | `---------------' |      \
      `-------------------'      \
                                  
  [2] = ACTIONMAP_tobi_keypad(   \
    NLCK,PSLS,PAST,PMNS,         \
    ENK1,ENK2,ENK3,PPLS,         \
    ENK4,ENK5,ENK6,TRNS,         \
    ENK7,ENK8,ENK9,FPSF,         \
    FPSC,FPBK,PDOT,FPEN),        

// LAYER 28: ---------------------\
      ,-------------------.      \
      |                   |      \
      |                   |      \
      | ,---------------. |      \
      | |NUM| / | * | - | |      \
      | |---------------| |      \
      | | 7 | 8 | 9 | + | |      \
      | |---------------| |      \
      | | 4 | 5 | 6 |PGU| |      \
      | |---------------| |      \
      | | 1 | 2 | 3 |PGD| |      \
      | |---------------| |      \
      | | 0 |BS | . |ENT| |      \
      | `---------------' |      \
      `-------------------'      \
                                  
  [28] = ACTIONMAP_tobi_keypad(  \
    1,   2,   3,   4,            \
    ESC, Q,   W,   R,            \
    F,   A,   S,   D,            \
    LSFT,NO,  NO,  C,            \
    NO,  GAMA,LAY0,SPC),        

// LAYER 29: ---------------------\
      ,-------------------.      \
      |                   |      \
      |                   |      \
      | ,---------------. |      \
      | |NUM| / | * | - | |      \
      | |---------------| |      \
      | | 7 | 8 | 9 | + | |      \
      | |---------------| |      \
      | | 4 | 5 | 6 |PGU| |      \
      | |---------------| |      \
      | | 1 | 2 | 3 |PGD| |      \
      | |---------------| |      \
      | | 0 |BS | . |ENT| |      \
      | `---------------' |      \
      `-------------------'      \
                                  
  [29] = ACTIONMAP_tobi_keypad(  \
    1,   2,   3,   4,            \
    ESC, UP,  NO,  NO,           \
    LEFT,DOWN,RGHT,NO,           \
    NO,  NO,  NO,  NO,           \
    SPC, GAMW,LAY0,NO),        

// LAYER 30: ---------------------\
      ,-------------------.      \
      |                   |      \
      |                   |      \
      | ,---------------. |      \
      | |NUM| / | * | - | |      \
      | |---------------| |      \
      | | 7 | 8 | 9 | + | |      \
      | |---------------| |      \
      | | 4 | 5 | 6 |PGU| |      \
      | |---------------| |      \
      | | 1 | 2 | 3 |PGD| |      \
      | |---------------| |      \
      | | 0 |BS | . |ENT| |      \
      | `---------------' |      \
      `-------------------'      \
                                  
  [30] = ACTIONMAP_tobi_keypad(  \
    NO,  NO,  NO,  NO,           \
    GAMW,GAMA,NO,  NO,           \
    NO,  NO,  NO,  NO,           \
    NO,  NO,  NO,  TRNS,         \
    NO,  NO,  NO,  NO),        

// LAYER 31: ---------------------\
      ,-------------------.      \
      |                   |      \
      |                   |      \
      | ,---------------. |      \
      | |NUM| / | * | - | |      \
      | |---------------| |      \
      | | 7 | 8 | 9 | + | |      \
      | |---------------| |      \
      | | 4 | 5 | 6 |PGU| |      \
      | |---------------| |      \
      | | 1 | 2 | 3 |PGD| |      \
      | |---------------| |      \
      | | 0 |BS | . |ENT| |      \
      | `---------------' |      \
      `-------------------'      \
                                  
  [31] = ACTIONMAP_tobi_keypad(  \
    NO,  NO,  NO,  NO,           \
    NO,  Q,   H,   NO,           \
    NO,  D,   C,   K,            \
    NO,  NO,  NO,  NO,           \
    MAKI,NO,  NO,  MAGI),        

};
