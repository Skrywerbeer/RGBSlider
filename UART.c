#include "UART.h"

volatile static char *TXBuffer;		// Pointer to the data to be written.
volatile static char *RXBuffer;		// Pointer to the buffer for the recieved data.
volatile static uint8_t bytesToSend, bytesToReceive;	// Index variables.
volatile uint8_t UARTFlags = 0;		// Holds various flags based on writes and reads in progress, see header for #define's.


void UARTInit(void) {
	// 8-N-1 data frame.
	UBRR0 = MYUBRR;
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

uint8_t UARTRead(char *buffer, uint8_t numOfBytes) {
	if((UARTFlags & RX_BUSY) != RX_BUSY) {	// If previous read complete.
		UARTFlags |= RX_BUSY;	// Set busy.
		// Store pointer to the buffer for use in the ISR.
		RXBuffer = buffer; bytesToReceive = numOfBytes;
		UCSR0B |= (1 << RXCIE0);

		return 0;
	}
	else return 1;	// Previous read still in progress.
}

ISR(USART_RX_vect) {
	if(bytesToReceive > 0) {
		*(RXBuffer++) = UDR0;
		bytesToReceive--;
	}
	else {
		// Disable recive interrupt, and set RXBuffer pointer to null.
		UARTFlags &= ~(RX_BUSY); RXBuffer = 0;
		UCSR0B &= ~(1 << RXCIE0);
	}
}

uint8_t UARTWriteChar(char data) {
	// Write a single character over UART.
	if(!(UARTFlags & TX_BUSY)) {
		UARTFlags |= TX_BUSY;
		UCSR0B |= (1 << TXCIE0);
		UDR0 = data;
		return 0;
	}
	else return 1;
}

uint8_t UARTWrite(char *buffer, uint8_t numOfBytes) {
	// If no writes are in progress.
	if((UARTFlags & TX_BUSY) != TX_BUSY) {
		bytesToSend = numOfBytes; TXBuffer = buffer;
		// Not sure if a check for message lenght greater than zero is necessary.
		if(bytesToSend > 0) {
			UCSR0B |= (1 << UDRIE0) | (1 << TXCIE0);
			UARTFlags |= TX_BUSY;	// Set busy.
			return 0;
		}
		else return 1;
	}
	else return 1;
}

uint8_t UARTWrite_S(char *buffer) {
	// Convenience function.
	return UARTWrite(buffer, strlen(buffer));
}

uint8_t UARTWrite_P(const char *buffer, uint8_t numOfBytes) {
	// Write data from program space, almost the same implementation as a normal write.
	if((UARTFlags & TX_BUSY) != TX_BUSY) {
		bytesToSend = numOfBytes;
		TXBuffer = ((char *) buffer);
		UARTFlags |= FLASH_TX_BUSY;
		UCSR0B |= (1 << UDRIE0) | (1 << TXCIE0);
		//}
		return 0;
	}

	else return 1;
}

ISR(USART_UDRE_vect) {
	if(bytesToSend > 0) {
		// If the data is being written from program space.
		if(UARTFlags & FLASH_STRING) {
				UDR0 = pgm_read_byte((char *)TXBuffer++);
				//TXBuffer++;
				bytesToSend--;
		}
		// Else the data is being written from RAM.
		else {
			UDR0 = *(TXBuffer++);
			bytesToSend--;
		}
	}
	// End of message.
	else {
		UCSR0B &= ~(1 << UDRIE0); TXBuffer = 0;
	}
}

ISR(USART_TX_vect) {
	UARTFlags &= ~FLASH_TX_BUSY;
	UCSR0B &= ~(1 << TXCIE0);
}
