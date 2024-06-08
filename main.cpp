// Copyright 2023 UNN-IASR

#include "textgen.h"

int main() {
  TextGenerator g = TextGenerator(2, 1000);
  g.readFromFile("input.txt");
  g.generateNewText();
}
