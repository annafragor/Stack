//
// Created by anna on 12.12.16.
//

#ifndef STACK_ALLOCATOR_HPP
#define STACK_ALLOCATOR_HPP

#include <iostream>
#include <algorithm>

template <typename T>
class allocator
{
protected:
    size_t count;
    size_t arr_size;
    T* array;

    allocator(size_t size_i = 0);
    allocator(const allocator&) = delete;
    ~allocator();

    auto allocate() -> void;
    auto deallocate() -> void;
    auto swap(allocator&) noexcept -> void;
    auto operator =(const allocator&) -> allocator& = delete;
};

template <typename T>
allocator<T>::allocator(size_t size_i)
{
    count = 0;
    arr_size = size_i;
    array = static_cast<T*>(::operator new(arr_size * sizeof(T)));
}

template <typename T>
allocator<T>::~allocator()
{
    for(size_t i = 0; i < count; i++)
        array[i].~T();
    ::operator delete[](array);
}

template <typename T>
auto allocator<T>::swap(allocator& rhs) noexcept -> void
{
    std::swap(array, rhs.array);
    std::swap(count, rhs.count);
    std::swap(arr_size, rhs.arr_size);
}

template <typename T>
auto allocator<T>::allocate() -> void
{
    T* control_array = array;
    size_t control_count = count;

    arr_size *= 2;
    try
    {
        allocator<T> longer(arr_size);
        std::copy(array, array + count, longer.array);
        longer.count = count;
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

template <typename T>
auto allocator<T>::deallocate() -> void
{
    arr_size /= 2;
    allocator<T> shorten(arr_size);
    std::copy(array, array + count, shorten.array);
    swap(shorten);
}

#endif //STACK_ALLOCATOR_HPP
