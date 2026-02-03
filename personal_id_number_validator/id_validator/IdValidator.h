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
  IdValidator();
  void userInsertingID();
  void showUserID();
  bool idSizeChecking();
  bool is_a_number(int);
  void settingYear();
  bool settingMonth();
  int monthDayLimit(int);
  bool settingDay();
};
