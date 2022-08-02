/* 
 * File:   main.c
 * Author: Youssef
 *
 * Created on September 18, 2020, 6:46 PM
 */

#include <xc.h>

int id[] = {3, 0, 0, 6, 2, 8, 9, 1};

void main (void){ 

    //set RA0 - RA2 and RA 4 as inputs 1
    
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    
    //RB0-RB2, RB4, RB7-RB9, RB12 as outputs 0
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    
    while(1){
        
        if(PORTA == 0x0000){
            //do nothing
        }
        else if(PORTA == 0x0001){
            displayLED(0);
        }
        else if(PORTA == 0x0002){
            displayLED(1);
        }
        else if(PORTA == 0x0003){
            displayLED(2);
        }
        else if(PORTA == 0x0004){
            displayLED(3);
        }
        else if(PORTA == 0x0005){
            displayLED(4);
        }
        else if(PORTA == 0x0006){
            displayLED(5);
        }
        else if(PORTA == 0x0007){
            displayLED(6);
        }
        else if(PORTA == 0x0010){
            displayLED(7);
        }
        else{
            //do nothing
        }
        LATB = 0X0000;
            
    }
}

void displayLED(int index){
    //function takes an integer argument index and 
    //displays LED according to the index passed
    
    if(index == 0){
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 1;
        LATBbits.LATB2 = 1;
    }
    else if(index == 1){
        LATB = 0;
    }
    else if(index == 2){
        LATB = 0;
    }
    else if(index == 3){
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 1;
        LATBbits.LATB2 = 1;
        LATBbits.LATB4 = 1;
        LATBbits.LATB7 = 1;
        LATBbits.LATB8 = 1;
    }
    else if(index == 4){
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 1;
    }
    else if(index == 5){
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 1;
        LATBbits.LATB2 = 1;
        LATBbits.LATB4 = 1;
        LATBbits.LATB7 = 1;
        LATBbits.LATB8 = 1;
        LATBbits.LATB9 = 1;
        LATBbits.LATB12 = 1;
    }
    else if(index == 6){
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 1;
        LATBbits.LATB2 = 1;
        LATBbits.LATB4 = 1;
        LATBbits.LATB7 = 1;
        LATBbits.LATB8 = 1;
        LATBbits.LATB9 = 1;
        LATBbits.LATB12 = 1;
        LATBbits.LATB13 = 1;
    }
    else if(index == 7){
        LATBbits.LATB0 = 1;
    }
    else{
        return;
    }
    
}

