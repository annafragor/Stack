//
// Created by anna on 03.12.16.
//

#include <stack.hpp>
#include "catch.hpp"

SCENARIO("if stack is empty => return 0")
{
    GIVEN("empty stack")
    {
        stack<size_t> st;
        WHEN("ask about length")
        {
            THEN("return 0")
            {
                REQUIRE(st.length() == 0);
            }
        }
    }
}
SCENARIO("if stack isn't empty => return right value")
{
    GIVEN("non-empty stack")
    {
        stack<size_t> st;
        st.push_back(1);
        st.push_back(2);
        WHEN("ask about length")
        {
            THEN("return 2")
            {
                REQUIRE(st.length() == 2);
            }
        }
    }
}

