//
// Created by anna on 03.12.16.
//

/*
 * Реализовать класс `allocator`, использующий для выделения
памяти `operator new` и сделать его базовым для класса `stack`.

Интерфейс класса `allocator`:

template <typename T>
class allocator
{
protected:
   allocator(size_t size = 0);
   ~allocator();
   auto swap(allocator& other) -> void;
   allocator(allocator const&) = delete;
   auto operator =(allocator const&) -> allocator& = delete;

   T * ptr_;
   size_t size_;
   size_t count_;
};
 */

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include "allocator.hpp"

#include <iostream>
#include <exception>
#include <cstring>
#include <algorithm>
#include <iterator>

template <typename T>
class stack : public allocator<T>
{
public:
    stack();
    ~stack() {}
    auto pop() noexcept -> void;
    auto top() const noexcept -> const T*;
    auto empty() const noexcept -> bool;
    auto length() const noexcept -> size_t;
    auto push_back(const T&) /* strong */ -> void;

    auto operator == (const stack&) -> bool;

    friend auto operator << (std::ostream& out, const stack<T>& st) -> std::ostream&
    {

        std::copy(st.array, st.array + st.count, std::ostream_iterator<T>(out, " "));
        out << "\n";
        return out;
    }
};

template <typename T>
stack<T>::stack() : allocator<T>(1) {}

template <typename T>
auto stack<T>::length() const noexcept -> size_t
{
    return allocator<T>::count;
}

template <typename T>
auto stack<T>::push_back(const T& data) /* strong */ -> void
{
    bool was_enlarged = false;
    if(allocator<T>::count == allocator<T>::arr_size)
    {
        try
        {
            allocator<T>::allocate();
        }
        catch(...) { return; }
        was_enlarged = true;
    }

    try
    {
        allocator<T>::array[allocator<T>::count] = data;
    }
    catch(...)
    {
        if(was_enlarged)
        {
            allocator<T>::arr_size /= 2;
            allocator<T> shorten(allocator<T>::arr_size);
            std::copy(allocator<T>::array, allocator<T>::array + allocator<T>::count, shorten.array);
            allocator<T>::swap(shorten);
        }    
        std::cerr << "stack<T>::push_back(" << data << ") threw an exception!" << std::endl;
        std::cerr << "probably it happend in the copy c-tor of your template type" << std::endl;
        return;
    }
    allocator<T>::count++;
}

template <typename T>
auto stack<T>::top() const noexcept -> const T*
{
    if(allocator<T>::count == 0)
        return nullptr;
    return &allocator<T>::array[allocator<T>::count - 1];
}

template <typename T>
auto stack<T>::pop() noexcept -> void try
{
    if(allocator<T>::count == 0)
        throw std::underflow_error("stack is empty.");
    --allocator<T>::count;
}
catch(std::underflow_error& err)
{
    std::cerr << "stack<T>::pop() threw an exception" << std::endl;
    std::cerr << err.what() << std::endl;
}

template <typename T>
auto stack<T>::empty() const noexcept -> bool
{
    if(allocator<T>::count == 0)
        return true;
    return false;
}

template <typename T>
auto stack<T>::operator == (const stack<T>& rhs) -> bool
{
    if(allocator<T>::count != rhs.allocator<T>::count)
        return false;
    for(size_t i = 0; i < allocator<T>::count; ++i)
        if(allocator<T>::array[i] != rhs.allocator<T>::array[i])
            return false;
    return true;
}

#endif //STACK_STACK_H
