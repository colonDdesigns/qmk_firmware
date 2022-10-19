// Copyright 2022 Seth Daly (@sethldaly)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCB9A
#define PRODUCT_ID      0x0461
#define DEVICE_VER      0x0001
#define MANUFACTURER    :D Designs
#define PRODUCT         Doza

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 2

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { D7, C0 }
#define MATRIX_COL_PINS { C2, C1 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

//#define DIRECT_PINS { {A0, A1}, {A2, A3} }

#define ENCODERS_PAD_A { A0 }
#define ENCODERS_PAD_B { A1 }


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

