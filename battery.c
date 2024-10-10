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

// Function to check warning conditions with reduced complexity
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
int batteryIsOk(float temperature, float soc, float chargeRate, 
                int checkTemp, int checkSoc, int checkChargeRate) {
    // Centralized configuration for each parameter
    ParameterLimits tempLimits = {0, 45, 2.25, 1};    // Warnings enabled for temperature
    ParameterLimits socLimits = {20, 80, 4, 1};       // Warnings enabled for SoC
    ParameterLimits chargeLimits = {0, 0.8, 0.04, 1}; // Warnings enabled for charge rate

    // Initialize status to true
    int status = 1;

    // Range checks based on which parameters to check
    if (checkTemp) {
        int isTempOk = checkRange(temperature, tempLimits, "Temperature", "°C");
        checkWarning(temperature, tempLimits, "Temperature", "°C");
        status &= isTempOk;  // Combine the result with status
    }

    if (checkSoc) {
        int isSocOk = checkRange(soc, socLimits, "State of Charge", "%");
        checkWarning(soc, socLimits, "State of Charge", "%");
        status &= isSocOk;  // Combine the result with status
    }

    if (checkChargeRate) {
        int isChargeRateOk = checkRange(chargeRate, chargeLimits, "Charge Rate", "C");
        checkWarning(chargeRate, chargeLimits, "Charge Rate", "C");
        status &= isChargeRateOk;  // Combine the result with status
    }

    // Return true (1) if all checked parameters are within range, false (0) otherwise
    return status;
}

int main() {
    // Test case 1: Checking all parameters
    int result1 = batteryIsOk(30, 50, 0.6, 1, 1, 1);
    printf("Battery check result (all parameters): %d\n", result1);

    // Test case 2: Only checking SoC
    int result2 = batteryIsOk(30, 90, 0.6, 0, 1, 0);  // Only checking SoC
    printf("Battery check result (only SoC): %d\n", result2);

    // Test case 3: Checking Temperature and Charge Rate
    int result3 = batteryIsOk(50, 50, 0.9, 1, 0, 1);  // Only checking Temperature and Charge Rate
    printf("Battery check result (Temp and Charge Rate): %d\n", result3);

    return 0;
}
