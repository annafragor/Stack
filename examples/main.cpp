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

    stack<int> s1;
    s1.push_back(1);
    s1.push_back(10);
    std::cout << s1;
    stack<int> s2;
    s2.push_back(1);
    s2.push_back(3);
    std::cout << s2;
    if(!(s1 == s2))
        std::cout << "non equal" << std::endl;
    std::cout << "\nok" << std::endl;
}