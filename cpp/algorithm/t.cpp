#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
void permutation(string &input, int index) {
  if (index == input.length()) {
    cout << input << endl;
    return;
  }

  for (int i = index; i < input.size(); i++) {
    swap(input.at(index), input.at(i));
    permutation(input, index + 1);
    swap(input.at(index), input.at(i));
  }
}

void permutationV1(string &input, string &answer, vector<bool> &used,
                   int level) {
  if (level == input.length()) {
    cout << answer << endl;
    return;
  }
  for (int i = 0; i < input.length(); i++) {
    if (used[i] == false) {
      answer += input[i];
      used[i] = true;
      permutationV1(input, answer, used, level + 1);
      used[i] = false;
      answer.erase(answer.begin() + answer.size());
    }
  }
}
 
int main() {
    int A[] = {1,2,3};
    do{
        std::cout << A[0] << " " << A[1] << " " << A[2] << std::endl;
    }while(std::next_permutation(A,A+3));
    return 0;
}