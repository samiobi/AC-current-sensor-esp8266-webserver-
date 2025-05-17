#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <math.h>

const char* ssid = "XXXXXXXXXXX";
const char* password = "XXXXXXXXX";

ESP8266WebServer server(80);

const int sensorPin = A0;
const float voltageRMS = 230.0;    // Mains voltage
const float calibrationFactor = 1.0;

float currentRMS = 0.0;
float apparentPower = 0.0;

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Current & Power Monitor</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; background: #f0f0f0; }
    .gauge-container { display: inline-block; margin: 30px; }
    .gauge {
      width: 200px; height: 100px;
      background: conic-gradient(green 0% 50%, red 50% 100%);
      border-radius: 100px 100px 0 0 / 100px 100px 0 0;
      position: relative;
    }
    .needle {
      position: absolute; width: 4px; height: 90px;
      background: #ff6b6b; bottom: 0; left: 50%;
      transform-origin: bottom center;
      transform: rotate(0deg);
    }
    .gauge-label { font-size: 18px; font-weight: bold; margin-top: 10px; }
    .gauge-value { font-size: 16px; margin-top: 5px; }
  </style>
</head>
<body>
  <h1>Live Current and Power Monitor</h1>
  <div class="gauge-container">
    <div class="gauge" id="gaugePower"><div class="needle" id="needlePower"></div></div>
    <div class="gauge-label">Power</div>
    <div class="gauge-value"><span id="powerVal">0</span> W</div>
  </div>
  <div class="gauge-container">
    <div class="gauge" id="gaugeCurrent"><div class="needle" id="needleCurrent"></div></div>
    <div class="gauge-label">Current</div>
    <div class="gauge-value"><span id="currentVal">0</span> A</div>
  </div>

  <script>
    function updateGauges(current, power) {
      const powerMax = 1150;
      const currentMax = 5;
      const powerDeg = Math.min((power / powerMax) * 180, 180);
      const currentDeg = Math.min((current / currentMax) * 180, 180);
      document.getElementById('needlePower').style.transform = `rotate(${powerDeg}deg)`;
      document.getElementById('needleCurrent').style.transform = `rotate(${currentDeg}deg)`;
      document.getElementById('powerVal').innerText = power.toFixed(1);
      document.getElementById('currentVal').innerText = current.toFixed(2);
    }

    async function fetchData() {
      try {
        const res = await fetch('/data');
        const data = await res.json();
        updateGauges(data.current, data.power);
      } catch (e) {
        console.error(e);
      }
    }

    setInterval(fetchData, 1000); // Update every second
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleData() {
  // Sensor readings
  const int sampleCount = 1000;
  unsigned long sumOfSquares = 0;

  for (int i = 0; i < sampleCount; i++) {
    int raw = analogRead(sensorPin);
    int centered = raw - 18;
    sumOfSquares += (long)centered * centered;
    delayMicroseconds(200);
  }

  float rmsADC = sqrt(sumOfSquares / (float)sampleCount);
  float sensorVoltageRMS = (rmsADC * 1.0) / 1023.0;
  currentRMS = sensorVoltageRMS * calibrationFactor;
  apparentPower = voltageRMS * currentRMS;

  String json = "{";
  json += "\"current\":" + String(currentRMS, 3) + ",";
  json += "\"power\":" + String(apparentPower, 1);
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
  Serial.println("Server started");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
