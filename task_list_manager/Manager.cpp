#include "Manager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::filesystem;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;

Manager::Manager() {
  cout << "Welcome to the task manager!" << '\n';

  fs::path p("tasks.txt");

  if (!fs::exists(p)) {
    cout << "\033[91mtasks.txt file not found. We created it for you.\033[0m"
         << '\n';
    ofstream file("tasks.txt");
  } else {
    cout << "\033[94mtasks.txt file loaded sucessfully\033[0m" << '\n';
  }

  this->tasks = this->taskCounter();

  int opts_size{static_cast<int>(this->options.size())};

  for (int i{}; i < opts_size; ++i) {
    cout << '\t' << i + 1 << ". " << this->options[i] << '\n';
  }
}

int Manager::taskCounter() {
  ifstream file("tasks.txt");
  int lineNum{};

  string line;

  while (getline(file, line)) {
    ++lineNum;
  }

  return lineNum;
}

void Manager::selectingOption() {
  cout << "What you want do: ";

  string num;
  char unixZero;

  while (true) {
    getline(cin, num);

    if (num.size() != 1) {
      cout << "Wrong key try again: ";
      continue;
    }

    unixZero = num[0] - this->unixCodeToZero;

    if (unixZero == 1) {
      this->checkTasks();
    } else if (unixZero == 2) {
      this->addTask();
    } else if (unixZero == 3) {
      this->editTask();
    } else if (unixZero == 4) {
      this->deleteTask();
    } else if (unixZero == 5) {
      cout << "Bye." << '\n';
      break;
    } else {
      cout << "Wrong command. Try again: ";
      continue;
    }

    cout << "What do you want do now?: ";
  }
}

void Manager::checkTasks() {
  ifstream file("tasks.txt");
  fs::path p("tasks.txt");
  string line;
  int line_num{1};

  if (fs::file_size(p) == 0) {
    cout << "No tasks founds!" << '\n';
  } else {
    while (getline(file, line)) {
      cout << '\t' << line_num << ". " << line << '\n';
      ++line_num;
    }
  }
}

void Manager::addTask() {
  ofstream file("tasks.txt", std::ios::app);

  string line;

  cout << "Insert new task: ";
  getline(cin, line);

  file << line << '\n';
}

void Manager::deleteTask() {
  string line;
  ifstream in_file("tasks.txt");
  ofstream out_file("temp.txt");

  cout << "Which task do you want to be deleted? (insert line number): ";

  char line_to_delete;
  int current_line_num{1};

  while (true) {
    getline(cin, line);

    if (line.size() != 1) {
      cout << "Wrong line. Try again: ";
      continue;
    }

    line_to_delete = line[0] - this->unixCodeToZero;

    if (line_to_delete < this->tasks || line_to_delete > this->tasks) {
      cout << "Wrong line. Try again: ";
      continue;
    } else {
      while (getline(in_file, line)) {
        if (current_line_num != line_to_delete) {
          out_file << line << '\n';
        }
        ++current_line_num;
      }

      in_file.close();
      out_file.close();

      fs::remove("tasks.txt");
      fs::rename("temp.txt", "tasks.txt");

      cout << "Task deleted." << '\n';
      break;
    }
  }
}

void Manager::editTask() {
  cout << "Which task do you want to edit?: ";

  string user_choice;

  int line_to_edit{};
  while (true) {
    getline(cin, user_choice);

    if (user_choice.size() != 1) {
      cout << "Wrong task number. Try again: ";
      continue;
    }

    line_to_edit = user_choice[0] - this->unixCodeToZero - 1;

    if (line_to_edit > this->tasks || line_to_edit < 0) {
      cout << "Wrong task number. Try again: ";
      continue;
    } else {
      break;
    }
  }

  string newEditedTask;

  cout << "Insert text: ";

  getline(cin, newEditedTask);

  ifstream inFile("tasks.txt");
  ofstream otFile("temp.txt");

  cout << "gagagugu" << '\n';
  string line;

  int actualLine{};

  while (getline(inFile, line)) {
    if (actualLine == line_to_edit) {
      otFile << newEditedTask << '\n';
    } else {
      otFile << line << '\n';
    }

    ++actualLine;
  }

  inFile.close();
  otFile.close();

  fs::remove("tasks.txt");
  fs::rename("temp.txt", "tasks.txt");
}