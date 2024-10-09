#include <stdio.h>
#include "battery.h"

// Helper function for range checking
int checkRange(float value, ParameterLimits limits, const char* paramName, const char* unit) {
    if (value < limits.lowerLimit) {
        printf("%s too low! %.2f %s\n", paramName, value, unit);
        return 0;
    }
    if (value > limits.upperLimit) {
        printf("%s too high! %.2f %s\n", paramName, value, unit);
        return 0;
    }
    return 1;
}

// Helper function for early warning
void checkWarning(float value, ParameterLimits limits, const char* paramName, const char* unit) {
    if (!limits.enableWarning) {
        return;  // Warning disabled for this parameter
    }

    float warningLower = limits.lowerLimit + limits.warningTolerance;
    float warningUpper = limits.upperLimit - limits.warningTolerance;

    if (value >= limits.lowerLimit && value <= warningLower) {
        printf("Warning: %s approaching low threshold! %.2f %s\n", paramName, value, unit);
    }
    if (value >= warningUpper && value <= limits.upperLimit) {
        printf("Warning: %s approaching high threshold! %.2f %s\n", paramName, value, unit);
    }
}

// Main function to check if battery is OK
int batteryIsOk(float temperature, float soc, float chargeRate) {
    // Centralized configuration for each parameter
    ParameterLimits tempLimits = {0, 45, 2.25, 1};    // Warnings enabled for temperature
    ParameterLimits socLimits = {20, 80, 4, 1};       // Warnings enabled for SoC
    ParameterLimits chargeLimits = {0, 0.8, 0.04, 1}; // Warnings enabled for charge rate

    // Range checks
    int isTempOk = checkRange(temperature, tempLimits, "Temperature", "°C");
    int isSocOk = checkRange(soc, socLimits, "State of Charge", "%");
    int isChargeRateOk = checkRange(chargeRate, chargeLimits, "Charge Rate", "C");

    // Warning checks only if warnings are enabled for each parameter
    checkWarning(temperature, tempLimits, "Temperature", "°C");
    checkWarning(soc, socLimits, "State of Charge", "%");
    checkWarning(chargeRate, chargeLimits, "Charge Rate", "C");

    // Return true if all parameters are within valid range
    return isTempOk && isSocOk && isChargeRateOk;
}
