/*
 * lesson_11.c
 *
 * Created: 13.04.2022 23:18:15
 * Author : Mishail
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int z = 0;

ISR(TIMER1_OVF_vect) {
    
    TCNT1 = 49910;
    z++;
    if (z >= 10) {
        z = 0;
        PORTC ^= (1<<0);
    }
    
}

int main(void)
{
    // найстрока кучи диодов
    DDRD = 0xff;
    PORTD = 0x00;
    
    // настройка порта для одинокого диода
    DDRC |= (1<<0);
    PORTC &= ~(1<<0);

    //настройка таймер-счетчика
    TCCR1B = 0b00000011; // делитель
    TCNT1 = 49910;

    TIMSK |= (1<<TOIE1);// разрешаем прерывания при переполенение первого 1-ого таймер счетчика

    sei();

    while (1)
    {
        PORTD = 0b00000000;
        _delay_ms(300);
        PORTD = 0b00000001;
        _delay_ms(300);
        PORTD = 0b00000011;
        _delay_ms(300);
        PORTD = 0b00000111;
        _delay_ms(300);
        PORTD = 0b00001111;
        _delay_ms(300);
        PORTD = 0b00011111;
        _delay_ms(300);
        PORTD = 0b00111111;
        _delay_ms(300);
        PORTD = 0b01111111;
        _delay_ms(300);
        PORTD = 0b11111111;
        _delay_ms(300);
    }
}