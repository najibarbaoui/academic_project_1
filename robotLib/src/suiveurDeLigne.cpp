#include "suiveurDeLigne.h"

 // Sauvegarder le type d'intersection franchie.
Intersection lastIntersection = inter_none;

// Le dernier capteur qui a été activé
Capteur dernierCapteurActif = capteur_aucun;

// Le dernier capteur qui a été activé, mais ignore le capteur central.
Capteur dernierCapteurCoteActif = capteur_aucun; 

Intersection possibiliteIntersection1 = inter_none;
Intersection possibiliteIntersection2 = inter_none;

//////////////////////////////////////////////////////////////////////////////////////////
void initialiserSuiveurDeLigne()
{
	//ports A1, A3, A5 à 0 (entrée)
	DDRA &= ~( (1 << capteur_gauche) | 
	           (1 << capteur_centre) | 
	           (1 << capteur_droit)  );
}

//////////////////////////////////////////////////////////////////////////////////////////
bool isCenter() { return !(PINA & _BV(PINA3)); }


//////////////////////////////////////////////////////////////////////////////////////////
bool isLeft() { return !(PINA & _BV(PINA1)); }


//////////////////////////////////////////////////////////////////////////////////////////
bool isRight() { return !(PINA & _BV(PINA5)); }


//////////////////////////////////////////////////////////////////////////////////////////
bool isCapteurValue( const Capteur& capteur_value )
{
	return !(PINA & _BV( capteur_value ) );
}

//////////////////////////////////////////////////////////////////////////////////////////
bool continuerTantQueCapteurCoteDetecter( const Capteur& side, 
										   const Capteur& opposite_side )
{
	bool opp_side_detected = false;
	
	while( isCapteurValue( side ) ) 
	{
		if( isCapteurValue( opposite_side ) )
		{
			opp_side_detected = true;
		}
	}
	
	return opp_side_detected;
}

//////////////////////////////////////////////////////////////////////////////////////////
void trouverTypeIntersectionPourUnCote( Intersection& type,
										 const Capteur& side, 
										 const Capteur& opposite_side )
{	
	// Pour les commentaires, on présume qu'une ligne a été détectée à gauche,
	// mais la fonction est valide pour les deux directions.
	
	// Devra se mettre à vrai dès qu'on trouve une ligne à droite, 
	// puis maintenir son état.
	bool opp_side_detected = false; 
	    
	// La petite pente permet d'éviter que le robot perde la ligne 
	// centrale dans l'intersection.
	// Puisque le côté gauche a touché la ligne en premier, on fait dévier
	// le robot légèrement vers la droite.
	ajusterCoteMoteur( side );
		    
	// On continue à avancer tant que le capteur de gauche est sur une ligne.
	// Entre temps, on vérifie si on est en train de passer sur une ligne à droite.
	opp_side_detected = continuerTantQueCapteurCoteDetecter( side, opposite_side );
	//On a fini de franchir à gauche.
			    
	// Si on a traversé une ligne à droite, on continue aussi à avancer 
	// jusqu'à ce qu'on finisse de la franchir, pour être sûr qu'on est sorti
	// de la ligne tranvsersale.
	if( opp_side_detected ) 
	{
		while( isCapteurValue( opposite_side ) );
		//On a fini de franchir à droite et à gauche.
	}
	
	// On avance un peu plus pour s'assurer
	// que le capteur central n'est pas sur la ligne transversale
	// et pour qu'on ne touche pas à la ligne transversale si on balaie.
	{
		_delay_ms(50);
	}
	
	
	
	
	// Permet de savoir si on a retrouvé une ligne centrale 

	// après l'intersection. On est sorti de l'intersection.

	// après l'intersection.
	
	// On est sorti de l'intersection.

	// On balaie pour savoir s'il y a une ligne au centre.
	bool ligneFranchie = balayerZone(VITESSEBALAYAGE, VITESSEBALAYAGE, TEMPS_BALAYAGE_MS );
	
	
	// Ligne à droite et à gauche: cross ou tBase.
	if( opp_side_detected ) 
	{ 
		if( ligneFranchie )	 type = inter_cross;
		else type = inter_tBase;
	}
	
	// Ligne à gauche seulement: tRight ou lLeft
	else 
	{ 
		if( ligneFranchie ) 
		{
			if( side == capteur_gauche ) type = inter_tRight;
			else type = inter_tLeft;
		}
		else 
		{
			if( side == capteur_gauche ) type = inter_lLeft;
			else type = inter_lRight;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
Intersection detecteTypeIntersection()
{
    Intersection intersectionType = inter_none;
    
    if ( isCenter() && ( isLeft() || isRight() ))
    {
		// Permettra un meilleur redressement par la suit
		enregistrerDernierCapteurActif( dernierCapteurActif, 
										 dernierCapteurCoteActif );
	    
	    // Teste si une ligne est détectée à gauche
	    // cas possibles: cross, tBase, tRight, lLeft.
	    if( isLeft() )
	    {
			trouverTypeIntersectionPourUnCote( intersectionType, 
												capteur_gauche, 
												capteur_droit );
	    }
	    
	    // Teste si une ligne est détectée à droite
	    // cas possibles: cross, tBase, tLeft, lRight.
	    else if( isRight() )
	    {	
			trouverTypeIntersectionPourUnCote( intersectionType, 
												capteur_droit, 
												capteur_gauche );
		}
    }
    return intersectionType;
}

//////////////////////////////////////////////////////////////////////////////////////////
void ajusterCoteMoteur( const Capteur& side )
{
	if( side == capteur_gauche )
	{
		ajusterGauche( VITESSEINTERSECTIONDROITE, 
					   VITESSEINTERSECTIONGAUCHE, 
					   PETITE_PENTEPOURTOURNER );
	}
	
	else
	{
		ajusterDroite( VITESSEINTERSECTIONDROITE, 
					   VITESSEINTERSECTIONGAUCHE, 
					   PETITE_PENTEPOURTOURNER );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void enregistrerDernierCapteurActif( Capteur &m_capteur = dernierCapteurActif, 
									  Capteur &m_capteurCote = dernierCapteurCoteActif ) 
{
	if(isRight() && !isLeft() && !isCenter())
	{
		m_capteur = capteur_droit ;
		m_capteurCote = capteur_droit;
	}	

	else if(!isRight() && isLeft() && !isCenter())
	{
		m_capteur = capteur_gauche ;
		m_capteurCote = capteur_gauche;
	}

	else if(!isRight() && !isLeft() && isCenter())
	{
		//m_capteurCote ne change pas
		m_capteur = capteur_centre ;
	}
	
	else if (isRight() && !isLeft() && isCenter()) { //droite et centre: on ne peut pas avoir gauche
		if (m_capteur == capteur_gauche || m_capteur == capteur_aucun)
			m_capteur = capteur_centre;
		m_capteurCote = capteur_droit;
	}
	
	else if (!isRight() && isLeft() && isCenter()) { //gauche et centre: on ne peut pas avoir droite
		if (m_capteur == capteur_droit || m_capteur == capteur_aucun)
			m_capteur = capteur_centre;
		m_capteurCote = capteur_gauche;
	}
	
	else if (!isRight() && !isLeft() && !isCenter()) { //aucun changement à l'état si on est dans l'état perdu
		//m_capteur = m_capteur;
	}
	
	else if (isRight() && isLeft() && isCenter()){ //les trois sont allumés: on change seulement si "aucun"
		if (m_capteur == capteur_aucun)
			m_capteur = capteur_centre;
	}
	
	else { //les deux extrémités sont allumés, mais pas le centre -- cas très rare, possible lorsqu'on tourne
		// et que les capteurs sont trop proches de l'intersection
		
		//m_capteur = m_capteur
	}

}

//////////////////////////////////////////////////////////////////////////////////////////
void suivreTrajet()
{	
	enregistrerDernierCapteurActif(dernierCapteurActif, dernierCapteurCoteActif);
		
	if(isRight() && !isLeft() && !isCenter())
	{
			ajusterDroite(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE , PENTEPOURTOURNER );
	}	
			
	else if(!isRight() && isLeft() && !isCenter())
	{
			ajusterGauche(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE , PENTEPOURTOURNER );
	}
	
	else if(!isRight() && !isLeft() && isCenter())
	{
			avancerRobot(VITESSEMOTEURDROITE  , VITESSEMOTEURGAUCHE );
	}
	// Dans le cas ou le robot se trouve dans un etat perdu	
	
	else if(!isRight() && !isLeft() && !isCenter())
	{
		if(dernierCapteurActif == capteur_centre)
		{
			//Si on vient de la droite et qu'on vient de dépasser le centre, on compense en retournant vers la droite
			if (dernierCapteurCoteActif == capteur_droit)
				ajusterGauche(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE, MOYENNE_PENTEPOURTOURNER );
			//vice-versa
			else if (dernierCapteurCoteActif == capteur_gauche)
				ajusterDroite(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE, MOYENNE_PENTEPOURTOURNER );
				//si on connait pas le dernier côté, on continue tout droit
			else
				avancerRobot(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE );
			}

				if(dernierCapteurActif == capteur_centre)
				{
					
					
///@todo					Fonction d'ajustement précise à décommenter si tout va bien
// 					
// 					// Sert à ajuster la direction du robot avant même d'actionner les senseurs de côté
// 					// en se basant sur la direction d'où vient le robot.
// 					//
// 					// Si on vient de la droite et qu'on vient de dépasser le centre, on compense en retournant vers la droite
// 					if (dernierCapteurCoteActif == capteur_droit)
// 						ajusterGauche(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE, MOYENNE_PENTEPOURTOURNER );
// 					//vice-versa
// 					else if (dernierCapteurCoteActif == capteur_gauche)
// 						ajusterDroite(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE, MOYENNE_PENTEPOURTOURNER );
// 					//si on connait pas le dernier côté, on continue tout droit
// 					else
						avancerRobot(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE );
				}

				
			else if(dernierCapteurActif == capteur_droit)
			{
				ajusterDroite(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE, PENTEPOURTOURNER );
			}
				
			else if(dernierCapteurActif == capteur_gauche)
			{
				ajusterGauche(VITESSEMOTEURDROITE , VITESSEMOTEURGAUCHE, PENTEPOURTOURNER );
			}
			else //dernierCapteurActif == aucun
			{
				//pour détectage d'erreur ou bogue seulement. Ce cas ne devrait jamais se produire, sauf si on démarre le circuit sans voir la ligne
				reculerRobot(VITESSEMOTEURDROITE  , VITESSEMOTEURGAUCHE );	
			}
	}	
	enregistrerDernierCapteurActif(dernierCapteurActif, dernierCapteurCoteActif);
}

// fonction qui permet de balayer une zone pour trouver une ligne
//la fonction arrête dès qu'une ligne est détectée.

//////////////////////////////////////////////////////////////////////////////////////////
bool balayer(uint8_t vitesse , uint16_t tempsBalayage, Direction dir)
{
	bool ligneDetectee = (isLeft() || isCenter() || isRight()) ; 
	
	while (!ligneDetectee && tempsBalayage > 0)
	{
		if (dir == direction_left)
			pivoterAntiHoraire(vitesse);
		else
			pivoterHoraire(vitesse);
		_delay_ms(1);
		ligneDetectee =  (isLeft() || isCenter() || isRight()) ; 
		tempsBalayage -- ;
	}
	
	arreterRobot();
	enregistrerDernierCapteurActif(dernierCapteurActif, dernierCapteurCoteActif);
	return ligneDetectee ;
}


//////////////////////////////////////////////////////////////////////////////////////////
bool balayerZone(uint8_t vitesseMoteurDroit , uint8_t vitesseMoteurGauche , uint16_t rayonDeBalayage )
{
	
	bool ligneTrouvee = ( isLeft() || isRight() || isCenter() );
	
	if (!ligneTrouvee)
		ligneTrouvee = balayer(vitesseMoteurDroit , rayonDeBalayage/2, direction_left);
	
	if (!ligneTrouvee)
		ligneTrouvee = balayer(vitesseMoteurGauche , rayonDeBalayage, direction_right);
	
		/*
		if (!ligneTrouvee)
		{
			while(!isCenter() && !isLeft() && !isRight())
				reculerRobot(vitesseMoteurDroit , vitesseMoteurGauche); //ligneTrouvee demeure false
			arreterRobot();
		}
		*/
	
	enregistrerDernierCapteurActif(dernierCapteurActif, dernierCapteurCoteActif);
	return ligneTrouvee ;
	
}


//////////////////////////////////////////////////////////////////////////////////////////

void tournerAtIntersection(uint8_t vitesse, Direction dir)
{
	// on vérifie si on est présentement sur une ligne-trajet,
	// comme dans un cross, ou tTight ou tLeft
	
	switch (dir)
	{
		//on fait avancer le robot un peu pour que le pivot se fasse au bon endroit
		if (isLeft() || isRight() || isCenter())
		{
			for (uint8_t i = 0; i < 50; i++)
			{
				suivreTrajet();
				_delay_ms(1);
			}
		}
		else
		{
			avancerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
			_delay_ms(50);
		}
		
		
		
		case direction_left:
			// on vérifie si le capteur de gauche est déjà sur la ligne trajet.
			// Si oui, il faut tourner while il sort de la ligne, entre dans la zone blanche
			// puis arrête quand la ligne transversale est au milieu.
			// Sinon, on est déjà dans la zone blanche et on saute la première étape.
			while(!isLeft())
				avancerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
			tournerAGauche(vitesse);
			
			if (isLeft())
				while (isLeft());
			
			while (!isLeft());
			while(!isCenter());
			
			break;
			
		case direction_right:
			//même chose que direction_left, mais à l'inverse
			while(!isRight())
				avancerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
			tournerADroite(vitesse);
			
			if (isRight())
				while (isRight());
				
			while (!isRight());
			while (!isCenter());
			
			break;
			
		case direction_reculer:
			//on recule tant qu'on n'est pas sur une ligne
			reculerRobot(vitesse, vitesse);
			while (!isRight() || !isLeft() || !isCenter()) ;
			
		case direction_continue: //nobreak
		default:
			break;
	}
	
	//on arrête le robot dans tous les cas.
	//arreterRobot();
			
			
}


//////////////////////////////////////////////////////////////////////////////////////////

void tournerAtNextIntersection(uint8_t vitesse, Direction dir)
{
	// on vérifie si on est présentement sur une ligne-trajet,
	// comme dans un cross, ou tTight ou tLeft
	
	switch (dir)
	{
		//on fait avancer le robot un peu pour que le pivot se fasse au bon endroit
		if (isLeft() || isRight() || isCenter())
		{
			for (uint8_t i = 0; (i < 50) && (isLeft() || isRight() || isCenter()); i++)
			{
				suivreTrajet();
				_delay_ms(1);
			}
		}
		else
		{
			avancerRobot(VITESSEINTERSECTIONDROITE, VITESSEINTERSECTIONGAUCHE);
			_delay_ms(50);
		}
		
		
		
		case direction_left:
			// on vérifie si le capteur de gauche est déjà sur la ligne trajet.
			// Si oui, il faut tourner while il sort de la ligne, entre dans la zone blanche
			// puis arrête quand la ligne transversale est au milieu.
			// Sinon, on est déjà dans la zone blanche et on saute la première étape.
			
			tournerAGauche(vitesse);
			
			if (isLeft())
				while (isLeft());
			
			while (!isLeft());
			while(!isCenter());
			
			break;
			
		case direction_right:
			//même chose que direction_left, mais à l'inverse
			tournerADroite(vitesse);
			
			if (isRight())
				while (isRight());
				
			while (!isRight());
			while (!isCenter());
			
			break;
			
		case direction_reculer:
			//on recule tant qu'on n'est pas sur une ligne
			reculerRobot(vitesse, vitesse);
			while (!isRight() || !isLeft() || !isCenter()) ;
			
		case direction_continue: //nobreak
		default:
			break;
	}
	
	//on arrête le robot dans tous les cas.
	//arreterRobot();
			
			
}




void robotAvanceEtAppelFonctionAuIntersection( void (*func)( const Intersection& type ) )
{
	Intersection type = detecteTypeIntersection();
	switch( type )
	{
		case inter_none: suivreTrajet(); break;
		case inter_lLeft: tournerAtIntersection( VITESSEBALAYAGE, direction_left ); break;
		case inter_lRight:	tournerAtIntersection( VITESSEBALAYAGE, direction_right ); break;
				
		default: func( type );
	}
}