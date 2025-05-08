#include <Arduino.h>
#include <ESP32Servo.h>

class Joint {
    Servo servo;
    int min_angle;
    int max_angle;
    int offset;
    bool invert;
    int current_angle;

    public:
        Joint(int pin, int min_angle, int max_angle, int offset, bool invert);
        // input to this function should be in global coordinate system
        int rotate(int angle);
        int get_angle();
        void move();
};

class Leg {
    public:
        Joint *hip;
        Joint *knee;
        Joint *ankle;
        Leg(Joint *hip, Joint *knee, Joint *ankle);
        void move();
};

class Spider {
    public:
        Leg *front_left;
        Leg *front_right;
        Leg *rear_left;
        Leg *rear_right;
        Spider(Leg *fl, Leg *fr, Leg *rl, Leg *rr);
};

struct Move {
    Joint* joint;
    int angle;
};
