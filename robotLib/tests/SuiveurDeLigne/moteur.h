#ifndef _MOTEUR_H
#define _MOTEUR_H

#include <avr/io.h>
#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

void activerMoteurs() ;
void desactiverMoteur();
void ajusterPWM (uint8_t valeurRegistreComparaisonA, uint8_t valeurRegistreComparaisonB);
uint8_t convertirPourcentageEnInt(uint8_t pourcentage );
void tournerAGauche(uint8_t vitesseMoteurDroit);
void tournerADroite(uint8_t vitesseMoteurGauche);
void avancerRobot(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche);
void reculerRobot(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche);
void pivoterAntiHoraire(uint8_t vitesse);
void pivoterHoraire(uint8_t vitesse);
void ajusterDroite(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche , uint8_t PENTEPOURTOURNER );
void ajusterGauche(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche , uint8_t PENTEPOURTOURNER );


void arreterRobot();

#endif
