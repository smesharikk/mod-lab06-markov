// Copyright 2024 unn
#include <iostream>
#include <fstream>
#include"textgen.h"
int main() {
    std::string line;
    std::string text = "";
    std::ifstream in("test.txt");
    if (in.is_open()) {
        while (getline(in, line)) {
            text += line + ' ';
        }
    }
    in.close();
    Gen gn = Gen(text, 2, 1000);
    std::string answer = gn.getText();
    std::ofstream out;
    out.open("answer.txt");
    if (out.is_open()) {
        out << answer;
    }
    out.close();
}
