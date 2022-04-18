/*
 * lesson_9.c
 *
 * Created: 13.04.2022 16:49:55
 * Author : Mishail
 */ 

#include <avr/io.h>

int counter = 0;

int main(void)
{
    DDRD = 0xff;
    PORTD = 0x00;

//     TCCR0 = 0b00000101; // делим 1024 бит.
//     TCNT0 = 0;

//     TCCR1B = 0b00000011; // делим на 64
//     TCNT1 = 0;

    TCCR2 = 0b00000111;
    TCNT2 = 0;

    while (1)
    {
//         if (TCNT1 == 15625) { // 1с
//             PORTD = 0b11000011;
//         }
// 
//         if (TCNT1 == 31250) { // 1с
//             TCNT1 = 0;
//             PORTD = 0b00111100;
//         }

        if (TCNT2 == 255) {
            TCNT2 = 0;
            counter++;
        }

        if (counter == 5) {
            PORTD = 0b11000011;
        }
        if (counter == 10) {
            counter = 0;
            PORTD = 0b00111100;
        }
    }
}