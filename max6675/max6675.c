/*
 * max6675.c
 *
 *  Created on: Jul 11, 2022
 *      Author: mannk
 */

#include "max6675.h"

uint8_t spiread(const max6675 self) {
	int i;
	uint8_t d = 0;

	for (i = 7; i >= 0; i--) {
		digitalWrite(self->sclk, LOW);
		delayMicroseconds(10);
		if (digitalRead(self->miso)) {
			// set the bit to 0 no matter what
			d |= (1 << i);
		}

		digitalWrite(self->sclk, HIGH);
		delayMicroseconds(10);
	}

	return d;
}

float readCel(const max6675 self) {
	uint16_t v;

	digitalWrite(self->cs, LOW);
	delayMicroseconds(10);

	v = self->spiread(self);
	v <<= 8;
	v |= spiread(self);

	digitalWrite(self->cs, HIGH);

	if (v & 0x4) {
		// uh oh, no thermocouple attached!
		return NAN;
		// return -100;
	}

	v >>= 3;

	return v * 0.25;
}

float readFah(const max6675 self) {
	return readCelsius() * 9.0 / 5.0 + 32;
}

max6675 newMax6675(uint8_t SCLK, uint8_t CS, uint8_t MISO) {
	max6675 self = (max6675) malloc(sizeof(struct MAX6675)); // return address of created struct

	self->cs = CS;
	self->sclk = SCLK;
	self->miso = MISO;

	self->spiread = &spiread;
	self->readCel = &readCel;
	self->readFah = &readFah;

	// define pin modes
	pinMode(self->cs, OUTPUT);
	pinMode(self->sclk, OUTPUT);
	pinMode(self->miso, INPUT);

	digitalWrite(self->cs, HIGH);

	return self;
}

