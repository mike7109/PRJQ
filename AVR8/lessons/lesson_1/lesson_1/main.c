/*
 * lesson_1.c
 *
 * Created: 07.04.2022 17:23:00
 * Author : Mishail
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD = 0b00000001; //��������� ���� �� �����(1) � ����(0)
    PORTD = 0b00000001; //�������� ������� ������: 1 - �������, 0 - ������

    while (1) 
    {
    }
}

