#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int find_kind(std::string s);

int main(int argc, char **argv) {
  // input
  std::vector<std::string> hands;
  std::vector<uint> bids;
  std::string line;
  while (getline(std::cin, line)) {
    std::string temp = "";
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ' ') {
        hands.push_back(temp);
        i++;
        temp = "";
        for (; i < line.size(); i++) {
          temp += line[i];
        }
        bids.push_back(std::stoi(temp));
      }
      temp += line[i];
    }
  }
  uint result = 0;
  uint rank = 1;
  /* five of a kind, four of a kind, full house, three of a kind, two pair, one
   pair, high card */
  std::vector<std::vector<std::pair<std::string, uint>>> kinds(7);
  for (int i = 0; i < hands.size(); i++) {
    kinds[find_kind(hands[i])].push_back({hands[i], bids[i]});
  }
  for (int i = kinds.size() - 1; i >= 0; i--) {
    std::sort(
        kinds[i].begin(), kinds[i].end(),
        [](std::pair<std::string, uint> s1, std::pair<std::string, uint> s2) {
          if (s1.first == s2.first) {
            return true;
          }

          std::unordered_map<char, int> cards = {
              {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}};

          for (int i = 0; i < 5; i++) {
            int ic1 =
                isdigit(s1.first[i]) ? s1.first[i] - '0' : cards[s1.first[i]];
            int ic2 =
                isdigit(s2.first[i]) ? s2.first[i] - '0' : cards[s2.first[i]];
            if (ic1 == ic2)
              continue;
            return ic1 < ic2;
          }

          return true;
        });
  }
  for (int i = kinds.size() - 1; i >= 0; i--) {
    for (int j = 0; j < kinds[i].size(); j++) {
      result += kinds[i][j].second * rank;
      rank++;
    }
  }
  std::cout << result;
  return 0;
}

int find_kind(std::string s) {
  std::unordered_map<char, int> count;
  for (int i = 0; i < s.size(); i++) {
    count[s[i]] += 1;
  }
  std::vector<int> vec_kind(5);
  for (std::pair<char, int> p : count) {
    vec_kind[p.second - 1] += 1;
  }
  if (vec_kind[4] == 1) {
    return 0;
  } else if (vec_kind[3] == 1 && vec_kind[0] == 1) {
    return 1;
  } else if (vec_kind[2] == 1) {
    if (vec_kind[1] == 1) {
      return 2;
    }
    if (vec_kind[0] == 2) {
      return 3;
    }
  } else if (vec_kind[1] == 2 && vec_kind[0] == 1) {
    return 4;
  } else if (vec_kind[1] == 1 && vec_kind[0] == 3) {
    return 5;
  } else if (vec_kind[0] == 5) {
    return 6;
  }

  return -1;
}
