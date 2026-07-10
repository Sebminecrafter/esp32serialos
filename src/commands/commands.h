#pragma once
#include <Arduino.h>
#include "config.h"
#include "utilities/utilities.h"
#ifdef USE_TFT
#include "commands/command/tft/tft_commands.h"
#endif

typedef void (*CommandFunc)(String arguments);
typedef struct
{
    const char *command;
    CommandFunc function;
    const char *help;
} CommandEntry;

extern void cmdHelp(String arguments);
extern void aboutCmd(String arguments);
extern void deepSleepTimer(String arguments);
inline void echo(String arguments) { println(arguments); }
extern void logo(String arguments);

extern CommandEntry commandTable[]; // Custom table of all commands
extern uint8_t commandCount;
extern void initCommandTable();