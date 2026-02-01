#include "machine/Machine.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {


  ifstream file("/home/cendyz/Desktop/dokument.txt");

  string line;

  int words{};

  string word;

  while (file >> word) {
    ++words;
  }
  cout << words << '\n';

  return 0;
}