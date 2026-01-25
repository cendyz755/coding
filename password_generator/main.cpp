#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

void welcome();
void showing_options(const map<int, string> &, vector<string> &);

const map<int, string> options_names{{1, "lowercase letters"},
                                     {2, "uppercase letters"},
                                     {3, "digits letters"},
                                     {4, "special letters"}};

vector<string> selected_options{};

int main() {

  welcome();

  showing_options(options_names, selected_options);

  return 0;
}

void welcome() {
  cout << "Welcome to the password generator!" << '\n';
  cout << "For first select minimum two password options.";
}

void showing_options(const map<int, string> &opts, vector<string> &user_opts) {

  for (auto &[key, value] : opts) {
    int j{1};

    if (find(user_opts.begin(), user_opts.end(), value) != user_opts.end()) {
      cout << "\033[32m" << j << ". " << key << "\033[0m\n";
    } else {
      cout << j << ". " << key << '\n';
    }
    ++j;
  }
}