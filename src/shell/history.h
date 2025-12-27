#pragma once
#include "shell/shell.h"
#include <Arduino.h>
#include "config.h"
#include "utilities/utilities.h"

extern String history[HISTORY_SIZE];
extern int historyCount;
extern int historyIndex;
extern String historyFirstSave;

extern void addToHistory(const String &cmd);
extern bool handleHistoryKeys(char c);