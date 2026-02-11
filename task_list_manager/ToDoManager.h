#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

class ToDoManager {
private:
  const string fileName{"tasks.txt"};
  const string tempFile{"temp.txt"};
  fs::path pathToFile{this->fileName};
  const string blueColor{"\033[94m"};
  const string redColor{"\033[91m"};
  const string colorStop{"\033[0m"};
  string welcomeMessage{"Welcome to task manager!"};
  string successFileLoadMessage{"File with tasks loaded successfully!"};
  string createdTaskFileMessage{
      "Could not find the task file, so it has been created."};
  string tryAgain{"Try again: "};
  string wrongOption{"Wrong option. "};
  string wrongFileLine{"Wrong line number. "};
  const vector<string> optionsToChoose{
      "1. Check current tasks", "2. Add task", "3. Delete task",
      "4. Edit task",           "5. Exit",     "What do you want to do?: "};
  int line;
  int currentLine{1};
  int linesInFile{};
  int zeroUnixFromNine{48};

public:
  bool terminateProgram{false};
  ToDoManager();
  void countFileLines();
  void showingOptions();
  void userSelectingOption();
  bool checkingUserSelectedOption(string &userOptionLine, int OptionsLinesSize);
  void selectedUserOptionIsOk(int LinesInOptionsFile, string &message);
  void executeSelectedOption();
  void checkCurrentTasks();
  void editFile();
  void addTask();
  void deleteTask();
  void closeRenameFile(ifstream &fileWithTasks, ofstream &tempFile);
  void resetCurrentLineAndLine();
  void editTask();
  string userInsertingTask();
  const void userLeaving();
};