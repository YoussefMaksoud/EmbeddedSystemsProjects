/* 
 * File:   TimerDelay.h
 * Author: Youssef Abdel Maksoud, Elgiz Abbasov, Kazi Ashfaque
 *
 * Created on October 22, 2020, 12:59 PM
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TIMERDELAY_H
#define	TIMERDELAY_H

#include <xc.h> // include processor files - each processor file is guarded.  


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

void timer2Init();

void delay_ms(uint16_t time_ms);

void __attribute__((interrupt, no_auto_psv))_T2Interrupt(void);

