# IR Blinky

## Observed Information

 - IR Modulation Frequency: 54.8kHz
 - IR Modulation Duty Cycle: 59.6% high, then low
 - Bit timing: 133us - 146us
 - Message Repetition Interval: A message starts every 11.9ms

### Packet Structure

`AAAAAAAAAA AAAAAAAAAA BBBBBBBBB`

(10 bits, then the same 10 bits again, then 9 bits)

### Observed Codes

 - 64: `1001001100 1001001100 111101110`
 - 65: `1101110100 1101110100 110100100`
 - 76: `0001000111 0001000111 010010110`
 - 92: `0001001111 0001001111 001000100`

