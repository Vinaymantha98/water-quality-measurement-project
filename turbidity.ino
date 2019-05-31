 #include <ESP8266WiFi.h> //Set to A0 as Analog Read
void setup() {
  Serial.begin(9600);

  

}
void loop() {
  int sensorValue = digitalRead(D0);
  float voltage = sensorValue * (5.0 / 1024.0);

  Serial.println ("Sensor Output (V):");
  Serial.println (voltage);
  Serial.println();
  delay(1000);
}
