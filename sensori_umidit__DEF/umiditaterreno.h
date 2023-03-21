
const int AirValue = 6900;   //replace the value with value when placed in air using calibration code
const int WaterValue = 3000;
int sensorPin = 12;

float soilMoistureValue = 0;
float soilmoisturepercent = 0;

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return ((x - in_min) * (out_max - out_min)) / ((in_max - in_min) + (out_min));
}


void loop_sensore() {
  soilMoistureValue = analogRead(sensorPin);
  Serial.print("Moisture Sensor Value:");
  Serial.println(soilMoistureValue);
  soilmoisturepercent = floatMap(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if (soilmoisturepercent >= 100)
  {
    Serial.println("100 %");
  }
  else if (soilmoisturepercent <= 0)
  {
    Serial.println("0 %");
  }
  else if (soilmoisturepercent > 0 && soilmoisturepercent < 100)
  {
    Serial.print(soilmoisturepercent);
    Serial.println("%");

  }
}
