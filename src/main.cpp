#include <Arduino.h>
#include "config.h"
#include "shell/shell.h"
#include "utilities/utilities.h"
#include "commands/commands.h"
#ifdef USE_TFT
#include "commands/command/tft/tft_init.h"
#endif
#include "commands/command/wifi/main.h"

bool showPrompt = true; // init prompt display

void setup()
{
  Serial.begin(BAUD_RATE);
  initCommandTable();
#ifdef USE_TFT
  initTFT();
#endif
  while (Serial.available() == 0)
  {
    println("Waiting for input...");
    delay(1000);
  }
#ifdef USE_TFT
  clearTFT();
#endif
  startWifi();

  // Deep sleep cause?
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == 4)
  {
    println("Awoken from deep sleep.");
  }
  println("");
}

void loop()
{
  // Show prompt once per command
  if (showPrompt)
  {
    print(PROMPT);
    showPrompt = false;
  }
  // Read incoming characters
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    if (handleHistoryKeys(c))
    { // Handle command history
      continue;
    }
    // Handle Enter key (CR or LF)
    if (c == '\r' || c == '\n')
    {
      println(); // move to next line
      command.trim();
      if (command.length() > 0)
      {
        if (historyIndex == -1)
        {
          addToHistory(command);
        }
        processCommand(command);
      }
      command = "";
      historyFirstSave = ""; // clear buffers
      showPrompt = true;     // show prompt again
      historyIndex = -1;     // reset history navigation
    }
    // Backspace handling
    else if (c == '\b' || c == 127)
    {
      if (command.length() > 0)
      {
        command.remove(command.length() - 1);
        print("\b \b"); // erase character on terminal
      }
    }
    // Normal character
    else
    {
      command += c;
      print(c); // echo character
    }
  }
}