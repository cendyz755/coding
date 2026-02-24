//
// Created by cendyz775 on 2026/02/23.
//

#include "Account.h"
#include <iostream>

using std::cout;
using std::cin;

Account::Account() = default;

Account::~Account() = default;

void Account::showAccInfo() const {
    cout << "Your account details" << '\n';
    cout << '\t' << "Id: " << this->id << '\n';
    cout << '\t' << "Name: " << this->name << '\n';
    cout << '\t' << "Surname: " << this->surname << '\n';
    cout << '\t' << "Email: " << this->email << '\n';
    cout << '\t' << "Balance: " << this->balance << '\n';
}

void Account::showMenu() {
    cout << "Your account options:" << '\n';
    for (int i{1}; i <= this->loggedMenu.size(); ++i) {
        cout << '\t' << i << ". " << this->loggedMenu[i - 1] << '\n';
    }

    cout << "What you want to do?: ";

    this->selectingLoggedOptions();
}

void Account::selectingLoggedOptions() {
    if (!this->validateSelectedOption()) {
        cout << "Wrong number option." << '\n';
        this->selectingLoggedOptions();
    }
    else {
        this->executeOption();
    }
}

bool Account::validateSelectedOption() {
    getline(cin, this->selectedOption);

    if (this->selectedOption.size() != 1) return false;

    if (this->selectedOption[0] - this->unixZero < 1 ||
        this->selectedOption[0] - this->unixZero > this->loggedMenu.size())
        return false;

    return true;
}

void Account::executeOption() {
    if (this->selectedOption == "1")
        this->withdrawFunc();

    if (this->selectedOption == "2")
        this->depositFunc();

    if (this->selectedOption == "3")
        this->checkBalance();

    if (this->selectedOption == "6")
        return;

    this->showMenu();
}

void Account::withdrawFunc() {
    cout << "How much do you want to withdraw?: ";
    getline(cin, this->money);

    if (!this->validateWithdrawDepositMoney()) {
        this->withdrawFunc();
        return;
    }

    if (stoi(this->money) > this->balance) {
        cout << "You can't withdraw more money than you have." << '\n';
        this->withdrawFunc();
        return;
    }

    balance -= stoi(this->money);
    cout << "Your current balance: " << this->balance << '\n';
}

bool Account::validateWithdrawDepositMoney() {
    const bool isCorrectAmount(std::all_of(money.begin(), this->money.end(),
                                           [](const char& c) { return isdigit(c); }));

    if (!isCorrectAmount) {
        cout << "This is not a number." << '\n';
        return false;
    }

    return true;
}

void Account::depositFunc() {
    cout << "How much do you want to deposit?: ";
    getline(cin, this->money);

    if (!this->validateWithdrawDepositMoney()) {
        this->withdrawFunc();
        return;
    }

    if (stoi(this->money) < 0) {
        cout << "You can't deposit negative or zero money." << '\n';
        this->withdrawFunc();
        return;
    }

    balance += stoi(this->money);
    cout << "Your current balance: " << this->balance << '\n';;
}

void Account::checkBalance() const {
    cout << "Your current balance is: " << this->balance << '\n';
}
