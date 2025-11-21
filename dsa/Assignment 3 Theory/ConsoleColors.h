#ifndef CONSOLE_COLORS_H
#define CONSOLE_COLORS_H

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace ConsoleColors {
    enum Color {
        RESET,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    inline void setColor(Color c) {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD color;
        switch (c) {
            case RED:     color = FOREGROUND_RED; break;
            case GREEN:   color = FOREGROUND_GREEN; break;
            case YELLOW:  color = FOREGROUND_RED | FOREGROUND_GREEN; break;
            case BLUE:    color = FOREGROUND_BLUE; break;
            case MAGENTA: color = FOREGROUND_RED | FOREGROUND_BLUE; break;
            case CYAN:    color = FOREGROUND_GREEN | FOREGROUND_BLUE; break;
            case WHITE:   color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
            case RESET:   color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
            default:      color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
        SetConsoleTextAttribute(hConsole, color);
#else
        std::string colorCode;
        switch (c) {
            case RED:     colorCode = "\033[31m"; break;
            case GREEN:   colorCode = "\033[32m"; break;
            case YELLOW:  colorCode = "\033[33m"; break;
            case BLUE:    colorCode = "\033[34m"; break;
            case MAGENTA: colorCode = "\033[35m"; break;
            case CYAN:    colorCode = "\033[36m"; break;
            case WHITE:   colorCode = "\033[37m"; break;
            case RESET:   colorCode = "\033[0m"; break;
            default:      colorCode = "\033[0m";
        }
        std::cout << colorCode;
#endif
    }
}

#endif
