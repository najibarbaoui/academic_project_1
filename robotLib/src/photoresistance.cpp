/////////////////////////////////////////////
// photoresistance.cpp                     //
// implémentation de photoresistance.h     //
/////////////////////////////////////////////

#include "photoresistance.h"

#include "can.h"
#include "LCD.h"


/*Variables globales utilisées*/

//bornes de ce qui est considéré comme étant illuminé. Une valeur plus grande équivaut à plus de lumière nécessaire.
#define borneGauche 220
#define borneDroite 220



uint8_t luminositeGauche()
{
    can unConverter; // creation d'un objet can pour obtenir les valeurs de la luminosite
    
    DDRA &= 0xBF; //On met la broche 7 en mode entrée
    return (uint8_t)(unConverter.lecture(6) >> 2);
}

uint8_t luminositeDroite()
{
    can unConverter; // creation d'un objet can pour obtenir les valeurs de la luminosite
    
    DDRA &= 0x7F; //On met la broche 8 en mode entrée
    return (uint8_t)(unConverter.lecture(7) >> 2);
}

bool isIllumineGauche()
{
	
    if (luminositeGauche() >= borneGauche)
	return true;
    else
	return false;
}


bool isIllumineDroite()
{
    if (luminositeDroite() >= borneDroite)
	return true;
    else
	return false;
}

void afficherPhotoresistances()
{
    LCM lcd( &DDRC, &PORTC );

    lcd.clear();
    writeValue( &lcd, luminositeDroite(), 0 );
    writeValue( &lcd, luminositeGauche(), 1 );
    writeValue( &lcd, 0, 2 );
    writeValue( &lcd, 0, 3 );
    _delay_ms(400);
}

/*fonction main exemple
 
 uint8_t main ()
 {
    
    activerMoteurs();
    
    while (true)
    {
	//fonctions pour faire tourner moteur à la prochaine intersection si isIllumineDroite()
	
	afficherPhotoresistances();
    }
    
    return 0; 
}
*/