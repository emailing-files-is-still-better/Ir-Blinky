/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F15214
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

// ========== DEFINES ==========
#define LED_PIN     LATAbits.LATA3
#define PWM_EN      PWM3CONbits.EN
 

// ========== GLOBAL VARIABLES ==========
const bool pattern[] = {0, 1, 0, 1, 1, 1};
uint8_t patternIndex = 0;


// ========== FUNCTION PROTOTYPES ==========
void bitTimerInterrupt();


// ========== MAIN ==========
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

 
    uint16_t dutycycle;

    PWM3_Initialize();
    TMR0_Initialize();
    
     // #define CODE    00100010    // Address to transmit out
    
    TMR0_SetInterruptHandler(bitTimerInterrupt);

     //#define PREAMBLE 000100111000100111
  
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
    {      
       //output(PREAMBLE);
       //output(CODE);
       //delay(some_amount);
        
      //PWM3_LoadDutyValue(0);
        IR1;
        __delay_us(20);  
       //PWM3_LoadDutyValue(51);
        IR0;
        __delay_us(10);
        
       
    }
}


// ========== LOCAL FUNCTIONS ==========
void bitTimerInterrupt() {
    PWM_EN = pattern[patternIndex];
    
    // Increment the pattern index and reset to 0 if you've looped back around
    if (++patternIndex >= sizeof(pattern)) {        // ++var will increment var by one before using it
        patternIndex = 0;
    }
}
