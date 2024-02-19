#include <cmath>
#include <cstdint>
#include <iostream>
#include <regex>

double parse_digit(std::string line);

double calculate_distance(uint16_t total_time, uint16_t loading_time);
std::pair<double, double> min_max_points(double b, double c);

int main(int argc, char **argv) {
  uint64_t result;

  std::string line;

  getline(std::cin, line);
  double duration = parse_digit(line);

  getline(std::cin, line);
  double distance = parse_digit(line);

  std::pair<double, double> min_max = min_max_points(duration, distance);

  result = (min_max.second - min_max.first + 1);

  std::cout << result << std::endl;
  return 0;
}

// y = 42x - x^2
std::pair<double, double> min_max_points(double total_duration,
                                         double distance_record) {
  double a = -1;
  double b = total_duration * -1;
  double c = distance_record;
  double determinant = sqrt((b * b) - (4 * c));
  double x1 = ((-1 * b) - determinant) / (2);
  double x2 = ((-1 * b) + determinant) / (2);

  double c_x1 = ceil(x1);
  double f_x2 = floor(x2);
  return {c_x1 == x1 ? x1 + 1 : c_x1, (f_x2 == x2) ? x2 - 1 : f_x2};
}
double calculate_distance(uint16_t total_time, uint16_t loading_time) {
  return (total_time * loading_time) - (loading_time * loading_time);
}
// parse all digits in a line into vector using
double parse_digit(std::string line) {
  double digit;
  std::string d = "";

  std::regex digit_regex(R"(\d+)");

  for (std::smatch match; std::regex_search(line, match, digit_regex);) {
    d += match[0];
    line = match.suffix();
  }

  digit = std::stod(d);
  return digit;
}
