#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

#include "hFramework.h"

#include "motor.h"

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
    setSteerAngle(0);
    sys.delay_ms(500);
    setSteerAngle(angle);
    sys.delay_ms(500);
    setSteerAngle(0);
    sys.delay_ms(500);
    setSteerAngle(-angle);
    sys.delay_ms(500);
    setSteerAngle(0);
    sys.delay_ms(500);
}

void allTests() {
    testDrive();
    testSteer(20);
    testSteer(60);
    testSteer(90);
}

#endif // TESTS_H_INCLUDED
