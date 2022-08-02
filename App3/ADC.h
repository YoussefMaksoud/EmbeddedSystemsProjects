//
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  



#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

void ADCInitAN5();
void ADCInitAN11();
void ADCInitAN12();
uint16_t Voltmeter(void);
uint16_t Ohmmeter(void);
void Pulsemeter(void);

void __attribute__((Interrupt, no_auto_psv))_ADC1Interrupt(void);

