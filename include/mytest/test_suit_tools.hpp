#pragma once
#include <string>

namespace mytest {
    const std::string ANSI_COLOR_GREEN = "\x1b[32m";
    const std::string ANSI_COLOR_RESET = "\x1b[0m";

    int assert(bool expr, std::string true_message, std::string false_message);

    void assert_abort(bool expr, std::string true_message, std::string false_message);
}