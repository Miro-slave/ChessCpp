#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iostream>

namespace chess {

using Coordinates = std::pair<size_t, size_t>;

//bool operator==(const Coordinates& a, const Coordinates& b) {
//  return a.first == b.first && a.second == b.second;
//}

struct pairhash {
 public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

using ChessboardMatrix = std::vector<std::vector<bool>>;


enum EColor {
  white = 0,
  black
};

};  // namespace chess
