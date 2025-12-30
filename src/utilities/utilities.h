#pragma once
#include <Arduino.h>

extern uint16_t parseColorInput(String input);                // Convert color (hex or r,g,b) to RGB565
extern String stripBeginning(String text, String removeText); // Remove specified text from the beginning of text (if it IS in the beginning)
extern uint64_t parseTime(String input);                      // Natural-ish language time parsing
extern String formatTime(uint64_t totalSeconds);              // Format seconds to _h _m _s
extern int getNumOf(String args, char delimiter);             // Get number of delimiter

extern void print(const char *text);
extern void print(const String &text);
extern void print(char c);
extern void print();
extern void println(const char *text);
extern void println(const String &text);
extern void println(char c);
extern void println();