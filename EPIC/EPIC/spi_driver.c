#include "spi_driver.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#define DD_MOSI DDB5
#define DD_MISO DDB6
#define DDR_SPI DDRB
#define DD_SCK DDB7

void spi_Slaveinit(void)
{
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPE);
}
void spi_Masterinit(void)
{	
	/* Set MOSI, SCK and SS output, all others input */
	DDRB |= (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
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