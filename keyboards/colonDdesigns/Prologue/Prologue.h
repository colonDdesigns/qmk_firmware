// Copyright 2022 Seth Daly (@sethldaly)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      K3E, \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B,      K4D, K4E, \
    K50, K51, K52,           K55,                K59, K5A, K5B, K5C, K5D, K5E  \
) { \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, XXX, K3E }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, XXX, K4D, K4E }, \
    { K50, K51, K52, XXX, XXX, K45, XXX, XXX, XXX, K49, K4A, K4B, K4C, K4D, K4E }  \
}
