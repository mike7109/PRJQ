/*
 * Lesson_35.c
 *
 * Created: 13.12.2021 20:05:57
 * Author : Дмитрий
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define VREF 5.0

unsigned int r1_1000, r2_100=0, r3_10=0,  r4_1=0;
int z=1;

unsigned char TWI_status = 0;
unsigned char TWI_data_L = 0;
unsigned char TWI_data_H = 0;

unsigned int T_16 = 0;
float voltage = 0;

void zzz (int cifra)
{
	switch(cifra)
	{
		case 0: PORTD &= ~((1<<6) | (1<<7)); PORTB |= (1<<4) | (1<<5) | (1<<6) | (1<<7); PORTD |= (1<<4) | (1<<5); break;
		case 1: PORTB &= ~((1<<4) | (1<<7)); PORTD &= ~((1<<4) | (1<<5) | (1<<6) | (1<<7)); PORTB |= (1<<5) | (1<<6); break;
		case 2: PORTD &= ~((1<<5) | (1<<7)); PORTB &= ~(1<<6); PORTB |= (1<<4) | (1<<5) | (1<<7); PORTD |= (1<<4) | (1<<6); break;
		case 3: PORTD &= ~((1<<4) | (1<<5) | (1<<7)); PORTB |= (1<<4) | (1<<5) | (1<<6) | (1<<7); PORTD |= (1<<6); break;
		case 4: PORTB &= ~((1<<4) | (1<<7)); PORTD &= ~((1<<4) | (1<<7)); PORTB |= (1<<5) | (1<<6); PORTD |= (1<<5) | (1<<6); break;
		case 5: PORTD &= ~((1<<4) | (1<<7)); PORTB &= ~(1<<5); PORTD |= (1<<5) | (1<<6); PORTB |= (1<<4) | (1<<6) | (1<<7); break;
		case 6: PORTD &= ~(1<<7); PORTB &= ~(1<<5); PORTD |= (1<<4) | (1<<5) | (1<<6); PORTB |= (1<<4) | (1<<6) | (1<<7); break;
		case 7: PORTB &= ~(1<<7); PORTD &= ~((1<<4) | (1<<5) | (1<<6) | (1<<7)); PORTB |= (1<<4) | (1<<5) | (1<<6); break;
		case 8: PORTD &= ~(1<<7); PORTB |= (1<<4) | (1<<5) | (1<<6) | (1<<7); PORTD |= (1<<4) | (1<<5) | (1<<6); break;
		case 9: PORTD &= ~((1<<7) | (1<<4)); PORTB |= (1<<4) | (1<<5) | (1<<6) | (1<<7); PORTD |= (1<<5) | (1<<6); break;
		
	}

	
}

void chislo (unsigned int chislo_z)
{
	r1_1000 = chislo_z/1000;
	r2_100 = chislo_z%1000/100;
	r3_10 = chislo_z%100/10;
	r4_1 = chislo_z%10;
}




ISR(TIMER0_OVF_vect)
{
	if (z==1)
	{
		
		PORTC |= (1<<1);
		PORTC |= (1<<2);
		PORTC |= (1<<3);
		PORTC &= ~(1<<0);
		zzz(r1_1000);
	}
	
	if (z==2)
	{
		PORTC |= (1<<0);
		PORTC |= (1<<2);
		PORTC |= (1<<3);
		PORTC &= ~(1<<1);
		zzz(r2_100);
		PORTD |= (1<<7);
		
	}
	
	if (z==3)
	{
		PORTC |= (1<<0);
		PORTC |= (1<<1);
		PORTC |= (1<<3);
		PORTC &= ~(1<<2);
		zzz(r3_10);
	}
	
	if (z==4)
	{
		PORTC |= (1<<0);
		PORTC |= (1<<1);
		PORTC |= (1<<2);
		PORTC &= ~(1<<3);
		zzz(r4_1);
	}
	
	z++;
	
	if (z>4) z=1;
	
}


// Настройки TWI
void TWI_settings (void)
{
	TWBR = 2; // Частота 50 кГц линии тактирования при fмк = 1 МГц
	TWSR &= ~((1<<TWPS1) | (1<<TWPS0)); // Коэф. деления = 1
}


// Старт TWI
void TWI_start (void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
}


// Стоп TWI
void TWI_stop (void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

void get_convers(void) {

//////////////////////////// Принимаем данные

_delay_ms(10);

TWI_start();

//TWI_status = TWSR;

TWDR = 0b10101010; // Адрес + запись W

TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWDR = 0; // Старший байт адреса внешней EEPROM 24C256
TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWI_start();

TWDR = 0b10101011; // Адрес + чтени е R

TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

// Принимаем данные из EEPROM
TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWI_data_H = TWDR;

_delay_ms(5);

// Принимаем данные из EEPROM
TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWI_data_L = TWDR;

//TWI_status = TWSR;

TWI_stop();

T_16 = (TWI_data_H<<8) | TWI_data_L;

voltage = T_16 * VREF / 4090.0;

voltage *= 100;


}



int main(void)
{
	

	// Сегменты
	DDRD |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
	PORTD &= ~((1<<4) | (1<<4) | (1<<6) | (1<<7));

	DDRB |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
	PORTB &= ~((1<<4) | (1<<4) | (1<<6) | (1<<7));

	//Разряды
	DDRC |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
	PORTC |= (1<<3) | (1<<2) | (1<<1) | (1<<0);


	TCCR0 = 0b00000010; // Делим часототу МК на 8
	TIMSK |= (1<<0); // Разрешаем прерывания при переполнении 0-го ТС
	TCNT0 = 0;
	
	sei();
	
	TWI_settings();	
	
// 	TWI_start();
// 	
// 	//TWI_status = TWSR;
// 	
// 	TWDR = 0b10101010; // Адрес + запись W
// 	
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
//     //TWI_status = TWSR;
// 	
// 	TWDR = 0; // Старший байт адреса внешней EEPROM 24C256
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	TWDR = 8; // Младший байт адреса внешней EEPROM 24C256
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 		
// 	
// 	TWDR = 56; // Запись данных во внешнюю EEPROM 24C256
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	TWI_stop();
		
	//TWI_status = TWSR;


	while (1)
	{
		
		get_convers();

		chislo(voltage);
		
        _delay_ms(300);
		
		
	}
}











// /*
//  * Lesson_36.c
//  *
//  * Created: 16.12.2021 19:53:36
//  * Author : Дмитрий
//  */ 
// 
// 
// /*
//  * Два трехразрядных 7 сег. индикатора с ОК!!!
//  * Без транзисторов индикация!!!
//  * 
//  * Выводы сегментов обеих индикаторов соеденены параллельно!!!
//  * Выводы разрядов обеих индикаторов должны быть разденьными!!!
//  */ 
// 
// #define F_CPU 1000000UL
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// 
// 
// unsigned char R1 = 0, R2 = 0, R3 = 0, R4  = 0, R5  = 0, R6  = 0;
// unsigned char BC547 = 0;
// 
// 
// unsigned char TWI_status = 0;
// unsigned char TWI_data = 0;
// 
// unsigned char Tst = 0;
// unsigned char Tml = 0;
// unsigned int  T_16 = 0;
// float		  Tf = 0;
// int			  Temperature = 0;
// 
// unsigned char Hst = 0;
// unsigned char Hml = 0;
// unsigned int  H_16 = 0;
// float		  Hf = 0;
// int			  Humidity = 0;
// 
// void segchar (unsigned char seg)  // Цыфры 
// {
// 	switch(seg)
// 	{
// 			
// 		//------------Общий катод
// 		
// 		case 0: PORTD |= (1<<0) | (1<<1) | (1<<3) | (1<<4) | (1<<5); PORTD &= ~(1<<6); PORTD |= (1<<2); break;
// 		case 1: PORTD |= (1<<1); PORTD &= ~((1<<0) | (1<<3) | (1<<4) | (1<<5) | (1<<6)); PORTD |= (1<<2); break;
// 		case 2: PORTD &= ~(1<<2); PORTD |= (1<<1) | (1<<3) | (1<<4) | (1<<0) | (1<<6); PORTD &= ~(1<<5); break;
// 		case 3: PORTD |= (1<<2); PORTD |= (1<<1) | (1<<3) | (1<<0) | (1<<6); PORTD &= ~((1<<5) | (1<<4)); break;
// 		case 4: PORTD |= (1<<2); PORTD |= (1<<1) | (1<<5) | (1<<6); PORTD &= ~((1<<0) | (1<<4) | (1<<3)); break;
// 		case 5: PORTD |= (1<<2); PORTD |= (1<<0) | (1<<3) | (1<<5) | (1<<6); PORTD &= ~((1<<1) | (1<<4)); break;
// 		case 6: PORTD |= (1<<2); PORTD |= (1<<0) | (1<<3) | (1<<4) | (1<<5) | (1<<6); PORTD &= ~(1<<1); break;
// 		case 7: PORTD |= (1<<2); PORTD |= (1<<1) | (1<<0); PORTD &= ~((1<<3) | (1<<4) | (1<<5) | (1<<6)); break;
// 		case 8: PORTD |= (1<<2); PORTD |= (1<<0) | (1<<1) | (1<<3) | (1<<4) | (1<<5) | (1<<6); break;
// 		case 9: PORTD |= (1<<2); PORTD |= (1<<0) | (1<<1) | (1<<3) | (1<<5) | (1<<6); PORTD &= ~(1<<4); break;
// 		
// 		
// 	}
// }
// 
// void timer0_settings(void) // Настройки таймер-счетчика 0 на прерывания по переполнению
// {
// 	
// 	TCCR0 &= ~(1<<0);
// 	TCCR0 &= ~(1<<2);  // Деление частоты на 8
// 	TCCR0 |= (1<<1);
// 	
// 	TIMSK |= (1<<0); // прерывания по перепелнению
// 	
// }  
// 
// 
// ISR (TIMER0_OVF_vect) // Управление разрядами семисегменрого индикатора
// {
// 	
// 	if (BC547==0) { PORTB |=(1<<1); PORTB |=(1<<2); PORTB |=(1<<3); PORTB |=(1<<4); PORTB |=(1<<5); segchar (R1); PORTB &=~(1<<0); PORTD &=~(1<<7);}
// 	if (BC547==1) { PORTB |=(1<<0); PORTB |=(1<<3); PORTB |=(1<<3); PORTB |=(1<<4); PORTB |=(1<<5); segchar (R2); PORTB &=~(1<<1); PORTD &=~(1<<7);}
// 	if (BC547==2) { PORTB |=(1<<0); PORTB |=(1<<1); PORTB |=(1<<3); PORTB |=(1<<4); PORTB |=(1<<5); segchar (R3); PORTB &=~(1<<2); PORTD &=~(1<<7);}
// 	if (BC547==3) { PORTB |=(1<<0); PORTB |=(1<<1); PORTB |=(1<<2); PORTB |=(1<<4); PORTB |=(1<<5); segchar (R4); PORTB &=~(1<<3); PORTD &=~(1<<7);}
// 	if (BC547==4) { PORTB |=(1<<0); PORTB |=(1<<1); PORTB |=(1<<2); PORTB |=(1<<3); PORTB |=(1<<5); segchar (R5); PORTB &=~(1<<4); PORTD &=~(1<<7);}	
// 	if (BC547==5) { PORTB |=(1<<0); PORTB |=(1<<1); PORTB |=(1<<2); PORTB |=(1<<3); PORTB |=(1<<4); segchar (R6); PORTB &=~(1<<5); PORTD &=~(1<<7);}
// 	BC547++;
// 	if (BC547>5) BC547=0;
// }
// 
// 
// 
// void chislo_1(unsigned char number_1) // Разбивка значения температуры на отдельные разряды
// {
// 	
// 	R1 = number_1/100;
// 	R2 = number_1%100/10;
// 	R3 = number_1%10;
// 	
// }
// 
// 
// void chislo_2(unsigned char number_2) // Разбивка значения влажности на отдельные разряды
// {
// 	
// 	R4 = number_2/100;
// 	R5 = number_2%100/10;
// 	R6 = number_2%10;
// 	
// 	
// }
// 
// 
// // Настройки TWI
// void TWI_settings (void)
// {
// 	TWBR = 2; // Частота 50 кГц линии тактирования при fмк = 1 МГц
// 	TWSR &= ~((1<<TWPS1) | (1<<TWPS0)); // Коэф. деления = 1
// }
// 
// 
// // Старт TWI
// void TWI_start (void)
// {
// 	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// }
// 
// 
// // Стоп TWI
// void TWI_stop (void)
// {
// 	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
// }
// 
// 
// // Заись команд
// void TWI_write (unsigned char twi_com)
// {
// 	TWDR = twi_com;
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// }
// 
// 
// 
// int main(void)
// {
//    DDRB |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5); // Выводы управления разрядами семисегментного индикатора
//    PORTB |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5); // Изначально все разряды погасшие
// 	
// 	  
//    DDRD |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7); // Выводы управления сегментами семисегментного индикатора
//    PORTD &= ~((1<<0) | (1<<1) |(1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)); // Изначально все сегменты погасшие
//      
// 
// 	sei ();
// 	
// 	timer0_settings ();
// 	
// 	
// 	TWI_settings ();
// 	
// 	
// 	TWI_start();
// 	
// 	TWI_write(0b10101010); // Адрес + W
// 
//     TWI_status = TWSR;
// 	
// 	TWI_write(0x21); // Запись старшего байта в регистр команд
// 		
// 	TWI_write(0x26); // Запись младшего байта в регистр команд	
// 	
// 	_delay_ms(50); // Проверить!!! Можно и не ставить задержку
// 	
// 	TWI_start(); 
// 	
// 	//TWI_status = TWSR;
// 	
// 	TWI_write(0b10001001); // Адрес + R
// 	
// 	////////////// Прием данных от датчика!!!!
// 	
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
// 	
// 	Tst = TWDR; // Принимаем старший байт температуры
// 	
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
// 	
// 	Tml = TWDR; // Принимаем младший байт температуры
// 	
// 	T_16 = (Tst<<8) | Tml;
// 	Tf = (float)T_16/65535*175.0;
// 	Temperature = Tf - 45; // Температура по Цельсию
// 	
// 	// Принимаем контрольную сумму по температуре
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
// 	
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
// 	
// 	Hst = TWDR; // Принимаем старший байт влажности
// 	
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
// 	
// 	Hml = TWDR; // Принимаем младший байт влажности
// 	
// 	H_16 = (Hst << 8) | Hml;
// 	Hf = (float)H_16/65535*100.0;
// 	Humidity = Hf;
// 	
// 	
// 	// Принимаем контрольную сумму по влажности
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
// 	
// 	TWI_stop();
// 	
//     while (1) 
//     {
// 		
// 		
// 		chislo_1(TWI_status);
// 		
// 		//chislo_2(Humidity);
// 		
// 		
//     }
// }
// 
// 
// 
// 
// 
// 
// 
