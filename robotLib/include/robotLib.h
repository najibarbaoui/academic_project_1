/**************************************************************************//**
 * @author Najib Arbaoui
 * @Date   11 Novembre 2013
 * 
 * @Details Ce fichier appelle tous les headers.
 *****************************************************************************/
#ifndef AVR_ROBOT_H
#define AVR_ROBOT_H

// Les paramètres du système, ex fréquence, sont réglés dans robotUtils.h.
// Ce fichier doit être appelé en premier.
#include "robotUtils.h"

#include "can.h"
#include "lcm_so1602dtr_m_fw.h"
#include "lcm_so1602dtr_m.h"
#include "memoire_24.h"

#include "capteurDistance.h"
#include "customprocs.h"
#include "del.h"
#include "LCD.h"
#include "midi.h"
#include "moteur.h"
#include "photoresistance.h"
#include "aleatoire.h"
#include "lineFollower.h"

#endif