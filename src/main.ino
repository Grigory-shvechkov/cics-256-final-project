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
std::vector<std::vector<Move>> scoot_forward;
std::vector<std::vector<Move>> walk_forward;
std::vector<std::vector<Move>> walk_backward;
std::vector<std::vector<Move>> rotate_left;
std::vector<std::vector<Move>> rotate_right;

enum direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    STOP,
};

direction current_direction = STOP;

WebServer server(80);
void on_home() {
    server.send(200, "application/json", "{\"status\":\"ok\"}");
};
void on_move() {
    String direction = server.arg("direction");
    if (direction == "forward") {
        current_direction = FORWARD;
    } else if (direction == "backward") {
        current_direction = BACKWARD;
    } else if (direction == "left") {
        current_direction = LEFT;
    } else if (direction == "right") {
        current_direction = RIGHT;
    } else if (direction == "stop") {
        current_direction = STOP;
    } else {
        server.send(400, "application/json", "{\"error\":\"invalid direction\"}");
        return;
    }
    server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    WiFi.softAP("Spider");
    server.on("/", on_home);
    server.on("/move", on_move);
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

    scoot_forward = {
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
    };

    walk_forward = {
        // lift knee and move hip forward and plant
        {
            {front_left->knee, 45},
        },
        {
            {front_left->hip, 45},
        },
        {
            {front_left->knee, 90},
        },
        // slide right front leg back and move left rear backwards
        {
            {front_right->hip, 270},
            {rear_left->hip, 135},
        },
        // move right rear forward
        {
            {rear_right->knee, 315},
        },
        {
            {rear_right->hip, 270},
        },
        {
            {rear_right->knee, 270},
        },

        // SECOND PART OF CYCLE

        // move front right forward and plant
        {
            {front_right->knee, 315},
        },
        {
            {front_right->hip, 315},
        },
        {
            {front_right->knee, 270},
        },
        // move front left back and move right rear back
        {
            {front_left->hip, 90},
            {rear_right->hip, 225},
        },
        // lift rear left and plant
        {
            {rear_left->knee, 45},
        },
        {
            {rear_left->hip, 90},
        },
        {
            {rear_left->knee, 90},
        },
    };

    walk_backward = {
        {
            {rear_right->knee, 315},
        },
        {
            {rear_right->hip, 225},
        },
        {
            {rear_right->knee, 270},
        },

        {
            {rear_left->hip, 90},
            {front_right->hip, 315},
        },

        {
            {front_left->knee, 45},
        },
        {
            {front_left->hip, 90},
        },
        {
            {front_left->knee, 90},
        },

        // second part

        {
            {rear_left->knee, 65},
        },
        {
            {rear_left->hip, 135},
        },
        {
            {rear_left->knee, 90},
        },

        {
            {rear_right->hip, 270},
            {front_left->hip, 45},
        },

        {
            {front_right->knee, 315},
        },
        {
            {front_right->hip, 270},
        },
        {
            {front_right->knee, 270},
        },
    };

    rotate_left = {
        // lift front left and swing counter clockwise
        {
            {front_left->knee, 45}
        },
        {
            {front_left->hip, 90}
        },
        {
            {front_left->knee, 90},
        },
        // lift rear right and swing counter clockwise
        {
            {rear_right->knee, 315}
        },
        {
            {rear_right->hip, 360}
        },
        {
            {rear_right->knee, 270}
        },
        // lift rear left and swing counter clockwise
        {
            {rear_left->knee, 45}
        },
        {
            {rear_left->hip, 180}
        },
        {
            {rear_left->knee, 90}
        },
        // lift front right and swing counter clockwise
        {
            {front_right->knee, 315}
        },
        {
            {front_right->hip, 360}
        },
        {
            {front_right->knee, 270}
        },
        // thrust counter clockwise
        {
            {front_left->hip, 45},
            {front_right->hip, 315},
            {rear_left->hip, 135},
            {rear_right->hip, 225}
        },
    };

    rotate_right = {
        // lift front left and swing clockwise
        {
            {front_left->knee, 45}
        },
        {
            {front_left->hip, 0}
        },
        {
            {front_left->knee, 90},
        },
        // lift rear right and swing clockwise
        {
            {rear_right->knee, 315}
        },
        {
            {rear_right->hip, 180}
        },
        {
            {rear_right->knee, 270}
        },
        // lift rear left and swing clockwise
        {
            {rear_left->knee, 45}
        },
        {
            {rear_left->hip, 90}
        },
        {
            {rear_left->knee, 90}
        },
        // lift front right and swing clockwise
        {
            {front_right->knee, 315}
        },
        {
            {front_right->hip, 270}
        },
        {
            {front_right->knee, 270}
        },
        // thrust clockwise
        {
            {front_left->hip, 45},
            {front_right->hip, 315},
            {rear_left->hip, 135},
            {rear_right->hip, 225}
        },
    };

    // lock ankles on startup
    front_left->ankle->rotate(180);
    front_right->ankle->rotate(180);
    rear_left->ankle->rotate(180);
    rear_right->ankle->rotate(180);
    // move knees
    front_left->knee->rotate(45);
    front_right->knee->rotate(315);
    rear_left->knee->rotate(45);
    rear_right->knee->rotate(315);
    // move hips
    front_left->hip->rotate(45);
    front_right->hip->rotate(315);
    rear_left->hip->rotate(135);
    rear_right->hip->rotate(225);
    // plant feet
    front_left->knee->rotate(90);
    front_right->knee->rotate(270);
    rear_left->knee->rotate(90);
    rear_right->knee->rotate(270);
    spider->move();
};

void run_cycle(std::vector<std::vector<Move>> moves) {
    for (int i = 0; i < moves.size(); i++) {
        int max_move_angle = 0;
        for (int j = 0; j < moves[i].size(); j++) {
            Move move = moves[i][j];
            // debug
            // Serial.printf("Joint: %d, Angle: %d\n", move.joint->get_angle(), move.angle);

            int angle_change = abs(move.joint->get_angle() - move.joint->convert_angle(move.angle));
            if (angle_change > max_move_angle) {
                max_move_angle = angle_change;
            }

            move.joint->rotate(move.angle);
        }
        spider->move();
        delayMicroseconds(max_move_angle * uS_PER_DEG);
    }
};

void loop() {
    server.handleClient();
    if (current_direction == FORWARD) {
        run_cycle(homunculus_walk);
    } else if (current_direction == BACKWARD) {
        run_cycle(homunculus_walk);
    } else if (current_direction == LEFT) {
        run_cycle(rotate_left);
    } else if (current_direction == RIGHT) {
        run_cycle(rotate_right);
    }
};
