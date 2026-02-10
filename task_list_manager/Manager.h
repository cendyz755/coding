#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Manager {
private:
  vector<string> options{"Check current tasks", "Add task", "Edit task",
                         "Delete task", "Exit"};
  int unixCodeToZero{48};
  int tasks{};

public:
  Manager();
  void selectingOption();
  void checkTasks();
  void addTask();
  void deleteTask();
  int taskCounter();
  void editTask();
};
