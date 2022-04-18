/*
 * lesson_2.c
 *
 * Created: 07.04.2022 19:05:53
 * Author : Mishail
 */ 

# define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BLINK 500

int main(void)
{
    DDRD = 0b10000001;
    

    while (1) 
    {
        PORTD = 0b10000000;
        _delay_ms(BLINK);
        PORTD = 0b00000001;
        _delay_ms(BLINK);
    }
}



