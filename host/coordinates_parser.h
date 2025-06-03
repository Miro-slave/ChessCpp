#pragma once

#include "common.h"

#include <optional>
#include <string>

namespace chess {

class CoordinatesParser {
 public:
  std::optional<std::pair<Coordinates, Coordinates>> tryParse(const std::string& coordinates);
};  // class CoordinatesParser

};  // namespace chess
