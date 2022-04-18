/*
 * lesson_1.c
 *
 * Created: 07.04.2022 17:23:00
 * Author : Mishail
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD = 0b00000001; //открывает порт на выход(1) и вход(0)
    PORTD = 0b00000001; //выбирает уровень выхода: 1 - высокий, 0 - низкий

    while (1) 
    {
    }
}

