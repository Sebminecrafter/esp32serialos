#include "commands/commands.h"
#include "tft.h"
#include <Arduino.h>

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

CommandEntry tftCommandTable[] = {
    {"show", showText, "Shows text on TFT screen"},
    {"clear", clearScreenCmd, "Clears the TFT screen"},
    {"size", TFTsetTextSize, "Sets the text size (1-7)"},
    {"textcolor", TFTtextColor, "Sets the TFT screen text color"},
    {"bgcolor", TFTbgColor, "Sets the TFT screen background color"},
    {"orientation", TFTorientation, "Sets the TFT screen orientation (0-3)"}};
const uint8_t tftCommandCount = sizeof(tftCommandTable) / sizeof(tftCommandTable[0]);