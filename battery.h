#ifndef BATTERY_H
#define BATTERY_H

#include <stdio.h>  // Add this line to ensure printf is recognized

// Define structure for parameter limits and warning configuration
typedef struct {
    float lowerLimit;
    float upperLimit;
    float warningTolerance;  // Percentage for early warning
    int enableWarning;       // Flag to enable/disable warning
} ParameterLimits;

// Function declarations
int checkRange(float value, ParameterLimits limits, const char* paramName, const char* unit);
void checkWarning(float value, ParameterLimits limits, const char* paramName, const char* unit);
int batteryIsOk(float temperature, float soc, float chargeRate);

#endif
