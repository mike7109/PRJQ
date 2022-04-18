/*
* lesson_5_array.c
*
* Created: 09.04.2022 13:00:53
* Author : Michail
*/

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define  SEG7_DDR DDRD
#define  SEG7_PORT PORTD

/************************************************************************/
/* Виды переменных
    int -32768....32767 -> 65536
    char -128....127 -> 256

    unsigned int 0.....65535
    unsigned char 0....255
*/
/************************************************************************/
    
/*инициализация массива*/
int digits[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
};



int main(void)
{
    SEG7_DDR = 0b11111111;
    SEG7_PORT = 0b00000000;

    while (1)
    {
        
       for (int i = 0; i < 10; i++)
       {
            SEG7_PORT = digits[i];
            _delay_ms(300);
       }
       for (int i = 8; i >= 1; i--)
       {
           SEG7_PORT = digits[i];
           _delay_ms(300);
       }
        
    }
}
