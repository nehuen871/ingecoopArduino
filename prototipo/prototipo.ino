#include <Nextion.h>
#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <EEPROM.h>


// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT22 

#define diraccionMemoria1 0
#define diraccionMemoria2 1
#define diraccionMemoria3 2
#define diraccionMemoria4 3
int in1 = A0;
int in11 = A1;
int MaxCharsEnviados = 50;
String response = "";
int number46 = 0;
String user;
String pass;
String WifiOlvidar;
String Valvula1;
String Valvula2;
String Valvula3;
String FinalDeCarrera;
String Hora;
String Minuto;
String Segundo;
String Porcentaje;
struct HumTemp{
  float temp;
  float hum;
};

struct Configuracion{
  int TempMax;
  int TempMin;
  int HuMax;
  int HuMin;
  int Thora;
  int Tmin;
};
int finalCarrera = 3;
int ventilador1 = 4;
int ventilador2 = 5;
int resistencia1 = 6;
int resistencia2 = 7;

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;     // crea objeto del tipo RTC_DS3231

//Boton GuardarWifi
NexButton buttonP0Configuracion1 = NexButton(1, 5, "b0");
NexButton buttonOlvidar = NexButton(1, 7, "b2");
NexText textUser = NexText(1, 1, "ssid");
NexText TextPass = NexText(1, 2, "passw");
char buffer[10] = {0};

NexTouch *nex_listen_list[] =
{
  &buttonP0Configuracion1,
  &buttonOlvidar,
  NULL
};

//Funcion guardar Wifi
void buttonP0PagPrinConf1(void *ptr){
  char userCh[10];
  char PassCh[12];
  textUser.getText(userCh, 10);
  TextPass.getText(PassCh, 12);
  Serial.print(userCh);
  user = userCh;
  Serial.print(PassCh);
  pass = PassCh;
}

void buttonOlvidarfunc(void *ptr){
  WifiOlvidar = "0";
}

void setup() {
 nexInit();
 Serial.begin(9600);           /* start serial for debug */
 pinMode(in1, OUTPUT);
 pinMode(in11, OUTPUT);
 digitalWrite(in1, HIGH);
 digitalWrite(in11, HIGH);
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 
 buttonP0Configuracion1.attachPush(buttonP0PagPrinConf1);
 buttonOlvidar.attachPush(buttonOlvidarfunc); 
}

void loop() {
  nexLoop(nex_listen_list);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    int c = Wire.read();      /* receive byte as a character */
    //Serial.print(c); 
     delay(1000);
    if(c != 0){
      //WifiOnOff(c);
    }
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  response = "";
  response += user + "/";
  response += pass + "/";
  response += WifiOlvidar+ "/";
  if(response.length() < MaxCharsEnviados){
    for(int i=response.length();i<MaxCharsEnviados;i++){
      response+="/"; 
    }
  }
  char resp[response.length()];
  response.toCharArray(resp,response.length()+1);
  Serial.println(resp);
  Wire.write(resp);  /*send string on request */
}


void calcularTempYHumedad(HumTemp DatV){
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);
  DatV.temp = t;
  DatV.hum = h;
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) /*|| isnan(f)*/) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  //float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);
}

void SetConfig(Configuracion vDat,int addres,int TempMaxS,int TempMinS,int HuMaxS,int HuMinS,int ThoraS,int TminS){
    int eeAddress = addres * sizeof(Configuracion);
    Serial.println( TempMaxS );
    Serial.println( TempMinS );
    Serial.println( HuMaxS );
    Serial.println( HuMinS );
    Serial.println( ThoraS );
    Serial.println( TminS );
    vDat.TempMax = TempMaxS;
    vDat.TempMin = TempMinS;
    vDat.HuMax = HuMaxS;
    vDat.HuMin = HuMinS;
    vDat.Thora = ThoraS;
    vDat.Tmin = TminS;
    EEPROM.put( eeAddress, vDat );   
}

Configuracion GetConfiguracion(int addres){
    Configuracion customVar;
    int eeAddress = addres * sizeof(Configuracion);
    EEPROM.get( eeAddress, customVar );  
    return customVar;
}
void inicializarConfig(Configuracion vDat){
    vDat.TempMax = 0;
    vDat.TempMin = 0;
    vDat.HuMax = 0;
    vDat.HuMin = 0;
    vDat.Thora = 0;
    vDat.Tmin = 0;
}

void senDataTanque(int numero){
      int maxPrcentaje = 192;// es el tamaño de la imagen hasta que llena el tanque en px
      int TamTankeCapacidad = 100; //CM
      int porcentajeMostrar = (numero * 100) / TamTankeCapacidad;
      int porcentajeMostrarImagen = (porcentajeMostrar * 100) / maxPrcentaje;
      Serial.print("page2.p4.h=");
      Serial.print(porcentajeMostrar);
      Serial.write(0xff); 
      Serial.print("page2.n0.val=");
      Serial.print(porcentajeMostrarImagen);
      Serial.write(0xff); 
}
void senDataValvula1(int onOff){
  if(onOff == 1){
    Valvula1 = "1";
    Serial.print("page2.p0.pic=12");
    Serial.write(0xff); 
  }else{
    Valvula1 = "0";
    Serial.print("page2.p0.pic=13");
    Serial.write(0xff); 
  }
}
void senDataValvula2(int onOff){
  if(onOff == 1){
    Valvula2 = "1";
    Serial.print("page2.p1.pic=12");
    Serial.write(0xff); 
  }else{
    Valvula2 = "0";
    Serial.print("page2.p1.pic=13");
    Serial.write(0xff); 
  }
}
void senDataValvula3(int onOff){
   if(onOff == 1){
    Valvula3 = "1";
    Serial.print("page2.p2.pic=12");
    Serial.write(0xff); 
  }else{
    Valvula3 = "0";
    Serial.print("page2.p2.pic=13");
    Serial.write(0xff); 
  }
}
void senDataFinalDeCarrera(int onOff){
   if(onOff == 1){
    Valvula3 = "1";
    Serial.print("page2.p5.pic=14");
    Serial.write(0xff); 
  }else{
    Valvula3 = "0";
    Serial.print("page2.p5.pic=15");
    Serial.write(0xff); 
  }
}

void SendHorasMinsSegs(){
  Serial.print("page2.n1.val=");
  Serial.print(Hora);
  Serial.write(0xff);
  Serial.print("page2.n2.val=");
  Serial.print(Minuto);
  Serial.write(0xff);
  Serial.print("page2.n3.val=");
  Serial.print(Segundo);
  Serial.write(0xff);
}

void WifiOnOff(int onOff){
  if(onOff != 0){
    Serial.print("page1.p1.pic=9");
    Serial.write(0xff);
  }else{
    Serial.print("page1.p1.pic=8");
    Serial.write(0xff);
  }
}
