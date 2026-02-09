#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
// using std::fstream;

class Manager {
private:
  vector<string> options{"Check current tasks", "Add task", "Edit task",
                         "Delete task", "Exit"};
  int unixCodeToZero{48};

public:
  Manager();
  void selectingOption();
  void checkTasks();
  void addTask();
};
