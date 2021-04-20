/*

##########
by cyber-ikaros with love
##########

*/

#include <iostream>
#include<windows.h>
#include <thread> 
#include <math.h> 

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void SetCoolConsoleFont()
{
    CONSOLE_FONT_INFOEX cf = { 0 };
    cf.cbSize = sizeof cf;
    cf.dwFontSize.X = 12;
    cf.dwFontSize.Y = 16;
    wcscpy_s(cf.FaceName, L"Terminal");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cf);
}

void SetCursorPosition(const int x, const int y)
{
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void PrintAt(string in_s, int x, int y)
{
    SetCursorPosition(x, y);
    cout << in_s;
}

void PrintColoredAt(string in_s, int x, int y, int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    PrintAt(in_s, x, y);
}

void PrintHorizontalRotated(string in_s, int x, int y, int alpha, int color)
{
    string a = in_s;
    int clampedAlpha = alpha % a.length();
    rotate(a.begin(), a.begin() + clampedAlpha, a.end());
    PrintColoredAt(a, x, y, color);
}

void PrintColoredFrame(string in_s, int x, int y, int color, int alpha)
{
    for (int j = x; j < x+in_s.length()+2; j++)
    {
        PrintColoredAt("-", j, y-1, color);
    }
    PrintColoredAt("|", x, y, color);
    PrintHorizontalRotated(in_s, x+1, y, color, alpha);
    PrintColoredAt("|", x+in_s.length()+1, y, color);
    for (int j = x; j < x+in_s.length()+2; j++)
    {
        PrintColoredAt("-", j, y+1, color);
    }
}

void PrintAnotherColoredFrame(string in_s, int x, int y, int color)
{
    for (int j = x; j < x + in_s.length() + 2; j++)
    {
        PrintColoredAt("-", j, y - 1, color);
    }
    PrintColoredAt("|", x, y, color);
    PrintColoredAt(in_s, x + 1, y, color);
    PrintColoredAt("|", x + in_s.length() + 1, y, color);
    for (int j = x; j < x + in_s.length() + 2; j++)
    {
        PrintColoredAt("-", j, y + 1, color);
    }
}

void PrintRotated(string in_s, int x, int y, int color, int origin, int rotation)
{
    rotation = rotation % 8;
    if (origin == 0)
    {
        int length = in_s.length();
        switch (rotation)
        {
        case 0:
            for (int i = 0; i < length; i++)
            { PrintColoredAt(string{ in_s[i] }, x+i, y, color); }
            break;
        case 1:
            for (int i = 0; i < length; i++)
            { PrintColoredAt(string{ in_s[i] }, x + i, y + i, color); }
            break;
        case 2:
            for (int i = 0; i < length; i++)
            { PrintColoredAt(string{ in_s[i] }, x, y + i, color); }
            break;
        case 3:
            for (int i = 0; i < length; i++)
            { PrintColoredAt(string{ in_s[i] }, x-i, y+i, color); }
            break;
        case 4:
            for (int i = 0; i < length; i++)
            { PrintColoredAt(string{ in_s[i] }, x - i, y, color); }
            break;
        case 5:
            for (int i = 0; i < length; i++)
            { PrintColoredAt(string{ in_s[i] }, x - i, y - i, color); }
            break;
        case 6:
            for (int i = 0; i < length; i++)
            { PrintColoredAt(string{ in_s[i] }, x, y - i, color); }
            break;
        case 7:
            for (int i = 0; i < length; i++)
            { PrintColoredAt(string{ in_s[i] }, x + i, y - i, color); }
            break;
        }
    }
}

void ClearSector(int fromX, int fromY, int size)
{
    for (int i = fromY; i < fromY + size + 1; i++)
    {
        string a = "";
        for (int j = 0; j < size; j++)
            a.append(" ");

        PrintAt(a, fromX, i);
    }
}

int main()
{
    //set console settings
    SetCoolConsoleFont();
    ShowConsoleCursor(false);

    //colored text!!!
    for (int i = 5; i < 14; i++)
    {
        this_thread::sleep_for(std::chrono::milliseconds(100));
        PrintAnotherColoredFrame(" Hello! I'm TorgaW! ", 10, 6, i);
        ClearSector(10, 9, 17);
        PrintRotated(" Hello! ", 20, 15, i+1, 0, i-5);
        PrintColoredFrame(" Hello! ", 15, 25, i, i);
        if (i == 13) i = 5;
    }
}

