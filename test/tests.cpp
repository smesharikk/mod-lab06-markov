// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

std::string readFile()
{
    std::string line;
    std::string text = "";
    std::ifstream in("test.txt");
    if (in.is_open()) {
        while (getline(in, line)) {
            text += line + ' ';
        }
    }
    in.close();
    return text;
}

TEST(test1, prefixNumber)
{
    std::string initial = readFile();
    Gen g = Gen(initial, 2, 1000);
    std::string answer = g.getText();
    int count = g.start.size();

    EXPECT_EQ(2, count);
}

TEST(test2, prefixSuffix)
{
    std::string initial = readFile();
    Gen g = Gen(initial, 2, 1000);
    std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
    it = g.statetab.find(g.start);
    std::string suff = it->second[0];

    EXPECT_EQ("the", suff);
}

TEST(test3, oneSuffix)
{
    std::string initial = readFile();
    Gen g = Gen(initial, 2, 1000);
    std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
    it = g.statetab.find(g.start);
    std::string suff = it->second[rand() % (it->second).size()];

    EXPECT_EQ("Жил", suff);
}

TEST(test4, chooseSuffix)
{
    std::string initial = readFile();
    Gen g = Gen(initial, 2, 1000);
    std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
    it = g.statetab.find(g.start);
    std::string suff = it->second[rand() % (it->second).size()];

    EXPECT_TRUE(suff == "старик" || suff == "своею" || suff == "землянке");
}

TEST(test5, lengthText)
{
    std::string initial = "";
    Gen g = Gen(initial, 2, 1000);

    std::string str;

    g.prefix.push_back("I");
    g.prefix.push_back("love");

    g.statetab[g.prefix].push_back("flowers");
    g.prefix.pop_front();
    g.prefix.push_back("flowers");

    g.statetab[g.prefix].push_back("I");
    g.prefix.pop_front();
    g.prefix.push_back("I");

    g.statetab[g.prefix].push_back("love");
    g.prefix.pop_front();
    g.prefix.push_back("love");

    g.statetab[g.prefix].push_back("books");
    g.prefix.pop_front();
    g.prefix.push_back("books");

    g.statetab[g.prefix].push_back("I");
    g.prefix.pop_front();
    g.prefix.push_back("I");

    g.statetab[g.prefix].push_back("love");
    g.prefix.pop_front();
    g.prefix.push_back("love");

    g.statetab[g.prefix].push_back("cats");
    g.prefix.pop_front();
    g.prefix.push_back("cats");

    g.statetab[g.prefix].push_back("I");
    g.prefix.pop_front();
    g.prefix.push_back("I");

    g.statetab[g.prefix].push_back("love");
    g.prefix.pop_front();
    g.prefix.push_back("love");

    g.getText();

    int count = g.words.size();

    EXPECT_EQ(33, count);
}
