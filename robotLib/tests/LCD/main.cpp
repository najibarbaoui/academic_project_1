#include "robotLib.h"

int main()
{
	LCM lcd( &DDRA, &PORTA );
	uint8_t test= 0;
	float test_float = 0;
	uint8_t test_cmp = 0;
	// Écriture d'un simple caractère au début de la première ligne
	while( 1 )
	{
		lcd.clear();
		writeValue( &lcd, test, 0 );
		writeValue( &lcd, test_float, 1 );
		writeValue( &lcd, test_cmp, 2 );
		writeValue( &lcd, "test", 3 );
		_delay_ms(400); // Temps minimum pour bien afficher.
		
		test++;
		test_float += 0.1;
		
		if( !test ) test_cmp++;
		
	}
	
	return 0;
}