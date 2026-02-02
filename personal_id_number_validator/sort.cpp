#include <iostream>
#include <vector>
using namespace std;
void selectionSort(vector<int> &);
void showElements(vector<int> &);

int main() {

  vector<int> nums_1{3, 1, 6, 2, 3, 8, 1};
  vector<int> nums_2{7, 3, 4, 2, 9, 8};

  showElements(nums_1);
  showElements(nums_2);

  selectionSort(nums_1);
  selectionSort(nums_2);

  cout << '\n';

  showElements(nums_1);
  showElements(nums_2);

  return 0;
}

void showElements(vector<int> &items) {
  cout << "Vector: ";

  for (int item : items) {
    cout << item << " ";
  }
  cout << '\n';
}

