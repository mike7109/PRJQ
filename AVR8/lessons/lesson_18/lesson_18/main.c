/*
 * lesson_18.c
 *
 * Created: 15.04.2022 0:47:19
 * Author : Mishail
 */ 

 #define F_CPU 1000000UL
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>

 #define  SEG7_DDR DDRD
 #define  SEG7_PORT PORTD
 #define  VREF 5
 #define  COEF_DIV 10.0

 int r1_100 = 0;
 int r2_10 = 0;
 int r3_1 = 0;

 int z = 0;

 float voltage = 0;
 int volty = 10;

 long ADC_10 = 0;
 int zbl = 0;

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
     r1_100 = vse_chislo/100;    // сотни
     r2_10  = vse_chislo%100/10; // десятки
     r3_1   = vse_chislo%10;		// единицы
 }

 ISR(TIMER0_OVF_vect) {
    TCNT0 = 127;
  
    if (++z > 3 ) z = 1;
  
    if (z == 1) {
        PORTB |= (1<<2) | (1<<1);	// Выключаем 2 и 3 разряды
        PORTB &= ~(1<<0);			// ВКлючаем 1 разряд
        SEG7_PORT = digits [r1_100];// Сотни
        if (voltage < 10) {
            SEG7_PORT |= (1<<7);
        } else {
            SEG7_PORT &= ~(1<<7);
        }
    } else if (z == 2) {
        PORTB |= (1<<2) | (1<<0);	// Выключаем 1 и 3 разряды
        PORTB &= ~(1<<1);			// ВКлючаем 2 разряд
        SEG7_PORT = digits [r2_10];	// Десятки
        if (voltage >= 10) {
            SEG7_PORT |= (1<<7);
        } else {
            SEG7_PORT &= ~(1<<7);
        }
    } else if (z == 3) {
        PORTB |= (1<<1) | (1<<0);	// Выключаем 1 и 2 разряды
        PORTB &= ~(1<<2);			// ВКлючаем 3 разряд
        SEG7_PORT = digits [r3_1];	// Единицы
    }

 }

ISR(ADC_vect) {
    
    ADC_10 += ADC;
    zbl++;
    if (zbl >= 10) {
        voltage = ADC_10/10*VREF/1024.*COEF_DIV;

        if (voltage > 45) {
            PORTB &= ~(1<<7);
        }
        if (voltage < 40) {
            PORTB |= (1<<7);
        }
        
        volty = (voltage < 10) ? 100 : 10;

        chislo(voltage * volty);

        zbl = 0;
        ADC_10 = 0;
    }

    ADCSRA |= (1<<ADSC); // Запуск преобразование АЦП
}

 void ADC_settings() {
     //настройка adc
     ADCSRA |= (1<<ADEN); // Включаем адс
     ADCSRA &= ~(1<<ADFR); // Выключаем режим непрерывного измерения
     // частота дискретизации 125кГц при Fmk = 1мГц и коэф.деления = 8
     ADCSRA &= ~(1<<ADPS2);
     ADCSRA |= (1<<ADPS1) | ((1<<ADPS0));
 
     ADMUX |= (1<<REFS0); // источник опорного напряжения 2.56В
     ADMUX &= ~(1<<REFS1);
     ADMUX &= ~(1<<ADLAR); // сдвинули 10 бит вправо в реигстре чтения измерения

     ADMUX &= ~((1<<3) | (1<<2));
     ADMUX |= (1<<1) | (1<<0);

     ADCSRA |= (1<<ADIE); // разрешает прерывание АЦП

     ADCSRA |= (1<<ADSC); // Запуск преобразование АЦП
 }

 int main(void)
 {
 
    ADC_settings();
    
    SEG7_DDR = 0xff;
    SEG7_PORT = 0x00;
     
    DDRB |= (1<<2) | (1<<1) | (1<<0);
    PORTB |= (1<<2) | (1<<1) | (1<<0);

    DDRB |= (1<<7);

    TCCR0 = 0b00000010; // делитель на 8
    TCNT0 = 0;

    TIMSK |= (1<<TOIE0);

    sei();
     
    while (1)
    {
        //chislo(531);
    }
 }