#include "moteur.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : activerMoteurs(void)                                                                                         //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																														    //	
//  La fonction qui active les moteurs en initialisant les registres du timer 1                                             //
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void activerMoteurs() 
{
	DDRD = 0xff; // Le portD est mis en mode sortie
	
	ajusterPWM (255, 255); //On s'assure que les roues tournent pas
	
	// Configuration du registre pour avoir le mode PWM, Phase correct , 8 bit (Mode 1, documentation Atmel 324pa, tableau 15-5, page 136)
	// les valeurs du registre change lorsque la comparaison esr vraie dans l'incrementation et decrementation, la valeur du compteur varie entre 0 et 255 (2^8bits = 256 valeurs)
	
	TCCR1A = (1 << COM1A0) |(1 << COM1A1) | (1 << COM1B0) |(1 << COM1B1) | (1 << WGM10) | (0 << WGM11); 
	
	// Diviser la fequence de CLK sur 8, permet d'avoir une PWM précise (8 MHZ / 8 = 1 MHZ)
	
	TCCR1B = (0 << WGM13) | (0 << WGM12) | (0 << CS10) | (1 << CS11) | (0 << CS12); 
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : ajusterPWM(uint16_t valeurRegistreComparaisonA, uint16_t valeurRegistreComparaisonB)                         //
//  Paramètres :   uint16_t valeurRegistreComparaisonA = valeur de comparaison mise dans le registre OCR1A 					//
//                 uint16_t valeurRegistreComparaisonB =  = valeur de comparaison mise dans le registre OCR1B               //
//	Retour : aucun                                                                                                          //
//																														    //	
//  La fonction qui ajuster le rapport A/B du PWM en mettant les valeurs de comparaison dans les registres OCR1A et OCRB1   //
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ajusterPWM (uint8_t valeurRegistreComparaisonA, uint8_t valeurRegistreComparaisonB)
{

	OCR1A = valeurRegistreComparaisonA;
	OCR1B = valeurRegistreComparaisonB;
	
// valeurRegistreComparaisonA= valeurRegistreComparaisonB = 255-255*0% = 255	       (O%)
// valeurRegistreComparaisonA= valeurRegistreComparaisonB = 255-255*25% = 191,25 = 191 (25%)
// valeurRegistreComparaisonA= valeurRegistreComparaisonB = 255-255*50% = 127,5 = 128  (50%)
// valeurRegistreComparaisonA= valeurRegistreComparaisonB = 255-255*75% = 63,75 = 64   (75%)
// valeurRegistreComparaisonA= valeurRegistreComparaisonB = 255-255*100% = 0 		   (100%)
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction :  convertirPourcentageEnInt(uint8_t pourcentage )                                                             //
//  Paramètres :  pourcentage      (entre 0 et 100)                                                                         //
//	Retour :       uint16_t                                                                                                 //
//																															//	
//  La fonction qui convertit un pourcentage en valeur entiere  pour generer  la PWM correspondante                         // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t convertirPourcentageEnInt(uint8_t pourcentage )
{
		uint8_t valeurRegistreComparaison ;
		valeurRegistreComparaison = (uint8_t)(255 - ((255 * pourcentage)/100)); 
		return valeurRegistreComparaison;
		

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : avancerRobot()                                            		                                            //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																															//	
//  La fonction qui fait avancer le robot, on avance le moteur droit et gauche en meme temps                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void avancerRobot(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche)
{
			ajusterPWM( convertirPourcentageEnInt(vitesseMoteurDroit) ,  convertirPourcentageEnInt(vitesseMoteurGauche));
			PORTD &= (0 << 0x07) | (0 << 0x06) ;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : reculerRobot()                                            		                                            //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																															//	
//  La fonction qui fait reculer le robot, en mettant le moteur droit et gauche en marche arriere                           // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reculerRobot(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche)
{
	ajusterPWM( convertirPourcentageEnInt(vitesseMoteurDroit),  convertirPourcentageEnInt(vitesseMoteurGauche));
	PORTD |= (1 << 0x07) | (1 << 0x06) ;
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : tournerAGauche()                                            		                                            //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																															//	
//  La fonction qui tourner le robot a Gauche, on arrete le moteur gauche et on avance le moteur droit                      // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tournerAGauche(uint8_t vitesseMoteurDroit)
{
	avancerRobot(vitesseMoteurDroit , 0);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : tournerADroite()                                            		                                            //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																															//	
//  La fonction qui tourner le robot a droite, on arrete le moteur droit et on avance le moteur gauche                      // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tournerADroite(uint8_t vitesseMoteurGauche)
{
		avancerRobot( 0 , vitesseMoteurGauche);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : arreterRobot()                                            		                                            //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																															//	
//  La fonction qui fait arreter le robot, en arretant le moteur droit et gauche                                            // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void arreterRobot()
{
	ajusterPWM( 255 , 255);
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : desactiverMoteur()                                            	                                            //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																															//	
//  La fonction qui desactive les moteurs										                                            // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void desactiverMoteur()
{
	TCCR1A = (0 << COM1A1) | (0 << COM1B1) | (0 << COM1A0) | (0 << COM1B0); // on initialise les bits de registre a 0 permet de deconnecter les timers 
	
}



void pivoterHoraire(uint8_t vitesse)
{
	
	

			
			
			
			ajusterPWM( convertirPourcentageEnInt(vitesse) ,  convertirPourcentageEnInt(vitesse));
			PORTD &=~(1 << 0x06) ;
			PORTD |= (1 << 0x07)  ;
			
	
}

void pivoterAntiHoraire(uint8_t vitesse)
{
			ajusterPWM( convertirPourcentageEnInt(vitesse) ,  convertirPourcentageEnInt(vitesse));
			PORTD &=~(1 << 0x07) ;
			PORTD |= (1 << 0x06)  ;
			
	
}
void ajusterDroite(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche , uint8_t pentePourTourner)
{
	avancerRobot(vitesseMoteurDroit - pentePourTourner , vitesseMoteurGauche );
}
void ajusterGauche(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche , uint8_t pentePourTourner )
{
	avancerRobot(vitesseMoteurDroit , vitesseMoteurGauche  - pentePourTourner );
}
