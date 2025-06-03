#include "game.h"

#include "bishop.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"

#include <iostream>

namespace chess {

Game::Game()
	: chessboard_(
		{{{0, 0}, PiecePtr(new Rook())}, {{1, 0}, PiecePtr(new Pawn())},
         {{0, 1}, PiecePtr(new Knight())}, {{1, 1}, PiecePtr(new Pawn())},
         {{0, 2}, PiecePtr(new Bishop())}, {{1, 2}, PiecePtr(new Pawn())},
		 {{0, 3}, PiecePtr(new Queen())}, {{1, 3}, PiecePtr(new Pawn())},
         {{0, 4}, PiecePtr(new King())}, {{1, 4}, PiecePtr(new Pawn())},
         {{0, 5}, PiecePtr(new Bishop())}, {{1, 5}, PiecePtr(new Pawn())},
		 {{0, 6}, PiecePtr(new Knight())}, {{1, 6}, PiecePtr(new Pawn())},
         {{0, 7}, PiecePtr(new Rook())}, {{1, 7}, PiecePtr(new Pawn())},

		 {{7, 0}, PiecePtr(new Rook())}, {{6, 0}, PiecePtr(new Pawn())},
         {{7, 1}, PiecePtr(new Knight())}, {{6, 1}, PiecePtr(new Pawn())},
         {{7, 2}, PiecePtr(new Bishop())}, {{6, 2}, PiecePtr(new Pawn())},
		 {{7, 3}, PiecePtr(new Queen())}, {{6, 3}, PiecePtr(new Pawn())},
         {{7, 4}, PiecePtr(new King())}, {{6, 4}, PiecePtr(new Pawn())},
         {{7, 5}, PiecePtr(new Bishop())}, {{6, 5}, PiecePtr(new Pawn())},
		 {{7, 6}, PiecePtr(new Knight())}, {{6, 6}, PiecePtr(new Pawn())},
         {{7, 7}, PiecePtr(new Rook())}, {{6, 7}, PiecePtr(new Pawn())},
		}
	), current_turn_(1), current_color_(white) 
{}

std::string Game::processMove(const std::string& move) {
  auto parse_res = coordinates_parser_.tryParse(move);

  if (!parse_res.has_value()) {
    return "invalid input\n";
  }

  Coordinates start = parse_res.value().first;
  Coordinates dest = parse_res.value().second;

  if (start == dest) {
    return "invalid move\n";
  } 

  auto get_color_res = chessboard_.tryGetColor(start);

  if (!get_color_res.has_value()) {
    return "invalid piece color\n";
  } else if (get_color_res.value() != current_color_) {
    return "you cannot move enemy's pieces\n";
  }

  if (!chessboard_.tryMove(start, dest)) {
    return "inconsistent move\n";
  }

  ++current_turn_;

  if (current_color_ == white) {
    current_color_ = black;
  } else {
    current_color_ = white;
  }

  return "move proceed successfully";
}

std::string Game::print() const {
  return drawer_.draw(chessboard_.getPieces());
}

};  // namespace chess
