#ifndef BANK_BANK_H
#define BANK_BANK_H


#include <format>
#include <random>
#include <regex>
#include <string>
#include <vector>
#include <regex>
using std::string;
using std::vector;
using std::format;

class Bank {
private:
    string specialSymbols{"!@#$%^&*(\\)/';:"};
    string redColor{"\033[91m"};
    string blueColor{"\033[94m"};
    string colorReset{"\033[0m"};
    string welcomeMessage{"Welcome to the bank!"};
    vector<string> startOptions{"Login", "Register", "Exit"};
    void selectingStartOption();

    string databaseFilePath{"database.csv"};
    void isAccountsDatabaseExists() const;

    int toZeroUnix{48};
    int userOption{};
    string tempUserOption;
    string wrongOptionMessage{"Wrong option. "};
    string startingOptsMess{"What do you want do now: "};
    bool validateUserOption();

    string tryAgainMessage{"Try again: "};
    void executeSelectedOption();

    void registerAccount();

    vector<int> nameLen{3, 15};
    string askingName{"Your name: "};
    string askingSurname{"And your surname: "};
    string wrongNameSize{format("Name size must be between {} and {}.", this->nameLen[0], this->nameLen[1])};
    string wrongNameMess{"Your name can contains only letters"};
    string userName;
    string userSurname;
    void userInsertingNameSurname();
    static bool isUserNameContainsSymbols(string name);

    string newPassMess{"New password: "};
    string password;
    vector<int> passLen{7, 20};
    vector<string> passLegalSymbols{
        "0123456789", "!@#$%^&*",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    };
    string wrongPassSymbolsMess{
        "Your password must contain letters, digits and special symbols."
    };
    string wrongPassLenMess{
        format("Password length must be between {} and {}", this->passLen[0], this->passLen[1])
    };
    void userInsertingPassword();
    void isStrongPassword();

    short int idLen{8};
    string tempId;
    int id{};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dist{0, 9};
    void generateId();
    void idAlreadyExists();
    [[nodiscard]] bool lookingForTheSameIdInFile(string accountDetails) const;

    std::regex emailRegex{
        R"(^[A-Za-z0-9._%+\-]+@[A-Za-z0-9\-]+(?:\.[A-Za-z0-9\-]+)*\.[A-Za-z]{2,}$)"
    };
    string wrongEmailMess{"This is not a valid email"};
    string emailMess{"Your email: "};
    string email;
    void userInsertingEmail();
    bool validateEmail();

    string tempDb{"tempDb.csv"};
    void addAccountToDatabase() const;

    string accSuccCreatedMess{"Account created successfully!"};
    string newAccInfoMess{"Your new account details: "};
    void accountCreated() const;

public:
    Bank();
};


#endif //BANK_BANK_H
