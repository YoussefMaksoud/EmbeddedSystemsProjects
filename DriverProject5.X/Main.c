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
// MPLAB header libraries
#include <xc.h>

int main(int argc, char** argv) {
    
    while(1){

        uint16_t value = do_ADC(); //returns digital output to the calling function
        
    }
    
    return 0;
    
}








