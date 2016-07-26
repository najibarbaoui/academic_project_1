#ifndef _SUIVEURDELIGNE_H
#define _SUIVEURDELIGNE_H

#include "robotUtils.h"
#include "moteur.h"
#include "del.h"

 /**************************************************************************//**
 * @brief La fonction initialise le PORT utilise pour lire les donnees 
 *        provenants du capteur.
 *****************************************************************************/
void initialiserSuiveurDeLigne();


 /**************************************************************************//**
 * @brief La fonction verifie si le capteur du centre est sur la ligne noire.
 *****************************************************************************/
bool isCenter();


 /**************************************************************************//**
 * @brief La fonction verifie si le capteur de gauche est sur la ligne noire.
 *****************************************************************************/
bool isLeft();


 /**************************************************************************//**
 * @brief La fonction verifie si le capteur de droite est sur la ligne noire.
 *****************************************************************************/
bool isRight();


 /**************************************************************************//**
 * @brief Equivalent a utiliser isLeft, isRight et isCenter mais prend la
 * 		  valeur de Capteur en parametre. Il n'est pas possible d'utiliser
 * 		  la valeur de Capteur::capteur_aucun en parametre.
 *****************************************************************************/
bool isCapteurValue( const Capteur& capteur_value ); 


 /**************************************************************************//**
 * @brief La fonction trouve le type d'intersection que le robot a atteint. 
 * @return Retourne inter_none si on est simplement sur le trajet.
 *****************************************************************************/
Intersection detecteTypeIntersection();


 /**************************************************************************//**
 * @brief La fonction permet au robot de suivre la ligne.
 *****************************************************************************/
void suivreTrajet();


/**************************************************************************//**
* @brief 
*****************************************************************************/
bool balayer(uint8_t vitesse , uint16_t tempsBalayage, Direction dir);

bool balayerZone( uint8_t vitesseMoteurDroit, 
				  uint8_t vitesseMoteurGauche, 
				  uint16_t rayonDeBalayage );


 /**************************************************************************//**
 * @brief Enregistre la valeur du dernier capteur. 
 * @Details Fonction qui permet d'enregistrer le dernier capteur actif dans 
 *          l'objet passé par référence. Si on a plus d'un capteur actif, 
 * 			la variable ne sera pas modifié sauf s'il désigne un capteur 
 * 			inactif. Dans ce case, la variable sera mis à "centre".
 * @return none
 *****************************************************************************/
void enregistrerDernierCapteurActif( Capteur& m_capteur, 
									  Capteur& m_capteurCote );


void tournerAtIntersection(uint8_t vitesse, Direction dir);


void trouverTypeIntersectionPourUnCote( Intersection& type, 
										 const Capteur& side, 
										 const Capteur& opposite_side );

/**************************************************************************//**
* @brief Lorsqu'on franchit une ligne, permet de savoir si une ligne existe
* 		 aussi du côté opposé de side.
* @return Retourne true s'il y avait une ligne, sinon false.
*****************************************************************************/
bool continuerTantQueCapteurCoteDetecter( const Capteur& side, 
										   const Capteur& opposite_side );

void ajusterCoteMoteur( const Capteur& side );

void tournerAtNextIntersection(uint8_t vitesse, Direction dir);

void robotAvanceEtAppelFonctionAuIntersection( void (*func)( const Intersection& type ) );

#endif
