#pragma once

#include <stdio.h>
#include <Arduino.h>

typedef __gnuc_va_list va_list;

class Debug {
    public:
    static void printLn(const char*, ...);
};