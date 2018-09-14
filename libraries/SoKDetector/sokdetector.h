#pragma once

// SoK Detector
// VIN = 5V
// |
// R1 = 5.1 Kohms
// |
// *------ VOUT 
// |
// R2 = {220ohms GameSoK / 510ohms DriveSok}
// |
// GND 
// 
// VOUT = R2 / (R1+R2) * VIN
//
/* 
#define deviation 10
#define vout(R1, R2) ((R2 / (R1+R2) * 5)
#define aout(vout) (vout * ares / 3.3)
*/

/*
 * Sok Selector principles, based on Hanazuki Trasures Band.
 * Detects in which type of hardware is mounted.
 * 
 * VIN =  5V
 * |
 * w
 * w R1, FIXED = 5K Ohms
 * |
 * + - - - A8 (SoK Selector) (Maximum 3.3v)
 * |
 * w
 * w R2, VARIABLE on each device. (Maximum 10K Ohms).
 * |
 * GND
 * 
 * Typical Deviation: 10..20
 * 
 *           Theorical
 * R2         Voltage   AnalogRead
 * 10K Ohms    3.3v     1023
 * 5K Ohms     2.5v     783 
 * 1K Ohm      0.833v   279
 * 550 Ohms    0.495v   172         <- Drive SoK
 * 220 Ohms    0.210v   80          <- Game SoK
 * GND         0v       0         
 */

#include <Arduino.h>

#define DEVIATION            25    // Standard deviation for selection
#define RESISTANCE_MAIN     5100  // Ohms (R1)
#define RESISTANCE_GAMESOK  220   // Ohms (R2)
#define RESISTANCE_DRIVESOK 510   // Ohms (R2)



int calculateAnalogValue (float VIN, float R1, float R2, int adcResolution, float MAX_VOUT);

int determineBoard (int pin, int adcResolution);