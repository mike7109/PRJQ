/*
 * lesson_12.c
 *
 * Created: 14.04.2022 0:33:51
 * Author : Mishail
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int r1_1000 = 0;
int r2_100 = 0;
int r3_10 = 0;
int r4_1 = 0;

int z=0;

int seconds = 0;


int digits [10] = {
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00000111,  // 7
    0b01111111,  // 8
    0b01101111   // 9
};

void chislo (unsigned int vse_chislo)
{
    r1_1000 = vse_chislo/1000;		// “ыс€чи
    r2_100 = vse_chislo%1000/100;	// —отни
    r3_10 = vse_chislo%100/10;		// ƒес€тки
    r4_1 = vse_chislo%10;			// ≈диницы
}

ISR(TIMER0_OVF_vect)
{
    //TCNT0 = 128;
    z++;
    if(z>4) z=1;
    if (z==1)
    {
        PORTB |= (1<<3) | (1<<2) | (1<<1); // ¬џ Ћючаем 2-й, 3-й и 4-й разр€ды
        PORTB &= ~(1<<0);		  // ¬ Ћёчаем 1-й разр€д
        
        PORTD = digits[r1_1000]; // ќтображаем тыс€чи
    }
    else if (z==2)
    {
        PORTB |= (1<<3) | (1<<2) | (1<<0); // ¬џ Ћючаем 1-й, 3-й и 4-й разр€ды
        PORTB &= ~(1<<1);		  // ¬ Ћёчаем 2-й разр€д
        
        PORTD = digits[r2_100]; // ќтображаем сотни
        
    }
    else if (z==3)
    {
        PORTB |= (1<<3) | (1<<1) | (1<<0); // ¬џ Ћючаем 1-й,2-й и 4-й разр€ды
        PORTB &= ~(1<<2);		  // ¬ Ћёчаем 3-й разр€д

        PORTD |= (1<<7);
        
        PORTD = digits[r3_10] | (1<<7);
        
    }
    else if (z==4)
    {
        PORTB |= (1<<2) | (1<<1) | (1<<0); // ¬џ Ћючаем 1-й, 2-й и 3-й разр€ды
        PORTB &= ~(1<<3);		  // ¬ Ћёчаем 4-й разр€д
        
        PORTD = digits[r4_1]; // ќтображаем единицы
    }
}

ISR(TIMER1_COMPA_vect) {
    if (--seconds <= 0) {
        seconds = 0;
        PORTC |= (1<<0);
        TCCR1B &= ~((1<<CS11)); // делитель 64
    }
    
}

int main(void)
{
    DDRD = 0xff;
    PORTD = 0x00;
    
    DDRB |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
    PORTB |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
    
    DDRC |= (1<<0);
    PORTC &= ~(1<<0);
    
    DDRC &= ~((1<<4) | (1<<3) | (1<<2) | (1<<1));
    PORTC |= ((1<<4) | 1<<3) | (1<<2) | (1<<1);
    
    TCCR0 = 0b00000010;
    TIMSK |= (1<<TOIE0);

    //TCCR1B |= (1<<CS11) | (1<<CS10); // делитель 64
    //TCCR1B |= (1<<CS11); // делитель 8
    TCCR1B &= ~(1<<CS12);

    TCNT1 = 0; // счетный регистр

    OCR1A = 12500; // установка в значени€ в регистр сравненеи€ дл€ 0.1
    //OCR1A = 15625; // установка в значени€ в регистр сравненеи€

    TIMSK |= (1<<OCIE1A); // разрешаем прерывание при сравнении первого таймер счетчика
    TCCR1B |= (1<<WGM12); // сброс TCNT1 в ноль при совпадение
    sei(); 

    while (1)
    {
        chislo(seconds);

        if (~PINC&(1<<1)) {
            seconds += 10;
            if (seconds >= 9999) seconds = 9999;
            _delay_ms(150);
        }

        if (~PINC&(1<<2)) {
            seconds -= 10;
            if (seconds >= 0) seconds = 0;
            _delay_ms(150);
        }

        if (~PINC&(1<<3)) {
            TCCR1B |= (1<<CS11); // вкл - делитель 8
            _delay_ms(150);
        }

        if (~PINC&(1<<4)) {
            TCCR1B &= ~(1<<CS11); // выкл - делитель 8
            _delay_ms(150);
        }


    }
}


