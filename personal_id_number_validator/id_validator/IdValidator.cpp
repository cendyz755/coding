#include "IdValidator.h"
#include <iostream>
#include <string>
using namespace std;

IdValidator::IdValidator() {};

void IdValidator::userInsertingID() {
  string user_id;

  while (true) {
    getline(cin, user_id);

    if (user_id.find(' ') != string::npos) {
      cout << "Do not use spaces. Try again: ";
    } else {
      IdValidator::user_id = user_id;
      break;
    }
  }
}

void IdValidator::showUserID() { cout << IdValidator::user_id << '\n'; };

bool IdValidator::idSizeChecking() {
  string userInput{IdValidator::user_id};

  if (userInput.size() == 11) {
    return true;
  }

  std::cout << "Your id length is not correct. Try again: ";
  return false;
};

bool IdValidator::is_a_number(int min_index) {
  string userIdCopy{IdValidator::user_id.substr(min_index, 2)};

  if (userIdCopy[0] - 0 > 9 || userIdCopy[1] - 0 > 9) {
    return false;
  }

  return true;
};

void IdValidator::settingYear() {
  string userIdCopy{IdValidator::user_id.substr(0, 2)};
  int year{};

  if (userIdCopy[0] - 0 == 0) {
    year = userIdCopy[1] - 0;
  } else {
    year = stoi(userIdCopy);
  }

  IdValidator::year = year;
}

bool IdValidator::settingMonth() {
  string userIdCopy{IdValidator::user_id.substr(2, 2)};
  int month{};

  if (userIdCopy[0] - 0 == 0) {
    month = userIdCopy[1] - 0;
    return true;
  } else if (userIdCopy[0] - 0 == 1 && userIdCopy[1] - 0 > 2) {
    return false;
  }

  month = stoi(userIdCopy);

  int month_code{month % 20};

  if (month_code > 11) {
    return false;
  }

  IdValidator::month = month;

  return true;
}

// bool IdValidator::settingDay() {
//   string userIdCopy{IdValidator::user_id.substr(4, 2)};

//   if (userIdCopy[0] - 0 > 3) {
//     return false;
//   } else if (userIdCopy[0] - 0 == 3)
// }