#include "suiveurDeLigne.h"
#include "moteur.h"
#include "del.h"


volatile uint8_t nbrFoisBloque = 0;
#define VITESSEMOTEURGAUCHE 50
#define VITESSEMOTEURDROITE 50
#define VITESSEINTERSECTIONDROITE 40
#define VITESSEINTERSECTIONGAUCHE 40
#define VITESSEBALAYAGE 40
#define PENTEPOURTOURNER 30 // dimuner la vitesse d un des moteurs pour permet au robot de tourner sans arreter une roue 
#define MOYENNE_PENTEPOURTOURNER 7 //permet de diminuer un peu la vitesse si on a dévié du trajet et atteint l'état perdu, sans toucher les côtés
#define PETITE_PENTEPOURTOURNER 4 //permet de diminuer legèrement la vitesse du côté qui a atteint l'intersection en premier
#define TEMPS_BALAYAGE_MS 500
#define COMPTEURTOURNER 4000 // le compteur de la boucle qui permet de tourner durant le balayage
capteur dernierCapteurActif = aucun ; //Le dernier capteur qui a été activé
capteur dernierCapteurCoteActif = aucun; //Le dernier capteur qui a été activé, mais ignore le capteur central
direction derniereDirection= noDirection; //La derniere direction prise par le robot apres franchir interction
//enum intersection  {noIntersection, cross, tBase , tLeft , tRight , lLeft , lRight};
//enum capteur {aucun, droit , centre , gauche };
//enum direction {directionDroite, directionGauche , noDirection};

intersection derniereIntersection = noIntersection; // Sauvegarder le type d'intersection franchie
intersection possibilite1 = noIntersection ;
intersection possibilite2 = noIntersection ; 


void initialiserSuiveurDeLigne()
{
	PORTA &= ~( (1 << 0x01) | (1 << 0x03) | (1 << 0x05) );
}


bool isCenter() { return ( !( PINA & _BV(PINA3) ) ); }						


bool isLeft() { return ( !( PINA & _BV(PINA1) ) );	}		


bool isRight() { return ( !( PINA & _BV(PINA5) ) ); }

intersection gererIntersectionTBase()
{
	arreterRobot();
	
	if(balayerZone(VITESSEBALAYAGE,VITESSEBALAYAGE,TEMPS_BALAYAGE_MS))
		return cross;
	else
		return tBase;
}

intersection gererIntersectionLLeft()
{
		arreterRobot();
		
		if(balayerZone(VITESSEBALAYAGE, VITESSEBALAYAGE, TEMPS_BALAYAGE_MS))

			return tRight;

		else
		{
			intersectionTournerAGauche();
			return lLeft;
		}
}

intersection gererIntersectionLRight()
{
		if(balayerDroite(VITESSEBALAYAGE,TEMPS_BALAYAGE_MS/2))

			return tLeft;

		else
		{
			intersectionTournerADroite();
			return lRight;
		}	
}

bool balayerGauche(uint8_t vitesse , uint16_t tempsBalayage)
{
	bool ligneDetectee =  (isLeft() || isCenter() || isRight()) ; 
	
	while (!ligneDetectee && tempsBalayage != 0)
	{
		pivoterAntiHoraire(vitesse);
		_delay_ms(1);
		ligneDetectee =  (isLeft() || isCenter() || isRight()) ; 
		tempsBalayage -- ;
	}
	arreterRobot();
	return ligneDetectee ;
}

bool balayerDroite(uint8_t vitesse , uint16_t tempsBalayage)
{
	bool ligneDetectee =  (isLeft() || isCenter() || isRight()) ; 
	
	while (!ligneDetectee && tempsBalayage != 0)
	{
		pivoterHoraire(vitesse);
		_delay_ms(1);
		ligneDetectee =  (isLeft() || isCenter() || isRight()) ; 
		tempsBalayage -- ;
	}
	arreterRobot();
	return ligneDetectee ;
}

void intersectionTournerAGauche()
{
		while( !isCenter() )
		{
			//tournerAGauche(VITESSEBALAYAGE);
			pivoterAntiHoraire( VITESSEBALAYAGE );
		}
	
	derniereDirection= directionGauche ;
	
}

void intersectionTournerADroite()
{
	while (!isCenter())
			//tournerADroite(VITESSEBALAYAGE);
			pivoterHoraire(VITESSEBALAYAGE);
	
	derniereDirection= directionDroite ;
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : detecteTypeIntersection()                                                                                       //
//  Paramètres : aucun                                                                                                      //
//	Retour : enum intersection                                                                                                         //
//																														    //	
//  La fonction trouve le type d'intersection que le robot a atteint. Retourne noIntersection si on est simplement sur un trajet
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum intersection detecteTypeIntersection()
{
    enum intersection intersectionType = noIntersection ;
		/*
		if(possibilite1 == cross && possibilite2 == tBase && (derniereIntersection == cross))
		{
						avancerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
						_delay_ms(50);
						
						if(isCenter())
							return cross;
						else
						intersectionType = gererIntersectionTBase();
		}
		if(possibilite1 == tRight && possibilite2 == lLeft)
		{
		
		}
		if(possibilite1 == tLeft && possibilite2 == lRight)
		{
		
		}
		*/ 
		
		
		if(isCenter() && isLeft() && isRight())
		{
			while( isCenter() && isLeft() && isRight())
						avancerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
						_delay_ms(50);
						if(isCenter())
						return cross;
						else
						intersectionType = gererIntersectionTBase();
		
		}
		if(isCenter() && isLeft())
		{
			while( isCenter() && isLeft() )
						avancerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
						_delay_ms(50);
						if(isCenter())
						return tRight;
						else
						intersectionType = gererIntersectionLLeft();
		
		}
		if(isCenter() && isRight())
		{
			while( isCenter() && isLeft() )
						avancerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
						_delay_ms(50);
						if(isCenter())
						return tLeft;
						else
						intersectionType = gererIntersectionLRight();
		
		}
		
		
		
		
    
    return intersectionType;
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : suivreTrajet()      		                                                                                    //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																														    //	
//  La fonction permet au robot de suivre la ligne						                                                    //
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void suivreTrajet()
{	
	
			if(!isLeft() && isCenter() && !isRight())
			{
				
				avancerRobot(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE);
				dernierCapteurActif = centre;
						
			}
			else if(isLeft() && !isCenter() && !isRight())
			{
				
				ajusterGauche(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE , PENTEPOURTOURNER );
				dernierCapteurActif = gauche;
			
			
			}
			else if(!isLeft() && !isCenter() && isRight())
			{
				
				ajusterDroite(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE , PENTEPOURTOURNER );
				dernierCapteurActif = droit;
				
			}
			else if(isLeft() && isCenter() && isRight())
			{
				possibilite1 = cross ;
				possibilite2 = tBase ;
				
			}
			else if(isLeft() && isCenter() && !isRight())
			{
				possibilite1 = tRight ;
				possibilite2 = lLeft ;
			}
			else if(!isLeft() && isCenter() && isRight())
			{
				possibilite1 = tLeft ;
				possibilite2 = lRight ;
			}
			else if(!isLeft() && !isCenter() && !isRight())
			{
				
				
				
				if(dernierCapteurActif==gauche)
				{
					
					ajusterGauche(VITESSEMOTEURDROITE  , VITESSEMOTEURGAUCHE , PENTEPOURTOURNER );
					
					
				}
				else if (dernierCapteurActif==droit)
				{
					
					ajusterDroite(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE , PENTEPOURTOURNER );
					
				}	
				else
				{	
					
					avancerRobot(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE);
					
				}
				
				
					
			}
			else
			{
					reculerRobot(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE);
			}
			
}



bool balayerZone(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche , uint16_t rayonDeBalayage )
{
	bool ligneTrouvee = false ;
	
	if(balayerGauche(vitesseMoteurDroit , rayonDeBalayage/2))
		ligneTrouvee = true;
	
	else if(balayerDroite(vitesseMoteurGauche , rayonDeBalayage))
		ligneTrouvee = true;
	
	else
		while(!isCenter() && !isLeft() && !isRight())
			reculerRobot(vitesseMoteurDroit , vitesseMoteurGauche);
			//ligneTrouvee demeure false
	
	arreterRobot();
	return ligneTrouvee ;	
	
}


///////////////////////////////////////TEST///////////////////////////////////////

int main()
{	initialiserSuiveurDeLigne();
    vertClignotant('B',0,40);
    //for(uint8_t i =);
    activerMoteurs();
    avancerRobot(100 , 100);
    _delay_ms(10);
    //arreterRobot();
     //balayerZone(35, 35,1000);
    
    

   //while (1) 
   //avancerRobot(VITESSEINTERSECTIONDROITE , VITESSEINTERSECTIONGAUCHE);
   //suivreTrajet();
	
    while (1) {
	
		
		//suivreTrajet();  
		switch(  detecteTypeIntersection()  )
		{
			case tLeft :
				intersectionTournerADroite(); 
				break;
				
			case tRight :
			intersectionTournerAGauche();
				break;
				
			case noIntersection:
				suivreTrajet();
				break;
				
			case tBase :
				intersectionTournerADroite(); 
				break;
			case cross:
				intersectionTournerAGauche();
				break;
			
			default :
				reculerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
				break;
		}
	}

	return 0;
}
