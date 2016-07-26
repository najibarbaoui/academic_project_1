/**************************************************************************//**
 * @file photoresistance.h
 * @author Najib Arbaoui
 * @Date   27 Novembre 2013
 *****************************************************************************/

#ifndef _PHOTORESISTANCE_H
#define _PHOTORESISTANCE_H

/**************************************************************************//**
 * @defgroup PhotoResistance
 * @brief  Capte les valeurs des photoresistances pour le robot souris .
 *****************************************************************************/

 #include "robotUtils.h"

 /**************************************************************************//**
 * @ingroup PhotoResistance
 * @brief Fonction qui retourne la luminosite de gauche suite à une nouvelle 
 *        lecture de la photoresistance de gauche (port #7).
 * @return La valeur de la luminosite de gauche (0 - 255, sombre à clair) .
 *****************************************************************************/
uint8_t luminositeGauche();


 /**************************************************************************//**
 * @ingroup PhotoResistance
 * @brief Fonction qui retourne la luminosite de droite suite à une nouvelle 
 *        lecture de la photoresistance de droite (port #8).
 * @return La valeur de la luminosite de droite (0 - 255, sombre à clair).
 *****************************************************************************/
uint8_t luminositeDroite();


/**************************************************************************//**
 * @ingroup PhotoResistance
 * @brief Fonction qui retourne l'état d'illumination de la photoresistance 
 * 		  de gauche.
 * @return Vrai lorsque la photoresistance de gauche détecte une illumination  .
 *****************************************************************************/
bool isIllumineGauche();


/**************************************************************************//**
 * @ingroup PhotoResistance
 * @brief  Fonction qui retourne l'état d'illumination de la photoresistance 
 *         de droite.
 * @return Vrai lorsque la photoresistance de droite détecte une illumination .
 *****************************************************************************/
bool isIllumineDroite();


/**************************************************************************//**
 * @ingroup PhotoResistance
 * @brief  Fonction qui affiche les valeurs lues par les photoresistances au 
 *         display branché au port C.
*          À mettre dans une boucle si on veut afficher continuellement.                                    
*          La fonction comprend un délai de 400ms à la fin.  
 *****************************************************************************/
void afficherPhotoresistances();

#endif //_PHOTORESISTANCE_H