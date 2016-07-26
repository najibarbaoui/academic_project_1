/**************************************************************************//**
 * @file midi.h
 * @author Najib Arbaoui
 * @Date   11 Novembre 2013
 * 
 * @Details Ce code permet de jouer une note midi de 45 a 81 en utilisant le 
 *          Timer0 avec un interrupt.
 *****************************************************************************/
 
#ifndef MIDI_NOTES_H
#define MIDI_NOTES_H

/**************************************************************************//**
 * @defgroup Audio
 * @brief Permet de faire jouer un son ou une note midi.
 *****************************************************************************/

#include "robotUtils.h"

/**************************************************************************//**
 * @ingroup Audio
 * @brief Permet de faire jouer un son.
 * @param v Valeur de 0 a 255.
 *****************************************************************************/
void jouerSon( const uint8_t& v );

/**************************************************************************//**
 * @ingroup Audio
 * @brief jouerNote permet de jouer une note midi de 45 a 81.
 * @param midi_note Note midi a jouer.
 *****************************************************************************/
void jouerNote( const uint8_t& midi_note );


/**************************************************************************//**
 * @ingroup Audio
 * @brief silence permet d'arreter le piezo de jouer la note en cour.
 *****************************************************************************/
void silence();


/**************************************************************************//**
 * @ingroup Audio
 * @brief timer0_init permet d'initialiser les bonnes valeurs de prescale et 
 *        d'initiation du Timer0.
 *****************************************************************************/
void timer0_init(void);

#endif // MIDI_NOTES_H.
