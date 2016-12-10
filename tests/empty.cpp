//
// Created by anna on 11.12.16.
//

#include <stack.hpp>
#include "catch.hpp"

SCENARIO("if stack is empty => return true")
{
    GIVEN("empty stack")
    {
        stack<size_t> st;
        WHEN("try empty() function")
        {
            THEN("return true")
            {
                REQUIRE(st.empty());
            }
        }
    }
}
SCENARIO("if stack isn't empty => return false")
{
    GIVEN("non-empty stack")
    {
        stack<size_t> st;
        st.push_back(1);
        st.push_back(2);
        WHEN("try empty() function")
        {
            THEN("return false")
            {
                REQUIRE_FALSE(st.empty());
            }
        }
    }
}