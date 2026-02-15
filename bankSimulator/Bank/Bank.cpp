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
  return true;
}

void Bank::executeSelectedOption() {
  switch (this->userOption) {
  case 2:
    this->registerAccount();
    break;
  };
}

void Bank::registerAccount() {
  this->userInsertingNameSurname();
  this->userInsertingPassword();
  this->generateUserId();
}

void Bank::userInsertingNameSurname() {
  while (!this->isEverythingFine) {
    this->checkingUserFullnameSize();
  }
  this->isEverythingFine = false;
}

bool Bank::checkingUserFullnameSize() {
  cout << this->askingName;
  getline(cin, this->tempUserName);
  cout << this->askingSurname;
  getline(cin, this->tempUserSurname);

  if (this->tempUserName.size() > this->maxNameSurnameLen ||
      this->tempUserName.size() < this->minNameSurnameLen ||
      this->tempUserSurname.size() > this->maxNameSurnameLen ||
      this->tempUserSurname.size() < this->minNameSurnameLen) {
    cout << this->redColor << this->wrongNameSize << this->colorReset << '\n';
    return false;
  }

  if (!this->isUserNameContainsSymbols(this->tempUserName) ||
      !this->isUserNameContainsSymbols(this->tempUserSurname)) {
    cout << this->redColor << this->wrongNameMess << this->colorReset << '\n';
    return false;
  }

  this->isEverythingFine = true;

  return true;
}

bool Bank::isUserNameContainsSymbols(string name) {
  for (char &c : name) {
    if (!isalpha(c))
      return false;
  }
  return true;
}

void Bank::userInsertingPassword() {
  while (!this->isEverythingFine) {
    this->checkingUserPassword();
  }
}

void Bank::checkingUserPassword() {
  cout << this->newPassMess;
  getline(cin, this->password);
  if (this->password.size() > this->maxPassLen ||
      this->password.size() < this->minPassLen) {
    cout << this->redColor << this->wrongPassLenMess << this->colorReset
         << '\n';
    return;
  }

  if (!this->isStrongPassword()) {
    cout << this->redColor << this->wrongPassSymbolsMess << this->colorReset
         << '\n';
    return;
  }

  this->isEverythingFine = true;
}

bool Bank::isStrongPassword() {
  if (this->password.find_first_of(this->passLegalSymbols[0]) == string::npos ||
      this->password.find_first_of(this->passLegalSymbols[1]) == string::npos ||
      this->password.find_first_of(this->passLegalSymbols[2]) == string::npos)
    return false;
  return true;
}

void Bank::generateUserId() {
  while (this->id.size() < this->minimumIdLen) {
    this->chooseSymbolForId();
  }
}

void Bank::chooseSymbolForId() {
  std::uniform_int_distribution<> whichSymbolsType(
      0, this->symbolsForId.size() - 1);
  string type{this->symbolsForId[whichSymbolsType(this->gen)]};
  std::uniform_int_distribution<> specificSymbol(0, type.size() - 1);
  this->id += type[specificSymbol(this->gen)];
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