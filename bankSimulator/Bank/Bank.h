#pragma once

#include <random>
#include <string>
#include <vector>
using std::mt19937;
using std::random_device;
using std::string;
using std::vector;

class Bank {
private:
  string databaseFilePath{"database.txt"};
  string welcomeMessage{"Welcome to the bank!"};
  string selectingMessage{"What do you want do now: "};
  string wrongOptionMessage{"Wrong option. "};
  string wrongPassLenMess{"Password length must be between 5 and 20"};
  string tryAgainMessage{"Try again: "};
  string newPassMess{"New password: "};
  string specialSymbols{"!@#$%^&*(\\)/';:"};
  string askingName{"Your name: "};
  string redColor{"\033[91m"};
  string colorReset{"\033[0m"};
  string askingSurname{"And your surname: "};
  string wrongNameSize{"Name size must be between 3 and 15. Try again."};
  string wrongNameMess{"Your name can contains only letters"};
  string wrongPassSymbolsMess{
      "Your password must contatin letters, digits and special symbols."};
  vector<string> passLegalSymbols{
      "0123456789", "!@#$%^&*",
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
  vector<string> symbolsForId{"0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                              "$&#"};
  string id;
  string tempUserName;
  string tempUserSurname;
  random_device rd;
  mt19937 gen{this->rd()};
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
  int minNameSurnameLen{3};
  int maxNameSurnameLen{15};
  int minPassLen{7};
  int maxPassLen{20};
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
  void chooseSymbolForId();
  void generateUserId();
  bool checkingAccountId(string id);
  void isAccountsDatabaseExists();
  void userInsertingNameSurname();
  void checkingUserPassword();
  bool isStrongPassword();
  void userInsertingPassword();
  bool checkingUserFullnameSize();
  bool isUserNameContainsSymbols(string name);
};