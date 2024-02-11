#include <iostream>
#include <map>
#include <regex>
#include <unordered_set>

int main(int argc, char **argv) {
  std::vector<std::string> cards;

  std::string line;
  while (getline(std::cin, line)) {
    cards.push_back(line);
  }

  int sum = 0;
  //{cardno, {remaining, total count, wins}}
  std::map<int, std::vector<int>> cardsmap;

  std::regex regex_digit(R"(\d+)");
  std::smatch temp;
  std::regex_search(cards[cards.size() - 1], temp, regex_digit);
  int last_card = stoi(temp[0]);
  for (int i = 0; i < cards.size(); i++) {
    std::string curr_line = cards[i];
    std::regex regex_card(R"(Card\s*(\d+): (.*)\|(.*))");
    std::smatch match_prizes;
    std::regex_match(curr_line, match_prizes, regex_card);

    int cardno = stoi(match_prizes[1]);
    std::string prizes = match_prizes[2];
    std::string our_numbers = match_prizes[3];

    int curr_counter = 0;
    std::unordered_set<int> prize;

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

    cardsmap[cardno].push_back(1);
    cardsmap[cardno].push_back(0);
    cardsmap[cardno].push_back(curr_counter);
  }

  for (std::pair<int, std::vector<int>> p : cardsmap) {
    for (int i = 1; i <= p.second[2]; i++) {
      if (p.first + i <= last_card) {
        cardsmap[p.first + i][0] += cardsmap[p.first][0];
      }
    }
    cardsmap[p.first][1] += cardsmap[p.first][0];
    cardsmap[p.first][0] = 0;
    sum += cardsmap[p.first][1];
  }

  std::cout << sum << std::endl;

  return 0;
}
