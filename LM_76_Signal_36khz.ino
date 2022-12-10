#define MODULATION_FREQ_KHZ   36

const byte LED = 10; 

// Calculate delays for modulation frequency
const float pinUpdateTime_us = 3.40;    // Time it takes to change a pin from a 0 to 1 or 1 to 0
// digitalWrite is slow! https://roboticsbackend.com/arduino-fast-digitalwrite/
const unsigned int modulationDelayTime_us = (unsigned int)((500/MODULATION_FREQ_KHZ)-pinUpdateTime_us);

void setup() {
  pinMode (LED, OUTPUT);
}

void pulse(int microseconds) {
    int fullModulationPulses = (microseconds*MODULATION_FREQ_KHZ)/1000;
    for (int i=0; i<fullModulationPulses; i++) {
      digitalWrite(LED,LOW);
      delayMicroseconds(10);
      digitalWrite(LED,HIGH);
      delayMicroseconds(10);
    }
}

void loop() {
//Start Preamble
  pulse(422);
  delayMicroseconds(130/3.258);// delay 0
  pulse(283);
  delayMicroseconds(570/3.258);// 570/3.05
  pulse(422);
  delayMicroseconds(130/3.258);// 570/3.05
  pulse(283);
  delayMicroseconds(570/3.258);// 570/3.05
//End Preamble

//Start Emitter Number  
  pulse(56);
  delayMicroseconds(130/2.9);// delay 0
  pulse(56);
  pulse(56);
  delayMicroseconds(130/3.258);// delay 0
  pulse(56);
  delayMicroseconds(260/3.258);// delay 00 
  pulse(56);
//End Emitter Number 
  
//Signal Gap
 delayMicroseconds(7960/3.258);// 10870/3.05
  //pulse(283);
  //delayMicroseconds(130/3.258);// 570/3.05
  //pulse(422);
  //delayMicroseconds(130/3.258);// 570/3.05
  //pulse(150);  
  delayMicroseconds(7960/3.258);// 10870/3.05
  //digitalWrite(LED,LOW);
  //delayMicroseconds(850);// 850us/3.05 Modulation Factor
  //digitalWrite(LED,HIGH);
  //delayMicroseconds(570);// 570/3.05
  //digitalWrite(LED,LOW);
  //delayMicroseconds(1230);// 1230us/3.05 Modulation Factor
  //digitalWrite(LED,HIGH);
  //delayMicroseconds(10870);// 570/3.05
  
}
