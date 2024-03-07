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
    std::regex digit_regex(R"(([-]*)(\d+))");
    for (std::smatch match; std::regex_search(temp, match, digit_regex);) {
      int curr = match[1] == '-' ? (stoi(match[2]) * (-1)) : stoi(match[2]);
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

  bool all_zeros = true;
  std::vector<int> next_seq;
  for (int i = 1; i < seq.size(); i++) {
    next_seq.push_back(seq[i] - seq[i - 1]);
    all_zeros = false;
  }

  if (all_zeros)
    return 0;

  result = seq[seq.size() - 1] + find_next(next_seq);

  return result;
}
