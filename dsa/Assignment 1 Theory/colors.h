#ifndef COLORS_H
#define COLORS_H

#include <string>

namespace Color {
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";

    const std::string BOX_TOP_LEFT = "┌";
    const std::string BOX_TOP_RIGHT = "┐";
    const std::string BOX_BOTTOM_LEFT = "└";
    const std::string BOX_BOTTOM_RIGHT = "┘";
    const std::string BOX_HORIZONTAL = "─";
    const std::string BOX_VERTICAL = "│";
}

#endif
