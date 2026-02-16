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
#include <sstream>
namespace fs = std::filesystem;

Bank::Bank() {

  cout << this->welcomeMessage << '\n';
  for (int i{1}; i <= this->startOptions.size(); ++i) {
    cout << '\t' << i << ". " << startOptions[i - 1] << '\n';
  }
  this->isAccountsDatabaseExists();
}

void Bank::isAccountsDatabaseExists() {

  fs::path databasePath(this->databaseFilePath);

  if (!fs::exists(databasePath)) {
    ofstream database(this->databaseFilePath);
  }
}

void Bank::userChosingStartingOption() {

  cout << this->startingOptsMess;

  if (!this->validateUserOption()) {
    cout << this->wrongOptionMessage << this->tryAgainMessage;
    this->validateUserOption();
    return;
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

  return true;
}

void Bank::executeSelectedOption() {

  switch (this->userOption) {
  case 2:
    this->registerAccount();
    break;
  };

  this->userOption = 0;
}

void Bank::registerAccount() {

  this->userInsertingNameSurname();

  this->userInsertingPassword();

  this->userInsertingId();
}

void Bank::userInsertingNameSurname() {

  cout << this->askingName;
  getline(cin, this->userName);

  cout << this->askingSurname;
  getline(cin, this->userSurname);

  if (this->userName.size() > this->maxNameSurnameLen ||
      this->userName.size() < this->minNameSurnameLen ||
      this->userSurname.size() > this->maxNameSurnameLen ||
      this->userSurname.size() < this->minNameSurnameLen) {
    cout << this->redColor << this->wrongNameSize << this->colorReset << '\n';
    this->userInsertingNameSurname();
    return;
  }

  if (!this->isUserNameContainsSymbols(this->userName) ||
      !this->isUserNameContainsSymbols(this->userSurname)) {
    cout << this->redColor << this->wrongNameMess << this->colorReset << '\n';
    this->userInsertingNameSurname();
    return;
  }
}

bool Bank::isUserNameContainsSymbols(string name) {

  for (char &c : name) {
    if (!isalpha(c))
      return false;
  }

  return true;
}

void Bank::userInsertingPassword() {

  cout << this->newPassMess;
  getline(cin, this->password);

  if (this->password.size() > this->maxPassLen ||
      this->password.size() < this->minPassLen) {
    cout << this->redColor << this->wrongPassLenMess << this->colorReset
         << '\n';
    this->userInsertingPassword();
    return;
  }

  if (!this->isStrongPassword()) {
    cout << this->redColor << this->wrongPassSymbolsMess << this->colorReset
         << '\n';
    this->userInsertingPassword();
    return;
  }

  this->isStrongPassword();
}

void Bank::isStrongPassword() {

  if (this->password.find_first_of(this->passLegalSymbols[0]) == string::npos ||
      this->password.find_first_of(this->passLegalSymbols[1]) == string::npos ||
      this->password.find_first_of(this->passLegalSymbols[2]) == string::npos) {
    this->userInsertingPassword();
    return;
  }
}

void Bank::userInsertingId() {
  this->checkIdSize();
  this->idAlreadyExists();
}

void Bank::checkIdSize() {

  cout << "Your id: ";
  getline(cin, this->id);

  if (this->id.size() > this->idLen[1] || this->id.size() < this->idLen[0]) {
    cout << this->wrongNewIdMess << '\n';
    this->checkIdSize();
  }
}

bool Bank::idAlreadyExists() {

  ifstream database{this->databaseFilePath};

  string line;

  while (getline(database, line)) {

    std::stringstream ss(line);

    string id;

    getline(ss, id, ';');

    if (id == this->id) {
      cout << "This id already exists. Choose other id." << '\n';
      this->userInsertingId();
      return false;
    }
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