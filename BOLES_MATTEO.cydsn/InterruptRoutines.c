/*
*    \file InterruptRoutines.c
*    \brief source file for the forth assignment.
*
*    This source file allows to control the brightness of a LED through a potentiometer once the LED is activated.
*    The LED is activated after the sampled signal coming from a photoresistor falls under a certain threshold.
*
*    \author: Matteo Boles
*    \date: October 30, 2020
*/

// Include required header files
#include "InterruptRoutines.h"
#include "project.h"

// Variables declaration
int32 value_digit_photo, value_digit_pot;                      // variables where we save the digitized values of the photoresistor and of the potentiometer
uint8 ch_received;                                             // variable where we save the char sent for the remote control 
uint8 SendBytesFlag=0;                                         // variable used to take trace of when the char 'b' or 'B' is sent so that we can start sampling signals

CY_ISR (Custom_ISR_ADC)
{
    Timer_ReadStatusRegister();                                // Read Timer status register to bring interrupt line low
    if (SendBytesFlag)                                         // if this flag is 1 we start to read the digitized values of the ADC
    { 
        AMux_FastSelect(0);                                    // we select the first channel of the Mux
        value_digit_photo = ADCDelSig_Read32();                // we read the digitized value of the photoresistor
        
        // this is done to fix unstable behaviours that would lead the digitized value below zero or over 65535
        if (value_digit_photo < 0)      value_digit_photo = 0;
        if (value_digit_photo > 65535)  value_digit_photo = 65535;
        
        AMux_FastSelect(1);                                    // we select the second channel of the Mux
        value_digit_pot = ADCDelSig_Read32();                  // we read the digitized value of the potentiometer
        
        // this is done to fix unstable behaviours that would lead the digitized value below zero or over 65535
        if (value_digit_pot < 0)        value_digit_pot = 0;         
        if (value_digit_pot > 65535)    value_digit_pot = 65535; 
        
        if (value_digit_photo < 20000)                          // if the digitized value of the photoresistor is below a certain threshold 
        {       
            PWM_WriteCompare(value_digit_pot);                  // we set the brightness of the external LED according to the digitized value of the potentiometer
        }
        else                                                    // if the digitized value of the photoresistor is over a certain threshold
        {
            PWM_WriteCompare(0);                                // we turn the external LED off
        }
        
        // we save the digitized values of the photoresistor and of the potentiometer in the DataBuffer array taking into account the most and least significant bits
        DataBuffer[1] = value_digit_photo >> 8;                   
        DataBuffer[2] = value_digit_photo & 0xFF;               
        DataBuffer[3] = value_digit_pot >> 8;
        DataBuffer[4] = value_digit_pot & 0xFF;          
        
        PacketReadyFlag = 1;                // we set this variable to 1 to say that the digitized values have been saved in the DataBuffer array
    }
}

CY_ISR (received_datum)                     // interrupt activated on the received byte
{
    ch_received = UART_GetChar();           // we save the char sent 
    
    switch(ch_received)
    {
        case 'B':                           // if the char sent was 'b' or 'B'
        case 'b':
            SendBytesFlag=1;                
            InternalLED_Write(1);               
            Timer_Start();                  // we start the timer that activates an ISR where we read and save the digitized values coming from the photoresistor and the potentiometer
            ADCDelSig_StartConvert();       // we start the ADC conversion
            break;                           
        case 'S':                           // if the char sent was 's' or 'S'
        case 's':
            SendBytesFlag=0;                 
            InternalLED_Write(0);           
            PWM_WriteCompare(0);            // we turn off the external LED
            Timer_Stop();                   // we stop the timer that activates the ISR where we read and save the digitized values coming from the photoresistor and the potentiometer
            ADCDelSig_StopConvert();        // we stop the ADC conversion
        default:
            break;
    }
}
/* [] END OF FILE */
