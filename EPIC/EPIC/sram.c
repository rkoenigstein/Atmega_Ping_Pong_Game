//SRAM funcions
#include "sram.h"

void sram_init(void)
{
	//enabling external memory
	MCUCR |= (1<<SRE);
	
	//realesing  JTAG pins from memory mapping
	SFIOR|=(1<<XMM2);
	SFIOR&=(0<<XMM1);
	SFIOR&=(0<<XMM0);
}

//TEST FUNCTIONS
void TEST_write_adress (void)
{
	int * a=0x0fff;
	while(1)
	{
		a=0x0fff;
		*a=0xff;
		_delay_ms(1000);
		a=0x0501;
		*a=0x44;
		_delay_ms(1000);		
	}

}

void TEST_GAL(void)
{
	volatile int *a=0;
	int b = -1;
	while(1)
	{
		uart_putstring("TEST GAL PRESS ENTER \n");
		while(b == -1){
			a=0x1800; // put the respective memory address which should be tested, here
			//ADC: active low chip select
			//OLED: active low chip select
			//SRAM: active high chip select
			*a = 0xf;
		}
	}
}

void TEST_ADC(void)
{
	volatile int *a=0;
	int b = -1;
	while(1)
	{
		uart_putstring("TEST GAL PRESS ENTER \n");
		while(b == -1){
			a=0x1400; // put the respective memory address which should be tested, here
			//ADC: active low chip select
			//OLED: active low chip select
			//SRAM: active high chip select
			printf((char*)a);
		}
	}	
}

//PROFESSOR TEST
void TEST_SRAM_test(void)
{
volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
uint16_t ext_ram_size = 0x800;
uint16_t write_errors = 0;
uint16_t retrieval_errors = 0;
printf("Starting SRAM test...\n");
// rand() stores some internal state, so calling this function in a loop will
// yield different seeds each time (unless srand() is called before this function)
uint16_t seed = rand();
// Write phase: Immediately check that the correct value was stored
srand(seed);
for (uint16_t i = 0; i < ext_ram_size; i++) {uint8_t some_value = rand();
ext_ram[i] = some_value;
uint8_t retreived_value = ext_ram[i];
if (retreived_value != some_value) {
printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);write_errors++;}}
// Retrieval phase: Check that no values were changed during or after the write phase
srand(seed);
// reset the PRNG to the state it had before the write phase
for (uint16_t i = 0; i < ext_ram_size; i++) {uint8_t some_value = rand();uint8_t retreived_value = ext_ram[i];
if (retreived_value != some_value) {
printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
retrieval_errors++;}}
printf("SRAM test completed with \n %4d errors in write phase and \n %4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}