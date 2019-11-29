#pragma once

#define make_predicate(t) bool(*predicate)(t)

template <typename T>
class Array {
    public:
    static int Count(T*, int, make_predicate(T));
    static int IndexOfFirst(T*, int, make_predicate(T));
};

template <typename T>
int Array<T>::Count(T* array, int length, make_predicate(T)) {
    int ctr = 0;
    for (int i = 0; i < length; i++)
        ctr += predicate(array[i]);
    return ctr;
}

template <typename T>
int Array<T>::IndexOfFirst(T* array, int length, make_predicate(T)) {
    for (int i = 0; i < length; i++)
        if (predicate(array[i])) return i;
    return -1;
}