#include <ESP8266WiFi.h>

const char *ssid = "ARD8266";
const char *password = "12345678";

void setup() {
  Serial.begin(115200);

  // Conéctate al ESP8266 como un punto de acceso
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password); // Configura el AP con SSID y contraseña
  IPAddress apIP(192, 168, 1, 1); // Establece la dirección IP del AP
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  Serial.print("Dirección IP del Punto de Acceso: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Tu código aquí
}
