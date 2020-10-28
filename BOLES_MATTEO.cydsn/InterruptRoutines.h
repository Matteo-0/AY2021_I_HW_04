/*
*    \file InterruptRoutines.h
*    \brief header file for the forth assignment.
*
*    This header file contains the definition of two interrupts and some variables
*
*    \author: Matteo Boles
*    \date: October 30, 2020
*/

#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H

    #include "cytypes.h"
    #include "stdio.h"
    
    #define BYTE_TO_SEND 4                                      // define how many bytes we want to send
    #define TRANSMIT_BUFFER_SIZE 1+BYTE_TO_SEND+1               // define how many bytes we send, including header and tail bytes

    CY_ISR_PROTO(Custom_ISR_ADC);                               // definition of the interrupt activated by the timer
    CY_ISR_PROTO(received_datum);                               // definition of the interrupt activated on the received byte 
    
    uint8 DataBuffer [TRANSMIT_BUFFER_SIZE];                    // array where we save the digitized values of the photoresistor and of the potentiometer  
    volatile uint8 PacketReadyFlag;                             // variable that we set to one after we have saved all the digitized values in the DataBuffer array
#endif
/* [] END OF FILE */
