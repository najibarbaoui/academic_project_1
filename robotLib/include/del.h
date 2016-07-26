/**************************************************************************//**
 * @file del.h
 *****************************************************************************/
 
#ifndef _DEL_H
#define _DEL_H

#include "robotUtils.h"

/**************************************************************************//**
 * @defgroup Del
 * @brief Permet de controller la del.
 *****************************************************************************/

#define DEL_VERT  ( 1 )
#define DEL_ROUGE ( 2 )

 /**************************************************************************//**
 * @ingroup Del
 * @brief Permet de faire clignoter un del, soit en rouge ou en vert.
 * @param ddr Permet de choisir le port de configuration des entrees sorties.
 * @param port Choisir le port sur lequel le del se trouve.
 * @param pin Choisir la premiere pin ou le del est connecte (0-7).
 * @param nfois Choisir le nombre de fois que le del clignotera.
 * @param color Choisir si le del clignote en rouge ou en vert. 
 * 			    ( DEL_VERT, DEL_ROUGE )
 *****************************************************************************/
void clignoterDel( volatile uint8_t* ddr, 
				   volatile uint8_t* port, 
				   const uint8_t& pin, 
				   const uint16_t& nfois,
				   const uint8_t& color );


 /**************************************************************************//**
 * @ingroup Del
 * @brief Permet d'allumer un del pendant un certain temps, 
 * 		  soit en rouge ou en vert.
 * @param ddr Permet de choisir le port de configuration des entrees sorties.
 * @param port Choisir le port sur lequel le del se trouve.
 * @param pin Choisir la premiere pin ou le del est connecte.
 * @param temps Choisir le nombre de temps que le del sera allume (par tranche
 * 				 de 100 millisecondes).
 * @param color Choisir si le del clignote en rouge ou en vert. 
 * 			    ( DEL_VERT, DEL_ROUGE )
 *****************************************************************************/
void allumerDel( volatile uint8_t* ddr, 
                 volatile uint8_t* port,
                 const uint8_t& pin,
                 const uint16_t& temps_ms,
                 const uint8_t& color );


 /**************************************************************************//**
 * @ingroup Del
 * @brief Permet d'allumer un del, soit en rouge ou en vert.
 * @param ddr Permet de choisir le port de configuration des entrees sorties.
 * @param port Choisir le port sur lequel le del se trouve.
 * @param pin Choisir la premiere pin ou le del est connecte.
 * @param color Choisir si le del clignote en rouge ou en vert. 
 * 			    ( DEL_VERT, DEL_ROUGE )
 *****************************************************************************/
void garderAllumerDel( volatile uint8_t* ddr, 
                       volatile uint8_t* port,
                       const uint8_t& pin,
                       const uint8_t& color );


/**************************************************************************//**
 * @ingroup Del
 * @brief Permet d'eteindre un del.
 * @param ddr Permet de choisir le port de configuration des entrees sorties.
 * @param port Choisir le port sur lequel le del se trouve.
 * @param pin Choisir la premiere pin ou le del est connecte.
 *****************************************************************************/
void eteindreDel( volatile uint8_t* ddr, 
				  volatile uint8_t* port, 
				  const uint8_t& pin );
#endif
 
