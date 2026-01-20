#include <cstdio>
#include <iostream>
#include <limits>
#include <math.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>
using namespace std;

int selecting_type(vector<string>);
int from_unit_func(unordered_map<int, vector<string>>, int);
int more_than_two_units(vector<string>, int);
double select_value();
double cel_to_fah();
double fah_to_cel();
void cleaner();

int main() {
  vector<string> types{"temperature", "length", "weight"};

  unordered_map<int, vector<string>> what_units{
      {1, {"celsius", "fahrenheit"}},
      {2, {"centimeter", "inch", "kilometer"}},
      {3, {"kilogram", "pound"}}};

  int selected_type{};
  selected_type = selecting_type(types);
  cout << '\n';

  int from_unit{};
  from_unit = from_unit_func(what_units, selected_type);
  cout << '\n';

  int to_unit{};
  if (what_units[selected_type].size() > 2) {
    to_unit = more_than_two_units(what_units[selected_type], from_unit);
    cout << '\n';
  }

  double user_value{};
  user_value = select_value();


  if (types[selected_type - 1] == "length") {
      if (from_unit == 1 && to_unit == 2) {
        user_value /= 2.54;
      }
  } 

  cout << "This is your result: " << fixed << setprecision(3) << user_value << '\n';

  return 0;
}

void cleaner() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int selecting_type(vector<string> type) {
  cout << "Welcome to units converter!" << '\n';
  cout << "You can choose from these types:" << '\n';

  for (size_t i{}; i < type.size(); ++i) {
    cout << '\t' << i + 1 << ". " << type[i] << '\n';
  }

  int selected{};
  string c;

  cout << "Enter unit type: ";

  while (true) {
    getline(cin, c);

    if (c.size() != 1) {
      cout << "Wrong number. Try again: ";
      continue;
    }

    selected = stoi(c);

    if (selected < 1 || selected > 3) {
      cout << "Wrong number. Try again: ";
    } else {
      break;
    }
  }

  return selected;
}

int from_unit_func(unordered_map<int, vector<string>> units, int selected) {
  cout << "Select from what unit do you want to convert:" << '\n';

  for (int i{}; i < units[selected].size(); ++i) {
    cout << '\t' << i + 1 << ". " << units[selected][i] << '\n';
  }

  cout << "Enter unit number: ";

  int sel_unit{};
  string c;

  while (true) {
    getline(cin, c);

    if (c.size() != 1) {
      cout << "Wrong number. Try again: ";
      continue;
    }

    sel_unit = stoi(c);

    if (sel_unit > units[selected].size() || sel_unit < 1) {
      cout << "Wrong number. Try again: ";
    } else {
      break;
    }
  }

  return sel_unit;
}

int more_than_two_units(vector<string> types, int from) {
  int dest_unit{};
  string s;

  cout << "It seems there is more than 2 units. Select to what unit it should "
          "be converted:"
       << '\n';

  for (int i{}; i < types.size(); ++i) {
    if (i != from - 1) {
      cout << '\t' << i + 1 << ". " << types[i] << '\n';
    }
  }

  cout << "Select final unit: ";

  while (true) {
    getline(cin, s);

    if (s.size() != 1) {
      cout << "Wrong number. Try again: ";
      continue;
    }

    dest_unit = stoi(s);

    if (dest_unit == from || dest_unit > types.size() || dest_unit < 1) {
      cout << "You can't choose that. Try again: ";
      continue;
    }

    break;
  }

  return dest_unit;
}

double select_value() {
  cout << "Enter the value you want to convert: ";

  double num{};
  char c;

  while (true) {

    if (!(cin >> num) || (cin.get(c) && c != '\n')) {
      cout << "This is not a number. Try again: ";
      cleaner();
    } else {
      break;
    }
  }

  return num;
}