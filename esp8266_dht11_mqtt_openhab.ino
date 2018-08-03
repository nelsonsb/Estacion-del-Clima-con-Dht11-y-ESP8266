#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SimpleDHT.h>

#define WLAN_SSID  "MY_SSID"
#define WLAN_PASS  "MY_PASSWORD"
  
/* DHT SENSOR SETUP */
#define DHTPIN  2

SimpleDHT11 dht11;

byte temperature = 0;
byte humidity = 0;
  
#define mqtt_server   "mqtt_ip_or_servername"
#define mqtt_user     "mqtt_user"
#define mqtt_password "mqtt_pwd"

#define humidity_topic "my/humidity/topic"
#define temperature_celsius_topic "my/temperature/topic"

String temp ,hum;
int delayTime = 60000; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    delay(10);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
        Serial.println("Attempting MQTT connection...");
    
      // Generate client name based on MAC address and last 8 bits of microsecond counter
      String clientName;  
      clientName += "myclientname";
      Serial.print("Connecting to ");
      Serial.print(mqtt_server);
      Serial.print(" as ");
      Serial.println(clientName);

    // Attempt to connect
    if (client.connect( (char*) clientName.c_str() , mqtt_user, mqtt_password) ) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
     
      delay(5000);
    }
  }
}

void loop () {

    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Wait a few seconds between measurements.
    delay(2000);
        
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(DHTPIN, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); Serial.println(err);
      delay(1000);
      return;
    }

    Serial.print("Sample OK : ");
    Serial.print((int)temperature); Serial.print(" *C, "); 
    Serial.print((int)humidity); Serial.println(" H");
    //Serial.println();
    // convert the bit data to string form   
    hum = String(humidity);
    temp= String(temperature);
    
    // Postear datos
    client.publish(temperature_celsius_topic, String(temperature).c_str(), true);
    client.publish(humidity_topic, String(humidity).c_str(), true);
    delay(delayTime);
}
