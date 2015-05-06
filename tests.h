#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

#include "hFramework.h"

#include "motor.h"
#include "sensors.h"

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

void allTests() {
    testDrive();
    testSteer(maxRightAngle);
    sonoScanAndSet();
}

#endif // TESTS_H_INCLUDED
