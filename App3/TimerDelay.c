/* 
 * File:   TimerDelay.c
 * Author: Youssef Abdel Maksoud, Elgiz Abbasov, Kazi Ashfaque
 *
 * Created on October 22, 2020, 12:59 PM
 */

//User header files
#include "TimerDelay.h"
#include "ChangeClk.h"

//MPLab header files
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


void timer2Init(){
    
    T1CON = 0x00;
    TMR2 = 0X0000; // TMR2 register
    
    T2CONbits.TCKPS = 0X00; // prescale set to 1:1
    T2CONbits.TSIDL = 0; // continue module operation in idle mode
    T2CONbits.T32 = 0; // timer 2 acts as 16 bit timer
    T2CONbits.TCS = 0; //internal clock f_osc/2
    T2CONbits.TGATE = 0; // disable gate timer
    
    
    
    IPC1bits.T2IP2 = 1;//Timer2 interrupt priority configuration
    IPC1bits.T2IP1 = 0;
    IPC1bits.T2IP0 = 0;//priority 6 (lower than CN interrupt priority)
    
    IFS0bits.T2IF = 0; // clear interrupt timer flag
    IEC0bits.T2IE = 1; // enable interrupt control
    
    T2CONbits.TON = 1; // start timer

}

void delay_ms(uint16_t time_ms){
    NewClk(32); //change the clock frequency
    timer2Init(); //initialize bits
    
    PR2 = time_ms*16; // PR2 computation
    
    Idle();
    NewClk(8); //when delay is done, return the clock frequency to normal
    return;      
}

void timer3Init(){
    //NewClk(32);
    
    T2CON = 0x00;
    TMR3 = 0X0000; // TMR2 register
    
    T3CONbits.TCKPS = 0X00; // prescale set to 1:1
    T3CONbits.TSIDL = 0; // continue module operation in idle mode
    T2CONbits.T32 = 0; // timer 3 acts as 16 bit timer
    T3CONbits.TCS = 0; //internal clock f_osc/2
    T3CONbits.TGATE = 0; // disable gate timer
    
    
    IPC2bits.T3IP2 = 1; //set priority to 6
    IPC2bits.T3IP1 = 1;
    IPC2bits.T3IP0 = 0;
    
    IFS0bits.T3IF = 0; // clear interrupt timer flag
    IEC0bits.T3IE = 1; // enable interrupt control
    
    //T3CONbits.TON = 1; // start timer
}

//timer 2 interrupt service routine
void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void){
    IFS0bits.T2IF = 0; //clear timer 2 interrupt flag
    T2CONbits.TON = 0;
}

void __attribute__((interrupt, no_auto_psv))_T3Interrupt(void){
    IFS0bits.T3IF = 0; //clear timer 3 interrupt flag
    T3CONbits.TON = 0; // stop the timer
    delay_ms(200);
}

