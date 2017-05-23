#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>       // For writting from program space. Used by UARTWrite(const char *, uint8_t)

#include <string.h>             // For convenience function. Used by UARTWrite_S(char *)

extern volatile uint8_t UARTFlags;

#define FOSC 16000000UL
#define BAUD 38400UL
#define MYUBRR ((FOSC / (16*BAUD)) - 1)

#define TX_BUSY 0x01	// If set, transmission in progress.
#define RX_BUSY 0x02	// If set, reception in progress.
#define FLASH_STRING 0x04	// If set, the data is read from flash.
#define FLASH_TX_BUSY 0x05	// TX_BUSY | FLASH_STRING

void UARTInit(void);
#define FinishTX while(UARTFlags & TX_BUSY)
#define FinishRX while(UARTFlags & RX_BUSY)
uint8_t UARTWriteChar(char data);
uint8_t UARTWrite(char *buffer, uint8_t numOfBytes);
uint8_t UARTWrite_S(char *buffer);
uint8_t UARTWrite_P(const char *buffer, uint8_t numOfBytes);
uint8_t UARTRead(char *buffer, uint8_t numOfBytes);
