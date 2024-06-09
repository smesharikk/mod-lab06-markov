// Copyright 2023 UNN-IASR

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <deque>
#include <string>
#include <ctime>

class MarkovGenerator {
public:
	typedef std::deque<std::string> prefix;
	std::map<prefix, std::vector<std::string>> statetab;
	std::deque<std::string> start;
	std::deque<std::string> next;
	int NPREF;
	int MAXGEN;
	int countWords = 0;

	MarkovGenerator(int kolvo, int size);
	void readFromFile(std::string path);
	void generateNewText();
};
