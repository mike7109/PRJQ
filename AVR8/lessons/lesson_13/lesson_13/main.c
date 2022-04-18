/*
 * lesson_13.c
 *
 * Created: 14.04.2022 2:19:22
 * Author : Mishail
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD |= (1<<0);
    PORTD &= ~(1<<0);

    while (1) 
    {
    }
}

