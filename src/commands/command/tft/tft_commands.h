#pragma once

#ifdef USE_TFT
#include <Arduino.h>
#include "commands/command/tft/tft.h"

extern void TFTtextColor(String arguments);
extern void TFTbgColor(String arguments);
extern void TFTorientation(String arguments);
extern void TFTsetTextSize(String arguments);
extern void showText(String arguments);
extern void clearScreenCmd(String arguments);

extern CommandEntry tftCommandTable[];
extern const uint8_t tftCommandCount;
#endif
