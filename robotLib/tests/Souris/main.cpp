// FICHIER POUR TESTER LE FONCTIONNEMENT DE LA SOURIS.

#include "robotLib.h"

bool light_left = false;
bool light_right = false;

bool tournerSiPhotoresistance( LineFollower* follower )
{
	bool aTourne = false;
	
	if( light_left ) 
	{
		//tournerAtIntersection( VITESSEBALAYAGE, direction_left );
		follower->turnLeft();
		aTourne = true;
		eteindreDel( &DDRD, &PORTD, 0 );
	}
	else if( light_right ) 
	{
		//tournerAtIntersection( VITESSEBALAYAGE, direction_right );
		follower->turnRight();
		aTourne = true;
		eteindreDel( &DDRD, &PORTD, 0 );
	}
	
	light_left = false;
	light_right = false;
	
	return aTourne;
}

void fonctionSouris( LineFollower* follower, const Intersection& type )
{
	Direction direction = prendreValeurAleatoire();
	
	switch( type )
	{
		case inter_cross: 
			if( !tournerSiPhotoresistance( follower ) )
			{
				//tournerAtIntersection( VITESSEBALAYAGE, direction );
				switch( direction )
				{
					case direction_left:
						follower->turnLeft();
						break;
						
					case direction_right:
						follower->turnRight();
						break;
				}
			}
			break;
			
		case inter_tBase: 
			if( !tournerSiPhotoresistance( follower ) )
			{
				if( direction == direction_continue ) 
					direction = direction_right;
				
// 				tournerAtIntersection( VITESSEBALAYAGE, direction );
				switch( direction )
				{
					case direction_left:
						follower->turnLeft();
						break;
						
					case direction_right:
						follower->turnRight();
						break;
				}
			}
			break;
				
		case inter_tLeft: 
			if( light_right )
			{
				//tournerAtIntersection( VITESSEBALAYAGE, direction_right );
				follower->turnRight();
				light_right = false;
				
			}
			else
			{
				if( direction == direction_left ) 
					direction = direction_right;
				
				//tournerAtIntersection( VITESSEBALAYAGE, direction );
				switch( direction )
				{
					case direction_left:
						follower->turnLeft();
						break;
						
					case direction_right:
						follower->turnRight();
						break;
				}
			}
			break;
				
		case inter_tRight:	
			if( light_left )
			{
				//tournerAtIntersection( VITESSEBALAYAGE, direction_left );
				follower->turnLeft();
				light_left = false;
				//eteindreDel( &DDRD, &PORTD, 0 );
			}
			else
			{
				if( direction == direction_right ) 
					direction = direction_left;
				
				//tournerAtIntersection( VITESSEBALAYAGE, direction );
				switch( direction )
				{
					case direction_left:
						follower->turnLeft();
						break;
						
					case direction_right:
						follower->turnRight();
						break;
				}
			}
			break;
	}
}

int main()
{
	//initTimerAleatoire();
	LineFollower follower( &fonctionSouris );
	
		
	while( 1 )
	{
		if( isIllumineGauche() ) 
		{
			light_left = true;
			garderAllumerDel( &DDRD, &PORTD, 0, DEL_VERT );
		}
		if( isIllumineDroite() ) 
		{
			light_right = true;
			garderAllumerDel( &DDRD, &PORTD, 0, DEL_ROUGE );
		}
		
		follower.followLine();
		//robotAvanceEtAppelFonctionAuIntersection( &fonctionSouris );
	}
	
	return 0;
}
