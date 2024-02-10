#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool is_symbol(char c) { return !isalnum(c) && c != '.'; }

bool perimeter_check(vector<string> &data, int line, int start, int end) {
  pair<bool, bool> border = {false, false};
  if (start == 0) {
    start = 1;
    border.first = true;
  }
  if (end == data[line].length() - 1) {
    end = data[line].length() - 2;
    border.second = true;
  }
  if (line > 1) {
    for (int i = start - 1; i <= end + 1; i++) {
      if (is_symbol(data[line - 1][i])) {
        return true;
      }
    }
  }
  if (line < data.size() - 1) {
    for (int i = start - 1; i <= end + 1; i++) {
      if (is_symbol(data[line + 1][i])) {
        return true;
      }
    }
  }
  bool flag1 = false;
  if (!border.first) {
    flag1 = is_symbol(data[line][start - 1]);
  }
  bool flag2 = false;
  if (!border.second) {
    flag2 = is_symbol(data[line][end + 1]);
  }
  return flag1 || flag2;
}

int main(int argc, char **argv) {
  std::vector<std::string> data;
  string line;
  while (cin >> line) {
    data.push_back(line);
  }

  int sum = 0;
  string curr_num = "";
  int start = -1, end = -1;
  bool checking_num = false;

  // parsing file
  for (int i = 0; i < data.size(); i++) {
    // parsing line
    for (int j = 0; j <= data[i].size(); j++) {
      if (j == data[i].size() || data[i][j] == '.' || !isalnum(data[i][j])) {
        if (checking_num) {
          end = j - 1;
          if (perimeter_check(data, i, start, end)) {
            sum += stoi(curr_num);
          }
          curr_num = "";
          checking_num = false;
          start = -1;
          end = -1;
        }
        continue;
      }
      if (isdigit(data[i][j])) {
        if (start == -1) {
          start = j;
        }
        curr_num += data[i][j];
        checking_num = true;
      }
    }
  }
  cout << sum << endl;
  return 0;
}
