//
// Created by anna on 03.12.16.
//

#include <stack.hpp>
#include "catch.hpp"

SCENARIO("if stack is empty => length must increase")
{
    GIVEN("empty stack")
    {
        stack<size_t> st;
        WHEN("try to push new element")
        {
            st.push_back(1);
            THEN("length must be equal to 1")
            {
                REQUIRE(st.length() == 1);
            }
        }
    }
}
SCENARIO("if stack isn't empty AND isn't full => length must increase")
{
    GIVEN("non-empty stack")
    {
        stack<size_t> st;
        st.push_back(1);
        WHEN("try to push new element")
        {
            st.push_back(2);
            THEN("length must be equal to 2")
            {
                REQUIRE(st.length() == 2);
            }
        }
    }
}
SCENARIO("if stack is full => element should be pushed anyway")
{
    GIVEN("full stack")
    {
        stack<size_t> st;
        st.push_back(1);
        st.push_back(2);
        st.push_back(3);
        st.push_back(4);
        st.push_back(5);
        WHEN("try to push new element")
        {
            st.push_back(6);
            THEN("length must be equal to 6")
            {
                REQUIRE(st.length() == 6);
            }
        }
    }
}