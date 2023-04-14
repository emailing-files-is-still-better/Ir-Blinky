#include "mcc_generated_files/mcc.h"
#include "addresses.h"

// ========== DEFINES ==========
#define DEFAULT_DATA                    ADDRESS_92  // Default address to transmit
#define TRANSMISSION_INTERVAL           10800       // Time between transmissions (in us)

#define LED_PIN     LATAbits.LATA3      // Write to this to force the pin high (1) or low (0)
#define PWM_EN      PWM3CONbits.EN      // Enables (1) or Disables (0) the PWM Output

#define BITS_PER_TRANSMISSION   (TRANSMISSION_INTERVAL/135)


// ========== GLOBAL VARIABLES ==========
bool data1[BITS_PER_TRANSMISSION] = {0};    // Data of our packet including delay (slot 1)
bool data2[BITS_PER_TRANSMISSION] = {0};    // Data of our packet including delay (slot 2)
bool* currArrayStartPtr = &data1[0];  // Points to the beginning of an array
bool* nextArrayStartPtr = &data2[0];  // Points to the beginning of the next array to transmit
uint8_t bitIndex = 0;                       // Keeps track of our bit position


// ========== FUNCTION PROTOTYPES ==========
void bitTimerInterrupt(void);
void stepThroughDataPatterns(uint32_t firstPattern, uint32_t finalPattern, uint16_t repeatEachPatternNTimes);
void repeatTransmission(uint16_t numOfTimes);
void beginTransmission(void);
void waitForTransmissionFinish(void);
void setDataPattern(uint32_t newDataPattern, uint8_t bitSize, bool* startPtr);
void switchArrays(void);

// ========== MAIN ==========
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    PWM3_Initialize();
    TMR0_Initialize();
    
    TMR0_SetInterruptHandler(bitTimerInterrupt);
    TMR0_StopTimer();                               // Begin with bit timer stopped

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // Set the data pattern
    setDataPattern(DEFAULT_DATA, DATA_LENGTH, currArrayStartPtr);

    while(1) {
        stepThroughDataPatterns(0, ((1UL<<DATA_LENGTH) - 1), 10);
     }
}


// ========== LOCAL FUNCTIONS ==========
void bitTimerInterrupt(void) {
    PWM_EN = currArrayStartPtr[bitIndex++];   // Enable or Disable PWM based on current bit, then increment index
}


void stepThroughDataPatterns(uint32_t firstPattern, uint32_t finalPattern, uint16_t repeatEachPatternNTimes) {
    setDataPattern(firstPattern, DATA_LENGTH, currArrayStartPtr);
    uint32_t nextPattern = firstPattern;                // Next Pattern to transmit. Initialized to firstPattern, will be incremented before used
    do {
        beginTransmission();
        repeatTransmission(repeatEachPatternNTimes - 1);
        // Final transmission is still underway at this point
        nextPattern++;
        setDataPattern(nextPattern, DATA_LENGTH, nextArrayStartPtr);
        waitForTransmissionFinish();
        switchArrays();
    } while(nextPattern <= finalPattern);
}


void repeatTransmission(uint16_t numOfTimes) {
    for(uint16_t timesLeft=numOfTimes; timesLeft>0; timesLeft--) {
        waitForTransmissionFinish();
        beginTransmission();
    }
}


void beginTransmission(void) {
  bitIndex = 0;               // Re-initialize bit index
  TMR0_StartTimer();          // Start bit timer
}


void waitForTransmissionFinish(void) {
  while(bitIndex < BITS_PER_TRANSMISSION);     // Wait here until the bit index reaches the end of the array
  TMR0_StopTimer();                            // Stop bit timer
}


/* Loads data[] with bools to correspond to an input
 *   For instance: setDataPattern(0b11011101) or setDataPattern(0xDD) or setDataPattern(221)
 *   Will result in data[] being set to {1, 1, 0, 1, 1, 1, 0, 1}
 */
void setDataPattern(uint32_t newDataPattern, uint8_t bitSize, bool* startPtr) {
    for(uint8_t i=0; i<bitSize; i++) {
        // To set the left most array element (element 0), you need to address
        // the left most bit (bit 7 in an 8 bit number). Bit 0 is the right most bit.
        startPtr[i] = ((newDataPattern & 1UL<<((bitSize-1)-i)) != 0);
    }
}


void switchArrays(void) {
    static bool* lastArrayStartPtr = &data1[0];       // static means it is only initialized once, then keeps its state for the next function call
    lastArrayStartPtr = currArrayStartPtr;
    currArrayStartPtr = nextArrayStartPtr;
    nextArrayStartPtr = lastArrayStartPtr;
}
