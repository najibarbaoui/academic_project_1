/**************************************************************************//**
 * @file aleatoire.h
 * @author Najib Arbaoui
 * @Date   27 Novembre 2013
 *****************************************************************************/
 
#ifndef ALEATOIRE_H
#define ALEATOIRE_H

/**************************************************************************//**
 * @defgroup Aleatoire
 * @brief Permet de gerer les deplacements aleatoires.
 *****************************************************************************/

#include "robotUtils.h"

/**************************************************************************//**
 * @ingroup Aleatoire
 * @brief Permet d'initialiser le timer2 pour creer un pseudo aleatoire.
 *****************************************************************************/
void initTimerAleatoire();

/**************************************************************************//**
 * @ingroup Aleatoire
 * @brief Retourne une valeur aleatoire de type Direction. (50% des changes
 * 	      que le resultat soit direction_continue et 25% des chances pour 
 * 		  chancun 	que le resultat soit direction_left ou direction_right).
 *****************************************************************************/
Direction prendreValeurAleatoire();

#endif // ALEATOIRE_H.
