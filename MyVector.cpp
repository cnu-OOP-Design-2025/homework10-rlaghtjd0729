// MyVector.cpp
#include "MyVector.h"
#include <algorithm>
#include <stdexcept>
#include <cstring>


template<typename T>
void MyVector<T>::reallocate(size_t new_cap) {
    if (new_cap <= cap) return;

    T* new_data = new T[new_cap];
    
    for (size_t i = 0; i < length; ++i) {
        new_data[i] = data[i];
    }
    
    delete[] data;
    data = new_data;
    cap = new_cap;
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> init) {
    length = init.size();
    cap = length;
    data = new T[cap];
    size_t i = 0;
    for (const auto& val : init) {
        data[i++] = val;
    }
}

template<typename T>
MyVector<T>::MyVector(): data(nullptr), length(0), cap(0) {}

template<typename T>
MyVector<T>::~MyVector() { delete[] data; }

template<typename T>
MyVector<T>::MyVector(const MyVector& other) : length(other.length), cap(other.cap) {
    if (cap > 0) {
        data = new T[cap];
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    } else {
        data = nullptr;
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        if (cap < other.length) {
            delete[] data;
            cap = other.cap;
            data = new T[cap];
        }
        length = other.length;
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept : data(other.data), cap(other.cap), length(other.length) {
    other.data = nullptr;
    other.cap = 0;
    other.length = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] data;

        data = other.data;
        cap = other.cap;
        length = other.length;

        other.data = nullptr;
        other.cap = 0;
        other.length = 0;
    }
    return *this;
}


template<typename T>
void MyVector<T>::push_back(const T& val) {
    if (length == cap) {
        reallocate(cap == 0 ? 1 : cap * 2);
    }
    data[length++] = val;
}

template<typename T>
void MyVector<T>::pop_back() {
    if (length > 0) {
        --length;
    }
}

template<typename T>
size_t MyVector<T>::size() const { return length; }

template<typename T>
T& MyVector<T>::operator[](size_t i) { return data[i]; }

template<typename T>
const T& MyVector<T>::operator[](size_t i) const { return data[i]; }

template<typename T>
T& MyVector<T>::at(size_t i) {
    if (i >= length) {
        throw std::out_of_range("MyVector::at: index out of range");
    }
    return data[i];
}

template<typename T>
const T& MyVector<T>::at(size_t i) const {
    if (i >= length) {
        throw std::out_of_range("MyVector::at: index out of range");
    }
    return data[i];
}

template<typename T>
T& MyVector<T>::front() { 
    if (empty()) { throw std::out_of_range("MyVector::front: vector is empty"); }
    return data[0]; 
}

template<typename T>
const T& MyVector<T>::front() const { 
    if (empty()) { throw std::out_of_range("MyVector::front: vector is empty"); }
    return data[0]; 
}

template<typename T>
T& MyVector<T>::back() { 
    if (empty()) { throw std::out_of_range("MyVector::back: vector is empty"); }
    return data[length - 1]; 
}

template<typename T>
const T& MyVector<T>::back() const { 
    if (empty()) { throw std::out_of_range("MyVector::back: vector is empty"); }
    return data[length - 1]; 
}

template<typename T>
size_t MyVector<T>::capacity() const { return cap; }

template<typename T>
bool MyVector<T>::empty() const { return length == 0; }

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    ptrdiff_t index = pos.ptr - data;

    if (length == cap) {
        reallocate(cap == 0 ? 1 : cap * 2);
        pos.ptr = data + index; 
    }

    for (size_t i = length; i > (size_t)index; --i) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    ++length;

    return Iterator(data + index);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    if (empty() || pos.ptr == end().ptr) {
        return end();
    }
    
    ptrdiff_t index = pos.ptr - data;

    for (size_t i = index; i < length - 1; ++i) {
        data[i] = data[i + 1];
    }
    
    --length;

    return Iterator(data + index);
}

template<typename T>
void MyVector<T>::clear() {
    length = 0;
}

template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; ++i) {
        if (!(data[i] == other.data[i])) return false;
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
    return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
}

template<typename T>
bool MyVector<T>::operator>(const MyVector& other) const {
    return other < *this;
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector& other) const {
    return !(*this > other);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector& other) const {
    return !(*this < other);
}

template<typename T>
T& MyVector<T>::Iterator::operator*() const { return *ptr; }

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    --ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}


template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(ptrdiff_t n) const {
    return Iterator(ptr + n);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(ptrdiff_t n) const {
    return Iterator(ptr - n);
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator+=(ptrdiff_t n) {
    ptr += n;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator-=(ptrdiff_t n) {
    ptr -= n;
    return *this;
}

template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

template<typename T>
ptrdiff_t MyVector<T>::Iterator::operator-(const Iterator& other) const {
    return ptr - other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator<(const Iterator& other) const {
    return ptr < other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator>(const Iterator& other) const {
    return ptr > other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator<=(const Iterator& other) const {
    return ptr <= other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator>=(const Iterator& other) const {
    return ptr >= other.ptr;
}


template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(data);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    return Iterator(data + length);
}

template<typename T>
const typename MyVector<T>::Iterator MyVector<T>::begin() const {
    return Iterator(data);
}

template<typename T>
const typename MyVector<T>::Iterator MyVector<T>::end() const {
    return Iterator(data + length);
}

template class MyVector<int>;