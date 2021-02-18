#include <Nextion.h>
#include <RTClib.h>
#include <Wire.h>

#define diraccionMemoria1 0
#define diraccionMemoria2 1
#define diraccionMemoria3 2
#define diraccionMemoria4 3
#define trigPin 4
#define echoPin 5
#define finalCarrera 6
#define RELAY0 A0
#define RELAY1 A1
#define RELAY2 A2
int in1 = A0;
int in11 = A1;
String ssid;
String password;
String separador = "/";
String response;
int WifiOnOffFlag = 0;
int number46 = 0;
int Hora;
int Minuto;
int Segundo;
int porcentajeMostrar = 0;
long duration;
int distance;
int onOff0 = 0;
int onOff1 = 0;
int onOff2 = 0;
int finalCarreraSend = 0;
RTC_DS3231 rtc;     // crea objeto del tipo RTC_DS3231

//Boton GuardarWifi
NexButton buttonP0Configuracion1 = NexButton(1, 5, "b0");
NexButton buttonValvula0 = NexButton(3, 18, "b1");
NexButton buttonValvula1 = NexButton(3, 19, "b2");
NexButton buttonValvula2 = NexButton(3, 20, "b3");
NexText textUser = NexText(1, 1, "ssid");
NexText TextPass = NexText(1, 2, "passw");
char buffer[10] = {0};

NexTouch *nex_listen_list[] =
{
  &buttonP0Configuracion1,
  &buttonValvula0,
  &buttonValvula1,
  &buttonValvula2,
  NULL
};

//Funcion guardar Wifi
void buttonP0PagPrinConf1(void *ptr){
  char userCh[10];
  char PassCh[12];
  for(int i = 0; i<10;i++){
    userCh[i] = 0;
  }
  for(int i = 0; i<12;i++){
    PassCh[i] = 0;
  }
  textUser.getText(userCh, 10);
  Serial.print("\xFF\xFF\xFF");
  TextPass.getText(PassCh, 12);
  Serial.print("\xFF\xFF\xFF");
  ssid = userCh;
  password = PassCh;
}
//FUNCTION VALVULAS
void buttonValvula0Func(void *ptr){
  if(onOff0 == 1){
    if(digitalRead(finalCarrera) == HIGH){
      onOff0 = 0;
      digitalWrite(RELAY0, HIGH);
      Serial.print("page2.p0.pic=13");
      Serial.print("\xFF\xFF\xFF");
    }else{
      onOff0 = 1;
      digitalWrite(RELAY0, LOW);
      Serial.print("page2.p0.pic=12.");
      Serial.print("\xFF\xFF\xFF"); 
    }
  }else{
    onOff0 = 1;
    digitalWrite(RELAY0, LOW);
    Serial.print("page2.p0.pic=12");
    Serial.print("\xFF\xFF\xFF"); 
  }
}
void buttonValvula1Func(void *ptr){
  if(onOff1 == 1){
    if(digitalRead(finalCarrera) == HIGH){
      onOff1 = 0;
      digitalWrite(RELAY1, HIGH);
      Serial.print("page2.p1.pic=13");
      Serial.print("\xFF\xFF\xFF");
    }else{
      onOff1 = 1;
      digitalWrite(RELAY1, LOW);
      Serial.print("page2.p1.pic=12");
      Serial.print("\xFF\xFF\xFF");
    }
  }else{
    onOff1 = 1;
    digitalWrite(RELAY1, LOW);
    Serial.print("page2.p1.pic=12");
    Serial.print("\xFF\xFF\xFF");
  }
}
void buttonValvula2Func(void *ptr){
   if(onOff2 == 1){
    if(digitalRead(finalCarrera) == HIGH){
      onOff2 = 0;
      digitalWrite(RELAY2, HIGH);
      Serial.print("page2.p2.pic=13");
      Serial.print("\xFF\xFF\xFF");
    }else{
      onOff2 = 1;
      digitalWrite(RELAY2, LOW);
      Serial.print("page2.p2.pic=12");
      Serial.print("\xFF\xFF\xFF");
    }
  }else{
    onOff2 = 1;
    digitalWrite(RELAY2, LOW);
    Serial.print("page2.p2.pic=12");
    Serial.print("\xFF\xFF\xFF");
  }
}
void setup() {
 nexInit();
 Serial.begin(9600);           /* start serial for debug */
 pinMode(in1, OUTPUT);
 pinMode(in11, OUTPUT);
 digitalWrite(in1, HIGH);
 digitalWrite(in11, HIGH);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(finalCarrera, INPUT);
 pinMode(RELAY0, OUTPUT);
 pinMode(RELAY1, OUTPUT);
 pinMode(RELAY2, OUTPUT);
 digitalWrite(RELAY0, LOW);
 digitalWrite(RELAY1, LOW);
 digitalWrite(RELAY2, LOW);
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 //rtc.adjust(DateTime(__DATE__, __TIME__));
 buttonP0Configuracion1.attachPush(buttonP0PagPrinConf1);
 buttonValvula0.attachPush(buttonValvula0Func);
 buttonValvula1.attachPush(buttonValvula1Func);
 buttonValvula2.attachPush(buttonValvula2Func);
}

void loop() {
  nexLoop(nex_listen_list);
  delay(1000);
  if(WifiOnOffFlag == 1){
    WifiOnOff(WifiOnOffFlag);
    SendHorasMinsSegs();
    hcsr04();
    senDataTanque(distance);
    finalCarreraGet();
  }
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    int c = Wire.read();      /* receive byte as a character */
    //Serial.print(c); 
  delay(1000);
    if(c != 0){
      WifiOnOffFlag = 1;
      //digitalWrite(in1, HIGH);
      //digitalWrite(in11, HIGH);
    }else{
      WifiOnOffFlag = 0;
      //digitalWrite(in1, LOW);
      //digitalWrite(in11, LOW);
    }
  }
}

// function that executes whenever data is requested from master
void requestEvent() {
  if(WifiOnOffFlag == 1){
    response = "";
    String HoraString(Hora);
    String MinutoString(Minuto);
    String SegundoString(Segundo);
    response += HoraString+"/"+MinutoString+"/"+SegundoString+"/"+porcentajeMostrar+"/"+onOff0+"/"+onOff1+"/"+onOff2+"/"+finalCarreraSend;
  }else{
    response = "";
    response += ssid + separador + password + separador;
  }
  char resp[response.length()];
  response.toCharArray(resp,response.length()+1);
  Serial.println(resp);
  Wire.write(resp);  /*send string on request */
}

void senDataTanque(int numero){
      //int maxPrcentaje = 192;// es el tamaño de la imagen hasta que llena el tanque en px
      int TamTankeCapacidad = 100; //CM
      int lleno = TamTankeCapacidad - numero;
      porcentajeMostrar = (lleno * 100) / TamTankeCapacidad;
      //int porcentajeMostrarImagen = (porcentajeMostrar * maxPrcentaje) / 100;
      if(porcentajeMostrar > 10 && porcentajeMostrar < 20){
        Serial.print("page2.p3.pic=16");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 20 && porcentajeMostrar < 30){
        Serial.print("page2.p3.pic=17");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 30 && porcentajeMostrar < 40){
        Serial.print("page2.p3.pic=18");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 40 && porcentajeMostrar < 50){
        Serial.print("page2.p3.pic=29");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 50 && porcentajeMostrar < 60){
        Serial.print("page2.p3.pic=20");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 60 && porcentajeMostrar < 70){
        Serial.print("page2.p3.pic=21");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 70 && porcentajeMostrar < 80){
        Serial.print("page2.p3.pic=22");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 80 && porcentajeMostrar < 90){
        Serial.print("page2.p3.pic=23");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 90 && porcentajeMostrar < 98){
        Serial.print("page2.p3.pic=23");
        Serial.print("\xFF\xFF\xFF");
      }else if(porcentajeMostrar > 98){
        Serial.print("page2.p3.pic=10");
        Serial.print("\xFF\xFF\xFF");
      }else{
        Serial.print("page2.p3.pic=10");
        Serial.print("\xFF\xFF\xFF");
      }
      Serial.print("page2.n0.val=");
      Serial.print(porcentajeMostrar);
      Serial.print("\xFF\xFF\xFF");
}

void SendHorasMinsSegs(){
  DateTime fecha = rtc.now(); 
  Hora = fecha.hour();
  Minuto = fecha.minute();
  Segundo = fecha.second();
  Serial.print("page2.n1.val=");
  Serial.print(Hora);
  Serial.print("\xFF\xFF\xFF");
  Serial.print("page2.n2.val=");
  Serial.print(Minuto);
  Serial.print("\xFF\xFF\xFF");
  Serial.print("page2.n3.val=");
  Serial.print(Segundo);
  Serial.print("\xFF\xFF\xFF");
}
void WifiOnOff(int onOff){
  if(onOff == 1){
    Serial.print("page1.p1.pic=8");
    Serial.print("\xFF\xFF\xFF");
  }else{
    Serial.print("page1.p1.pic=9");
    Serial.print("\xFF\xFF\xFF");
  }
}
void finalCarreraGet(){
  if(digitalRead(finalCarrera) == LOW){
    Serial.print("page2.p5.pic=14");
    Serial.print("\xFF\xFF\xFF");
    digitalWrite(RELAY2, LOW);
    Serial.print("page2.p2.pic=12");
    Serial.print("\xFF\xFF\xFF");
    digitalWrite(RELAY1, LOW);
    Serial.print("page2.p1.pic=12");
    Serial.print("\xFF\xFF\xFF");
    digitalWrite(RELAY0, LOW);
    Serial.print("page2.p0.pic=12");
    Serial.print("\xFF\xFF\xFF");
    onOff0 = 0;
    onOff1 = 0;
    onOff2 = 0;
    finalCarreraSend = 0;
  }else{
    Serial.print("page2.p5.pic=15");
    Serial.print("\xFF\xFF\xFF");
    finalCarreraSend = 1;
  }
}
void hcsr04(){
    // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  /*Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");*/
  delay(50);
}
