#include <Arduino.h>
#include <ESP32Servo.h>

// based on range of motion

//-------------------------//
//    LEFT REAR LIMITS     //
//-------------------------//

#define LR_HIP_MAX 90
#define LR_HIP_MIN 180

#define LR_KNEE_MAX 90
#define LR_KNEE_MIN 0

#define LR_ANKLE_MAX 90
#define LR_ANKLE_MIN 0

//-------------------------//
//    LEFT FRONT LIMITS    //
//-------------------------//

#define LF_HIP_MAX 90
#define LF_HIP_MIN 0

#define LF_KNEE_MAX 90
#define LF_KNEE_MIN 180

#define LF_ANKLE_MAX 90
#define LF_ANKLE_MIN 180

//-------------------------//
//    RIGHT REAR LIMITS    //
//-------------------------//

#define RR_HIP_MAX 90
#define RR_HIP_MIN 0

#define RR_KNEE_MAX 90
#define RR_KNEE_MIN 180

#define RR_ANKLE_MAX 90
#define RR_ANKLE_MIN 180

//-------------------------//
//   RIGHT FRONT LIMITS    //
//-------------------------//

#define RF_HIP_MAX 90
#define RF_HIP_MIN 0

#define RF_KNEE_MAX 90
#define RF_KNEE_MIN 0

#define RF_ANKLE_MAX 90
#define RF_ANKLE_MIN 180

//-------------------------//

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
       // Serial.println("Moved");
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
    Leg *left_front;
    Leg *left_rear;
    Leg *right_front;
    Leg *right_rear;

public:
   

    Spider(Leg *lf_param, Leg *lr_param, Leg *rf_param, Leg *rr_param)
    {
        this->left_front = lf_param;
        this->left_rear = lr_param;
        this->right_front = rf_param;
        this->right_rear = rr_param;
    }

    //move selected leg to given angles in respective order
    void move_leg(int leg_num, int HIP_ANGLE, int KNEE_ANGLE, int ANKLE_ANGLE)
    {
        switch (leg_num)
        {
        case 1:
            this->left_front->move(HIP_ANGLE, KNEE_ANGLE, ANKLE_ANGLE);
            break;
        case 2:
            this->left_rear->move(HIP_ANGLE, KNEE_ANGLE, ANKLE_ANGLE);
            break;
        case 3:
            this->right_front->move(HIP_ANGLE, KNEE_ANGLE, ANKLE_ANGLE);
            break;
        case 4:
            this->right_rear->move(HIP_ANGLE, KNEE_ANGLE, ANKLE_ANGLE);
            break;
        default:
            return;
        }
    }

    void sprawl()
    {
        //Serial.println("SPRAWLED");
        left_front->move(LF_HIP_MAX,LF_KNEE_MAX,LF_ANKLE_MAX);
        left_rear->move(LR_HIP_MAX,LR_KNEE_MAX,LR_ANKLE_MAX);
        right_front->move(RF_HIP_MAX,RF_KNEE_MAX,RF_ANKLE_MAX);
        right_rear->move(RR_HIP_MAX,RR_KNEE_MAX,RR_ANKLE_MAX);
    }

    void stand_up()
    {   
        //TODO: finish this
        // left_front.move(HIP_MAX,KNEE_MIN,ANKLE_MAX);
        // left_rear.move(HIP_MAX,KNEE_MIN,ANKLE_MAX);
        // right_front.move(HIP_MAX,KNEE_MIN,ANKLE_MAX);
        // right_rear.move(HIP_MAX,KNEE_MIN,ANKLE_MAX);
    }

    void forward()
    {
        // Implement forward movement
    }
};

void run_servo(Servo servo,int max_angle,int min_angle)
{
    while(true)
    {
        servo.write(max_angle);
        delay(1000);
        servo.write(min_angle);
        delay(1000);
    }
}


Leg *left_front;
Leg *left_rear;
Leg *right_front;
Leg *right_rear;

Spider *spider;

Servo test_servo;

void setup()
{
    
    //setup serial communication
    Serial.begin(115200);
    
    

    //create four leg objects
    left_rear = new Leg(12, 14, 27); // issue with hardwaare with this leg
    left_front = new Leg(26, 25, 33);
    right_front = new Leg(23, 22, 21);
    right_rear = new Leg(5, 18, 19);
    // //create new spider object
     spider = new Spider(left_front, left_rear, right_front, right_rear); // give spider the leg objects
     //spider->stand_up();
     //delay(5000);
     Serial.println("TIME TO CRAWL");
     

   
}

void loop()
{   

    spider->sprawl();
    delay(1000);

    // left_front->move(LF_HIP_MAX,LF_KNEE_MAX,LF_ANKLE_MAX);
    // left_rear->move(LR_HIP_MAX,LR_KNEE_MAX,LR_ANKLE_MAX);
    // right_front->move(RF_HIP_MAX, RF_KNEE_MAX, RF_ANKLE_MAX);
    // right_rear->move(RR_HIP_MAX, RR_KNEE_MAX, RR_ANKLE_MAX);
    // delay(1000);
    // left_front->move(LF_HIP_MIN,LF_KNEE_MIN,LF_ANKLE_MIN);
    // left_rear->move(LR_HIP_MIN,LR_KNEE_MIN,LR_ANKLE_MIN);
    // right_front->move(RF_HIP_MIN, RF_KNEE_MIN, RF_ANKLE_MIN);
    // right_rear->move(RR_HIP_MIN, RR_KNEE_MIN, RR_ANKLE_MIN);
    // delay(1000);


    //loop code goes here
}
