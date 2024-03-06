#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

int main(int argc, char **argv) {

  std::string path;
  getline(std::cin, path);

  std::unordered_map<std::string, std::pair<std::string, std::string>> network;

  std::string temp;
  getline(std::cin, temp);
  temp = "";

  std::regex regex_network(R"((\w+) = \((\w+), (\w+)\))");

  while (getline(std::cin, temp)) {
    std::smatch match;
    std::regex_match(temp, match, regex_network);
    network[match[1]] = std::make_pair(match[2], match[3]);
  }

  uint step = 0;
  bool found = false;

  while (!found) {
    std::string curr = "AAA";
    std::string next;
    for (int i = 0; !found; i++) {
      if (i == path.size()) {
        i = 0;
      }
      switch (path[i]) {
      case 'R':
        next = network[curr].second;
        break;
      case 'L':
        next = network[curr].first;
        break;
      }
      step++;
      if (next == "ZZZ") {
        found = true;
        continue;
      }
      curr = next;
    }
  }

  std::cout << step << std::endl;
  return 0;
}
