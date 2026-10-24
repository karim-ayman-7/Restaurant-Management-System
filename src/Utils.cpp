#include "Utils.h"

#include <iostream>
#include <limits>
#include <cstdlib>
#include <cstdio>

#ifdef _WIN32
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

using namespace std;

void ClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear && printf '\\033[3J'");
#endif
}


int GetTerminalWidth()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
        return 80;

    return info.srWindow.Right - info.srWindow.Left + 1;
#else
    struct winsize w{};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 || w.ws_col == 0)
        return 80;

    return w.ws_col;
#endif
}


void PrintLine(char symbol)
{
    cout << string(GetTerminalWidth(), symbol) << endl;
}


void PrintCentered(const string& text)
{
    int terminalWidth = GetTerminalWidth();
    int spaces = (terminalWidth - static_cast<int>(text.length())) / 2;

    if (spaces < 0)
        spaces = 0;

    cout << string(spaces, ' ') << text << endl;
}


bool ReadInt(int& value)
{
    if (!(cin >> value))
    {
        if (cin.eof())
        {
            cout << endl << "Input ended. Exiting program." << endl;
            exit(0);
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    int next = cin.peek();

    if (next != '\n' && next != EOF)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}


string ReadLine()
{
    string line;

    if (!getline(cin, line))
    {
        cout << endl << "Input ended. Exiting program." << endl;
        exit(0);
    }

    return line;
}


bool ReadYesNo()
{
    while (true)
    {
        string answer = ReadLine();

        if (answer == "y" || answer == "Y")
            return true;

        if (answer == "n" || answer == "N")
            return false;

        cout << "Invalid choice! Enter y or n only." << endl;
    }
}

void PauseAndWaitForEnter()
{
    cout << endl << "Press Enter to continue...";
    cin.get();
}
