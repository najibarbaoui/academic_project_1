#include "robotLib.h"

// FICHIER DE TESTS POUR CAPTEUR DE DISTANCE.

int main()
{
	DDRD = 0xFF;
 	LCM lcd( &DDRC, &PORTC );
	timer0_init();
	
	while( 1 )
	{
		can convertisseur;
		uint8_t intensite = convertisseur.lecture(0) >> 2;
		uint8_t midi_note = 0;
		
		
 		if( intensite < (uint8_t) 35 ) 
 		{
 			//intensite = 0;
 			silence();
 		}
 		else
		{
			jouerSon(255 - intensite);
			//jouerSon( 255 - intensite );
		}
// 		else
// 		{
// 			float v = ( (intensite - 30.0) / 225.0) * 36.0;
// 			midi_note = v + 45;
// 		}
// 	
// 		jouerNote( midi_note );
		//float v = intensite / 1024.0;
		
		lcd.clear();
		writeValue( &lcd, intensite, 0 );
		writeValue( &lcd, 0, 1 );
		writeValue( &lcd, 0, 2 );
		writeValue( &lcd, 0, 3 );
// 		_delay_ms(400); // Temps minimum pour bien afficher.
	}
	
	return 0;
}