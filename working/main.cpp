#include <iostream>
#include <unordered_map>
#include <vector>

int find_kind(std::string s);
bool compare_hands(std::string s1, std::string s2);
void quick_sort(std::vector<std::pair<std::string, uint>> &array, int low,
                int high);

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
    for (std::pair<std::string, uint> p : kinds[i]) {
      std::cout << p.second << " " << p.first << std::endl;
    }
  }
  for (int i = kinds.size() - 1; i >= 0; i--) {
    quick_sort(kinds[i], 0, kinds[i].size() - 1);
  }
  for (int i = kinds.size() - 1; i >= 0; i--) {
    for (std::pair<std::string, uint> p : kinds[i]) {
      std::cout << p.second << " " << p.first << std::endl;
    }
  }
  for (int i = kinds.size() - 1; i >= 0; i--) {
    for (int j = 0; j < kinds[i].size(); j++) {
      std::cout << kinds[i][j].second << " " << rank << std::endl;
      result += kinds[i][j].second * rank;
      rank++;
    }
  }
  std::cout << compare_hands("KK677", "KTJJT") << std::endl;
  std::cout << result;
  return 0;
}
bool compare_hands(std::string s1, std::string s2) {
  if (s1 == s2) {
    return s1 == s2;
  }

  std::unordered_map<char, int> cards = {
      {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}};

  for (int i = 0; i < 5; i++) {
    int ic1 = isdigit(s1[i]) ? s1[i] - '0' : cards[s1[i]];
    int ic2 = isdigit(s2[i]) ? s2[i] - '0' : cards[s2[i]];
    if (ic1 == ic2)
      continue;
    return ic1 > ic2;
  }

  return s1 == s2;
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

int partition(std::vector<std::pair<std::string, uint>> &array, int low,
              int high) {

  int pivot = (low + high) / 2;

  // std::pair<std::string, uint> temp = array[pivot];
  // array[pivot] = array[high];
  // array[high] = temp;
  array[pivot].swap(array[high]);

  int i = low;
  int j = high - 1;
  for (; i < j;) {
    // compare function s1>s2
    if (compare_hands(array[i].first, array[high].first)) {
      i++;
    } else if (!compare_hands(array[j].first, array[high].first)) {
      j--;
    } else {
      array[j].swap(array[i]);
      // temp = array[j];
      // array[j] = array[i];
      // array[i] = temp;
      i++;
      j--;
    }
  }
  array[high].swap(array[i]);
  // temp = array[high];
  // array[high] = array[i];
  // array[i] = temp;
  return i;
}

void quick_sort(std::vector<std::pair<std::string, uint>> &array, int low,
                int high) {
  if (array.size() == 2) {
    if (compare_hands(array[0].first, array[1].first)) {
      array[0].swap(array[1]);
    }
    return;
  }
  if (low < high) {
    int p = partition(array, low, high);
    quick_sort(array, low, p - 1);
    quick_sort(array, p + 1, high);
  }
}
