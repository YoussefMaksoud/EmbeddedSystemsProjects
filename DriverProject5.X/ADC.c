/* 
 * File:   ADC.c
 * Author: youssef
 *
 * Created on November 22, 2020, 8:37 PM
 */


#include <xc.h>
#include "ADC.h"
#include "UART2.h" 
#include <stdio.h>

void ADCInit(){

    AD1CON1bits.ADON = 0b1; //turn on analogue to digital conversion
    AD1CON1bits.FORM = 0b00; //integer form
    AD1CON1bits.SSRC = 0b111; //enable auto triggered conversion
    AD1CON1bits.ASAM = 0b0; // ADC sampling
    
    AD1CON2bits.VCFG = 0b000;
    AD1CON2bits.CSCNA = 0b0; // no input scan enabled
    AD1CON2bits.SMPI = 0b0000; // interrupt after each sample
    AD1CON2bits.BUFM = 0b0; //16 bit buffer
    AD1CON2bits.ALTS = 0b0; // Using mux A
    
    AD1CON3bits.ADRC = 0b0; // system clock derivation
    AD1CON3bits.SAMC = 0b1010; // 1/10th sampling time
    
    AD1CHSbits.CH0NA = 0b0; // vr - is zero
    AD1CHSbits.CH0SA = 0b0101; // vr+ will be voltage at AN5
    
    AD1PCFG = 0b0; // analogue
    
    IPC3bits.AD1IP = 0b101; // set priority to 5
    IFS0bits.AD1IF = 0b0; // clear interrupt flag
    IEC0bits.AD1IE = 0b1; // enable interrupt
}

uint16_t do_ADC(void){
    
    uint16_t ADCvalue; // 16 bit register used to hold ADC converted digital output ADC1BUF0
    uint16_t num_of_bars = 1; // number of bars to display on graph
    NewClk(500); // allow display at 4800 baud rate
    ADCInit(); //initialize ADC bits
    
    AD1CON1bits.SAMP = 0b1; //Start Sampling, Conversion starts automatically after SSRC and SAMC settings
    while(AD1CON1bits.DONE == 0b0) // wait for sampling to finish
    {}
    
    ADCvalue = ADC1BUF0; // ADC output is stored in ADC1BUF0 as this point   
    AD1CON1bits.SAMP = 0b0; //Stop sampling
    AD1CON1bits.ADON = 0b0; //Turn off ADC, ADC value stored in ADC1BUF0;
    
    //printing the graph and value
    
    if(ADCvalue >= 1023/30){
        num_of_bars = ADCvalue * 30 / 1023; // make number of bars proportional to digital output
    }
    
    XmitUART2('\r', 1); //clear line
    XmitUART2('-', num_of_bars); //display bars
    XmitUART2(' ', 30 - num_of_bars); //display hex value of digital output at a fixed position on the screen
    Disp2Hex(ADCvalue); //display the hex digital output
    XmitUART2('\r', 1); // clear line
        
    
    //NewClk(32);
    return ADCvalue; //returns 10 bit ADC output stored in ADC1BIF0 to calling function
}

void __attribute__((Interrupt, no_auto_psv))_ADC1Interrupt(void){
    
    IFS0bits.AD1IF = 0;//clear th interrupt flag
    
}

