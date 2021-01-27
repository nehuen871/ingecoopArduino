#include <Nextion.h>
#include <EEPROM.h>
#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>

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
String ssid;
String password;
String response;
int number46 = 0;
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
NexButton buttonP0Configuracion1 = NexButton(0, 5, "b0");
NexText textUser = NexText(0, 1, "ssid");
NexText TextPass = NexText(0, 2, "passw");
char buffer[10] = {0};

NexTouch *nex_listen_list[] =
{
  &buttonP0Configuracion1,
  NULL
};

//Funcion guardar Wifi
void buttonP0PagPrinConf1(void *ptr){
  char userCh[10];
  char PassCh[10];
  textUser.getText(userCh, 10);
  TextPass.getText(PassCh, 10);
  //ssid = userCh;
  //password = PassCh;
  response = "";
  ssid = "Ingecoop";
  password = "1ng3c00p686";
  response = ssid + "/" + password;

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
}

void loop() {
  nexLoop(nex_listen_list);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    int c = Wire.read();      /* receive byte as a character */
    //Serial.print(c); 
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
  char resp[26];
  response.toCharArray(resp, 26);
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
