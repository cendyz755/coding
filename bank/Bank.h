#ifndef BANK_BANK_H
#define BANK_BANK_H

#include <random>
#include <regex>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::regex;
using std::regex_match;

class Bank {
private:
    string redColor{"\033[91m"};
    string blueColor{"\033[94m"};
    string colorReset{"\033[0m"};
    string welcomeMessage{"Welcome to the bank!"};
    vector<string> startOptions{"Login", "Register", "Exit"};
    void selectingStartOption();
    void showMenu() const;

    string databaseFilePath{"database.csv"};
    void isAccountsDatabaseExists() const;

    regex menuOptRegex{R"(^[1-3]$)"};
    string userOption;
    string tempUserOption;
    string wrongOptionMessage{"Wrong option. "};
    string startingOptsMess{"What do you want do now: "};
    bool validateUserOption();

    string tryAgainMessage{"Try again: "};
    void executeSelectedOption();

    void registerAccount();

    regex nameRegex{R"(^[A-Za-z]{3,15}$)"};
    string askingName{"Your name: "};
    string askingSurname{"And your surname: "};
    string wrongNameMess{
        "Your name can contains only letters and "
        "size must be between 3 and 15."
    };
    string userName;
    string userSurname;
    void userInsertingNameSurname();
    [[nodiscard]] bool validateUsername();

    regex passRegex{R"(^[a-zA-Z0-9!@#$%^&*]{7,16}$)"};
    string newPassMess{"New password: "};
    string password;
    vector<int> passLen{7, 20};
    string wrongNewPassMess{
        "Your password must contain letters, digits and special symbols "
        "and size must be between 7 and 20."
    };
    void userInsertingPassword();
    [[nodiscard]] bool validatePassword();

    string id{};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dist{0, 9};
    void generateId();
    [[nodiscard]] bool idAlreadyExists() const;
    [[nodiscard]] bool lookingForTheSameIdInFile(const string& accountDetails) const;

    string sameEmailMess{"This e-mail already exists."};
    regex emailRegex{
        R"(^[A-Za-z0-9._%+\-]+@[A-Za-z0-9\-]+(?:\.[A-Za-z0-9\-]+)*\.[A-Za-z]{2,}$)"
    };
    string wrongEmailMess{"This is not a valid email"};
    string emailMess{"Your email: "};
    string email;
    void userInsertingEmail();
    [[nodiscard]] bool validateEmail() const;
    [[nodiscard]] bool emailAlreadyExists() const;

    string tempDb{"tempDb.csv"};
    void addAccountToDatabase() const;

    string accSuccCreatedMess{"Account created successfully!"};
    string newAccInfoMess{"Your new account details: "};
    void accountCreated();
    void resetClassInfo();

    void login();

    bool idOk{};
    bool passOk{};
    void loginInId();
    bool idAndPassInDatabase() const;

public:
    Bank();
};

#endif //BANK_BANK_H
