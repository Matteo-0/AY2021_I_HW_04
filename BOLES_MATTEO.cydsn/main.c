/*
*    \file main.c
*    \brief Main source file for the forth assignment.
*
*    In this main source file we start the components and initialize the variables
*
*    \author: Matteo Boles
*    \date: October 30, 2020
*/

#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"

int main(void)
{
    CyGlobalIntEnable;                             // Enable global interrupts
    
    // Start the components
    ADCDelSig_Start();
    UART_Start();
    PWM_Start();
    ISR_ADC_StartEx(Custom_ISR_ADC);
    ISR_Received_StartEx(received_datum);
    
    // Initialize send flag
    PacketReadyFlag = 0;                           // this variable tells us if the digitized values of the photoresistor and of the potentiometer have been saved in the DataBuffer array                
    
    DataBuffer[0]=0xA0;                            // we save the header byte in the first position of the DataBuffer array
    DataBuffer[TRANSMIT_BUFFER_SIZE-1]=0xC0;       // we save the tail byte in the last position of the DataBuffer array
    
    // Start the ADC conversion
    ADCDelSig_StartConvert();
    
    for(;;)
    {
        if (PacketReadyFlag == 1)                  // if the digitized values of the photoresistor and of the potentiometer are ready
        {
            UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE);          // we print the digitized values of the photoresistor and of the potentiometer
            PacketReadyFlag = 0;                                      // we set the value again to zero to wait for the next digitized values
        }
        
    }
}