/*
 * led7seg.c
 *
 *  Created on: Jul 25, 2022
 *      Author: mannk
 */

#include "led7seg.h"

const uint8_t Led7seg[10] = {		// 0 to 9
		B11000000, //0
				B11001111, //1
				B10100100, //2
				B10110000, //3
				B10011001, //4
				B10010010, //5
				B10000010, //6
				B11111000, //7
				B10000000, //8
				B10010000  //9
		};

void sevenSegInit() {
	spiInitMaster(SPI_CLOCK_DIV128, MSBFIRST, MASTERNOISR);// clk_div = 128 for long_time display each digits
}

// 321	3 -> 2 -> 1, right -> B00001000 <- left	// this funtion and old shiftout(use digitalWrite) take 2.5ms for 4digit display
// this function use spi, take only 512us for 4 digits
void sevenSegDisplay(uint16_t value, uint8_t mode) {
	uint8_t common = B00001000;

	switch (mode) {
	case SLEEP_MODE:
		while (common) {
			SLAVE_SELECT;
			spiTradeByte(common);
			spiTradeByte(B10111111);
			SLAVE_DESELECT;
			common = common >> 1;
		}
		break;
	case DEFAULT:
		if (value == 0) {
			SLAVE_SELECT;
			spiTradeByte(common);
			spiTradeByte(Led7seg[value]);
			SLAVE_DESELECT;
		} else {
			while (value) {
				SLAVE_SELECT;
				spiTradeByte(common);
				spiTradeByte(Led7seg[value % 10]);
				SLAVE_DESELECT;
				common = common >> 1;
				value /= 10;
				//SLAVE_DESELECT;
			}
		}
		break;
	case CHOSE_MODE:
		SLAVE_SELECT;
		spiTradeByte(B00000001);
		spiTradeByte(B11110111);
		SLAVE_DESELECT;
		if (value == 0) {
			SLAVE_SELECT;
			spiTradeByte(common);
			spiTradeByte(Led7seg[value]);
			SLAVE_DESELECT;
		} else {
			while (value) {
				SLAVE_SELECT;
				spiTradeByte(common);
				spiTradeByte(Led7seg[value % 10]);
				SLAVE_DESELECT;
				common = common >> 1;
				value /= 10;
			}
		}
		break;
	case TEMP_MATCH:
		SLAVE_SELECT;
		spiTradeByte(B00000001);
		spiTradeByte(B01111111);
		SLAVE_DESELECT;
		if (value == 0) {
			SLAVE_SELECT;
			spiTradeByte(common);
			spiTradeByte(Led7seg[value]);
			SLAVE_DESELECT;
		} else {
			while (value) {
				SLAVE_SELECT;
				spiTradeByte(common);
				spiTradeByte(Led7seg[value % 10]);
				SLAVE_DESELECT;
				common = common >> 1;
				value /= 10;
			}
		}
		break;
	}
// turn off all led
	SLAVE_SELECT;
	spiTradeByte(B00000000);
	spiTradeByte(B11111111);
	SLAVE_DESELECT;
}

void sevenSegIsrDisplay(uint16_t value, uint8_t mode) {
	uint8_t common = B00001000;

	switch (mode) {
	case SLEEP_MODE:
		while (common) {
			//SLAVE_SELECT;
			spiTradeByteISR(common);
			spiTradeByteISR(B10111111);
			//SLAVE_DESELECT;
			common = common >> 1;
		}
		break;
	case DEFAULT:
		if (value == 0) {
			SLAVE_SELECT;
			spiTradeByteISR(common);
			spiTradeByteISR(Led7seg[value]);
			SLAVE_DESELECT;
		} else {
			while (value) {
				SLAVE_SELECT;
				spiTradeByteISR(common);
				spiTradeByteISR(Led7seg[value % 10]);
				SLAVE_DESELECT;
				common = common >> 1;
				value /= 10;
				//SLAVE_DESELECT;
			}
		}
		break;
	case CHOSE_MODE:
		SLAVE_SELECT;
		spiTradeByteISR(B00000001);
		spiTradeByteISR(B11110111);
		SLAVE_DESELECT;
		if (value == 0) {
			SLAVE_SELECT;
			spiTradeByteISR(common);
			spiTradeByteISR(Led7seg[value]);
			SLAVE_DESELECT;
		} else {
			while (value) {
				SLAVE_SELECT;
				spiTradeByteISR(common);
				spiTradeByteISR(Led7seg[value % 10]);
				SLAVE_DESELECT;
				common = common >> 1;
				value /= 10;
			}
		}
		break;
	case TEMP_MATCH:
		SLAVE_SELECT;
		spiTradeByteISR(B00000001);
		spiTradeByteISR(B01111111);
		SLAVE_DESELECT;
		if (value == 0) {
			SLAVE_SELECT;
			spiTradeByteISR(common);
			spiTradeByteISR(Led7seg[value]);
			SLAVE_DESELECT;
		} else {
			while (value) {
				SLAVE_SELECT;
				spiTradeByteISR(common);
				spiTradeByteISR(Led7seg[value % 10]);
				SLAVE_DESELECT;
				common = common >> 1;
				value /= 10;
			}
		}
		break;
	}
// turn off all led
	SLAVE_SELECT;
	spiTradeByteISR(B00000000);
	spiTradeByteISR(B11111111);
	SLAVE_DESELECT;
}

