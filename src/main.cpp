#include <Arduino.h>
#include "config.h"
#include "shell/shell.h"
#include "utilities.h"
#include "commands/commands.h"
#include "commands/command/tft/tft.h"
#include "misc/startuplogo.h"

bool showPrompt = true; // init prompt display

void setup()
{
  Serial.begin(BAUD_RATE);
  tft.init();
  startTFT();
  splash();
  while (Serial.available() == 0)
  {
    Serial.println("Waiting for input...");
    delay(1000);
  }
  clearScreen();

  // Deep sleep cause?
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == 4)
  {
    Serial.println("Awoken from deep sleep.");
  }
  Serial.println("");
}

void loop()
{
  // Show prompt once per command
  if (showPrompt)
  {
    Serial.print(PROMPT);
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
      Serial.println(); // move to next line
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
        Serial.print("\b \b"); // erase character on terminal
      }
    }
    // Normal character
    else
    {
      command += c;
      Serial.print(c); // echo character
    }
  }
}