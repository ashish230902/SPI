/*
 * main.c
 *
 * Created: 2/16/2021 9:03:34 AM
 *  Author: Ashish Sharma
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL // telling controller crystal frequency (10 MHz AVR ATMega328P)
#endif
#include <avr/io.h> //header to enable data flow control over pins. Defines pins, ports, etc.  
#include <xc.h>
#include <util/delay.h>


void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDRB = (1<<DDB4);
	/* Enable SPI */
	SPCR = (1<<SPE);
	DDRD= (1<<DDD0);
}

char SPI_SlaveReceive(void)
{    
    
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return Data Register */
	
	return SPDR;
}

int main(void)
{   unsigned char x;
	SPI_SlaveInit();
	
    while(1)
    {
	    x=SPI_SlaveReceive();
		PORTD = (x<<PORTD0);  
       
    }
}