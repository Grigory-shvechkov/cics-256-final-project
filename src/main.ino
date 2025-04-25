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
        if (server.arg("leg") == "fl") {
            if (server.arg("joint") == "hip") {
                front_left->rotateHip(server.arg("angle").toInt());
            } else if (server.arg("joint") == "knee") {
                front_left->rotateKnee(server.arg("angle").toInt());
            } else if (server.arg("joint") == "ankle") {
                front_left->rotateAnkle(server.arg("angle").toInt());
            }
            front_left->move();
        } else if (server.arg("leg") == "fr") {
            if (server.arg("joint") == "hip") {
                front_right->rotateHip(server.arg("angle").toInt());
            } else if (server.arg("joint") == "knee") {
                front_right->rotateKnee(server.arg("angle").toInt());
            } else if (server.arg("joint") == "ankle") {
                front_right->rotateAnkle(server.arg("angle").toInt());
            }
            front_right->move();
        } else if (server.arg("leg") == "rl") {
            if (server.arg("joint") == "hip") {
                rear_left->rotateHip(server.arg("angle").toInt());
            } else if (server.arg("joint") == "knee") {
                rear_left->rotateKnee(server.arg("angle").toInt());
            } else if (server.arg("joint") == "ankle") {
                rear_left->rotateAnkle(server.arg("angle").toInt());
            }
            rear_left->move();
        } else if (server.arg("leg") == "rr") {
            if (server.arg("joint") == "hip") {
                rear_right->rotateHip(server.arg("angle").toInt());
            } else if (server.arg("joint") == "knee") {
                rear_right->rotateKnee(server.arg("angle").toInt());
            } else if (server.arg("joint") == "ankle") {
                rear_right->rotateAnkle(server.arg("angle").toInt());
            }
            rear_right->move();
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
        new Joint(23, FL_HIP_MIN, FL_HIP_MAX, 0, false), // hip
        new Joint(22, FL_KNEE_MIN, FL_KNEE_MAX, 180, true), // knee
        new Joint(21, FL_ANKLE_MIN, FL_ANKLE_MAX, 0, false) // ankle
    );
    front_right = new Leg(
        new Joint(12, FR_HIP_MIN, FR_HIP_MAX, -180, false), // hip
        new Joint(14, FR_KNEE_MIN, FR_KNEE_MAX, 360, true), // knee
        new Joint(27, FR_ANKLE_MIN, FR_ANKLE_MAX, 0, false) // ankle
    );
    rear_left = new Leg(
        new Joint(19, RL_HIP_MIN, RL_HIP_MAX, 0, false), // hip
        new Joint(18, RL_KNEE_MIN, RL_KNEE_MAX, 0, false), // knee
        new Joint(5, RL_ANKLE_MIN, RL_ANKLE_MAX, 0, false) // ankle
    );
    rear_right = new Leg(
        new Joint(33, RR_HIP_MIN, RR_HIP_MAX, -180, false), // hip
        new Joint(25, RR_KNEE_MIN, RR_KNEE_MAX, -180, false), // knee
        new Joint(26, RR_ANKLE_MIN, RR_ANKLE_MAX, 0, false) // ankle
    );

    spider = new Spider(front_left, front_right, rear_left, rear_right);
}

void loop() {
    // spider->front_left->rotateHip(90)->move();
    // delay(500);

    // spider->front_right->rotateHip(270)->move();
    // delay(500);

    // spider->rear_right->rotateHip(270)->move();
    // delay(500);

    // spider->rear_left->rotateHip(90)->move();
    // delay(500);

    spider->front_left->rotateKnee(130)->move();
    delay(500);
    spider->front_right->rotateKnee(230)->move();
    delay(500);
    spider->rear_right->rotateKnee(230)->move();
    delay(500);
    spider->rear_left->rotateKnee(130)->move();
    delay(500);
}
