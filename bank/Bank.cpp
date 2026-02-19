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
    for (int i{1}; i <= this->startOptions.size(); ++i) {
        cout << '\t' << i << ". " << startOptions[i - 1] << '\n';
    }
    this->isAccountsDatabaseExists();
    this->selectingStartOption();
}

void Bank::isAccountsDatabaseExists() const {
    if (const fs::path databasePath(this->databaseFilePath); !fs::exists(databasePath)) {
        ofstream database(this->databaseFilePath);
    }
}

void Bank::selectingStartOption() {
    cout << this->startingOptsMess;

    if (!this->validateUserOption()) {
        cout << this->wrongOptionMessage << this->tryAgainMessage;
        this->validateUserOption();
        return;
    }

    this->executeSelectedOption();
}

bool Bank::validateUserOption() {
    getline(cin, this->tempUserOption);

    if (tempUserOption.size() != 1) {
        return false;
    }

    this->userOption = this->tempUserOption[0] - this->toZeroUnix;

    if (this->userOption < 1 || this->userOption > this->startOptions.size())
        return false;

    return true;
}

void Bank::executeSelectedOption() {
    switch (this->userOption) {
        case 2:
            this->registerAccount();
            break;
        default: this->userOption = 0;
    };
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
    cout << this->askingName;
    getline(cin, this->userName);

    cout << this->askingSurname;
    getline(cin, this->userSurname);

    if (this->userName.size() > this->nameLen[1] ||
        this->userName.size() < this->nameLen[0] ||
        this->userSurname.size() > this->nameLen[1] ||
        this->userSurname.size() < this->nameLen[0]) {
        cout << this->redColor << this->wrongNameSize << this->colorReset <<
                '\n';
        this->userInsertingNameSurname();
        return;
    }

    if (!Bank::isUserNameContainsSymbols(this->userName) ||
        !Bank::isUserNameContainsSymbols(this->userSurname)) {
        cout << this->redColor << this->wrongNameMess << this->colorReset <<
                '\n';
        this->userInsertingNameSurname();
        return;
    }
}

bool Bank::isUserNameContainsSymbols(string name) {
    const bool onlyLetters{
        std::all_of(name.begin(), name.end(), [](char c) { return isalpha(c); })
    };

    return onlyLetters;
}

void Bank::userInsertingPassword() {
    cout << this->newPassMess;
    getline(cin, this->password);

    if (this->password.size() > this->passLen[1] ||
        this->password.size() < this->passLen[0]) {
        cout << this->redColor << this->wrongPassLenMess << this->colorReset
                << '\n';
        this->userInsertingPassword();
        return;
    }

    this->isStrongPassword();
}

void Bank::isStrongPassword() {
    if (this->password.find_first_of(this->passLegalSymbols[0]) == string::npos
        ||
        this->password.find_first_of(this->passLegalSymbols[1]) == string::npos
        ||
        this->password.find_first_of(this->passLegalSymbols[2]) == string::npos) {
        cout << this->redColor << this->wrongPassSymbolsMess << this->colorReset
                << '\n';
        this->userInsertingPassword();
    }
}

void Bank::generateId() {
    while (--this->idLen + 1) {
        this->tempId += std::to_string(this->dist(this->gen));
    }

    this->id = stoi(this->tempId);

    this->idAlreadyExists();
}


void Bank::idAlreadyExists() {
    ifstream databasePath{this->databaseFilePath};
    string accountDetails;

    while (getline(databasePath, accountDetails)) {
        if (this->lookingForTheSameIdInFile(accountDetails)) {
            this->generateId();
            return;
        }
    }
}

bool Bank::lookingForTheSameIdInFile(string accountDetails) const {
    std::stringstream ss(accountDetails);

    string accountId;
    getline(ss, accountDetails, ';');

    if (const int numId{stoi(accountId)}; numId == this->id) {
        return false;
    }

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

bool Bank::validateEmail() {
    return std::regex_match(this->email, this->emailRegex);
}

void Bank::addAccountToDatabase() const {
    ofstream tempDatabaseFile(this->tempDb);
    ifstream databaseFile{this->databaseFilePath};
    string accountDetails;

    while (getline(databaseFile, accountDetails)) {
        tempDatabaseFile << accountDetails;
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
