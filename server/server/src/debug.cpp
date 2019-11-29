#include "debug.hpp"

void Debug::printLn(const char *format, ...) {
    char printBuffer [100];

    va_list argList;
    va_start(argList, format);

    vsprintf(printBuffer, format, argList);

    Serial.println(printBuffer);

    va_end(argList);
}