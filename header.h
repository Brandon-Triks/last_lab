//
// Created by user on 24.11.2025.
//

#ifndef LAST_LAB_HEADER_H
#define LAST_LAB_HEADER_H

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <format>
bool is_numb(std::string str);
bool is_operator(const std::string& str);
void edit_string(std::string& vhod, const std::vector <std::string>& op);
std::vector <std::string> pars(const std::string& vhod);
void replace_un_minus(std::vector <std::string>& pars,const std::vector <std::string>& op);
bool is_correct(const std::vector <std::string>& vec);
bool is_func(const std::string& str);
bool pr_comparing(const char& a, const char& b);
#endif //LAST_LAB_HEADER_H