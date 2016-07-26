#include "robotLib.h"

// FICHIER DE TESTS POUR LINEFOLLOWER.

bool ggggg = true;

void fonctionDeplacement( LineFollower* follower, 
						   const Intersection& type )
{
	switch( type )
	{
		case inter_tBase:
			//clignoterDel( &DDRD, &PORTD, 0, 5, DEL_ROUGE );
			follower->turnRight();
		break;

		case inter_cross:
			//clignoterDel( &DDRD, &PORTD, 0, 5, DEL_VERT );
		break;
	}
}

int main()
{
	clignoterDel( &DDRD, &PORTD, 0, 5, DEL_ROUGE );
	LineFollower follower( &fonctionDeplacement );
	
	
	while( 1 )
	{
		follower.followLine();
	}
	
	return 0;
}