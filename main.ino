#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wifi.h>
#include <WebServer.h>
#include "limits.h"
#include "legs.h"

Spider *spider;
Leg *front_left, *front_right, *rear_left, *rear_right;

WebServer server(80);
void on_home() {
    server.send(200, "application/json", "{\"status\":\"ok\"}");
}
void on_rotate() {
    if (server.hasArg("leg") && server.hasArg("joint") && server.hasArg("angle")) {
        if (server.arg("leg") == "front_left") {
            if (server.arg("joint") == "hip") {
                front_left->hip->rotate(server.arg("angle").toInt());
            } else if (server.arg("joint") == "knee") {
                front_left->knee->rotate(server.arg("angle").toInt());
            } else if (server.arg("joint") == "ankle") {
                front_left->ankle->rotate(server.arg("angle").toInt());
            }
        } else if (server.arg("leg") == "front_right") {
            if (server.arg("joint") == "hip") {
                front_right->hip->rotate(server.arg("angle").toInt());
            } else if (server.arg("joint") == "knee") {
                front_right->knee->rotate(server.arg("angle").toInt());
            } else if (server.arg("joint") == "ankle") {
                front_right->ankle->rotate(server.arg("angle").toInt());
            }
        } else if (server.arg("leg") == "rear_left") {
            if (server.arg("joint") == "hip") {
                rear_left->hip->rotate(server.arg("angle").toInt());
            } else if (server.arg("joint") == "knee") {
                rear_left->knee->rotate(server.arg("angle").toInt());
            } else if (server.arg("joint") == "ankle") {
                rear_left->ankle->rotate(server.arg("angle").toInt());
            }
        } else if (server.arg("leg") == "rear_right") {
            if (server.arg("joint") == "hip") {
                rear_right->hip->rotate(server.arg("angle").toInt());
            } else if (server.arg("joint") == "knee") {
                rear_right->knee->rotate(server.arg("angle").toInt());
            } else if (server.arg("joint") == "ankle") {
                rear_right->ankle->rotate(server.arg("angle").toInt());
            }
        }
    }
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    WiFi.softAP("Spider");
    server.on("/", on_home);
    server.on("/rotate", on_rotate);
    server.begin();

    front_left = new Leg(
        new Joint(23, FL_HIP_MIN, FL_HIP_MAX, 0), // hip
        new Joint(22, FL_KNEE_MIN, FL_KNEE_MAX, 0), // knee
        new Joint(21, FL_ANKLE_MIN, FL_ANKLE_MAX, 0) // ankle
    );
    front_right = new Leg(
        new Joint(12, FR_HIP_MIN, FR_HIP_MAX, -180), // hip
        new Joint(14, FR_KNEE_MIN, FR_KNEE_MAX, 0), // knee
        new Joint(27, FR_ANKLE_MIN, FR_ANKLE_MAX, 0) // ankle
    );
    rear_left = new Leg(
        new Joint(19, RL_HIP_MIN, RL_HIP_MAX, 0), // hip
        new Joint(18, RL_KNEE_MIN, RL_KNEE_MAX, 0), // knee
        new Joint(5, RL_ANKLE_MIN, RL_ANKLE_MAX, 0) // ankle
    );
    rear_right = new Leg(
        new Joint(33, RR_HIP_MIN, RR_HIP_MAX, -180), // hip
        new Joint(25, RR_KNEE_MIN, RR_KNEE_MAX, 0), // knee
        new Joint(26, RR_ANKLE_MIN, RR_ANKLE_MAX, 0) // ankle
    );

    spider = new Spider(front_left, front_right, rear_left, rear_right);


}

void loop() {
    String command = "";
}
