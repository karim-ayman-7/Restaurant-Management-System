#pragma once

#include <string>

void PauseAndWaitForEnter();
int GetTerminalWidth();
void PrintCentered(const std::string& text);
void PrintLine(char symbol = '-');
void ClearScreen();
bool ReadInt(int& value);
std::string ReadLine();
bool ReadYesNo();