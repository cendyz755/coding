#include "ToDoManager.h"

int main() {

  ToDoManager userTasks;
  while (!userTasks.terminateProgram) {
    userTasks.showingOptions();
    userTasks.userSelectingOption();
  }

  return 0;
}