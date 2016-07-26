#include "moteur.h"

uint8_t vitesseCouranteGauche = 0;
bool directionCouranteGaucheAvance = true;
uint8_t vitesseCouranteDroite = 0;
bool directionCouranteDroiteAvance = true;

void activerMoteurs() 
{
	//DDRD = 0xFF; // Le portD est mis en mode sortieD 
	DDRD = 0b11111011;
	
	// Configuration du registre pour avoir le mode PWM, Phase correct , 8 bit (Mode 1, documentation Atmel 324pa, tableau 15-5, page 136)
	// les valeurs du registre change lorsque la comparaison esr vraie dans l'incrementation et decrementation, la valeur du compteur varie entre 0 et 255 (2^8bits = 256 valeurs)
	
	TCCR1A = (1 << COM1A0) | 
	         (1 << COM1A1) | 
	         (1 << COM1B0) |
	         (1 << COM1B1) | 
	         (1 << WGM10)  | 
	         (0 << WGM11); 
	
	// Diviser la fequence de CLK sur 8, permet d'avoir une PWM précise (8 MHZ / 8 = 1 MHZ)
	
	TCCR1B = (0 << WGM13) | 
			 (0 << WGM12) | 
			 (0 << CS10)  | 
			 (1 << CS11)  | 
			 (0 << CS12); 
	
	ajusterPWM (255, 255); //On s'assure que les roues tournent pas
	_delay_ms(10);
	
// 	DDRD |= 0xF0; // Le portD, broches #5,6,7,8 sont mis en mode sortie
// 	
// 	ajusterPWM (255, 255); // On s'assure que les roues tournent pas.
// 	vitesseCouranteGauche = 0;
// 	directionCouranteGaucheAvance = true;
// 	vitesseCouranteDroite = 0;
// 	directionCouranteDroiteAvance = true;
// 	
// 	// Configuration du registre pour avoir le mode PWM, Phase correct , 
// 	// 8 bit (Mode 1, documentation Atmel 324pa, tableau 15-5, page 136)
// 	// les valeurs du registre change lorsque la comparaison est vraie 
// 	// dans l'incrementation et decrementation, la valeur du compteur 
// 	// varie entre 0 et 255 (2^8bits = 256 valeurs)
// 	
// 	TCCR1A = (1 << COM1A0) |
// 			 (1 << COM1A1) | 
// 			 (1 << COM1B0) |
// 			 (1 << COM1B1) | 
// 			 (1 << WGM10)  | 
// 			 (0 << WGM11); 
// 	
// 	// Diviser la fequence de CLK sur 8, 
//     // permet d'avoir une PWM précise (8 MHZ / 8 = 1 MHZ).
// 	TCCR1B = (0 << WGM13) | 
// 			 (0 << WGM12) | 
// 			 (0 << CS10)  | 
// 			 (1 << CS11)  | 
// 			 (0 << CS12); 
}

void ajusterPWM ( const uint8_t& valeurRegistreComparaisonA, 
				  const uint8_t& valeurRegistreComparaisonB )
{
	OCR1A = valeurRegistreComparaisonA;
	OCR1B = valeurRegistreComparaisonB;
} 

uint8_t convertirPourcentageEnInt( const uint8_t& pourcentage )
{
		uint8_t valeurRegistreComparaison ;
		valeurRegistreComparaison = (uint8_t)((uint8_t)255 - (((uint8_t)255 * (uint8_t)pourcentage)/(uint8_t)100));
		return valeurRegistreComparaison;
}

void avancer( const uint8_t& vitesseMoteurGauche,
			  const uint8_t& vitesseMoteurDroit )
{
	//ajusterPWM( 90, 90);
	ajusterPWM( 255 - vitesseMoteurDroit,  
				255- vitesseMoteurGauche  );
	
	//sauvegarde l'état des moteurs
// 	vitesseCouranteGauche = vitesseMoteurGauche;
// 	directionCouranteGaucheAvance = true;
// 	vitesseCouranteDroite = vitesseMoteurDroit;
// 	directionCouranteDroiteAvance = true;
	PORTD &= ~( (1 << 0x07) | (1 << 0x06) );
}

void avancerRobot( const uint8_t& vitesseMoteurDroit, 
				   const uint8_t& vitesseMoteurGauche )
{
	/*
	// "boost" si le moteur ne roule pas ou est dans le sens inverse
	if ( ( vitesseCouranteGauche == 0 || !directionCouranteGaucheAvance 
		|| vitesseCouranteDroite == 0 || !directionCouranteDroiteAvance ) 
		&& vitesseMoteurGauche != 0 && vitesseMoteurDroit != 0 )
	{
		ajusterPWM( convertirPourcentageEnInt( (vitesseMoteurDroit != 0 ? 100 : 0) ),  
					convertirPourcentageEnInt( (vitesseMoteurGauche != 0 ? 100 : 0) ) );
		PORTD &= ~( (1 << 0x07) | (1 << 0x06) );
		_delay_ms(10);
	}
	*/
	ajusterPWM( 90, 90);
	ajusterPWM( convertirPourcentageEnInt( vitesseMoteurDroit ),  
				convertirPourcentageEnInt( vitesseMoteurGauche ) );
	
	//sauvegarde l'état des moteurs
	vitesseCouranteGauche = vitesseMoteurGauche;
	directionCouranteGaucheAvance = true;
	vitesseCouranteDroite = vitesseMoteurDroit;
	directionCouranteDroiteAvance = true;
	PORTD &= ~( (1 << 0x07) | (1 << 0x06) );
}

void reculerRobot( const uint8_t& vitesseMoteurDroit, 
				   const uint8_t& vitesseMoteurGauche )
{
	/*
	// "boost" si le moteur ne roule pas ou est dans le sens inverse
	if ( ( vitesseCouranteGauche == 0 || directionCouranteGaucheAvance 
		|| vitesseCouranteDroite == 0 || directionCouranteDroiteAvance ) 
		&& vitesseMoteurGauche != 0 && vitesseMoteurDroit != 0 )
	{
		ajusterPWM( convertirPourcentageEnInt( (vitesseMoteurDroit != 0 ? 100 : 0) ),  
					convertirPourcentageEnInt( (vitesseMoteurGauche != 0 ? 100 : 0) ) );
		PORTD |= (1 << 0x07) | (1 << 0x06) ;
		_delay_ms(10);
	}
	*/
	ajusterPWM( convertirPourcentageEnInt( vitesseMoteurDroit ),  
				convertirPourcentageEnInt( vitesseMoteurGauche ) );
	PORTD |= (1 << 0x07) | (1 << 0x06) ;
	
	//sauvegard l'état des moteurs
	vitesseCouranteGauche = vitesseMoteurGauche;
	directionCouranteGaucheAvance = false;
	vitesseCouranteDroite = vitesseMoteurDroit;
	directionCouranteDroiteAvance = false;
}

void tournerAGauche( const uint8_t& vitesseMoteurDroit )
{
	avancerRobot( vitesseMoteurDroit , 0 );	
}

void tournerADroite( const uint8_t& vitesseMoteurGauche )
{
	avancerRobot( 0 , vitesseMoteurGauche );
}

void arreterRobot()
{
	ajusterPWM( 255 , 255);
	
	_delay_ms(100); //délai pour s'assurer que le robot est complètement arrêté
	
	//sauvegarder l'état
	vitesseCouranteGauche = 0;
	directionCouranteGaucheAvance = true;
	vitesseCouranteDroite = 0;
	directionCouranteDroiteAvance = false;
}

void stopRobotNow()
{
	ajusterPWM( 255 , 255);
	
	//_delay_ms(100); //délai pour s'assurer que le robot est complètement arrêté
	
	//sauvegarder l'état
	vitesseCouranteGauche = 0;
	directionCouranteGaucheAvance = true;
	vitesseCouranteDroite = 0;
	directionCouranteDroiteAvance = false;
}

void desactiverMoteur()
{
	// Initialise les bits de registre a 0 permet de deconnecter les timers.
	TCCR1A = (0 << COM1A1) | (0 << COM1B1) | (0 << COM1A0) | (0 << COM1B0);
	
	vitesseCouranteGauche = 0;
	directionCouranteGaucheAvance = true;
	vitesseCouranteDroite = 0;
	directionCouranteDroiteAvance = false;
}

void pivoterHoraire( const uint8_t& vitesse )
{
	/*
	// "boost" si le moteur ne roule pas ou est dans le sens inverse
	if ( ( (vitesseCouranteGauche == 0 || !directionCouranteGaucheAvance)
		|| (vitesseCouranteDroite == 0 || directionCouranteDroiteAvance) ) && vitesse != 0  )
		{
			ajusterPWM( convertirPourcentageEnInt( 70 ),  
						convertirPourcentageEnInt( 70 ) );
			PORTD &= ~(1 << 0x06) ;
			PORTD |= (1 << 0x07)  ;
			_delay_ms(5);
		}
		*/
	ajusterPWM( convertirPourcentageEnInt( vitesse ),  
				convertirPourcentageEnInt( vitesse ) );
	PORTD &= ~(1 << 0x06) ;
	PORTD |= (1 << 0x07)  ;
	
	//sauvegarder l'état des moteurs
	vitesseCouranteGauche = vitesse;
	directionCouranteGaucheAvance = true;
	vitesseCouranteDroite = vitesse;
	directionCouranteDroiteAvance = false;
}

void pivHoraire( const uint8_t& vitesse )
{
	ajusterPWM( 255 - vitesse, 255 - vitesse );
	PORTD &= ~(1 << 0x06) ;
	PORTD |= (1 << 0x07)  ;
}

void pivAntiHoraire( const uint8_t& vitesse )
{
	ajusterPWM( 255 - vitesse, 255 - vitesse );
	PORTD &= ~(1 << 0x07) ;
	PORTD |= (1 << 0x06)  ;
}

void pivoterAntiHoraire( const uint8_t& vitesse )
{
	/*
	// "boost" si le moteur ne roule pas ou est dans le sens inverse
	if ( ( (vitesseCouranteGauche == 0 || !directionCouranteGaucheAvance)
		|| (vitesseCouranteDroite == 0 || directionCouranteDroiteAvance) ) && vitesse != 0  )
	{
		ajusterPWM( convertirPourcentageEnInt( 70 ),  
					convertirPourcentageEnInt( 70 ) );
		PORTD &= ~(1 << 0x07) ;
		PORTD |= (1 << 0x06)  ;
		_delay_ms(5);
	}
	*/
	
	ajusterPWM( convertirPourcentageEnInt( vitesse ),  
				convertirPourcentageEnInt( vitesse ) );
	PORTD &= ~(1 << 0x07) ;
	PORTD |= (1 << 0x06)  ;
	
	//sauvegarder l'état des moteurs
	vitesseCouranteGauche = vitesse;
	directionCouranteGaucheAvance = false;
	vitesseCouranteDroite = vitesse;
	directionCouranteDroiteAvance = true;
}

void ajusterDroite( const uint8_t& vitesseMoteurDroit, 
					const uint8_t& vitesseMoteurGauche, 
					const uint8_t& pentePourTourner )
{
	avancerRobot( vitesseMoteurDroit - pentePourTourner, 
				  vitesseMoteurGauche );
}

void ajusterGauche( const uint8_t& vitesseMoteurDroit, 
					const uint8_t& vitesseMoteurGauche, 
					const uint8_t& pentePourTourner )
{
	avancerRobot( vitesseMoteurDroit, 
				  vitesseMoteurGauche  - pentePourTourner );
}
