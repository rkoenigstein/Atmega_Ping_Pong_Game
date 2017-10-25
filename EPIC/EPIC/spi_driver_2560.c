#include "spi_driver_2560.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#define DD_MOSI DDB2
#define DD_MISO DDB3
#define DDR_SPI DDRB
#define DD_SCK DDB1
#define DD_SS DDB0

void spi_Slaveinit(void)
{
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}
void spi_Masterinit(void)
{	
	DDRB=0xFF;
	/* Set MOSI, SCK and SS output, all others input */
	DDR_SPI |= (1<<DD_SS)|(1<<DD_MOSI)|(1<<DD_SCK);
	//DDRB &= ~(1<<DD_MISO); //set MISO as input
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void spi_init(void)
{
	spi_Masterinit();
}

void spi_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	

}


char spi_SlaveReceive(void)
{
	//send dummy data
	SPDR = 0xFF;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return data register */
	return SPDR;
}

void spi_TEST(void)
{
	char data='a';
	spi_MasterTransmit(data);
	data=spi_SlaveReceive();
}