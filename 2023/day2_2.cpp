#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

using namespace std;
unordered_map<string, int> mymap = {{"red", 0}, {"green", 0}, {"blue", 0}};

int main(int argc, char **argv) {
  int result = 0;

  string line;
  while (getline(cin, line)) {
    string curr_line = line;

    regex regex_count(R"((\d*) ([a-z]+))");
    int i = 0;
    for (smatch match2; regex_search(curr_line, match2, regex_count);) {
      int curr = stoi(match2[1]);
      if (mymap[match2[2]] < curr) {
        mymap[match2[2]] = curr;
      }
      curr_line = match2.suffix();
    }
    result += mymap["red"] * mymap["green"] * mymap["blue"];
    mymap = {{"red", 0}, {"green", 0}, {"blue", 0}};
  }

  cout << result << endl;

  return 0;
}
