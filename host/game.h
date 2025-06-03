#pragma once

#include "chessboard.h"
#include "coordinates_parser.h"
#include "drawer.h"

namespace chess {

class Game {
 public:
  Game();
  std::string processMove(const std::string&);
  std::string print() const;
 private:
  Drawer drawer_;
  Chessboard chessboard_;
  CoordinatesParser coordinates_parser_;

  size_t current_turn_;
  EColor current_color_;
}; // class Game


}; // namespace chess
