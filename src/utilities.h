#pragma once
#include <Arduino.h>

extern uint16_t parseColorInput(String input);                // Convert color (hex or r,g,b) to RGB565
extern String stripBeginning(String text, String removeText); // Remove specified text from the beginning of text (if it IS in the beginning)
extern uint64_t parseTime(String input);                      // Natural-ish language time parsing
extern String formatTime(uint64_t totalSeconds);              // Format seconds to _h _m _s