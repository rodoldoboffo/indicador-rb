/*
 * prc.c
 *
 * Created: 26/04/2017 16:45:26
 *  Author: Rodolfo
 */ 
//
 #include "mystdlib.h"
 #include "mystring.h"
 #include "indicator.h"
 #include "serial.h"
 #include "software_uart.h"
 #include "software_uart_ble.h"
 #include "nx4832t035.h"
 #include "ads1231.h"
 #include "myeeprom.h"
 #include "passive_buzzer.h"
 #include "ssr.h"
 #include "least_square.h"
 #include "ds3231.h"

 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include <util/delay.h>
 #include <avr/common.h>
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <time.h>

 const unsigned char UNIT_COMMAND[] = "unit=";
 const unsigned char PAGE_COMMAND[] = "page=";
 const unsigned char CHANGE_CALIBRATION_UNIT_COMMAND[] = "cal_unit=";
 const unsigned char CHANGE_DISPLAY_UNIT_COMMAND[] = "disp_unit=";
 const unsigned char CHANGE_DISPLAY_UNIT_TYPE_COMMAND[] = "disp_unit_t=";
 const unsigned char POINT_LOCKED_COMMAND[] = "plock";
 const unsigned char GO_TO_COMMAND[] = "goto=";
 const unsigned char CONFIRM_NEW_POINT_COMMAND[] = "cal=";
 const unsigned char CHANGE_CALIBRATION_POINT_COMMAND[] = "point=";
 const unsigned char CHANGE_SAMPLE_COMMAND[] = "sample=";
 const unsigned char DELETE_CALIBRATION_POINT_COMMAND[] = "delp=";
 const unsigned char FLOAT_VAR_COMMAND[] = "fvar=";
 const unsigned char FLOAT_VAL_COMMAND[] = "fval=";
 const unsigned char FLOAT_VAL_CANCEL_COMMAND[] = "fcancel";
 const unsigned char OVERFLOW_PROTECTION_MODE_COMMAND[] = "ovfmode=";
 const unsigned char OVERFLOW_PROTECTION_PERCENTAGE_COMMAND[] = "ovfpct=";
 const unsigned char TOGGLE_OVERFLOW_PROTECTION_COMMAND[] = "ovfchk=";
 const unsigned char ZERO_COMMAND[] = "zero";
 const unsigned char CLEAR_PEAK_COMMAND[] = "clpk";
 const unsigned char CHANGE_HOUR_COMMAND[] = "hour=";
 const unsigned char CHANGE_MINUTE_COMMAND[] = "min=";
 const unsigned char SET_CLOCK_COMMAND[] = "clk=";
 const unsigned char READY[] = "ready\n";
 
 const unsigned char forceUnitsString[][5] = {
	"kgf",
	"tf",
	"gf",
	"N",
	"kN",
	"lbf"
 };

 const unsigned char tensionUnitsString[][10] = {"MPa", "psi", "kgf/mm2", "N/mm2"};

 unsigned char currentPage = WAIT_PAGE;
 unsigned char displayUnitType = FORCE_UNIT;
 unsigned char displayForceUnit = 0;
 unsigned char displayTensionUnit = 0;
 unsigned char selectedPoint = 0;
 unsigned char calibratedPoints = 0;
 unsigned char calibrationUnit = 0;
 long int lastAdData = 0L;
 float peakForceValue = 0.0;
 unsigned char adFetchStop = 0;
 float newPointValue = 0.0;

 CalibrationPoint calibrationPoints[MAX_CALIBRATION_POINTS];
 unsigned char sortedCalibrationPoints[MAX_CALIBRATION_POINTS];
 float fittedStraightLineCoef[2] = {0.0, 1.0};

 unsigned char sample = 0;
 float sampleValues[3] = {0.0, 0.0, 0.0}, sampleArea = 1.0;

 float machineCapacity = 1000.0;
 unsigned char overflowProtectionMode = 0, overflowProtectionThreshold = 80U;
 float overflowThresholdForce = 1000.0;
 unsigned char overflowBeepCounter = 0, overflowProtectionEnabled = 0;

 TestSpeed testSpeedCalculationArray[SPEED_CALC_ARRAY_LENGTH];
 unsigned char testSpeedCalcArrayIndex = 0;
 unsigned long timerTick = 0UL;
 long lastTestSpeed = 0L;

 struct tm tempTime;

 float *fVarPtr;
 void (*fVarCallbackPtr)();

 ISR(TIMER0_COMPA_vect)
 {
	 timerTick++;
 }

 void enableGlobalInterrupt() {
	SREG |= (1<<SREG_I);
 }

 void disableGlobalInterrupt() {
	 SREG &= ~((1<<SREG_I));
 }

void initializeSystem() {
	initializeBuzzer();
	initSoftwareUARTSend();
	initSoftwareUARTReceive();
	initBleUARTSend();
	initBleUARTReceive();
	//serialInitialize(BAUDRATE);
	adcInitialize(0);
	loadStoredParameters();
	clearFVarPointers();
	initializeRelay(!overflowProtectionMode);
	_delay_ms(800);

	initiliazeTimerTicker();
	startTimerTicker();

	softwareSerialPrint(READY);
}

void initiliazeTimerTicker() {
	TCCR0A = (1<<WGM01);
	TCCR0B = 0;
	TCNT0 = 0;
	OCR0A = 0x6C;
	TIMSK0 = (1<<OCIE0A);
	enableGlobalInterrupt();
}

void startTimerTicker() {
	TCCR0B |= ((1<<CS00) | (1<<CS02));
}

void stopTimerTicker() {
	TCCR0B &= ((~(1<<CS00)) & (~(1<<CS02)));
}

void processBLEMessages() {
	unsigned char displayCommandBuffer[36];
	while (serialFind(';') != -1) {
		serialBufferReadUntil(';', displayCommandBuffer);
		#ifdef DEBUG
		softwareSerialPrint("Command Buffer:\n");
		softwareSerialPrint(displayCommandBuffer);
		softwareSerialPrint("\n");
		#endif
		if ((unsigned char *)strstr(displayCommandBuffer, UNIT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processSetDisplayUnit(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, GO_TO_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processGoToPage(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, PAGE_COMMAND) == displayCommandBuffer) {
			processSetPage(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, POINT_LOCKED_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processPointLock(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CONFIRM_NEW_POINT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processNewCalibrationPoint(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_CALIBRATION_POINT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeCalPoint(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_CALIBRATION_UNIT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeCalUnit(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, DELETE_CALIBRATION_POINT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processDeleteCalPoint(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_SAMPLE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeSample(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, FLOAT_VAR_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processFloatVar(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, FLOAT_VAL_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processFloatVal(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_DISPLAY_UNIT_TYPE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeDisplayUnitType(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_DISPLAY_UNIT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeDisplayUnit(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, OVERFLOW_PROTECTION_MODE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeOverflowProtectionMode(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, OVERFLOW_PROTECTION_PERCENTAGE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeOverflowProtectionPercentage(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, TOGGLE_OVERFLOW_PROTECTION_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processToggleOverflowProtection(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, ZERO_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processZeroCommand(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CLEAR_PEAK_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processClearPeakCommand(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_HOUR_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeHourCommand(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_MINUTE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeMinuteCommand(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, SET_CLOCK_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processSetClockCommand(displayCommandBuffer);
		}
	}
}

void processDisplayMessages() {
	unsigned char displayCommandBuffer[36];
	while (serialFind(';') != -1) {
		serialBufferReadUntil(';', displayCommandBuffer);
		#ifdef DEBUG
		softwareSerialPrint("Command Buffer:\n");
		softwareSerialPrint(displayCommandBuffer);
		softwareSerialPrint("\n");
		#endif
		if ((unsigned char *)strstr(displayCommandBuffer, UNIT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processSetDisplayUnit(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, GO_TO_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processGoToPage(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, PAGE_COMMAND) == displayCommandBuffer) {
			processSetPage(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, POINT_LOCKED_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processPointLock(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CONFIRM_NEW_POINT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processNewCalibrationPoint(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_CALIBRATION_POINT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeCalPoint(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_CALIBRATION_UNIT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeCalUnit(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, DELETE_CALIBRATION_POINT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processDeleteCalPoint(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_SAMPLE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeSample(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, FLOAT_VAR_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processFloatVar(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, FLOAT_VAL_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processFloatVal(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_DISPLAY_UNIT_TYPE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeDisplayUnitType(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_DISPLAY_UNIT_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeDisplayUnit(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, OVERFLOW_PROTECTION_MODE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeOverflowProtectionMode(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, OVERFLOW_PROTECTION_PERCENTAGE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeOverflowProtectionPercentage(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, TOGGLE_OVERFLOW_PROTECTION_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processToggleOverflowProtection(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, ZERO_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processZeroCommand(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CLEAR_PEAK_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processClearPeakCommand(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_HOUR_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeHourCommand(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, CHANGE_MINUTE_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processChangeMinuteCommand(displayCommandBuffer);
		}
		else if ((unsigned char *)strstr(displayCommandBuffer, SET_CLOCK_COMMAND) == displayCommandBuffer) {
			playLowBuzz(BEEP_DURATION);
			processSetClockCommand(displayCommandBuffer);
		}
	}
}

void processSetClockCommand(const unsigned char *displayCommandBuffer) {
	if (strstr(displayCommandBuffer, "ok") != 0) {
		ds3231SetTimeDateFromTm(&tempTime);
	}
	displayShowPage(CONFIG_PAGE_NAME);
}

void processChangeHourCommand(const unsigned char *displayCommandBuffer) {
	if (strstr(displayCommandBuffer, "++") != 0) {
		tempTime.tm_hour++;
	}
	else if (strstr(displayCommandBuffer, "--") != 0) {
		tempTime.tm_hour--;
	}
	tempTime.tm_hour = tempTime.tm_hour % 24;
	updateClockPage();
}

void processChangeMinuteCommand(const unsigned char *displayCommandBuffer) {
	if (strstr(displayCommandBuffer, "++") != 0) {
		tempTime.tm_min++;
	}
	else if (strstr(displayCommandBuffer, "--") != 0) {
		tempTime.tm_min--;
	}
	tempTime.tm_min = tempTime.tm_min % 60;
	updateClockPage();
}

void processToggleOverflowProtection(const unsigned char *displayCommandBuffer) {
	if (strstr(displayCommandBuffer, "++") != 0) {
		overflowProtectionEnabled = (overflowProtectionEnabled + 1 + 2) % 2;
	}
	//#ifdef DEBUG
	//softwareSerialPrint("Overflow Protection Enabled: ");
	//softwareSerialPrintInt(overflowProtectionEnabled);
	//softwareSerialPrint("\n");
	//#endif
	storeOverflowProtectionDetails();
	updateCapacityPage();
}

void processZeroCommand(const unsigned char *displayCommandBuffer) {
	if (calibratedPoints >= 2) {
		float zeroIntersection = getAdjustedForceValue(lastAdData, calibrationUnit, calibrationUnit);
		fittedStraightLineCoef[0] -= zeroIntersection;
	}
	updateMainNumbers();
}

void processClearPeakCommand(const unsigned char *displayCommandBuffer) {
	peakForceValue = 0.0;
	updateMainNumbers();
}

void processChangeOverflowProtectionMode(const unsigned char *displayCommandBuffer) {
	unsigned char * overflowModeString = (unsigned char *)(&(displayCommandBuffer[strlen(OVERFLOW_PROTECTION_MODE_COMMAND)]));
	replace(overflowModeString, ';', 0);
	overflowProtectionMode = atoi(overflowModeString);
	#ifdef DEBUG
	softwareSerialPrint("Overflow Protection Mode: ");
	softwareSerialPrintInt(overflowProtectionMode);
	softwareSerialPrint("\n");
	#endif
	storeOverflowProtectionDetails();
	updateCapacityPage();
}

void processChangeOverflowProtectionPercentage(const unsigned char *displayCommandBuffer) {
	unsigned long *percentagePointer = (unsigned long *)(&displayCommandBuffer[strlen(OVERFLOW_PROTECTION_PERCENTAGE_COMMAND)]);
	unsigned long percentageValue = (unsigned long)(*percentagePointer);
	overflowProtectionThreshold = percentageValue;
	#ifdef DEBUG
	softwareSerialPrint("Overflow Protection Threshold: ");
	softwareSerialPrintInt(percentageValue);
	softwareSerialPrint("%\n");
	#endif
	storeOverflowProtectionDetails();
	calculateOverflowThresholdForce();
	updateCapacityPage();
}

void processGoToPage(const unsigned char *displayCommandBuffer) {
	unsigned char gotoPage = currentPage;
	unsigned char * gotoPageString = (unsigned char *)(&(displayCommandBuffer[strlen(GO_TO_COMMAND)]));
	replace(gotoPageString, ';', 0);
	gotoPage = atoi(gotoPageString);
	if (gotoPage != currentPage) {
		currentPage = 0xFF;
		displayShowPage(gotoPageString);
	}
	#ifdef DEBUG
	softwareSerialPrint("Go to page: ");
	softwareSerialPrintInt(gotoPage);
	softwareSerialPrint("\n");
	#endif
}

void processChangeCalPoint(const unsigned char *displayCommandBuffer) {
	unsigned char oldSelectedPoint = selectedPoint;
	if (calibratedPoints > 0) {
		if (strstr(displayCommandBuffer, "--") != 0) {
			selectedPoint = (selectedPoint - 1 + calibratedPoints) % calibratedPoints;
		}
		else if (strstr(displayCommandBuffer, "++") != 0) {
			selectedPoint = (selectedPoint + 1 + calibratedPoints) % calibratedPoints;
		}
	}
	if (oldSelectedPoint != selectedPoint)
		updateCalibrationPage();
}

void processChangeSample(const unsigned char *displayCommandBuffer) {
	unsigned char i;
	if (strstr(displayCommandBuffer, "--") != 0) {
		sample = (sample - 1) % MAX_SAMPLE;
	}
	else if (strstr(displayCommandBuffer, "++") != 0) {
		sample = (sample + 1) % MAX_SAMPLE;
	}
	for (i=0; i<3; i++) {
		sampleValues[i] = 1.0;
	}
	sampleArea = calculateSampleArea(sample, sampleValues[0], sampleValues[1], sampleValues[2]);
	storeSample(sample);
	storeSampleValues();
	updateSamplePage();
}

void processChangeCalUnit(const unsigned char *displayCommandBuffer) {
	if (strstr(displayCommandBuffer, "--") != 0) {
		calibrationUnit = (calibrationUnit - 1 + FORCE_UNITS_LEN) % FORCE_UNITS_LEN;
	}
	else if (strstr(displayCommandBuffer, "++") != 0) {
		calibrationUnit = (calibrationUnit + 1 + FORCE_UNITS_LEN) % FORCE_UNITS_LEN;
	}
	#ifdef DEBUG
	softwareSerialPrint("Cal Unit: ");
	softwareSerialPrint(forceUnitsString[calibrationUnit]);
	softwareSerialPrint("\n");
	#endif
	storeCalibrationUnit(calibrationUnit);
	updateCalibrationPage();
}

void processChangeDisplayUnitType(const unsigned char *displayCommandBuffer) {
	if (strstr(displayCommandBuffer, "++") != 0) {
		displayUnitType = (displayUnitType + 1 + 2) % 2;
	}
	storeDisplayUnitType(displayUnitType);
	updateMainPage();
}

void processChangeDisplayUnit(const unsigned char *displayCommandBuffer) {
	if (displayUnitType == FORCE_UNIT) {
		if (strstr(displayCommandBuffer, "--") != 0) {
			displayForceUnit = (displayForceUnit - 1 + FORCE_UNITS_LEN) % FORCE_UNITS_LEN;
		}
		else if (strstr(displayCommandBuffer, "++") != 0) {
			displayForceUnit = (displayForceUnit + 1 + FORCE_UNITS_LEN) % FORCE_UNITS_LEN;
		}
		storeDisplayForceUnit(displayForceUnit);
	}
	else {
		if (strstr(displayCommandBuffer, "--") != 0) {
			displayTensionUnit = (displayTensionUnit - 1 + TENSION_UNITS_LEN) % TENSION_UNITS_LEN;
		}
		else if (strstr(displayCommandBuffer, "++") != 0) {
			displayTensionUnit = (displayTensionUnit + 1 + TENSION_UNITS_LEN) % TENSION_UNITS_LEN;
		}
		storeDisplayTensionUnit(displayTensionUnit);
	}
	//#ifdef DEBUG
	//if (displayUnitType == FORCE_UNIT) {
		//softwareSerialPrint("Display Force Unit: ");
		//softwareSerialPrint(forceUnitsString[displayForceUnit]);
	//}
	//else {
		//softwareSerialPrint("Display Tension Unit: ");
		//softwareSerialPrint(tensionUnitsString[displayTensionUnit]);
	//}
	//softwareSerialPrint("\n");
	//#endif
	updateMainPage();
}

void clearTestSpeedCalculation() {
	testSpeedCalcArrayIndex = 0;
	for (unsigned char i = 0; i < SPEED_CALC_ARRAY_LENGTH; i++) {
		testSpeedCalculationArray[i].rawForceValue = 0;
		testSpeedCalculationArray[i].timeTick = 0;
	}
}

long calculateTestSpeed() {
	long result = 0L;
	if (testSpeedCalculationArray[(testSpeedCalcArrayIndex-1+SPEED_CALC_ARRAY_LENGTH)%SPEED_CALC_ARRAY_LENGTH].timeTick != 0 && testSpeedCalculationArray[(testSpeedCalcArrayIndex+SPEED_CALC_ARRAY_LENGTH)%SPEED_CALC_ARRAY_LENGTH].timeTick != 0) {
		result = (testSpeedCalculationArray[(testSpeedCalcArrayIndex-1+SPEED_CALC_ARRAY_LENGTH)%SPEED_CALC_ARRAY_LENGTH].rawForceValue - testSpeedCalculationArray[(testSpeedCalcArrayIndex+SPEED_CALC_ARRAY_LENGTH)%SPEED_CALC_ARRAY_LENGTH].rawForceValue) /
			(testSpeedCalculationArray[(testSpeedCalcArrayIndex-1+SPEED_CALC_ARRAY_LENGTH)%SPEED_CALC_ARRAY_LENGTH].timeTick - testSpeedCalculationArray[(testSpeedCalcArrayIndex+SPEED_CALC_ARRAY_LENGTH)%SPEED_CALC_ARRAY_LENGTH].timeTick);
		result *= 100;
	}
	lastTestSpeed = result;
	return result;
}

void processSetPage(const unsigned char *displayCommandBuffer) {
	if (strstr(displayCommandBuffer, MAIN_PAGE_NAME) != 0) {
		currentPage = MAIN_PAGE;
		lastTestSpeed = 0L;
		clearTestSpeedCalculation();
		updateMainPage();
	}
	else if (strstr(displayCommandBuffer, CALIBRATION_PAGE_NAME) != 0) {
		currentPage = CALIBRATION_PAGE;
		updateCalibrationPage();
	}
	else if (strstr(displayCommandBuffer, CAPACITY_PAGE_NAME) != 0) {
		currentPage = CAPACITY_PAGE;
		updateCapacityPage();
	}
	else if (strstr(displayCommandBuffer, MENU_PAGE_NAME) != 0) {
		currentPage = MENU_PAGE;
	}
	else if (strstr(displayCommandBuffer, SAMPLE_PAGE_NAME) != 0) {
		if (currentPage != SAMPLE_PAGE) {
			currentPage = SAMPLE_PAGE;
			updateSamplePage();
		}
	}
	else if (strstr(displayCommandBuffer, NEW_POINT_PAGE_NAME) != 0) {
		if (currentPage != NEW_POINT_PAGE) {
			currentPage = NEW_POINT_PAGE;
			newPointValue = 0.0;
			lastAdData = 0UL;
			adFetchStop = 0;
		}
		updateNewPointPage();
	}
	else if (strstr(displayCommandBuffer, CLOCK_PAGE_NAME) != 0) {
		currentPage = CLOCK_PAGE;
		ds3231GetTimeDate(&tempTime);
		updateClockPage();
	}
	else {
		currentPage = MAIN_PAGE;
	}
	#ifdef DEBUG
	softwareSerialPrint("Set Page: ");
	softwareSerialPrintInt(currentPage);
	softwareSerialPrint("\n");
	#endif
}

void afterSetSampleValue() {
	sampleArea = calculateSampleArea(sample, sampleValues[0], sampleValues[1], sampleValues[2]);
	storeSampleValues();
	updateSamplePage();
}

void afterSetCapacityValue() {
	storeMachineCapacity();
	calculateOverflowThresholdForce();
	updateCapacityPage();
}

void processFloatVal(const unsigned char *displayCommandBuffer) {
	const unsigned char *floatValStr = &displayCommandBuffer[strlen(FLOAT_VAL_COMMAND)];
	float auxFloat = atof(floatValStr);
	if (!isnan(auxFloat) && fVarPtr != 0) {
		(*fVarPtr) = auxFloat;
		if (fVarCallbackPtr != 0) {
			(*fVarCallbackPtr)();
		}
	}
	clearFVarPointers();
}

void processFloatVar(const unsigned char *displayCommandBuffer) {
	const unsigned char *floatVarName = &displayCommandBuffer[strlen(FLOAT_VAR_COMMAND)];
	if (strstr(floatVarName, "sample1") != 0) {
		fVarPtr = &(sampleValues[0]);
		fVarCallbackPtr = &afterSetSampleValue;
	}
	else if (strstr(floatVarName, "sample2") != 0) {
		fVarPtr = &(sampleValues[1]);
		fVarCallbackPtr = &afterSetSampleValue;
	}
	else if (strstr(floatVarName, "sample3") != 0) {
		fVarPtr = &(sampleValues[2]);
		fVarCallbackPtr = &afterSetSampleValue;
	}
	else if (strstr(floatVarName, "newcal") != 0) {
		fVarPtr = &newPointValue;
		//fVarCallbackPtr = &updateNewPointPage;
	}
	else if (strstr(floatVarName, "capacity") != 0) {
		fVarPtr = &machineCapacity;
		fVarCallbackPtr = &afterSetCapacityValue;
	}
}

void processNewCalibrationPoint(const unsigned char *displayCommandBuffer) {
	if (calibratedPoints < 10) {
		float calValue = 0.0;
		unsigned long *calDigitalValuePointer = (unsigned long *)(&displayCommandBuffer[strlen(CONFIRM_NEW_POINT_COMMAND)]);
		unsigned long calDigitalValue = (unsigned long)(*calDigitalValuePointer);
		unsigned char *calString = (unsigned char *)(&displayCommandBuffer[strlen(CONFIRM_NEW_POINT_COMMAND)+4]);
		replace(calString, ';', 0);
		calValue = atof(calString);
		//#ifdef DEBUG
		//unsigned char b[16];
		//ultoa(calDigitalValue, b, 10);
		//softwareSerialPrint("DIGITAL POINT: ");
		//softwareSerialPrint(b);
		//softwareSerialPrint("\nCALIBRATION: ");
		//softwareSerialPrint(calString);
		//softwareSerialPrint("\n");
		//#endif
		CalibrationPoint p;
		p.rawValue = calDigitalValue;
		p.value = calValue;
		addCalibrationPoint(p);
		//sortCalibrationPoints();
		fitStraighLine();
		storeCalibrationPoints(calibrationPoints, calibratedPoints);
	}
	displayShowPage(CALIBRATION_PAGE_NAME);
}

void processDeleteCalPoint(const unsigned char *displayCommandBuffer) {
	if (calibratedPoints > 0) {
		unsigned long *pointIndexPointer = (unsigned long *)(&displayCommandBuffer[strlen(DELETE_CALIBRATION_POINT_COMMAND)]);
		unsigned char pointIndex = (unsigned char)(*pointIndexPointer);
		if (pointIndex >= 0 && pointIndex < calibratedPoints) {
			//#ifdef DEBUG
			//softwareSerialPrint("Remove point: ");
			//softwareSerialPrintInt(pointIndex);
			//softwareSerialPrint("\n");
			//#endif
			deleteCalibrationPoint(pointIndex);
			selectedPoint--;
			//sortCalibrationPoints();
			storeCalibrationPoints(calibrationPoints, calibratedPoints);
			displayShowPage(CALIBRATION_PAGE_NAME);
		}
	}
}

void sortCalibrationPoints() {
	//#ifdef DEBUG
	//unsigned char output[40] = {0}, buffer[10];
	//softwareSerialPrint("\nSorting...\n");
	//#endif
	unsigned char i, j, min;
	CalibrationPoint aux;
	for (i=0; i<calibratedPoints; i++) {
		for (j=i+1, min=i; j<calibratedPoints; j++) {
			if (calibrationPoints[j].rawValue < calibrationPoints[min].rawValue) {
				min = j;
			}
		}
		if (min != i) {
			//#ifdef DEBUG
			//output[0] = 0;
			//utoa(min, buffer, 10);
			//strcat(output, buffer);
			//strcat(output, "<");
			//utoa(i, buffer, 10);
			//strcat(output, buffer);
			//strcat(output, "|");
			//ultoa(calibrationPoints[min].rawValue, buffer, 10);
			//strcat(output, buffer);
			//strcat(output, "|");
			//ultoa(calibrationPoints[i].rawValue, buffer, 10);
			//strcat(output, buffer);
			//strcat(output, "|\n");
			//softwareSerialPrint(output);
			//softwareSerialPrint("\n");
			//#endif
			aux = calibrationPoints[i];
			calibrationPoints[i] = calibrationPoints[min];
			calibrationPoints[min] = aux;
		}
	}
	//#ifdef DEBUG
	//softwareSerialPrint("\nEnd Sort!\n");
	//#endif
}

void fitStraighLine() {
	if (calibratedPoints >= 2) {
		int n = 2, p[MAX_CALIBRATION_POINTS], r;
		unsigned char i;
		float A[MAX_CALIBRATION_POINTS][2], b[MAX_CALIBRATION_POINTS], sigma[MAX_CALIBRATION_POINTS], gamma[MAX_CALIBRATION_POINTS];

		for (i=0; i<calibratedPoints; i++) {
			A[i][0] = 1.0;
			A[i][1] = ((float)calibrationPoints[i].rawValue);
			b[i] = (float)calibrationPoints[i].value;
		}

		r = QR((int)calibratedPoints, n, A, sigma, gamma, p);
		solveLeastSquare((int)calibratedPoints, n, A, b, sigma, gamma, p, r);

		for (i=0; i<2; i++) {
			fittedStraightLineCoef[i] = b[i];
		}
	}
	else {
		fittedStraightLineCoef[0] = 0.0;
		fittedStraightLineCoef[1] = 1.0;
	}
}

void deleteCalibrationPoint(unsigned char index) {
	if (index < (calibratedPoints-1)) {
		calibrationPoints[index] = calibrationPoints[calibratedPoints-1];
	}
	calibratedPoints--;
}

void addCalibrationPoint(CalibrationPoint p) {
	calibrationPoints[calibratedPoints++] = p;
}

void processSetDisplayUnit(const unsigned char *displayCommandBuffer) {
	unsigned long *unit_pointer = (unsigned long *)(&displayCommandBuffer[strlen(UNIT_COMMAND)]);
	unsigned char unit = (unsigned char)(*unit_pointer);
	storeDisplayForceUnit(unit);
}

void processPointLock(const unsigned char *displayCommandBuffer) {
	unsigned char b[3];
	adFetchStop = (adFetchStop + 1)%2;
	utoa(adFetchStop, b, 10);
	displaySetValue(LOCKED_VAR, b);
	updateNewPointPage();
	#ifdef DEBUG
	softwareSerialPrint("TOGGLE LOCK\n");
	#endif
}

void loadStoredParameters() {
	unsigned char byteVal;
	
	loadDisplayUnitType();
	loadMachineCapacity();
	loadOverflowProtectionDetails();
	loadSample();
	loadSampleValues();
	loadDisplayForceUnit();
	loadCalibrationUnit();
	loadNumCalibratedPoints();
	displaySetValueUInt("calibration.total_points", calibratedPoints);
	for (byteVal=0; byteVal<calibratedPoints; byteVal++) {
		loadCalibrationPoint(byteVal);
	}
	//sortCalibrationPoints();
	fitStraighLine();
}

long publishForceRawValue() {
	unsigned long tick;
	lastAdData = adcFetchData();
	tick = timerTick;
	testSpeedCalculationArray[testSpeedCalcArrayIndex].rawForceValue = lastAdData;
	testSpeedCalculationArray[testSpeedCalcArrayIndex].timeTick = tick;
	testSpeedCalcArrayIndex = (testSpeedCalcArrayIndex+1)%SPEED_CALC_ARRAY_LENGTH;
	//#ifdef DEBUG
	//softwareSerialPrint("\nForce Raw Value: ");
	//softwareSerialPrintULong(rawValue);
	//softwareSerialPrint("\nTime Tick: ");
	//softwareSerialPrintULong(tick);
	//#endif
	return lastAdData;
}

void updateNewPointDigitalValue() {
	unsigned char buffer[10];
	if (adFetchStop == 0) {
		lastAdData = adcFetchData();
		ltoa(lastAdData, buffer, 10);
		displaySetText(DIGITAL_VALUE_LABEL, buffer);
		displaySetValueLong(DIGITAL_VALUE_VAR, lastAdData);
	}
}

void updateNewPointPage() {
	unsigned char buffer[10];
	if (adFetchStop == 0) {
		lastAdData = adcFetchData();
		ltoa(lastAdData, buffer, 10);
		displaySetText(DIGITAL_VALUE_LABEL, buffer);
		displaySetValueLong(DIGITAL_VALUE_VAR, lastAdData);
		displaySetText(NEW_POINT_CALIBRATION_VALUE_LABEL, "");
		displaySetPic(LOCKED_IMG_NAME, UNLOCKED_IMG_INDEX);
		displayHide(CONFIRM_BUTTON);
	}
	else {
		dtostrf(newPointValue, 10, 2, buffer);
		displaySetText(NEW_POINT_CALIBRATION_VALUE_LABEL, buffer);
		displaySetPic(LOCKED_IMG_NAME, LOCKED_IMG_INDEX);
		displayUnhide(CONFIRM_BUTTON);
	}
}

float getAdjustedValue(long rawValue) {
	//unsigned char slopeIndex=0, i;
	//float value;
	//if (rawValue <= calibrationPoints[0].rawValue)
		//slopeIndex = 0;
	//else if (rawValue > calibrationPoints[calibratedPoints-1].rawValue)
		//slopeIndex = calibratedPoints-2;
	//else {
		//for (i=0; i<calibratedPoints; i++)
			//if (rawValue <= calibrationPoints[i+1].rawValue) {
				//slopeIndex = i;
				//break;
			//}
	//}
	//value = calibrationPoints[slopeIndex].value + gradients[slopeIndex] * ((signed long)rawValue - (signed long)(calibrationPoints[slopeIndex].rawValue));
	//return value;
	return fittedStraightLineCoef[0] + fittedStraightLineCoef[1] * (float)rawValue;
}

float convertForceValue(float v, unsigned char fromForceUnit, unsigned char toForceUnit) {
	if (toForceUnit == KGF || fromForceUnit == KGF) {
		v *= getForceConversionFactor(fromForceUnit, toForceUnit);
	}
	else {
		v = convertForceValue(v, fromForceUnit, KGF);
		v = convertForceValue(v, KGF, toForceUnit);
	}
	return v;
}

float getForceConversionFactor(unsigned char fromForceUnit, unsigned char toForceUnit) {
	float factor = 1.0;
	if (fromForceUnit == toForceUnit) {
		factor = 1.0;
	}
	else if (toForceUnit == N) {
		factor = 9.80665;
	}
	else if (toForceUnit == KN) {
		factor = 0.00980665;
	}
	//else if (toForceUnit == DAN) {
		//factor = 0.980665;
	//}
	else if (toForceUnit == GF) {
		factor = 1000.0;
	}
	else if (toForceUnit == TF) {
		factor = 0.0001;
	}
	//else if (toForceUnit == DYN) {
		//factor = 980665;
	//}
	else if (toForceUnit == LBF) {
		factor = 2.20462;
	}
	else if (toForceUnit == KGF) {
		factor = 1.0 / getForceConversionFactor(toForceUnit, fromForceUnit);
	}
	return factor;
}

float convertTensionValue(float v, unsigned char fromTensionUnit, unsigned char toTensionUnit) {
	if (toTensionUnit == MPA || fromTensionUnit == MPA) {
		v *= getTensionConversionFactor(fromTensionUnit, toTensionUnit);
	}
	else {
		v = convertTensionValue(v, fromTensionUnit, MPA);
		v = convertTensionValue(v, MPA, toTensionUnit);
	}
	return v;
}

float getTensionConversionFactor(unsigned char fromTensionUnit, unsigned char toTensionUnit) {
	float factor = 1.0;
	if (fromTensionUnit == toTensionUnit) {
		factor = 1.0;
	}
	else if (toTensionUnit == N_MM2) {
		factor = 1.0;
	}
	else if (toTensionUnit == PSI) {
		factor = 145.037738;
	}
	else if (toTensionUnit == KGF_MM2) {
		factor = 0.10197162129779282425700927431896;
	}
	else if (toTensionUnit == MPA) {
		factor = 1.0 / getTensionConversionFactor(toTensionUnit, fromTensionUnit);
	}
	return factor;
}

float getAdjustedForceValue(long lastAdData, unsigned char calibrationUnit, unsigned char displayForceUnit) {
	float value = getAdjustedValue(lastAdData);
	return convertForceValue(value, calibrationUnit, displayForceUnit);
	//return value;
}

float getAdjustedTensionValue(long lastAdData, unsigned char calibrationUnit, float sampleArea, unsigned char displayTensionUnit) {
	float value = getAdjustedValue(lastAdData);
	return convertForceToTension(value, calibrationUnit, sampleArea, displayTensionUnit);
}

float convertForceToTension(float forceValue, unsigned char forceUnit, float sampleArea, unsigned char tensionUnit) {
	float value = convertForceValue(forceValue, forceUnit, N);
	value /= sampleArea;
	return convertTensionValue(value, MPA, tensionUnit);
}

void updateDisplayUnit() {
	const unsigned char *displayUnit;
	unsigned char buffer[14] = {0};
	if (displayUnitType == FORCE_UNIT) {
		displayUnit = forceUnitsString[displayForceUnit];
	}
	else {
		displayUnit = tensionUnitsString[displayTensionUnit];
	}
	displaySetText(DISPLAY_UNIT_LABEL, displayUnit);
	strcat(buffer, displayUnit);
	strcat(buffer, "/s");
	displaySetText(TEST_SPEED_UNIT_LABEL, buffer);
}

void updateDisplayUnitType() {
	displaySetPicChar(DISPLAY_UNIT_TYPE_BUTTON, TOGGLE_IMG_POINTER + (displayUnitType%2));
	displaySetPicChar(DISPLAY_UNIT_TYPE_LABEL, DISPLAY_UNIT_TYPE_IMG_POINTER + (displayUnitType%2));
}

void calculateOverflowThresholdForce() {
	overflowThresholdForce = machineCapacity * overflowProtectionThreshold / 100.0;
}

void checkMachineOverflow() {
	float forceValue = NAN;
	if (calibratedPoints >= 2) {
		forceValue = getAdjustedForceValue(lastAdData, calibrationUnit, calibrationUnit);
		if (forceValue > overflowThresholdForce) {
			relayOnOff(overflowProtectionMode);
			displaySetPrimaryColorUint(MAIN_NUMBER_LABEL, COLOR_RED);
			//displayUnhide(OVERFLOW_ALERT_LABEL);
			if (overflowBeepCounter == 0) {
				playHighBuzz(0.1);
				playLowBuzz(0.1);
			}
			overflowBeepCounter = (overflowBeepCounter + 1) % OVERFLOW_BEEP_INTERVAL;
		}
		else {
			relayOnOff(!overflowProtectionMode);
			displaySetPrimaryColorUint(MAIN_NUMBER_LABEL, COLOR_BLACK);
			//displayHide(OVERFLOW_ALERT_LABEL);
			overflowBeepCounter = 0;
		}
	}
}

float getMainDisplayValue() {
	float value = NAN;
	if (calibratedPoints >= 2) {
		//#ifdef DEBUG
		//unsigned char buffer[10] = {0};
		//ultoa(lastAdData, buffer, 10);
		//softwareSerialPrint("AD Data: ");
		//softwareSerialPrint(buffer);
		//softwareSerialPrint("\n");
		//#endif
		if (displayUnitType == FORCE_UNIT) {
			value = getAdjustedForceValue(lastAdData, calibrationUnit, displayForceUnit);
			//#ifdef DEBUG
			//softwareSerialPrint("\nTest Speed: ");
			//softwareSerialPrint("\n");
			//softwareSerialPrintLong(lastTestSpeed);
			//softwareSerialPrint("\n");
			//softwareSerialPrintFloat(speedTestValue, 5);
			//softwareSerialPrint("\n");
			//#endif
		}
		else {
			value = getAdjustedTensionValue(lastAdData, calibrationUnit, sampleArea, displayTensionUnit);
		}
	}
	return value;
}

const unsigned char* getDisplayUnitStr() {
	if (displayUnitType == FORCE_UNIT) {
		return (const unsigned char*)(&forceUnitsString[displayForceUnit]);
		//#ifdef DEBUG
		//softwareSerialPrint("\nTest Speed: ");
		//softwareSerialPrint("\n");
		//softwareSerialPrintLong(lastTestSpeed);
		//softwareSerialPrint("\n");
		//softwareSerialPrintFloat(speedTestValue, 5);
		//softwareSerialPrint("\n");
		//#endif
	}
	else {
		return (const unsigned char*)(&tensionUnitsString[displayTensionUnit]);
	}
}

void updatePeakForce() {
	float newPeakForce = 0.0;
	if (calibratedPoints >= 2) {
		newPeakForce = getAdjustedForceValue(lastAdData, calibrationUnit, calibrationUnit);
		if (newPeakForce > peakForceValue) {
			peakForceValue = newPeakForce;
		}
	}
}

float getPeakValue() {
	float value = NAN;
	if (calibratedPoints >= 2) {
		//#ifdef DEBUG
		//unsigned char buffer[10] = {0};
		//ultoa(lastAdData, buffer, 10);
		//softwareSerialPrint("AD Data: ");
		//softwareSerialPrint(buffer);
		//softwareSerialPrint("\n");
		//#endif
		if (displayUnitType == FORCE_UNIT) {
			value = convertForceValue(peakForceValue, calibrationUnit, displayForceUnit);
			//#ifdef DEBUG
			//softwareSerialPrint("\nTest Speed: ");
			//softwareSerialPrint("\n");
			//softwareSerialPrintLong(lastTestSpeed);
			//softwareSerialPrint("\n");
			//softwareSerialPrintFloat(speedTestValue, 5);
			//softwareSerialPrint("\n");
			//#endif
		}
		else {
			value = convertForceToTension(peakForceValue, calibrationUnit, sampleArea, displayTensionUnit);
		}
	}
	return value;
}


float getTestSpeedValue() {
	float speedTestValue = 0.0;
	if (calibratedPoints >= 2) {
		//#ifdef DEBUG
		//unsigned char buffer[10] = {0};
		//ultoa(lastAdData, buffer, 10);
		//softwareSerialPrint("AD Data: ");
		//softwareSerialPrint(buffer);
		//softwareSerialPrint("\n");
		//#endif
		if (displayUnitType == FORCE_UNIT) {
			speedTestValue = getAdjustedForceValue(lastTestSpeed - fittedStraightLineCoef[0]/fittedStraightLineCoef[1], calibrationUnit, displayForceUnit);
			//#ifdef DEBUG
			//softwareSerialPrint("\nTest Speed: ");
			//softwareSerialPrint("\n");
			//softwareSerialPrintLong(lastTestSpeed);
			//softwareSerialPrint("\n");
			//softwareSerialPrintFloat(speedTestValue, 5);
			//softwareSerialPrint("\n");
			//#endif
		}
		else {
			speedTestValue = getAdjustedTensionValue(lastTestSpeed - fittedStraightLineCoef[0]/fittedStraightLineCoef[1], calibrationUnit, sampleArea, displayTensionUnit);
		}
	}
	return speedTestValue;
}

void updateMainPage() {
	updateDisplayUnitType();
	updateDisplayUnit();
	updateMainNumbers();
	updateTemperature();
}

void updateTemperature() {
	float temp = ds3231GetTemperature();
	unsigned char buffer[10];
	ftoa(temp, buffer, 2);
	strcat(buffer, "ºC");
	displaySetText(TEMPERATURE_LABEL, buffer);
}

void updateMainNumbers() {
	unsigned char buffer[16] = {0};
	float displayValue, testSpeedValue, peakValue;

	publishForceRawValue();
	updatePeakForce();
	calculateTestSpeed();

	displayValue = getMainDisplayValue();
	peakValue = getPeakValue();
	testSpeedValue = getTestSpeedValue();
	if (!isnan(displayValue)) {
		ftoa(displayValue, buffer, 2);
		//#ifdef DEBUG
		//softwareSerialPrint("Display Value ");
		//softwareSerialPrint(buffer);
		//softwareSerialPrint("\n");
		//#endif
		displaySetText(MAIN_NUMBER_LABEL, buffer);
		ftoa(peakValue, buffer, 2);
		displaySetText(PEAK_VALUE_LABEL, buffer);
	}
	else {
		displaySetText(MAIN_NUMBER_LABEL, "--");
		displaySetText(PEAK_VALUE_LABEL, "--");
	}
	ftoa(testSpeedValue, buffer, 1);
	strcat(buffer, getDisplayUnitStr());
	strcat(buffer, "/s");
	displaySetText(TEST_SPEED_LABEL, buffer);
}

void updateCapacityPage() {
	unsigned char buffer[10] = {0};
	ftoa(machineCapacity, buffer, 1);
	displaySetText(CAPACITY_VALUE_LABEL, buffer);
	displaySetText(CALIBRATION_UNIT_LABEL, forceUnitsString[calibrationUnit]);
	displaySetPicChar(OVERFLOW_MODE_OFF_RADIO, RADIOBUTTON_IMG_POINTER + ((overflowProtectionMode+1)%2));
	displaySetPicChar(OVERFLOW_MODE_ON_RADIO, RADIOBUTTON_IMG_POINTER + (overflowProtectionMode%2));
	displaySetPicChar(OVERFLOW_ENABLED_CHECK, CHECKBOX_IMG_POINTER + (overflowProtectionEnabled%2));
	displaySetValueLong(OVERFLOW_THRESHOLD_SLIDER, overflowProtectionThreshold);
	utoa(overflowProtectionThreshold, buffer, 10);
	strcat(buffer, "%");
	displaySetText(OVERFLOW_THRESHOLD_LABEL, buffer);
}

void updateClockPage() {
	unsigned char buffer[4] = {0};
	utoa(tempTime.tm_hour % 24, buffer, 10);
	displaySetText(CLOCK_HOUR_LABEL, buffer);
	utoa(tempTime.tm_min % 60, buffer, 10);
	displaySetText(CLOCK_MINUTE_LABEL, buffer);
}

void updateCalibrationPage() {
	if (calibratedPoints == 0) {
		displaySetText(SELECTED_POINT_LABEL, "Sem calibração");
	}
	else {
		unsigned char output[20] = {0};
		unsigned char buffer[4];
		utoa(selectedPoint+1, buffer, 10);
		strcat(output, "Ponto ");
		strcat(output, buffer);
		strcat(output, " de ");
		utoa(calibratedPoints, buffer, 10);
		strcat(output, buffer);
		#ifdef DEBUG
		softwareSerialPrint(output);
		softwareSerialPrint("\n");
		#endif
		displaySetText(SELECTED_POINT_LABEL, output);
		displaySetValueUInt(SELECTED_POINT_VAR, selectedPoint);
		float cValue = calibrationPoints[selectedPoint].value;
		dtostrf(cValue, 9, 2, output);
		#ifdef DEBUG
		softwareSerialPrint(output);
		softwareSerialPrint("\n");
		#endif
		displaySetText(CALIBRATION_VALUE_LABEL, output);
		displayUnhide(PREV_POINT_IMG_NAME);
		displayUnhide(NEXT_POINT_IMG_NAME);
		displayUnhide(REMOVE_IMG_NAME);
	}
	displaySetText(CALIBRATION_UNIT_LABEL, forceUnitsString[calibrationUnit]);
	displayUnhide(PREV_CAL_UNIT_IMG_NAME);
	displayUnhide(NEXT_CAL_UNIT_IMG_NAME);
}

float calculateSampleArea(unsigned char sample, float sample1, float sample2, float sample3) {
	float area = 1.0;
	if (sample == SQUARE) {
		area = sample1 * sample1;
	}
	else if (sample == RECTANGLE) {
		area = sample1 * sample2;
	}
	else if (sample == CIRCLE) {
		area = M_PI_4 * sample1 * sample1;
	}
	else if (sample == TUBE) {
		area = M_PI * sample2 * (sample1 - sample2);
	}
	else if (sample == TUBESECTOR) {
		area = sample3 / 4.0 * pow((pow(sample1, 2.0) - pow(sample3, 2.0)), 0.5) + pow(sample1, 2.0) / 4.0 * asin(sample3 / sample1) - sample3 / 4 * pow((pow((sample1 - 2 * sample2),2.0) - pow(sample3, 2.0)), 0.5) - pow(((sample1 - 2 * sample2) / 2), 2.0) * asin(sample3 / (sample1 - 2 * sample2));
	}
	return area;
}

void updateSamplePage() {
	displaySetPicChar(SAMPLE_IMG_NAME, SAMPLE_IMG_POINTER+sample);
	displayRefreshComponent(BUTTON_BACK_NAME);
	if (sample == SQUARE || sample == CIRCLE) {
		displayUnhide(SAMPLE_FIELD_1_NAME);
		displayHide(SAMPLE_FIELD_2_NAME);
		displayHide(SAMPLE_FIELD_3_NAME);
	}
	else if (sample == RECTANGLE || sample == TUBE) {
		displayUnhide(SAMPLE_FIELD_1_NAME);
		displayUnhide(SAMPLE_FIELD_2_NAME);
		displayHide(SAMPLE_FIELD_3_NAME);
	}
	else if (sample == TUBESECTOR) {
		displayUnhide(SAMPLE_FIELD_1_NAME);
		displayUnhide(SAMPLE_FIELD_2_NAME);
		displayUnhide(SAMPLE_FIELD_3_NAME);
	}
	else {
		displayHide(SAMPLE_FIELD_1_NAME);
		displayHide(SAMPLE_FIELD_2_NAME);
		displayHide(SAMPLE_FIELD_3_NAME);
	}
	displayUnhide(SAMPLE_AREA_NAME);
	
	unsigned char output[10];
	dtostrf(sampleValues[0], 7, 1, output);
	displaySetText(SAMPLE_FIELD_1_NAME, output);
	dtostrf(sampleValues[1], 7, 1, output);
	displaySetText(SAMPLE_FIELD_2_NAME, output);
	dtostrf(sampleValues[2], 7, 1, output);
	displaySetText(SAMPLE_FIELD_3_NAME, output);
	dtostrf(sampleArea, 7, 1, output);
	displaySetText(SAMPLE_AREA_NAME, output);
}

void clearFVarPointers() {
	fVarCallbackPtr = 0;
	fVarPtr = 0;
}