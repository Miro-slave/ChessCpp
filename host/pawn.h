#pragma once

#include "ipiece.h"

#include <algorithm>

namespace chess {

class Pawn : public IPiece {
 public:

  ~Pawn() override = default;

  IPiece* create_copy() const override {
    Pawn* copy = new Pawn();
    copy->setCoords(coordinates_);
    copy->setColor(color_);

    return copy;
  };

  int move(Coordinates dest, const PieceMap& pieces) const override {
    ChessboardMatrix possible_moves_matrix(8, std::vector<bool>(8, false));
    colorAttackFields(possible_moves_matrix, pieces);

    Coordinates move_forward = coordinates_;

    if (color_ == white) {
      ++move_forward.first;
    } else {
      --move_forward.first;
    }

    if (pieces.find(move_forward) == pieces.end()) {
      possible_moves_matrix[move_forward.first][move_forward.second] = true;

      if (coordinates_.first == 1 && color_ == white) {
        ++move_forward.first;

        if (pieces.find(move_forward) == pieces.end()) {
          possible_moves_matrix[move_forward.first][move_forward.second] = true; // double pawn move at start
        }
      } else if(coordinates_.first == 6 && color_ == black) {
        --move_forward.first;

        if (pieces.find(move_forward) == pieces.end()) {
          possible_moves_matrix[move_forward.first][move_forward.second] = true; // double pawn move at start
        }
      }
    }

    return possible_moves_matrix[dest.first][dest.second];
  }  // checks if move is valid

  char getAscii() const override {
    if (color_ == white) {
      return 'P';
    } else {
      return 'p';
    }
  };

  void colorAttackFields(ChessboardMatrix& matrix, const PieceMap& pieces) const override {
    std::vector<Coordinates> potential_fields;

    if (color_ == white) {
      potential_fields.push_back({coordinates_.first + 1, coordinates_.second + 1});
      potential_fields.push_back({coordinates_.first + 1, coordinates_.second - 1});
    } else {
      potential_fields.push_back({coordinates_.first - 1, coordinates_.second + 1});
      potential_fields.push_back({coordinates_.first - 1, coordinates_.second - 1});
    }

    for (const auto& field : potential_fields) {
      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7)) 
      {
        continue;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }
      }
    }

    return; 
  }
};  // class Pawn

};  // namespace chess
