/*** Arduino Soil Moisture Sensor Project with LCD ***/
// Define to which pin of the Arduino the output of the Arduino Soil Moisture Sensor is connected:
int sensorPin = A0;
int sensorValue = 0; // variable to store the value coming from the sensor
#include<LiquidCrystal.h>
/* Create object named lcd of the class LiquidCrystal */
LiquidCrystal lcd(12,11,5,4,3,2); /* For 4-bit mode */
//LiquidCrystal lcd(8,9,10, 2, 3, 4, 5, 10,11,12,13); /* For 8-bit mode */
byte degree[8] =
{
0b00011,
0b00011,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};
void setup()
{
lcd.begin(16,2);
lcd.createChar(1, degree);
lcd.setCursor(2,0);
lcd.print("Arduino Point");
lcd.setCursor(2,1);
lcd.print("Soil Moisture");
delay(2000);
lcd.clear();
// Begin serial communication at a baud rate of 9600:
Serial.begin(9600);
}
void loop()
{
// Get a reading from the Moisture sensor:
  sensorValue = analogRead(sensorPin);
/*------Display Moisture Sensor Value in Serial Monitor------*/
 Serial.print("Moisture Sensor Value:");
 Serial.println(sensorValue);

 //Display the Moisture Percentage
 float moisturePercentage;
 //moisturePercentage = (sensorValue/876)*100;
 moisturePercentage = map(sensorValue,0,876,0,100);
 Serial.print("Moisture Percentage = ");
 Serial.print(moisturePercentage);
 Serial.print("%\n");
 
 //Display the plant need
 if(sensorValue < 300){
  Serial.println("I am thirsty, please give me water");
 }
 else if(sensorValue > 300 && sensorValue < 700){
  Serial.println("I feel so comfortable");
 }
 if(sensorValue > 700){
  Serial.println("Too much water, I might get hurt");
 }
 
Serial.print("\n");

/*------Display Moisture Sensor Value in LCD------*/
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Soil Moisture");

lcd.setCursor(0,1);
lcd.print(sensorValue);
lcd.setCursor(6,1);
lcd.print("&");
lcd.setCursor(8,1);
lcd.print(moisturePercentage);
lcd.print(" %");
delay(1000);
}