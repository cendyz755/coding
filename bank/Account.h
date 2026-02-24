#pragma once

#include <string>
#include <utility>
#include <vector>
using std::string;
using std::vector;

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

class Account {
public:
    Account();

    Account(string id, string name, string surname, string email,
            const int bal) : id(std::move(id)), name(std::move(name)),
                             surname(std::move(surname)),
                             email(std::move(email)), balance(bal) {
    };
    ~Account();

    string id;
    string name;
    string surname;
    string email;
    string password;
    double balance{};;

    void showAccInfo() const;

    vector<string> loggedMenu{
        "Withdraw", "Deposit", "Check balance",
        "Change e-mail", "Change password", "Logout and save all changes"
    };
    void showMenu();

private:
    int unixZero{48};
    string selectedOption;
    void selectingLoggedOptions();
    bool validateSelectedOption();

    void executeOption();

    string money;
    void withdrawFunc();
    void depositFunc();
    bool validateWithdrawDepositMoney();

    void checkBalance() const;
};

#endif //BANK_ACCOUNT_H
