#include "aleatoire.h"

Direction prendreValeurAleatoire()
{
// 	uint8_t v = (TCNT2 << 6);
// 	
// 	Direction direction;
// 	if( v == 0 || v == 192 ) direction = direction_continue;
// 	else if( v == 64 ) direction = direction_left;
// 	else if( v == 128 ) direction = direction_right;
// 		
// 	return direction;

	Direction direction;
	
	uint8_t v = rand() % 3;
	
	if( v == 0 ) direction = direction_continue;
	else if( v == 1 ) direction = direction_left;
	else if( v == 2 ) direction = direction_right;
	
	return direction;
}

uint8_t prendreValeurCompteur2()
{
	return TCNT2;
}

void initTimerAleatoire()
{ 
//     TCCR2A = _BV(WGM20); // toggle output set mode to ctc 
//     TCCR2B = _BV(CS20); // CTC mode and prescaler to 64 
// 	OCR2A = 254; 
}