#include <Arduino.h>
#include <ESP32Servo.h>

class Joint {
    Servo servo;
    int min_angle;
    int max_angle;
    int offset;

    int convertAngle(int angle);

    public:
        Joint(int pin, int min_angle, int max_angle, int offset);
        Joint rotate(int angle);
};

class Leg {
    public:
        Joint *hip;
        Joint *knee;
        Joint *ankle;
        Leg(Joint *hip, Joint *knee, Joint *ankle);
};

class Spider {
    Leg *front_left;
    Leg *front_right;
    Leg *rear_left;
    Leg *rear_right;

    public:
        Spider(Leg *fl, Leg *fr, Leg *rl, Leg *rr);
};
