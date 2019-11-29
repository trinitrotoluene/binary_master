#pragma once

#include <stdio.h>
#include <Arduino.h>

// Arduino.h gives va_list a funky name.
typedef __gnuc_va_list va_list;

class Debug {
    public:
    static void printLn(const char*, ...);
};

// Comment this out to globally disable Debugging for the application.
// TODO: This MUST be disabled before submitting!
#define ENABLE_DEBUG

// By default Debug::printLn will no-op, allowing us to use serial tx/rx without having to remove calls to this method
// and instead just removing a #define.
#ifndef ENABLE_DEBUG
void Debug::printLn(const char*, ...) { return; }
#else
void Debug::printLn(const char *format, ...) {
    char printBuffer [100];

    va_list argList;
    va_start(argList, format);

    vsprintf(printBuffer, format, argList);

    Serial.println(printBuffer);

    va_end(argList);
}
#endif
