#include <climits>
#include <fstream>
#include <iostream>
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

typedef unsigned long long ullong;

std::vector<ullong> parse_digits(std::string line);
bool inrange(ullong n, ullong start, ullong len);

int main(int argc, char **argv) {
  std::vector<ullong> initial_seeds;
  std::vector<std::vector<std::vector<ullong>>> all_maps(7);

  // get input and parse it into vectors
  std::ifstream inputfile("./in/input.txt", std::ios::in);
  std::string line;
  getline(inputfile, line);
  initial_seeds = parse_digits(line);

  int flag = -1;

  while (getline(inputfile, line)) {

    if (line == "seed-to-soil map:") {
      flag = SEED_SOIL;
      continue;
    } else if (line == "soil-to-fertilizer map:") {
      flag = SOIL_FERTILIZER;
      continue;
    } else if (line == "fertilizer-to-water map:") {
      flag = FERTILIZER_WATER;
      continue;
    } else if (line == "water-to-light map:") {
      flag = WATER_LIGHT;
      continue;
    } else if (line == "light-to-temperature map:") {
      flag = LIGHT_TEMPERATURE;
      continue;
    } else if (line == "temperature-to-humidity map:") {
      flag = TEMPERATURE_HUMIDITY;
      continue;
    } else if (line == "humidity-to-location map:") {
      flag = HUMIDITY_LOCATION;
      continue;
    }
    std::vector<ullong> vec = parse_digits(line);
    if (vec.size() == 3) {
      all_maps[flag].push_back(vec);
    }
  }

  ullong lowest_location = ULLONG_MAX;
  for (int i = 0; i < initial_seeds.size(); i++) {
    ullong curr = initial_seeds[i];
    for (int map = SEED_SOIL; map <= HUMIDITY_LOCATION; map++) {
      for (int j = 0; j < all_maps[map].size(); j++) {
        if (inrange(curr, all_maps[map][j][0], all_maps[map][j][0]))
          // find the map
          ;
      }
    }
  }

  return 0;
}

bool inrange(ullong n, ullong start, ullong len) {
  return (n >= start) && (n < start + len);
}

// parse all digits in a line into vector using
std::vector<ullong> parse_digits(std::string line) {
  std::vector<ullong> alldigits;

  std::regex digit_regex(R"(\d+)");
  for (std::smatch match; std::regex_search(line, match, digit_regex);) {
    alldigits.push_back(std::stoll(match[0]));
    line = match.suffix();
  }

  return alldigits;
}
