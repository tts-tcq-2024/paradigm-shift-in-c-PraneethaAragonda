// Helper function for early warning
void checkWarning(float value, ParameterLimits limits, const char* paramName, const char* unit) {
    if (!limits.enableWarning) {
        return;  // Warning disabled for this parameter
    }

    float warningLower = limits.lowerLimit + limits.warningTolerance;
    float warningUpper = limits.upperLimit - limits.warningTolerance;

    // Use a single function to handle warnings both for low and high thresholds
    void printWarning(const char* message, float value) {
        printf("Warning: %s approaching %s threshold! %.2f %s\n", paramName, message, value, unit);
    }

    if (value >= limits.lowerLimit && value <= warningLower) {
        printWarning("low", value);
    }

    if (value >= warningUpper && value <= limits.upperLimit) {
        printWarning("high", value);
    }
}
