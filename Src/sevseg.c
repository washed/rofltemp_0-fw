/*
 * sevseg.c
 *
 *  Created on: 17.04.2017
 *      Author: washed
 */

#include "stm32l4xx_hal.h"
#include "sevseg.h"
#include "MAX31865.h"

const uint32_t sevSegSymbolArray[SEVSEG_SYMBOLS] = {
		( ~SEVSEG_GPIO_CAT_MASK | (SEVSEG_GPIO_CAT_MASK >> 16) ),
		( ~(SEVSEG_TOP | SEVSEG_BOT | SEVSEG_TOP_LEFT | SEVSEG_TOP_RIGHT | SEVSEG_BOT_LEFT | SEVSEG_BOT_RIGHT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP_RIGHT | SEVSEG_BOT_RIGHT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP | SEVSEG_TOP_RIGHT | SEVSEG_MID | SEVSEG_BOT_LEFT | SEVSEG_BOT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP | SEVSEG_TOP_RIGHT | SEVSEG_MID | SEVSEG_BOT_RIGHT | SEVSEG_BOT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP_LEFT | SEVSEG_MID | SEVSEG_TOP_RIGHT | SEVSEG_BOT_RIGHT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP | SEVSEG_TOP_LEFT | SEVSEG_MID | SEVSEG_BOT_RIGHT | SEVSEG_BOT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP | SEVSEG_TOP_LEFT | SEVSEG_MID | SEVSEG_BOT_LEFT | SEVSEG_BOT | SEVSEG_BOT_RIGHT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP | SEVSEG_TOP_RIGHT | SEVSEG_BOT_RIGHT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP | SEVSEG_MID | SEVSEG_BOT | SEVSEG_TOP_LEFT | SEVSEG_TOP_RIGHT | SEVSEG_BOT_LEFT | SEVSEG_BOT_RIGHT) | SEVSEG_GPIO_CAT_MASK ),
		( ~(SEVSEG_TOP | SEVSEG_MID | SEVSEG_BOT | SEVSEG_TOP_LEFT | SEVSEG_TOP_RIGHT | SEVSEG_BOT_RIGHT) | SEVSEG_GPIO_CAT_MASK )
};

const uint32_t sevSegDigitArray[SEVSEG_DIGITS] = {
		( SEVSEG_DIG_0 | SEVSEG_GPIO_AN_MASK ),
		( SEVSEG_DIG_1 | SEVSEG_GPIO_AN_MASK ),
		( SEVSEG_DIG_2 | SEVSEG_GPIO_AN_MASK )
};

int8_t sevSegValue[SEVSEG_DIGITS] = {
		0,
		0,
		0,
};

static void setSevSegValue(uint16_t value);
static void WriteSevSegDigitFast( uint8_t digit, int8_t number );

static void setSevSegValue(uint16_t value)
{
if ( (value >= 0) && (value < 1000) )
{
	if ( value >= 100 )
	{
		sevSegValue[0] = value / 100;
		value = value % 100;
	}
	else
	{
		sevSegValue[0] = -1;
		value = value % 100;
	}

	if ( value >= 10 )
	{
		sevSegValue[1] = value / 10;
		value = value % 10;
	}
	else
	{
		sevSegValue[1] = 0;
		value = value % 10;
	}

	sevSegValue[2] = value;

}
}

void handleSevSeg()
{
  static uint32_t current_digit = 0;
  if ( display_update == 1 )
  {
    display_update = 0;
    setSevSegValue( averaged_RTD_temp / ( TEMP_INT_FACTOR / 10 ) );
	WriteSevSegDigitFast(current_digit, sevSegValue[current_digit] );
	if( ++current_digit >= SEVSEG_DIGITS) current_digit = 0;
  }
}

static void WriteSevSegDigitFast( uint8_t digit, int8_t number )
{
	if ( (number >= -1) && ( number < SEVSEG_SYMBOLS) && (digit >= 0) && (digit < SEVSEG_DIGITS) )
	  {
		  GPIOC->BSRR = (uint32_t)sevSegDigitArray[digit];
		  GPIOB->BSRR = (uint32_t)sevSegSymbolArray[number + 1];
	  }
}
