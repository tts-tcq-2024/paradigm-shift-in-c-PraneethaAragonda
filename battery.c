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

// Helper function to print a warning
void printWarning(const char* message, float value, const char* paramName, const char* unit) {
    printf("Warning: %s approaching %s threshold! %.2f %s\n", paramName, message, value, unit);
}

// Refactored checkWarning function to reduce CCN
void checkWarning(float value, ParameterLimits limits, const char* paramName, const char* unit) {
    if (!limits.enableWarning) {
        return;  // Warning disabled for this parameter
    }

    // Calculate the warning thresholds
    float warningLower = limits.lowerLimit + limits.warningTolerance;
    float warningUpper = limits.upperLimit - limits.warningTolerance;

    // Check for low warning condition
    if (value >= limits.lowerLimit && value <= warningLower) {
        printWarning("low", value, paramName, unit);
    }

    // Check for high warning condition
    if (value >= warningUpper && value <= limits.upperLimit) {
        printWarning("high", value, paramName, unit);
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

