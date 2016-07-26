#include "robotLib.h"

// FICHIER DE TESTS POUR DEL.

int main()
{
	while( 1 )
	{
		_delay_ms( 1000 );
		clignoterDel( &DDRB, &PORTB, 0, 5, DEL_VERT );
		
		_delay_ms( 1000 );
		clignoterDel( &DDRB, &PORTB, 0, 5, DEL_ROUGE );
		
		_delay_ms( 1000 );
		allumerDel( &DDRB, &PORTB, 0, 1000, DEL_VERT );
		
		_delay_ms( 1000 );
		allumerDel( &DDRB, &PORTB, 0, 1000, DEL_ROUGE );
		
		_delay_ms( 1000 );
		garderAllumerDel( &DDRB, &PORTB, 0, DEL_VERT );
		
		_delay_ms( 1000 );
		eteindreDel( &DDRB, &PORTB, 0 );
		
		_delay_ms( 1000 );
		garderAllumerDel( &DDRB, &PORTB, 0, DEL_ROUGE );
		
		_delay_ms( 1000 );
		eteindreDel( &DDRB, &PORTB, 0 );
	}
	
	return 0;
}