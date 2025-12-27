#pragma once
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Arduino.h>
#include "utilities/utilities.h"
extern TFT_eSPI tft;
extern int crTextY;
extern int currentTextSize;
extern uint32_t crBGColor, crTextColor;

extern void startTFT();
extern void TFTtextColor(String arguments);
extern void TFTbgColor(String arguments);
extern void TFTorientation(String arguments);
extern void TFTsetTextSize(String arguments);
extern void displayText(String text);
extern void clearScreen();
extern void setTextSize(int size);
extern void showText(String arguments);
extern void clearScreenCmd(String arguments);