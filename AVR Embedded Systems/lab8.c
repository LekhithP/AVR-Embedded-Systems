#include <avr/io.h>//Include AVR I/O definitions
#include <util/delay.h>//Include delay functions
#include <stdint.h>//Include standard integer types
#define a 14//Define pin number for segment A
#define b 15//Define pin number for segment B
#define c 16//Define pin number for segment C
#define d 17//Define pin number for DP
static const uint8_t e[7]={7,b,13,6,a,9,11};//Array of 7 pins used for the 7 segment display
static const uint8_t f[4]={4,12,10,c};//Array of 4 pins used for digit selection
static const uint8_t g[12]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40,0x00};//Lookup table for 7 segment patterns:digits 0-9, then '-'
static uint8_t h[4];//Buffer for the 4 digits to display
static void i(uint8_t m){if(m<8)DDRD|=(1<<m);//Function to set a pin as output
    else if(m<14)DDRB|=(1<<(m-8));//If pin number is 0-7
    else DDRC|=(1<<(m-14));//Set corresponding bit in DDRD to output
}static void v(uint8_t m,uint8_t n){uint8_t o;//If pin number is 8-13
    if(m<8){o=(1<<m);//Adjust and set bit in DDRB
        if(n)PORTD|=o;//If pin number is 14-?
        else PORTD&=~o;//Adjust and set bit in DDRC
    }else if(m<14){o=(1<<(m-8));//Function to write a value
        if(n)PORTB|=o;//Temporary variable for bit mask
        else PORTB &=~o;//Pin on PORTD
    }else{o=(1<<(m-14));//Create bit mask
        if(n)PORTC|=o;//If value is 1
        else PORTC &=~o;//Set pin HIGH
    }}static void j(uint8_t p){for(uint8_t q=0;//If value is 0
        q<7;//Set pin LOW
        q++)v(e[q],(p>>q)&1);//Pin on PORTB
}static void k(void){for(uint8_t r=0;//Create adjusted mask
    r<4;//Pin on PORTC
    r++){for(uint8_t s=0;//Create adjusted mask
        s<4;//Function to set all 7 segment pins according to a bit pattern
        s++)v(f[s],1);//Loop over the 7 segment pins
        j(g[h[r]]);//Write each segment bit
        v(f[r],0);//Function to multiplex the 4 digits
        _delay_ms(5);//Loop over each digit position
    }}static long l(void){PORTC&=~(1<<3);//Turn all digit select pins ON
        _delay_us(2);//Set all digit pins HIGH first
    PORTC|=(1<<3);//Output the segment pattern for current digit
    _delay_us(10);//Turn ON the selected digit
    PORTC&=~(1<<3);//Wait 5ms to persist the digit
    TCCR1A=0;//Function to read ultrasonic sensor distance
    TCCR1B=(1<<CS11);//Set trigger pin
    TCNT1=0;//Wait 2µs
    while(!(PIND&(1<<3))&&TCNT1<60000);//Set trigger pin HIGH
    if(!(PIND&(1<<3))){TCCR1B=0;//Wait 10µs
        return 999;//Set trigger pin LOW again
    }TCNT1=0;//Timer1 normal mode, no PWM
    while((PIND&(1<<3))&&TCNT1<60000);//Start Timer1 with prescaler 8
    uint16_t t=TCNT1;//Reset timer counter
    TCCR1B=0;//Wait for echo pin
    return(long)(t/116);//If still LOW after timeout
}int main(void){for(uint8_t s=0;//Stop timer
    s<7;//Return error distance
    s++){i(e[s]);//Reset timer for echo high pulse measurement
        v(e[s],0);//Wait for echo LOW or timeout
    }for(uint8_t s=0;//Capture timer value
        s<4;//Stop timer
        s++){i(f[s]);//Convert ticks to cm
            v(f[s],1);//Initialize 7 segment segment pins as outputs and set LOW initially
        }i(2);//Set segment pin as output
        v(2,0);//Set segment pin LOW
    i(d);//Initialize digit select pins as outputs and set HIGH
    v(d,0);//Set digit pin as output
    DDRD&=~(1<<3);//Set digit pin HIGH
    TCCR1B=0;//Set pin 2 as output
    for(;;){long u=l();//Set pin 2 LOW
        if(u<5||u>50){h[0]=h[1]=h[2]=h[3]=10;//Set DP pin
        }else{h[0]=u%10;//Set DP pin LOW
            h[1]=(u/10)%10;//Set PD3 as input
            h[2]=(u/100)%10;//Stop Timer1 initially
            h[3]=(u/1000)%10;//Infinite loop
        }for(uint8_t s=0;//Measure distance in cm
            s<10;//If distance out of 5-50cm range
            s++)k();//Display "----"
    }}//Extract decimal digits for display