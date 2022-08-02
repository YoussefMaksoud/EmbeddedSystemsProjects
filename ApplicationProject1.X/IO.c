/* 
 * File:   IO.c
 * Author: youssef
 *
 * Created on November 4, 2020, 12:12 AM
 */

//MPLab header files
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

//User header files
#include "TimerDelay.h"

unsigned int pb1Flag = 0; //interrupt flag for pb1
unsigned int pb2Flag = 0; //interrupt flag for pb2
unsigned int pb3Flag = 0; //interrupt flag for pb3
unsigned int count_down = 0;
unsigned int reset = 0;

//initializes the change of notification bits
void CNInit(){
    
    //configuring the enable bits
    CNEN1bits.CN0IE = 1; 
    CNEN1bits.CN1IE = 1;
    CNEN2bits.CN30IE = 1;
    
    //configuring pull up resistors
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;
    CNPU2bits.CN30PUE = 1;
    
    //setting interrupt priority to 7 (highest)
    IPC4bits.CNIP0 = 1; 
    IPC4bits.CNIP1 = 1;
    IPC4bits.CNIP2 = 1;
    
    IFS1bits.CNIF = 0; //clear CN interrupt flag
   
    IEC1bits.CNIE = 1; //enable CN interrupts
}



void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void){

    IEC1bits.CNIE = 0; //disable interrupt shortly to prevent debounce effects
    if(IFS1bits.CNIF == 1){
       
        
        //delay_ms(200);
        
        //if button 1 is pressed on its own
        if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1){
           pb1Flag = 1; //raise the global flag for button 1  
           pb2Flag = 0;
           pb3Flag = 0;
        }
        
        //if button 2 is pressed on its own
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0){
           pb1Flag = 0; 
           pb2Flag = 1; //raise global flag for button 2
           pb3Flag = 0;
        }
        
        //if button 3 is pressed alone
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1){
            timer3Init(); //start a timer
            pb3Flag = 1; //raise the flag
            reset = 0;
            count_down = !count_down; //toggle countdown flag
            
        }
        
        //on release on any of the buttons
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1) {
            IEC0bits.T3IE = 0; //disable timer 3
            T3CONbits.TON = 0; //stop the timer (if we are in this condition, it means
            //the button was not pressed long enough for interrupt to occur)
            pb1Flag = 0; //iclear all global flags
            pb2Flag = 0;
            pb3Flag = 0;
            reset = 0;
        }
    }
    IFS1bits.CNIF = 0; //clear interrupt flag
    IEC1bits.CNIE = 1; //re enable the interrupt
    Nop();
}
