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
using std::stringstream;
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
    else if (this->userOption == "1") {
        this->login();
        return;
    }

    this->showMenu();
    this->selectingStartOption();
}

void Bank::login() {
    this->loginInId();
}

void Bank::loginInId() {
    cout << "Your id: ";
    getline(cin, this->id);

    cout << "Your password: ";
    getline(cin, this->password);

    if (!this->idAndPassInDatabase()) {
        cout << this->redColor << "Wrong login or password." << this->colorReset << '\n';
        this->loginInId();
    }
    else {
        cout << this->blueColor << "Login successfully!" << this->colorReset << '\n';
    }
}

bool Bank::idAndPassInDatabase() const {
    ifstream databaseFile{this->databaseFilePath};
    string accDetails;
    vector<string> idPass(5, "");

    while (getline(databaseFile, accDetails)) {
        stringstream ss(accDetails);
        string cell;

        int i{};
        while (getline(ss, cell, ';') && i < 5) {
            idPass[i] = cell;
            ++i;
        }

        if (idPass[0] == this->id && this->password == idPass[4]) {
            return true;
        }
    }

    return false;
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
    int idLen{8};

    while (--idLen + 1) {
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

bool Bank::lookingForTheSameIdInFile(const string& accountDetails) const {
    stringstream ss(accountDetails);
    string accId;

    int i{};
    while (getline(ss, accId, ';') && i < 1) {
        if (accId == this->id) {
            return false;
        }
        ++i;
    }

    return true;
}

void Bank::userInsertingEmail() {
    cout << this->emailMess;
    getline(cin, this->email);
    if (!this->validateEmail()) {
        userInsertingEmail();
    }
}

bool Bank::validateEmail() const {
    if (!regex_match(this->email, this->emailRegex)) {
        cout << this->redColor << this->wrongEmailMess << this->colorReset << '\n';
        return false;
    }

    if (!this->emailAlreadyExists()) {
        cout << this->redColor << this->sameEmailMess << '\n' << this->colorReset;
        return false;
    }

    return true;
}

bool Bank::emailAlreadyExists() const {
    ifstream databaseFile{this->databaseFilePath};
    string accInfo;

    while (getline(databaseFile, accInfo)) {
        stringstream ss(accInfo);
        string accEmail;

        int i{};
        while (getline(ss, accEmail, ';') && i < 2) {
            if (accEmail == this->email)
                return false;
            ++i;
        }
    }

    return true;
}

void Bank::addAccountToDatabase() const {
    ofstream tempDatabaseFile(this->tempDb);
    ifstream databaseFile{this->databaseFilePath};
    string accountDetails;

    while (getline(databaseFile, accountDetails)) {
        tempDatabaseFile << accountDetails << '\n';
    }

    tempDatabaseFile << this->id << ';' << this->email << ';' << this->userName
        << ';' << this->userSurname << ';' << this->password << '\n';

    fs::remove(this->databaseFilePath);
    fs::rename(this->tempDb, this->databaseFilePath);
}

void Bank::resetClassInfo() {
    this->id = "";
    this->userName = "";
    this->userSurname = "";
    this->password = "";
    this->email = "";
}

void Bank::accountCreated() {
    cout << this->blueColor << this->accSuccCreatedMess << this->colorReset << '\n';
    cout << "Your account details: " << '\n';
    cout << "\tId and your login: " << this->id << '\n';
    cout << "\tName: " << this->userName << '\n';
    cout << "\tSurname: " << this->userSurname << '\n';
    cout << "\tEmail: " << this->email << '\n';

    this->resetClassInfo();
}
