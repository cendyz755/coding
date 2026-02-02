#include "IdValidator.h"
#include <iostream>
#include <string>
using namespace std;

bool IdValidator::idSizeChecking() {
  string userInput;

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

bool IdValidator::checkingYear() {
  string userIdCopy{IdValidator::user_id.substr(0, 2)};
  int year{};

  if (userIdCopy[0] - 0 == 0) {
    year = userIdCopy[1] - 0;
  } else {
    year = stoi(userIdCopy);
  }

  if (year > 92 || (year > 72 && year < 81)) {
    return false;
  }

  IdValidator::year = 
  

  return true;
}