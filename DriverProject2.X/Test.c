/* 
 * File:   Test.c
 * Authors: youssef Abdel Maksoud, Elgiz Abbasov, Kazi Ashfaque
 *
 * Created on October 15, 2020, 1:00 PM
 */

# include <xc.h>

int main(int argc, char** argv) {
    
    IOinit(); // IOinit() initializes the input and output ports
    
    while(1){
        IOcheck();   // checks if any of the pushbuttons are pressed
    }
    
    return;
    
}

void IOinit(){
    TRISAbits.TRISA4 = 1; // sets pin RA4 to input 
    TRISAbits.TRISA2 = 1; // sets pin RA2 to input
    TRISBbits.TRISB4 = 1; // sets pin RB4 to input
    TRISBbits.TRISB8 = 0; // sets pin RB8 to output
    CNPU1bits.CN0PUE = 1; // enables pull up resistor
    AD1PCFG = 0xFFFF; // sets multiplexed ports to analog
}

void IOcheck(){
    
    // this while loop is only satisfied and entered if 2 or more push
    //buttons are pressed
    while((PORTAbits.RA2 + PORTBbits.RB4 + PORTAbits.RA4) <= 1){
        LATBbits.LATB8 = 1; // led on
    }
     
    // if push button 1 is pressed, the led blinks at
    //approximately 1 blink per second
    while(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 1 && PORTBbits.RB4 == 1){
        LATBbits.LATB8 = 1; //led on
        delay(30); // delays 1 second
        LATBbits.LATB8 = 0; //led off
        delay(30); //delays 1 second
    }
    
    // if push button 2 is pressed, the led blinks at
    //approximately 1 blink every 2 seconds
    while(PORTAbits.RA4 == 1 && PORTAbits.RA2 == 1 && PORTBbits.RB4 == 0){
        LATBbits.LATB8 = 1; // led on
        delay(60); // delays 2 seconds
        LATBbits.LATB8 = 0; // led off
        delay(60); // delays 2 seconds
    }
    
    // if push button 3 is pressed, the led blinks at
    //approximately 1 blink every 3 seconds
    while(PORTAbits.RA4 == 1 && PORTAbits.RA2 == 0 && PORTBbits.RB4 == 1){
        LATBbits.LATB8 = 1; // led on
        delay(90); // delays 3 seconds
        LATBbits.LATB8 = 0; // led off
        delay(90); // delays 3 seconds
    }
        //sets led to OFF
        LATBbits.LATB8 = 0; // led off
}

// the delay function takes an integer argument, loops 
// then recursively calls itself sec number of times
//to cause a delay
void delay(int sec){
    if(sec == 0){ // base case for recursion
        return;
    }
    
    int i = 0; // counter
    while(i < (sec*10000)){ // loop to create a delay
        i++;
    }
    
    delay(sec - 1); // recursive call to extend delay duration
}



