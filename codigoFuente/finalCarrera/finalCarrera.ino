void setup() {
  Serial.begin(9600);  
  pinMode(3,INPUT);
}

void loop() {
  if(digitalRead(3) == LOW){
    Serial.println("FUNCIONA");
  }else{
    Serial.println("NO FUNCIONA");
  }
  delay(1000);         // demora de 1 segundo
}
