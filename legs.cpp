#include "legs.h"


Joint::Joint(int pin, int min_angle, int max_angle, int offset) {
    this->servo.attach(pin);
    delay(100);
    this->min_angle = min_angle;
    this->max_angle = max_angle;
    this->offset = offset;
    this->current_angle = 90;
}

int Joint::rotate(int angle) {
    int convertedAngle = angle + offset;
    if (convertedAngle < min_angle) {
        convertedAngle = min_angle;
        Serial.printf("Warning: angle %d given, min is %d\n", convertedAngle, min_angle);
    } else if (convertedAngle > max_angle) {
        convertedAngle = max_angle;
        Serial.printf("Warning: angle %d given, max is %d\n", convertedAngle, max_angle);
    }
    this->current_angle = convertedAngle;
    return convertedAngle;
}

void Joint::move() {
    this->servo.write(this->current_angle);
}


Leg::Leg(Joint *hip, Joint *knee, Joint *ankle) {
    this->hip = hip;
    this->knee = knee;
    this->ankle = ankle;
}

Leg* Leg::rotateHip(int angle) {
    this->hip->rotate(angle);
    return this;
}
Leg* Leg::rotateKnee(int angle) {
    this->knee->rotate(angle);
    return this;
}
Leg* Leg::rotateAnkle(int angle) {
    this->ankle->rotate(angle);
    return this;
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
