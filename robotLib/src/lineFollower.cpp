#include "lineFollower.h"

const uint8_t LineFollower::c_moteur_speed = 160;
const uint8_t LineFollower::c_slope_speed = 100;

LineFollower::LineFollower( void (*func)( LineFollower* follower, 
										   const Intersection& type ) ): 
			  // Members
			  m_last_straight_line_direction( direction_left )
{
	m_fct_ptr = func;
	
	PORTA &= ~( (1 << capteur_gauche) | 
	            (1 << capteur_centre) | 
	            (1 << capteur_droit)  );
	
	activerMoteurs();
}


bool LineFollower::isCenter() 
{ return ( !( PINA & _BV(PINA3) ) ); }	

bool LineFollower::isLeft() 
{ return ( !( PINA & _BV(PINA1) ) );	}		

bool LineFollower::isRight() 
{ return ( !( PINA & _BV(PINA5) ) ); }

bool LineFollower::isOnlyCenterOn() 
{ return ( !isLeft() && isCenter() && !isRight() ); }

bool LineFollower::isOnlyLeftOn() 
{ return ( isLeft() && !isCenter() && !isRight() ); }

bool LineFollower::isOnlyRightOn() 
{ return ( !isLeft() && !isCenter() && isRight() ); }

bool LineFollower::isNotOnLine() 
{ return ( !isLeft() && !isCenter() && !isRight() ); }

bool LineFollower::isAllOnLine() 
{ return ( isLeft() && isCenter() && isRight() ); }

bool LineFollower::isOnlyLeftOff() 
{ return ( !isLeft() && isCenter() && isRight() ); }

bool LineFollower::isOnlyRightOff() 
{ return ( isLeft() && isCenter() && !isRight() ); }

bool LineFollower::isMoreThanOneOn()
{
	return ( isOnlyLeftOff() || isOnlyRightOff() );
}

bool LineFollower::isAtLeastOneOn()
{
	return ( isCenter() || isRight() || isLeft() );
}

void LineFollower::followLine()
{
	// Seulement le sensor centrale est allume.
	if( isOnlyCenterOn() )
	{
		if( m_last_straight_line_direction == direction_left )
		{
			avancer( c_moteur_speed - 20, c_moteur_speed );
		}
		else // Right.
		{
			avancer( c_moteur_speed, c_moteur_speed - 20 );
		}
	}
	
	// Seulement le sensor de gauche est allume.
	else if( isOnlyLeftOn() )
	{	
		// Verifier l'anti rebon pour les 3 lumieres.
		bool all_on = false;
		uint8_t tmp = 50;
		
		while( tmp-- )
		{
			if( isAllOnLine() )
			{
				handleTBaseAndCross();
				all_on = true;
				break;
			}
			_delay_ms( 1 );
		}
		
		if( !all_on )
		{
			reculerRobot( 180, 180 - 30 );
			_delay_ms( 300 );
				
			while( !isCenter() ) 
			{
				avancer( 0, c_moteur_speed );
			}
				
			// Tenter de le garder droit apres avoir redresser.
			avancer( c_moteur_speed, 20 );
			_delay_ms( 100 );
		}
	}
		
	// Seulement le sensor de droite est allume.
	else if( isOnlyRightOn() )
	{
		bool all_on = false;
		uint8_t tmp = 50;
		
		while( tmp-- )
		{
			if( isAllOnLine() )
			{
				handleTBaseAndCross();
				all_on = true;
				break;
			}
			_delay_ms( 1 );
		}
		
		if( !all_on )
		{
			reculerRobot( 254, 254 );
			_delay_ms( 300 );
				
			while( !isCenter() ) 
			{
				avancer( c_moteur_speed, 0 );
			}
				
			// Tenter de le garder droit apres avoir redresser.
			avancer( 20, c_moteur_speed );
			_delay_ms( 100 );
		}
	}
		
	else if( isNotOnLine() )
	{
		// Si la direction etait a gauche, il est maintenant temps 
		// d'aller vers la droite jusqu'a temps qu'on soit revenu au centre.
		if( m_last_straight_line_direction == direction_left )
		{	
			// Avancer vers la droite.
			while( !isCenter() )
			{
				avancer( c_moteur_speed, c_moteur_speed - 80 );
				
				if( isOnlyLeftOn() || isOnlyRightOn() )
				{
					stopRobotNow();
					break;
				}
			}
			
			m_last_straight_line_direction = direction_right;
		}
		else 
		{
			// Avancer vers la gauche.
			
			while( !isCenter() )
			{
				avancer( c_moteur_speed - 80, c_moteur_speed );
				
				if( isOnlyLeftOn() || isOnlyRightOn() )
				{
					stopRobotNow();
					break;
				}
			}
			
			m_last_straight_line_direction = direction_left;
		}
	}

	else
	{
		// Anti rebbon.
		_delay_ms( 5 );
		if( isMoreThanOneOn() )
		{
			//stopRobotNow();
			handleIntersection();
		}
	}
}


void LineFollower::handleIntersection()
{
	if( isAllOnLine() )
	{
		handleTBaseAndCross();
	}
	
	else if( isOnlyLeftOff() )
	{
		bool all_on = false;
		uint8_t tmp = 100;
		
		while( tmp-- )
		{
			if( isAllOnLine() )
			{
				handleTBaseAndCross();
				all_on = true;
				break;
			}
			_delay_ms( 1 );
		}
		
		if( !all_on )
		{
			handleTLeftAndLRight();
		}
	}
	else if( isOnlyRightOff() )
	{
		bool all_on = false;
		uint8_t tmp = 100;
		
		while( tmp-- )
		{
			if( isAllOnLine() )
			{
				handleTBaseAndCross();
				all_on = true;
				break;
			}
			_delay_ms( 1 );
		}
		
		if( !all_on )
		{
			handleTRightAndLLeft();
		}
	}
}

void LineFollower::handleTBaseAndCross()
{
	keepGoingAlittleBit();
	
	//_delay_ms( 1000 );
	if( !lookForCenterLineAfterIntersection( direction_continue ) )
	{
		//keepGoingAlittleBit();
		m_fct_ptr( this, inter_tBase );
	}
	else
	{
		//keepGoingAlittleBit();
		m_fct_ptr( this, inter_cross );
	}
}


void LineFollower::keepGoingAlittleBit()
{
	uint8_t tmp = 1500;
		
	// Avancer encore un petit pour voir si c'est un lLeft.
	while( tmp-- )
	{
		if( isOnlyCenterOn() )
		{
			if( m_last_straight_line_direction == direction_left )
			{
				avancer( c_moteur_speed, c_moteur_speed - 10 );
			}
			else // Right.
			{
				avancer( c_moteur_speed - 10, c_moteur_speed );
			}
		}
		else if( isNotOnLine() )
		{
			// Si la direction etait a gauche, il est maintenant temps 
			// d'aller vers la droite jusqu'a temps qu'on soit revenu au centre.
			if( m_last_straight_line_direction == direction_left )
			{				
				avancer( c_moteur_speed, c_moteur_speed - 40 );
				m_last_straight_line_direction = direction_right;
			}
			else 
			{
				m_last_straight_line_direction = direction_left;
				avancer( c_moteur_speed - 40, c_moteur_speed );
			}
		}
		
		_delay_ms( 1 );
	}
}

void LineFollower::handleTRightAndLLeft()
{
	keepGoingAlittleBit();
			
	// Si on est dans le cas du lRight.
	if( !lookForCenterLineAfterIntersection( direction_right ) )
	{
		turnLeft();
	}
	
	// tLeft.
	else
	{
		m_fct_ptr( this, inter_tRight );
	}
}

void LineFollower::handleTLeftAndLRight()
{
	keepGoingAlittleBit();
			
	// Si on est dans le cas du lLeft.
	if( !lookForCenterLineAfterIntersection( direction_left ) )
	{
		turnRight();
	}
	
	// tLeft.
	else
	{
		m_fct_ptr( this, inter_tLeft );
		
	}
}

bool LineFollower::lookForCenterLineAfterIntersection( const Direction& direction  )
{
	// Balayer un peu pour voir si on est sur un lLeft.
	if( direction_left )
	{
		uint8_t tmp = 400;
		while( tmp-- /*&& !centerWasOn*/ )
		{
			//avancer( c_moteur_speed, 0 );
			pivAntiHoraire( 160 );
			
			//if( isCenter() )  
			if( isAtLeastOneOn() )
			{
				//centerWasOn = true;
				return true;
			}
			_delay_ms( 1 );
			}

			stopRobotNow();
			_delay_ms( 100 );
	}
	else if( direction_right )
	{
		uint8_t tmp = 400;
		while( tmp--/* && !centerWasOn*/ )
		{
			//avancer( 0, c_moteur_speed );
			pivHoraire( 160 );
			//if( isCenter() ) 
			if( isAtLeastOneOn() )
			{
				return true;
			}
			_delay_ms( 1 );
		}
		
		stopRobotNow();
		_delay_ms( 100 );
	}
	else
	{
		while( isAllOnLine() )
		{
			avancer( c_moteur_speed, c_moteur_speed );
		}
		_delay_ms( 200 );
		
		stopRobotNow();
		_delay_ms( 50 );
		
		uint8_t tmp = 300;
		while( tmp--/* && !centerWasOn*/ )
		{
			//avancer( 0, c_moteur_speed );
			pivHoraire( 160 );
			//if( isCenter() ) 
			if( isAtLeastOneOn() )
			{
				return true;
			}
			_delay_ms( 1 );
		}
		
		tmp = 1000;
		while( tmp--/* && !centerWasOn*/ )
		{
			//avancer( 0, c_moteur_speed );
			pivHoraire( 160 );
			//if( isCenter() ) 
			if( isAtLeastOneOn() )
			{
				return true;
			}
			_delay_ms( 1 );
		}
				
		stopRobotNow();
		_delay_ms( 100 );
	}
	
	
	//return centerWasOn;
	return false;
}

void LineFollower::turnRight()
{
	// Avancer un petit peu encore et tourner.
// 	avancer( c_moteur_speed - 40, c_moteur_speed - 40 );
// 	_delay_ms( 100 );
	keepGoingAlittleBit();
	
	stopRobotNow();
	_delay_ms( 50 );
			
	while( !isRight() )
	{
		pivHoraire( c_moteur_speed - 20 );
	}
	
 	stopRobotNow();
 	_delay_ms( 20 );
	
	while( !isCenter() )
	{
		avancer( c_moteur_speed - 40, 0 );
	}
}

void LineFollower::turnLeft()
{
	// Avancer un petit peu encore et tourner.
	//avancer( c_moteur_speed - 40, c_moteur_speed - 40 );
	//_delay_ms( 100 );
	keepGoingAlittleBit();
	
	stopRobotNow();
	_delay_ms( 50 );
			
	while( !isLeft() )
	{
		pivAntiHoraire( c_moteur_speed - 20 );
	}
	
 	stopRobotNow();
 	_delay_ms( 20 );
	
	while( !isCenter() )
	{
		avancer( 0, c_moteur_speed - 40 );
	}
}

