/*
 * my_encoder.c
 *
 *  Created on: Apr 1, 2022
 *      Author: mannk
 */

#include "encoder.h"

//uint16_t counter;

void encoderInit(encoder *self, uint8_t pinA, uint8_t pinB) {

	self->pinA = pinA;
	self->pinB = pinB;
	self->count = 0;
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);
	self->pre_pinA_State = digitalRead(self->pinA);

}

// volatile help change it value inside Interrupt
void encoderCheck(encoder *self, void *counter) { // pass address of itself
	uint8_t pinA_State, pinB_State;
	pinA_State = digitalRead(self->pinA);
	pinB_State = digitalRead(self->pinB);
	int *p;

	if (pinA_State != self->pre_pinA_State) {
		if (pinA_State == pinB_State) {
			self->count++;
			if (self->count == 2) {
				p = (int*) counter;
				(*p)++;
				self->count = 0;
			}
		} else {
			self->count++;
			if (self->count == 2) {
				(*((int*) counter))--;
				//(*p)--;
				self->count = 0;
			}
		}
		self->pre_pinA_State = pinA_State;
	}

	//return *counter;
}

