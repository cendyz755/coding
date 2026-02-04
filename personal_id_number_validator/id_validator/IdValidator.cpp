#include "IdValidator.h"
#include <iostream>
#include <string>
using namespace std;

IdValidator::IdValidator() = default;

void IdValidator::userInsertingID() {
  string user_id;

  while (true) {
    getline(cin, user_id);

    if (user_id.find(' ') != string::npos) {
      cout << lightRed << "Do not use spaces. Try again: " << colorRest;
    } else {
      this->user_id = user_id;
      break;
    }
  }
}

bool IdValidator::idSizeChecking() {
  string userInput{this->user_id};

  if (userInput.size() == 11) {
    return true;
  }

  std::cout << lightRed
            << "Your id length is not correct. Try again: " << colorRest;
  return false;
};

bool IdValidator::is_a_number(int min_index) {
  string userIdCopy{this->user_id.substr(min_index, 2)};

  if (userIdCopy[0] - 0 > 57 || userIdCopy[1] - 0 > 57 ||
      userIdCopy[1] - 0 < 48 || userIdCopy[0] < 48) {
    return false;
  }

  return true;
};

void IdValidator::settingYear() {
  string userIdCopy{this->user_id.substr(0, 2)};
  int year{};

  if (userIdCopy[0] - 48 == 0) {
    year = userIdCopy[1] - 48;
  } else {
    year = stoi(userIdCopy);
  }
  this->short_year = year;
}

bool IdValidator::settingCheckingMonth() {
  string userIdCopy{this->user_id.substr(2, 2)};
  int month{};

  if (userIdCopy[0] - 48 == 0) {
    this->month = userIdCopy[1] - 48;
    this->settingYear();
    this->settingFullYear(0);
    return true;
  }

  month = stoi(userIdCopy);

  int month_code{month % 20};

  if (month_code > 12) {
    return false;
  }

  this->month = month_code;
  this->settingYear();
  this->settingFullYear(userIdCopy[0] - 48);

  return true;
}

void IdValidator::settingFullYear(int year_code) {
  int full_year{};

  switch (year_code) {
  case 0:
  case 1:
    full_year = 1900;
    break;
  case 2:
  case 3:
    full_year = 2000;
    break;
  case 4:
  case 5:
    full_year = 2100;
    break;
  case 6:
  case 7:
    full_year = 2200;
    break;
  case 8:
  case 9:
    full_year = 1800;
  }

  this->full_year = full_year + this->short_year;
}

int IdValidator::monthDayLimit() {
  int user_month{this->month};

  switch (user_month) {
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  }

  if (user_month == 2) {
    if ((this->full_year % 4 == 0 && this->full_year % 100 != 0) ||
        this->full_year % 400 == 0) {
      return 29;
    } else {
      return 28;
    }
  }

  return 31;
}

bool IdValidator::checkingDay() {
  string userIdCopy{this->user_id.substr(4, 2)};

  if (userIdCopy[0] - 47 > 3) {
    return false;
  }

  if (userIdCopy[0] - 48 == 3 && userIdCopy[1] - 48 > 1) {
    return false;
  }

  int days{stoi(userIdCopy)};

  if (days > this->monthDayLimit()) {
    return false;
  } else {
    this->day = days;
  }

  return true;
}

inline string IdValidator::monthName() {

  switch (this->month) {
  case 2:
    return "February";
  case 3:
    return "March";
  case 4:
    return "April";
  case 5:
    return "May";
  case 6:
    return "June";
  case 7:
    return "July";
  case 8:
    return "August";
  case 9:
    return "September";
  case 10:
    return "October";
  case 11:
    return "November";
  case 12:
    return "December";
  }

  return "January";
}

void IdValidator::maleOrFemale() {
  int userIdCopy{stoi(this->user_id.substr(9, 1))};

  if (userIdCopy % 2 == 0) {
    this->gender = "Female";
  } else {
    this->gender = "Male";
  }
}

bool IdValidator::checkingControlNumber() {
  int num{};
  string userIdCopy{this->user_id.substr(10, 1)};

  for (int i{}; i < this->weights.size(); ++i) {
    num += this->weights[i] * (this->user_id[i] - 48);
  }

  num %= 10;

  if (10 - num == stoi(userIdCopy) || num == 0) {
    return true;
  }

  return false;
}

void IdValidator::showPersonInfo() {
  cout << "You were born in:" << '\n';
  cout << lightBlue << "Year" << colorRest << ": " << this->full_year << '\n';
  cout << lightBlue << "Month" << colorRest << ": " << this->monthName()
       << '\n';
  cout << lightBlue << "Day" << colorRest << ": " << this->day << '\n';
  cout << lightBlue << "Gender" << colorRest << ": " << this->gender << '\n';
}

bool IdValidator::continueChecking() {
  string user_decision;

  while (true) {
    getline(cin, user_decision);

    if (user_decision.size() != 1) {
      cout << lightRed << "Wrong command. Try again: " << colorRest;
      continue;
    }

    if (user_decision == "y" || user_decision == "Y") {
      return true;
    } else if (user_decision == "n" || user_decision == "N") {
      break;
    } else {
      cout << lightRed << "Wrong key. Try again: " << colorRest;
    }
  }

  return false;
}

IdValidator::~IdValidator() = default;