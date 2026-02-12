#include "Bank.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
using std::cin;
using std::cout;
using std::getline;
using std::ifstream;
using std::ofstream;
namespace fs = std::filesystem;

Bank::Bank() {
  cout << this->welcomeMessage << '\n';
  for (int i{1}; i <= this->startOptions.size(); ++i) {
    cout << '\t' << i << ". " << startOptions[i - 1] << '\n';
  }
  this->checkingAccountsDatabase();
}

void Bank::userChosingOption() {
  cout << this->selectingMessage;
  while (!this->isUserOptionOk) {
    if (!this->validateUserOption())
      cout << this->wrongOptionMessage << this->tryAgainMessage;
  }
}

bool Bank::validateUserOption() {
  getline(cin, this->tempUserOption);
  if (tempUserOption.size() != 1) {
    return false;
  }
  this->userOption = this->tempUserOption[0] - this->toZeroUnix;
  if (this->userOption < 1 || this->userOption > this->startOptions.size())
    return false;
  this->isUserOptionOk = true;
  return true;
}

void Bank::executeSelectedOption() {
  switch (this->userOption) {
  case 2:
    this->registerAccount();
    break;
  };
}

void Bank::registerAccount() {}

void Bank::checkingAccountsDatabase() {
  fs::path databasePath(this->databaseFilePath);
  if (!fs::exists(databasePath)) {
    ofstream database(this->databaseFilePath);
  }
  ifstream database(this->databaseFilePath);
  string singleAccountDetails;
  while (getline(database, singleAccountDetails)) {
    if (!this->checkingSingleAccountDetails(singleAccountDetails))
      break;
  }
}

bool Bank::checkingSingleAccountDetails(string accountDetails) {
  if (std::count(accountDetails.begin(), accountDetails.end(),
                 this->accountInfoSeparator) !=
          this->correctNumberOfSeparators ||
      this->checkingAccountId(accountDetails))
    return false;
  return true;
}

bool Bank::checkingAccountId(string id) {
  if (id.size() < this->passwordMinimumLength ||
      id.size() > this->passwordMaximumLength ||
      id.find_first_of(this->specialSymbols) != string::npos)
    return false;
  return true;
}