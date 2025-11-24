#include <iostream>
#include <mytest/test_suit_tools.hpp>

int mytest::assert(bool expr, std::string true_message, std::string false_message)
{
    if (!expr) {
        std::fprintf(stderr, "%s", (false_message + "\n").c_str());
        return 1;
    } else {
        std::fprintf(stdout, "%s", (mytest::ANSI_COLOR_GREEN + true_message + mytest::ANSI_COLOR_RESET + "\n").c_str());
        return 0;
    }
}

void mytest::assert_abort(bool expr, std::string true_message, std::string false_message)
{
    if (!mytest::assert(expr, true_message, false_message))
    {
        abort();
    }
}