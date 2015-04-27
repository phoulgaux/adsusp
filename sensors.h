#ifndef SENSORS_H_INCLUDED
#define SENSORS_H_INCLUDED

const int MinScannerDeclination = 30;
const int MaxScannerDeclination = 90;
const int ScanStep = 10;
int scanResult[2*(MaxScannerDeclination-MinScannerDeclination)/ScanStep+2];


#endif // SENSORS_H_INCLUDED
