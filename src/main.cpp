#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ESP_SSID = "WiFi-Collector";
const char* ESP_PASSWORD = "Pracownia16";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>WiFi-Collector WebUI</title>
</head>
</body>
  <div>
    <h2>Available Networks</h2>
    <ul id="networks"></ul>
  </div>
  <script>
    async function fetchNetworks() {
      const response = await fetch('/scan');
      const networks = await response.json();
      const networksList = document.getElementById('networks');
      networksList.innerHTML = '';
      networks.forEach(network => {
        const li = document.createElement('li');
        li.textContent = `${network.ssid} (${network.rssi}) ${network.encryption}`;
        networksList.appendChild(li);
      });
    }

    setInterval(fetchNetworks, 5000);
    fetchNetworks();
  </script>
</html>
)rawliteral";

WebServer server(80);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  delay(100);

  // Connect to WiFi
  WiFi.softAP(ESP_SSID, ESP_PASSWORD);
  IPAddress local_IP(192, 168, 0, 1);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);

  Serial.printf("WiFi SSID: "); Serial.print(ESP_SSID); Serial.print(" WiFi Password: "); Serial.print(ESP_PASSWORD);
  Serial.printf("IP Address: "); Serial.print(WiFi.localIP());

  pinMode(2, OUTPUT);

  server.begin();

  Serial.println("Setup done");
}

void loop() {
  // WiFiClient client = server.available(); 

  server.on("/", []() {
    server.send_P(200, "text/html", index_html);
  });

  server.on("/scan", []() {
    int n = WiFi.scanNetworks();
    String json = "[";
    for (int i = 0; i < n; ++i) {
      if (i > 0) json += ",";
      json += "{";
      json += "\"ssid\":\"" + WiFi.SSID(i) + "\",";
      json += "\"rssi\":" + String(WiFi.RSSI(i)) + ",";
      json += "\"encryption\":\"" + String((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "open" : "secured") + "\"";
      json += "}";
    }
    json += "]";
    server.send(200, "application/json", json);
  });

  server.begin();

  // WiFi.scanNetworks will return the number of networks found
  digitalWrite(2, HIGH);
  int n = WiFi.scanNetworks();
  digitalWrite(2, LOW);
  
  // Check if networks were found and list them
  if (n == 0) {
      Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}