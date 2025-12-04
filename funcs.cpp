#include <ranges>

#include "header.h"
void edit_string(std::string& vhod, const std::vector <std::string>& op) {  //работа с пробелами
    vhod += ' ';
    std::string tmp;
    bool flag = 0;
    for (auto n: vhod) {
        bool all = std::all_of(op.begin(),op.end(),[n] (std::string c){return c[0]!=n;});
        for (auto m: op) {
            if (all && flag == 0) {
                tmp+=n;
                flag = 1;
            }
            if (n==m[0]){
                tmp+=' ';
                tmp+=m;
                tmp+=' ';
            }
        }
        flag = 0;
    }
    std::replace(tmp.begin(),tmp.end(),',','.');
    vhod = tmp;
}
std::vector <std::string> pars(const std::string& vhod) {   //парсинг
    std::vector <std::string> v;
    std::string buf;
    for (int i = 0; i < vhod.size();i++) {
        if (vhod[i] != ' ') {
            buf += vhod[i];
        }
        else if (!buf.empty()){
            v.push_back(buf);
            buf.clear();
        }
    }
    return v;
}

void replace_un_minus(std::vector <std::string>& pars,const std::vector <std::string>& op) { //замена унарного минуса на функцию neg
    bool flag = 0;
    if (pars[0]=="-") {
        pars[0] = "neg";
    }
    for (int i=1; i < pars.size()-1; i++) {
        if (pars[i] == "-") {
            if (is_operator(pars[i-1]) || pars[i-1]=="(")  {
                pars[i] = "neg";
            }
        }
    }
}
bool is_numb(std::string str) {     //является ли строка целым или вещественным числом
    if (str=="π"){return 1;}
    if (str.front() == '.') {
        return 0;
    }
    if (str.back() == '.') {
        return 0;
    }
    int count = 0;
    int k = std::count(str.begin(),str.end(),'.');
    if (k>1){return 0;}
    for (auto n:str) {
        if (std::__format::__is_digit(n)) {
                count++;
            }
        }
    return count==(str.length()-k);
}

bool is_func(const std::string& str){   //является ли функцией
    if (!is_numb(str) && str.length()>1 && str.length()<=3) {
        return 1;
    }
    else {return 0;}
}

bool pr_comparing(const char& a, const char& b){    //сравнение приоритетов
    std::vector<std::pair<char,char>> vec = {{'(','0'},{'^','1'},{'*','2'},{'/','2'},
        {'+','3'},{'-','3'}};
    std::pair<char,char> num_a,num_b;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].first == a) {
                num_a = vec[i];
        }
        if (vec[i].first == b) {
                num_b = vec[i];
        }
    }
    if (num_a.second <= num_b.second) {
        return 1;
    }
    return 0;
}
bool is_operator(const std::string& str) {  //является ли оператором (за исключением скобок)
    std::vector <std::string> op1 = {"+","-","*","/","^"};
    bool any = std::any_of(op1.begin(),op1.end(),[str](std::string c){return str==c;});
    if (any) {
        return 1;
    }
    return 0;
}
bool is_correct(const std::vector <std::string>& vec) { //проверка введённого выражения на корректность
    if (is_func(vec.back()) || is_operator(vec.back()) || vec.back()=="("
        || vec.front() == ")" || is_operator(vec.front()) ||
        (std::count(vec.begin(),vec.end(),"(")!=std::count(vec.begin(),vec.end(),")"))) {
        return 0;
    }
    bool all = std::all_of(vec.begin(),vec.end(),[](std::string c) {
        return is_operator(c)||is_numb(c)||is_func(c)||c=="x"||c=="("||c==")";
    });
    if (!all) {
        return 0;
    }
    for (int i = 0; i < vec.size()-1;i++) {
        if (vec[i]=="neg" && vec[i+1]=="-"){return 0;}
        if (vec[i]=="neg" && vec[i+1]==")"){return 0;}
        if (vec[i]==")" && vec[i+1]=="("){return 0;}
        if (is_operator(vec[i]) && vec[i+1]==")"){return 0;}
        if (is_func(vec[i]) && vec[i]!="neg" && vec[i+1]!="("){return 0;}
        if (is_operator(vec[i]) && is_operator(vec[i+1])){return 0;}
    }
    for (int i = 0; i < vec.size()-2;i++) {
        if (is_func(vec[i]) && vec[i]!="neg" && vec[i+2]==")"){return 0;}
    }
    return 1;
}

