/*
 * lesson_10.c
 *
 * Created: 13.04.2022 19:18:23
 * Author : Mishail
 */ 

 #define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define  SEG7_DDR DDRB
#define  SEG7_PORT PORTB

int zbl = 0;
    
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

ISR(INT0_vect) {
    SEG7_PORT = digits[6];
    _delay_ms(2500);
}

int main(void)
{
    SEG7_DDR = 0b11111111;
    SEG7_PORT = 0b00000000;

    DDRD &= ~((1<<3) | (1<<2));
    PORTD |= (1<<3) | (1<<2);

    //настройка прериывания
    MCUCR |= (1<<ISC01); // прерывание int0 по спаду
    MCUCR &= ~(1<<ISC00);

    GICR |= (1<<INT0); // Разрешаем прерывание оп int0

    //SREG |= (1<<7); // разрешаем глобальные прерывания
    sei(); // разрешаем глобальные прерывания, анлог строчки выше.

    //SREG &= ~(1<<7); // запрещаем глобальные прерывания
    //cli(); // запрещаем глобальные прерывания, анлог строчки выше.

    while (1)
    {
        SEG7_PORT = digits[0];        _delay_ms(300);        SEG7_PORT = digits[1];        _delay_ms(300);        SEG7_PORT = digits[2];        _delay_ms(300);
        SEG7_PORT = digits[3];
        _delay_ms(300);        SEG7_PORT = digits[4];        _delay_ms(300);        SEG7_PORT = digits[5];        _delay_ms(300);        SEG7_PORT = digits[6];        _delay_ms(300);        SEG7_PORT = digits[7];        _delay_ms(300);        SEG7_PORT = digits[8];        _delay_ms(300);        SEG7_PORT = digits[9];        _delay_ms(300);
        SEG7_PORT = digits[8];        _delay_ms(300);
        SEG7_PORT = digits[7];        _delay_ms(300);
        SEG7_PORT = digits[6];        _delay_ms(300);
        SEG7_PORT = digits[5];        _delay_ms(300);
        SEG7_PORT = digits[4];        _delay_ms(300);
        SEG7_PORT = digits[3];        _delay_ms(300);
        SEG7_PORT = digits[2];        _delay_ms(300);
        SEG7_PORT = digits[1];        _delay_ms(300);
        
    }
}