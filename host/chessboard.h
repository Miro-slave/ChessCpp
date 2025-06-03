#pragma once

#include "common.h"
#include "ipiece.h"

#include <optional>
#include <unordered_map>
#include <array>

namespace chess {

class Chessboard {
 public:
  Chessboard(PieceMap);
  int tryMove(Coordinates, Coordinates);
  std::optional<EColor> tryGetColor(Coordinates) const;
  const PieceMap& getPieces() const;
 private:
  ChessboardMatrix getAttackMatrix(const PieceMap&, EColor) const;
  bool isUnderAttack(const ChessboardMatrix&, Coordinates) const;
  std::optional<Coordinates> tryFindKing(EColor) const;
  bool moveIsValid(Coordinates, Coordinates) const;

  PieceMap pieces_;
};  // class Chessboard

};  // namespace chess
