/*
 * nx4832t035.h
 *
 * Created: 30/04/2017 18:57:11
 *  Author: Rodolfo
 */ 


#ifndef NX4832T035_H_
#define NX4832T035_H_

#define RESPONSE_WAIT_TIME 10
#define SAMPLE_IMG_POINTER 15
#define RADIOBUTTON_IMG_POINTER 9
#define CHECKBOX_IMG_POINTER 25
#define TOGGLE_IMG_POINTER 27
#define DISPLAY_UNIT_TYPE_IMG_POINTER 29

// Color

#define COLOR_BLACK 0
#define COLOR_RED 63488

////////////

extern const unsigned char MAIN_PAGE_NAME[];
extern const unsigned char MENU_PAGE_NAME[];
extern const unsigned char UNIT_SELECTION_PAGE_NAME[];
extern const unsigned char CALIBRATION_PAGE_NAME[];
extern const unsigned char NEW_POINT_PAGE_NAME[];
extern const unsigned char SAMPLE_PAGE_NAME[];
extern const unsigned char CAPACITY_PAGE_NAME[];
extern const unsigned char CONFIG_PAGE_NAME[];
extern const unsigned char CLOCK_PAGE_NAME[];
extern const unsigned char DIGITAL_VALUE_LABEL[];
extern const unsigned char DIGITAL_VALUE_VAR[];
extern const unsigned char NEW_POINT_CALIBRATION_VALUE_LABEL[];
extern const unsigned char MAIN_NUMBER_LABEL[];
extern const unsigned char PEAK_VALUE_LABEL[];
extern const unsigned char DISPLAY_UNIT_LABEL[];
extern const unsigned char LOCKED_VAR[];
extern const unsigned char LOCKED_IMG_NAME[];
extern const unsigned char LOCKED_IMG_INDEX[];
extern const unsigned char UNLOCKED_IMG_INDEX[];
extern const unsigned char CONFIRM_BUTTON[];
extern const unsigned char SELECTED_POINT_LABEL[];
extern const unsigned char SELECTED_POINT_VAR[];
extern const unsigned char CALIBRATION_VALUE_LABEL[];
extern const unsigned char CALIBRATION_UNIT_LABEL[];
extern const unsigned char NEXT_POINT_IMG_NAME[];
extern const unsigned char PREV_POINT_IMG_NAME[];
extern const unsigned char NEXT_CAL_UNIT_IMG_NAME[];
extern const unsigned char PREV_CAL_UNIT_IMG_NAME[];
extern const unsigned char REMOVE_IMG_NAME[];
extern const unsigned char SAMPLE_IMG_NAME[];
extern const unsigned char SAMPLE_FIELD_1_NAME[];
extern const unsigned char SAMPLE_FIELD_2_NAME[];
extern const unsigned char SAMPLE_FIELD_3_NAME[];
extern const unsigned char SAMPLE_AREA_NAME[];
extern const unsigned char CAPACITY_VALUE_LABEL[];
extern const unsigned char OVERFLOW_MODE_OFF_RADIO[];
extern const unsigned char OVERFLOW_MODE_ON_RADIO[];
extern const unsigned char OVERFLOW_THRESHOLD_SLIDER[];
extern const unsigned char OVERFLOW_THRESHOLD_LABEL[];
extern const unsigned char OVERFLOW_ENABLED_CHECK[];
extern const unsigned char OVERFLOW_ALERT_LABEL[];
extern const unsigned char TEST_SPEED_LABEL[];
extern const unsigned char TEMPERATURE_LABEL[];
extern const unsigned char TEST_SPEED_UNIT_LABEL[];
extern const unsigned char DISPLAY_UNIT_TYPE_BUTTON[];
extern const unsigned char DISPLAY_UNIT_TYPE_LABEL[];
extern const unsigned char BUTTON_BACK_NAME[];
extern const unsigned char CLOCK_HOUR_LABEL[];
extern const unsigned char CLOCK_MINUTE_LABEL[];

enum pages {WAIT_PAGE, MAIN_PAGE, MENU_PAGE, CALIBRATION_PAGE, NEW_POINT_PAGE, SAMPLE_PAGE, KEYPAD_PAGE, CAPACITY_PAGE, CONFIG_PAGE, CLOCK_PAGE};

void displayClearCommandBuffer();
int displayGetCurrentPage();
unsigned char displayShowPage(const unsigned char *pageId);
unsigned char displayRefreshComponent(const unsigned char *componentName);
unsigned char displaySetText(const unsigned char *labelName, const unsigned char *text);
unsigned char displaySetValue(const unsigned char *valueName, const unsigned char *text);
unsigned char displaySetValueUInt(const unsigned char *valueName, const unsigned char val);
unsigned char displaySetValueUnsignedLong(const unsigned char *valueName, const unsigned long int val);
unsigned char displaySetValueLong(const unsigned char *valueName, const long int val);
unsigned char displaySetPic(const unsigned char *picName, const unsigned char *picIndex);
unsigned char displaySetPicChar(const unsigned char *picName, const unsigned char picIndex);
unsigned char _displayVis(const unsigned char *component, const unsigned char v);
unsigned char displayHide(const unsigned char *component);
unsigned char displayUnhide(const unsigned char *component);
unsigned char displaySetPrimaryColor(const unsigned char *valueName, const unsigned char *text);
unsigned char displaySetPrimaryColorUint(const unsigned char *valueName, const unsigned int val);

#endif /* NX4832T035_H_ */