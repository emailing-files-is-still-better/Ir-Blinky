#include "mcc_generated_files/mcc.h"

// ========== DEFINES ==========
#define LED_PIN     LATAbits.LATA3      // Write to this to force the pin high (1) or low (0)
#define PWM_EN      PWM3CONbits.EN      // Enables (1) or Disables (0) the PWM Output
 

// ========== GLOBAL VARIABLES ==========
const bool preamble[] = {1, 1, 1, 0, 1, 1, 0, 0, 0, 0,                         
                         1, 1, 1, 0, 1, 1, 0, 0, 0, 0};       // Preamble
const bool pattern[] = {1, 1, 0, 1, 1, 1, 0, 1};              // Data of our packet
const bool delayBetweenTransmissions[61] = {0};               // Fill an array of zeros
bool* arrayStartPtr = NULL;                                   // Points to the beginning of an array
uint8_t bitIndex = 0;                                         // Keeps track of our bit position


// ========== FUNCTION PROTOTYPES ==========
void bitTimerInterrupt();
void transmitBits(bool* arrayStart, uint8_t size);

// ========== MAIN ==========
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    PWM3_Initialize();
    TMR0_Initialize();
    
    TMR0_SetInterruptHandler(bitTimerInterrupt);

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
    {
      transmitBits(&preamble[0], sizeof(preamble));
      transmitBits(&pattern[0], sizeof(pattern));
      transmitBits(&delayBetweenTransmissions[0], sizeof(delayBetweenTransmissions));
    }
}


// ========== LOCAL FUNCTIONS ==========
void bitTimerInterrupt() {
    PWM_EN = arrayStartPtr[bitIndex++];   // Enable or Disable PWM based on current bit, then increment index
}


void transmitBits(bool* arrayStart, uint8_t size) {
  bitIndex = 0;               // Re-initialize bit index
  arrayStartPtr = arrayStart; // Point to the start of the array we want to transmit
  while(bitIndex < size);     // Wait here until the bit index reaches the end of the array
}
