#include "id_validator/IdValidator.h"
#include <iostream>
using namespace std;

int main() {
  cout << "Welcome to the personal id validator programme." << '\n';

  bool shouldBeContinued{};

  while (true) {

    IdValidator *person_id{new IdValidator{}};

    cout << "Insert id number: ";

    while (true) {
      person_id->userInsertingID();

      if (person_id->idSizeChecking()) {
        break;
      }
    }

    vector<bool> isLetterHere{
        person_id->is_a_number(0), person_id->is_a_number(2),
        person_id->is_a_number(4), person_id->is_a_number(6),
        person_id->is_a_number(8), person_id->is_a_number(9)};

    for (bool num : isLetterHere) {
      if (!num) {
        cout << person_id->lightRed
             << "There are letters in your id. Try again."
             << person_id->colorRest << '\n';
        shouldBeContinued = true;
        break;
      }
    }

    if (shouldBeContinued) {
      shouldBeContinued = false;
      delete person_id;
      continue;
    }

    vector<bool> correctNumbers{person_id->settingCheckingMonth(),
                                person_id->checkingDay(),
                                person_id->checkingControlNumber()};

    for (bool correctNum : correctNumbers) {
      if (!correctNum) {
        cout << person_id->lightRed << "Your id is invalid. Try again."
             << person_id->colorRest << '\n';
        shouldBeContinued = true;
        break;
      }
    }

    if (shouldBeContinued) {
      shouldBeContinued = false;
      delete person_id;
      continue;
    }

    person_id->maleOrFemale();

    person_id->showPersonInfo();

    cout << '\n';

    cout << "Do you want check another person id? Y/N: ";

    if (person_id->continueChecking()) {
      delete person_id;
    } else {
      cout << "Bye." << '\n';
      break;
    }
  }
  return 0;
}