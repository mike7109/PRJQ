/*
 * lesson_17_adc.c
 *
 * Created: 14.04.2022 17:49:20
 * Author : Mishail
 */ 

#include <avr/io.h>


int main(void)
{
    
    DDRB |= (1<<1) | (1<<0);
    PORTB &= ~((1<<1) | (1<<0));

    DDRC &= ~(1<<3); // 3�� ����� ���

    //��������� adc
    ADCSRA |= (1<<ADEN); // �������� ���
    ADCSRA |= (1<<ADFR); // �������� ����� ������������ ���������
    // ������� ������������� 125��� ��� Fmk = 1��� � ����.������� = 8
    ADCSRA &= ~(1<<ADPS2); 
    ADCSRA |= (1<<ADPS1) | ((1<<ADPS0));
    
    ADMUX |= (1<<REFS1) | (1<<REFS0); // �������� �������� ���������� 2.56�
    ADMUX &= ~(1<<ADLAR); // �������� 10 ��� ������ � �������� ������ ���������

    ADMUX &= ~((1<<3) | (1<<2));
    ADMUX |= (1<<1) | (1<<0);

    ADCSRA |= (1<<ADSC); // ������ �������������� ���

    while (1) 
    {
        if (ADCSRA&(1<<ADIF))
        {
            if (ADC > 600)
            {
                PORTB |= (1<<0); //     green LED on
                PORTB &= ~(1<<1); //    yellow LED off
            }
            else
            {
                PORTB &= ~(1<<0); //green LED off
                PORTB |= (1<<1); //yellow LED on
            }

            ADCSRA |= (1<<ADIF);
        }
    }
}

