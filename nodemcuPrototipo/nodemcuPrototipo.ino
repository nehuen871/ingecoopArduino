#include <ESP8266WiFi.h>
#include <Wire.h>
// replace with your wifi ssid and wpa2 key
char *ssid = "";
char *password = "";
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

void loop() {
  
  WiFiClient client = server.available();
  if (client) //Si hay un cliente presente
  { 
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
     WiFi.begin(ssid, password); //Conexión a la red
     server.begin(); //Iniciamos el servidor
     Wire.requestFrom(8, 20); /* request & read data of size 13 from slave */
     String a = "";
     int flag = 0;
     while(Wire.available()){
        char c = Wire.read();
        a += c;
     }
          int ind1 = a.indexOf('/');
          String ssidS = a.substring(0, ind1);
          String passwordS = a.substring(ind1+1);
          ssidS.toCharArray(ssid, 10);
          passwordS.toCharArray(password, 10);

     Serial.println(a);
     Serial.println(ssid);
     Serial.println(password);
     delay(1000);
  }
}
