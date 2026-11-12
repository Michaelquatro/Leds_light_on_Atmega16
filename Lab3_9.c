#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Настройка портов как выходы
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;
    
    // Инициализация портов в 0
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    // Настройка PC0 как вход с подтяжкой к VCC
    DDRC &= ~(1 << PC0);
    PORTC |= (1 << PC0);
    
    uint8_t letter_on = 0;
    uint8_t prev = 1;
    
    while (1) 
    {
        uint8_t cur = (PINC & (1 << PC0)) ? 1 : 0;
        
        // Детектирование нажатия (переход 1 -> 0)
        if (prev == 1 && cur == 0)
        {
            letter_on = !letter_on;
            _delay_ms(20); // Дебаунс кнопки
        }
        
        // Управление светодиодами
        if (letter_on)
        {
            PORTA = 0b11111111;
            PORTB = 0b00011000;
            PORTC = 0b00011000;
            PORTD = 0b11111111;
        }
        else
        {
            PORTA = 0x00;
            PORTB = 0x00;
            PORTC = 0x00;
            PORTD = 0x00;
        }
        
        prev = cur;
    }
    
    return 0;
}
