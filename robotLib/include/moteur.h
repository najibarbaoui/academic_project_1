/**************************************************************************//**
 * @file moteur.h
 * @author Najib Arbaoui
 *****************************************************************************/
 
#ifndef _MOTEUR_H
#define _MOTEUR_H

/**************************************************************************//**
 * @defgroup Moteur
 * @brief Permet de la vitesse des deux moteurs.
 *****************************************************************************/

#include "robotUtils.h"

 /**************************************************************************//**
 * @ingroup Moteur
 * @brief activerMoteurs, permet d'activer les moteurs en initialisant les 
 *        registres du timer 1.
 *****************************************************************************/
void activerMoteurs() ;


 /**************************************************************************//**
 * @ingroup Moteur
 * @brief La fonction qui fait arreter le robot, en arretant le moteur 
 * 		  droit et gauche.
 *****************************************************************************/
void desactiverMoteur();


 /**************************************************************************//**
 * @ingroup Moteur
 * @brief ajusterPWM ajuste le rapport A/B du PWM en mettant les valeurs de 
 * 		  comparaison dans les registres OCR1A et OCRB1.
 * 
 * @param valeurRegistreComparaisonA Valeur de comparaison mise 
 * 									  dans le registre OCR1A.
 * 
 * @param valeurRegistreComparaisonB Valeur de comparaison mise dans le 
 * 								      registre OCR1B.
 *****************************************************************************/
void ajusterPWM ( const uint8_t& valeurRegistreComparaisonA, 
				  const uint8_t& valeurRegistreComparaisonB );

void avancer( const uint8_t& vitesseMoteurGauche,
			  const uint8_t& vitesseMoteurDroit );

 /**************************************************************************//**
 * @ingroup Moteur
 * @brief convertirPourcentageEnInt convertit un pourcentage en valeur 
 * 		  entiere pour generer le PWM correspondante.
 * @param pourcentage Valeur entre 0.0 et 100.0.
 * @return Retour la valeur en pourcentage.
 *****************************************************************************/
uint8_t convertirPourcentageEnInt( const uint8_t& pourcentage );


 /**************************************************************************//**
 * @ingroup Moteur
 * @brief tournerAGauche permet de tourner le robot a gauche, 
 * 		   on arrete le moteur gauche et on avance le moteur droit.
 * @param vitesseMoteurDroit Permet de choisir la vitesse pour tourner.
 *****************************************************************************/
void tournerAGauche( const uint8_t& vitesseMoteurDroit );


 /**************************************************************************//**
 * @ingroup Moteur
 * @brief tournerADroite permet de tourner le robot a droite, 
 * 		   on arrete le moteur droite et on avance le moteur gauche.
 * @param vitesseMoteurGauche Permet de choisir la vitesse pour tourner.
 *****************************************************************************/
void tournerADroite( const uint8_t& vitesseMoteurGauche );


 /**************************************************************************//**
 * @ingroup Moteur
 * @brief avacerRobot permet d'avancer le robot, on avance le moteur droit 
 * 		  et gauche en meme temps.
 * @param vitesseMoteurDroit Permet de choisir la vitesse du moteur droit.
 * @param vitesseMoteurGauche Permet de choisir la vitesse du moteur gauche.
 *****************************************************************************/
void avancerRobot( const uint8_t& vitesseMoteurDroit, 
				   const uint8_t& vitesseMoteurGauche );


 /**************************************************************************//**
 * @ingroup Moteur
 * @brief reculerRobot permet de reculer le robot, on met en marche arriere 
 * 		  le moteur droit et gauche en meme temps.
 * @param vitesseMoteurDroit Permet de choisir la vitesse du moteur droit.
 * @param vitesseMoteurGauche Permet de choisir la vitesse du moteur gauche.
 *****************************************************************************/
void reculerRobot( const uint8_t& vitesseMoteurDroit, 
				   const uint8_t& vitesseMoteurGauche );


 /**************************************************************************//**
 * @ingroup Moteur
 * @brief arreterRobot permet d'arreter le robot, en arretant le moteur 
 * 		  droit et gauche.
 *****************************************************************************/
void arreterRobot();

void stopRobotNow();

void pivAntiHoraire( const uint8_t& vitesse );
void pivHoraire( const uint8_t& vitesse );


///@todo Ajouter description.
void ajusterDroite( const uint8_t& vitesseMoteurDroit, 
                    const uint8_t& vitesseMoteurGauche,
                    const uint8_t& pente_tourner );

///@todo Ajouter description.
void ajusterGauche( const uint8_t& vitesseMoteurDroit, 
                    const uint8_t& vitesseMoteurGauche,
                    const uint8_t& pente_tourner );


///@todo Ajouter description.
void pivoterHoraire( const uint8_t& vitesse );

///@todo Ajouter description.
void pivoterAntiHoraire( const uint8_t& vitesse );


#endif
