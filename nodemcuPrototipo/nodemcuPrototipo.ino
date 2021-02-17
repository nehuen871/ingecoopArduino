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
    WiFi.begin(user, pass); 
    delay(3000);
    while (WiFi.status() != WL_CONNECTED)
    {
      
      delay(500);
      setWifiOnOff(0);
       Wire.requestFrom(8, 100); /* request & read data of size 13 from slave */
       String a = "";
       while(Wire.available()){
          char c = Wire.read();
          a += c;
       }
       user = getValue(a, '/', 0);
       pass = getValue(a, '/', 1);
       //pass.remove(11);
       Serial.println("User");
       Serial.println(user);
       Serial.println("Pass");
       Serial.println(pass);
       WiFi.begin(user, pass); //Conexión a la red
       delay(3000);
       server.begin(); //Iniciamos el servidor
       Serial.println(WiFi.localIP()); //Obtenemos la IP
       delay(3000);
     }
     server.begin();
     setWifiOnOff(1);
     delay(3000);
  }
    Wire.requestFrom(8, 100); /* request & read data of size 13 from slave */
    String ab = "";
    while(Wire.available()){
       char cc = Wire.read();
       ab += cc;
    }
    testC++;
    Serial.println(ab);
    //Pagina html  para en el navegador
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<script src='https://code.jquery.com/jquery-3.5.1.slim.js' integrity='sha256-DrT5NfxfbHvMHux31Lkhxg42LY6of8TaYyK50jnxRnM=' crossorigin='anonymous'></script>");
    client.println("<head><title>Naylam Mechatronics</title>");
    client.println("<body>");
    client.println("<h1 align='center'>");
    client.println(testC);
    client.println("</h1>");
    client.println("<h1 align='center'>Test ESP8266</h1>");
    client.println("<div style='text-align:center;'>");
    client.println("<br />");            
    client.println("<button onClick=location.href='./?LED=ON'>LED ON</button>");           
    client.println("<button onClick=location.href='./?LED=OFF'>LED OFF</button>");
    client.println("<br />");
    client.println("</div>");
    client.println("</body>");
    client.println("<script>$(document).ready(function() {setInterval(function() {cache_clear()}, 1000);});function cache_clear(){window.location.reload(true);}</script>");
    client.println("</html>");
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
