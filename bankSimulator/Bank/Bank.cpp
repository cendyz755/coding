#include "Bank.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
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
  this->isAccountsDatabaseExists();
  this->checkingAccountsDatabase();
}

void Bank::isAccountsDatabaseExists() {
  fs::path databasePath(this->databaseFilePath);
  if (!fs::exists(databasePath)) {
    ofstream database(this->databaseFilePath);
  }
}

void Bank::checkingAccountsDatabase() {
  ifstream database(this->databaseFilePath);
  string account;
  while (getline(database, account)) {
    if (!this->checkingAccount(account))
      break;
  }
}

void Bank::userChosingOption() {
  cout << this->selectingMessage;
  while (!this->isUserOptionOk) {
    if (!this->validateUserOption())
      cout << this->wrongOptionMessage << this->tryAgainMessage;
  }
  this->executeSelectedOption();
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
  cout << "to jest opcja: " << this->userOption << '\n';
  return true;
}

void Bank::executeSelectedOption() {
  switch (this->userOption) {
  case 2:
    this->registerAccount();
    break;
  };
}

void Bank::registerAccount() { Bank::userInsertingNameSurname(); }

void Bank::userInsertingNameSurname() {
  while (!this->isEverythingFine) {
    this->checkingUserFullnameSize();
  }
  this->isEverythingFine = false;
  this->generateUserId();
}

bool Bank::checkingUserFullnameSize() {
  cout << this->askingName;
  getline(cin, this->tempUserName);
  cout << this->askingSurname;
  getline(cin, this->tempUserSurname);

  if (this->tempUserName.size() > this->maximumNameSurnameSize ||
      this->tempUserName.size() < this->minimumNameSurnameSize ||
      this->tempUserSurname.size() > this->maximumNameSurnameSize ||
      this->tempUserSurname.size() < this->minimumNameSurnameSize) {
    cout << this->wrongNameSize << '\n';
    return false;
  }

  if (!this->isUserNameContainsSymbols(this->tempUserName) ||
      !this->isUserNameContainsSymbols(this->tempUserSurname)) {
    cout << this->wrongName << '\n';
    return false;
  }

  this->isEverythingFine = true;

  return true;
}

void Bank::generateUserId() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, this->symbolsForId.size() - 1);

  while (this->id.size() < this->minimumIdLen) {
    char temp{this->symbolsForId[dist(gen)]};
    this->id += temp;
  }

  cout << "Twoje id: " << this->id << '\n';
}

bool Bank::isUserNameContainsSymbols(string name) {
  for (char &c : name) {
    if (!isalpha(c))
      return false;
  }
  return true;
}

bool Bank::checkingAccount(string accountDetails) {
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