//
// Created by anna on 12.12.16.
//

#ifndef STACK_ALLOCATOR_HPP
#define STACK_ALLOCATOR_HPP
#pragma once

#include <iostream>

template <typename T>
class allocator
{
public:
    allocator(size_t size_i = 0);
    ~allocator();

    auto allocate() -> T*;
    auto swap(allocator&) noexcept -> void;

    allocator(const allocator&) = delete;
    auto operator =(const allocator&) -> allocator& = delete;

protected:
    size_t count;
    size_t arr_size;
    T* array;
};

template <typename T>
allocator<T>::allocator(size_t size_i) : count(0), arr_size(size_i), array(new T[arr_size]) {}

template <typename T>
allocator<T>::~allocator()
{
    delete [] array;
}

template <typename T>
auto allocator<T>::swap(allocator& rhs) noexcept -> void
{
    T* tmp_arr = array;
    array = rhs.array;
    rhs.array = tmp_arr;

    size_t tmp_count = count;
    count = rhs.count;
    rhs.count = tmp_count;

    size_t tmp_size = arr_size;
    arr_size = rhs.arr_size;
    rhs.arr_size = tmp_size;
}

template <typename T>
auto allocator<T>::allocate() -> T*
{
    T* control_array = array;
    size_t control_count = count;

    arr_size *= 2;
    try
    {
        allocator<T> longer(arr_size);
        std::copy(array, array + count, longer.array);
        swap(longer);
    }
    catch(...)
    {
        array = control_array;
        arr_size /= 2;
        control_array = nullptr;
        std::cerr << "an error happend when memory allocation" << std::endl;
        throw;
    }
}

#endif //STACK_ALLOCATOR_HPP
