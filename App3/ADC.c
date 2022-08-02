/* 
 * File:   ADC.c
 * Author: youssef
 *
 * Created on November 22, 2020, 8:37 PM
 */


#include <xc.h>
#include "ADC.h"
#include "UART2.h" 
#include "TimerDelay.h"
#include <stdio.h>

#define OMEGA "\u03a9"

char buffer[256];

extern uint16_t clk;
extern uint16_t div;

extern  int pb3Flag;
extern int test_case;

int count = 0;

void ADCInitAN5(){

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
    
    //AD1PCFG = 0xFFFF; // analogue
    //AD1PCFGbits.PCFG4 = 0b1;
    
    IPC3bits.AD1IP = 0b101; // set priority to 5
    IFS0bits.AD1IF = 0b0; // clear interrupt flag
    IEC0bits.AD1IE = 0b1; // enable interrupt
}

void ADCInitAN11(){

    AD1CON1bits.ADON = 0b1; //turn on analog to digital conversion
    AD1CON1bits.FORM = 0b00; //integer form
    AD1CON1bits.SSRC = 0b111; //enable auto triggered conversion
    AD1CON1bits.ASAM = 0b0; // ADC sampling
    
    AD1CON2bits.VCFG = 0b000;
    AD1CON2bits.CSCNA = 0b0; // no input scan enabled
    AD1CON2bits.SMPI = 0b0000; // interrupt after each sample
    AD1CON2bits.BUFM = 0b0; //16 bit buffer
    AD1CON2bits.ALTS = 0b0; // Using Mux A
    
    AD1CON3bits.ADRC = 0b0; // system clock derivation
    AD1CON3bits.SAMC = 0b1010; // 1/10th sampling time
    
    AD1CHSbits.CH0NA = 0b0; // Vr - is zero
    AD1CHSbits.CH0SA = 0b1011; // Vr+ will be voltage at AN11
    
    //AD1PCFG = 0b0; // analog
    
    IPC3bits.AD1IP = 0b111; // set priority to 5
    IFS0bits.AD1IF = 0b0; // clear interrupt flag
    IEC0bits.AD1IE = 0b1; // enable interrupt
}

void ADCInitAN12(){

    AD1CON1bits.ADON = 0b1; //turn on analog to digital conversion
    AD1CON1bits.FORM = 0b00; //integer form
    AD1CON1bits.SSRC = 0b111; //enable auto triggered conversion
    AD1CON1bits.ASAM = 0b0; // ADC sampling
    
    AD1CON2bits.VCFG = 0b000;
    AD1CON2bits.CSCNA = 0b0; // no input scan enabled
    AD1CON2bits.SMPI = 0b0000; // interrupt after each sample
    AD1CON2bits.BUFM = 0b0; //16 bit buffer
    AD1CON2bits.ALTS = 0b0; // Using Mux A
    
    AD1CON3bits.ADRC = 0b0; // system clock derivation
    AD1CON3bits.SAMC = 0b1010; // 1/10th sampling time
    
    AD1CHSbits.CH0NA = 0b0; // Vr - is zero
    AD1CHSbits.CH0SA = 0b1100; // Vr+ will be voltage at AN12
    
    //AD1PCFG = 0b0; // analog
    
    IPC3bits.AD1IP = 0b110; // set priority to 6
    IFS0bits.AD1IF = 0b0; // clear interrupt flag
    IEC0bits.AD1IE = 0b1; // enable interrupt
}

uint16_t Voltmeter(void){
    
    uint16_t ADCvalue; // will hold digital output of the analog in put at channel 5
    float resolution = 3.2/1023;
    float dec_voltage;
    NewClk(500); // allow for display at 4800 baud rate
    ADCInitAN5(); // initialize the ADC converter bits and enable channel 5 as analog input
    
    AD1CON1bits.SAMP = 0b1; // start sampling
    while(AD1CON1bits.DONE == 0b0){} // sample
    
    ADCvalue = ADC1BUF0; // get the ADC output
    AD1CON1bits.SAMP = 0b0; // stop sampling
    AD1CON1bits.ADON = 0b0; // turn off converter
    
    dec_voltage = ADCvalue * resolution; // convert digital output to decimal voltage
    
    sprintf(buffer,"\rVOLTMETER Voltage = %f V     \r", dec_voltage);
    Disp2String(buffer); // display text

    //NewClk(8);
    return ADCvalue;
}

uint16_t Ohmmeter(void){
    uint16_t ADCvalue; // will hold digital output of the analog in put at channel 5
    float dec_voltage; // decimal value of digital voltage
    float resolution = 3.2/1023;
    float dec_resistance; // voltage in decimal form
    uint16_t pull_up_res = 1000; // known value of pull up resistor on channel 10
    NewClk(500); // allow for display at 4800 baud rate
    ADCInitAN11(); // initialize the ADC converter bits and enable channel 5 as analog input
    
    AD1CON1bits.SAMP = 0b1;// start sampling
    while(AD1CON1bits.DONE == 0b0){} // sample
    
    ADCvalue = ADC1BUF0; // get ADC output
    AD1CON1bits.SAMP = 0b0; // stop sampling
    AD1CON1bits.ADON = 0b0; // turn off converter
    
    dec_voltage = ADCvalue * resolution; // convert digital output to decimal voltage
    
    dec_resistance = (pull_up_res * dec_voltage)/(3.2 - dec_voltage); // voltage divider formula
    
    sprintf(buffer,"\rOHMMETER Resistance =  %f %s            \r", dec_resistance, OMEGA);
    Disp2String(buffer); // display the following text
    
    //NewClk(8);
    
}

void Pulsemeter(void){
    count = 0;
    float freq;
    float amp;
    float resolution = 3.2/1023;
    uint16_t ADCvalue;
    ADCInitAN12(); // initialize the ADC converter bits and enable channel 5 as analog input
    
    
    timer3Init();
    
    if(test_case == 1 || test_case == 2 || test_case == 2 ){
        NewClk(8);
    }        
    else{
        NewClk(500);
    }
    
    AD1CON1bits.SAMP = 0b1;// start sampling  
    T3CONbits.TON = 1;
    while(AD1CON1bits.DONE == 0b0){
    }
    

    T3CONbits.TON = 0;
    ADCvalue = ADC1BUF0; // get ADC output
    AD1CON1bits.SAMP = 0b0; // stop sampling
    AD1CON1bits.ADON = 0b0; // turn off converter
    
    amp = ADCvalue * resolution;
    freq = (clk * 100000)/(2*div*TMR3);
    
    sprintf(buffer, "\rPULSEMETER Frequency = %.2f kHz, Amplitude = %.2f V\r",freq, amp);
    
    NewClk(500);
    
    Disp2String(buffer);

}

void __attribute__((Interrupt, no_auto_psv))_ADC1Interrupt(void){
    
    if(ADC1BUF0 == 1023 && count == 0 && pb3Flag == 1){
        T3CONbits.TON = 1;
        count++;
    }
    else if(ADC1BUF0 == 1023 && count == 1 && pb3Flag == 1){
        T3CONbits.TON = 0;
        count++;
    }
    IFS0bits.AD1IF = 0;//clear th interrupt flag
    
}

