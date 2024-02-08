#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

using namespace std;
unordered_map<string, int> mymap = {{"red", 12}, {"green", 13}, {"blue", 14}};

int main(int argc, char **argv) {
  int result = 0;
  int game_id = 1;

  string line;
  while (getline(cin, line)) {
    string curr_line = line;
    bool flag = true;

    regex regex_count(R"((\d*) ([a-z]+))");
    int i = 0;
    for (smatch match2; regex_search(curr_line, match2, regex_count);) {
      if (mymap[match2[2]] < stoi(match2[1])) {
        flag = false;
        break;
      }
      curr_line = match2.suffix();
    }
    if (flag) {
      result += game_id;
    }
    game_id++;
  }

  cout << result << endl;

  return 0;
}
