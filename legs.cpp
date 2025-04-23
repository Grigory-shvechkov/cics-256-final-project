#include "legs.h"

Joint::Joint(int pin, int min_angle, int max_angle, int offset) {
    this->servo.attach(pin);
    delay(100);
    this->min_angle = min_angle;
    this->max_angle = max_angle;
    this->offset = offset;
}

int Joint::convertAngle(int angle) {
    return ((angle + offset) % 360 + 360) % 360;
}

Joint Joint::rotate(int angle) {
    angle = convertAngle(angle);
    if (angle < min_angle) {
        angle = min_angle;
        Serial.printf("Warning: angle %d given, min is %d\n", angle, min_angle);
    } else if (angle > max_angle) {
        angle = max_angle;
        Serial.printf("Warning: angle %d given, max is %d\n", angle, max_angle);
    }
    this->servo.write(angle);
    return *this;
}

Leg::Leg(Joint *hip, Joint *knee, Joint *ankle) {
    this->hip = hip;
    this->knee = knee;
    this->ankle = ankle;
}

Spider::Spider(Leg *fl, Leg *fr, Leg *rl, Leg *rr) {
    this->front_left = fl;
    this->front_right = fr;
    this->rear_left = rl;
    this->rear_right = rr;
}
