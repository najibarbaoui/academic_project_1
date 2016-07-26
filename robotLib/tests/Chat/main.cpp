#include "robotLib.h"

//declaration des fonctions

bool boutonPoussoirAppuye();
void courseChat( LineFollower* follower, const Intersection& type);
void testSon( const uint8_t& intensite );


bool aDetecterSouris;


int main()
{	
	LineFollower follower(&courseChat);
	timer0_init();
	//can convertisseur;
	bool sourisCapturee = false; 
	
	//distance_souris = 0;
	aDetecterSouris = false;
	//attendreProchainIntersection = false;
	
	// Test sonore.
	while( !boutonPoussoirAppuye() )
	{ 
		testSon( getDistance0_255() );
	}
	
	silence();
    clignoterDel(&DDRD, &PORTD, 0, 12, DEL_ROUGE);
    //activerMoteurs();
    
    while( !sourisCapturee ) 
	{	
		//distance_souris = ;
 		if( getDistance0_255() >= 80 )
 		{
 			aDetecterSouris = true;
			testSon( getDistance0_255() );
			jouerSon( 100 );
			_delay_ms( 10 );
 			silence();
 		}
	
		if ( getDistance0_255() >= 180 )
		{
			sourisCapturee = true;
			break;
		}
// 		
 		follower.followLine();
    }
    
  		arreterRobot();
		clignoterDel(&DDRD, &PORTD, 0, 12, DEL_VERT);
	
   
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
	
	if( PIND & _BV(PIND2) ) // si le bouton poussoir est appuye
	{ 
		_delay_ms( 30 ); // le systeme attend un delai = DELAIPOUSSOIR (antirebond)
		
		estAppuye = (PIND & _BV(PIND2)) ? true : false; // verifie apres l'expiration du delai si le bouton est toujours appuye 
	}
	
	return estAppuye; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : void courseChat(etat e)                                                                             //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                           //
//																															//	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void courseChat( LineFollower* follower, 
				 const Intersection& type )
{
		switch( type )
		{
			case inter_cross : 
				if( aDetecterSouris )
				{
					follower->turnRight();
					aDetecterSouris = false;
				}
				
				
				break;
				
			case inter_tBase : 
				follower->turnRight();

				break;
				
			case inter_tLeft: 					
				if( aDetecterSouris )
				{
					follower->turnRight();
					aDetecterSouris = false;
				}
				
				break;
				
			case inter_tRight:
				follower->turnLeft();
				
				break;
			default : 
				if( aDetecterSouris )
				{
					follower->turnRight();
					aDetecterSouris = false;
				}
		}
	}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : void testSon(uint8_t intensite)                                                                           //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                           //
//																															//	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void testSon( const uint8_t& intensite )
{
	if( intensite < 35 )
	{
		silence();
	}
 	else 
		jouerSon( 255 - intensite ); //La sonnette doit être dans le port B avec le fil rouge sur la broche 0

}

