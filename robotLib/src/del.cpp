#include "del.h"

void clignoterDel( volatile uint8_t* ddr, 
				   volatile uint8_t* port, 
				   const uint8_t& pin, 
				   const uint16_t& nfois,
				   const uint8_t& color )
{
	*ddr |= ( 1 << pin ) | ( 1 << (pin + 1) );
	*port &= ~( 1 << pin );
	*port &= ~( 1 << (pin + 1) );
	
	uint16_t tmp = 0;
	while( nfois > tmp )
	{
		*port |= ( color << pin);
		_delay_ms( 125 ); //laisser absolument à 125, fréquence est un requis
		
		*port &= ~( color << pin );
		_delay_ms( 125 );
		
		++tmp;
	}

}

void allumerDel( volatile uint8_t* ddr, 
				  volatile uint8_t* port, 
				  const uint8_t& pin, 
				  const uint16_t& temps_ms,
				  const uint8_t& color )
{
	uint16_t tmp = 0;

	*ddr |= ( 1 << pin ) | ( 1 << (pin + 1) );
	*port |= ( color << pin );
	
	while( temps_ms >= tmp )
	{
		_delay_ms( 1 );
		++tmp;
	}
	*port &= ~( 1 << pin );
	*port &= ~( 1 << (pin + 1) );
}

void garderAllumerDel( volatile uint8_t* ddr, 
						volatile uint8_t* port, 
						const uint8_t& pin,
						const uint8_t& color )
{
	*ddr |= ( 1 << pin ) | ( 1 << (pin + 1) );
	
	*port |= ( 0b11 << pin );
	*port &= ( color << pin );
	//*port |= ( color << pin );
}

void eteindreDel( volatile uint8_t* ddr, 
				  volatile uint8_t* port, 
				  const uint8_t& pin )
{
	*ddr |= ( 1 << pin ) | ( 1 << (pin + 1) );
	*port &= ~( 1 << pin );
	*port &= ~( 1 << (pin+1) );
}
