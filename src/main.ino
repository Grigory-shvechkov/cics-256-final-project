#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wifi.h>
#include <WebServer.h>
#include "limits.h"
#include "legs.h"
#include <vector>

#define uS_PER_DEG 1389

Spider *spider;
Leg *front_left, *front_right, *rear_left, *rear_right;

std::vector<std::vector<Move>> homunculus_walk;
std::vector<std::vector<Move>> walk_forward;

WebServer server(80);
void on_home() {
    server.send(200, "application/json", "{\"status\":\"ok\"}");
};
void on_rotate() {
    // if (server.hasArg("leg") && server.hasArg("joint") && server.hasArg("angle")) {
    //     if (server.arg("leg") == "fl") {
    //         if (server.arg("joint") == "hip") {
    //             front_left->rotateHip(server.arg("angle").toInt());
    //         } else if (server.arg("joint") == "knee") {
    //             front_left->rotateKnee(server.arg("angle").toInt());
    //         } else if (server.arg("joint") == "ankle") {
    //             front_left->rotateAnkle(server.arg("angle").toInt());
    //         }
    //         front_left->move();
    //     } else if (server.arg("leg") == "fr") {
    //         if (server.arg("joint") == "hip") {
    //             front_right->rotateHip(server.arg("angle").toInt());
    //         } else if (server.arg("joint") == "knee") {
    //             front_right->rotateKnee(server.arg("angle").toInt());
    //         } else if (server.arg("joint") == "ankle") {
    //             front_right->rotateAnkle(server.arg("angle").toInt());
    //         }
    //         front_right->move();
    //     } else if (server.arg("leg") == "rl") {
    //         if (server.arg("joint") == "hip") {
    //             rear_left->rotateHip(server.arg("angle").toInt());
    //         } else if (server.arg("joint") == "knee") {
    //             rear_left->rotateKnee(server.arg("angle").toInt());
    //         } else if (server.arg("joint") == "ankle") {
    //             rear_left->rotateAnkle(server.arg("angle").toInt());
    //         }
    //         rear_left->move();
    //     } else if (server.arg("leg") == "rr") {
    //         if (server.arg("joint") == "hip") {
    //             rear_right->rotateHip(server.arg("angle").toInt());
    //         } else if (server.arg("joint") == "knee") {
    //             rear_right->rotateKnee(server.arg("angle").toInt());
    //         } else if (server.arg("joint") == "ankle") {
    //             rear_right->rotateAnkle(server.arg("angle").toInt());
    //         }
    //         rear_right->move();
    //     }
    // }
};

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

    homunculus_walk = {
        // Lift FL
        {
            {front_left->knee, 180},
            {front_left->ankle, 90},
        },
        // Turn FL
        {
            {front_left->hip, 45},
        },
        // Plant FL
        {
            {front_left->knee, 90},
            {front_left->ankle, 165},
        },

        // Lift FR
        {
            {front_right->knee, 180},
            {front_right->ankle, 90},
        },
        // Turn FR
        {
            {front_right->hip, 315},
        },
        // Plant FR
        {
            {front_right->knee, 270},
            {front_right->ankle, 175},
        },

        // Thrust ALL
        {
            {front_left->hip, 90},
            {front_left->knee, 75},
            {front_left->ankle, 180},
        },
        {
            {front_right->hip, 270},
            {front_right->knee, 285},
            {front_right->ankle, 180},
        },
        {
            {rear_left->hip, 135},
            {rear_left->knee, 90},
            {rear_left->ankle, 165},
        },
        {
            {rear_right->hip, 225},
            {rear_right->knee, 270},
            {rear_right->ankle, 195},
        },

        // Lift RL
        {
            {rear_left->knee, 0},
            {rear_left->ankle, 90},
        },
        // Turn RL
        {
            {rear_left->hip, 90},
        },
        // Plant RL
        {
            {rear_left->knee, 90},
            {rear_left->ankle, 165},
        },

        // Lift RR
        {
            {rear_right->knee, 0},
            {rear_right->ankle, 270},
        },
        // Turn RR
        {
            {rear_right->hip, 270},
        },
        // Plant RR
        {
            {rear_right->knee, 270},
            {rear_right->ankle, 195},
        },
    };

    walk_forward = {
        // Lift FL
        {
            {front_left->knee, 30},
            {front_left->ankle, 110},
        },
        // Turn FL
        {
            {front_left->hip, 15},
        },
        // Plant FL
        {
            {front_left->knee, 90},
            {front_left->ankle, 165},
        },

        // Lift FR
        {
            {front_right->knee, 330},
            {front_right->ankle, 290},
        },
        // Turn FR
        {
            {front_right->hip, 345},
        },
        // Plant FR
        {
            {front_right->knee, 270},
            {front_right->ankle, 195},
        },

        // Thrust ALL
        {
            {front_left->hip, 45},
            {front_left->knee, 75},
            {front_left->ankle, 180},
            {front_right->hip, 315},
            {front_right->knee, 285},
            {front_right->ankle, 180},
            {rear_left->hip, 165},
            {rear_left->knee, 75},
            {rear_left->ankle, 165},
            {rear_right->hip, 195},
            {rear_right->knee, 285},
            {rear_right->ankle, 195},
        },

        // Lift RL
        {
            {rear_left->knee, 30},
            {rear_left->ankle, 110},
        },
        // Turn RL
        {
            {rear_left->hip, 135},
        },
        // Plant RL
        {
            {rear_left->knee, 90},
            {rear_left->ankle, 165},
        },

        // Lift RR
        {
            {rear_right->knee, 330},
            {rear_right->ankle, 290},
        },
        // Turn RR
        {
            {rear_right->hip, 225},
        },
        // Plant RR
        {
            {rear_right->knee, 270},
            {rear_right->ankle, 195},
        },
    };
};

void loop() {
    for (int i = 0; i < walk_forward.size(); i++) {
        int max_move_angle = 0;
        for (int j = 0; j < walk_forward[i].size(); j++) {
            Move move = walk_forward[i][j];
            // debug
            Serial.printf("Joint: %d, Angle: %d\n", move.joint->get_angle(), move.angle);

            if (move.joint->get_angle() > max_move_angle) {
                max_move_angle = move.joint->get_angle();
            }

            move.joint->rotate(move.angle);
        }
        spider->front_left->move();
        spider->front_right->move();
        spider->rear_left->move();
        spider->rear_right->move();
        delayMicroseconds(max_move_angle * uS_PER_DEG);
    }
};
