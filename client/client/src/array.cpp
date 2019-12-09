#include "array.hpp"

int Array::Count(Button array[], int length, bool(*predicate)(Button)) {
    int ctr = 0;
    for (int i = 0; i < length; i++)
        ctr += predicate(array[i]);
    return ctr;
}

int Array::IndexOfFirst(Button array[], int length, bool(*predicate)(Button)) {
    for (int i = 0; i < length; i++)
        if (predicate(array[i])) return i;
    return -1;
}