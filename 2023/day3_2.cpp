#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
bool is_symbol(char c) { return c == '*'; }

vector<pair<int, int>> perimeter_check(vector<string> &data, int line,
                                       int start, int end) {
  vector<pair<int, int>> result;
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
        result.push_back(make_pair(line - 1, i));
      }
    }
  }
  if (line < data.size() - 1) {
    for (int i = start - 1; i <= end + 1; i++) {
      if (is_symbol(data[line + 1][i])) {
        result.push_back(make_pair(line + 1, i));
      }
    }
  }
  bool flag1 = false;
  if (!border.first) {
    if (is_symbol(data[line][start - 1])) {
      result.push_back(make_pair(line, start - 1));
    }
  }
  bool flag2 = false;
  if (!border.second) {
    if (is_symbol(data[line][end + 1])) {
      result.push_back(make_pair(line, end + 1));
    }
  }
  return result;
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
  map<pair<int, int>, vector<int>> starmap;

  // parsing file
  for (int i = 0; i < data.size(); i++) {
    // parsing line
    for (int j = 0; j <= data[i].size(); j++) {
      if (j == data[i].size() || data[i][j] == '.' || !isalnum(data[i][j])) {
        if (checking_num) {
          end = j - 1;
          vector<pair<int, int>> allstars =
              perimeter_check(data, i, start, end);
          int icurr_num = stoi(curr_num);
          if (allstars.size() != 0) {
            for (int k = 0; k < allstars.size(); k++) {
              starmap[allstars[k]].push_back(icurr_num);
            }
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
  for (pair<pair<int, int>, vector<int>> p : starmap) {
    if (p.second.size() == 2) {
      sum += p.second[0] * p.second[1];
    }
  }
  cout << sum << endl;
  return 0;
}
