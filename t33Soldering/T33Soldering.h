/*
 * soldering.h
 *
 *  Created on: Apr 21, 2022
 *      Author: mannk
 */

#ifndef SOLDERING_H_
#define SOLDERING_H_

#include <avr/io.h>
//#include <stdlib.h>    for abs() function, but it wrong.

//#define my_abs(xK) (((xK) >= 0) ? (xK) : -(xK) )

//uint16_t volToTemp(uint16_t adc_value);

float volToTemp(uint16_t adc_value);

#endif /* SOLDERING_H_ */
