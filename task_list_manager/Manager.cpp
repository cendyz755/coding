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
    std::ofstream file("tasks.txt");
  }

  int opts_size{static_cast<int>(this->options.size())};

  for (int i{}; i < opts_size; ++i) {
    cout << '\t' << i + 1 << ". " << this->options[i] << '\n';
  }
}

void Manager::selectingOption() {
  cout << "What you want do: ";

  string num;
  char c;

  while (true) {
    std::getline(cin, num);

    if (num.size() != 1) {
      cout << "Wrong key try again: ";
      continue;
    }

    c = num[0];

    if (c - 48 == 1) {
      this->checkTasks();
      break;
    }
  }
}

void Manager::checkTasks() {
  std::ifstream file("tasks.txt");

  string line;

  while (std::getline(file, line)) {
    cout << '\t' << line << '\n';
  }
}
