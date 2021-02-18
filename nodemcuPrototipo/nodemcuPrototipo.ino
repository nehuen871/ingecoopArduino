#include <ESP8266WiFi.h>
#include <Wire.h>
// replace with your wifi ssid and wpa2 key
char *ssid = "";
char *password = "";
WiFiServer server(80);
int testC = 0;
void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

void loop() {
  
  WiFiClient client = server.available();
  if (client) //Si hay un cliente presente
  {
    setWifiOnOff(1); 
    //esperamos hasta que hayan datos disponibles
    client.flush(); 

  }else{
    String user;
    String pass;
    delay(1000);
    while (WiFi.status() != WL_CONNECTED)
    {
       WiFi.begin(user, pass); 
       delay(3000);
       setWifiOnOff(0);
       Wire.requestFrom(8, 50); /* request & read data of size 13 from slave */
       String a = "";
       while(Wire.available()){
          char c = Wire.read();
          a += c;
       }
       Serial.println("resp");
       Serial.println(a);
       user = getValue(a, '/', 0);
       pass = getValue(a, '/', 1);
       //pass.remove(11);
       Serial.println("User");
       Serial.println(user);
       Serial.println("Pass");
       Serial.println(pass);
       delay(3000);
       WiFi.begin(user, pass); //Conexión a la red
       server.begin(); //Iniciamos el servidor
       Serial.println(WiFi.localIP()); //Obtenemos la IP
       delay(3000);
     }
     setWifiOnOff(1);
     server.begin();
     Serial.println(WiFi.localIP());
  }
    Wire.requestFrom(8, 50); /* request & read data of size 13 from slave */
    String ab = "";
    while(Wire.available()){
       char cc = Wire.read();
       ab += cc;
    }
    String hora = getValue(ab, '/', 0);
    String mins = getValue(ab, '/', 1);
    String seg = getValue(ab, '/', 2);
    String porCent = getValue(ab, '/', 3);
    String valv2 = getValue(ab, '/', 4);
    String valv1 = getValue(ab, '/', 5);
    String valv0 = getValue(ab, '/', 6);
    String finalCarrera = getValue(ab, '/', 7);
    String valv2S;
    String valv1S;
    String valv0S;
    String finalCarreraS;
    int pocentajeInt = porCent.toInt();
    //Pagina html  para en el navegador
    if(valv2.toInt() == 0){
      valv2S = "red";
    }else{
      valv2S = "green";
    }
    if(valv1.toInt() == 0){
      valv1S = "red";
    }else{
      valv1S = "green";
    }
    if(valv0.toInt() == 0){
      valv0S = "red";
    }else{
      valv0S = "green";
    }
    if(finalCarrera.toInt() == 0){
      finalCarreraS = "red";
    }else{
      finalCarreraS = "green";
    }
    client.println("<!DOCTYPE html><html><head><style>.rectanguloNegro{width: 0;         height: 0;        border-top: 250px solid black;        border-right:50px solid black;        border-bottom:00px solid black;        border-left:50px solid black;        position: relative;        top: -250px;    }.rectanguloRojo{width: 0;         height: 0;        border-top: 250px solid red;        border-right:50px solid red;        border-bottom:00px solid red;        border-left:50px solid red;}.circulo{position: relative; height: 30px; width: 30px; background-color: green;border-radius: 30px;}.triangleTop{width: 0; height: 0;border-top: 1px solid black;border-right:20px solid white;border-bottom:20px solid orange;border-left:20px solid white;}.triangleRight{width: 0;height: 0;border-top: 20px solid white;border-right: 0px solid white;border-bottom: 20px solid white;border-left: 20px solid orange;}.triangleLeft {width: 0;height: 0;border-top: 20px solid white;border-right: 20px solid orange;border-bottom: 20px solid white;border-left: 0px solid white;}.triangleButton{width: 0; height: 0;border-top: 20px solid orange;border-right:20px solid white;border-bottom:0px solid white;border-left:20px solid white;}.valvula3{display: inline-block;position: relative;top: 70px;}.valvula2{display: inline-block;position: relative;left: 300px;}.valvula1{display: inline-block;position: relative;left: 90px;}.finaldecarrera{display: inline-block;position: relative;left: 60px;top: 120px;}.tanque{position: relative;left: 185px;top: 140px;}.container{width: 800px;height: 600px;}.linaeCanvas{position: absolute;}.tiempo{position: absolute;top: 140px;left: 440px;}.dataTanque{display: inline;position: relative;top: -236px;}</style><title>Page Title</title><script src='https://code.jquery.com/jquery-3.5.1.slim.js' integrity='sha256-DrT5NfxfbHvMHux31Lkhxg42LY6of8TaYyK50jnxRnM=' crossorigin='anonymous'></script></head><body><div><h1>Ingecoop</h1></div><div class='container'><canvas id='linea' class='linaeCanvas'></canvas><div class='valvula1'><div class='triangleButton' style='border-top: 20px solid "+valv0S+";'></div><div class='triangleTop' style='border-bottom:20px solid "+valv0S+";'></div></div><div class='valvula2'><div class='triangleButton' style='border-top: 20px solid "+valv1S+";'></div><div class='triangleTop' style='border-bottom:20px solid "+valv1S+";'></div></div><div class='valvula3'><div class='triangleButton' style='border-top: 20px solid "+valv2S+";'></div><div class='triangleTop' style='border-bottom:20px solid "+valv2S+";'></div></div><div class='finaldecarrera'><div class='circulo' style='background-color: "+finalCarreraS+"'></div></div><div class='tanque'><div class='tanqueLleno rectanguloRojo'></div><div class='tanqueVacio rectanguloNegro'></div><div class='dataTanque'><span>%"+pocentajeInt+"</span></div></div><div class='tiempo'><span>"+hora+":"+mins+":"+seg+"</span></div></div></body><script>var canvas = document.getElementById('linea');var ctx = canvas.getContext('2d');canvas.width  = 800;canvas.height = 600;canvas.fillStyle = '#000';ctx.fillRect(0, 20, 500, 1);ctx.fillRect(0, 90, 206, 1);ctx.fillRect(206, 20, 1, 200);</script></html><script>$(document).ready(function() {setInterval(function() {cache_clear()}, 1000);});function cache_clear(){window.location.reload(true);}</script>");
}


 String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setWifiOnOff(int a){
  Wire.beginTransmission(8); /* begin with device address 8 */
  if(a == 1){
    Wire.write(1);  /* sends hello string */
  }else{
    Wire.write(0);  /* sends hello string */
  }
  Wire.endTransmission(); 
}
