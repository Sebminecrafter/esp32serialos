#include "utilities.h"
#include <Arduino.h>

uint16_t parseColorInput(String input)
{ // Imma be honest i got chatgpt to do this color parsing
    input.trim();
    input.toUpperCase();
    int r = 0, g = 0, b = 0;
    // If input is hex format (e.g., "#FFAABB" or "FFAABB")
    if (input.startsWith("#") || (input.length() == 6 && input.indexOf(',') == -1))
    {
        if (input.startsWith("#"))
        {
            input = input.substring(1); // Remove `#`
        }
        if (input.length() != 6)
        {
            Serial.println("Invalid hex color format.");
            return 0;
        }
        char rStr[3], gStr[3], bStr[3];
        input.substring(0, 2).toCharArray(rStr, 3);
        input.substring(2, 4).toCharArray(gStr, 3);
        input.substring(4, 6).toCharArray(bStr, 3);
        r = strtol(rStr, NULL, 16);
        g = strtol(gStr, NULL, 16);
        b = strtol(bStr, NULL, 16);
    }
    // Else, assume it's comma-separated RGB
    else
    {
        int firstComma = input.indexOf(',');
        int secondComma = input.indexOf(',', firstComma + 1);
        if (firstComma == -1 || secondComma == -1)
        {
            Serial.println("Invalid RGB format. Use R,G,B or #RRGGBB.");
            return 0;
        }
        r = input.substring(0, firstComma).toInt();
        g = input.substring(firstComma + 1, secondComma).toInt();
        b = input.substring(secondComma + 1).toInt();
    }
    r = constrain(r, 0, 255);
    g = constrain(g, 0, 255);
    b = constrain(b, 0, 255);
    // Convert to RGB565
    uint16_t color565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    Serial.print("Input color: R=");
    Serial.print(r);
    Serial.print(", G=");
    Serial.print(g);
    Serial.print(", B=");
    Serial.println(b);
    return color565;
}

String stripBeginning(String text, String removeText)
{
    String newText;

    // Check if 'text' starts with 'remove'
    if (text.startsWith(removeText))
    {
        newText = text.substring(removeText.length()); // remove the prefix
    }
    else
    {
        newText = text; // if prefix doesn't match, keep original
    }
    return newText;
}

// Natural-ish language time parsing
uint64_t parseTime(String input)
{
    input.trim();
    input.toLowerCase();
    if (input.length() == 0)
        return 0;
    uint64_t totalSeconds = 0;
    int numberBuffer = 0;
    bool numberActive = false;

    for (unsigned int i = 0; i < input.length(); i++)
    {
        char c = input[i];
        if (isDigit(c))
        {
            numberBuffer = numberBuffer * 10 + (c - '0');
            numberActive = true;
        }
        else if (isAlpha(c) && numberActive)
        {
            if (c == 'h')
                totalSeconds += (uint64_t)numberBuffer * 3600ULL;
            else if (c == 'm')
                totalSeconds += (uint64_t)numberBuffer * 60ULL;
            else if (c == 's')
                totalSeconds += (uint64_t)numberBuffer;
            else
                return 0; // invalid unit

            numberBuffer = 0;
            numberActive = false;
        }
        else if (c == ' ' || c == '\t')
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
    if (numberActive)
        totalSeconds += numberBuffer; // number left without unit = seconds
    return totalSeconds;
}

// Format seconds to _h _m _s
String formatTime(uint64_t totalSeconds)
{
    uint64_t hours = totalSeconds / 3600ULL;
    uint64_t minutes = (totalSeconds % 3600ULL) / 60ULL;
    uint64_t seconds = totalSeconds % 60ULL;

    String result = "";
    if (hours > 0)
        result += String(hours) + "h ";
    if (minutes > 0 || hours > 0)
        result += String(minutes) + "m ";
    result += String(seconds) + "s";

    return result;
}