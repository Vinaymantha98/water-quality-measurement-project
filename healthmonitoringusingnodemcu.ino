 #include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//-------- Customise these values -----------

const char* ssid = "vishnu";
const char* password = "password";

SoftwareSerial m(D2,D3);
String url2; 
#define ORG "ymbknh"
#define DEVICE_TYPE "ESP8266"
#define DEVICE_ID "vishnu1"
#define TOKEN "ultimatestar"
//-------- Customise the above values --------
 
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char publishTopic[] = "iot-2/evt/Data/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
char topic[] = "iot-2/cmd/home/fmt/String";
 
WiFiClient wifiClient;
PubSubClient client(server, 1883,wifiClient);


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
 m.begin(9600);
 mqttConnect();
}

void loop() {
  // put your main code here, to run repeatedly:
if (m.find("#"))
{
  url2=m.readStringUntil('~');
  Serial.println(url2);
  //m.toInt(url2);
  //Serial.println(url2.toInt());
  delay(2000);
  Serial.print("\n");
  Serial.print("Sending payload: "); Serial.println(url2);
  if (client.publish(publishTopic, (char*) url2.c_str())) {
    Serial.println("Publish OK");
  } else {
    Serial.println("Publish FAILED");
  }
}
else{
  Serial.println("no data from arduino1");
}    
delay(2000);
}

 void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("nWiFi connected, IP address: "); Serial.println(WiFi.localIP());
}
void initManagedDevice() {
  if (client.subscribe(topic)) {
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}
void mqttConnect() {
  if (!client.connected()) {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}
