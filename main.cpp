/* External devices
[+] hMot1: drive
[+] hMot2: steer/sono
[-] hMot3: elevation
[!] hSens1: sono (obstacles)
[-] hSens2: camera (ground roughness)
[?] hSens3: accel (additional roughness)
*/

#include <stdio.h>

#include "hFramework.h"
#include "Lego_Ultrasonic.h"
#include "hMotor.h"

using namespace hFramework;
using namespace hSensors;

// own headers
#include "motor.h"
#include "tests.h"

Lego_Ultrasonic sono(hSens1);

void init() {
	sys.setLogDev(&Serial);
    setSteerAngle(0);
}

void hMain(void)
{
	for (;;)
	{
	    LED1.on();
		allTests();
		LED1.off();
		sys.delay_ms(2000);
	}
}
