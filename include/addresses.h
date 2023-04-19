#define DATA_LENGTH   30                 // Number of bits transmitted in a packet

#if DATA_LENGTH > 32
    #error "Data length has to be 32 bits or less"
#endif

#define ADDRESS_76  0b111011100011101110001011010010
#define ADDRESS_92  0b111011000011101100001101110100
#define ADDRESS_10  295
