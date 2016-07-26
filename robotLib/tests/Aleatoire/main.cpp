/**************************************************************************//**
 * @file main.cpp (Test pour gerer l'aleatoire.)
 * @author Najib Arbaoui
 * @Date   28 Novembre 2013
 *****************************************************************************/
// FICHIER DE TESTS POUR GERER L'ALEATOIRE.

#include "robotLib.h"

/**************************************************************************//**
 * @test Test pour varifier si la direction est belle et bien aleatoire.
 *****************************************************************************/
int main()
{
	LCM lcd( &DDRC, &PORTC );
	initTimerAleatoire();
	
	while( 1 )
	{
		Direction direction = prendreValeurAleatoire();
		
		lcd.clear();
		
		switch( direction)
		{
			case direction_continue:
				writeValue( &lcd, "Continue", 0 );
				break;
				
			case direction_left:
				writeValue( &lcd, "Left", 0 );
				break;
				
			case direction_right:
				writeValue( &lcd, "Right", 0 );
				break;
		};
		
		writeValue( &lcd, 0, 1 );
		writeValue( &lcd, 0, 2 );
		writeValue( &lcd, "test", 3 );
		_delay_ms( 100 ); 
		
	}
	
	return 0;
}
