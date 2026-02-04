#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class IdValidator {
private:
  const vector<int> weights{1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
  string user_id;
  int short_year{};
  int full_year{};
  int month{};
  int day{};
  string gender;
  string continueCheckingID{"y"};
  // string lightBlue{"\033[94m"};
  // string lightRed{"\033[91m"};
  // string colorRest{"\033[0m"};

public:
  IdValidator();
  void userInsertingID();
  bool idSizeChecking();
  bool is_a_number(int);
  void settingYear();
  void settingFullYear(int);
  bool settingCheckingMonth();
  int monthDayLimit();
  string monthName();
  bool checkingDay();
  void maleOrFemale();
  void showPersonInfo();
  bool checkingControlNumber();
  bool continueChecking();
  string lightBlue{"\033[94m"};
  string lightRed{"\033[91m"};
  string colorRest{"\033[0m"};
  ~IdValidator();
};
