#include "midi.h"

volatile bool TIME_SWITCH;
volatile bool SOUND_ON;

ISR ( TIMER0_COMPA_vect ) 
{
	TCNT0 = 0;
	
	if( SOUND_ON )
	{
		if( TIME_SWITCH ) 
		{
					//PORTA = 0b00000010;
			TIME_SWITCH = 0;
			PORTB  = 0b00000000; 
			//PORTD &= ~( 1 << 0x0 );
			//PORTD &= ~( 1 << 0x1 );
		}
					
		else 
		{
			//PORTA = 0b00000001; // RED.
			TIME_SWITCH = 1;
			PORTB = 0b00000001;
			//PORTD |= ( 0 << 0x0 );
			//PORTD &= ( 1 << 0x1 );
		}
	}
}


void timer0_init(void)
{   
    TCCR0A = _BV(COM0A0) | _BV(WGM01); // toggle output set mode to ctc 
    TCCR0B = _BV(CS01) | _BV(CS00); // CTC mode and prescaler to 64 
	OCR0A = 75 - 1; 
	TIMSK0 |= ( 1<<OCIE0A ); //Enable timer interrupts
	SOUND_ON = false;
	//DDRB = 0xFF;
	TIME_SWITCH = 0;
	DDRB = 0xFF;
    sei();                  //Enable global interrupts
}

void silence( ) 
{
	SOUND_ON = false;
	TIMSK0 &= ~( 1 << OCIE0A ); // Disable timer0 interrupts
}

// v de 0 a 255;
void jouerSon( const uint8_t& v )
{
		TIMSK0 |= ( 1<<OCIE0A ); //Enable timer interrupts
		TCCR0B = _BV(CS01) | _BV(CS00); // CTC mode and prescaler to 64 
		SOUND_ON = true;
		OCR0A = v;
}

void jouerNote( const uint8_t& midi_note )
{
	TIMSK0 |= ( 1<<OCIE0A ); //Enable timer interrupts
	
	if( midi_note >= 59 )
		TCCR0B = _BV(CS01) | _BV(CS00); // CTC mode and prescaler to 64 
		
	else TCCR0B = _BV(CS02); // prescaler 256
	
	
	SOUND_ON = true;
	
	switch( midi_note )
	{
		case 45: OCR0A = 141; break;
		case 46: OCR0A = 133; break;
		case 47: OCR0A = 126; break;
		case 48: OCR0A = 118; break;
		case 49: OCR0A = 112; break;
		case 50: OCR0A = 105; break;
		case 51: OCR0A = 99; break;
		case 52: OCR0A = 94; break;
		case 53: OCR0A = 88; break;
		case 54: OCR0A = 83; break;
		case 55: OCR0A = 79; break;
		case 56: OCR0A = 74; break;
		case 57: OCR0A = 70; break;
		case 58: OCR0A = 66; break;
		
		case 59:  OCR0A = 252; break;
		case 60:  OCR0A = 238; break;
		case 61:  OCR0A = 224; break;
		case 62:  OCR0A = 212; break;
		case 63:  OCR0A = 200; break;
		case 64:  OCR0A = 189; break;
		case 65:  OCR0A = 178; break;
		case 66:  OCR0A = 168; break;
		case 67:  OCR0A = 158; break;
		case 68:  OCR0A = 149; break;
		case 69:  OCR0A = 141; break;
		case 70:  OCR0A = 133; break;
		case 71:  OCR0A = 126; break;
		case 72:  OCR0A = 118; break;
		case 73:  OCR0A = 112; break;
		case 74:  OCR0A = 105; break;
		case 75:  OCR0A = 99; break;
		case 76:  OCR0A = 94; break;
		case 77:  OCR0A = 88; break;
		case 78:  OCR0A = 83; break;
		case 79:  OCR0A = 79; break;
		case 80:  OCR0A = 74; break;
		case 81:  OCR0A = 70; break;
		default: silence(); 
	}
}
/*
int main()
{
	DDRA = 0xFF;
	DDRB = 0xFF;

	TIME_SWITCH = 0;

	timer0_init();
	jouerNote( 0 );

	while( 1 )
	{		
	}
	
	return 0;
}*/
// 		jouerNote( 50 );
// 		
// 		if( SOUND_ON )
// 		{
// 			if( TIME_SWITCH ) 
// 			{
// 				//PORTA = 0b00000010;
// 				PORTB = 0b00000000; 
// 			}
// 				
// 			else 
// 			{
// 				//PORTA = 0b00000001; // RED.
// 				PORTB = 0b00000001;
// 			}
// 		}
// 		
// 	}
//   
// 	return 0;
// }
	   

	  
	  
	  
	  
	  
	 

























