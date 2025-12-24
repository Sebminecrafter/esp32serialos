#pragma once
#include "config.h"
#include "shell/history.h"
#include "commands/commands.h"
#include <Arduino.h>

extern String command;

extern void processCommand(String input);
extern void redrawLine();