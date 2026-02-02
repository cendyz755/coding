#pragma once
#include <string>
using std::string;

class IdValidator {
private:
  string user_id;
  int year{};
  int month{};
  int day{};

public:
  bool idSizeChecking();
  bool is_a_number(int);
  bool checkingYear();
  bool monthChecking();
  bool dayChecking();
};
