#include "drawer.h"

#include <iostream>
#include <sstream>

namespace chess {

std::string Drawer::draw(const PieceMap& pieces) const {
  std::vector<std::vector<char>> art(11, std::vector<char>(11, ' '));

  for (size_t i = 0; i < 10; i++) {
    art[i][0] = '|';
    art[i][9] = '|';

    if (i == std::clamp(i, (size_t)1, (size_t)8)) {
      art[i][10] = '0' + i;
    }
  }

  for (size_t i = 0; i < 10; i++) {
    art[0][i] = '-';
    art[9][i] = '-';

    if (i == std::clamp(i, (size_t)1, (size_t)8)) {
      art[10][i] = 'A' + i - 1;
    }
  }

  art[0][0] = '>';
  art[0][9] = '<';
  art[9][0] = '>';
  art[9][9] = '<';

  for (size_t i = 1; i < 9; i++) {
    for (size_t j = 1; j < 9; j++) {
      if (((i - 1) * 8 + (j - 1) + i) % 2 == 0) {
        art[i][j] = '#';
      }
    }
  }

  for (const auto& [coords, piece] : pieces) {
    art[coords.first + 1][coords.second + 1] = piece->getAscii();
  }

  std::stringstream sstream;

  std::reverse(art.begin(), art.end());

  for (const auto& line : art) {
    sstream << std::string(line.begin(), line.end()) << '\n';
  }

  sstream << std::string(art[0].begin(), art[0].end()) << "\n\n";

  std::string str = sstream.str();
  std::reverse(str.begin(), str.end());

  return sstream.str();
}

};  // namespace chess
