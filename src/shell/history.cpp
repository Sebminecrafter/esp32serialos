#include <Arduino.h>
#include "shell/shell.h"
#include "config.h"
#include "utilities/utilities.h"
String history[HISTORY_SIZE];
int historyCount = 0;
int historyIndex = -1;
String historyFirstSave = ""; // for saving command after scrolling up in history

void addToHistory(const String &cmd)
{
    if (cmd.length() == 0)
        return;

    if (historyCount < HISTORY_SIZE)
    {
        history[historyCount++] = cmd;
    }
    else
    {
        for (int i = 1; i < HISTORY_SIZE; i++)
        {
            history[i - 1] = history[i];
        }
        history[HISTORY_SIZE - 1] = cmd;
    }
}
bool handleHistoryKeys(char c)
{
    static bool esc = false;
    static uint8_t escPos = 0;

    // Start of escape sequence
    if (c == 0x1B)
    { // ESC
        esc = true;
        escPos = 0;
        return true;
    }
    if (!esc)
        return false;
    escPos++;
    // ESC [
    if (escPos == 1 && c == '[')
        return true;
    // Final key
    if (escPos == 2)
    {
        esc = false;
        // Up arrow
        if (c == 'A')
        {
            if (historyIndex == -1)
            {
                historyFirstSave = command;
            }
            if (historyCount > 0 && historyIndex < historyCount - 1)
            {
                historyIndex++;
                command = history[historyCount - 1 - historyIndex];
                redrawLine();
            }
            return true;
        }
        else if (c == 'B')
        { // Down arrow
            if (historyIndex > 0)
            {
                historyIndex--;
                command = history[historyCount - 1 - historyIndex];
            }
            else
            {
                historyIndex = -1;
                command = historyFirstSave;
            }
            redrawLine();
            return true;
        }
        else if (c == 'C')
        { // Right arrow
            return true;
        }
        else if (c == 'D')
        { // Left arrow
            return true;
        }
    }

    esc = false;
    return false;
}