#pragma once
#include <iostream>
using std::cout;


class Machine {

private:
  int words{};
  int lines{};
  int letters{};

public:
  Machine();
  int calculate_words;

//   ~Machine();
};


Machine::Machine() {
    cout << "Hello!" << '\n';
}
