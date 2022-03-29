
#ifndef _LVGL_DEMO_H_
#define _LVGL_DEMO_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/
bool isLvglReady(void);

void lvgl_task(void *param);
void vApplicationTickHook_lvgl(void);

void openMenuScreen();
void openLEDScreen();
void openAVScreen();

void setLedRedImgState(bool state);
void setLedGreenImgState(bool state);
void setLedBlueImgState(bool state);

void enableMic(int mic, bool state);
void addMicData(int mic, int16_t value);

#endif //_LVGL_DEMO_H_
