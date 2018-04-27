#include <ESP8266WiFi.h>
#include <SimpleDHT.h>

#define WLAN_SSID  "XXXXXXXXX"
#define WLAN_PASS  "YYYYYYYYYY"

/* DHT SENSOR SETUP */
#define DHTPIN  2

SimpleDHT11 dht11;
// read without samples.
byte temperature = 0;
byte humidity = 0;
  
String data;
const char* server = "example.com"; // 
String uri = "/iot/proyecto/?";

String temp ,hum;
//Wait 5 minutes before sending data to web
int delayTime = 180000; // 3 minutos

WiFiClient client;
const int httpPort = 80;

void setup() {
    Serial.begin(115200);
    delay(10);
            
    // Connect to WiFi access point.
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);
    
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
  
    Serial.println("WiFi connected");
    Serial.println("IP address: "); 
    Serial.println(WiFi.localIP());

}

void loop () {
    
    //Serial.println("Iniciando loop.");

    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(DHTPIN, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); Serial.println(err);
      delay(1000);
      return;
    }

    Serial.print("Sample OK: ");
    Serial.print((int)temperature); Serial.print(" *C, "); 
    Serial.print((int)humidity); Serial.println(" H");
    //Serial.println();
    // convert the bit data to string form   
    hum = String(humidity);
    temp= String(temperature);
    data = "consulta=dht11&temp=" + temp + "&humedad=" + hum;
    // Postear datos
    httppost();
    delay(delayTime);
}

void httppost () {
    //Serial.println(data);

    if (!client.connect(server, httpPort)) {
        Serial.println("connection failed");
        return;
     }

     // This will send the request to the server
     String postRequest =
                  "GET " + uri + data+" HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" +
                  //"Connection: close\r\n\r\n" ;
                  "Accept: *" + "/" + "*\r\n" +
                  //"Content-Length: " + data.length() + "\r\n" +
                  //"Content-Type: application/x-www-form-urlencoded\r\n" +
                  "\r\n" ;
     Serial.println(postRequest);
     client.print(postRequest);
     
     unsigned long timeout = millis();
     
     while (client.available() == 0) {
         if (millis() - timeout > 5000) {
             Serial.println(">>> Client Timeout !");
             client.stop();
             return;
         }
     }

     while (client.available()) {
         //Serial.println(">>> Respuesta del servidor :");
         String line = client.readStringUntil('\r');
         Serial.print(line);
     }
    
     Serial.println();
     Serial.println("closing connection");

}
