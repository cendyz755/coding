#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
using namespace std;

void cleaner();
float selecting_num();
char selecting_operator(string &);
void calculating(float &, char &, float &);

int main() {
  cout << "Welcome to simple calculator!" << '\n';
  cout << "Select number: ";

  float n1{};
  n1 = selecting_num();

  while (true) {
    cout << "What do you want do? [+, -, ÷, ×] ";

    string operators{"+-/*"};
    char op;
    op = selecting_operator(operators);

    cout << "Select second number: ";

    float n2{};
    n2 = selecting_num();

    calculating(n1, op, n2);

    cout << "Wanna continue? Y/N: ";
    string check_con;
    char con;

    while (true) {
      getline(cin, check_con);

      if (check_con.size() == 1) {
        con = check_con[0];
        con = tolower(con);
      } else {
        cout << "You inserted too much letters. Try again: ";
        continue;
      }

      if (con == 'y' || con == 'n') {
        break;
      } else {
        cout << "Wrong key. Try again: ";
      }
    }

    if (con == 'n') {
      cout << "Bye." << '\n';
      break;
    }
  }

  return 0;
}

float selecting_num() {
  float n{};
  char c;

  while (true) {
    if (!(cin >> n) || (cin.get(c) && c != '\n')) {
      cout << "Wrong number. Try again: ";
      cleaner();
      continue;
    }
    return n;
  }
}

char selecting_operator(string &ops) {
  char s;

  while (true) {
    cin >> s;

    if (find(ops.begin(), ops.end(), s) == ops.end()) {
      cout << "This operator is not corret. Try again: ";
      cleaner();
      continue;
    }

    return s;
  }
}

void calculating(float &n1, char &op, float &n2) {
  float result{};

  if (op == '-') {
    result = n1 - n2;
  } else if (op == '+') {
    result = n1 + n2;
  } else if (op == '/') {
    result = n1 / n2;
  } else {
    result = n1 * n2;
  }

  cout << "Your result: " << result << '\n';
}

void cleaner() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
