/* External devices
[+] hMot1: drive left
[+] hMot2: drive right
[-] hMot3: steer
[-] hMot4: elevation
[!] hSens1: sumo eyes (low obstacles)
[+] hSens2: accelerometer (roughness)
[-] hSens3: sono (high obstacles)
[+] LED1: main loop (blinking)
[-] LED2: lowered suspension
[-] LED3: obstacle (solid - evadable, blinking - got lost)
*/

#include <cstdio>
#include <cmath>

#include "../include/hFramework.h"
#include "../include/hMotor.h"
#include "../include/hButton.h"
#include "../include/hSensors/Lego_Ultrasonic.h"
#include "../include/hSensors/Lego_Light.h"
#include "../include/hSensors/Hitechnic_Accel.h"

using namespace hFramework;
using namespace hSensors;

const int maxRightAngle = 80;
const int maxLeftAngle = -maxRightAngle;
const int scanResolution = 10;
const int scanStep = (maxRightAngle - maxLeftAngle) / scanResolution;
const int cruisePower = 800;
const int SuspensionExtensionEncoderCount = 10000;

Lego_Ultrasonic sono = Lego_Ultrasonic(hSens1);
Hitechnic_Accel accel = Hitechnic_Accel(hSens2);
Lego_Light eyes = Lego_Light(hSens3);

float x, y, z;
int shake;
bool obstacleLeft = true;
bool obstacleRight = true;
bool obstacle = obstacleLeft or obstacleRight;

void setDrivePower(int power) {
    hMot1.setPower(power);
    hMot2.setPower(power);
}

void setSteerAngle(int angle) {
    hMot3.rotAbs(angle);
}

void returnSteer() {
    setSteerAngle(0);
}

void retractSuspension() {
    hMot4.rotAbs(0);
}

void extendSuspension() {
    hMot4.rotAbs(SuspensionExtensionEncoderCount);
}

// sensors

int sonoScanAndSet() { // wywaliæ
    // returns absolute angle to the farthest obstacle (if any)
    int max = 0;
    int at = 0;
    for (int angle = maxLeftAngle; angle <= maxRightAngle; angle += scanStep) {
        setSteerAngle(angle);
        int dist = sono.readDist();
        if (dist > max) {
            max = dist;
            at = angle;
        }
        sys.delay_ms(250);
    }
    setSteerAngle(at);
    return at;
}

void accelReadShake() {
    float data[10];
    for(;;) {

        for (int i = 0; i < 10; i++) {
            accel.read(x, y, z);
            data[i] = z;
            sys.delay_ms(20);
        }
        float mean=0.0, sum_deviation=0.0;
        for (int i = 0; i < 10; ++i)
        {
            mean += data[i];
        }
        mean /= 10;
        for (int i = 0; i < 10; ++i)
            sum_deviation += (data[i] - mean) * (data[i] - mean);
        shake = (int)(sqrt(sum_deviation/10)*200);
    }
}

void lookForObstacles(){
    for (;;) {
        int data = eyes.readRaw();
        if (30 < data and data < 36) {
                obstacleLeft = true;
                obstacleRight = false;
        }
        if (63 < data and data < 69) {
                obstacleLeft = false;
                obstacleRight = true;
        }
        if (74 < data and data < 80) {
                obstacleLeft = true;
                obstacleRight = true;
        }
        obstacle = obstacleLeft and obstacleRight;
    }
}

void init() {
	sys.setLogDev(&Serial);
    sys.taskCreate(accelReadShake);
}

void reset() {
    returnSteer();
    retractSuspension();
}

void hMain(void)
{
    init();
	while (!hBtn1.isPressed()) {
	    LED1.toggle();
	    setDrivePower(cruisePower);
        while (!obstacle);
        if (true);
	}
	reset();
}
