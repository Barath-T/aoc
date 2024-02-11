#include <cmath>
#include <iostream>
#include <regex>
#include <unordered_set>

int main(int argc, char **argv) {
  int sum = 0;

  std::string line;
  while (getline(std::cin, line)) {
    std::string curr_line = line;
    std::regex regex_card(R"(Card\s*\d+: (.*)\|(.*))");
    std::smatch match_prizes;
    std::regex_match(curr_line, match_prizes, regex_card);

    std::string prizes = match_prizes[1];
    std::string our_numbers = match_prizes[2];

    int curr_counter = 0;
    std::unordered_set<int> prize;

    std::regex regex_digit(R"(\d+)");
    for (std::smatch match; std::regex_search(prizes, match, regex_digit);) {
      prize.insert(stoi(match[0]));
      prizes = match.suffix();
    }
    for (std::smatch match;
         std::regex_search(our_numbers, match, regex_digit);) {
      if (prize.find(stoi(match[0])) != prize.end()) {
        curr_counter++;
      }
      our_numbers = match.suffix();
    }

    if (curr_counter > 0) {
      sum += (pow(2, (curr_counter - 1)));
      curr_counter = 0;
    }
  }
  std::cout << sum << std::endl;

  return 0;
}
