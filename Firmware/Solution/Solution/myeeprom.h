/*
 * myeeprom.h
 *
 * Created: 02/07/2017 13:56:05
 *  Author: Rodolfo
 */ 


#ifndef MYEEPROM_H_
#define MYEEPROM_H_

void storeCalibrationPoints(CalibrationPoint* points, unsigned char qtyPoints);
void storeCalibrationUnit(unsigned char calUnit);
void storeDisplayUnitType(unsigned char unitType);
void storeDisplayForceUnit(unsigned char calUnit);
void storeDisplayTensionUnit(unsigned char calUnit);
void storeSample(unsigned char selectedSample);
void storeSampleValues();
void storeMachineCapacity();
void storeOverflowProtectionDetails();

unsigned char loadNumCalibratedPoints();
unsigned char loadDisplayUnitType();
unsigned char loadDisplayForceUnit();
unsigned char loadDisplayTensionUnit();
unsigned char loadSample();
void loadSampleValues();
unsigned char loadCalibrationUnit();
void loadCalibrationPoint(unsigned char index);
void loadMachineCapacity();
void loadOverflowProtectionDetails();

#endif /* MYEEPROM_H_ */