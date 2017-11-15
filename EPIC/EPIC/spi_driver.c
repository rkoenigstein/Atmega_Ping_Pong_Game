#include <avr/io.h>
#include <avr/interrupt.h>
#include "spi_driver.h"
#include "Parameters.h"

#ifdef ATMEGA2560
	#define DD_MOSI DDB2
	#define DD_MISO DDB3
	#define DDR_SPI DDRB
	#define DD_SCK DDB1
	#define DD_SS DDB0
#else
	#define DD_MOSI DDB5
	#define DD_MISO DDB6
	#define DDR_SPI DDRB
	#define DD_SCK DDB7
	#define DD_SS DDB4
#endif

void spi_Slaveinit(void)
{
	//set MISO output, all others input
	DDR_SPI = (1 << DD_MISO);

	//enable SPI
	SPCR = (1 << SPE);
}

void spi_Masterinit(void)
{
	DDRB = 0xFF;

	//set MOSI, SCK and SS output, all others input
	DDR_SPI |= (1 << DD_SS) | (1 << DD_MOSI) | (1 << DD_SCK);

	//enable SPI, Master, set clock rate fck/16
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void spi_init(void)
{
	spi_Masterinit();
}

void spi_MasterTransmit(char cData)
{
	//start transmission
	SPDR = cData;

	//wait for transmission complete
	while(!(SPSR & (1 << SPIF)));
}

char spi_SlaveReceive(void)
{
	//send dummy data
	SPDR = 0xFF;

	//wait for reception complete
	while(!(SPSR & (1 << SPIF)));

	//return data register
	return SPDR;
}

void spi_TEST(void)
{
	char data='a';
	spi_MasterTransmit(data);
	data = spi_SlaveReceive();
}
