#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <string>

template <typename T = int>
class Array {
private:
    T * data;
    size_t asize;

public:
    Array(size_t size = 1) : asize(size) {
        data = new T[asize];
    }

    Array(std::initializer_list<T> list) : Array(list.size()) {
        size_t i = 0;
        for (const auto& item : list) {
            data[i++] = item;
        }
    }

    Array(const Array& other) : asize(other.asize) {
        data = new T[asize];
        for (size_t i = 0; i < asize; ++i) {
            data[i] = other.data[i];
        }
    }

    ~Array() {
        delete[] data;
    }

    size_t size() const {
        return asize;
    }

    T & operator[](size_t position) {
        if (position >= asize) {
            throw std::out_of_range("Access to [" + std::to_string(position) + "] is out of bounds");
        }
        return data[position];
    }

    const T & operator[](size_t position) const {
        if (position >= asize) {
            throw std::out_of_range("Access to [" + std::to_string(position) + "] is out of bounds");
        }
        return data[position];
    }

    Array & operator=(const Array & other) {
        if (this != &other) {
            delete[] data;
            asize = other.asize;
            data = new T[asize];
            for (size_t i = 0; i < asize; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    template <typename U>
    friend std::ostream & operator<<(std::ostream & os, const Array<U> & array);
};

template <typename T>
std::ostream & operator<<(std::ostream & os, const Array<T> & array) {
    os << "[";
    for (size_t i = 0; i < array.size(); ++i) {
        os << array[i];
        if (i < array.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif
