/*
 * soldering.c
 *
 *  Created on: Apr 21, 2022
 *      Author: mannk
 */

#include "typeK.h"

// voltage mV
#define VOLTAGE_AT_190 7.739
#define VOLTAGE_AT_270 10.971
#define VOLTAGE_AT_350 14.293

// have offset because of Opam-Config(cau hinh doi hoi offset).
/*
#define OFFSET_under190	25
#define OFFSET_190to270	32
#define OFFSET_270to350 23
#define OFFSET_over350 19
*/
#define OFFSET_under190	0
#define OFFSET_190to270	0
#define OFFSET_270to350 0
#define OFFSET_over350 0

/*
static float my_abs(float xK);
static float my_pow(float x, uint8_t n);
static float findNthRoot(float x, uint8_t n);

static float my_abs(float xK){
    if(xK >= 0 ) return xK;
    return -xK;
}


static float my_pow(float x, uint8_t n){
	float result = 1;
	for(uint8_t i = 0; i<n; i++){
		result *= x;
	}
	return result;
}


static float findNthRoot(float x, uint8_t n){					// USE quick sort -> use this, it take 3.2ms on Atmega8 16MHZ
    // Initialize boundary values
    float low, high;
    if (x >= 0 && x <= 1){
        low = x;
        high = 1;
    }
    else{
        low = 1;
        high = x;
    }
    // Used for taking approximations
    // of the answer
    float epsilon = 0.1;		// xac dinh do chinh xac	// 0.000001 for more accurate

    // Do binary search
    float guess = (low + high) / 2;
    while (my_abs((my_pow(guess, n)) - x) >= epsilon)
    {
        if (my_pow(guess, n) > x){
            high = guess;
        }
        else{
            low = guess;
        }
        guess = (low + high) / 2;
    }
 	return guess;
}

uint16_t volToTemp(uint16_t adc_value){		// USE quick sort
	uint16_t temp;
	//temp = 207*nthRoot((float)adc_value, 5) - 450;
	temp = 207*findNthRoot((float)adc_value, 5) - 422;
	return temp;
}


//////////////////////////////////////////////////////////////////////
 *
 */


/*
float nthRoot(float A, uint8_t N){
    // initially guessing a random number between
    // 0 and 9
    //double xPre = rand() % 10;
    float xPre  = 100;
    //  smaller eps, denotes more accuracy
    float eps = 1e-3;
    // initializing difference between two
    // roots by INT_MAX
    float delX = 2147483648;

    //  xK denotes current value of x
    float xK;

    //  loop until we reach desired accuracy
    while (delX > eps){
        //  calculating current value from previous4.321
        // value by newton's method
        xK = ((N - 1.0) * xPre + (float)A/my_pow(xPre, N-1)) / (float)N;
        delX = my_abs(xK - xPre);
        xPre = xK;VOLTAGE_AT_190
    }
    return xK;
}
*/

/*
uint16_t volToTemp1(uint16_t adc_value){		// 207*(adc_value)^0.2 - 450
	uint16_t temp;
	temp = 207*nthRoot((float)adc_value, 5) - 450;
	//temp = 207*findNthRoot((double)adc_value, 5) - 450;
	return temp;
}*/


float volToTemp(uint16_t adc_value){					// Thermocouple type C
	float realTemp = 0;
	float thermoVoltage = adc_value*0.02237; 		// mV
	if(thermoVoltage == 0)
		return 0;	// error, wrong connect

	if( thermoVoltage > 0 && thermoVoltage <= VOLTAGE_AT_190){				// thermo voltage lower than reality
		realTemp = 24.95* thermoVoltage - 3.12 + OFFSET_under190;
	}
	else if(thermoVoltage > VOLTAGE_AT_190 && thermoVoltage <= VOLTAGE_AT_270){
		realTemp = 24.7* thermoVoltage - 0.97 + OFFSET_190to270;
	}
	else if(thermoVoltage > VOLTAGE_AT_270 && thermoVoltage <= VOLTAGE_AT_350){
		realTemp = 24.1* thermoVoltage + 9.67 + OFFSET_270to350;
	}
	else if(thermoVoltage >  VOLTAGE_AT_350 ){
		realTemp =  23.8* thermoVoltage + 44.68 + OFFSET_over350;
	}

	return realTemp;
}


// 50 -> 190: temp = 	62.9832x + 7.73879 (x = (ADCval*(1.074))/150)
// 190 -> 270: temp = 57.0686x + 23.74
// 270 -> 350: temp = 54.4695x + 34.88
// 350 -> 420: temp = 52.7697x + 44.675

