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
#include <math.h>

// MPLAB header libraries
# include <xc.h>

void IOinit();
void IOCheck();


extern unsigned int pb1Flag; //interrupt flag for pb1
extern unsigned int pb2Flag; //interrupt flag for pb2
extern unsigned int pb3Flag; //interrupt flag for pb3

uint16_t clk;
uint16_t div;

int test_case;

// CLOCK CONTROL
#pragma config IESO = OFF // 2 Speed Startup disabled
#pragma config FNOSC = FRC // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor off
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS //Primary Oscillator/External clk freq betwn
#pragma config OSCIOFNC = ON //CLKO output disabled on pin 8, use as IO.
#pragma config POSCMOD = NONE // Primary oscillator mode is disabled

int main(int argc, char** argv) {
    
    IOinit();
    CNInit();
    PulseInit(5);
    
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
        Pulsemeter();
    }
}

void PulseInit(int c){
    // Change Clock
    test_case = c;
    if(c == 1){ //1000000
        NewClk(8); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
        clk = 80;
        //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
        TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO // pin 18
        REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
        REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
        REFOCONbits.RODIV = 0b0011;
        REFOCONbits.ROEN = 1; // Ref oscillator is enabled
        
    }
    else if(c == 2){ // 15625
        ///////////////PULSE TEST SETTING 1
        // Change Clock
        NewClk(8); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
        clk = 80;
        //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
        TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
        REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
        REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
        REFOCONbits.RODIV = 0b1001;
        REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    }
    else if(c == 3){ // 244
        // Change Clock
        NewClk(8); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
        clk = 80;
        //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
        TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
        REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
        REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
        REFOCONbits.RODIV = 0b0111;
        REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    }
    else if(c == 4){ //976
        // Change Clock
        NewClk(500); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
        clk = 5;
        //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
        TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
        REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
        REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
        REFOCONbits.RODIV = 0b1001;
        REFOCONbits.ROEN = 1; // Ref oscillator is enabled 
    }
    else if(c == 5){ // 3906
        // Change Clock
        NewClk(500); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
        clk = 5;
        //Clock output on REFO/RB15 ? PULSE GEN Testing purposes only
        TRISBbits.TRISB15 = 0; // Set RB15 as output for REFO
        REFOCONbits.ROSSLP = 1; // Ref oscillator is disabled in sleep
        REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
        REFOCONbits.RODIV = 0b0111;
        REFOCONbits.ROEN = 1; // Ref oscillator is enabled 
    }
    
    div = pow(2, REFOCONbits.RODIV);
}






