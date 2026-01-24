#include <ios>
#include <iostream>
#include <limits>
#include <random>
#include <string>

using std::cin;
using std::cout;
using std::mt19937;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

char user_want_to_continue{'y'};
void welcome();
long long check_user_number(long long);
void guessing_number(long long correct_num);
void do_you_want_to_continue(char &);

int main() {
  if (user_want_to_continue == 'y') {
    void welcome();
  }
  long long from{};
  long long to{};

  cout << "From what number?: ";

  from = check_user_number(0);

  cout << "To what number?: ";

  to = check_user_number(from);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(from, to);

  long long x{dist(gen)};

  guessing_number(x);

  do_you_want_to_continue(user_want_to_continue);

  return 0;
}

inline void welcome(char c) {
  cout << "Welcome to guess the number game." << '\n';
  cout << "First, choose the range you want to guess." << '\n';
}

long long check_user_number(long long from) {
  string try_a{"Try again: "};

  long long s;
  char c;

  while (true) {

    if (!(cin >> s) || (cin.get(c) && c != '\n')) {
      cout << "This is not a number!" << '\n';
      cout << try_a;
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    } else if (from > s) {
      cout << "Your number can\'t be bigger than from number!" << '\n';
      cout << try_a;
      continue;
    } else {
      return s;
    }
  }
}

void guessing_number(long long correct_num) {
  cout << "Now guess the number!: ";
  string try_mess{"Try again: "};
  string nice_try{"Nice try! but your number is too "};

  long long user_num{};
  char c;

  while (true) {
    if (!(cin >> user_num) || (cin.get(c) && c != '\n')) {
      cout << "This is not a number! Try again: ";
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    if (user_num > correct_num) {
      cout << nice_try << "big" << '\n';
      cout << try_mess;
    } else if (user_num < correct_num) {
      cout << nice_try << "small" << '\n';
      cout << try_mess;
    } else {
      cout << "Congrats you guessed the number: " << user_num << "!" << '\n';
      return;
    }
  }
}

void do_you_want_to_continue(char &c) {
  cout << "Do you want start over? Y/N : ";
  string mess{"Wrong key. Try again: "};

  string s;

  while (true) {
    std::getline(cin, s);

    if (s.size() != 1) {
      cout << mess;
      continue;
    }

    if (s == "y" || s == "y") {
      c = 'n';
      main();
      return;
    } else if (s == "n" || s == "N") {
      cout << "Bye." << '\n';
      return;
    } else {
      cout << mess;
    }
  }
}