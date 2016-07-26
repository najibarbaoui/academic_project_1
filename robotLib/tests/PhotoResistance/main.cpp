// FICHIER DE TESTS POUR GERER L'ALEATOIRE.

#include "robotLib.h"

int main()
{
	LCM lcd( &DDRC, &PORTC );
	initTimerAleatoire();
	
	while( 1 )
	{
		lcd.clear();
		
		if( isIllumineGauche() ) writeValue( &lcd, "GAUCHE", 0 );
		else writeValue( &lcd, "---", 0 );

		if( isIllumineDroite() ) writeValue( &lcd, "DROITE", 1 );
		else writeValue( &lcd, "---", 1 );

		writeValue( &lcd, luminositeGauche(), 2 );
		
		writeValue( &lcd, luminositeDroite(), 3 );
		_delay_ms( 400 ); 
		
	}
	
	return 0;
}
