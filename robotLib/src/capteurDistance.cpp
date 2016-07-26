#include "capteurDistance.h"

#include "can.h"


//tous les valeurs sont entre 90-120
//void test(uint8_t a,uint8_t e, uint8_t b, uint8_t c,uint8_t d){
//	can convertisseur;
//	uint16_t intensite = convertisseur.lecture(2) >> 2;
	
//	if(intensite<=a )  eteindreDel('B',0); plus que 22po
//	else if((intensite>a)&&(intensite<=e))  allumeVert('B',0,5);// de 22 - > 12po
//	else if((intensite>e)&&(intensite<=b))  allumeRouge('B',0,5);//a partir 12po -> 10po
//	else if((intensite>b)&&(intensite<=c))  vertClignotant('B',0,5);// 10po -> 8po
//	else if((intensite>c)&&(intensite<=d))  rougeClignotant('B',0,5);// 8po -> 7po					
//	else if (intensite>d) 	allumeRouge('B',0,5);// moins que 7po
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : initialiserPortCapDistance()                                                                                  //
//  Paramètres : aucun                                                                                                      //
//	Retour : aucun                                                                                                          //
//																														    //	
//  La fonction initialiser le PORT utilise pour lire les donnees provenants du capteur                                     //
//               																			                                // 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialiserPortCapDistance()
{
		DDRA &= ~( 1 << 0x02 );
		//PORTA &= ~(1 << 0x02);
			
}

uint8_t getDistance0_255()
{
	can convertisseur;
	return convertisseur.lecture(0) >> 2;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : bool isFarThan22po()                                                                                            //
//  Paramètres : void                                                                                                      //
//	Retour : booléen                                                                                                          //
//																//
//  La fonction retourne true lorsqu'on est loin de 22pousse                            // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isFarThan22po(){
	can convertisseur;
	uint16_t intensite = convertisseur.lecture(1) >> 2;
	if((intensite<=55))
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : bool isBetween22And12po()                                                                                            //
//  Paramètres : void                                                                                                      //
//	Retour : booléen                                                                                                          //
//																//
//  La fonction retourne true dans l'intervalle 12<x<=22 (pousse)                            // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isBetween22And12po(){
	can convertisseur;
	uint16_t intensite = convertisseur.lecture(1) >> 2;
	if((intensite>55)&&(intensite<=80))
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : bool isBetween12And10po()                                                                                            //
//  Paramètres : void                                                                                                      //
//	Retour : booléen                                                                                                          //
//																//
//  La fonction retourne true dans l'intervalle 10<x<=12 (pousse)                              // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isBetween12And10po(){
	can convertisseur;
	uint16_t intensite = convertisseur.lecture(1) >> 2;
	if((intensite>80)&&(intensite<=110))
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : bool isBetween10And8po()                                                                                            //
//  Paramètres : void                                                                                                      //
//	Retour : booléen                                                                                                          //
//																//
//  La fonction retourne true dans l'intervalle 8<x<=10 (pousse)                              // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isBetween10And8po(){
	can convertisseur;
	uint16_t intensite = convertisseur.lecture(1) >> 2;
	if((intensite>110)&&(intensite<=120))
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : bool isBetween8And7po()                                                                                            //
//  Paramètres : void                                                                                                      //
//	Retour : booléen                                                                                                          //
//																//
//  La fonction retourne true dans l'intervalle 7<x<=8 (pousse)                              // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isBetween8And7po(){
	can convertisseur;
	uint16_t intensite = convertisseur.lecture(1) >> 2;
	if((intensite>120)&&(intensite<=150))
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																															//
//  Fonction : isLessThan7po()                                                                                            //
//  Paramètres : void                                                                                                      //
//	Retour : booléen                                                                                                          //
//																//
//  La fonction retourne true lorsque l'obstacle est de moins de 7 pousse                             // 
//																
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isLessThan7po(){
	can convertisseur;
	uint16_t intensite = convertisseur.lecture(1) >> 2;
	if((intensite>150))
		return true;
	else
		return false;
}





//int main(){
//	DDRA= 0x00;	
//	for(;;)	{	
//	if (detecterPlus22po()){ eteindreDel('B',0);}
//	else if (detecter22Et12po()) { allumeVert('B',0,5);}
//	else if	(detecter12Et10po()) {allumeRouge('B',0,5);}
//	else if (detecter10Et8po()) {vertClignotant('B',0,5);}
//	else if (detecter8Et7po()) {rougeClignotant('B',0,5);}
//	else if (detecter7poEtMoins()) {allumeRouge('B',0,5);}
//	}
//	return 0;
//}
	
							 



