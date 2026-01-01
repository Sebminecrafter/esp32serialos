#pragma once
#include <Arduino.h>
#include "config.h"
#include "commands/command/tft/tft.h"
#include "utilities/utilities.h"

typedef void (*CommandFunc)(String arguments);
typedef struct
{
    const char *command;
    CommandFunc function;
    const char *help;
} CommandEntry;

extern void cmdHelp(String arguments);
extern void showText(String arguments);
extern void clearScreenCmd(String arguments);
extern void TFTsetTextSize(String arguments);
extern void TFTtextColor(String arguments);
extern void TFTbgColor(String arguments);
extern void TFTorientation(String arguments);
extern void aboutCmd(String arguments);
extern void deepSleepTimer(String arguments);
inline void echo(String arguments) { println(arguments); }
extern void logo(String arguments);

extern CommandEntry commandTable[]; // Custom table of all commands
extern const uint8_t commandCount;