/*
 * lesson_6_bitoper.c
 *
 * Created: 09.04.2022 15:07:31
 * Author : Mishail
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD = 0b11111111;
    //PORTD = 0b11100000;

    // & - and
    // | - or
    // ^ - nor

    while (1) 
    {
//         PORTD |= (1<<3);
//         _delay_ms(300);
//         PORTD &= ~(1<<3);
//         _delay_ms(300);
        
        PORTD ^= (1<<3);
        _delay_ms(300);
    }
}

