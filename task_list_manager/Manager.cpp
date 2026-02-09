#include "Manager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::filesystem;
using std::cin;
using std::cout;

Manager::Manager() {
  cout << "Welcome to the task manager!" << '\n';

  fs::path p("tasks.txt");

  if (!fs::exists(p)) {
    cout << "\033[91mtasks.txt file not found. We created it for you.\033[0m"
         << '\n';
    std::ofstream file("tasks.txt");
  } else {
    cout << "\033[94mtasks.txt file loaded sucessfully\033[0m" << '\n';
  }

  int opts_size{static_cast<int>(this->options.size())};

  for (int i{}; i < opts_size; ++i) {
    cout << '\t' << i + 1 << ". " << this->options[i] << '\n';
  }
}

void Manager::selectingOption() {
  cout << "What you want do: ";

  string num;
  char unixZero;

  while (true) {
    std::getline(cin, num);

    if (num.size() != 1) {
      cout << "Wrong key try again: ";
      continue;
    }

    unixZero = num[0] - this->unixCodeToZero;

    if (unixZero == 1) {
      this->checkTasks();
    } else if (unixZero == 2) {
      this->addTask();
    }

    cout << "What do you want do now?: ";
  }
}

void Manager::checkTasks() {
  std::ifstream file("tasks.txt");
  fs::path p("tasks.txt");
  string line;
  int line_num{1};

  if (fs::file_size(p) == 0) {
    cout << "No tasks founds!" << '\n';
  } else {
    while (std::getline(file, line)) {
      cout << '\t' << line_num << ". " << line << '\n';
      ++line_num;
    }
  }
}

void Manager::addTask() {
  std::ofstream file("tasks.txt", std::ios::app);

  string line;

  cout << "Insert new task: ";
  getline(cin, line);

  file << line << '\n';
}
