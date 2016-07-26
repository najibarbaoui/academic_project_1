/**************************************************************************//**
 * @file robotUtils.h
 * @author Najib Arbaoui
 * @Date   11 Novembre 2013
 * 
 * @Details Ce fichier definit des macros pour faciliter le code.
 * 			Il contient aussi l'initialisation et les includes généraux.
 * 			Tous les fichiers peuvent appeler ce header.
 *****************************************************************************/
#ifndef AVR_ROBOT_UTILS_H
#define AVR_ROBOT_UTILS_H

/**************************************************************************//**
 * @defgroup RobotUtils
 * @brief Permet de gerer plusieurs structures pour le robot.
 *****************************************************************************/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <stdio.h> 
#include <stdlib.h> 

#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

//#define __DELAY_BACKWARD_COMPATIBLE__

#define PIN_INPUT 0x0
#define PIN_OUTPUT 0x1
#define PORT_INPUT 0x00
#define PORT_OUTPUT 0xFF

#define HIGH 0x1
#define LOW  0x0

#define nbClockPerUs() ( F_CPU / 1000000L )
#define msToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define readBit(value, bit) ( ( (value) >> (bit) ) & 0x01 )
#define setBit(value, bit) ( (value) |= ( 1UL << (bit) ) )
#define clearBit(value, bit) ( (value) &= ~( 1UL << (bit) ) )
#define writeBit(value, bit, bitvalue) ( bitvalue ? setBit(value, bit) \
										  : clearBit(value, bit) )
		
#define delay_ms( delayMs ) for(uint16_t i = 0; i < delayMs; ++i) _delay_ms(1);

#define VITESSEMOTEURGAUCHE 55
#define VITESSEMOTEURDROITE 55
#define VITESSEINTERSECTIONDROITE 40
#define VITESSEINTERSECTIONGAUCHE 40
#define VITESSEBALAYAGE 40

// Dimuner la vitesse d un des moteurs pour permet
// au robot de tourner sans arreter une roue.
#define PENTEPOURTOURNER 30

// Permet de diminuer un peu la vitesse si on a dévié du
// trajet et atteint l'état perdu, sans toucher les côtés.
#define MOYENNE_PENTEPOURTOURNER 10

// Permet de diminuer legèrement la vitesse du côté qui a
// atteint l'intersection en premier.
#define PETITE_PENTEPOURTOURNER 3

#define TEMPS_BALAYAGE_MS 500

 /**************************************************************************//**
 * @ingroup RobotUtils
 * @brief Enumeration pour les directions.
 *****************************************************************************/
enum Direction
{
	direction_continue,
	direction_left,
	direction_right,
	direction_reculer
};

 /**************************************************************************//**
 * @ingroup RobotUtils
 * @brief Enumeration pour le capteur de ligne.
 *****************************************************************************/
enum Capteur
{ 
	capteur_aucun = 255, 
	capteur_droit = PINA5, 
	capteur_centre = PINA3, 
	capteur_gauche = PINA1 
};

 /**************************************************************************//**
 * @ingroup RobotUtils
 * @brief Enumeration de tous les intersections possibles.
 *****************************************************************************/
enum Intersection
{ 
	inter_none, 
	inter_cross, 
	inter_tBase, 
	inter_tLeft, 
	inter_tRight, 
	inter_lLeft, 
	inter_lRight 
};

// Sauvegarder le type d'intersection franchie.
extern Intersection lastIntersection; 

// Le dernier capteur qui a été activé.
extern Capteur dernierCapteurActif;

// Le dernier capteur qui a été activé, mais ignore le capteur central.
extern Capteur dernierCapteurCoteActif;

///@todo décider quoi faire si on détecte une intersection invalide...
// Retiennent les types d'intersection possible pour éviter les lectures impossibles.
extern Intersection possibiliteIntersection1;
extern Intersection possibiliteIntersection2;

// utilisé par moteur.cpp pour savoir si la vitesse courante est à 0, pour donner un "boost" si nécessaire..
extern uint8_t vitesseCouranteGauche;
extern bool directionCouranteGaucheAvance;
extern uint8_t vitesseCouranteDroite;
extern bool directionCouranteDroiteAvance;

#endif
