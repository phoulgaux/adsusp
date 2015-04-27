#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "hMotor.h"

void setDrivePower(int power) {
    hMot1.setPower(power);
}

void setSteerAngle(int angle) {
    hMot2.rotAbs(angle);
}

#endif // MOTOR_H_INCLUDED
