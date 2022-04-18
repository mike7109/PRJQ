/*
 * lesson_8.c
 *
 * Created: 12.04.2022 23:05:44
 * Author : Mishail
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define  SEG7_DDR DDRD
#define  SEG7_PORT PORTD

int r1_100 = 0;
int r2_10 = 0;
int r3_1 = 0;

int digits [10] =
{
    0b00111111, //0
    0b00000110, //1
    0b01011011, //2
    0b01001111, //3
    0b01100110, //4
    0b01101101, //5
    0b01111101, //6
    0b00000111, //7
    0b01111111, //8
    0b01101111  //9
};


void chislo (unsigned int vse_chislo)
{
    r1_100 = vse_chislo/100;    // �����
    r2_10  = vse_chislo%100/10; // �������
    r3_1   = vse_chislo%10;		// �������
}

int main(void)
{
    
    SEG7_DDR = 0xff;
    SEG7_PORT = 0x00;
    
    DDRB |= (1<<2) | (1<<1) | (1<<0);
    PORTB &= ~((1<<2) | (1<<1) | (1<<0));
    
    while (1)
    {
        chislo(347);
        
        PORTB &= ~((1<<2) | (1<<1));	// ��������� 2 � 3 �������
        PORTB |= (1<<0);			// �������� 1 ������
        SEG7_PORT = digits [r1_100];// �����
        _delay_ms(3);
        
        PORTB &= ~((1<<2) | (1<<0));	// ��������� 1 � 3 �������
        PORTB |= (1<<1);			// �������� 2 ������
        SEG7_PORT = digits [r2_10];	// �������
        _delay_ms(3);
        
        PORTB &= ~((1<<1) | (1<<0));	// ��������� 1 � 2 �������
        PORTB |= (1<<2);			// �������� 3 ������
        SEG7_PORT = digits [r3_1];	// �������
        _delay_ms(3);
    }
}

