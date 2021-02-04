#include <ESP8266WiFi.h>
#include <Wire.h>
// replace with your wifi ssid and wpa2 key
char *ssid = "";
char *password = "";
WiFiServer server(80);

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
    Wire.requestFrom(8, 24); /* request & read data of size 13 from slave */
    String a = "";
    while(Wire.available()){
      char c = Wire.read();
      a += c;
    }
    Serial.println("Nuevo Cliente");
    
    //esperamos hasta que hayan datos disponibles
    while(!client.available()&&client.connected())
    {
    delay(1);
    }
    
    // Leemos la primera línea de la petición del cliente.
    String linea1 = client.readStringUntil('r');
    Serial.println(linea1);

    if (linea1.indexOf("LED=ON")>0) //Buscamos un LED=ON en la 1°Linea
    {
       Wire.beginTransmission(8); /* begin with device address 8 */
       Wire.write(1);  /* sends hello string */
       Wire.endTransmission();    /* stop transmitting */
       Serial.println();
      digitalWrite(2,HIGH);
    }
    if (linea1.indexOf("LED=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
       Wire.beginTransmission(8); /* begin with device address 8 */
       Wire.write(0);  /* sends hello string */
       Wire.endTransmission();    /* stop transmitting */
       Serial.println();
      digitalWrite(2,LOW);
    }
    
    client.flush(); 
                
    Serial.println("Enviando respuesta...");   
    //Encabesado http    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");// La conexión se cierra después de finalizar de la respuesta
    client.println();
    //Pagina html  para en el navegador
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><title>Naylam Mechatronics</title>");
    client.println("<body>");
    client.println("<h1 align='center'>Test ESP8266</h1>");
    client.println("<div style='text-align:center;'>");
    client.println("<br />");            
    client.println("<button onClick=location.href='./?LED=ON'>LED ON</button>");           
    client.println("<button onClick=location.href='./?LED=OFF'>LED OFF</button>");
    client.println("<br />");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    
    delay(1);
    Serial.println("respuesta enviada");
    Serial.println();

  }else{
    int i=0;
    String user;
    String pass;
    WiFi.begin(user, pass); 
    delay(3000);
    while (WiFi.status() != WL_CONNECTED)
    {
      i++;
      if(i>5){
        i=0;
      }
      Wire.beginTransmission(8); /* begin with device address 8 */
      Wire.write(i);  /* sends hello string */
      Wire.endTransmission();    /* stop transmitting */
      Serial.println();
      delay(500);
      Wire.requestFrom(8, 24); /* request & read data of size 13 from slave */
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
     Wire.beginTransmission(8); /* begin with device address 8 */
     Wire.write(0);  /* sends hello string */
     Wire.endTransmission();    /* stop transmitting */
     Serial.println();
     server.begin();
     delay(3000);
  }
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
