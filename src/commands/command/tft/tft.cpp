#include <TFT_eSPI.h>
#include <SPI.h>
#include <Arduino.h>
#include "utilities/utilities.h"
#include "commands/command/tft/tft.h"
TFT_eSPI tft = TFT_eSPI();
int crTextY = 0;
int currentTextSize = 1;
uint32_t crBGColor = TFT_BLACK, crTextColor = TFT_WHITE;

void clearScreen()
{
    tft.fillScreen(crBGColor);
    crTextY = 0;
}
void setTextSize(int size)
{
    currentTextSize = size;
    tft.setTextSize(size);
    clearScreen();
}
void displayText(String text)
{
    tft.setTextColor(crTextColor, crBGColor);
    tft.setCursor(0, crTextY);
    tft.println(text);
    crTextY = crTextY + (currentTextSize * 8);
}
void startTFT()
{
    println("TFT soft reset");                           // Notify serial
    TFTorientation("0");                                 // Reset orientation
    crTextY = 0;                                         // Reset vars
    currentTextSize = 1;                                 // Reset vars
    crBGColor = TFT_BLACK;                               // Reset vars
    crTextColor = TFT_WHITE;                             // Reset vars
    tft.setSwapBytes(true);                              // To fix inverted colors
    tft.setTextSize(currentTextSize);                    // Reset setting
    clearScreen();                                       // Clear
    displayText("Use serial to connect to this device"); // Message
}