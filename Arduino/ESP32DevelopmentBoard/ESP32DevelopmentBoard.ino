#define tombolMerah 2
#define tombolKuning 18
#define tombolHijau 21
#define tombolBiru 23
#define tombolPutih 16

#include <WiFi.h>
#include <MQTT.h>
#include <NusabotSimpleTimer.h>

const char ssid[] = "Galaxy";
const char pass[] = "makanmie";

WiFiClient net;
MQTTClient client;
NusabotSimpleTimer timer;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("diva")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
}

void publish() {
  bool statusMerah  = digitalRead(tombolMerah);
  bool statusKuning = digitalRead(tombolKuning);
  bool statusHijau  = digitalRead(tombolHijau);
  bool statusBiru   = digitalRead(tombolBiru);
  bool statusPutih  = digitalRead(tombolPutih);

  Serial.println(statusMerah);
  Serial.println(statusKuning);
  Serial.println(statusHijau);
  Serial.println(statusBiru);
  Serial.println(statusPutih);

  if(statusMerah == 1){
    client.publish("diva/Merah", "1");
  }

  if(statusKuning == 1){
    client.publish("diva/Kuning", "1");

  }

  if(statusHijau == 1){
    client.publish("diva/Hijau", "1");
   
  }

  if(statusBiru == 1){
    client.publish("diva/Biru", "1");
    
  }

   if(statusPutih == 1){
    client.publish("diva/Putih", "1");
  
  }
  
}

void setup() {
  pinMode(tombolMerah, INPUT);
  pinMode(tombolKuning, INPUT);
  pinMode(tombolHijau, INPUT);
  pinMode(tombolBiru, INPUT);
  pinMode(tombolPutih, INPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  client.begin("broker.emqx.io", net);
  timer.setInterval(1000, publish);

  connect();
}

void loop() {
  client.loop();
  timer.run();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
}
