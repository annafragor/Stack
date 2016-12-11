//
// Created by anna on 03.12.16.
//

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
	auto top() const noexcept -> T*;
	auto empty() const noexcept -> bool;
	auto length() const noexcept -> size_t;
	auto push_back(const T&) noexcept -> void;

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
auto stack<T>::push_back(const T& data) noexcept -> void
{
	bool was_enlarged = false;
	if(count == arr_size) //if stack is full
	{		
	arr_size *= 2;

		T* longer_array = nullptr;
		try
		{
			longer_array = new T[arr_size];
			std::copy(array, array + count, longer_array);
			delete [] array;
		}
		catch(...)
		{
			delete [] longer_array; arr_size /= 2;
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
			arr_size /= 2;
			T* shorten_array = new T[arr_size];
			std::copy(array, array + count, shorten_array);
			delete [] array;
			array = shorten_array;
			shorten_array = nullptr;	
		}	
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
