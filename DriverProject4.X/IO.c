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
    NewClk(8); //change clock to allow for serial display to work
    if(IFS1bits.CNIF == 1){
        delay_ms(200); // delay to allow for time to press all desired buttons
       
        //if button 1 is pressed on its own
        if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1){
           Disp2String("\n\rPushbutton 1 pressed"); //display the button pressed
           pb1Flag = 1; //raise the global flag for button 1         
        }
        
        //if button 2 is pressed on its own
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0){
           Disp2String("\n\rPushbutton 2 pressed"); //notify button 2 is pressed
           pb2Flag = 1; //raise global flag for button 2
        }
        
        //if button 3 is pressed alone
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1){         
           Disp2String("\n\rPushbutton 3 pressed");//notify button 3 is pressed
           pb3Flag = 1; //raise global flag for button 3
        }
        
        //if buttons 1 and 2 are pressed together
        else if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0){
           Disp2String("\n\rPushbuttons 1 and 2 pressed"); //notify buttons 1 and 2 are pressed
           pb1Flag = 1; //raise global flags 1 and 2
           pb2Flag = 1;
        }
        
        //if buttons 1 and 3 are pressed together
        else if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1){           
           Disp2String("\n\rPushbuttons 1 and 3 pressed"); //notify buttons 1 and 3 are pressed
           pb1Flag = 1; //raise global flags 1 and 3
           pb3Flag = 1;
        }

        //if buttons 2 and 3 are pressed together
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 0){          
           Disp2String("\n\rPushbuttons 2 and 3 pressed"); //notify buttons 2 and 3 are pressed
           pb2Flag = 1; //raise global flags 2 and 3
           pb3Flag = 1;
        }
        
        //if all buttons are pressed
        else if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 0){          
           Disp2String("\n\rAll pushbuttons pressed"); //notify all buttons pressed
           pb1Flag = 1; //raise all three global flags
           pb2Flag = 1;
           pb3Flag = 1;
        }
        //if no buttons pressed
        else{
            Disp2String("\n\rNo pushbuttons pressed");
            pb1Flag = 0; //if no pushbuttons are pressed anymore clear all global flags
            pb2Flag = 0;
            pb3Flag = 0;
        }
    }
    IFS1bits.CNIF = 0; //clear interrupt flag
    IEC1bits.CNIE = 1; //re enable the interrupt
    Nop();
}
