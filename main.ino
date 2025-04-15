#include <Arduino.h>
#include <ESP32Servo.h>

// based on range of motion
#define HIP_MAX 90
#define HIP_MIN 0

#define KNEE_MIN 180
#define KNEE_MAX 90

#define ANKLE_MAX 90
#define ANKLE_MIN 180

enum joint
{
    HIP = 1,
    KNEE = 2,
    ANKLE = 3,
};

class Leg
{
    Servo hip;
    Servo knee;
    Servo ankle;

public:
    Leg(int HIP_PIN, int KNEE_PIN, int ANKLE_PIN)
    {

        this->hip.attach(HIP_PIN);
        delay(100); // Delay for servo initialization
        this->knee.attach(KNEE_PIN);
        delay(100);
        this->ankle.attach(ANKLE_PIN);
    }

    //returns a requested joint angle
    int joint_ang(int joint)
    {
        switch (joint)
        {
        case HIP:
            return this->hip.read();
            break;

        case KNEE:
            return this->knee.read();
            break;

        case ANKLE:
            return this->ankle.read();
            break;

        default:
            return 0;
        }
    }
    //moves all joints to specificed angle
    void move(int HIP_ANGLE, int KNEE_ANGLE, int ANKLE_ANGLE)
    {
        Serial.println("Moved");
        this->hip.write(HIP_ANGLE);
        this->knee.write(KNEE_ANGLE);
        this->ankle.write(ANKLE_ANGLE);
    }

    //prints every joints current angle
    void read()
    {
        Serial.println(hip.read());
        Serial.println(knee.read());
        Serial.println(ankle.read());
    }
};

class Spider
{
    Leg left_front;
    Leg left_rear;
    Leg right_front;
    Leg right_rear;

public:
    Spider(Leg lf_param, Leg lr_param, Leg rf_param, Leg rr_param)
        : left_front(lf_param), left_rear(lr_param), right_front(rf_param), right_rear(rr_param) {}

    //move selected leg to given angles in respective order
    void move_leg(int leg_num, int HIP_ANGLE, int KNEE_ANGLE, int ANKLE_ANGLE)
    {
        switch (leg_num)
        {
        case 1:
            this->left_front.move(HIP_ANGLE, KNEE_ANGLE, ANKLE_ANGLE);
            break;
        case 2:
            this->left_rear.move(HIP_ANGLE, KNEE_ANGLE, ANKLE_ANGLE);
            break;
        case 3:
            this->right_front.move(HIP_ANGLE, KNEE_ANGLE, ANKLE_ANGLE);
            break;
        case 4:
            this->right_rear.move(HIP_ANGLE, KNEE_ANGLE, ANKLE_ANGLE);
            break;
        default:
            return;
        }
    }

    void stand_up()
    {   

        left_front.move(HIP_MAX,KNEE_MIN,ANKLE_MAX);
    }

    void forward()
    {
        // Implement forward movement
    }
};

Leg *left_front;
Leg *left_rear;
Leg *right_front;
Leg *right_rear;

Spider *spider;

Servo test_servo;

void setup()
{
    /*
    //setup serial communication
    Serial.begin(115200);
    Serial.println("TIME TO CRAWL");

    //create four leg objects
    left_front = new Leg(34, 35, 32); // issue with hardwaare with this leg
    left_rear = new Leg(26, 25, 33);
    right_front = new Leg(23, 22, 21);
    right_rear = new Leg(5, 18, 19);
    //create new spider object
    spider = new Spider(*left_front, *left_rear, *right_front, *right_rear); // give spider the leg objects
    */
    test_servo.attach(35);
}

void loop()
{   
    test_servo.write(90);
    delay(1000);
    test_servo.write(0);
    delay(1000);
    //loop code goes here
}
