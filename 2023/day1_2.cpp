#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void preprocess(string &line) {
  unordered_map<string, char> numbers = {
      {"one", '1'},   {"two", '2'},   {"three", '3'},
      {"four", '4'},  {"five", '5'},  {"six", '6'},
      {"seven", '7'}, {"eight", '8'}, {"nine", '9'},
  };

  size_t pos = 0;

  string preprocessed = line;

  for (pair<string, int> p : numbers) {
    pos = line.find(p.first, 0);
    while (pos != string::npos) {
      preprocessed[pos] = numbers[p.first];
      pos = line.find(p.first, pos + 1);
    }
  }
  line = preprocessed;
}

int main(int argc, char **argv) {
  string line;
  int curr = 0;
  int sum = 0;
  while (std::cin >> line) {
    preprocess(line);
    for (int i = 0; i < line.length(); i++) {
      if (isdigit(line[i])) {
        curr += (line[i] - '0') * 10;
        break;
      }
    }
    for (int i = (int)line.length() - 1; i >= 0; i--) {
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
