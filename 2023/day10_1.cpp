#include <iostream>
#include <unordered_map>
#include <vector>

char next_step(char c, char direction);

int main(int argc, char **argv) {
  std::vector<std::string> map;
  std::pair<uint, uint> start;

  std::string line;
  while (getline(std::cin, line)) {
    map.push_back(line);
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == 'S') {
        start = std::make_pair(i, map.size() - 1);
      }
    }
  }

  uint result = 0;

  std::unordered_map<char, std::pair<uint, uint>> directions = {
      {'s', {0, 1}}, {'e', {1, 0}}, {'n', {0, -1}}, {'w', {-1, 0}}};
  char curr_direction;
  int found = -1;

  for (std::pair<char, std::pair<uint, uint>> direction : directions) {
    uint curr_x = start.first + direction.second.first;
    uint curr_y = start.second + direction.second.second;
    if (curr_x >= map[0].size() || curr_y >= map.size() || curr_x < 0 ||
        curr_y < 0)
      continue;
    curr_direction = direction.first;
    uint step = 0;

    while (1) {
      char curr_char = map[curr_y][curr_x];
      if (curr_char == '.')
        break;

      if (curr_char == 'S') {
        found = step;
        break;
      }

      char next = next_step(curr_char, curr_direction);
      if (next == 'b')
        break;

      curr_direction = next;

      map[curr_y][curr_x] = next;
      curr_x += directions[next].first;
      curr_y += directions[next].second;
      step++;
      if (curr_x >= map[0].size() || curr_y >= map.size() || curr_x < 0 ||
          curr_y < 0)
        break;
    }
    if (found != -1)
      break;
  }
  result = found / 2;
  result++;

  std::cout << result << std::endl;
  return 0;
}

char next_step(char c, char direction) {
  switch (c) {
  case '-':
    switch (direction) {
    case 'w':
    case 'e':
      return direction;
    }

  case '|':
    switch (direction) {
    case 'n':
    case 's':
      return direction;
    }

  case 'F':
    switch (direction) {
    case 'w':
      return 's';
    case 'n':
      return 'e';
    }

  case 'J':
    switch (direction) {
    case 's':
      return 'w';
    case 'e':
      return 'n';
    }
  case 'L':
    switch (direction) {
    case 's':
      return 'e';
    case 'w':
      return 'n';
    }
  case '7':
    switch (direction) {
    case 'e':
      return 's';
    case 'n':
      return 'w';
    }
  }
  return 'b';
}
