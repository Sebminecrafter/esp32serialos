#include "utilities/utilities.h"
#include <Arduino.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// BEGIN OUPUT

// ---------
// internals
// ---------

// Main internal print function, controls outputs
void _print(const char *text)
{
    Serial.print(text);
}

// Internal println function
void _println(const char *text)
{
    _print(text + '\n');
}

// -----
// print
// -----

// C string
void print(const char *text)
{
    _print(text);
}

// Arduino String
void print(const String &text)
{
    _print(text.c_str());
}

// Single character
void print(char c)
{
    char buf[2] = {c, '\0'};
    _print(buf);
}

// blank ig
void print()
{
    _print("");
}

// -------
// println
// -------

// C string
void println(const char *text)
{
    _println(text);
}

// Arduino String
void println(const String &text)
{
    _println(text.c_str());
}

// Single character
void println(char c)
{
    char buf[2] = {c, '\0'};
    _println(buf);
}

// Print empty line
void println()
{
    _println("");
}

// format
char *formatf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    va_list args_copy;
    va_copy(args_copy, args);
    int len = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    if (len < 0)
    {
        va_end(args);
        return NULL;
    }

    char *buffer = (char *)malloc(len + 1);
    if (!buffer)
    {
        va_end(args);
        return NULL;
    }

    vsnprintf(buffer, len + 1, format, args);
    va_end(args);

    return buffer;
}

// printf
void printf(const char *format)
{
    char *text = formatf(format);
    print(text);
    free(text);
}

// END OF OUTPUT

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
            println("Invalid hex color format.");
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
            println("Invalid RGB format. Use R,G,B or #RRGGBB.");
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
    print("Input color: R=");
    print(r);
    print(", G=");
    print(g);
    print(", B=");
    println(b);
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

int getNumOf(String args, char delim)
{
    int numOf = 0;
    for (int i = 0; i < args.length(); i++)
    {
        if (args[i] == delim)
        {
            numOf++;
        }
    }
    return numOf;
}