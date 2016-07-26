#ifndef _DEL_H
#define _DEL_H

#ifndef _AVRLIBS_
#define _AVRLIBS_
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

void rougeClignotant(uint8_t port,uint8_t broche,uint16_t temps);
void vertClignotant(uint8_t port,uint8_t broche,uint16_t temps);
void eteindreDel(uint8_t port,uint8_t broche);
void allumeVert(uint8_t port,uint8_t broche,uint16_t temps);
void allumeRouge(uint8_t port,uint8_t broche,uint16_t temps);

void garderVertAllume(uint8_t port,uint8_t broche);
void garderRougeAllume(uint8_t port,uint8_t broche);

#endif
 
