/*
 * main.c
 *
 * Created: 2/16/2021 9:03:34 AM
 *  Author: Ashish Sharma
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL // telling controller crystal frequency (16 MHz AVR ATMega328P)
#endif
#include <xc.h>
#include <util/delay.h>
#include <avr/io.h> //header to enable data flow control over pins. Defines pins, ports, etc.  

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK and CS output, all others input */
	DDRB = (1<<DDB3)|(1<<DDB5)|(1 << DDB2); // DDB3 IS MOSI AND DDB5 IS SCK
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	PORTB= (1<<PORTB2); //setting cs high
}
void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

int main(void)
{ SPI_MasterInit(); //initiallising SPI master
    while(1)
    {
         
	         PORTB= 0<<PORTB2; //setting cs low
	         SPI_MasterTransmit(69); // transmitting char 'a'
			 PORTB= 1<<PORTB2; //setting cs high
	         _delay_ms(100);
			 PORTB= 0<<PORTB2; //setting cs low
	         SPI_MasterTransmit(0);// transmitting char 'b'
			 PORTB= 1<<PORTB2; //setting cs high
	         _delay_ms(100);
	        
         
    }
}