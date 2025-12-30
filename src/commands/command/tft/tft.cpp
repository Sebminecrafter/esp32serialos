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
void TFTtextColor(String arguments)
{
    println("Attempting to set text color to " + arguments);
    crTextColor = parseColorInput(arguments);
    clearScreen();
}
void TFTbgColor(String arguments)
{
    println("Attempting to set background color to " + arguments);
    crBGColor = parseColorInput(arguments);
    clearScreen();
}
void TFTorientation(String arguments)
{
    arguments.toLowerCase();
    if (arguments == "0" or arguments == "portrait")
    {
        tft.setRotation(0); // Portrait
        clearScreen();
        println("Orientation set to portrait");
    }
    else if (arguments == "1" or arguments == "landscape")
    {
        tft.setRotation(1); // Landscape
        clearScreen();
        println("Orientation set to landscape");
    }
    else if (arguments == "2" or arguments == "portrait flipped")
    {
        tft.setRotation(2); // Portrait flipped
        clearScreen();
        println("Orientation set to portrait (flipped)");
    }
    else if (arguments == "3" or arguments == "landscape flipped")
    {
        tft.setRotation(3); // Landscape flipped
        clearScreen();
        println("Orientation set to landscape (flipped)");
    }
    else
    {
        println("Unknown orientation. Options are: portrait (0), landscape (1), portrait flipped (2), landscape flipped (3)");
    }
}
void TFTsetTextSize(String arguments)
{
    if (arguments.length() == 1)
    {
        int newTextSize = arguments.toInt();
        if (newTextSize > 7)
        {
            println("Text size too big (1-7)");
        }
        else if (newTextSize < 1)
        {
            println("Text size too small (1-7)");
        }
        else
        {
            setTextSize(newTextSize);
            println("Text size set to " + arguments);
        }
    }
    else
    {
        println("Invalid usage.");
        println("Usage: `size [1-7]`");
    }
}
void displayText(String text)
{
    tft.setTextColor(crTextColor, crBGColor);
    tft.setCursor(0, crTextY);
    tft.println(text);
    crTextY = crTextY + (currentTextSize * 8);
}
void showText(String arguments)
{
    println("Showing `" + arguments + "`");
    displayText(arguments);
}
void clearScreenCmd(String arguments)
{
    clearScreen();
    println("Screen cleared.");
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