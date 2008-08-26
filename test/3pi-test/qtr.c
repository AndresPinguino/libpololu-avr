#include <pololu/3pi.h>
#include "assert.h"

void display_values(unsigned int *values, unsigned int max)
{
	unsigned char i;

	unsigned char characters[] = {' ',0,1,2,3,4,5,255};

	lcd_goto_xy(0,1);
	for(i=0;i<5;i++)
	{
		// get characters[0] to characters[7]
		print_character(characters[values[i]*8/(max+1)]);
	}
}

void test_qtr()
{
	unsigned char i;
	unsigned int values[5];

	clear();

	// Wait for each sensor to be > 750 while the others are < 250.
	unsigned int passed_sensors[5] = {0,0,0,0,0};

	while(!button_is_pressed(ALL_BUTTONS))
	{
		read_line_sensors(values,IR_EMITTERS_ON);

		unsigned char i;
		unsigned char sensor_above=0;
		char num_above=0;
		char num_below=0;
		for(i=0;i<5;i++)
		{
			if(values[i] > 750)
			{
				sensor_above = i;
				num_above ++;
			}
			else if(values[i] < 500)
				num_below ++;
		}

		if(num_above == 1 && num_below == 4)
			passed_sensors[sensor_above] = 1;

		lcd_goto_xy(0,0);
		for(i=0;i<5;i++)
		{
			if(passed_sensors[i])
				print_character('*');
			else
				print_character(' ');
		}

		display_values(values,1000);
		delay_ms(50);
	}
 
	wait_for_button(ALL_BUTTONS);

	clear();

	// off values
	while(!button_is_pressed(ALL_BUTTONS))
	{
		read_line_sensors(values,IR_EMITTERS_OFF);

		lcd_goto_xy(0,0);
		print("IR- ");
		display_values(values,1000);
    
		delay_ms(50);
	}

	wait_for_button(ALL_BUTTONS);
}

// Local Variables: **
// mode: C **
// c-basic-offset: 4 **
// tab-width: 4 **
// indent-tabs-mode: t **
// end: **