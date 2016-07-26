#include "suiveurDeLigne.h"
#include "moteur.h"
#include "del.h"

volatile uint8_t nbrFoisBloque = 0;
#define VITESSEMOTEURGAUCHE 50
#define VITESSEMOTEURDROITE 50
#define VITESSEINTERSECTIONDROITE 45
#define VITESSEINTERSECTIONGAUCHE 45
#define PENTEPOURTOURNER 10 // dimuner la vitesse d un des moteurs pour permet au robot de tourner sans arreter une roue 
#define MOYENNE_PENTEPOURTOURNER 7 //permet de diminuer un peu la vitesse si on a dévié du trajet et atteint l'état perdu, sans toucher les côtés
#define PETITE_PENTEPOURTOURNER 4 //permet de diminuer legèrement la vitesse du côté qui a atteint l'intersection en premier
#define TEMPS_BALAYAGE_MS 100
#define COMPTEURTOURNER 4000 // le compteur de la boucle qui permet de tourner durant le balayage
volatile enum capteur dernierCapteurActif = aucun ; //Le dernier capteur qui a été activé
volatile enum capteur dernierCapteurCoteActif = aucun; //Le dernier capteur qui a été activé, mais ignore le capteur central
volatile enum direction derniereDirection= noDirection; //La derniere direction prise par le robot apres franchir interction
//enum intersection  {noIntersection, cross, tBase , tLeft , tRight , lLeft , lRight};
//enum capteur {aucun, droit , centre , gauche };
//enum direction {directionDroite, directionGauche , noDirection};

volatile enum intersection derniereIntersection = noIntersection; // Sauvegarder le type d'intersection franchie
volatile enum intersection possibilite1 = noIntersection ;
volatile enum intersection possibilite2 = noIntersection ; 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : initialiserSuiveurDeLigne()                                                                                  //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																														    //	
//  La fonction initialiser le PORT utilise pour lire les donnees provenants du capteur                                     //
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialiserSuiveurDeLigne()
{
		PORTA &= (0 << 0x01) | (0 << 0x03) | (0 << 0x05);
			
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : IsCenter()                                                                                                  //
//  Paramètres : aucun                                                                                                      //
//	Retour : bool                                                                                                           //
//																														    //	
//  La fonction verifie si le capteur du centre est sur la ligne noir                                                       //
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isCenter()
{	
	 return (!(PINA & _BV(PINA3))) ;						
								
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : IsLeft()                                                                                                     //
//  Paramètres : aucun                                                                                                      //
//	Retour : bool                                                                                                           //
//																														    //	
//  La fonction verifie si le capteur du gauche est sur la ligne noir                                                       //
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isLeft()
{	
	return (!(PINA & _BV(PINA1)));
						
						
}		

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : IsRight()                                                                                                     //
//  Paramètres : aucun                                                                                                      //
//	Retour : bool                                                                                                           //
//																														    //	
//  La fonction verifie si le capteur du droite est sur la ligne noir                                                       //
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isRight()
{	
	return (!(PINA & _BV(PINA5))) ;
						
						
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
		
		if(possibilite1 == cross && possibilite2 == tBase )
		{
			if(balayerZone(VITESSEINTERSECTIONDROITE , VITESSEINTERSECTIONGAUCHE , TEMPS_BALAYAGE_MS))
			{
				if(derniereIntersection == cross ||(derniereIntersection == tRight && derniereDirection == directionGauche))
				{	intersectionType = possibilite1 ;
					derniereIntersection = intersectionType ;
					possibilite1 = noIntersection;
					possibilite2 = noIntersection;
				}
			}
			else
			{
				if(derniereIntersection == cross)
				{
					intersectionType = possibilite2 ;
					derniereIntersection = intersectionType ;
					possibilite1 = noIntersection;
					possibilite2 = noIntersection;
				}
			}
		}
		
		else if(possibilite1 == tRight && possibilite2 == lLeft )
		{
			if(balayerZone(VITESSEINTERSECTIONDROITE , VITESSEINTERSECTIONGAUCHE , TEMPS_BALAYAGE_MS))
			{
				if(((derniereIntersection == tBase ||derniereIntersection == lLeft) && derniereDirection == directionGauche) || derniereIntersection == tRight)
				{	intersectionType = possibilite1 ;
					derniereIntersection = intersectionType ;
					possibilite1 = noIntersection;
					possibilite2 = noIntersection;
				}
			}
			else
			{
				if((derniereIntersection == tBase && derniereDirection == directionGauche)||derniereIntersection == lLeft || derniereIntersection == tRight )
				{
					intersectionType = possibilite2 ;
					derniereIntersection = intersectionType ;
					possibilite1 = noIntersection;
					possibilite2 = noIntersection;
					
					while(!isCenter())
						
						tournerAGauche(VITESSEINTERSECTIONDROITE);
					
						arreterRobot();
					
						_delay_ms(10);
						
						suivreTrajet();
				}
			}
		}
		else if(possibilite1 == tLeft && possibilite2 == lRight )
		{
			if(balayerZone(VITESSEINTERSECTIONDROITE , VITESSEINTERSECTIONGAUCHE , TEMPS_BALAYAGE_MS))
			{
				if(((derniereIntersection == tBase ||derniereIntersection == lRight) && derniereDirection == directionDroite) || derniereIntersection == tLeft)
				{	intersectionType = possibilite1 ;
					derniereIntersection = intersectionType ;
					possibilite1 = noIntersection;
					possibilite2 = noIntersection;
				}
			}
			else
			{
				if((derniereIntersection == tBase && derniereDirection == directionDroite)||derniereIntersection == lRight || derniereIntersection == tLeft )
				{
					intersectionType = possibilite2 ;
					derniereIntersection = intersectionType ;
					possibilite1 = noIntersection;
					possibilite2 = noIntersection;
					
					while(!isCenter())
						
						tournerADroite(VITESSEINTERSECTIONGAUCHE);
					
						
						
						suivreTrajet();
				}
			}
		}
		else
		{
			intersectionType = noIntersection ;
			
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
				
					ajusterGauche(VITESSEMOTEURDROITE  , VITESSEMOTEURGAUCHE , PENTEPOURTOURNER );
				
				else if (dernierCapteurActif==droit)
					
					ajusterDroite(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE , PENTEPOURTOURNER );
					
				else
					avancerRobot(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE);
				
				
				
					
			}
			else
			{
					reculerRobot(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE);
			}
			
}



bool balayerZone(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche , uint16_t rayonDeBalayage )
{
	bool ligneTrouvee = false;
	

	
	
	
	while(isLeft() && isCenter() && isRight())
	
		avancerRobot(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE);
		
		_delay_ms(TEMPS_BALAYAGE_MS);
		
	uint16_t compteurTourner = COMPTEURTOURNER;
	
	
	while( !ligneTrouvee && compteurTourner != 0 ) 
	{
			tournerAGauche(VITESSEMOTEURDROITE);
			
			ligneTrouvee = isLeft() || isCenter() || isRight();
			
			compteurTourner -- ;
			
		
	}
	arreterRobot();	
	
	if(compteurTourner != 0)
	
			return ligneTrouvee;
			
	compteurTourner = COMPTEURTOURNER;
	
	
		
	while( !ligneTrouvee && compteurTourner != 0 ) 
	{
			tournerADroite(VITESSEMOTEURGAUCHE);
			
			ligneTrouvee = isLeft() || isCenter() || isRight();
			
			compteurTourner -- ;
			
		
	}
	
	arreterRobot();	
		
	
	return ligneTrouvee;
}

void detecterPremiereIntersection()
{

		while(derniereIntersection == noIntersection)
		{
			
			if(isCenter())
			{	
				avancerRobot(50 , 50);
				
				if(isCenter()&& isLeft() && isRight())
				{
					while(isCenter()&& isLeft() && isRight())
					
					avancerRobot(50 , 50);
					_delay_ms(100);
					if(!isCenter()&& !isLeft() && !isRight())
						{
							derniereIntersection = tBase ;
							rougeClignotant('B',0,2);
							
						}
					else
						if(isCenter())
						{
							derniereIntersection = cross ;
							rougeClignotant('B',0,2);
						}
				}
				else if(isCenter()&& isLeft() && !isRight())
				{
					while(isCenter()&& isLeft() && !isRight())
					
					avancerRobot(50 , 50);
					_delay_ms(100);
					if(!isCenter()&& !isLeft() && !isRight())
						{
							derniereIntersection = lLeft ;
							rougeClignotant('B',0,2);
						}
					else
						if(isCenter())
						{
							derniereIntersection = tRight ;
						}
				}
				else if(isCenter()&& !isLeft() && isRight())
				{
					while(isCenter()&& !isLeft() && isRight())
					
					avancerRobot(50 , 50);
					_delay_ms(100);
					if(!isCenter()&& !isLeft() && !isRight())
					{
						derniereIntersection = lRight ;
						rougeClignotant('B',0,2);
					}
					else
						if(isCenter())
						{
							derniereIntersection = tLeft ;
							rougeClignotant('B',0,2);
						}
				}
				else
					
					derniereIntersection = noIntersection ;
			}	
			else
				reculerRobot(50 , 50);
			
		}
	
}
///////////////////////////////////////TEST///////////////////////////////////////

int main()
{	initialiserSuiveurDeLigne();
    vertClignotant('B',0,40);
    //for(uint8_t i =);
    activerMoteurs();
     avancerRobot(100 , 100);
    _delay_ms(100);
    
    
    while( derniereIntersection == noIntersection)
		detecterPremiereIntersection();
    
   // while(1) tournerADroite(100); 
    //tournerAGauche(VITESSEMOTEURDROITE);
   // avancerRobot(90 , 90);
    //_delay_ms(2000);
   // balayerZone(VITESSEINTERSECTIONDROITE , VITESSEINTERSECTIONGAUCHE , TEMPS_BALAYAGE_MS);
    
     //arreterRobot();
    

   // while (1) suivreTrajet();
    while (1) {
	
	
	//suivreTrajet();  
	switch(detecteTypeIntersection())
	{
	    case tLeft :
		    
		    //reculerRobot(99, 99);
		    //_delay_ms(1000);
		    break;
	    case tRight :
		    garderRougeAllume('B',0);
		    break;
	    case noIntersection:
		    suivreTrajet();
		    break;
		 case lLeft:
		    
		    while(!isCenter())
				tournerAGauche(65);
				suivreTrajet();
		    break;
		   case lRight:
		    
		    while(!isCenter())
				tournerADroite(65);
				suivreTrajet();
		    break;
		 case tBase :
		    garderRougeAllume('B',0);
		    break;
		   case cross:
		    
		    garderVertAllume('B',0); 
		    break;
	    default :
		reculerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
		    break;
	}
    
    

}



	return 0;
}
