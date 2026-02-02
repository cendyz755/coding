#include "id_validator/IdValidator.h"
#include <iostream>
using namespace std;

int main() {
  string idIsWrongMessage{"Your entered id number is not correct. Try again: "};

  cout << "Welcome to the personal id validator programme." << '\n';
  cout << "Inset your id number: ";

  IdValidator person_id;

  while (true) {
  }

  person_id.is_a_number(0);
  person_id.is_a_number(2);
  person_id.is_a_number(4);


  
  return 0;
}