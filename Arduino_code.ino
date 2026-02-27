#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Master Edition";
const char* password = "";

WebServer server(80);

const int relay1 = 13;
const int relay2 = 12;

void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(relay1, HIGH); // OFF
  digitalWrite(relay2, HIGH); // OFF

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.enableCORS(true);

  server.on("/relay1on", []() {
    digitalWrite(relay1, LOW);
    server.send(200, "text/plain", "Relay1 ON");
  });

  server.on("/relay1off", []() {
    digitalWrite(relay1, HIGH);
    server.send(200, "text/plain", "Relay1 OFF");
  });

  server.on("/relay2on", []() {
    digitalWrite(relay2, LOW);
    server.send(200, "text/plain", "Relay2 ON");
  });

  server.on("/relay2off", []() {
    digitalWrite(relay2, HIGH);
    server.send(200, "text/plain", "Relay2 OFF");
  });

  server.on("/allon", []() {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    server.send(200, "text/plain", "All ON");
  });

  server.on("/alloff", []() {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    server.send(200, "text/plain", "All OFF");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
