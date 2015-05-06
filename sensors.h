#ifndef SENSORS_H_INCLUDED
#define SENSORS_H_INCLUDED

#include "motor.h"

const int scanResolution = 10;
const int scanStep = (maxRightAngle - maxLeftAngle) / scanResolution;

Lego_Ultrasonic sono(hSens1);

int sonoScanAndSet() {
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

#endif // SENSORS_H_INCLUDED
