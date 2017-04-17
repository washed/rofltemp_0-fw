/*
 * sevseg.h
 *
 *  Created on: 17.04.2017
 *      Author: washed
 */

#ifndef SEVSEG_H_
#define SEVSEG_H_

extern volatile uint8_t display_update;

#define SEVSEG_SYMBOLS 11
#define SEVSEG_DIGITS 3

#define SEVSEG_GPIO_CAT_MASK 0xE4380000
#define SEVSEG_GPIO_AN_MASK 0x00070000

#define SEVSEG_DIG_0 0x00000001
#define SEVSEG_DIG_1 0x00000002
#define SEVSEG_DIG_2 0x00000004

#define SEVSEG_TOP 0x00000020
#define SEVSEG_MID 0x00000400
#define SEVSEG_BOT 0x00004000
#define SEVSEG_TOP_LEFT 0x00000010
#define SEVSEG_TOP_RIGHT 0x00000008
#define SEVSEG_BOT_LEFT 0x00008000
#define SEVSEG_BOT_RIGHT 0x00002000


void handleSevSeg();

#endif /* SEVSEG_H_ */
