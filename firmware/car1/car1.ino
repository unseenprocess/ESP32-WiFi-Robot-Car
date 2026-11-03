#include <WiFi.h>
#include <WebServer.h>

// =================================
// MOTOR PIN CONFIGURATION
// =================================

#define IN1 26
#define IN2 27
#define IN3 18
#define IN4 19

// =================================
// WIFI CONFIGURATION
// =================================

const char* ssid = "ESP32_Car_2";
const char* password = "123456789";

WebServer server(80);

// =================================
// SAFETY TIMEOUT
// =================================

unsigned long lastCommandTime = 0;
const unsigned long safetyTimeout = 1000;

bool motorsRunning = false;

// =================================
// MOTOR FUNCTIONS
// =================================

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  motorsRunning = false;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  motorsRunning = true;
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  motorsRunning = true;
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  motorsRunning = true;
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  motorsRunning = true;
}

// =================================
// WEB COMMAND HANDLER
// =================================

void handleCommand() {

  if (!server.hasArg("d")) {
    stopMotors();
    server.send(400, "text/plain", "Missing command");
    return;
  }

  String direction = server.arg("d");

  if (direction == "F") {
    moveForward();
  }
  else if (direction == "B") {
    moveBackward();
  }
  else if (direction == "L") {
    turnLeft();
  }
  else if (direction == "R") {
    turnRight();
  }
  else if (direction == "S") {
    stopMotors();
  }
  else {
    stopMotors();
    server.send(400, "text/plain", "Invalid command");
    return;
  }

  lastCommandTime = millis();

  server.send(200, "text/plain", "OK");
}

// =================================
// CONTROL WEBPAGE
// =================================

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

<meta name="viewport"
content="width=device-width, initial-scale=1">

<title>ESP32 Robot Car</title>

<style>

body {
  background: #151923;
  color: white;
  font-family: Arial, sans-serif;
  text-align: center;
  margin: 0;
  padding: 20px;
  user-select: none;
}

h2 {
  margin-top: 25px;
}

p {
  color: #aab2c0;
}

.controls {
  display: grid;
  grid-template-columns: 90px 90px 90px;
  gap: 14px;
  justify-content: center;
  margin-top: 45px;
}

button {
  height: 85px;
  border: none;
  border-radius: 18px;
  color: white;
  font-size: 16px;
  font-weight: bold;
  touch-action: none;
  user-select: none;
}

button:active {
  opacity: 0.7;
  transform: scale(0.95);
}

.move {
  background: #247c54;
}

.turn {
  background: #3268a8;
}

.stop {
  background: #c03939;
}

.empty {
  visibility: hidden;
}

</style>

</head>

<body>

<h2>ESP32 Robot Car</h2>

<p>Press and hold a direction to move</p>

<div class="controls">

  <button class="empty"></button>

  <button class="move" data-dir="F">
    ▲<br>Forward
  </button>

  <button class="empty"></button>

  <button class="turn" data-dir="L">
    ◀<br>Left
  </button>

  <button class="stop" data-dir="S">
    ■<br>STOP
  </button>

  <button class="turn" data-dir="R">
    ▶<br>Right
  </button>

  <button class="empty"></button>

  <button class="move" data-dir="B">
    ▼<br>Backward
  </button>

  <button class="empty"></button>

</div>

<script>

// Keep HTTP commands in order
let requestQueue = Promise.resolve();

function sendCommand(direction) {

  requestQueue = requestQueue
    .then(() => fetch('/cmd?d=' + direction))
    .catch(error => {
      console.log("Command error:", error);
    });

}

let activeTimer = null;

function stopCar() {

  if (activeTimer !== null) {
    clearInterval(activeTimer);
    activeTimer = null;
  }

  sendCommand('S');
}

document.querySelectorAll('button[data-dir]')
.forEach(button => {

  button.addEventListener('pointerdown', event => {

    event.preventDefault();

    if (activeTimer !== null) {
      clearInterval(activeTimer);
      activeTimer = null;
    }

    button.setPointerCapture(event.pointerId);

    const direction = button.dataset.dir;

    if (direction === 'S') {
      sendCommand('S');
      return;
    }

    sendCommand(direction);

    activeTimer = setInterval(() => {
      sendCommand(direction);
    }, 250);

  });

  button.addEventListener('pointerup', stopCar);

  button.addEventListener('pointercancel', stopCar);

  button.addEventListener('lostpointercapture', stopCar);

  button.addEventListener('contextmenu', event => {
    event.preventDefault();
  });

});

window.addEventListener('blur', stopCar);

document.addEventListener('visibilitychange', () => {
  if (document.hidden) {
    stopCar();
  }
});

</script>

</body>
</html>
)rawliteral";

// =================================
// SETUP
// =================================

void setup() {

  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  WiFi.mode(WIFI_AP);

  bool wifiStarted = WiFi.softAP(ssid, password);

  if (!wifiStarted) {
    Serial.println("WiFi startup failed!");
    return;
  }

  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", webpage);
  });

  server.on("/cmd", HTTP_GET, handleCommand);

  server.onNotFound([]() {
    server.send(404, "text/plain", "Not found");
  });

  server.begin();

  Serial.println();
  Serial.println("Robot car controller ready!");

  Serial.print("WiFi network: ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

}

// =================================
// MAIN LOOP
// =================================

void loop() {

  server.handleClient();

  if (motorsRunning &&
      millis() - lastCommandTime > safetyTimeout) {

    stopMotors();

  }

}
