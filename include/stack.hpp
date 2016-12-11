//
// Created by anna on 03.12.16.
//


/*
Реализовать класс `allocator`, использующий для выделения
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

#include <iostream>
#include <exception>
#include <cstring>
#include <algorithm>
#include <iterator>

template <typename T>
class stack
{
public:
    stack();
    ~stack();
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

private:
    size_t count;
    size_t arr_size;
    T* array;
};

template <typename T>
stack<T>::stack() : count(0), arr_size(1), array(new T[arr_size]) {}

template <typename T>
auto stack<T>::length() const noexcept -> size_t
{
    return count;
}

template <typename T>
auto stack<T>::push_back(const T& data) /* strong */ -> void
{
    bool was_enlarged = false;
    T* longer_array = nullptr;
    T* control_array = array;

    if(count == arr_size)
    {
        arr_size *= 2;
        try
        {
            longer_array = new T[arr_size];
            std::copy(array, array + count, longer_array);
            array = nullptr;
        }
        catch(...)
        {
            arr_size /= 2;
            array = control_array;
            control_array = nullptr;

            delete [] longer_array;

            std::cerr << "stack<T>::push_back(" << data << ") threw an exception!" << std::endl;
            return;
        }
        array = longer_array;
        was_enlarged = true;
        longer_array = nullptr;
    }

    try
    {
        array[count] = data;
    }
    catch(...)
    {
        if(was_enlarged)
        {
            delete [] array;
            arr_size /= 2;
            array = control_array;
            control_array = nullptr;
        }    
        std::cerr << "stack<T>::push_back(" << data << ") threw an exception!" << std::endl;
        std::cerr << "probably it happend in the copy c-tor of your template type" << std::endl;
        return;
    }

    if(was_enlarged)
    {
        try
        {
            delete [] control_array;
        }
        catch(...) {}
    }
    control_array = nullptr;
    count++;
}

template <typename T>
auto stack<T>::top() const noexcept -> const T*
{
    if(count == 0)
        return nullptr;
    return &array[count - 1];
}

template <typename T>
auto stack<T>::pop() noexcept -> void try
{
    if(count == 0)
        throw std::underflow_error("stack is empty.");
    --count;
}
catch(std::underflow_error& err)
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
