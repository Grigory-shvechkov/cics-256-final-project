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
#define RF_HIP_MIN 180

#define RF_KNEE_MAX 90
#define RF_KNEE_MIN 0

#define RF_ANKLE_MAX 90
#define RF_ANKLE_MIN 0

//-------------------------//

enum joint {
    HIP = 1,
    KNEE = 2,
    ANKLE = 3,
};

class Leg {
    Servo hip;
    Servo knee;
    Servo ankle;

    public:
        Leg(int HIP_PIN, int KNEE_PIN, int ANKLE_PIN) {

            this->hip.attach(HIP_PIN);
            delay(100); // delay for servo initialization
            this->knee.attach(KNEE_PIN);
            delay(100);
            this->ankle.attach(ANKLE_PIN);
        }

        // returns a requested joint angle
        int joint_ang(int joint) {
            switch (joint) {
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

        // moves all joints to specificed angle
        void move(int HIP_ANGLE, int KNEE_ANGLE, int ANKLE_ANGLE) {
            // Serial.println("Moved");
            this->hip.write(HIP_ANGLE);
            this->knee.write(KNEE_ANGLE);
            this->ankle.write(ANKLE_ANGLE);
        }

        // prints every joints current angle
        void read() {
            Serial.println(hip.read());
            Serial.println(knee.read());
            Serial.println(ankle.read());
        }
};

class Spider {
    Leg *left_front;
    Leg *left_rear;
    Leg *right_front;
    Leg *right_rear;

    public:
        Spider(Leg *lf_param, Leg *lr_param, Leg *rf_param, Leg *rr_param) {
            this->left_front = lf_param;
            this->left_rear = lr_param;
            this->right_front = rf_param;
            this->right_rear = rr_param;
        }

        // move selected leg to given angles in respective order
        void move_leg(int leg_num, int HIP_ANGLE, int KNEE_ANGLE, int ANKLE_ANGLE) {
            switch (leg_num) {
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

        void sprawl() {
            // Serial.println("SPRAWLED");
            left_front->move(LF_HIP_MAX,LF_KNEE_MAX,LF_ANKLE_MAX);
            left_rear->move(LR_HIP_MAX,LR_KNEE_MAX,LR_ANKLE_MAX);
            right_front->move(RF_HIP_MAX,RF_KNEE_MAX,RF_ANKLE_MAX);
            right_rear->move(RR_HIP_MAX,RR_KNEE_MAX,RR_ANKLE_MAX);
        }

        void stand_up() {   
            left_front->move(LF_HIP_MIN + 45, LF_KNEE_MAX, LF_ANKLE_MAX);
            left_rear->move(LR_HIP_MIN - 45, LR_KNEE_MAX, LR_ANKLE_MAX);
            right_front->move(RF_HIP_MIN - 45, RF_KNEE_MAX, RF_ANKLE_MAX);
            right_rear->move(RR_HIP_MIN + 45, RR_KNEE_MAX, RR_ANKLE_MAX);
            delay(1000);
            left_front->move(LF_HIP_MIN + 45, LF_KNEE_MAX, LF_ANKLE_MIN - 15);
            left_rear->move(LR_HIP_MIN - 45, LR_KNEE_MAX, LR_ANKLE_MIN + 15);
            right_front->move(RF_HIP_MIN - 45, RF_KNEE_MAX, RF_ANKLE_MIN + 15);
            right_rear->move(RR_HIP_MIN + 45, RR_KNEE_MAX, RR_ANKLE_MIN - 15);
            delay(1000);
            left_front->move(LF_HIP_MIN + 45, LF_KNEE_MAX -30, LF_ANKLE_MIN - 15);
            left_rear->move(LR_HIP_MIN - 45, LR_KNEE_MAX + 30, LR_ANKLE_MIN + 15);
            right_front->move(RF_HIP_MIN - 45, RF_KNEE_MAX + 30, RF_ANKLE_MIN + 15);
            right_rear->move(RR_HIP_MIN + 45, RR_KNEE_MAX - 30, RR_ANKLE_MIN - 15);
        }

        void forward() {
            left_front->move(LF_HIP_MIN + 45, LF_KNEE_MAX - 30, LF_ANKLE_MIN - 15);
            right_rear->move(RR_HIP_MIN, RR_KNEE_MAX - 30, RR_ANKLE_MIN - 15);
            delay(500);
            right_front->move(RF_HIP_MIN, RF_KNEE_MAX + 30, RF_ANKLE_MIN + 15);
            left_rear->move(LR_HIP_MIN, LR_KNEE_MAX + 30, LR_ANKLE_MIN + 15);
            delay(500);
            left_front->move(LF_HIP_MIN, LF_KNEE_MAX - 30, LF_ANKLE_MIN - 15);
            right_rear->move(RR_HIP_MIN, RR_KNEE_MAX - 30, RR_ANKLE_MIN - 15);
            delay(500);
            left_rear->move(LR_HIP_MIN , LR_KNEE_MAX + 30, LR_ANKLE_MIN + 15);
            right_front->move(RF_HIP_MIN - 45, RF_KNEE_MAX + 30, RF_ANKLE_MIN + 15);
            delay(500);
        }
};

void run_servo(Servo servo,int max_angle,int min_angle) {
    while(true) {
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

void setup() {
    // setup serial communication
    Serial.begin(115200);

    // create four leg objects
    left_rear = new Leg(19, 18, 5); // issue with hardware with this leg
    left_front = new Leg(23, 22, 21);
    right_front = new Leg(12, 14, 27);
    right_rear = new Leg(33, 25, 26);
    // create new spider object
    spider = new Spider(left_front, left_rear, right_front, right_rear); // give spider the leg objects
    // spider->stand_up();
    // delay(5000);
    Serial.println("TIME TO CRAWL");

    spider->sprawl();
    delay(1000);
    spider->stand_up();
    delay(1000);
    for(int i = 0; i < 20; i++) {
        spider->forward();
    }
}

void loop() {
    static String command = "";
    if (Serial.available() > 0) {
        char input = Serial.read();
        if (input == '\n') {
            command.trim();
            if (command.length() > 0) {
                char buffer[64];
                command.toCharArray(buffer, sizeof(buffer));
                char* firstStr = strtok(buffer, " ");
                char* legStr = strtok(nullptr, " ");
                char* jointStr = strtok(nullptr, " ");
                char* angleStr = strtok(nullptr, " ");

                if (firstStr && strcmp(firstStr, "move") == 0 && legStr && jointStr && angleStr) {
                    int angle = atoi(angleStr);
                    int legNum = 0;

                    if (strcmp(legStr, "lf") == 0) legNum = 1;
                    else if (strcmp(legStr, "lr") == 0) legNum = 2;
                    else if (strcmp(legStr, "rf") == 0) legNum = 3;
                    else if (strcmp(legStr, "rr") == 0) legNum = 4;

                    if (legNum) {
                        Leg* legPtr = nullptr;
                        switch (legNum) {
                            case 1: legPtr = left_front; break;
                            case 2: legPtr = left_rear; break;
                            case 3: legPtr = right_front; break;
                            case 4: legPtr = right_rear; break;
                        }
                        int hip = legPtr->joint_ang(HIP);
                        int knee = legPtr->joint_ang(KNEE);
                        int ankle = legPtr->joint_ang(ANKLE);

                        if (strcmp(jointStr, "hip") == 0) hip = angle;
                        else if (strcmp(jointStr, "knee") == 0) knee = angle;
                        else if (strcmp(jointStr, "ankle") == 0) ankle = angle;

                        spider->move_leg(legNum, hip, knee, ankle);
                        Serial.println("OK");
                    }
                }
            }
            command = "";
        } else if (input != '\r') {
            command += input;
        }
    }
}
