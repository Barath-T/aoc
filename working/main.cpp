#include <iostream>
#include <regex>
#include <unordered_set>

int main(int argc, char **argv) {
  int sum = 0;

  std::string line;
  while (getline(std::cin, line)) {
    std::string curr_line = line;
    std::regex cardRegex(R"(\d+)");
    std::unordered_set<int> prize;
    int i = 0;
    int curr_counter = 0;
    for (std::smatch match; std::regex_search(curr_line, match, cardRegex);) {
      if (i == 0) {
      } else if (i <= 5) {
        prize.insert(stoi(match[0]));
      } else {
        if (prize.find(stoi(match[0])) != prize.end()) {
          curr_counter++;
        }
      }
      curr_line = match.suffix();
      i++;
    }
    //check here
    std::cout << ((2 ^ (curr_counter - 1))) << std::endl;
    sum += ((2 ^ (curr_counter - 1)) * curr_counter);
    i = 0;
    curr_counter = 0;
  }
  std::cout << sum << std::endl;

  return 0;
}
