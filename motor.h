#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "hMotor.h"

const int maxRightAngle = 80;
const int maxLeftAngle = -maxRightAngle;

void setDrivePower(int power) {
    hMot1.setPower(power);
}

void setSteerAngle(int angle) {
    hMot2.rotAbs(angle);
}

void returnSteer() {setSteerAngle(0);}

#endif // MOTOR_H_INCLUDED
