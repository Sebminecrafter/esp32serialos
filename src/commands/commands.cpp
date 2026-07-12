#include "commands/commands.h"
#include <Arduino.h>
#include "commands/command/wifi/main.h"
#include "commands/command/fs/fs_commands.h"

static const uint8_t MAX_COMMANDS = 32;
CommandEntry commandTable[MAX_COMMANDS];
uint8_t commandCount = 0;

#ifdef USE_TFT
extern CommandEntry tftCommandTable[];
extern const uint8_t tftCommandCount;
#endif

static void addCommand(const char *command, CommandFunc function, const char *help)
{
    if (commandCount < MAX_COMMANDS)
    {
        commandTable[commandCount++] = {command, function, help};
    }
}

void initCommandTable()
{
    commandCount = 0;
    addCommand("help", cmdHelp, "Show this help message");
#ifdef USE_TFT
    for (uint8_t i = 0; i < tftCommandCount; i++)
    {
        addCommand(tftCommandTable[i].command, tftCommandTable[i].function, tftCommandTable[i].help);
    }
#endif
    addCommand("about", aboutCmd, "About OS and version");
    addCommand("version", aboutCmd, "alias for about");
    addCommand("ver", aboutCmd, "alias for about");
    addCommand("sleep", deepSleepTimer, "Deep sleep for _ amount of time *WILL MAKE DEVICE TEMPORARILY UNAVAILABLE*");
    addCommand("echo", echo, "Echo text back/display text to console");
    addCommand("logo", logo, "Prints Sebby logo");
    addCommand("connect", connect, "Connect to a WiFi network");
    addCommand("disconnect", disconnect, "Disconnect from WiFi");
    addCommand("scan", scan, "Scan for WiFi networks");
    addCommand("ls", cmdLs, "List directory contents, e.g. `ls /sd/docs`");
    addCommand("cat", cmdCat, "Print a file's contents, e.g. `cat /flash/docs/welcome.txt`");
    addCommand("mounts", cmdMounts, "Show filesystem mount status");
}

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