const byte LED = 10; 

void setup() {
  pinMode (LED, OUTPUT);


}  // end of setup
void pulse422(){
    for (int i=0; i<5; i++) {
    digitalWrite(LED,LOW);
    delayMicroseconds(10);
    digitalWrite(LED,HIGH);
    delayMicroseconds(10);
  }
}
void pulse283(){
    for (int i=0; i<5; i++) {
    digitalWrite(LED,LOW);
    delayMicroseconds(10);
    digitalWrite(LED,HIGH);
    delayMicroseconds(10);
  }
}
void pulse1(){
    for (int i=0; i<2; i++) {
    digitalWrite(LED,LOW);
    delayMicroseconds(9);
    digitalWrite(LED,HIGH);
    delayMicroseconds(9);
  }
}
int out=LOW;
void loop() {
//Start Preamble
  pulse422();
  delayMicroseconds(130/3.258);// delay 0
  pulse283();
  delayMicroseconds(570/3.258);// 570/3.05
  pulse422();
  delayMicroseconds(130/3.258);// 570/3.05
  pulse283();
  delayMicroseconds(570/3.258);// 570/3.05
//End Preamble

//Start Emitter Number  
  pulse1();
  delayMicroseconds(130/2.9);// delay 0
  pulse1();
  pulse1();
  delayMicroseconds(130/3.258);// delay 0
  pulse1();
  delayMicroseconds(260/3.258);// delay 00 
  pulse1();
//End Emitter Number 
  
//Signal Gap
 delayMicroseconds(7960/3.258);// 10870/3.05
  //pulse283();
  //delayMicroseconds(130/3.258);// 570/3.05
  //pulse422();
  //delayMicroseconds(130/3.258);// 570/3.05
  //pulse150();  
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
