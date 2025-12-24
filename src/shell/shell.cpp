#include "shell.h"
#include "utilities.h"

String command = ""; // init command string

void redrawLine()
{                             // Redraw current command line
    Serial.print("\r\033[K"); // clear line
    Serial.print(PROMPT);
    Serial.print(command);
}

void processCommand(String input)
{
    input.trim();
    if (input.length() == 0)
        return;

    int spaceIndex = input.indexOf(' ');
    String command = (spaceIndex == -1)
                         ? input
                         : input.substring(0, spaceIndex);

    for (uint8_t i = 0; i < commandCount; i++)
    {
        if (command.equals(commandTable[i].command))
        {
            input = stripBeginning(input, command);
            commandTable[i].function(stripBeginning(input, " "));
            return;
        }
    }

    Serial.println("Unknown command: `" + command + "` type help for a list of commands.");
}