//
// Created by alvaro on 26/07/15.
//

#ifndef PRUEBA_PLAT_VOLTMETER_H
#define PRUEBA_PLAT_VOLTMETER_H
#include "Arduino.h"

class VoltMeter {
private:
    
public:
    int _readPin;
    float _r1;
    float _r2;
    float _referenceVoltage;
    VoltMeter(float r1, float r2, float referenceVoltage=5);
    float getVoltage();
	void Setup_Voltage(int readPin);
};


#endif //PRUEBA_PLAT_VOLTMETER_H
