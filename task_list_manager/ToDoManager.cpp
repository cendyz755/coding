#include "ToDoManager.h"
#include <filesystem>
#include <iostream>

using std::cin;
using std::cout;

ToDoManager::ToDoManager() {
  cout << this->welcomeMessage << '\n';
  if (!fs::exists(this->pathToFile)) {
    ofstream newTaskFile{this->pathToFile};
    cout << this->blueColor << this->createdTaskFileMessage << this->colorStop
         << '\n';
  } else {
    cout << this->blueColor << this->successFileLoadMessage << this->colorStop
         << '\n';
  }
  this->countFileLines();
};

void ToDoManager::countFileLines() {
  ifstream taskFile{this->pathToFile};
  string line;
  int lineNumbers{};
  while (getline(taskFile, line)) {
    ++lineNumbers;
  }
  this->linesInFile = lineNumbers;
}

void ToDoManager::showingOptions() {
  for (size_t i{}; i < this->optionsToChoose.size(); ++i) {
    if (i == this->optionsToChoose.size() - 1) {
      cout << this->optionsToChoose[i];
    } else {
      cout << '\t' << this->optionsToChoose[i] << '\n';
    }
  }
  this->resetCurrentLineAndLine();
}

void ToDoManager::userSelectingOption() {
  this->selectedUserOptionIsOk(static_cast<int>(this->optionsToChoose.size()),
                               this->wrongOption);
  this->executeSelectedOption();
  // resetCurrentLineAndLine();
}

void ToDoManager::selectedUserOptionIsOk(int linesInFileOptions,
                                         string &message) {
  string line;
  while (true) {
    if (this->checkingUserSelectedOption(line, linesInFileOptions)) {
      break;
    } else {
      cout << this->redColor << message << this->colorStop << this->tryAgain;
    };
  }
  this->line = line[0] - this->zeroUnixFromNine;
}

bool ToDoManager::checkingUserSelectedOption(string &userOptionLine,
                                             int optionsLineSize) {
  getline(cin, userOptionLine);
  if (userOptionLine.size() != 1 ||
      userOptionLine[0] - this->zeroUnixFromNine < 1 ||
      userOptionLine[0] - this->zeroUnixFromNine > optionsLineSize) {
    return false;
  }
  return true;
}

void ToDoManager::executeSelectedOption() {
  switch (this->line) {
  case 1:
    this->checkCurrentTasks();
    break;
  case 2:
    this->addTask();
    break;
  case 3:
    this->deleteTask();
    break;
  case 4:
    editTask();
    break;
  default:
    this->userLeaving();
  }
}

void ToDoManager::checkCurrentTasks() {
  ifstream fileWithTasks{this->pathToFile};
  if (fs::file_size(this->pathToFile) == 0) {
    cout << this->blueColor << "No tasks found!" << this->colorStop << '\n';
    return;
  }
  string line;
  string separator(20, '~');
  cout << separator << '\n';
  cout << "Current tasks:" << '\n';
  while (getline(fileWithTasks, line)) {
    cout << '\t' << this->blueColor << this->currentLine << ". "
         << this->colorStop << line << '\n';
    ++this->currentLine;
  }
  cout << separator << '\n';
}

void ToDoManager::addTask() {
  cout << "New task: ";
  ifstream taskFile{this->pathToFile};
  ofstream tempFile{this->tempFile};
  string line;
  while (getline(taskFile, line)) {
    tempFile << line << '\n';
  }
  tempFile << this->userInsertingTask() << '\n';
  this->closeRenameFile(taskFile, tempFile);
  this->countFileLines();
  cout << blueColor << "Task added!" << colorStop << '\n';
}

void ToDoManager::deleteTask() {
  cout << "Which number of task do you want be deleted?: ";
  this->selectedUserOptionIsOk(this->linesInFile, this->wrongFileLine);
  ifstream fileWithTasks{this->pathToFile};
  ofstream newTaskFile{this->tempFile};
  string line;
  while (getline(fileWithTasks, line)) {
    if (this->currentLine != this->line) {
      newTaskFile << line << '\n';
    }
    ++this->currentLine;
  }
  this->closeRenameFile(fileWithTasks, newTaskFile);
  this->countFileLines();
  cout << this->blueColor << "Task deleted." << this->colorStop << '\n';
}

void ToDoManager::closeRenameFile(ifstream &fileWithTasks,
                                  ofstream &newTaskFile) {
  fileWithTasks.close();
  newTaskFile.close();
  fs::remove(this->pathToFile);
  fs::rename(this->tempFile, this->pathToFile);
}

void ToDoManager::resetCurrentLineAndLine() {
  this->currentLine = 1;
  this->line = 0;
}

void ToDoManager::editTask() {
  cout << "Which task do you want edit?: ";
  this->selectedUserOptionIsOk(this->linesInFile, this->wrongFileLine);
  ifstream fileWithTasks{this->pathToFile};
  ofstream newTaskFile{this->tempFile};
  string line;
  cout << "Insert your text: ";
  string userEditedTask{this->userInsertingTask()};
  while (getline(fileWithTasks, line)) {
    if (this->currentLine == this->line) {
      newTaskFile << userEditedTask << '\n';
    } else {
      newTaskFile << line << '\n';
    }
    ++this->currentLine;
  }
  this->closeRenameFile(fileWithTasks, newTaskFile);
  this->countFileLines();
  cout << this->blueColor << "Task edited." << this->colorStop << '\n';
}

string ToDoManager::userInsertingTask() {
  string newTask;
  getline(cin, newTask);
  return newTask;
};

const void ToDoManager::userLeaving() {
  this->terminateProgram = true;
  cout << "Bye." << '\n';
}