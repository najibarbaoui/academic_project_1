#ifndef _SUIVEURDELIGNE_H
#define _SUIVEURDELIGNE_H


#include <avr/io.h>
#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdbool.h>


enum intersection  {noIntersection, cross, tBase , tLeft , tRight , lLeft , lRight};
enum capteur {aucun, droit , centre , gauche };
enum direction {directionDroite, directionGauche , noDirection};
void initialiserSuiveurDeLigne();
bool isCenter();
bool isLeft();
bool isRight();
bool isIntersectionTBase();
bool isIntersectionTRight();
bool isIntersectionTLeft();
bool isIntersectionLLeft();
bool isIntersectionLRight();
bool isIntersectionC();
enum intersection detecteTypeIntersection();
void suivreTrajet();
bool balayerZone(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche , uint16_t rayonDeBalayage );
void enregistrerDernierCapteurActif(volatile enum capteur &m_capteur, volatile enum capteur &m_capteurCote);

#endif
