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

    DDRC &= ~(1<<3); // 3ий канал ацп

    //настройка adc
    ADCSRA |= (1<<ADEN); // Включаем адс
    ADCSRA |= (1<<ADFR); // Включаем режим непрерывного измерения
    // частота дискретизации 125кГц при Fmk = 1мГц и коэф.деления = 8
    ADCSRA &= ~(1<<ADPS2); 
    ADCSRA |= (1<<ADPS1) | ((1<<ADPS0));
    
    ADMUX |= (1<<REFS1) | (1<<REFS0); // источник опорного напряжения 2.56В
    ADMUX &= ~(1<<ADLAR); // сдвинули 10 бит вправо в реигстре чтения измерения

    ADMUX &= ~((1<<3) | (1<<2));
    ADMUX |= (1<<1) | (1<<0);

    ADCSRA |= (1<<ADSC); // Запуск преобразование АЦП

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

