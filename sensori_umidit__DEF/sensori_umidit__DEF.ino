String myName = "pippo";

#include "_wifi.h"
#include "_mqtt.h"
#include "umiditaterreno.h"

int SENSOR_TIME = 5000;

void setup() {

  Serial.begin(115200);
  setup_wifi();

  randomSeed(micros());
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(mqttReceive);


}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastMsg > SENSOR_TIME) {
    lastMsg = now;
    loop_sensore();

    DynamicJsonDocument doc(1024);
    doc["umidità"] = soilMoistureValue;
    doc["percentuale"] = soilmoisturepercent;
    String mqttPayload = "";
    serializeJson(doc, mqttPayload);

    Serial.println("Publish message: " + mqttTopicPubish_sensor + " " + mqttPayload);
    mqttClient.publish(mqttTopicPubish_sensor.c_str(), mqttPayload.c_str());
  }



}
