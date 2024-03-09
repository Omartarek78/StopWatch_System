/*
 * interfacing_project.c
 *
 *  Created on: Feb 4, 2024
 *      Author: omart
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
typedef unsigned char uint8;
uint8 secondunits=0,secondtens=0,minuteunits=0,minutetens=0,hourunits=0,hourtens=0;
ISR(TIMER1_COMPA_vect){
		secondunits++;
		if(secondunits==10){
			secondunits = 0;
			secondtens++;
		}
		if(secondtens==6){
			secondtens=0;
			minuteunits++;
		}
		if(minuteunits==10){
			minuteunits=0;
			minutetens++;
		}
		if(minutetens==6){
			minutetens=0;
			hourunits++;
		}
		if(hourunits==10){
			hourunits=0;
			hourtens++;
		}
		if(hourtens==10){
			secondunits=secondtens=minuteunits=minutetens=hourunits=hourtens=0;
		}
}
ISR(INT0_vect){
	TCNT1 = 0;
	secondunits=secondtens=minuteunits=minutetens=hourunits=hourtens=0;
}
ISR(INT1_vect){
	TCCR1B &= (~(1<<CS12))&(~(1<<CS11))&(~(1<<CS10));
}
ISR(INT2_vect){
//	TCCR1B &= (~(1<<CS12))|(1<<CS11)|(1<<CS10);
	TCCR1B = (1<<WGM12)|(1<<CS11)|(1<<CS10);
}

void INT_init(void)
{
	DDRD &= (~(1<<PD2)) & (~(1<<PD3));
	PORTD |=(1<<PD2); //for enabling pull up resistor
	MCUCR |= (1<<ISC11)|(1<<ISC10)|((1<<ISC01)&(~(1<<ISC00)));


	DDRB &= (~(1<<PB2));
	PORTB |= (1<<PB2);
	MCUCSR &= (~(1<<ISC2));

	GICR |=(1<<INT1) |(1<<INT0)|(1<<INT2);

	SREG |=(1<<7);
}
void Timer1_init(void){
	TCNT1 = 0;
	TCCR1A = (1<<FOC0);
	TCCR1B = (1<<WGM12)|(1<<CS11)|(1<<CS10);
	OCR1A = 15624;
	TIMSK |= (1<<OCIE1A);
}
int main(void)
{	DDRC |=0x0F;
	DDRA |=0b00111111;
	INT_init();
	Timer1_init();
	while(1){
		PORTA = (PORTA & 0xC0)|(0xC1);
		PORTC = (PORTC & 0xF0) | (secondunits & 0x0F);
		_delay_ms(5);
		PORTA = (PORTA & 0xC0)|(0xC2);
		PORTC = (PORTC & 0xF0) | (secondtens & 0x0F);
		_delay_ms(5);
		PORTA = (PORTA & 0xC0)|(0xC4);
		PORTC = (PORTC & 0xF0) | (minuteunits & 0x0F);
		_delay_ms(5);
		PORTA = (PORTA & 0xC0)|(0xC8);
		PORTC = (PORTC & 0xF0) | (minutetens & 0x0F);
		_delay_ms(5);
		PORTA = (PORTA & 0xC0)|(0xD0);
		PORTC = (PORTC & 0xF0) | (hourunits & 0x0F);

		_delay_ms(5);
		PORTA = (PORTA & 0xC0)|(0xE0);
		PORTC = (PORTC & 0xF0) | (hourtens & 0x0F);
		_delay_ms(5);
	}
}
