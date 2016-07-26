#include "LCD.h"

uint16_t writeVx( LCM* lcd, char* tmp, const uint8_t& value_number )
{
	/// @todo Mettre tous dans un seul tableau avant d'appeler write.
	uint16_t val_pos = value_number * 8;
	lcd->write("V", val_pos );
	itoa( value_number, tmp, 10);
	lcd->write( tmp, val_pos + 1 );
	lcd->write(":", val_pos + 2 );
	
	return val_pos;
}

void writeValue( LCM* lcd, 
				  const int& value, 
				  const uint8_t& value_number )
{
	char v[16];
	
	// Ecrire "Vx:" au bon endroit.
	// Potentiellement trop d'overhead pour ecrire "Vx:".
	uint16_t val_pos = writeVx( lcd, v, value_number );

	// Ecrire value au bon endroit.
	itoa( value, v, 10);
	lcd->write( v , val_pos + 3 );
}

void writeValue( LCM* lcd, 
				  const char* txt, 
				  const uint8_t& value_number )
{
	char v[16];
	uint16_t val_pos = writeVx( lcd, v, value_number );
	
	// Ecrire valeur au bon endroit.
	lcd->write( txt , val_pos + 3 );
}

void writeValue( LCM* lcd, 
				  const float& value,
				  const uint8_t& value_number )
{
	char v[16];
	uint16_t val_pos = writeVx( lcd, v, value_number );
	
	int vTest = value;
		
	itoa( vTest, v, 10);
	lcd->write( v, val_pos + 3);
	
	uint16_t len = cp_strlen( v );
	double f_value = value - vTest;
	f_value *= 10.0;
	vTest = f_value;
		
	itoa( vTest, v, 10);
	lcd->write( ".", len + val_pos + 3);
	lcd->write( v, len + val_pos + 4);
}
  
	  
	  
	  
	  
	  
	  
	 

























