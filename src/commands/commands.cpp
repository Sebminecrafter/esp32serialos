#include "commands/commands.h"
#include <Arduino.h>
#include "commands/command/wifi/main.h"

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
    {"logo", logo, "Prints Sebby logo"},
    {"connect", connect, "Connect to a WiFi network"},
    {"disconnect", disconnect, "Disconnect from WiFi"},
    {"scan", scan, "Scan for WiFi networks"}};
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
        println("\nAvailable Commands:\n");
        for (uint8_t i = 0; i < commandCount; i++)
        {
            print(commandTable[i].command);
            print(" - ");
            println(commandTable[i].help);
        }
        println();
    }
    else
    {
        signed int cmdIdx = getCommandIndex(arguments);
        if (cmdIdx == -1)
        {
            println("Couldn't find command `" + arguments + "`");
        }
        else
        {
            print(commandTable[cmdIdx].command);
            print(" - ");
            println(commandTable[cmdIdx].help);
        }
    }
}
void logo(String arguments)
{
    for (int i = 0; i < logoCount; i++)
    {
        println(LOGO[i]);
    }
}

void aboutCmd(String arguments) // About OS
{
    logo("");
    print(" --- ");
    print(NAME);
    println(" --- ");
    print("Version ");
    println(OSVERSION);
    print("Made by ");
    println(CONTRIB);
    println("Written in C++");
    print("Last update: ");
    println(LASTUPD);
}

// Deep sleep
void deepSleepTimer(String arguments)
{
    uint64_t totalSeconds = parseTime(arguments);

    if (totalSeconds < 1)
    {
        println("Invalid usage. Could not parse time or zero duration.");
        return;
    }

    print("Sleeping for ");
    println(formatTime(totalSeconds));

    delay(250);
    Serial.flush();

    delay(250);
    Serial.end();

    uint64_t sleepTimeUs = totalSeconds * 1000000ULL;
    delay(250);

    esp_sleep_enable_timer_wakeup(sleepTimeUs);
    esp_deep_sleep_start();
}