// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
#include <iostream>
#include <fstream>

std::string readFile() {
    std::string line;
    std::string text = "";
    std::ifstream in;
    in.open("test.txt");
    if (in.is_open()) {
        while (getline(in, line)) {
            text += line + ' ';
        }
    }
    in.close();
    return text;
}

TEST(test1, prefixNumber) {
    std::string initial = readFile();
    Gen g = Gen(initial, 2, 1000);
    std::string answer = g.getText();
    int count = g.start.size();

    EXPECT_EQ(2, count);
}

TEST(test2, prefixSuffix) {
    std::string initial = readFile();
    Gen g = Gen(initial, 2, 1000);
    std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
    it = g.statetab.find(g.start);
    std::string suff = it->second[0];

    EXPECT_EQ("the", suff);
}

TEST(test3, oneSuffix) {
    std::string initial = readFile();
    Gen g = Gen(initial, 2, 1000);
    std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
    it = g.statetab.find(g.start);
    std::string suff = it->second[rand() % (it->second).size()];

    EXPECT_EQ("Жил", suff);
}

TEST(test4, chooseSuffix) {
    std::string initial = readFile();
    Gen g = Gen(initial, 2, 1000);
    std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
    it = g.statetab.find(g.start);
    std::string suff = it->second[rand() % (it->second).size()];

    EXPECT_TRUE(suff == "старик" || suff == "своею" || suff == "землянке");
}

TEST(test5, lengthText) {
    Gen g = Gen("", 2, 1000);

    std::string str;

    g.words.push_back("I");
    g.words.push_back("love");

    g.words.front();
    g.words.push_back("birds");

    g.words.front();
    g.words.push_back("I");

    g.words.front();
    g.words.push_back("love");

    g.words.front();
    g.words.push_back("letters");

    g.words.front();
    g.words.push_back("I");

    g.words.front();
    g.words.push_back("love");

    g.words.front();
    g.words.push_back("dogs");

    g.words.front();
    g.words.push_back("I");

    g.words.front();
    g.words.push_back("love");

    g.getText();

    int count = g.words.size();

    EXPECT_EQ(33, count);
}
