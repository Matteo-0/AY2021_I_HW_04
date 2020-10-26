/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"

int main(void)
{
    CyGlobalIntEnable; // Enable global interrupts.
    // Start the components
    ADCDelSig_Start();
    UART_Start();
    PWM_Start();
    ISR_ADC_StartEx(Custom_ISR_ADC);
    ISR_Received_StartEx(received_datum);
   
    /*DataBufferPhotoresistor[0]=0xA0;
    DataBufferPhotoresistor[TRANSMIT_BUFFER_SIZE-1]=0xC0;
    DataBufferPotentiometer[0]=0xA0;
    DataBufferPotentiometer[TRANSMIT_BUFFER_SIZE-1]=0xC0;*/
    // Start the ADC conversion
    ADCDelSig_StartConvert();
    
    for(;;)
    {
        
    }
}