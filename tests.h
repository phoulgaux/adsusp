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
    sys.delay_ms(500);
    testSteer(20);
    sys.delay_ms(500);
    testSteer(60);
    sys.delay_ms(500);
    testSteer(90);
    sys.delay_ms(500);
}

#endif // TESTS_H_INCLUDED
