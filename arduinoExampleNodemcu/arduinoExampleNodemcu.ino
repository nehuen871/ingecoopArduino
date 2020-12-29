#include <Wire.h>
int in1 = A0;
int in11 = A1;

void setup() {
 pinMode(in1, OUTPUT);
 pinMode(in11, OUTPUT);
 digitalWrite(in1, HIGH);
      digitalWrite(in11, HIGH);
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */
}

void loop() {
 delay(100);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    int c = Wire.read();      /* receive byte as a character */
    Serial.print(c); 
  delay(3000);
    if(c != 0){
      digitalWrite(in1, HIGH);
      digitalWrite(in11, HIGH);
    }else{
      digitalWrite(in1, LOW);
      digitalWrite(in11, LOW);
    }
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
 Wire.write("Hello NodeMCU");  /*send string on request */
}
