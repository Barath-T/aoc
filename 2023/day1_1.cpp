#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  string line;
  int curr = 0;
  int sum = 0;
  while (std::cin >> line) {
    for (int i = 0; i < line.length(); i++) {
      if (isdigit(line[i])) {
        curr += (line[i] - '0') * 10;
        break;
      }
    }
    for (int i = line.length() - 1; i >= 0; i--) {
      if (isdigit(line[i])) {
        curr += (line[i] - '0');
        break;
      }
    }
    sum += curr;
    curr = 0;
  }
  cout << sum << endl;
  return 0;
}
