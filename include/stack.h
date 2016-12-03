//
// Created by anna on 03.12.16.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <iostream>
#include <exception>

template <typename T>
class stack
{
public:
    class something_bad : public std::logic_error
    {
    public:
        something_bad(const std::string& data = "") : logic_error(data) {}
    };

    stack();
    auto length() const noexcept -> size_t;
    auto push_back(const T&) -> void;
    auto pop() -> T;
    ~stack();

    static auto memcpy(T* dest, const T* src, size_t size) noexcept -> T*
    {
        for(size_t i = 0; i < size; ++i)
            *(dest + i) = src[i];
        return dest;
    }

    friend auto operator << (std::ostream& out, const stack<T>& st) -> std::ostream&
    {
        for(size_t i = 0; i < st.count + 1; ++i)
            out << st.array[i] << " ";
        out << "\n";
        return out;
    }

    auto operator == (const stack&) -> bool;

private:
    size_t count; //last element position
    size_t arr_size;
    T* array;
};

template <typename T>
stack<T>::stack() : count(-1), arr_size(5), array(new T[arr_size]) {}

template <typename T>
auto stack<T>::length() const noexcept -> size_t
{
    return (count + 1);
}

template <typename T>
auto stack<T>::push_back(const T& data) -> void
{
    if(count + 1 == arr_size) //if stack is full
    {
        arr_size += 5;
        T* longer_array = new T[arr_size];
        longer_array = stack<T>::memcpy(longer_array, array, arr_size);
        delete [] array;
        array = longer_array;
        longer_array = nullptr;
    }
    count++;
    array[count] = data;
}

template <typename T>
auto stack<T>::pop() -> T
{
    if(count == -1)
        throw stack<T>::something_bad("stack is empty.");
    T prev_top = array[count];
    --count;
    return prev_top;
}

template <typename T>
stack<T>::~stack()
{
    if(arr_size)
        delete [] array;
}

template <typename T>
auto stack<T>::operator == (const stack<T>& rhs) -> bool
{
    if(count != rhs.count)
        return false;
    for(size_t i = 0; i < (count + 1); ++i)
        if(array[i] != rhs.array[i])
            return false;
    return true;
}



#endif //STACK_STACK_H
