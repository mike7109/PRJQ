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

unsigned int r1_1000, r2_100=0, r3_10=0,  r4_1=0;
int z=1;

unsigned char TWI_status = 0;
unsigned char TWI_data = 0;

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
	
	TWI_start();
	
	//TWI_status = TWSR;
	
	TWDR = 0b10100000; // Адрес + запись W
	
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	
	TWDR = 0; // Старший байт адреса внешней EEPROM 24C256
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	TWDR = 8; // Младший байт адреса внешней EEPROM 24C256
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
		
	
	TWDR = 56; // Запись данных во внешнюю EEPROM 24C256
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	TWI_stop();
		
	//TWI_status = TWSR;
//////////////////////////// Принимаем данные

_delay_ms(10);

TWI_start();

//TWI_status = TWSR;

TWDR = 0b10100000; // Адрес + запись W

TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;


TWDR = 0; // Старший байт адреса внешней EEPROM 24C256
TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWDR = 8; // Младший байт адреса внешней EEPROM 24C256
TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;	
	
TWI_start();	
	
TWDR = 0b10100001; // Адрес + чтени е R

TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

// Принимаем данные из EEPROM
TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWI_data = TWDR;	
//TWI_status = TWSR;

TWI_stop();

	
	while (1)
	{
		
		//chislo(TWI_status);
		
		chislo(TWI_data);
		
		
		
	}
}



