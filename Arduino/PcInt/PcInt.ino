#include <avr/interrupt.h>   
#include <avr/io.h> 

#define LEFT false
#define RIGHT true

int mPin1 = 5; // H-bridge leg 1
int mPin2 = 6; // H-bridge leg 2
int mEnable = 7; 

boolean volatile mDirection = RIGHT;
int volatile mSpeed = 200;

ISR( PCINT1_vect )
{
 if( ( ( PINC & _BV( PORTC4 ) ) && mDirection == LEFT ) ||
     ( ( PINC & _BV( PORTC5 ) ) && mDirection == RIGHT ) )
     switch_direction();
}

void setup() {
 pinMode( mPin1, OUTPUT );
 pinMode( mPin2, OUTPUT );
 pinMode( mEnable, OUTPUT );
 
 //make analog pins 5 and 6 into pin change interrupts  
 PCICR |= (1 << PCIE1);
 PCMSK1 |= (1 << PCINT12);
 PCMSK1 |= (1 << PCINT13);  
 
 digitalWrite( mEnable, HIGH );
 set_motor();
}

void loop() {   
}

void set_motor()
{
 boolean speedPin = ( mDirection ) ? mPin1 : mPin2;
 boolean unusedPin = ( mDirection ) ? mPin2 : mPin1;

 analogWrite( unusedPin, 0 );
 analogWrite( speedPin, mSpeed );  
}

void switch_direction()
{
 mDirection = !mDirection;   
 set_motor();
}
