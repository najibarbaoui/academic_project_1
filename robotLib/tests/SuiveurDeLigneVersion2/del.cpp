#include "del.h"
#include <util/delay.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : rougeClignotant(uint8_t port,uint8_t broche,uint16_t temps)                                                                                        //
//  Paramètres : uint8_t port,uint8_t broche,uint16_t temps                                                                                                      //
//	Retour : aucun                                                                                                          //
//																															//	
//  La fonction qui fait clignoter la DEL en rouge en mettant la valeur 00000010 (base 2) dans le PORT A pour un délai temps*100ms                    // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rougeClignotant(uint8_t port,uint8_t broche,uint16_t temps)
{
		uint16_t tmp = 0;
	switch(port){
		case 'A': while (temps >= tmp) {
					DDRA = 0xff;
					PORTA = (2 << broche); 
					_delay_ms(50);
					PORTA = (0 << broche);
					_delay_ms(50);
					tmp++;
					}
					PORTA = 0;
					break;
        case 'B': while (temps > tmp) {
					DDRB = 0xff;
					PORTB = (2 << broche); 
					_delay_ms(50);
					PORTB = (0 << broche);
					_delay_ms(50);
					tmp++;
					} 
					PORTB = 0;
					break;
		case 'C': while (temps > tmp) {
					DDRC = 0xff;
					PORTC = (2 << broche); 
					_delay_ms(50);
					PORTC = (0 << broche);
					_delay_ms(50);
					tmp++;
					}
					PORTC = 0;
					break;
		case 'D': while (temps > tmp) {
					DDRD = 0xff;
					PORTD = (2 << broche); 
					_delay_ms(50);
					PORTD = (0 << broche);
					_delay_ms(50);
					tmp++;
					}
					PORTD = 0; 
					break;
		default :  break;
    }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : vertClignotant(uint8_t port,uint8_t broche,uint16_t temps)                                                                                         //
//  Paramètres : uint8_t port,uint8_t broche,uint16_t temps                                                                                                      //
//	Retour : aucun                                                                                                          //
//																															//	
// La fonction qui fait clignoter la DEL en rouge en mettant la valeur 00000010 (base 2) dans le PORT A pour un délai temps*100ms // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void vertClignotant(uint8_t port,uint8_t broche,uint16_t temps)
{
	uint16_t tmp = 0;
	switch(port){
		case 'A': while (temps >= tmp) {
					DDRA = 0xff;
					PORTA = (1 << broche); 
					_delay_ms(50);
					PORTA = (0 << broche);
					_delay_ms(50);
					tmp++;
					}
					PORTA = 0;
					break;
        case 'B': while (temps > tmp) {
					DDRB = 0xff;
					PORTB = (1 << broche); 
					_delay_ms(50);
					PORTB = (0 << broche);
					_delay_ms(50);
					tmp++;
					} 
					PORTB = 0;
					break;
		case 'C': while (temps > tmp) {
					DDRC = 0xff;
					PORTC = (1 << broche); 
					_delay_ms(50);
					PORTC = (0 << broche);
					_delay_ms(50);
					tmp++;
					}
					PORTC = 0;
					break;
		case 'D': while (temps > tmp) {
					DDRD = 0xff;
					PORTD = (1 << broche); 
					_delay_ms(50);
					PORTD = (0 << broche);
					_delay_ms(50);
					tmp++;
					}
					PORTD = 0; 
					break;
		default :  break;
    }
	
        

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : eteindreDel(uint8_t port,uint8_t broche)                                                                                            //
//  Paramètres : uint8_t port,uint8_t broche                                                                                                      //
//	Retour : aucun                                                                                                          //
//																	
//  La fonction qui éteint la DEL sur la broche et le port spécifiés
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void eteindreDel(uint8_t port,uint8_t broche)
{
        switch(port){
		case 'A':{
					DDRA = 0xff;
					PORTA &= (0 << broche); 
					}
					
					break;
        	case 'B': {
					DDRB = 0xff;
					PORTB &= (0 << broche); 
					} 
					
					break;
		case 'C': {
					DDRC = 0xff;
					PORTC &= (0 << broche); 
					}
					
					break;
		case 'D': {
					DDRD = 0xff;
					PORTD &= (0 << broche); 
					}
					
					break;
		default : break;
    }
        
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : allumeVert(uint8_t port,uint8_t broche,uint16_t temps)                                                                                            //
//  Paramètres : Le port, la broche et le temps en 100ms                                                                    //
//	Retour : aucun                                                                                                          //
//
//  La fonction qui allume la DEL verte pour temps*100 ms en mettant la valeur 00000001 (base 2) dans le PORT                             // 			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void allumeVert(uint8_t port,uint8_t broche,uint16_t temps)
{
	uint16_t tmp = 0;
	switch(port){
		case 'A': while (temps >= tmp) {
					DDRA = 0xff;
					PORTA = (1 << broche); 
					_delay_ms(100);
					tmp++;
					}
					PORTA = 0;
					break;
        case 'B': while (temps > tmp) {
					DDRB = 0xff;
					PORTB = (1 << broche); 
					_delay_ms(100);
					tmp++;
					} 
					PORTB = 0;
					break;
		case 'C': while (temps > tmp) {
					DDRC = 0xff;
					PORTC = (1 << broche); 
					_delay_ms(100);
					tmp++;
					}
					PORTC = 0;
					break;
		case 'D': while (temps > tmp) {
					DDRD = 0xff;
					PORTD = (1 << broche); 
					_delay_ms(100);
					tmp++;
					}
					PORTD = 0; 
					break;
		default : break;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : allumeRouge(uint8_t port,uint8_t broche,uint16_t temps)                                                                                            //
//  Paramètres : uint8_t port,uint8_t broche,uint16_t temps                                                                                                      //
//	Retour : aucun                                                                                                          //
//																//
//  La fonction qui allume la DEL rouge en mettant la valeur 00000010 (base 2) dans le PORT                             // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void allumeRouge(uint8_t port,uint8_t broche,uint16_t temps)
{
    uint16_t tmp = 0;
	switch(port){
		case 'A': while (temps >= tmp) {
					DDRA = 0xff;
					PORTA = (2 << broche); 
					_delay_ms(100);
					tmp++;
					}
					PORTA = 0;
					break;
        case 'B': while (temps > tmp) {
					DDRB = 0xff;
					PORTB = (2 << broche); 
					_delay_ms(100);
					tmp++;
					} 
					PORTB = 0;
					break;
		case 'C': while (temps > tmp) {
					DDRC = 0xff;
					PORTC = (2 << broche); 
					_delay_ms(100);
					tmp++;
					}
					PORTC = 0;
					break;
		case 'D': while (temps > tmp) {
					DDRD = 0xff;
					PORTD = (2 << broche); 
					_delay_ms(100);
					tmp++;
					}
					PORTD = 0; 
					break;
		default :  break;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : garderRougeAllume(uint8_t port,uint8_t broche)                                                                                          //
//  Paramètres : uint8_t port,uint8_t broche                                                                                                      //
//	Retour : aucun                                                                                                          //
//																//
//  La fonction qui allume la DEL rouge en mettant la valeur 00000010 (base 2) dans le PORT                             // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void garderRougeAllume(uint8_t port,uint8_t broche)
{
	switch(port){
		case 'A': 
					DDRA = 0xff;
					PORTA |= (2 << broche);
					break;
        	case 'B': 
					DDRB = 0xff;
					PORTB |= (2 << broche);
					break;
        	case 'C': 
					DDRC = 0xff;
					PORTC |= (2 << broche);
					break;
        	case 'D': 
					DDRD = 0xff;
					PORTD |= (2 << broche);
					break;
		default :  break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : garderVertAllume(uint8_t port,uint8_t broche)                                                                                          //
//  Paramètres : uint8_t port,uint8_t broche                                                                                                      //
//	Retour : aucun                                                                                                          //
//																//
//  La fonction qui allume la DEL verte en mettant la valeur 00000001 (base 2) dans le PORT                             // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void garderVertAllume(uint8_t port,uint8_t broche)
{
	switch(port){
		case 'A': 
					DDRA = 0xff;
					PORTA |= (1 << broche);
					break;
        	case 'B': 
					DDRB = 0xff;
					PORTB |= (0x1 << broche);
					break;
        	case 'C': 
					DDRC = 0xff;
					PORTC |= (1 << broche);
					break;
        	case 'D': 
					DDRD = 0xff;
					PORTD |= (1 << broche);
					break;
		default :  break;
    }
}

/****** Exemple: 
int main(void){
	allumeRouge('A',0,50);
	allumeVert('A',0,50);
	eteindreDel('A',0);
	rougeClignotant('A',0,50);
	vertClignotant('A',0,50);
}

*////////
