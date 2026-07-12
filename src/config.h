#pragma once
#define CONFIG_H
#include <Arduino.h>

#define HISTORY_SIZE 5
#define BAUD_RATE 9600

// Uncomment and set to your SD card reader's chip-select pin to enable
// the /sd mount. Leave undefined to build without SD support.
// #define SD_CS_PIN 5

#define NAME "Esp32 Serial OS"
#define PROMPT "Esp32SerialOS> "
#define OSVERSION "Beta 1.1.0"
#define CONTRIB "Sebminecrafter"
#define LASTUPD "Update for all models"

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