#include "LCD.h"
#include <stdio.h>
#include <string.h>
#include "Lib_ds18b20.h"
int main(void)
{
    int temp = 0;
    init_LCD();
    clr_LCD();      // xoa noi dung LCD
    move_LCD(2, 4); // di chuyen den dong 2 bat dau tu ki tu thu 4
    print_LCD("XIN CHAO");
    move_LCD(1, 1); // di chuyen den dong 1 bat dau tu ki tu thu 1
    char str[80];
    ds18b20_init();
    while (1)
    {
        GPIO_Pin_Input();
        // nhiet_do = read_ds18b20();
        temp = get_temperature();
        move_LCD(1, 1);
        sprintf(str, "NHIET DO: %d *C", temp);
        clr_LCD();
        print_LCD(str);
    }
}
