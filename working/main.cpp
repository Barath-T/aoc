#include <fstream>
#include <regex>
#include <string>
#include <vector>

#define SEED_SOIL 0
#define SOIL_FERTILIZER 1
#define FERTILIZER_WATER 2
#define WATER_LIGHT 3
#define LIGHT_TEMPERATURE 4
#define TEMPERATURE_HUMIDITY 5
#define HUMIDITY_LOCATION 6

typedef unsigned long long muint;

std::vector<muint> parse_digits(std::string line) {
  std::vector<muint> alldigits;

  std::regex digit_regex(R"(\d)");
  for (std::smatch match; std::regex_search(line, match, digit_regex);) {
    alldigits.push_back(std::stoll(match[0]));
    line = match.suffix();
  }

  return alldigits;
}
int set_flag(std::string line) {
  std::regex regex_flag(R"((\w*)-to-(\w*) map:)");
  std::smatch match;
  std::regex_match(line, match, regex_flag);
  if (match.size() == 0) {
    return -1;
  } else {
    return 
  }
}

int main(int argc, char **argv) {
  std::vector<muint> initial_seeds;
  std::vector<std::vector<muint>> all_maps;

  std::ifstream inputfile("./in/input.txt", std::ios::in);
  std::string line;
  getline(inputfile, line);
  initial_seeds = parse_digits(line);

  int flag = -1;

  soil - to - fertilizer map : fertilizer - to - water map : water - to -
                                                             light map
      : light -
        to - temperature map : temperature - to - humidity map : humidity - to -
                                                                 location map
      : while (getline(inputfile, line)) {

    if (line == "seed-to-soil map:") {
      flag = SEED_SOIL;
      continue;
    } else if (line == "soil-to-fertilizer map:") {
      flag = SOIL_FERTILIZER;
      continue;
    }
  }

  return 0;
}
