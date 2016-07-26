/**************************************************************************//**
 * @file LCD.h
 * @author Najib Arbaoui
 * @Date   11 Novembre 2013
 * 
 * @Details Ce code permet d'afficher quatres valeurs sur l'ecran LCD en 
 * 		    utilisant la fonction WriteValue avec soit un char*, un int ou 
 * 		    un float.
 *		    |V0:.....V1:.....|
 *		    |V2:.....V3:.....|
 *****************************************************************************/
 
#ifndef LCD_H
#define LCD_H

/**************************************************************************//**
 * @defgroup Lcd
 * @brief Permet de gerer l'ecriture sur l'ecran lcd pour debugger.
 *****************************************************************************/

#include "robotUtils.h"

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
  
  
 /**************************************************************************//**
 * @ingroup Lcd
 * @brief WriteValue (INT)
 * @param lcd Classe LCM pour utiliser la fonction write sur le bon port.
 * @param value Valeur a etre ecrite.
 * @param value_number Numero de la valeur soit (0, 1, 2, 3) pour V0 a V3.
 *****************************************************************************/
void writeValue( LCM* lcd, 
				  const int& value, 
				  const uint8_t& value_number );


/**************************************************************************//**
 * @ingroup Lcd
 * @brief WriteValue ( FLOAT ).
 * @param lcd Classe LCM pour utiliser la fonction write sur le bon port.
 * @param value Valeur a etre ecrite entre [0.00 et 999.99].
 * @param value_number Numero de la valeur soit (0, 1, 2, 3) pour V0 a V3.
 *****************************************************************************/
void writeValue( LCM* lcd, 
				  const float& value,
				  const uint8_t& value_number );


/**************************************************************************//**
 * @ingroup Lcd
 * @brief WriteValue ( STRING ).
 * @param lcd Classe LCM pour utiliser la fonction write sur le bon port.
 * @param value String de 5 characteres maximum.
 * @param value_number Numero de la valeur soit (0, 1, 2, 3) pour V0 a V3.
 *****************************************************************************/
void writeValue( LCM* lcd, 
				  const char* txt,
				  const uint8_t& value_number );


/**************************************************************************//**
 * @ingroup Lcd
 * @brief writeVx est une fonction interne utilisee par writeValue(..) 
 * 		  pour afficher Vx de 0 a 3.
 * @param lcd Classe LCM pour utiliser la fonction write sur le bon port.
 * @param tmp Buffer pour utiliser itoa dans la fonction. ( la valeur du 
 * 			  buffer sera alteree ).
 * @param value_number Numero de la valeur soit (0, 1, 2, 3) pour V0 a V3.
 *****************************************************************************/
uint16_t writeVx( LCM* lcd, 
				  char* tmp, 
				  const uint8_t& value_number );

#endif // LCD_H.