/*
 * indicator.h
 *
 * Created: 26/04/2017 11:05:53
 *  Author: Rodolfo
 */ 


#ifndef INDICATOR_H_
#define INDICATOR_H_

#define F_CPU 11059200UL
#define BAUDRATE 9600UL

#define MAX_CALIBRATION_POINTS 10
#define FORCE_UNITS_LEN 8
#define TENSION_UNITS_LEN 4
#define MAX_SAMPLE 6
#define EPSILON 0.00001
#define BEEP_DURATION 0.1
#define OVERFLOW_BEEP_INTERVAL 8
#define SPEED_CALC_ARRAY_LENGTH 5

#define EEPROM_ADR_DISPLAY_UNIT_TYPE 0
#define EEPROM_ADR_DISPLAY_FORCE_UNIT EEPROM_ADR_DISPLAY_UNIT_TYPE + sizeof(char)
#define EEPROM_ADR_DISPLAY_TENSION_UNIT EEPROM_ADR_DISPLAY_FORCE_UNIT + sizeof(char)
#define EEPROM_ADR_CAL_POINTS EEPROM_ADR_DISPLAY_TENSION_UNIT + sizeof(char)
#define EEPROM_ADR_CAL_POINTS_VECTOR EEPROM_ADR_CAL_POINTS + sizeof(char)
#define EEPROM_ADR_CAL_UNIT EEPROM_ADR_CAL_POINTS_VECTOR + ((sizeof(long) + sizeof(float)) * MAX_CALIBRATION_POINTS)
#define EEPROM_ADR_SAMPLE EEPROM_ADR_CAL_UNIT + sizeof(char)
#define EEPROM_ADR_SAMPLE_VALUE1 EEPROM_ADR_SAMPLE + sizeof(char)
#define EEPROM_ADR_SAMPLE_VALUE2 EEPROM_ADR_SAMPLE_VALUE1 + sizeof(float)
#define EEPROM_ADR_SAMPLE_VALUE3 EEPROM_ADR_SAMPLE_VALUE2 + sizeof(float)
#define EEPROM_ADR_SAMPLE_AREA EEPROM_ADR_SAMPLE_VALUE3 + sizeof(float)
#define EEPROM_ADR_MACHINE_CAPACITY EEPROM_ADR_SAMPLE_AREA + sizeof(float)
#define EEPROM_ADR_OVERFLOW_PROTECTION_MODE EEPROM_ADR_MACHINE_CAPACITY + sizeof(float)
#define EEPROM_ADR_OVERFLOW_PROTECTION_THRESHOLD EEPROM_ADR_OVERFLOW_PROTECTION_MODE + sizeof(char)
#define EEPROM_ADR_OVERFLOW_PROTECTION_ENABLED EEPROM_ADR_OVERFLOW_PROTECTION_THRESHOLD + sizeof(char)

enum samples {SQUARE, RECTANGLE, CIRCLE, TUBE, TUBESECTOR, NONE};
enum dsplayUnitTypes {FORCE_UNIT, TENSION_UNIT};
enum forceUnits {KGF, TF, GF, N, KN, LBF};
enum tensionUnits {MPA, PSI, KGF_MM2, N_MM2};

typedef struct t_calibrationPoint CalibrationPoint;
struct t_calibrationPoint {
	long rawValue;
	float value;
};

typedef struct t_testSpeed TestSpeed;
struct t_testSpeed {
	long rawForceValue;
	unsigned int timeTick;
};

extern unsigned char currentPage;
extern unsigned char displayForceUnit;
extern unsigned char displayTensionUnit;
extern unsigned char displayUnitType;
extern unsigned char calibratedPoints;
extern unsigned char calibrationUnit;
extern CalibrationPoint calibrationPoints[MAX_CALIBRATION_POINTS];
extern CalibrationPoint *fisrtCalibrationPoint;

extern unsigned char sample;
extern float sampleValues[3], sampleArea;

extern float machineCapacity;
extern unsigned char overflowProtectionMode, overflowProtectionThreshold, overflowProtectionEnabled;

void enableGlobalInterrupt();
void disableGlobalInterrupt();

void initializeSystem();
void loadStoredParameters();

void processDisplayMessages();
void processSetDisplayUnit(const unsigned char *displayCommandBuffer);
void processGoToPage(const unsigned char *displayCommandBuffer);
void processSetPage(const unsigned char *displayCommandBuffer);
void processPointLock(const unsigned char *displayCommandBuffer);
void processChangeCalPoint(const unsigned char *displayCommandBuffer);
void processChangeCalUnit(const unsigned char *displayCommandBuffer);
void processNewCalibrationPoint(const unsigned char *displayCommandBuffer);
void processDeleteCalPoint(const unsigned char *displayCommandBuffer);
void processChangeSample(const unsigned char *displayCommandBuffer);
void processFloatVar(const unsigned char *displayCommandBuffer);
void processFloatVal(const unsigned char *displayCommandBuffer);
void processChangeDisplayUnit(const unsigned char *displayCommandBuffer);
void processChangeDisplayUnitType(const unsigned char *displayCommandBuffer);
void processChangeOverflowProtectionMode(const unsigned char *displayCommandBuffer);
void processChangeOverflowProtectionPercentage(const unsigned char *displayCommandBuffer);
void processToggleOverflowProtection(const unsigned char *displayCommandBuffer);
void processZeroCommand(const unsigned char *displayCommandBuffer);
void processClearPeakCommand(const unsigned char *displayCommandBuffer);
void processChangeHourCommand(const unsigned char *displayCommandBuffer);
void processChangeMinuteCommand(const unsigned char *displayCommandBuffer);
void processSetClockCommand(const unsigned char *displayCommandBuffer);

void sortCalibrationPoints();
void fitStraighLine();
float getAdjustedValue(long rawValue);

void addCalibrationPoint(CalibrationPoint p);
void deleteCalibrationPoint(unsigned char index);

float calculateSampleArea(unsigned char sample, float sample1, float sample2, float sample3);

void updateCalibrationPage();
void updateSamplePage();
void updateNewPointPage();
void updateNewPointDigitalValue();
void updateMainPage();
void updateMainNumbers();
void updateTemperature();
void updateDisplayUnit();
void updateCapacityPage();
void updateClockPage();

void clearFVarPointers();
void afterSetSampleValue();
void afterSetCapacityValue();
void calculateOverflowThresholdForce();
void checkMachineOverflow();

float getAdjustedForceValue(long lastAdData, unsigned char calibrationUnit, unsigned char displayForceUnit);
float getAdjustedTensionValue(long lastAdData, unsigned char calibrationUnit, float sampleArea, unsigned char displayTensionUnit);
float convertForceValue(float v, unsigned char fromForceUnit, unsigned char toForceUnit);
float getForceConversionFactor(unsigned char fromForceUnit, unsigned char toForceUnit);
float convertTensionValue(float v, unsigned char fromTensionUnit, unsigned char toTensionUnit);
float convertForceToTension(float forceValue, unsigned char forceUnit, float sampleArea, unsigned char tensionUnit);
float getTensionConversionFactor(unsigned char fromTensionUnit, unsigned char toTensionUnit);

float getMainDisplayValue();
const unsigned char* getDisplayUnitStr();

void initiliazeTimerTicker();
void startTimerTicker();
void stopTimerTicker();

#endif /* INDICATOR_H_ */