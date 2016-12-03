//
// Created by anna on 03.12.16.
//

#include <stack.h>
#include "catch.h"

SCENARIO("if stack is empty => throw an exception")
{
    GIVEN("empty stack")
    {
        stack<size_t> st;
        WHEN("try to pop an element")
        {
            THEN("throw an exception")
            {
                REQUIRE_THROWS(st.pop());
            }
        }
    }
}
SCENARIO("if stack is empty => length must stay constant")
{
    GIVEN("empty stack")
    {
        stack<size_t> st;
        WHEN("try to pop an element")
        {
            THEN("length must be 0")
            {
                REQUIRE(st.length() == 0);
            }
        }
    }
}
SCENARIO("if stack isn't empty => pop an element")
{
    GIVEN("non-empty stack")
    {
        stack<int> st;
        st.push_back(1);
        st.push_back(2);
        st.push_back(3);
        st.push_back(4);
        st.push_back(5);

        stack<int> control_st;
        control_st.push_back(1);
        control_st.push_back(2);
        control_st.push_back(3);
        control_st.push_back(4);
        WHEN("try to pop an element")
        {
            st.pop();
            THEN("st must be equal to control stack")
            {
                REQUIRE(st == control_st);
            }
        }
    }
}
SCENARIO("if stack isn't empty => length must diminish")
{
    GIVEN("non-empty stack")
    {
        stack<int> st;
        st.push_back(1);
        st.push_back(2);
        st.push_back(3);
        st.push_back(4);
        st.push_back(5);
        WHEN("try to pop an element")
        {
            st.pop();
            THEN("length must be equal to 4")
            {
                REQUIRE(st.length() == 4);
            }
        }
    }
}