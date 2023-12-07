#include "Lib_ds18b20.h"
#include "stdio.h"
void GPIO_Pin_Input()
{
    DDRD &= ~(1 << PD0);
}
int GPIO_Read_Input()
{
    if (PIND & (1 << PD0))
        return 1;
    return 0;
}
void GPIO_Pin_Output()
{
    DDRD |= (1 << PD0);
    PORTD &= ~(1 << PD0);
}
void GPIO_Write_Output()
{

    PORTD &= ~(1 << PD0);
}
void GPIO_Write_Output_high()
{
    PORTD |= (1 << PD0);
}
uint8_t ds18b20_init(void)
{
    GPIO_Pin_Output();   // set the pin as output
    GPIO_Write_Output(); // pull the pin LOW
    _delay_us(480);      // delay according to datasheet
    GPIO_Pin_Input();    // set the pin as input
    _delay_us(80);
    if (!GPIO_Read_Input()) // if the pin is low i.e the presence pulse is there
    {
        _delay_us(400); // wait for 400 us
        return 0;
    }
    else
    {
        _delay_us(400); // wait for 400 us
        return 1;
    }
}
void write_ds18b20(uint8_t data)
{
    GPIO_Pin_Output(); // set as output
    for (int i = 0; i < 8; i++)
    {
        if (data >> i & 0x01) // if the bit is high
        {
            // write 1
            GPIO_Pin_Output();   // set as output
            GPIO_Write_Output(); // pull the pin LOW
            _delay_us(1);        // wait for us
            GPIO_Pin_Input();    // set as input
            _delay_us(60);       // wait for 60 us
        }
        else // if the bit is low
        {
            // write 0
            GPIO_Pin_Output();
            GPIO_Write_Output(); // pull the pin LOW
            _delay_us(50);       // wait for 50 us
            GPIO Pin Input();

            _delay_us(10);
        }
    }
}
uint8_t read_ds18b20(void)
{
    uint8_t value = 0;
    -GPIO_Pin_Input();
    for (int i = 0; i < 8; i++)
    {
        GPIO_Pin_Output();     // set as output
        GPIO_Write_Output();   // pull the data pin LOW
        _delay_us(5);          // wait for 5 us
        GPIO_Pin_Input();      // set as input
        if (GPIO_Read_Input()) // if the pin is HIGH
        {
            value = 1 << i; // read = 1
        }
        _delay_us(55); // wait for 55 us
    }
    return value;
}
float get_temperature()
{
    uint16_t temp = 0;
    float temperature = 0;
    uint8_t temp_1 = 0, temp_h = 0;
    ds18b20_init();
    write_ds18b20(0xCC);
    write_ds18b20(0x44);
    _delay_ms(800);
    ds18b20_init();
    write_ds18b20(0xCC);
    write_ds18b20(0xBE);
    temp_1 = read_ds18b20();
    temp_h = read_ds18b200();
    temp = (temp_h << 8)\temp_1;
    temperature = (float)temp / 16;
    return temperature;
}