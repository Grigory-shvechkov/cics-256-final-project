#include "legs.h"


Joint::Joint(int pin, int min_angle, int max_angle, int offset, bool invert) {
    this->servo.attach(pin);
    delay(100);
    this->min_angle = min_angle;
    this->max_angle = max_angle;
    this->offset = offset;
    this->invert = invert;
    this->current_angle = 90;
}

int Joint::rotate(int angle) {
    this->current_angle = convert_angle(angle);
    return current_angle;
}

int Joint::convert_angle(int angle) {
    int convertedAngle = angle;
    if (this->invert) {
        convertedAngle = -convertedAngle;
    }
    convertedAngle += offset;
    if (convertedAngle < min_angle) {
        convertedAngle = min_angle;
        Serial.printf("Warning: angle %d given, min is %d\n", convertedAngle, min_angle);
    } else if (convertedAngle > max_angle) {
        convertedAngle = max_angle;
        Serial.printf("Warning: angle %d given, max is %d\n", convertedAngle, max_angle);
    }
    return convertedAngle;
}

int Joint::get_angle() {
    return this->current_angle;
}

void Joint::move() {
    this->servo.write(this->current_angle);
}


Leg::Leg(Joint *hip, Joint *knee, Joint *ankle) {
    this->hip = hip;
    this->knee = knee;
    this->ankle = ankle;
}

void Leg::move() {
    this->hip->move();
    this->knee->move();
    this->ankle->move();
}


Spider::Spider(Leg *fl, Leg *fr, Leg *rl, Leg *rr) {
    this->front_left = fl;
    this->front_right = fr;
    this->rear_left = rl;
    this->rear_right = rr;
}
