//
// Created by anna on 03.12.16.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <allocator.hpp>
#include <exception>
//#include <cstring>
#include <iterator>

template <typename T>
class stack : private allocator<T>
{
public:
    stack();
    auto pop() noexcept -> void;
    auto top() const /* strong */ -> T;
    auto empty() const noexcept -> bool;
    auto length() const noexcept -> size_t;
    auto push_back(const T&) /* strong */ -> void;

    auto operator == (const stack&) -> bool;

    friend auto operator << (std::ostream& out, const stack<T>& st) -> std::ostream&
    {
        std::copy(st.allocator<T>::array,
                  st.allocator<T>::array + st.allocator<T>::count,
                  std::ostream_iterator<T>(out, " "));
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
auto stack<T>::top() const /* strong */ -> T try
{
    if(allocator<T>::count == 0)
        throw std::underflow_error("stack is empty.");
    return allocator<T>::array[allocator<T>::count - 1];
}
catch(std::underflow_error& err)
{
    std::cerr << "stack<T>::top() threw an exception" << std::endl;
    std::cerr << err.what() << std::endl;
    throw;
}
catch(...)
{
    std::cerr << "stack<T>::top() threw an exception" << std::endl;
    throw;
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
    return allocator<T>::count ? false : true;
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
