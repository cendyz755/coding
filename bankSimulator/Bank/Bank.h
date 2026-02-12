#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

class Bank {
private:
  string databaseFilePath{"database.txt"};
  string welcomeMessage{"Welcome to the bank!"};
  string selectingMessage{"What do you want do now: "};
  string wrongOptionMessage{"Wrong option. "};
  string tryAgainMessage{"Try again: "};
  string specialSymbols{"!@#$%^&*(\\)/';:"};
  string id;
  int passwordMinimumLength{5};
  int passwordMaximumLength{16};
  char accountInfoSeparator{';'};
  int correctNumberOfSeparators{5};
  vector<string> startOptions{"Login", "Register", "Exit"};
  string tempUserOption{};
  int toZeroUnix{48};
  int userOption{};
  bool isUserOptionOk{false};
  int login{};
  string password;
  string email;
  double balance{};

public:
  Bank();
  void registerAccount();
  void loginToBank();
  void forgotPassword();
  void checkBalance();
  void depositMoney();
  void withdrawMoney();
  void userChosingOption();
  bool validateUserOption();
  void executeSelectedOption();
  void checkingAccountsDatabase();
  bool checkingSingleAccountDetails(string accountInfo);
  bool checkingAccountId(string id);
};