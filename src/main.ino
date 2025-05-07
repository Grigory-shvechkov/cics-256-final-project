#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wifi.h>
#include <WebServer.h>
#include "limits.h"
#include "legs.h"

Spider *spider;
Leg *front_left, *front_right, *rear_left, *rear_right;

Move walk_forward[][] = {
    // Lift FL
    {
        {FRONT_LEFT, KNEE, 180},
        {FRONT_LEFT, ANKLE, 90},
    },
    // Turn FL
    {
        {FRONT_LEFT, HIP, 45},
    },
    // Plant FL
    {
        {FRONT_LEFT, KNEE, 90},
        {FRONT_LEFT, ANKLE, 165},
    },

    // Lift FR
    {
        {FRONT_RIGHT, KNEE, 180},
        {FRONT_RIGHT, ANKLE, 90},
    },
    // Turn FR
    {
        {FRONT_RIGHT, HIP, 315},
    },
    // Plant FR
    {
        {FRONT_RIGHT, KNEE, 270},
        {FRONT_RIGHT, ANKLE, 175},
    },

    // Thrust ALL
    {
        {FRONT_LEFT, HIP, 90},
        {FRONT_LEFT, KNEE, 75},
        {FRONT_LEFT, ANKLE, 180},
    },
    {
        {FRONT_RIGHT, HIP, 270},
        {FRONT_RIGHT, KNEE, 285},
        {FRONT_RIGHT, ANKLE, 180},
    },
    {
        {REAR_LEFT, HIP, 135},
        {REAR_LEFT, KNEE, 90},
        {REAR_LEFT, ANKLE, 165},
    },
    {
        {REAR_RIGHT, HIP, 225},
        {REAR_RIGHT, KNEE, 270},
        {REAR_RIGHT, ANKLE, 195},
    },

    // Lift RL
    {
        {REAR_LEFT, KNEE, 0},
        {REAR_LEFT, ANKLE, 90},
    },
    // Turn RL
    {
        {REAR_LEFT, HIP, 90},
    },
    // Plant RL
    {
        {REAR_LEFT, KNEE, 90},
        {REAR_LEFT, ANKLE, 165},
    },

    // Lift RR
    {
        {REAR_RIGHT, KNEE, 0},
        {REAR_RIGHT, ANKLE, 270},
    },
    // Turn RR
    {
        {REAR_RIGHT, HIP, 270},
    },
    // Plant RR
    {
        {REAR_RIGHT, KNEE, 270},
        {REAR_RIGHT, ANKLE, 195},
    },
};

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
        new Joint(27, FR_ANKLE_MIN, FR_ANKLE_MAX, -180, false) // ankle
    );
    rear_left = new Leg(
        new Joint(19, RL_HIP_MIN, RL_HIP_MAX, 0, false), // hip
        new Joint(18, RL_KNEE_MIN, RL_KNEE_MAX, 0, false), // knee
        new Joint(5, RL_ANKLE_MIN, RL_ANKLE_MAX, 180, true) // ankle
    );
    rear_right = new Leg(
        new Joint(33, RR_HIP_MIN, RR_HIP_MAX, -180, false), // hip
        new Joint(25, RR_KNEE_MIN, RR_KNEE_MAX, -180, false), // knee
        new Joint(26, RR_ANKLE_MIN, RR_ANKLE_MAX, 360, true) // ankle
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

    // spider->front_left->rotateKnee(130)->move();
    // delay(500);
    // spider->front_right->rotateKnee(230)->move();
    // delay(500);
    // spider->rear_right->rotateKnee(230)->move();
    // delay(500);
    // spider->rear_left->rotateKnee(130)->move();
    // delay(500);

    // spider->front_left->rotateAnkle(180)->move();
    // delay(500);
    // spider->front_right->rotateAnkle(180)->move();
    // delay(500);
    // spider->rear_right->rotateAnkle(180)->move();
    // delay(500);
    // spider->rear_left->rotateAnkle(180)->move();
    // delay(500);

    int i = 0;
    while (walk_forward[i][0]) {
        for (int j = 0; walk_forward[i][j]; j++) {
            Move move = walk_forward[i][j];
            if (move.leg_type == FRONT_LEFT) {
                if (move.joint_type == HIP) {
                    front_left->rotateHip(move.angle);
                } else if (move.joint_type == KNEE) {
                    front_left->rotateKnee(move.angle);
                } else if (move.joint_type == ANKLE) {
                    front_left->rotateAnkle(move.angle);
                }
            } else if (move.leg_type == FRONT_RIGHT) {
                if (move.joint_type == HIP) {
                    front_right->rotateHip(move.angle);
                } else if (move.joint_type == KNEE) {
                    front_right->rotateKnee(move.angle);
                } else if (move.joint_type == ANKLE) {
                    front_right->rotateAnkle(move.angle);
                }
            } else if (move.leg_type == REAR_LEFT) {
                if (move.joint_type == HIP) {
                    rear_left->rotateHip(move.angle);
                } else if (move.joint_type == KNEE) {
                    rear_left->rotateKnee(move.angle);
                } else if (move.joint_type == ANKLE) {
                    rear_left->rotateAnkle(move.angle);
                }
            } else if (move.leg_type == REAR_RIGHT) {
                if (move.joint_type == HIP) {
                    rear_right->rotateHip(move.angle);
                } else if (move.joint_type == KNEE) {
                    rear_right->rotateKnee(move.angle);
                } else if (move.joint_type == ANKLE) {
                    rear_right->rotateAnkle(move.angle);
                }
            }
        }
        spider->front_left->move();
        spider->front_right->move();
        spider->rear_left->move();
        spider->rear_right->move();
        delay(500);
        i++;
    }
}
