#pragma once

#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <iomanip>
using std::regex;
using std::string;
using std::vector;

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

class Account {
public:
    Account();

    Account(string id, string email, string name, string surname, string pass,
            const double bal) : id(std::move(id)), email(std::move(email)), name(std::move(name)),
                                surname(std::move(surname)), password(std::move(pass)),
                                balance(bal) {
    };
    ~Account();

    string id;
    string email;
    string name;
    string surname;
    string password;
    double balance{};;

    void showAccInfo() const;

    vector<string> loggedMenu{
        "Withdraw", "Deposit", "Check balance",
        "Change e-mail", "Change password", "Logout and save all changes"
    };
    void showMenu();

private:
    string redColor{"\033[91m"};
    string blueColor{"\033[94m"};
    string colorReset{"\033[0m"};

    string newAccInfoMess{"Your account details:"};
    vector<string> newAccDetailsMess{"Id", "Name", "Surname", "E-mail", "Balance"};
    vector<string> newAccVars{this->id, this->name, this->surname, this->email};

    string wrongOptMess{"Wrong number option."};
    string accOptsMess{"Your account options:"};
    string whatToDoMess{"What you want to do?: "};
    int unixZero{48};
    string selectedOption;
    void selectingLoggedOptions();
    bool validateSelectedOption();

    void executeOption();

    string wrongNumMoneyMess{"This is not correct value."};
    string currBalanceMess{"Your current balance"};
    string errWithdrawMess{"You can't withdraw more money than you have."};
    string howMuchWithdrawMess{"How much do you want to withdraw?: "};
    string depositMess{"How much do you want to deposit?: "};
    string wrongDepositMess{"You can't deposit negative or zero money."};
    regex isThisDouble{R"(^[+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?$)"};
    string money;
    void withdrawFunc();
    void depositFunc();
    [[nodiscard]] bool validateWithdrawDepositMoney() const;

    void checkBalance() const;
    regex emailRegex{
        R"(^[A-Za-z0-9._%+\-]+@[A-Za-z0-9\-]+(?:\.[A-Za-z0-9\-]+)*\.[A-Za-z]{2,}$)"
    };
    string databaseFilePath{"database.csv"};
    void changeEmail();
    [[nodiscard]] bool emailAlreadyExists() const;
    [[nodiscard]] bool itsCorrectEmail() const;

    regex passRegex{R"(^[a-zA-Z0-9!@#$%^&*]{7,16}$)"};
    void changePass();
    bool isAstrongPass();
};

#endif //BANK_ACCOUNT_H
