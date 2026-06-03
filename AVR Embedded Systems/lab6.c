#include <avr/io.h> //Include AVR registers
#include <util/delay.h>//Include delay functions
#include <stdint.h>//Include fixed size integers
#define RL PC5//Red LED on A5
#define GL PC4//Green LED on A4
#define BL PC3//Blue LED on A3
#define RB PD0//Red Button on D0
#define GB PD1//Green Button on D1
#define BB PD2 //Blue Button on D2
int main(void){DDRC|=(1<<RL)|(1<<GL)|(1<<BL); //Program starts here
    DDRD&=~((1<<RB)|(1<<GB)|(1<<BB)); //Set button pins as inputs
    PORTD|=(1<<RB)|(1<<GB)|(1<<BB); //Enable pull up resistors
    while(1){uint8_t test=PIND;//Repeat forever
        if(!(test&(1<<RB))&&(test&(1<<GB))&&(test&(1<<BB))){PORTC=(PORTC&~((1<<GL)|(1<<BL)))|(1<<RL);//Only red pressed
            _delay_ms(125);//Wait 125ms
            PORTC&=~(1<<RL);//Red off
            _delay_ms(125);//Wait 125ms
            }else if((test&(1<<RB))&&!(test&(1<<GB))&&(test&(1<<BB))){PORTC=(PORTC&~((1<<RL)|(1<<BL)))|(1<<GL);//Only green pressed
                _delay_ms(125);//Wait 125ms
                PORTC&=~(1<<GL);//Green off
                _delay_ms(125);//Wait 125ms
                }else if((test&(1<<RB))&&(test&(1<<GB))&&!(test&(1<<BB))){PORTC=(PORTC&~((1<<RL)|(1<<GL)))|(1<<BL);//Only blue pressed
                    _delay_ms(125);//Wait 125ms
                    PORTC&=~(1<<BL);//Blue off
                    _delay_ms(125);//Wait 125ms
                    }else{PORTC&=~((1<<RL)|(1<<GL)|(1<<BL));//Turn all LEDs off
                    }}}