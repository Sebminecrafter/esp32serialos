#pragma once
#define CONFIG_H
#include <Arduino.h>

#define HISTORY_SIZE 5
#define BAUD_RATE 9600

#define NAME "Esp32 Serial OS"
#define PROMPT "Esp32SerialOS> "
#define OSVERSION "Beta 1.0.0"
#define CONTRIB "Sebminecrafter"
#define LASTUPD "Converted project from .ino single file to full-on C++ codebase"

constexpr const char *LOGO[] = {
    "    ████████████    ",
    "  ██░░░░░░░██░░░██  ",
    " █░░░░░░░░████░░░░█ ",
    "█░░░░░░░░██████░░░░█",
    "█░░░░░░░░███░░░░░░░█",
    "█░░░░░░░░██░░░░░░░░█",
    "█░░░░░░░███░░░░░░░░█",
    "█░░░░██████░░░░░░░░█",
    " █░░░░████░░░░░░░░█ ",
    "  ██░░░███░░░░░░██  ",
    "    ████████████    "};
const uint8_t logoCount =
    sizeof(LOGO) / sizeof(LOGO[0]);