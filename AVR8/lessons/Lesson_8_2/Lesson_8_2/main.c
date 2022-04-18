/*
 * Lesson_8_2.c
 *
 * Created: 13.04.2022 0:00:23
 * Author : Mishail
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD = 0xff;
    PORTD = 0x00;

    TCCR0 = 0b00000101; // делим 1024 бит.
    TCNT0 = 0;

    while (1) 
    {
        if (TCNT0 == 127) {
            PORTD = 0b11000011;
        }

        if (TCNT0 == 255) {
            PORTD = 0b00111100;
        }
    }
}

