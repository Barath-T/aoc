#include <iostream>
#include <regex>
#include <vector>

int find_next(std::vector<int> seq);

int main(int argc, char **argv) {

  std::vector<std::vector<int>> input;
  std::string line;

  while (getline(std::cin, line)) {
    input.push_back(std::vector<int>());
    std::string temp = line;
    std::regex digit_regex(R"(\d+)");
    for (std::smatch match; std::regex_search(temp, match, digit_regex);) {
      input[input.size() - 1].push_back(std::stoi(match[0]));
      temp = match.suffix();
    }
  }

  int result = 0;

  for (int i = 0; i < input.size(); i++) {
    int curr = find_next(input[i]);
    result += curr;
  }
  std::cout << result << std::endl;
  return 0;
}

int find_next(std::vector<int> seq) {
  int result;
  std::vector<int> next_sequence;
  bool all_zeros = true;
  for (int i = 0; i < seq.size() - 1; i++) {
    int diff = seq[i + 1] - seq[i];
    next_sequence.push_back(diff);
    if (all_zeros && (diff != 0)) {
      all_zeros = false;
    }
  }

  if (all_zeros)
    return seq[seq.size() - 1];

  int down = find_next(next_sequence);
  result = seq[seq.size() - 1] + down;
  return result;
}
