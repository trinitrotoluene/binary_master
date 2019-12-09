#pragma once
#include "button.hpp"

class Array {
    public:
    static int Count(Button[], int, bool(*)(Button));
    static int IndexOfFirst(Button[], int, bool(*)(Button));
};
