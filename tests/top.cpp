//
// Created by anna on 12.12.16.
//

#include <stack.hpp>
#include "catch.hpp"

SCENARIO("if stack is empty => top() throws")
{
    GIVEN("empty stack")
    {
        stack<size_t> st;
        WHEN("try to pop an element")
        {
            THEN("it must throw")
            {
                REQUIRE_THROWS(st.top());
            }
        }
    }
}
SCENARIO("if stack isn't empty => return control value")
{
    GIVEN("non-empty stack")
    {
        stack<size_t> st;
        st.push_back(1);
        st.push_back(2);
        WHEN("try to pop an element")
        {
            THEN("top must be equal to 2")
            {
                REQUIRE(st.top() == 2);
            }
        }
    }
}