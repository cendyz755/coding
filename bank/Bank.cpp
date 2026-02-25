#include "Bank.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Account.h"
using std::cin;
using std::cout;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::stringstream;
namespace fs = std::filesystem;

Bank::Bank() : Account() {
    this->isAccountsDatabaseExists();

    cout << this->welcomeMessage << '\n';
    this->showMenu();

    this->selectingStartOption();
}

Bank::~Bank() = default;

void Bank::showMenu() const {
    for (int i{1}; i <= this->startOptions.size(); ++i) {
        cout << '\t' << i << ". " << startOptions[i - 1] << '\n';
    }
}

void Bank::isAccountsDatabaseExists() {
    if (const fs::path databasePath(this->databaseFilePath); !fs::exists(databasePath)) {
        ofstream database(this->databaseFilePath);
    }
    else {
        this->loadDataToFile();
    }
}

void Bank::loadDataToFile() {
    ifstream databaseFile{this->databaseFilePath};
    string line;

    while (getline(databaseFile, line)) {
        this->insertDataToVariable(line);
    }
}

void Bank::selectingStartOption() {
    while (!this->validateUserOption()) {
        cout << this->redColor << this->wrongOptionMessage << this->colorReset << '\n';
    }

    this->executeSelectedOption();
}

void Bank::insertDataToVariable(const string& accountData) {
    stringstream ss(accountData);
    string cell;
    const int userId{stoi(accountData.substr(0, 8))};

    while (getline(ss, cell, ';')) {
        this->accountsData[userId].push_back(cell);
    }
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
    if (this->userOption == "1")
        this->login();

    if (this->userOption == "2")
        this->registerAccount();
    if (this->userOption == "3")
        this->recoveringPassword();

    if (this->userOption == "4") {
        this->updateDatabaseFile();
        cout << "Bye." << '\n';
        return;
    }

    this->showMenu();
    this->selectingStartOption();
}

void Bank::login() {
    this->loginInId();
    this->grabAccData();
    this->acc = this->sendInfoToAccClass();
    this->acc.showAccInfo();
    this->acc.showMenu();
    this->updateAccount();
    this->addAccountToDatabase();
    // this->resetClassInfo();
}

void Bank::loginInId() {
    cout << this->idMess;
    getline(cin, this->id);

    cout << this->passMess;
    getline(cin, this->password);

    if (!this->idAndPassInDatabase()) {
        cout << this->redColor << this->wrongLoginPassMess << this->colorReset << '\n';
        this->loginInId();
    }
    else {
        cout << this->blueColor << this->successfulLoginMess << this->colorReset << '\n';
    }
}

bool Bank::idAndPassInDatabase() {
    if (!this->isIdANum())
        return false;

    int const idToNum{stoi(this->id)};

    if (!this->accountsData.contains(idToNum))
        return false;

    if (this->accountsData[idToNum][4] != this->password)
        return false;

    return true;
}

void Bank::grabAccData() {
    this->numId = stoi(this->id);

    this->id = this->accountsData[this->numId][0];
    this->userName = this->userName = this->accountsData[this->numId][1];
    this->userSurname = this->accountsData[this->numId][2];
    this->email = this->accountsData[this->numId][3];
    this->password = this->accountsData[this->numId][4];
    this->balance = this->accountsData[this->numId][5];
}

Account Bank::sendInfoToAccClass() const {
    Account loginAcc{
        this->id, this->userName, this->userSurname,
        this->email, this->password, stoi(this->balance)
    };

    return loginAcc;
}

void Bank::registerAccount() {
    this->userInsertingNameSurname();

    this->userInsertingPassword();

    this->generateId();

    this->userInsertingEmail();

    this->addAccountToDatabase();

    this->addAccountToVariable();

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
    else {
        this->numId = stoi(this->id);
    }
}

bool Bank::idAlreadyExists() {
    if (!this->isIdANum() || this->accountsData.contains(this->numId))
        return false;

    return true;
}

bool Bank::isIdANum() {
    if (all_of(this->id.begin(),
               this->id.end(),
               [](const char& c) {
                   return isdigit(c);
               })) {
        this->numId = stoi(this->id);
        return true;
    }
    return false;
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
    return all_of(this->accountsData.begin(), this->accountsData.end(), [this](auto& pair) {
        return pair.second[1] != this->email;
    });
}

void Bank::recoveringPassword() {
    cout << this->idMess;
    getline(cin, this->id);

    cout << this->emailMess;
    getline(cin, this->email);

    if (!this->isIdANum() || !this->isTheSameEmail()) {
        cout << this->redColor << this->wrongEmailIdMess << this->colorReset << '\n';
        this->recoveringPassword();
    }
    else {
        this->showRecoveredPassword();
    }
}

bool Bank::isTheSameEmail() {
    return this->email == this->accountsData[this->numId][1];
}

void Bank::showRecoveredPassword() {
    cout << this->accountsData[this->numId][4] << '\n';
}

void Bank::addAccountToDatabase() const {
    ofstream tempDatabaseFile(this->tempDb);
    ifstream databaseFile{this->databaseFilePath};
    string accountDetails;

    while (getline(databaseFile, accountDetails)) {
        tempDatabaseFile << accountDetails << '\n';
    }

    tempDatabaseFile << this->id << ';' << this->email << ';' << this->userName
        << ';' << this->userSurname << ';' << this->password << ";" << "0" << '\n';

    fs::remove(this->databaseFilePath);
    fs::rename(this->tempDb, this->databaseFilePath);
}

void Bank::addAccountToVariable() {
    this->accountsData[this->numId].push_back(this->id);
    this->accountsData[this->numId].push_back(this->email);
    this->accountsData[this->numId].push_back(this->userName);
    this->accountsData[this->numId].push_back(this->userSurname);
    this->accountsData[this->numId].push_back(this->password);
    this->accountsData[this->numId].emplace_back("0");
}

void Bank::accountCreated() {
    cout << this->blueColor << this->accSuccCreatedMess << this->colorReset << '\n';
    cout << "Your account details: " << '\n';
    cout << "\tId and your login: " << this->numId << '\n';
    cout << "\tName: " << this->userName << '\n';
    cout << "\tSurname: " << this->userSurname << '\n';
    cout << "\tEmail: " << this->email << '\n';

    this->resetClassInfo();
}

void Bank::resetClassInfo() {
    this->numId = 0;
    this->id = "";
    this->userName = "";
    this->userSurname = "";
    this->password = "";
    this->email = "";
}

void Bank::updateAccount() {
    const string newBalance{std::to_string(acc.balance)};
    cout << "balans po konwercie " << newBalance << '\n';
    cout << "a to jest num id: " << this->numId << '\n';
    cout << "a to jest zwykły id: " << this->id << '\n';

    this->accountsData[this->numId][1] = acc.email;
    this->accountsData[this->numId][4] = acc.password;
    this->accountsData[this->numId][5] = newBalance;
}

void Bank::updateDatabaseFile() const {
    ofstream tempDbFile{this->tempDb};
    string accountDetails;
    for (auto& acc : this->accountsData) {
        for (int i{}; i < acc.second.size(); ++i) {
            if (i == acc.second.size() - 1) {
                tempDbFile << acc.second[i] << '\n';
            }
            else {
                tempDbFile << acc.second[i] << ';';
            }
        }
    }

    fs::remove(this->databaseFilePath);
    fs::rename(this->tempDb, this->databaseFilePath);
}
