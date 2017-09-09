/*
 * nx4832t035.c
 *
 * Created: 30/04/2017 18:58:37
 *  Author: Rodolfo
 */ 

 #include "indicator.h"
 #include "mystdlib.h"
 #include "serial.h"
 #include "nx4832t035.h"
 #include <stdlib.h>
 #include <avr/pgmspace.h>
 #include <util/delay.h>

const unsigned char SENDME[] = "sendme";
const unsigned char REFRESH[] = "ref ";
const unsigned char PAGE[] = "page ";
const unsigned char VIS[] = "vis ";
const unsigned char END[] = "ÿÿÿ";
const unsigned char TXT[] = ".txt=";
const unsigned char VAL[] = ".val=";
const unsigned char PCO[] = ".pco=";
const unsigned char PIC[] = ".pic=";
const unsigned char MAIN_PAGE_NAME[] = "1";
const unsigned char MENU_PAGE_NAME[] = "2";
const unsigned char CALIBRATION_PAGE_NAME[] = "3";
const unsigned char NEW_POINT_PAGE_NAME[] = "4";
const unsigned char SAMPLE_PAGE_NAME[] = "5";
const unsigned char CAPACITY_PAGE_NAME[] = "7";
const unsigned char DIGITAL_VALUE_LABEL[] = "d_value_label";
const unsigned char DIGITAL_VALUE_VAR[] = "d_value";
const unsigned char NEW_POINT_CALIBRATION_VALUE_LABEL[] = "new_calib";
const unsigned char MAIN_NUMBER_LABEL[] = "num";
const unsigned char PEAK_VALUE_LABEL[] = "peak_val";
const unsigned char DISPLAY_UNIT_LABEL[] = "disp_unit";
const unsigned char LOCKED_VAR[] = "locked";
const unsigned char LOCKED_IMG_NAME[] = "lock_img";
const unsigned char LOCKED_IMG_INDEX[] = "11";
const unsigned char UNLOCKED_IMG_INDEX[] = "12";
const unsigned char CONFIRM_BUTTON[] = "b_confirm";
const unsigned char SELECTED_POINT_LABEL[] = "point_label";
const unsigned char SELECTED_POINT_VAR[] = "selected_point";
const unsigned char CALIBRATION_VALUE_LABEL[] = "cal_label";
const unsigned char CALIBRATION_UNIT_LABEL[] = "calunit";
const unsigned char NEXT_POINT_IMG_NAME[] = "b_next_p";
const unsigned char PREV_POINT_IMG_NAME[] = "b_prev_p";
const unsigned char NEXT_CAL_UNIT_IMG_NAME[] = "b_next_cunit";
const unsigned char PREV_CAL_UNIT_IMG_NAME[] = "b_prev_cunit";
const unsigned char REMOVE_IMG_NAME[] = "b_remove";
const unsigned char SAMPLE_IMG_NAME[] = "p_sample";
const unsigned char SAMPLE_FIELD_1_NAME[] = "t_sample1";
const unsigned char SAMPLE_FIELD_2_NAME[] = "t_sample2";
const unsigned char SAMPLE_FIELD_3_NAME[] = "t_sample3";
const unsigned char SAMPLE_AREA_NAME[] = "t_area";
const unsigned char CAPACITY_VALUE_LABEL[] = "capac_txt";
const unsigned char OVERFLOW_MODE_OFF_RADIO[] = "b_off";
const unsigned char OVERFLOW_MODE_ON_RADIO[] = "b_on";
const unsigned char OVERFLOW_THRESHOLD_SLIDER[] = "sl_relay";
const unsigned char OVERFLOW_THRESHOLD_LABEL[] = "ovf_thr";
const unsigned char OVERFLOW_ENABLED_CHECK[] = "check_ovf";
const unsigned char OVERFLOW_ALERT_LABEL[] = "overflow_label";
const unsigned char TEST_SPEED_LABEL[] = "speed_val";
const unsigned char TEST_SPEED_UNIT_LABEL[] = "speed_unit";
const unsigned char DISPLAY_UNIT_TYPE_BUTTON[] = "disp_unittp_b";
const unsigned char DISPLAY_UNIT_TYPE_LABEL[] = "disp_unittp_l";
const unsigned char BUTTON_BACK_NAME[] = "b_back";

unsigned char _nextionResponse[8];

void displayClearCommandBuffer() {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	serialBufferReadAll(_nextionResponse);
	return;
}

int displayGetCurrentPage() {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(SENDME);
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	serialBufferReadAll(_nextionResponse);
	if (_nextionResponse[0] == 0x66)
		return _nextionResponse[1];
	return -1;
}

//int displayDoEvents() {
	//disableGlobalInterrupt();
	//serialClearInputBuffer();
	//serialPrint(SENDME);
	//serialPrint(END);
	//enableGlobalInterrupt();
	//_delay_ms(RESPONSE_WAIT_TIME);
	//serialBufferReadAll(_nextionResponse);
	//if (_nextionResponse[0] == 0x66)
	//return _nextionResponse[1];
	//return -1;
//}

unsigned char displayShowPage(const unsigned char *pageId) {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(PAGE);
	serialPrint(pageId);
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	//serialBufferReadAll(_nextionResponse);
	//return _nextionResponse[0];
	return 0;
}

unsigned char displayRefreshComponent(const unsigned char *componentName) {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(REFRESH);
	serialPrint(componentName);
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	//serialBufferReadAll(_nextionResponse);
	//return _nextionResponse[0];
	return 0;
}

unsigned char _displayVis(const unsigned char *component, const unsigned char v) {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(VIS);
	serialPrint(component);
	serialPrint(",");
	serialPutChar(v);
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	//serialBufferReadAll(_nextionResponse);
	//return _nextionResponse[0];
	return 0;
}

unsigned char displayHide(const unsigned char *component) {
	return _displayVis(component, '0');
}

unsigned char displayUnhide(const unsigned char *component) {
	return _displayVis(component, '1');
}

unsigned char displaySetText(const unsigned char *labelName, const unsigned char *text) {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(labelName);
	serialPrint(TXT);
	serialPutChar('\"');
	serialPrint(text);
	serialPutChar('\"');
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	//serialBufferReadAll(_nextionResponse);
	//return _nextionResponse[0];
	return 0;
}

unsigned char displaySetValue(const unsigned char *valueName, const unsigned char *text) {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(valueName);
	serialPrint(VAL);
	serialPrint(text);
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	//serialBufferReadAll(_nextionResponse);
	//return _nextionResponse[0];
	return 0;
}

unsigned char displaySetValueUInt(const unsigned char *valueName, const unsigned char val) {	
	unsigned char conversionBuffer[16];
	utoa(val, conversionBuffer, 10);
	return displaySetValue(valueName, conversionBuffer);
}

unsigned char displaySetPrimaryColor(const unsigned char *valueName, const unsigned char *text) {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(valueName);
	serialPrint(PCO);
	serialPrint(text);
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	//serialBufferReadAll(_nextionResponse);
	//return _nextionResponse[0];
	return 0;
}

unsigned char displaySetPrimaryColorUint(const unsigned char *valueName, const unsigned int val) {
	unsigned char conversionBuffer[16];
	utoa(val, conversionBuffer, 10);
	return displaySetPrimaryColor(valueName, conversionBuffer);
}

unsigned char displaySetValueUnsignedLong(const unsigned char *valueName, const unsigned long int val) {
	unsigned char conversionBuffer[16];
	ultoa(val, conversionBuffer, 10);
	return displaySetValue(valueName, conversionBuffer);
}

unsigned char displaySetValueLong(const unsigned char *valueName, const long int val) {
	unsigned char conversionBuffer[16];
	ltoa(val, conversionBuffer, 10);
	return displaySetValue(valueName, conversionBuffer);
}

unsigned char displaySetPic(const unsigned char *picName, const unsigned char *picIndex) {
	disableGlobalInterrupt();
	serialClearInputBuffer();
	serialPrint(picName);
	serialPrint(PIC);
	serialPrint(picIndex);
	serialPrint(END);
	enableGlobalInterrupt();
	_delay_ms(RESPONSE_WAIT_TIME);
	//serialBufferReadAll(_nextionResponse);
	//return _nextionResponse[0];
	return 0;
}

unsigned char displaySetPicChar(const unsigned char *picName, const unsigned char picIndex) {
	unsigned char buffer[3];
	utoa(picIndex, buffer, 10);
	return displaySetPic(picName, buffer);
}
