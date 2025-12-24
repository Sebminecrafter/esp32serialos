# ESP32 Serial OS - AI Coding Guidelines

## Architecture Overview

This is a modular C++ firmware for ESP32 devices with serial command interface and TFT display. Core components:

- **Shell System** (`src/shell/`): Command parsing, history navigation (up/down arrows)
- **Command Registry** (`src/commands/`): Extensible command table in `commands.cpp`
- **TFT Display** (`src/commands/command/tft.cpp`): Visual output with color/text controls
- **Utilities** (`src/utilities.cpp`): Color parsing (hex/RGB), time parsing (1h2m3s), string helpers

## Key Patterns

- **Command Structure**: Add new commands to `commandTable[]` in `commands.cpp` with function pointer and help text
- **Argument Handling**: Commands receive `String arguments` - and automatically use `stripBeginning()` for parsing
- **State Management**: Global variables track UI state (e.g., `showPrompt`, `command`, TFT colors/position)
- **Output**: `Serial.println()` for console feedback, TFT functions for display
- **Color Input**: Accepts "#RRGGBB" or "R,G,B" formats, converts to RGB565 via `parseColorInput()`
- **Time Parsing**: Natural format like "30m" or "1h 30m" via `parseTime()`, outputs formatted strings

## Development Workflow

- **Build**: `pio run` (PlatformIO)
- **Upload**: `pio run -t upload`
- **Monitor**: `pio device monitor` (9600 baud)
- **Board**: lilygo-t-display (ESP32 with TFT)
- **Library**: TFT_eSPI@^2.5.43

## Conventions

- Header guards with `#pragma once` and `#ifndef`
- Extern declarations in headers for globals/functions
- TFT operations clear screen on config changes (orientation, colors, size)
- History buffer: 5 commands max (`HISTORY_SIZE`)
- Deep sleep: Use `esp_sleep_enable_timer_wakeup()` with microseconds

## Adding Features

1. Define command function in appropriate module (e.g., `tft.cpp` for display commands)
2. Add prototype to header (e.g., `commands/command/tft.h`)
3. Register in `commandTable[]` with help text
4. Update `commands.h` externs if needed

## Example: New TFT Command

````cpp
// In tft.cpp
void TFTdrawCircle(String arguments) {
    // Parse arguments, draw on tft
    Serial.println("Circle drawn");
}

// In tft.h
extern void TFTdrawCircle(String arguments);

// In commands.cpp
{"circle", TFTdrawCircle, "Draw circle on TFT"},
```</content>
<parameter name="filePath">c:\Users\sebas\OneDrive\Documents\Projects\cpp\esp32serialos\.github\copilot-instructions.md
````
