#include <avr/io.h>//register definitions
#include <util/delay.h>//_delay_ms()
#include <stdlib.h>//dtostrf()
#include <string.h>//strlen()
#include "SSD1306.h"//OLED display library
#include "i2c.h"//I2C communication library
#include "my_adc_lib.h"//ADC library
#include "my_uart_lib.h"//UART library
#define t 80.0//too hot threshold in degrees F
int main(void){uart_init();//initialize UART
    i2c_init();//initialize I2C
    OLED_Init();//initialize OLED display
    adc_init();//initialize ADC
    DDRC|=(1<<PC3);//set PC3 as output for LED
    PORTC&=~(1<<PC3);//LED off initially
    DDRD&=~(1<<PD2);//set PD3 as input for button
    PORTD|=(1<<PD2);//enable internal pull up on button
    char a[10];//buffer to hold formatted temperature string
    while (1){float v=(get_adc()/1023.0)*5.0;//convert ADC count to volts
        float te=(v-0.5)/0.01;//convert voltage to Celsius
        float tem=te*9.0/5.0+32.0;//convert Celsius to Fahrenheit
        if(!(PIND&(1<<PD2))){dtostrf(te,4,1,a);//if button is pressed
            strcat(a,"C");//append unit letter
            }else{dtostrf(tem,4,1,a);//button not pressed
                strcat(a,"F");//append unit letter
                }if(tem>=t)PORTC|=(1<<PC3);//if temperature exceeds threshold
                else PORTC&=~(1<<PC3);//turn LED off
                send_string(a);//send temperature string over UART
                send_string("\r\n");//send newline
                OLED_Clear();//clear OLED screen
                OLED_GoToLine(1);//move cursor to line 1
                OLED_DisplayString("Temp:");//display label
                OLED_GoToLine(2);//move cursor to line 2
                OLED_DisplayString(a);//display temperature
                _delay_ms(500);//wait 500ms before next reading
            }}