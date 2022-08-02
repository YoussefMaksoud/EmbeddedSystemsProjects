/* 
 * File:   TimerDelay.c
 * Author: Youssef Abdel Maksoud, Elgiz Abbasov, Kazi Ashfaque
 *
 * Created on October 22, 2020, 12:59 PM
 */

# include "TimerDelay.h"
#include "ChangeClk.h"


#include <xc.h>
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} //

//Preprocessor directives - Configuration bits for MCU start up
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled


void timer2Init(){
    
   
    T1CON = 0x00;
    TMR2 = 0X0000; // TMR2 register
    
    T2CONbits.TCKPS = 0X00; // prescale set to 1:1
    T2CONbits.TSIDL = 0; // continue module operation in idle mode
    T2CONbits.T32 = 0; // timer 2 acts as 16 bit timer
    T2CONbits.TCS = 0; //internal clock f_osc/2
    T2CONbits.TGATE = 0; // disable gate timer
    
    
    
    IPC1bits.T2IP2 = 1;//Timer2 interrupt priority configuration
    IPC1bits.T2IP1 = 1;
    IPC1bits.T2IP0 = 1;//priority 7
    
    IFS0bits.T2IF = 0; // clear interrupt timer flag
    IEC0bits.T2IE = 1; // enable interrupt control
    
    T2CONbits.TON = 1; // start timer

}

void delay_ms(uint16_t time_ms){
    //NewClk(8);
    
    timer2Init();
    
    unsigned int sec = time_ms/1000; 
    PR2 = sec*16000; // PR2 computation
    
    Idle();
    
    return;      
}

//timer 2 interrupt service routine
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    IFS0bits.T2IF = 0; //clear timer 2 interrupt flag
    T2CONbits.TON = 0;
}
