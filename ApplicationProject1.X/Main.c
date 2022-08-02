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
# include <stdio.h>
//# include "ADC.h"

#define MINMAX 59
#define SECMAX 59

char buffer[256];

int min = 0;
int sec = 0;

// MPLAB header libraries
#include <xc.h>

//these three global variables come from the IO.c file
extern unsigned int pb1Flag; //global interrupt flag for button 1
extern unsigned int pb2Flag; //global interrupt flag for button 2
extern unsigned int pb3Flag; //global interrupt flag for button 3
extern unsigned int count_down; //flag to enable countdown
extern unsigned int reset; // global reset flag

int main(int argc, char** argv) {
    
    IOinit(); //initializes io pins
    CNInit(); // initialize pins for cn interrupts
    
    while(1){
        NewClk(8); //change clock to alow display at 9600 baud rate
        IOCheck(); //check for raised flags
        sprintf(buffer,"\r%.2dm : %.2ds             \r", min, sec); //put time in a string buffer to prepare for display
        Disp2String(buffer); //display the time on a single line
        NewClk(32); // change clock back to slower frequency
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

//initializes IO bits
void IOinit(){
    
    TRISAbits.TRISA4 = 1; // sets pin RA4 to input 
    TRISAbits.TRISA2 = 1; // sets pin RA2 to input
    TRISBbits.TRISB4 = 1; // sets pin RB4 to input
    TRISBbits.TRISB8 = 0; // sets pin RB8 to output
    
    INTCON1bits.NSTDIS = 1; // enable nested interrupts
           
    AD1PCFG = 0xFFFF; // sets multiplexed ports to analog to digital
}

//a2, b4, a4
void IOCheck(){
    
    if(pb1Flag == 1){ // if first button is pressed
       if(min == MINMAX){
           min = 0; //ensures min does not go out of bounds
       }
       min += 1; // increments minutes
       delay_ms(1000); //slow enough so user can decide on minutes
    }
    else if(pb2Flag == 1){ // if second button pressed
       if(sec == SECMAX){
           sec = 0 - 1; // ensures minutes increments if seconds reaches 59
           min += 1;
       } 
       sec += 1; // increments seconds 
       delay_ms(1000);   //slow enough that user can decide on seconds
    }
    else if(count_down == 1){ //if countdown flag is raised, count down the timer
       if(sec == 0 && min > 0){ // decrements minutes if seconds reaches zero
           sec = SECMAX + 1; // if seconds is at 0
           min -= 1; // decrease minutes by one
       }
       if(sec >= 0 && min > -1){ // as long as there is time on the timer
           sec -= 1; //countdown every second
           Blink(500); // blink the led every second
       } 
    }
    else if(reset == 1 && count_down == 0){ // if reset flag is raised and timer is not counting down
        min = 0; // reset all time and all flags
        sec = 0;
        pb3Flag = 0;
        reset = 0;
    }
    
    //the if statement will wait for timer to be reset
    if(min == 0 && sec == 0 && count_down == 1){ //if timer is in the process of counting down and reset flag is raised
        while(min == 0 && sec == 0 && count_down == 1){ //while the above conditions hold
            Solid(); //turn on led
            sprintf(buffer,"\r%.2dm : %.2ds -- ALARM\r", min, sec); //display the following
            Disp2String(buffer);
        }
    }
}







