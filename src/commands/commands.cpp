#include "commands/commands.h"
#include <Arduino.h>

CommandEntry commandTable[] = {
    {"help", cmdHelp, "Show this help message"},
    {"show", showText, "Shows text on TFT screen"},
    {"clear", clearScreenCmd, "Clears the TFT screen"},
    {"size", TFTsetTextSize, "Sets the text size (1-7)"},
    {"textcolor", TFTtextColor, "Sets the TFT screen text color"},
    {"bgcolor", TFTbgColor, "Sets the TFT screen background color"},
    {"orientation", TFTorientation, "Sets the TFT screen orientation (0-3)"},
    {"about", aboutCmd, "About OS and version"},
    {"version", aboutCmd, "alias for about"},
    {"ver", aboutCmd, "alias for about"},
    {"sleep", deepSleepTimer, "Deep sleep for _ amount of time *WILL MAKE DEVICE TEMPORARILY UNAVAILABLE*"},
    {"echo", echo, "Echo text back/display text to console"},
    {"logo", logo, "Prints Sebby logo"}};
const uint8_t commandCount = sizeof(commandTable) / sizeof(commandTable[0]);

// Esp32SerialOS essential/main shell commands

int getCommandIndex(String name)
{
    name.toLowerCase();
    for (int i = 0; i < commandCount; i++)
    {
        if (name.equals(commandTable[i].command))
        {
            return i; // If found, return
        }
    }
    return -1; // Not found
}

void cmdHelp(String arguments)
{
    if (arguments == "")
    {
        Serial.println("\nAvailable Commands:\n");
        for (uint8_t i = 0; i < commandCount; i++)
        {
            Serial.print(commandTable[i].command);
            Serial.print(" - ");
            Serial.println(commandTable[i].help);
        }
        Serial.println();
    }
    else
    {
        signed int cmdIdx = getCommandIndex(arguments);
        if (cmdIdx == -1)
        {
            Serial.println("Couldn't find command `" + arguments + "`");
        }
        else
        {
            Serial.print(commandTable[cmdIdx].command);
            Serial.print(" - ");
            Serial.println(commandTable[cmdIdx].help);
        }
    }
}
void logo(String arguments)
{
    for (int i = 0; i < logoCount; i++)
    {
        Serial.println(LOGO[i]);
    }
}

void aboutCmd(String arguments) // About OS
{
    logo("");
    Serial.print(" --- ");
    Serial.print(NAME);
    Serial.println(" --- ");
    Serial.print("Version ");
    Serial.println(OSVERSION);
    Serial.print("Made by ");
    Serial.println(CONTRIB);
    Serial.println("Written in C++");
    Serial.print("Last update:");
    Serial.println(LASTUPD);
}

// Deep sleep
void deepSleepTimer(String arguments)
{
    uint64_t totalSeconds = parseTime(arguments);

    if (totalSeconds < 1)
    {
        Serial.println("Invalid usage. Could not parse time or zero duration.");
        return;
    }

    Serial.print("Sleeping for ");
    Serial.println(formatTime(totalSeconds));

    delay(250);
    Serial.flush();

    delay(250);
    Serial.end();

    uint64_t sleepTimeUs = totalSeconds * 1000000ULL;
    delay(250);

    esp_sleep_enable_timer_wakeup(sleepTimeUs);
    esp_deep_sleep_start();
}