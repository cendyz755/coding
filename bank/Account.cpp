#include "Account.h"
#include <iostream>

using std::cout;
using std::cin;

Account::Account() = default;

Account::~Account() = default;

void Account::showAccInfo() const {
    cout << this->newAccInfoMess << '\n';

    for (int i{}; i < this->newAccVars.size() - 1; ++i) {
        cout << '\t' << this->blueColor << this->newAccDetailsMess[i] << this->colorReset << ": " <<
            this->newAccVars[i] << '\n';
    }

    cout << '\t' << this->blueColor << this->newAccDetailsMess[4] << this->colorReset << ": " <<
        std::fixed << std::setprecision(2) << this->balance << '\n';
}

void Account::showMenu() {
    cout << this->accOptsMess << '\n';
    for (int i{1}; i <= this->loggedMenu.size(); ++i) {
        cout << '\t' << i << ". " << this->loggedMenu[i - 1] << '\n';
    }

    cout << this->whatToDoMess;

    this->selectingLoggedOptions();
}

void Account::selectingLoggedOptions() {
    if (!this->validateSelectedOption()) {
        cout << this->wrongOptMess << '\n';
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
    cout << this->howMuchWithdrawMess;
    getline(cin, this->money);

    if (!this->validateWithdrawDepositMoney()) {
        cout << this->redColor << this->wrongNumMoneyMess << this->colorReset << '\n';
        this->withdrawFunc();
        return;
    }

    const double newMoney{stod(this->money)};

    if (newMoney > this->balance) {
        cout << this->redColor << this->errWithdrawMess << this->colorReset
            << '\n';
        this->withdrawFunc();
        return;
    }

    balance -= newMoney;
    cout << this->blueColor << this->currBalanceMess << this->colorReset << ": " << this->balance
        << '\n';
}

bool Account::validateWithdrawDepositMoney() const {
    return std::regex_match(this->money, this->isThisDouble);
}

void Account::depositFunc() {
    cout << this->depositMess;
    getline(cin, this->money);

    if (!this->validateWithdrawDepositMoney()) {
        cout << this->redColor << this->wrongNumMoneyMess << this->colorReset << '\n';
        this->withdrawFunc();
        return;
    }

    const double newMoney{stod(this->money)};

    if (newMoney < 0) {
        cout << this->wrongDepositMess << '\n';
        this->withdrawFunc();
        return;
    }

    balance += newMoney;
    cout << this->blueColor << this->currBalanceMess << this->colorReset << ": " << this->balance
        << '\n';
}

void Account::checkBalance() const {
    cout << this->currBalanceMess << this->balance << '\n';
}
