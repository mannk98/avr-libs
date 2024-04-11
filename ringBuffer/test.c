/*
 ============================================================================
 Name        : test-ringbuffer(array).c
 Author      : mannk
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ringbuff.h"

void ringBuff_show(ringBuff *self);

int main(void) {
	ringBuff my_ringbuff;
	uint8_t a;
	//char b[6] = { 9, 8, 7, 6, 5, 4 };
	char *b = "we are thee";
	char out[10];

	ringBuff_init(&my_ringbuff, 16);

	ringBuff_put(&my_ringbuff, 'a');
	ringBuff_put(&my_ringbuff, 'b');
	ringBuff_put(&my_ringbuff, 'c');
	ringBuff_put(&my_ringbuff, '3');
	ringBuff_put(&my_ringbuff, 'f');

	ringBuff_putString(&my_ringbuff, b);

	ringBuff_show(&my_ringbuff);

	printf("stringBuffer get: \n");
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);
	printf("%c\n", a);

	// test getBytes
	ringBuff_getBytes(&my_ringbuff, out, 6);
	for (int i=0; i<10; i++){
		printf("%c ", out[i]);
	}
	printf("\n");

	printf("buffer after free: \n");
	ringBuff_free(&my_ringbuff);

	a = ringBuff_get(&my_ringbuff);	// return NULL
	printf("%c\n", a);
	a = ringBuff_get(&my_ringbuff);	// return NULL
	printf("%c\n", a);

	ringBuff_show(&my_ringbuff);
	//ringBuff_show(my_ringbuff);

	return 0;
}

void ringBuff_show(ringBuff *self) {
	printf("%c ", *(self->buffer));
	uint8_t *temp = self->buffer + 1;
	while (temp <= self->endBuffer) {
		printf("%c ", *(temp));
		temp++;
	}
	printf("\n");
}
