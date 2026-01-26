#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <string>
#include <vector>
using namespace std;

void welcome();
void showing_options(map<int, string> *, vector<string> &);
void selecting_options();
void adding_deleting_options(map<int, string> *, map<int, string> *,
                             vector<string> *, vector<string> &, string);
void continue_adding_options();
void toggle_all(vector<string> &, string);
void cleaner();
void generate_password(vector<string> &, int, string);

void selecting_password_size(int &);

map<int, string> *options_names{new map<int, string>};
map<int, string> *options_values{new map<int, string>};

vector<string> selected_options{};
vector<string> selected_values{};
string still_choosing{"y"};
int pass_size{};
string generated_password;

int main() {
  (*options_names)[1] = "lowercase letters";
  (*options_names)[2] = "uppercase letters";
  (*options_names)[3] = "digits";
  (*options_names)[4] = "special symbols";

  (*options_values)[1] = "abcdefghijklmnopqrstuvwxyz";
  (*options_values)[2] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  (*options_values)[3] = "0123456789";
  (*options_values)[4] = "!@#$%^&*";

  welcome();

  while (selected_options.size() < 2 && still_choosing == "y") {
    showing_options(options_names, selected_options);
    selecting_options();
  }

  selecting_password_size(pass_size);

  delete options_names;
  delete options_values;

  cout << '\n';

  generate_password(selected_values, pass_size, generated_password);

  return 0;
}

void cleaner() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void welcome() {
  cout << "Welcome to the password generator!" << '\n';
  cout << "For first select minimum two password options.\n\n";
}

void showing_options(map<int, string> *opts, vector<string> &user_opts) {
  for (auto &[key, value] : *opts) {
    cout << key << ". " << value << '\n';
  }
}

void selecting_options() {
  int num{};
  char c;
  string s;

  while (still_choosing == "y") {
    cout << "\tWhat option do you want to add: ";

    if (!(cin >> num) || (cin.get(c) && c != '\n') || (num > 4 && num < 1)) {
      cout << "Wrong option. Try again: ";
      cleaner();
      continue;
    }

    cout << '\n';

    cout << "Option added." << '\n';
    cout << "Current options: ";

    toggle_all(selected_options, (*options_names)[num]);
    toggle_all(selected_values, (*options_values)[num]);

    for (int i{}; i < selected_options.size(); ++i) {
      if (i == selected_options.size() - 1) {
        cout << "\033[32m" << (selected_options)[i] << "\033[0m";
      } else {
        cout << "\033[32m" << (selected_options)[i] << "\033[0m" << ", ";
      }
    }

    cout << "\n\n";

    if (selected_values.size() >= 2) {
      cout << "There is already " << selected_values.size()
           << " selected options." << '\n';
      cout << "Do you want to continue adding options? Y/N: ";

      continue_adding_options();
    }
  }
}

void toggle_all(vector<string> &v, string value) {
  auto it = find(v.begin(), v.end(), value);

  if (it != v.end()) {
    v.erase(it);
  } else {
    v.push_back(value);
  }
}

void continue_adding_options() {
  string s;

  while (true) {
    getline(cin, s);

    if (s.size() != 1) {
      cout << "Wrong key. Try again: ";
    }

    if (s == "y" || s == "Y") {
      return;
    } else if (s == "n" || s == "N") {
      still_choosing = "n";
      return;
    } else {
      cout << "Wrong key. Try again: ";
    }
  }
}

void selecting_password_size(int &n) {
  int num{};
  char c;

  cout << "Select password length between 6 and 20: ";

  while (true) {

    if (!(cin >> num) || (cin.get(c) && c != '\n')) {
      cout << "This is not a number try again: ";
      cleaner();
      continue;
    }

    if (num > 20 || num < 6) {
      cout << "Wrong number. try again: ";
    } else {
      n = num;
      break;
    }
  }
}

void generate_password(vector<string> &opts, int len, string pass) {

  random_device rd;
  mt19937 gen(rd());

  while (pass.size() < len) {
    uniform_int_distribution<> dist(0, opts.size() - 1);

    string selected_op{opts[dist(gen)]};
    uniform_int_distribution<> dist2(0, selected_op.size() - 1);

    if (pass.size() >= len - 3) {

      for (int i{}; i < len - pass.size(); ++i) {
        pass += selected_op[dist2(gen)];
      }

    } else {
      pass += selected_op[dist2(gen)];
    }
  }

  cout << "Your password: " << pass << '\n';
}