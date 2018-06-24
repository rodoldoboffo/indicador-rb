/*
 * myeeprom.c
 *
 * Created: 02/07/2017 13:55:49
 *  Author: Rodolfo
 */ 

#include "indicator.h"
#include <math.h>
#include <avr/eeprom.h>

 void storeCalibrationPoints(CalibrationPoint* points, unsigned char qtyPoints) {
	 unsigned char i;
	 eeprom_write_byte((uint8_t *)EEPROM_ADR_CAL_POINTS, qtyPoints);
	 for (i=0; i<qtyPoints; i++) {
		 eeprom_write_dword((uint32_t *)(EEPROM_ADR_CAL_POINTS_VECTOR + (i*8)), points[i].rawValue);
		 eeprom_write_float((float*)(EEPROM_ADR_CAL_POINTS_VECTOR + (i*8) + 4), points[i].value);
	 }
 }

 void storeCalibrationUnit(unsigned char calUnit) {
	 eeprom_write_byte((uint8_t *)EEPROM_ADR_CAL_UNIT, calUnit);
 }

 void storeDisplayForceUnit(unsigned char u) {
	 eeprom_write_byte((uint8_t *)EEPROM_ADR_DISPLAY_FORCE_UNIT, u);
 }

 void storeDisplayUnitType(unsigned char t) {
	 eeprom_write_byte((uint8_t *)EEPROM_ADR_DISPLAY_UNIT_TYPE, t);
 }

 void storeDisplayTensionUnit(unsigned char u) {
	 eeprom_write_byte((uint8_t *)EEPROM_ADR_DISPLAY_TENSION_UNIT, u);
 }

 void storeSample(unsigned char s) {
	 eeprom_write_byte((uint8_t *)EEPROM_ADR_SAMPLE, s);
 }

 void storeSampleValues() {
	 unsigned char i;
	 for (i=0; i<3; i++) {
		 eeprom_write_float((float*)(EEPROM_ADR_SAMPLE_VALUE1+(i*sizeof(float))), sampleValues[i]);
	 }
	 eeprom_write_float((float*)(EEPROM_ADR_SAMPLE_AREA), sampleArea);
 }

 void storeMachineCapacity() {
	 eeprom_write_float((float*)(EEPROM_ADR_MACHINE_CAPACITY), machineCapacity);
 }

 void storeOverflowProtectionDetails() {
	 eeprom_write_byte((uint8_t*)(EEPROM_ADR_OVERFLOW_PROTECTION_MODE), overflowProtectionMode);
	 eeprom_write_byte((uint8_t*)(EEPROM_ADR_OVERFLOW_PROTECTION_THRESHOLD), overflowProtectionThreshold);
	 eeprom_write_byte((uint8_t*)(EEPROM_ADR_OVERFLOW_PROTECTION_ENABLED), overflowProtectionEnabled);
 }
 
 unsigned char loadDisplayUnitType() {
	 displayUnitType = eeprom_read_byte((uint8_t*)EEPROM_ADR_DISPLAY_UNIT_TYPE);
	 if (displayUnitType >= 2)
	 displayUnitType = 0;
	 return displayUnitType;
 }

 unsigned char loadDisplayForceUnit() {
	 displayForceUnit = eeprom_read_byte((uint8_t*)EEPROM_ADR_DISPLAY_FORCE_UNIT);
	 if (displayForceUnit >= FORCE_UNITS_LEN)
	 displayForceUnit = 0;
	 return displayForceUnit;
 }

 unsigned char loadDisplayTensionUnit() {
	 displayTensionUnit = eeprom_read_byte((uint8_t*)EEPROM_ADR_DISPLAY_TENSION_UNIT);
	 if (displayTensionUnit >= TENSION_UNITS_LEN)
	 displayTensionUnit = 0;
	 return displayTensionUnit;
 }

 unsigned char loadSample() {
	 sample = eeprom_read_byte((uint8_t*)EEPROM_ADR_SAMPLE);
	 if (sample >= MAX_SAMPLE)
	 sample = 0;
	 return sample;
 }

 void loadSampleValues() {
	 unsigned char i;
	 for (i=0; i<3; i++) {
		sampleValues[i] = eeprom_read_float((float*)(EEPROM_ADR_SAMPLE_VALUE1+(i*sizeof(float))));
		if (isnan(sampleValues[i]))
			sampleValues[i] = 1.0;
	 }
	 sampleArea = eeprom_read_float((float*)(EEPROM_ADR_SAMPLE_AREA));
	 if (isnan(sampleArea) || sampleArea < EPSILON)
		sampleArea = 1.0;
 }

 void loadMachineCapacity() {
	 machineCapacity = eeprom_read_float((float*)(EEPROM_ADR_MACHINE_CAPACITY));
	 if (isnan(machineCapacity))
	 machineCapacity = 1000.0;
	 calculateOverflowThresholdForce();
 }

 void loadOverflowProtectionDetails() {
	 overflowProtectionMode = eeprom_read_byte((uint8_t*)EEPROM_ADR_OVERFLOW_PROTECTION_MODE);
	 if (overflowProtectionMode >= 2)
	 overflowProtectionMode = 0;

	 overflowProtectionThreshold = eeprom_read_byte((uint8_t*)EEPROM_ADR_OVERFLOW_PROTECTION_THRESHOLD);
	 if (overflowProtectionThreshold > 100)
	 overflowProtectionThreshold = 80U;
	 calculateOverflowThresholdForce();

	 overflowProtectionEnabled = eeprom_read_byte((uint8_t*)EEPROM_ADR_OVERFLOW_PROTECTION_ENABLED);
	 if (overflowProtectionEnabled > 1)
	 overflowProtectionEnabled = 0U;
 }

 unsigned char loadNumCalibratedPoints() {
	 calibratedPoints = eeprom_read_byte((uint8_t*)EEPROM_ADR_CAL_POINTS);
	 if (calibratedPoints > 10)
	 calibratedPoints = 0;
	 return calibratedPoints;
 }

 unsigned char loadCalibrationUnit() {
	 calibrationUnit = eeprom_read_byte((uint8_t*)EEPROM_ADR_CAL_UNIT);
	 if (calibrationUnit >= FORCE_UNITS_LEN)
	 calibrationUnit = 0;
	 return calibrationUnit;
 }

 void loadCalibrationPoint(unsigned char index) {
	 unsigned long adRawValue = eeprom_read_dword((uint32_t*)(EEPROM_ADR_CAL_POINTS_VECTOR+(index*8)));
	 float calibrationValue = eeprom_read_float((float*)(EEPROM_ADR_CAL_POINTS_VECTOR+(index*8)+4));
	 CalibrationPoint p;
	 p.rawValue = adRawValue;
	 p.value = calibrationValue;
	 calibrationPoints[index] = p;
 }
