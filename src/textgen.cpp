// Copyright 2024 unn
#include "textgen.h"
#include <time.h>
#include <random>

Gen::Gen(std::string array, int val1, int val2) {
    srand(time(NULL));
    NPREF = val1;
    MAXGEN = val2;
    data = array;
    int i = 0, state = 0, count = -1;
    while (array[i] != '\0') {
        if (state == 0 && array[i] != ' ' &&
            array[i] != '\r' && array[i] != '\n') {
            state = 1;
            count++;
            words.push_back("");
            words[count] = words[count] + array[i];
        } else if (state == 1 && (array[i] == ' ' ||
            array[i] == '\r' || array[i] == '\n')) {
            state = 0;
        } else if (state == 1 && array[i] != ' ' &&
            array[i] != '\r' && array[i] != '\n') {
            words[count] = words[count] + array[i];
        }
        i++;
    }
    for (int i = 0; i < words.size() - NPREF + 1; i++) {
        prefix prf;
        for (int j = 0; j < NPREF; j++)
            prf.push_back(words[i + j]);
        if (i + NPREF < words.size()) {
            statetab[prf].push_back(words[i + NPREF]);
        } else {
            statetab[prf].push_back("END_OF_FILE");
        }
    }
}
std::string Gen::getText() {
    prefix str;
    for (int i = 0; i < NPREF; i++) str.push_back(words[i]);
    std::string answer = "";
    int count = 1;
    while (answer.size() < MAXGEN) {
        if (answer.size() == 0) {
            for (int i = 0; i < NPREF; i++)
                answer = answer + str[i] + ' ';
        }
        int val;
        if (statetab[str].size() == 1 && statetab[str][0] == "END_OF_FILE")
            break;
        if (statetab[str].size() == 0) break;
        std::random_device rd;
        std::mt19937 gen(rd());
        val = gen() % statetab[str].size();
        if (statetab[str][statetab[str].size() - 1] == "END_OF_FILE")
            val = gen() % (statetab[str].size() - 1);
        answer = answer + statetab[str][val] + ' ';
        if (count * 100 - answer.size() < 0 ||
            count * 100 - answer.size() > 100) {
            count++;
            answer = answer + '\n';
        }
        std::string tmp = statetab[str][val];
        for (int i = 0; i < NPREF - 1; i++) str[i] = str[i + 1];
        str[NPREF - 1] = tmp;
    }
    return answer;
}
Gen::Gen(std::map<prefix, std::vector<std::string> > value,
    std::vector<std::string> word, int val1, int val2) {
    NPREF = val1;
    MAXGEN = val2;
    statetab = value;
    words = word;
}
