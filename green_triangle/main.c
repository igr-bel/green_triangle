/*
 * green_triangle.c
 *
 * Created: 25.06.2017 23:52:30
 * Author : igr
 */ 
//====================================================================================================

#include <avr/io.h>
#include <util/delay.h>

//---------------------------------------------------------------------------------------------------
//#define F_CPU 8000000

#define red	0
#define green	1

#define btn_1_pressed	1
#define btn_2_pressed	1
#define btn_3_pressed	1

#define  magnet_on	1
#define  magnet_off	0

//---------------------------------------------------------------------------------------------------
//---prototypes
void shake_it(unsigned char button_number);
inline void display_it(void);
inline void win(void);
//---------------------------------------------------------------------------------------------------
unsigned char display_array[12];
unsigned char *win_array[6] = { &display_array[2], &display_array[3], &display_array[4],
								&display_array[6], &display_array[7], &display_array[10]};

unsigned char *btn_1_array[6] = { &display_array[0], &display_array[1], &display_array[4],
								  &display_array[7], &display_array[6], &display_array[2]};
		
unsigned char *btn_2_array[6] = { &display_array[3], &display_array[4], &display_array[8],
								  &display_array[11], &display_array[10], &display_array[6]};

unsigned char *btn_3_array[6] = { &display_array[2], &display_array[3], &display_array[7],
								  &display_array[10], &display_array[9], &display_array[5]};



//====================================================================================================
int main(void)
{
    //LED's pins
	DDRB = 0xFF;
	DDRD |= ( (1<<3) | (1<<4) | (1<<5) | (1<<6) ); 
	
	unsigned char error_flag = 0;
	
	//start inits
	magnet_on;
	
    while (1) 
    {
		if (btn_1_pressed)
		{
			_delay_ms(100);
			if (btn_1_pressed)
			{
				shake_it(1);
			}//if(for debounce)
			while (btn_1_pressed);
		}//if(btn_1)
		
		if (btn_2_pressed)
		{
			_delay_ms(100);
			if (btn_2_pressed)
			{
				shake_it(2);
			}//if(for debounce)
			while (btn_2_pressed);
		}//if(btn_2)
				
		if (btn_3_pressed)
		{
			_delay_ms(100);
			if (btn_3_pressed)
			{
				shake_it(3);
			}//if(for debounce)
			while (btn_3_pressed);
		}//if(btn_3)
		
		display_it();
		
		for (unsigned char i=0; i<6; i++)
		{
			if ( red == *(win_array[i]) ) error_flag = 1;
			if ( (5 == i) && (!error_flag) ) win();
		}//for
		
		error_flag = 0;
		
    }//while
}//main()
//====================================================================================================
//---functions
void shake_it(unsigned char button_number)
{
	unsigned char buffer;
	
	switch (button_number)
	{
		case 1:
			buffer = *(btn_1_array[0]);
			for (unsigned char i=0; i<5 ; i++)
			{
				*(btn_1_array[i]) = *(btn_1_array[i+1]);
			}//for
			*(btn_1_array[5]) = buffer;
		break;

		case 2:
		buffer = *(btn_2_array[0]);
		for (unsigned char i=0; i<5 ; i++)
		{
			*(btn_2_array[i]) = *(btn_2_array[i+1]);
		}//for
		*(btn_2_array[5]) = buffer;
		break;

		case 3:
		buffer = *(btn_3_array[0]);
		for (unsigned char i=0; i<5 ; i++)
		{
			*(btn_3_array[i]) = *(btn_3_array[i+1]);
		}//for
		*(btn_3_array[5]) = buffer;
		break;
		
		default: break;
	}//switch
	
	
}//shake_it()
//---------------------------------------------------------------------------------------------------
inline void display_it(void)
{
	PORTB = ( (display_array[0]<<0) | (display_array[1]<<1) | (display_array[2]<<2) 
			| (display_array[3]<<3) | (display_array[4]<<4) | (display_array[5]<<5)
			| (display_array[6]<<6) | (display_array[7]<<7) );
			
	PORTD &= ( (1<<3) | (1<<4) | (1<<5) | (1<<6) );
	PORTD |= ( (display_array[8]<<3) | (display_array[9]<<4) | (display_array[10]<<5) 
			| (display_array[11]<<6) ); 
	
	return;
}//display_it()
//---------------------------------------------------------------------------------------------------
inline void win(void)
{
	//voice "door open"
	
	magnet_off;
	
	return;
}//win()
//---------------------------------------------------------------------------------------------------