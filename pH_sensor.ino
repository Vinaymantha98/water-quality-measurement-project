#include <ESP8266WiFi.h> 
#define SensorPin 0             //pH meter Analog output to Arduino1 Analog Input 0
#define Offset 0.00            //deviation compensate
unsigned long int avgValue;     //Store the average value of the sensor feedback
void setup()
{
  Serial.begin(9600);  
  Serial.println("Ready");    //Test the serial monitor
}
void loop()
{
  
  Serial.print("Raw analog:");
  Serial.print(analogRead(SensorPin));
  Serial.println(" ");
  float phValue=(float)analogRead(SensorPin)*5.0/1024; //convert the analog into millivolt
  Serial.print("Volt:");
  Serial.print(phValue);
  Serial.println(" ");
  phValue=3.5*phValue+Offset;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  delay(1000);
}
