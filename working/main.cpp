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
ullong map_sd(ullong ss, ullong ds, ullong curr);
ullong find_lowest(std::vector<std::pair<ullong, ullong>> vec);

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
  for (int i = 0; i < initial_seeds.size(); i += 2) {
    std::vector<std::pair<ullong, ullong>> yet_to_be;
    std::vector<std::pair<ullong, ullong>> mapped;
    std::vector<std::pair<ullong, ullong>> next;

    ullong seed_start = initial_seeds[i];
    ullong seed_end = initial_seeds[i] + initial_seeds[i + 1] - 1;

    yet_to_be.push_back({seed_start, seed_end});

    for (int map = SEED_SOIL; map <= HUMIDITY_LOCATION; map++) {

      for (int j = 0; j < all_maps[map].size(); j++) {

        ullong source_start = all_maps[map][j][1];
        ullong source_end = all_maps[map][j][1] + all_maps[map][j][2] - 1;

        ullong dest_start = all_maps[map][j][0];
        ullong dest_end = all_maps[map][j][0] + all_maps[map][j][2] - 1;

        for (int k = yet_to_be.size() - 1; k >= 0; k--) {
          std::cout << yet_to_be.size() << " " << mapped.size() << " " << j
                    << std::endl;
          ullong curr_start = yet_to_be[k].first;
          ullong curr_end = yet_to_be[k].second;
          yet_to_be.pop_back();
          //52 50 48
          // 79 93
          //81 94 50 97

          if (curr_start > source_end || curr_end < source_start) {
            next.push_back({curr_start, curr_end});
          } else if (curr_start >= source_start && curr_end <= source_end) {
            mapped.push_back({map_sd(source_start, dest_start, curr_start),
                              map_sd(source_start, dest_start, curr_end)});
          } else if (curr_start >= source_start && curr_end > source_end) {
            mapped.push_back({map_sd(source_start, dest_start, curr_start),
                              map_sd(source_start, dest_start, source_end)});
            yet_to_be.push_back({source_end + 1, curr_end});
          } else if (curr_end <= source_end && curr_start < source_start) {
            mapped.push_back({map_sd(source_start, dest_start, source_start),
                              map_sd(source_start, dest_start, curr_end)});
            yet_to_be.push_back({curr_start, source_start - 1});
          }
        }
        for (std::pair<ullong, ullong> p : next) {
          yet_to_be.push_back(p);
        }
      }
      for (std::pair<ullong, ullong> p : mapped) {
        yet_to_be.push_back(p);
      }
      mapped.clear();
    }

    ullong curr_lowest = find_lowest(yet_to_be);
    std::cout << curr_lowest << std::endl;
    if (curr_lowest < lowest_location) {
      lowest_location = curr_lowest;
    }
  }
  std::cout << lowest_location << std::endl;

  return 0;
}

ullong find_lowest(std::vector<std::pair<ullong, ullong>> vec) {
  ullong lowest = ULLONG_MAX;
  for (std::pair<ullong, ullong> p : vec) {
    if (lowest > p.first) {
      lowest = p.first;
    }
  }
  return lowest;
}

ullong map_sd(ullong ss, ullong ds, ullong curr) { return (curr - ss) + ds; }

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
