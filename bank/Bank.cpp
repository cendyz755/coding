#include "Bank.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using std::cin;
using std::cout;
using std::getline;
using std::ifstream;
using std::ofstream;
namespace fs = std::filesystem;

Bank::Bank() {
    cout << this->welcomeMessage << '\n';
    this->showMenu();

    this->isAccountsDatabaseExists();

    this->selectingStartOption();
}

void Bank::showMenu() const {
    for (int i{1}; i <= this->startOptions.size(); ++i) {
        cout << '\t' << i << ". " << startOptions[i - 1] << '\n';
    }
}

void Bank::isAccountsDatabaseExists() const {
    if (const fs::path databasePath(this->databaseFilePath); !fs::exists(databasePath)) {
        ofstream database(this->databaseFilePath);
    }
}

void Bank::selectingStartOption() {
    while (!this->validateUserOption()) {
        cout << this->redColor << this->wrongOptionMessage << this->colorReset << '\n';
    }

    this->executeSelectedOption();
}

bool Bank::validateUserOption() {
    cout << this->startingOptsMess;
    getline(cin, this->userOption);

    if (!regex_match(this->userOption, this->menuOptRegex)) {
        return false;
    }

    return true;
}

void Bank::executeSelectedOption() {
    if (this->userOption == "2") {
        this->registerAccount();
    }

    this->showMenu();
    this->selectingStartOption();
}

void Bank::registerAccount() {
    this->userInsertingNameSurname();

    this->userInsertingPassword();

    this->generateId();

    this->userInsertingEmail();

    this->addAccountToDatabase();

    this->accountCreated();
}

void Bank::userInsertingNameSurname() {
    while (!this->validateUsername()) {
        cout << this->redColor << this->wrongNameMess << this->colorReset << '\n';
    }
}

bool Bank::validateUsername() {
    cout << this->askingName;
    getline(cin, this->userName);

    cout << this->askingSurname;
    getline(cin, this->userSurname);

    if (!regex_match(this->userName, this->nameRegex) ||
        !regex_match(this->userSurname, this->nameRegex)) {
        return false;
    }

    return true;
}

void Bank::userInsertingPassword() {
    while (!this->validatePassword()) {
        cout << this->redColor << this->wrongNewPassMess <<
                this->colorReset << '\n';
    }
}

bool Bank::validatePassword() {
    cout << this->newPassMess;
    getline(cin, this->password);

    if (!regex_match(this->password, this->passRegex)) {
        return false;
    }

    return true;
}

void Bank::generateId() {
    while (--this->idLen + 1) {
        this->id += std::to_string(this->dist(this->gen));
    }

    if (!this->idAlreadyExists()) {
        this->generateId();
    }
}


bool Bank::idAlreadyExists() const {
    ifstream databasePath{this->databaseFilePath};
    string accountDetails;

    while (getline(databasePath, accountDetails)) {
        if (!this->lookingForTheSameIdInFile(accountDetails)) {
            return false;
        }
    }

    return true;
}

bool Bank::lookingForTheSameIdInFile(const string &accountDetails) const {
    std::stringstream ss(accountDetails);

    string accountId;
    getline(ss, accountId, ';');

    if (accountId == this->id)
        return false;

    return true;
}

void Bank::userInsertingEmail() {
    cout << this->emailMess;
    getline(cin, this->email);
    if (!this->validateEmail()) {
        cout << this->redColor << this->wrongEmailMess << this->colorReset << '\n';
        userInsertingEmail();
    }
}

bool Bank::validateEmail() const {
    return std::regex_match(this->email, this->emailRegex);
}

void Bank::addAccountToDatabase() const {
    ofstream tempDatabaseFile(this->tempDb);
    ifstream databaseFile{this->databaseFilePath};
    string accountDetails;

    while (getline(databaseFile, accountDetails)) {
        tempDatabaseFile << accountDetails << '\n';
    }

    tempDatabaseFile << this->id << ';' << this->userName << ';' << this->userSurname
            << ';' << this->password << ';' << this->email << '\n';

    fs::remove(this->databaseFilePath);
    fs::rename(this->tempDb, this->databaseFilePath);
}

void Bank::accountCreated() const {
    cout << this->blueColor << this->accSuccCreatedMess << this->colorReset << '\n';
    cout << "Your account details: " << '\n';
    cout << "\tId: " << this->id << '\n';
    cout << "\tName: " << this->userName << '\n';
    cout << "\tSurname: " << this->userSurname << '\n';
    cout << "\tEmail: " << this->email << '\n';
}
