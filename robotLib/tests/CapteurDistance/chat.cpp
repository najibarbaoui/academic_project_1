#include "robotLib.h"

bool boutonPoussoirAppuye(void);

void testSon(uint8_t intensite);
//enum intersection  {noIntersection, cross, tBase , tLeft , tRight , lLeft , lRight};
//enum intersection detecteTypeIntersection();

enum etat {testDepat,grilleADroit,grilleAGauche};

uint8_t midi_note = 0;
volatile bool boutonRelache =true;	

int main()
{
	
	
	DDRA = 0x00;
	DDRD = 0x00;
	DDRB = 0xff;
	can convertisseur;
	timer0_init();
	while(1)
		testSon(convertisseur.lecture(0) >> 2);
	
							
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : bool boutonPoussoirAppuye(void)                                                                              //
//  Paramètres : aucun                                                                                                      //
//	Retour : bool                                                                                                           //
//																															//	
//  La fonction teste si le boutoin poussoir est appuyé (le broche numéro 2 PIND == 1), attend un delai pour l'antirebond et// 
//  revérifier si le bouton est	toujours appuyé, si c'est le cas la fonction retourne true sinon returnera false            //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool boutonPoussoirAppuye(void)
{
	
	bool estAppuye = false; // variable temporaire
	
	if (PIND & _BV(PIND2)) // si le bouton poussoir est appuye
	{ 
		_delay_ms (30); // le systeme attend un delai = DELAIPOUSSOIR (antirebond)
		
		estAppuye = (PIND & _BV(PIND2))  ? true : false; // verifie apres l'expiration du delai si le bouton est toujours appuye
      
	}
	
  return estAppuye; 
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : void testSon(uint8_t intensite)                                                                           //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                           //
//																															//	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void testSon(uint8_t intensite)
{
	if( intensite < (uint8_t) 35 )
		silence();
 	else 
		jouerSon(255 - intensite); //La sonnette doit être dans le port B avec le fil rouge sur la broche 0

}


