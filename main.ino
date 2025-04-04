#include <Arduino.h>
#include <ESP32Servo.h>

#define MIN_ANGLE_LEFT_HIP  90
#define MAX_ANGLE_LEFT_HIP  180
#define MIN_ANGLE_LEFT_KNEE 0
#define MAX_ANGLE_LEFT_KNEE 90
#define MIN_ANGLE_LEFT_ANKLE 80
#define MAX_ANGLE_LEFT_ANKLE 180
#define MIN_ANGLE_RIGHT_HIP 0
#define MAX_ANGLE_RIGHT_HIP 90
#define MIN_ANGLE_RIGHT_KNEE 90
#define MAX_ANGLE_RIGHT_KNEE 180
#define MIN_ANGLE_RIGHT_ANKLE 0
#define MAX_ANGLE_RIGHT_ANKLE 100

class Joint {
    Servo servo;
    int pin;
    int minAngle;
    int maxAngle;
    public:
        Joint(int pin, int minAngle, int maxAngle) {
            servo.attach(pin);
            servo.write(minAngle + (maxAngle - minAngle) / 2); // set initial position to the middle
        }

        void move(int angle) {
            if (angle < minAngle) {
                Serial.printf("Angle is less than %d degrees, setting to %d degrees.\n", minAngle, minAngle);
                angle = minAngle;
            } else if (angle > maxAngle) {
                Serial.printf("Angle is greater than %d degrees, setting to %d degrees.\n", maxAngle, maxAngle);
                angle = maxAngle;
            }
            servo.write(angle);
        }
};
struct Leg {
    Joint hip;
    Joint knee;
    Joint ankle;
};
struct Legs {
    Leg frontLeft;
    Leg frontRight;
    Leg rearleft;
    Leg rearRight;
};

Legs *legs;

void setup() {
    Serial.begin(115200);

    // initialize servos
    legs = new Legs {
        .frontLeft = {
            .hip = Joint(34, MIN_ANGLE_LEFT_HIP, MAX_ANGLE_LEFT_HIP),
            .knee = Joint(35, MIN_ANGLE_LEFT_KNEE, MAX_ANGLE_LEFT_KNEE),
            .ankle = Joint(32, MIN_ANGLE_LEFT_ANKLE, MAX_ANGLE_LEFT_ANKLE),
        },
        .frontRight = {
            .hip = Joint(23, MIN_ANGLE_RIGHT_HIP, MAX_ANGLE_RIGHT_HIP),
            .knee = Joint(22, MIN_ANGLE_RIGHT_KNEE, MAX_ANGLE_RIGHT_KNEE),
            .ankle = Joint(21, MIN_ANGLE_RIGHT_ANKLE, MAX_ANGLE_RIGHT_ANKLE),
        },
        .rearleft = {
            .hip = Joint(26, MIN_ANGLE_LEFT_HIP, MAX_ANGLE_LEFT_HIP),
            .knee = Joint(25, MIN_ANGLE_LEFT_KNEE, MAX_ANGLE_LEFT_KNEE),
            .ankle = Joint(33, MIN_ANGLE_LEFT_ANKLE, MAX_ANGLE_LEFT_ANKLE),
        },
        .rearRight = {
            .hip = Joint(5, MIN_ANGLE_RIGHT_HIP, MAX_ANGLE_RIGHT_HIP),
            .knee = Joint(18, MIN_ANGLE_RIGHT_KNEE, MAX_ANGLE_RIGHT_KNEE),
            .ankle = Joint(19, MIN_ANGLE_RIGHT_ANKLE, MAX_ANGLE_RIGHT_ANKLE),
        },
    };
}

void loop() {
    Serial.println("Hello World!");
    delay(1000);
}
