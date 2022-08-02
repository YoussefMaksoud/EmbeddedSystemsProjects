/* 
 * File:   Main.c
 * Author: Youssef Abdel Maksoud, Elgiz Abbasov, Kazi Ashfaque
 *
 * Created on October 22, 2020, 12:59 PM
 */

// User header files
# include "ChangeClk.h"
# include "UART2.h"
# include "IO.h"
# include "TimerDelay.h"

// MPLAB header libraries
#include <xc.h>


//these three global variables come from the IO.c file
extern unsigned int pb1Flag; //global interrupt flag for button 1
extern unsigned int pb2Flag; //global interrupt flag for button 2
extern unsigned int pb3Flag; //global interrupt flag for button 3

int main(int argc, char** argv) {
    
    IOinit(); // IOinit() initializes the input and output ports
    CNInit(); // configures interrupt change notification bits
    Disp2String("\n\rNo pushbuttons pressed");
    
    while(1){
        
        // checks if any of the pushbuttons are pressed 
        //based on the flags raised by the CN interrupt service routine
        IOcheck();   
        
    }
    
    return 0;
    
}

//turns led on blinking at the specified rate
void Blink(uint16_t time_ms){
    
    LATBbits.LATB8 = 1;
    delay_ms(time_ms);
    LATBbits.LATB8 = 0;
    delay_ms(time_ms);
    
}

//turns led on without blinking
void Solid(){
    
    LATBbits.LATB8 = 1; 
    
}

//turns led off
void OFF(){
    
    LATBbits.LATB8 = 0; 
    
}

//initializes io bits
void IOinit(){
    
    TRISAbits.TRISA4 = 1; // sets pin RA4 to input 
    TRISAbits.TRISA2 = 1; // sets pin RA2 to input
    TRISBbits.TRISB4 = 1; // sets pin RB4 to input
    TRISBbits.TRISB8 = 0; // sets pin RB8 to output
    
    INTCON1bits.NSTDIS = 1; // enable nested interrupts
           
    AD1PCFG = 0xFFFF; // sets multiplexed ports to analog to digital
}

//checks for flags raised by the CN interrupt service routine lights up led accordingly
void IOcheck(){
    
    if(pb1Flag && !pb2Flag && !pb3Flag){
        Blink(500); //blinks once every 500 milliseconds
    }
    else if(!pb1Flag && pb2Flag && !pb3Flag){
        Blink(2000); //blinks every 2 seconds
    }
    else if(!pb1Flag && !pb2Flag && pb3Flag){
        Blink(3000); //blinks every 3 seconds
    }
    else if(pb1Flag && pb2Flag && !pb3Flag){
        Solid(); //led lights up solid
    }
    else if(pb1Flag && !pb2Flag && pb3Flag){
        Solid(); //led lights up solid
    }
    else if(!pb1Flag && pb2Flag && pb3Flag){
        Solid(); //led lights up solid
    }
    else if(pb1Flag && pb2Flag && pb3Flag){
        Solid(); //led lights up solid
    }
    else{
        OFF(); //led is turned off
    }
}







