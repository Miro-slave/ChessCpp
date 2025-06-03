#pragma once

#include "ipiece.h"

#include <vector>
#include <string>
#include <optional>

namespace chess {

class Drawer {
 public:
  std::string draw(const PieceMap&) const;
};  // class Drawer

};  // namespace chess
