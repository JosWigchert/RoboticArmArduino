#pragma once

#include <Arduino.h>

namespace Split
{
    void split(String toSplit, char delimiter, String* array, int arraySize, int &count);
}