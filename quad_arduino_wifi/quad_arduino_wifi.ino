// 安装 esp32 by Espressif Systems 开发板
// 安装 ESP32Servo (by Kevin) 库
//
//  --------                       --------
// | 2      |                     | 3      |
// | FLL    |                     | FRL    |
//  -------- --------    --------  --------
//          | 0      |  | 1      |
//          | FLH    |  | FRH    |
//           --------    --------
//          | 4      |  | 5      |
//          | BLH    |  | BRH    |
//  -------- --------    --------  --------
// | 6      |                     | 7      |
// | BLL    |                     | BRL    |
//  --------                       --------

#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTP_Method.h>
#include "Quad.h"


const char *ssid = "Yi";
const char *password = "88889999";
IPAddress staticIP(192, 168, 3, 183); // 设置静态 IP 地址
IPAddress gateway(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);

const char* serverIndex = "<!DOCTYPE html>"
"<!DOCTYPE html>"
"<html>"
"<head>"
"    <meta charset='utf-8'>"
"    <title>Otto</title>"
"    <style>"
"        body {"
"            margin: 0;"
"            padding: 0;"
"            display: flex;"
"            justify-content: center;"
"            align-items: center;"
"            /*height: 90vh;*/"
"            /*flex-direction: row;*/"
"            /*flex-direction: column;*/"
"            /*overflow: scroll;*/"
"        }"
"        .container {"
"            display: flex;"
"            flex-wrap: wrap;"
"            justify-content: center;"
"            align-items: center;"
"            max-width: 100%;"
"            padding: 50px;"
"        }"
"        .left {"
"            display: flex;"
"            flex-direction: column;"
"            justify-content: center;"
"            align-items: center;"
"            max-width: 100%;"
"            margin: 30px;"
"        }"
"        .right {"
"            display: grid;"
"            grid-template-columns: repeat(3, 1fr);"
"            /* grid-template-rows: repeat(3, 1fr); */"
"            gap: 5px;"
"            margin: 30px;"
"        }"
"        .top-row {"
"            display: flex;"
"            justify-content: center;"
"            align-items: center;"
"        }"
"        .middle-row {"
"            display: flex;"
"            justify-content: space-between;"
"            align-items: center;"
"            width: 100%;"
"            margin-top: 10px;"
"            margin-bottom: 10px;"
"        }"
"        .bottom-row {"
"            display: flex;"
"            justify-content: center;"
"            align-items: center;"
"        }"
"        .button {"
"            background-color: #f0f0f0;"
"            border: 1px solid #ccc;"
"            margin: 5px;"
"            display: flex;"
"            justify-content: center;"
"            align-items: center;"
"            border-radius: 10px;"
"            cursor: pointer;"
"        }"
"        .left .button {"
"            width: 150px;"
"            height: 150px;"
"            font-size: 60px;"
"        }"
"        .right .button {"
"            width: 220px;"
"            height: 100px;"
"            font-size: 26px;"
"        }"
"    </style>"
"</head>"
"<body>"
"    <div class='container'>"
"        <div class='left'>"
"            <div class='button' onclick=\"fetch('/control?command=walk')\">▴</div>"
"            <div class='middle-row'>"
"                <div class='button' onclick=\"fetch('/control?command=turnL')\">◂</div>"
"                <div class='button' onclick=\"fetch('/control?command=home')\">●</div>"
"                <div class='button' onclick=\"fetch('/control?command=turnR')\">▸</div>"
"            </div>"
"            <div class='button' onclick=\"fetch('/control?command=backward')\">▾</div>"
"        </div>"
"        <div class='right'>"
"            <div class='button' onclick=\"fetch('/control?command=zero')\">Zero</div>"
"            <div class='button' onclick=\"fetch('/control?command=hello')\">Hello</div>"
"            <div class='button' onclick=\"fetch('/control?command=omniWalk')\">OmniWalk</div>"
"            <div class='button' onclick=\"fetch('/control?command=run')\">Run</div>"
"            <div class='button' onclick=\"fetch('/control?command=moonwalkL')\">Moonwalk</div>"
"            <div class='button' onclick=\"fetch('/control?command=dance')\">Dance</div>"
"            <div class='button' onclick=\"fetch('/control?command=upDown')\">UpDown</div>"
"            <div class='button' onclick=\"fetch('/control?command=pushUp')\">PushUp</div>"
"            <div class='button' onclick=\"fetch('/control?command=frontBack')\">FrontBack</div>"
"            <div class='button' onclick=\"fetch('/control?command=waveHand')\">WaveHand</div>"
"            <div class='button' onclick=\"fetch('/control?command=hide')\">Hide</div>"
"            <div class='button' onclick=\"fetch('/control?command=scared')\">Scared</div>"
"        </div>"
"    </div>"
"</body>"
"</html>";


WebServer server(80);

Quad robot;
int ledPin = 2;

void handleRoot() {
  server.send(200, "text/html", serverIndex);
}

void handleCommand() {
  if (server.method() == HTTP_GET) {
    String command = server.arg("command");
    if (command == "home") {robot.home();}
    else if (command == "zero") {robot.zero();}
    else if (command == "hello") {robot.hello();}
    else if (command == "walk") {robot.walk(1, 4, 1000);}
    else if (command == "backward") {robot.walk(0, 4, 1000);}
    else if (command == "omniWalk") {robot.omniWalk();}
    else if (command == "run") {robot.run();}
    else if (command == "turnL") {robot.turnL();}
    else if (command == "turnR") {robot.turnR();}
    else if (command == "moonwalkL") {robot.moonwalkL();}
    else if (command == "dance") {robot.dance();}
    else if (command == "upDown") {robot.upDown();}
    else if (command == "pushUp") {robot.pushUp();}
    else if (command == "frontBack") {robot.frontBack();}
    else if (command == "waveHand") {robot.waveHand();}
    else if (command == "hide") {robot.hide();}
    else if (command == "scared") {robot.scared();}
    else {Serial.println("Command '" + command + "' not find!");};
  }
  server.send(200);
}

void setup(void) {

  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/control", handleCommand);
  server.begin();
  Serial.println("HTTP server started");


  delay(10);
  robot.init(
    12, 16, 25, 18, 13, 17, 26, 19,  // set servo pins
    0, 0, 0, 0, 0, 0, 0, 0           // set servo trims
  );
  robot.home();
 
}

void loop() {
  server.handleClient();
  analogWrite(ledPin, 128);
  delay(500);
}
