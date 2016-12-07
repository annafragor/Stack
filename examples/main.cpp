#include <stack.hpp>

int main()
{
    stack<int> st;
    st.push_back(1);
    st.push_back(2);
    st.push_back(3);
    st.push_back(4);
    st.push_back(5);
    std::cout << st;
    st.push_back(6);
    st.push_back(7);
    std::cout << st;
    std::cout << "\nok" << std::endl;
}