#ifndef _CAPTEURDISTANCE_H
#define _CAPTEURDISTANCE_H

#include "robotUtils.h"

void initialiserPortCapDistance();

uint8_t getDistance0_255();
bool isFarThan22po();
bool isBetween22And12po();
bool isBetween12And10po();
bool isBetween10And8po();
bool isBetween8And7po();
bool isLessThan7po();

#endif
 
