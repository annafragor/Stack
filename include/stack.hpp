//
// Created by anna on 03.12.16.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <iostream>
#include <exception>
#include <cstring>

template <typename T>
class stack
{
public:
    class stack_underflow : public std::logic_error
    {
    public:
        stack_underflow(const std::string& data = "") : logic_error(data) {}
    };

    stack();
    ~stack();
    auto pop() noexcept -> void;
    auto top() const noexcept -> T*;
    auto empty() const noexcept -> bool;
    auto length() const noexcept -> size_t;
    auto push_back(const T&) noexcept -> void;

    auto operator == (const stack&) -> bool;

    friend auto operator << (std::ostream& out, const stack<T>& st) -> std::ostream&
    {
        for(size_t i = 0; i < st.count; ++i)
            out << st.array[i] << " ";
        out << "\n";
        return out;
    }

private:
    size_t count;
    size_t arr_size;
    T* array;
};

template <typename T>
stack<T>::stack() : count(0), arr_size(5), array(new T[arr_size]) {}

template <typename T>
auto stack<T>::length() const noexcept -> size_t
{
    return count;
}

template <typename T>
auto stack<T>::push_back(const T& data) noexcept -> void
{
    if(count == arr_size) //if stack is full
    {
        arr_size += 5;

        T* longer_array = nullptr;
        try
        {
            longer_array = new T[arr_size];

            for (auto i = 0; i < count; ++i)
                longer_array[i] = array[i];
        }
        catch(...)
        {
            delete [] longer_array;
            std::cerr << "stack<T>::push_back(" << data << ") threw an exception!" << std::endl;
            return;
        }

        delete [] array;
        array = longer_array;
        longer_array = nullptr;
    }

    try
    {
        array[count] = data;
    }
    catch(...)
    {
        std::cerr << "stack<T>::push_back(" << data << ") threw an exception!" << std::endl;
        std::cerr << "probably it happend in the copy c-tor of your template type" << std::endl;
        return;
    }
    count++;
}

template <typename T>
auto stack<T>::top() const noexcept -> T*
{
    if(count == 0)
        return nullptr;
    return &array[count - 1];
}

template <typename T>
auto stack<T>::pop() noexcept -> void try
{
    if(count == 0)
        throw stack<T>::stack_underflow("stack is empty.");
    --count;
}
catch(stack<T>::stack_underflow& err)
{
    std::cerr << "stack<T>::pop() threw an exception" << std::endl;
    std::cerr << err.what() << std::endl;
}

template <typename T>
auto stack<T>::empty() const noexcept -> bool
{
    if(count == 0)
        return true;
    return false;
}

template <typename T>
stack<T>::~stack()
{
    delete [] array;
}

template <typename T>
auto stack<T>::operator == (const stack<T>& rhs) -> bool
{
    if(count != rhs.count)
        return false;
    for(size_t i = 0; i < count; ++i)
        if(array[i] != rhs.array[i])
            return false;
    return true;
}

#endif //STACK_STACK_H
