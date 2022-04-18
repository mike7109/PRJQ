/*
 * Lesson_35.c
 *
 * Created: 13.12.2021 20:05:57
 * Author : �������
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


// ��������� TWI
void TWI_settings (void)
{
	TWBR = 2; // ������� 50 ��� ����� ������������ ��� f�� = 1 ���
	TWSR &= ~((1<<TWPS1) | (1<<TWPS0)); // ����. ������� = 1
}


// ����� TWI
void TWI_start (void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
}


// ���� TWI
void TWI_stop (void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

void get_convers(void) {

//////////////////////////// ��������� ������

_delay_ms(10);

TWI_start();

//TWI_status = TWSR;

TWDR = 0b10101010; // ����� + ������ W

TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWDR = 0; // ������� ���� ������ ������� EEPROM 24C256
TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWI_start();

TWDR = 0b10101011; // ����� + ����� � R

TWCR = (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

// ��������� ������ �� EEPROM
TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
while (!(TWCR&(1<<TWINT)))
;

TWI_data_H = TWDR;

_delay_ms(5);

// ��������� ������ �� EEPROM
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
	

	// ��������
	DDRD |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
	PORTD &= ~((1<<4) | (1<<4) | (1<<6) | (1<<7));

	DDRB |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
	PORTB &= ~((1<<4) | (1<<4) | (1<<6) | (1<<7));

	//�������
	DDRC |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
	PORTC |= (1<<3) | (1<<2) | (1<<1) | (1<<0);


	TCCR0 = 0b00000010; // ����� �������� �� �� 8
	TIMSK |= (1<<0); // ��������� ���������� ��� ������������ 0-�� ��
	TCNT0 = 0;
	
	sei();
	
	TWI_settings();	
	
// 	TWI_start();
// 	
// 	//TWI_status = TWSR;
// 	
// 	TWDR = 0b10101010; // ����� + ������ W
// 	
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
//     //TWI_status = TWSR;
// 	
// 	TWDR = 0; // ������� ���� ������ ������� EEPROM 24C256
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	TWDR = 8; // ������� ���� ������ ������� EEPROM 24C256
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 		
// 	
// 	TWDR = 56; // ������ ������ �� ������� EEPROM 24C256
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
//  * Author : �������
//  */ 
// 
// 
// /*
//  * ��� ������������� 7 ���. ���������� � ��!!!
//  * ��� ������������ ���������!!!
//  * 
//  * ������ ��������� ����� ����������� ��������� �����������!!!
//  * ������ �������� ����� ����������� ������ ���� �����������!!!
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
// void segchar (unsigned char seg)  // ����� 
// {
// 	switch(seg)
// 	{
// 			
// 		//------------����� �����
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
// void timer0_settings(void) // ��������� ������-�������� 0 �� ���������� �� ������������
// {
// 	
// 	TCCR0 &= ~(1<<0);
// 	TCCR0 &= ~(1<<2);  // ������� ������� �� 8
// 	TCCR0 |= (1<<1);
// 	
// 	TIMSK |= (1<<0); // ���������� �� ������������
// 	
// }  
// 
// 
// ISR (TIMER0_OVF_vect) // ���������� ��������� �������������� ����������
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
// void chislo_1(unsigned char number_1) // �������� �������� ����������� �� ��������� �������
// {
// 	
// 	R1 = number_1/100;
// 	R2 = number_1%100/10;
// 	R3 = number_1%10;
// 	
// }
// 
// 
// void chislo_2(unsigned char number_2) // �������� �������� ��������� �� ��������� �������
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
// // ��������� TWI
// void TWI_settings (void)
// {
// 	TWBR = 2; // ������� 50 ��� ����� ������������ ��� f�� = 1 ���
// 	TWSR &= ~((1<<TWPS1) | (1<<TWPS0)); // ����. ������� = 1
// }
// 
// 
// // ����� TWI
// void TWI_start (void)
// {
// 	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// }
// 
// 
// // ���� TWI
// void TWI_stop (void)
// {
// 	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
// }
// 
// 
// // ����� ������
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
//    DDRB |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5); // ������ ���������� ��������� ��������������� ����������
//    PORTB |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5); // ���������� ��� ������� ��������
// 	
// 	  
//    DDRD |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7); // ������ ���������� ���������� ��������������� ����������
//    PORTD &= ~((1<<0) | (1<<1) |(1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)); // ���������� ��� �������� ��������
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
// 	TWI_write(0b10101010); // ����� + W
// 
//     TWI_status = TWSR;
// 	
// 	TWI_write(0x21); // ������ �������� ����� � ������� ������
// 		
// 	TWI_write(0x26); // ������ �������� ����� � ������� ������	
// 	
// 	_delay_ms(50); // ���������!!! ����� � �� ������� ��������
// 	
// 	TWI_start(); 
// 	
// 	//TWI_status = TWSR;
// 	
// 	TWI_write(0b10001001); // ����� + R
// 	
// 	////////////// ����� ������ �� �������!!!!
// 	
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //���������!!! ����� � �� ������� ��������
// 	
// 	Tst = TWDR; // ��������� ������� ���� �����������
// 	
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //���������!!! ����� � �� ������� ��������
// 	
// 	Tml = TWDR; // ��������� ������� ���� �����������
// 	
// 	T_16 = (Tst<<8) | Tml;
// 	Tf = (float)T_16/65535*175.0;
// 	Temperature = Tf - 45; // ����������� �� �������
// 	
// 	// ��������� ����������� ����� �� �����������
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	_delay_ms(5); //���������!!! ����� � �� ������� ��������
// 	
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //���������!!! ����� � �� ������� ��������
// 	
// 	Hst = TWDR; // ��������� ������� ���� ���������
// 	
// 	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //���������!!! ����� � �� ������� ��������
// 	
// 	Hml = TWDR; // ��������� ������� ���� ���������
// 	
// 	H_16 = (Hst << 8) | Hml;
// 	Hf = (float)H_16/65535*100.0;
// 	Humidity = Hf;
// 	
// 	
// 	// ��������� ����������� ����� �� ���������
// 	TWCR = (1<<TWINT) | (1<<TWEN);
// 	while (!(TWCR&(1<<TWINT)))
// 	;
// 	
// 	_delay_ms(5); //���������!!! ����� � �� ������� ��������
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
