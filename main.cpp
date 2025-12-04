#include "header.h"

int main() {
    std::vector <std::string> op = {"+","-","*","/","^","(",")"};
    std::string vhod,vihod;
    std::cout << "Введите выражение:";
    std::getline(std::cin,vhod);
    edit_string(vhod,op);
    std::vector<std::string> vec = pars(vhod);
    replace_un_minus(vec,op);
    bool check = is_correct(vec);
    if (!check) {
        std::cout << "ОШИБКА!" << '\n';
        return 1;
    }
    std::stack<std::string> st;
    for (auto m: vec) {
        if (is_numb(m) || m=="x") {
            vihod+=m;
            vihod+=' ';
        }
        else if (m=="(") {
            st.push(m);
        }
        else if (is_func(m)) {
            st.push(m);
        }
        else if (m==")" && !st.empty()) {
            while (st.top()!="(") {
                vihod+=st.top();
                vihod+=' ';
                st.pop();
            }
            st.pop();
        }
        else if (is_operator(m)) {

            if (!st.empty() && is_func(st.top())) {
                vihod+=st.top();
                vihod+=' ';
                st.pop();
            }
            if (!st.empty() && pr_comparing(st.top()[0],m[0])) {
                if (st.top()!="("){
                    vihod+=st.top();
                    vihod+=' ';
                    st.pop();
                }
            }
            st.push(m);
        }
    }
    while (!st.empty()) {
        vihod+=st.top();
        vihod+=' ';
        st.pop();
    }
    std::cout << '\n' << vihod;
}