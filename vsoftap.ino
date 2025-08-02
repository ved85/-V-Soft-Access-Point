#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const char* ssid = "VESP";
const char* password = "12345678";

IPAddress local_IP(192, 168, 1, 1);         // ESP32 IP
IPAddress gateway(192, 168, 1, 1);          // Gateway
IPAddress subnet(255, 255, 255, 0);         // Subnet

const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Configure the AP
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  delay(100);

  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Start DNS server to redirect all domains to ESP32
  dnsServer.start(DNS_PORT, "*", local_IP);

  // Handle root page
  server.on("/", handleRoot);
  server.onNotFound(handleRoot); // Redirect unknown paths

  server.begin();
  Serial.println("HTTP server started");

  // Print connected station MACs every 10 seconds
  xTaskCreatePinnedToCore(printConnectedStations, "Stations", 4096, NULL, 1, NULL, 1);
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 Captive Portal</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{font-family:sans-serif;text-align:center;margin-top:50px;}button{padding:10px 20px;}</style>";
  html += "</head><body><h1>Welcome to ESP32</h1>";
  html += "<p>You are connected to the SoftAP captive portal.</p>";
  html += "<button onclick=\"alert('Button Clicked')\">Click Me</button>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void printConnectedStations(void *parameter) {
  while (true) {
    Serial.println("Connected Stations:");
    wifi_sta_list_t stationList;
    tcpip_adapter_sta_list_t adapterList;

    if (esp_wifi_ap_get_sta_list(&stationList) == ESP_OK) {
      if (tcpip_adapter_get_sta_list(&stationList, &adapterList) == ESP_OK) {
        for (int i = 0; i < adapterList.num; i++) {
          tcpip_adapter_sta_info_t station = adapterList.sta[i];
          Serial.printf("  - MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                        station.mac[0], station.mac[1], station.mac[2],
                        station.mac[3], station.mac[4], station.mac[5]);
        }
      }
    }

    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}
