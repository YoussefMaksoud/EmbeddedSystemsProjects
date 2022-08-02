/* 
 * File:   Main.c
 * Author: Youssef Abdel Maksoud, Elgiz Abbasov, Kazi Ashfaque
 *
 * Created on October 22, 2020, 12:59 PM
 */

// User header files
# include "ChangeClk.h"
# include "UART2.h"
# include "ADC.h"
# include "IO.h"
# include "TimerDelay.h"

// MPLAB header libraries
# include <xc.h>

void IOinit();
void IOCheck();


extern unsigned int pb1Flag; //interrupt flag for pb1
extern unsigned int pb2Flag; //interrupt flag for pb2
extern unsigned int pb3Flag; //interrupt flag for pb3

int main(int argc, char** argv) {
    
    IOinit();
    CNInit();
    
    while(1){
        

        IOCheck();
        
    }
    
    return;
    
}

void IOinit(){
    TRISAbits.TRISA4 = 1; // sets pin RA4 to input 
    TRISAbits.TRISA2 = 1; // sets pin RA2 to input
    TRISBbits.TRISB4 = 1; // sets pin RB4 to input
    INTCON1bits.NSTDIS = 0; // enable nested interrupts
    AD1PCFG = 0xFFFF;
    AD1PCFGbits.PCFG5 = 0x0000;
    CNPU1bits.CN0PUE = 1; // enables pull up resistor
}

void IOCheck(){
    if(pb1Flag == 1 && pb2Flag == 0 && pb3Flag == 0){
        uint16_t a = Voltmeter();
    }
    else if(pb1Flag == 0 && pb2Flag == 1 && pb3Flag == 0){
        uint16_t a = Ohmmeter();
    }
    else if(pb1Flag == 0 && pb2Flag == 0 && pb3Flag == 1){
        NewClk(500);
        Idle();
    }
}




