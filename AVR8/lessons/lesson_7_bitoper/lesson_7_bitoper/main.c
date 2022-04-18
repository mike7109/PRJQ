/*
 * lesson_7_bitoper.c
 *
 * Created: 10.04.2022 15:10:45
 * Author : Mishail
 */ 

# define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define  SEG7_DDR DDRD
#define  SEG7_PORT PORTD

int r1_1000 = 0;
int r2_100 = 0;
int r3_10 = 0;
int r4_1 = 0;

/*������������� �������*/
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

void chicslo(unsigned int vse_chislo) {
    r1_1000 = vse_chislo / 1000;
    r2_100 = vse_chislo % 1000 / 100;
    r3_10 = vse_chislo % 100 / 10;
    r4_1 = vse_chislo %10;
}

int main(void)
{
    SEG7_DDR = 0xff;
    SEG7_PORT = 0x00;

    DDRB |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
    PORTB |= (1<<3) | (1<<2) | (1<<1) | (1<<0);

    DDRB &= ~(1<<7);
    PORTB |= (1<<7);

    unsigned int chislo_7seg = 0;
    unsigned int timer = 0;
    while (1) 
    {
        
        if (~PINB & (1<<7)) {
            chislo_7seg = 0;
        }

        chicslo(chislo_7seg);

        PORTB |= (1<<3) | (1<<2) | (1<<1); //��������� 2 � 1 ������
        PORTB &= ~(1<<0); // �������� 1 ������
        SEG7_PORT = digits[r1_1000]; // �����

        _delay_ms(3);

        PORTB |= (1<<3) | (1<<2) | (1<<0); //��������� 2 � 1 ������
        PORTB &= ~(1<<1); // �������� 1 ������
        SEG7_PORT = digits[r2_100]; // �����

        _delay_ms(3);

        PORTB |= (1<<3) | (1<<1) | (1<<0); //��������� 2 � 1 ������
        PORTB &= ~(1<<2); // �������� 1 ������
        SEG7_PORT = digits[r3_10]; // �����

        _delay_ms(3);

        PORTB |= (1<<2) |(1<<1) | (1<<0); //��������� 2 � 1 ������
        PORTB &= ~(1<<3); // �������� 1 ������
        SEG7_PORT = digits[r4_1]; // �����

        _delay_ms(3);
        timer++;
        if (timer == 10) {
            timer = 0;
            chislo_7seg = (chislo_7seg + 1) % 10000;
        }
        
          
    }
}

// if (0 == (PINB & (1<<0))) - ��������, ��� ������ 0 ��� � pinb ����� 0.
// if (!(PINB & (1<<0))) - ���� �����, ��� � ����.
// if (~PINB & (1<<0)) - �� �� �����, ��� ����. ���������, ��� 0 ��� ����� 0.
// if (PINB & (1<<0)) - ���������, ��� 0 ��� ����� 1.
// if (PINB & (1<<3)) - ���������, ��� 3 �� ����� 1.

