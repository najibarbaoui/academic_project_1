/**************************************************************************//**
 * @file main.cpp (Test pour gerer le suiveur de ligne.)
 * @Date   28 Novembre 2013
 *****************************************************************************/
// FICHIER DE TESTS POUR GERER LE SUIVEUR DE LIGNE.

#include "robotUtils.h"
#include "robotLib.h"



// La direction que doit prendre le robot à la prochaine intersection
Direction prochaineDirection = direction_continue;
bool sourisDetectee = false;
bool sourisCapturee = false;

int main()
{	
	///@todo insérer test sonsore
	
	
	// Clignoter à 4Hz pour 3 secondes = 12 cycles.
	// Ceci est un requis du projet
    clignoterDel(&DDRD, &PORTD, 0, 12, DEL_ROUGE);
	
	
    activerMoteurs();
	
	
	
	//////////////////////////
	
	LCM lcd( &DDRC, &PORTC );
	
	
	lcd.clear();
	
	///////////////////////
	
	
    
    while (!sourisCapturee) 
	{
		switch( detecteTypeIntersection() )
		{
			case inter_none:
				suivreTrajet();
				
				//if ( [souris détectée])
				// jouer le son, préférablement sans prendre trop de ressources de temps...
				// if souris est à moins de 10 pouces
				// sourisCapturee = true;
				// prochaineDirection = direction_right;
				
				
				writeValue( &lcd, "trajet", 0 );
				break;
				
			case inter_cross :
				if (prochaineDirection == direction_right) 
				{
					tournerAtIntersection(VITESSEBALAYAGE, direction_right);
					prochaineDirection == direction_continue;
				}
				else
					suivreTrajet();
				
				writeValue( &lcd, "cross", 1 );
				break;
				
			case inter_tBase :
				tournerAtIntersection(VITESSEBALAYAGE, direction_right);
				
				writeValue( &lcd, "tBase", 1 );
				break;
				
			case inter_tLeft:
				tournerAtIntersection(VITESSEBALAYAGE, direction_right);
				writeValue( &lcd, "tLeft", 1 );
				break;
				
			case inter_tRight:
				tournerAtIntersection(VITESSEBALAYAGE, direction_left);
				writeValue( &lcd, "tRight", 1 );
				break;
				
			case inter_lLeft:
				tournerAtIntersection(VITESSEBALAYAGE, direction_left);
				writeValue( &lcd, "lLeft", 1 );
				break;
				
			case inter_lRight:
				tournerAtIntersection(VITESSEBALAYAGE, direction_right);
				writeValue( &lcd, "lRight", 1 );
				break;
				
			default :
				reculerRobot(VITESSEBALAYAGE, VITESSEINTERSECTIONGAUCHE);
				writeValue( &lcd, "NONE", 1 );
				break;
		}
    
    }
    
    //la souris est capturée
    
    //allumer LED vert
    
    arreterRobot();
	
	while (1); //pour que le LED vert reste allumé
    
	return 0;
}

