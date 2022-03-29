/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_

#include "gui_guider.h"

typedef enum
{
    eLEDRed = 0,
    eLEDGreen,
    eLEDBlue,
}eLED;

void custom_init(lv_ui *ui);
void NavigateToLEDScreen();
void NavigateToAudioScreen();
void NavigateToHomeScreen();
void ToggleLEDState(eLED led, bool state);
void ToggleMicState(int mic, bool state);

extern volatile bool LEDRedState;
extern volatile bool LEDGreenState;
extern volatile bool LEDBlueState;

extern volatile bool MIC1Checked;
extern volatile bool MIC2Checked;
extern volatile bool MIC3Checked;
extern volatile bool MIC4Checked;

#endif /* EVENT_CB_H_ */
