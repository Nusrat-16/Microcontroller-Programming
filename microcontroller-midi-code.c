/*
ATmega8, 48, 88, 168, 328

/Reset PC6|1   28|PC5
       PD0|2   27|PC4
       PD1|3   26|PC3
       PD2|4   25|PC2
       PD3|5   24|PC1
       PD4|6   23|PC0
       Vcc|7   22|Gnd
       Gnd|8   21|Aref
       PB6|9   20|AVcc
       PB7|10  19|PB5 SCK
       PD5|11  18|PB4 MISO
       PD6|12  17|PB3 MOSI
       PD7|13  16|PB2
LED    PB0|14  15|PB1
*/



#define  F_CPU 1000000UL // defines the clock frequency as 1 MHz (unsigned long)
#include <avr/io.h>      // defines all macros and symbols
#include <util/delay.h>  
#include <avr/interrupt.h> // interrupt library
//uart.h for midi communication
#include "uart.h"
//lcd.h for lcd screen
#include "lcd.h"
//timer and initial timer variables for delay_until function
double *timer, *initial_timer; //create the timer
double *exit_loop;
//set note positions variables
//for scale 0
unsigned char C0  =  0 +  (12 * 0);
unsigned char Db0 =  1 +  (12 * 0);
unsigned char D0  =  2 +  (12 * 0);
unsigned char Eb0 =  3 +  (12 * 0);
unsigned char E0  =  4 +  (12 * 0);
unsigned char F0  =  5 +  (12 * 0);
unsigned char Gb0 =  6 +  (12 * 0);
unsigned char G0  =  7 +  (12 * 0);
unsigned char Ab0 =  8 +  (12 * 0);
unsigned char A0  =  9 +  (12 * 0);
unsigned char Bb0 =  10 + (12 * 0);
unsigned char B0  =  11 + (12 * 0);

//for scale 1
unsigned char C1  =  0 +  (12 * 1);
unsigned char Db1 = 1 +   (12 * 1);
unsigned char D1  =  2 +  (12 * 1);
unsigned char Eb1 = 3 +   (12 * 1);
unsigned char E1  =  4 +  (12 * 1);
unsigned char F1  =  5 +  (12 * 1);
unsigned char Gb1 = 6 +   (12 * 1);
unsigned char G1  =  7 +  (12 * 1);
unsigned char Ab1 = 8 +   (12 * 1);
unsigned char A1  =  9 +  (12 * 1);
unsigned char Bb1 = 10 +  (12 * 1);
unsigned char B1  =  11 + (12 * 1);

//for scale 2
unsigned char C2  =  0 +  (12 * 2);
unsigned char Db2 =  1 +  (12 * 2);
unsigned char D2  =  2 +  (12 * 2);
unsigned char Eb2 =  3 +  (12 * 2);
unsigned char E2  =  4 +  (12 * 2);
unsigned char F2  =  5 +  (12 * 2);
unsigned char Gb2 =  6 +  (12 * 2);
unsigned char G2  =  7 +  (12 * 2);
unsigned char Ab2 =  8 +  (12 * 2);
unsigned char A2  =  9 +  (12 * 2);
unsigned char Bb2 =  10 + (12 * 2);
unsigned char B2  =  11 + (12 * 2);

//for scale 3
unsigned char C3  =  0 +  (12 * 3);
unsigned char Db3 =  1 +  (12 * 3);
unsigned char D3  =  2 +  (12 * 3);
unsigned char Eb3 =  3 +  (12 * 3);
unsigned char E3  =  4 +  (12 * 3);
unsigned char F3  =  5 +  (12 * 3);
unsigned char Gb3 =  6 +  (12 * 3);
unsigned char G3  =  7 +  (12 * 3);
unsigned char Ab3 =  8 +  (12 * 3);
unsigned char A3  =  9 +  (12 * 3);
unsigned char Bb3 =  10 + (12 * 3);
unsigned char B3  =  11 + (12 * 3);

//for scale 4
unsigned char C4  =  0 +  (12 * 4);
unsigned char Db4 =  1 +  (12 * 4);
unsigned char D4  =  2 +  (12 * 4);
unsigned char Eb4 =  3 +  (12 * 4);
unsigned char E4  =  4 +  (12 * 4);
unsigned char F4  =  5 +  (12 * 4);
unsigned char Gb4 =  6 +  (12 * 4);
unsigned char G4  =  7 +  (12 * 4);
unsigned char Ab4 =  8 +  (12 * 4);
unsigned char A4  =  9 +  (12 * 4);
unsigned char Bb4 =  10 + (12 * 4);
unsigned char B4  =  11 + (12 * 4);

//for scale 5
unsigned char C5  =  0 +  (12 * 5);
unsigned char Db5 =  1 +  (12 * 5);
unsigned char D5  =  2 +  (12 * 5);
unsigned char Eb5 =  3 +  (12 * 5);
unsigned char E5  =  4 +  (12 * 5);
unsigned char F5  =  5 +  (12 * 5);
unsigned char Gb5 =  6 +  (12 * 5);
unsigned char G5  =  7 +  (12 * 5);
unsigned char Ab5 =  8 +  (12 * 5);
unsigned char A5  =  9 +  (12 * 5);
unsigned char Bb5 =  10 + (12 * 5);
unsigned char B5  =  11 + (12 * 5);

//for scale 6
unsigned char C6  =  0 +  (12 * 6);
unsigned char Db6 =  1 +  (12 * 6);
unsigned char D6  =  2 +  (12 * 6);
unsigned char Eb6 =  3 +  (12 * 6);
unsigned char E6  =  4 +  (12 * 6);
unsigned char F6  =  5 +  (12 * 6);
unsigned char Gb6 =  6 +  (12 * 6);
unsigned char G6  =  7 +  (12 * 6);
unsigned char Ab6 =  8 +  (12 * 6);
unsigned char A6  =  9 +  (12 * 6);
unsigned char Bb6 =  10 + (12 * 6);
unsigned char B6  =  11 + (12 * 6);

//for scale 7
unsigned char C7  =  0 +  (12 * 7);
unsigned char Db7 =  1 +  (12 * 7);
unsigned char D7  =  2 +  (12 * 7);
unsigned char Eb7 =  3 +  (12 * 7);
unsigned char E7  =  4 +  (12 * 7);
unsigned char F7  =  5 +  (12 * 7);
unsigned char Gb7 =  6 +  (12 * 7);
unsigned char G7  =  7 +  (12 * 7);
unsigned char Ab7 =  8 +  (12 * 7);
unsigned char A7  =  9 +  (12 * 7);
unsigned char Bb7 =  10 + (12 * 7);
unsigned char B7  =  11 + (12 * 7);

//for scale 8
unsigned char C8  =  0 +  (12 * 8);
unsigned char Db8 =  1 +  (12 * 8);
unsigned char D8  =  2 +  (12 * 8);
unsigned char Eb8 =  3 +  (12 * 8);
unsigned char E8  =  4 +  (12 * 8);
unsigned char F8  =  5 +  (12 * 8);
unsigned char Gb8 =  6 +  (12 * 8);
unsigned char G8  =  7 +  (12 * 8);
unsigned char Ab8 =  8 +  (12 * 8);
unsigned char A8  =  9 +  (12 * 8);
unsigned char Bb8 =  10 + (12 * 8);
unsigned char B8  =  11 + (12 * 8);

//for scale 9
unsigned char C9  =  0 +  (12 * 9);
unsigned char Db9 =  1 +  (12 * 9);
unsigned char D9  =  2 +  (12 * 9);
unsigned char Eb9 =  3 +  (12 * 9);
unsigned char E9  =  4 +  (12 * 9);
unsigned char F9  =  5 +  (12 * 9);
unsigned char Gb9 =  6 +  (12 * 9);
unsigned char G9  =  7 +  (12 * 9);
unsigned char Ab9 =  8 +  (12 * 9);
unsigned char A9  =  9 +  (12 * 9);
unsigned char Bb9 =  10 + (12 * 9);
unsigned char B9  =  11 + (12 * 9);

//for scale 10
unsigned char C10 =  0 +  (12 * 10);


//baudrate 31250 for midi communication
#define BAUDRATE 31250


//Interrupt function for using the delay_until function
//WE NEED TO USE COMPA_vect
ISR( TIMER0_COMPA_vect )
{
	//every 10ms, increase the timer by 10
	*timer += 10;
	
}


void init(void);
void delay_until(double delay_amount);
void init_timer(void);
void play_music(void);
void test_notes(void);
void play_note(unsigned char note_position, char volume, int time);
void play_2_notes(unsigned char note_position1, unsigned char note_position2, char volume, int time);
void play_3_notes(unsigned char note_position1, unsigned char note_position2, unsigned char note_position3, char volume, int time);
void play_4_notes(unsigned char note_position1, unsigned char note_position2, unsigned char note_position3, unsigned char note_position4, char volume, int time);
void play_5_notes(unsigned char note_position1, unsigned char note_position2, unsigned char note_position3, unsigned char note_position4, unsigned char note_position5, char volume, int time);
//declaration and implementation of delay_until function
//We need to declare the timer as a pointer so we could use it globally
void delay_until(double delay_amount)
{
	//declare and initialize new input that it needs to be checked with the current time
	double input = delay_amount + *initial_timer;
	//while timer is less than input
	while(*timer < input)
	{
		//delay for 1 ms
		_delay_ms(1);
	}
	//set initial_timer to delay_amount
	*initial_timer = delay_amount;
}

//Basic initialization function
void init(void)
{
	*exit_loop = 1;
	PORTB = 0b00000010; // pull-up resistor active PB1
	//initialize uart communication, pin
	//uart_putc(unsigned char data) to send one data!
	uart_init ( UART_BAUD_SELECT (BAUDRATE , F_CPU ));
	//initialize lcd screen
	lcd_init( LCD_DISP_ON );
	lcd_clrscr();
}

//initialize timer
void init_timer(void)
{
	
	*timer = 0;
	*initial_timer = 0;
	//8 bit timer
	//CTC Mode
	TCCR0A = (0 << COM0A1) | (0 << COM0A0) | (0 << COM0B1) | (0 << COM0B0)
	//WGM00: 0, WGM01: 1, WGM02: 0 for activating CTC (OCRA)
	| (1 << WGM01)  | (0 << WGM00);
	TCCR0B = (0 << WGM02)
	| (1 << CS02)   | (0 << CS01)   | (1 << CS00);
	TIMSK0 = (0 << OCIE0B) | (0 << OCIE0A) | (1 << TOIE0);
	// allow interrupts globally
	OCR0A = 10; //with 255 counter, it is about 4 interrupts per second, with 10, it is about 10 ms per interrupt
	TIMSK0 = (1 << OCIE0A);
	//Set global interrupt flag
	sei();
}

void play_note(unsigned char note_position, char volume, int time)
{
	//Note on command
	uart_putc(0x90);uart_putc(note_position);uart_putc(volume);
	//Delay until command
	delay_until(time);
	//Note off command
	uart_putc(0x80);uart_putc(note_position);uart_putc(volume);	
}

void play_2_notes(unsigned char note_position1, unsigned char note_position2, char volume, int time)
{
	//Note on command
	uart_putc(0x90);uart_putc(note_position1);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position2);uart_putc(volume);
	//Delay until command
	delay_until(time);
	//Note off command
	uart_putc(0x80);uart_putc(note_position1);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position2);uart_putc(volume);
}

void play_3_notes(unsigned char note_position1, unsigned char note_position2, unsigned char note_position3, char volume, int time)
{
	//Note on command
	uart_putc(0x90);uart_putc(note_position1);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position2);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position3);uart_putc(volume);
	//Delay until command
	delay_until(time);
	//Note off command
	uart_putc(0x80);uart_putc(note_position1);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position2);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position3);uart_putc(volume);
}

void play_4_notes(unsigned char note_position1, unsigned char note_position2, unsigned char note_position3, unsigned char note_position4,
char volume, int time)
{
	//Note on command
	uart_putc(0x90);uart_putc(note_position1);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position2);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position3);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position4);uart_putc(volume);
	//Delay until command
	delay_until(time);
	//Note off command
	uart_putc(0x80);uart_putc(note_position1);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position2);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position3);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position4);uart_putc(volume);
}

void play_5_notes(unsigned char note_position1, unsigned char note_position2, unsigned char note_position3, unsigned char note_position4,
unsigned char note_position5, char volume, int time)
{
	//Note on command
	uart_putc(0x90);uart_putc(note_position1);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position2);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position3);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position4);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position5);uart_putc(volume);
	//Delay until command
	delay_until(time);
	//Note off command
	uart_putc(0x80);uart_putc(note_position1);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position2);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position3);uart_putc(volume);
	uart_putc(0x80);uart_putc(note_position4);uart_putc(volume);
	uart_putc(0x90);uart_putc(note_position5);uart_putc(volume);
}

void test_notes(void)
{
	
	play_note(60, 127, 1000);
	delay_until(1000);
}

int main (void)
{ 
  init();
  while (1)            // infinite main loop
  {
	lcd_clrscr();
	lcd_gotoxy (0 ,1);
	lcd_puts( "Press button 1!\n" );  
	if(! (PINB & 0b00000010) )
	{
		lcd_gotoxy (0 ,1);
		lcd_puts( "Button 1 pressed!\n" );
		while(*exit_loop)
		{
			init_timer();
			//Insert music CODE here
			//Function list: 
			//play_note(note_position, volume, duration ms)
			//play_2_notes(note_position1, note_position2, volume, duration ms)
			//play_3_notes(note_position1, note_position2, note_position3, volume, duration ms)			
			//play_4_notes(note_position1, note_position2, note_position3, note_position4, volume, duration ms)
			//play_5_notes(note_position1, note_position2, note_position3, note_position4, note_position5, volume, duration ms)
			//delay_until(ms) 


			*exit_loop = 0;
		}
		
		*exit_loop = 1
		delay_until(1000);
		//If button 2 pressed, all Notes off
		//run the loop 3 times
		for(int j = 0; j < 3; j++)
		{
			for(int i = 0; i < 128; i++)
			{
				//Note off command
				uart_putc(0x80);
				//Note position
				uart_putc(i);
				//Note velocity
				uart_putc(127);
			}	
		}
			
	}
  }
}