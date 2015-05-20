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

#include "hFramework.h"
#include "hMotor.h"
#include "Lego_Ultrasonic.h"
#include "sensors/Hitechnic_Accel.h"

using namespace hFramework;
using namespace hSensors;

const int maxRightAngle = 80;
const int maxLeftAngle = -maxRightAngle;
const int scanResolution = 10;
const int scanStep = (maxRightAngle - maxLeftAngle) / scanResolution;

Lego_Ultrasonic sono(hSens1);
Hitechnic_Accel accel = Hitechnic_Accel(hSens2);
float x, y, z;
int shake;

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

// tests
void testDrive() {
    setDrivePower(0);
    setDrivePower(1000);
    sys.delay_ms(500);
    setDrivePower(-1000);
    sys.delay_ms(500);
    setDrivePower(0);
    sys.delay_ms(500);
}

void testSteer(int angle) {
    returnSteer();
    sys.delay_ms(500);
    setSteerAngle(angle);
    sys.delay_ms(500);
    returnSteer();
    sys.delay_ms(500);
    setSteerAngle(-angle);
    sys.delay_ms(500);
    returnSteer();
    sys.delay_ms(500);
}

void testAccel() {
    hMot1.setPower(shake);
}

void allTests() {
    //testDrive();
    //testSteer(maxRightAngle);
    //sonoScanAndSet();
    for(;;) {
        testAccel();
        LED2.on(); sys.delay_ms(10); LED2.off(); sys.delay_ms(10);
    }
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
        shake = (int)(sqrt(sum_deviation/10)*500); // todo: change to actual shake
    }
}

void init() {
	sys.setLogDev(&Serial);
    returnSteer();
    sys.taskCreate(accelReadShake);
}

void hMain(void)
{
    init();
	for (;;)
	{
	    LED1.toggle();

	}
}
