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
  string databaseFilePath{"database.csv"};
  string welcomeMessage{"Welcome to the bank!"};
  string startingOptsMess{"What do you want do now: "};
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
  vector<int> idLen{5, 10};
  string id;
  string userName;
  string userSurname;
  string wrongNewIdMess{"Id length mus be between 0 and 10"};
  random_device rd;
  mt19937 gen{this->rd()};
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
  void checkIdSize();
  void userInsertingId();
  bool idAlreadyExists();
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
  void userChosingStartingOption();
  bool validateUserOption();
  void executeSelectedOption();
  bool checkingAccount(string account);
  bool chooseSymbolForId();
  void generateUserId();
  bool checkingAccountId(string id);
  void isAccountsDatabaseExists();
  void userInsertingNameSurname();
  void checkingUserPassword();
  void isStrongPassword();
  void userInsertingPassword();
  bool checkingUserFullnameSize();
  bool isUserNameContainsSymbols(string name);
};