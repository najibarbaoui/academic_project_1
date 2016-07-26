/**************************************************************************//**
 * @file lineFollower.h
 * @author Najib Arbaoui
 * @Date   5 Decembre 2013
 * 
 * @Details Permet de suivre le ligne, de detecter les intersections et
 *          de tourner.
 *****************************************************************************/

#ifndef _LINE_FOLLOWER_H
#define _LINE_FOLLOWER_H

/**************************************************************************//**
 * @defgroup LineFollower
 * @brief Permet de suivre le ligne, de detecter les intersections et
 *        de tourner.
 *****************************************************************************/

#include "robotUtils.h"
#include "moteur.h"
#include "del.h"
#include "LCD.h"

 /**************************************************************************//**
 * @ingroup LineFollower
 * @brief Permet la gestion des lignes et intersections.
 * @Details Lorsque le capteur tttraverse une intersection, une fonction passee
 *          en parametre par pointeur est appelee. Cette fonction, definie par 
 *          l'utilisateur, permet de choisir la direction qui le robot prendra.
 *          Si les fonctions pour tourner ne sont pas appelees, le robot va
 *          continuer a avancer. La classe permet egalement de tourner 
 *          automatiquement au intersection aux coins.
 *          
 * @param lcd Classe LCM pour utiliser la fonction write sur le bon port.
 * @param value Valeur a etre ecrite.
 * @param value_number Numero de la valeur soit (0, 1, 2, 3) pour V0 a V3.
 *****************************************************************************/
class LineFollower
{
public:
	LineFollower( void (*func)( LineFollower* follower,
	                            const Intersection& type ) );
	
	/**************************************************************************//**
	* @brief Permet de suivre la ligne et appel la fonction handelIntersection
	* 		 lorsque plus de deux sensors dont detectes.
	*****************************************************************************/
	void followLine();

	/**************************************************************************//**
	* @brief Permet de tourner a gauche.
	*****************************************************************************/	
	void turnLeft();
	
	/**************************************************************************//**
	* @brief Permet de tourner a droite.
	*****************************************************************************/	
	void turnRight();
	
private:
	
	//bool m_more_than_two_lights_on;
	Direction m_last_straight_line_direction;
	
	/// Variable pour se rappeler de la fonction a appeler.
	void (*m_fct_ptr)( LineFollower* follower, const Intersection& type);
	
	static const uint8_t c_moteur_speed;
	static const uint8_t c_slope_speed;
	
	/**************************************************************************//**
	* @brief Permet de savoir si le capteur central est detectee.
	*****************************************************************************/
	bool isCenter();		
	
	/**************************************************************************//**
	* @brief Permet de savoir si le capteur de gauche est detectee.
	*****************************************************************************/
	bool isLeft();
	
	/**************************************************************************//**
	* @brief Permet de savoir si le capteur de droite est detectee.
	*****************************************************************************/	
	bool isRight();

	/**************************************************************************//**
	* @brief Permet de savoir si seulement le capteur central est detectee.
	*****************************************************************************/		
	bool isOnlyCenterOn();
	
	/**************************************************************************//**
	* @brief Permet de savoir si seulement le capteur de gauche est detectee
	*****************************************************************************/		
	bool isOnlyLeftOn();
	
	/**************************************************************************//**
	* @brief Permet de savoir si seulement le capteur de droite est detecteee.
	*****************************************************************************/		
	bool isOnlyRightOn();
	
	/**************************************************************************//**
	* @brief Permet de savoir si le capteur de droite est detectee.
	*****************************************************************************/		
	bool isNotOnLine();
	
	/**************************************************************************//**
	* @brief Permet de savoir si tous les capteurs sont detectes.
	*****************************************************************************/		
	bool isAllOnLine();
	
	/**************************************************************************//**
	* @brief Permet de savoir si tous les capteurs sont pas detectes.
	*****************************************************************************/		
	bool isOnlyLeftOff();
	
	/**************************************************************************//**
	* @brief Permet de savoir si seulement le capteur central est eteint.
	*****************************************************************************/		
	bool isOnlyRightOff();
	
	/**************************************************************************//**
	* @brief Permet de savoir si plus de deux capteurs sont allumes.
	*****************************************************************************/		
	bool isMoreThanOneOn();
	
	/**************************************************************************//**
	* @brief Permet de savoir si au moin un capteur est allume.
	*****************************************************************************/		
	bool isAtLeastOneOn();
	
	/**************************************************************************//**
	* @brief Permet de balayer, en tournant a gauche et a droite, pour detecter
	* 		 si le robot est toujours sur la ligne.
	*****************************************************************************/		
	bool lookForCenterLineAfterIntersection( const Direction& direction );

	/**************************************************************************//**
	* @brief Permet de de choisir quelle intersection qui sera a gerer.
	******************************************************************************/	
	void handleIntersection();
	
	void handleTLeftAndLRight();
	void handleTRightAndLLeft();
	void handleTBaseAndCross();
	
	void keepGoingAlittleBit();
// 	void followLineWithLittleZ();
};

#endif //_LINE_FOLLOWER_H