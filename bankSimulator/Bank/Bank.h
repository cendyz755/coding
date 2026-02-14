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
  string askingName{"Your name: "};
  string askingSurname{"And your surname: "};
  string wrongNameSize{"Name size must be between 3 and 15. Try again."};
  string wrongName{"Your name can contains only letters"};
  string symbolsForId{"0123456789abcdefghijklmnopqrstuvwxyz"};
  string id;
  string tempUserName;
  string tempUserSurname;
  bool isEverythingFine{false};
  int passwordMinimumLength{5};
  int passwordMaximumLength{16};
  int minimumIdLen{7};
  char accountInfoSeparator{';'};
  int correctNumberOfSeparators{5};
  vector<string> startOptions{"Login", "Register", "Exit"};
  string tempUserOption{};
  int toZeroUnix{48};
  int userOption{};
  bool isUserOptionOk{false};
  int minimumNameSurnameSize{3};
  int maximumNameSurnameSize{15};
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
  bool checkingAccount(string account);
  void generateUserId();
  bool checkingAccountId(string id);
  void isAccountsDatabaseExists();
  void userInsertingNameSurname();
  bool checkingUserFullnameSize();
  bool isUserNameContainsSymbols(string name);
};