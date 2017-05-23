#include <avr/io.h>
#include <avr/interrupt.h>

#include "UART.h"

#define RGB_PORT PORTD
#define RED PORTD6
#define GREEN PORTD7
#define BLUE PORTD5

void InitPorts();
void InitTimer0();
void UpdateColors();

volatile uint8_t red = 0, green = 0, blue = 0, softPrescaller = 0;
volatile uint8_t tempPrescaller;

int main() {
	DDRB |= (1 << PORTB5);
	InitPorts(); InitTimer0(); UARTInit(); sei();
	while(1) {
	//	PORTB ^= (1 << PORTB5);
		UpdateColors();
	}
}

void InitPorts() {
	DDRD |= (1 << DDD7) | (1 << DDD6) | (1 << DDD5);    // Arduino pin number 11, 10 and 9.
	PORTD &= ~((1 << PORTD7) | (1 << PORTD6) | (1 << PORTD5));      // Set OutPuts low.
}

void InitTimer0() {
	TCCR0A |= (1 << WGM01);                 // CTC Mode.
	TCCR0B |= (1 << CS01) | (1 << CS00);    // Prescaller 64.
	OCR0A = 10;
	TIMSK0 |= (1 << OCIE0A);                 // Timer overflow interrupt enable.
}

ISR(TIMER0_COMPA_vect) {
//	PORTB ^= (1 << PORTB5);
	red > softPrescaller ? (PORTD |= (1 << RED)) : (PORTD &= ~(1 << RED));
	green > softPrescaller ? (RGB_PORT |= (1 << GREEN)) : (RGB_PORT &= ~(1 << GREEN));
	blue > softPrescaller ? (RGB_PORT |= (1 << BLUE)) : (RGB_PORT &= ~(1 << BLUE));
	//tempPrescaller = softPrescaller;
	//softPrescaller = tempPrescaller + 1;
	softPrescaller++;
	//if(softPrescaller >= 201) {
	//	softPrescaller = 0;
	//	PORTB ^= (1 << PORTB5);
	//}
}

void UpdateColors() {
	// Wait to recieve a null character, then reply with a null and recieve the color values.
	uint8_t startChar = 1;
	uint8_t colorValues[3];
	// Wait for null character.
	do {
		UARTRead((char *) &startChar, 1);
	} while(startChar != 0);
	// Send reply.
	UARTWriteChar('\0');
	FinishRX;
	// Recieve color values.
	UARTRead((char *) &colorValues, 3);
	red = colorValues[0];
	green = colorValues[1];
	blue = colorValues[2];
}
