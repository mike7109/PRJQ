/*
 * lesson_3_button.c
 *
 * Created: 08.04.2022 18:33:05
 * Author : Mishail
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD = 0b11111111;
    PORTD = 0b11111111;

    DDRB = 0b00000000;
    PORTB = 0b00000001;

    DDRC = 0b0000000;
    PORTC = 0b0001000;

    while (1) 
    {
        if (PINB == 0b00000000) {
            PORTD = 0b01010101;
        }
        if (PINC == 0b00000000) {
            PORTD = 0b10101010;
        } else {
            PORTD = 0b11111111;
        }  
    }
}

