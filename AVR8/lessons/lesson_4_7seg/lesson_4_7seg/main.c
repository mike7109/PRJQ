/*
 * lesson_4_7seg.c
 *
 * Created: 08.04.2022 23:01:58
 * Author : Mishail
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define SEG7_DDR DDRB
#define SEG7_PORT PORTB

int main(void)
{
    DDRD = 0b11111111;
    PORTD = 0b00000000;

    DDRC = 0b0000000;
    PORTC = 0b0000001;

    while (1) 
    {
// 		SEG7_PORT = 0b00111111; //0
// 		_delay_ms(300);
// 		SEG7_PORT = 0b00000110; //1
// 		_delay_ms(300);
// 		SEG7_PORT = 0b01011011; //2
// 		_delay_ms(300);
// 		SEG7_PORT = 0b01001111; //3
// 		_delay_ms(300);
// 		SEG7_PORT = 0b01100110; //4
// 		_delay_ms(300);
// 		SEG7_PORT = 0b01101101; //5
// 		_delay_ms(300);
// 		SEG7_PORT = 0b01111101; //6
// 		_delay_ms(300);
// 		SEG7_PORT = 0b00000111; //7
// 		_delay_ms(300);
// 		SEG7_PORT = 0b01111111; //8
// 		_delay_ms(300);
// 		SEG7_PORT = 0b01101111; //9
// 		_delay_ms(300);
//       SEG7_PORT = 0b10000000; //точка
// 		_delay_ms(500)

        if (PINC == 0b1000000) {
            PORTD = 0b00000110; //1
        } else {
            PORTD = 0b00111111; //0
        }
    }
}

