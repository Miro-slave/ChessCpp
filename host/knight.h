#pragma once

#include "ipiece.h"

namespace chess {

class Knight : public IPiece {
 public:

  ~Knight() override = default;

  IPiece* create_copy() const override { 
    Knight* copy = new Knight();
    copy->setCoords(coordinates_);
    copy->setColor(color_);

    return copy;
  };

  int move(Coordinates dest, const PieceMap& pieces) const override { 
    ChessboardMatrix possible_moves_matrix(8, std::vector<bool>(8, false));
    colorAttackFields(possible_moves_matrix, pieces);

    return possible_moves_matrix[dest.first][dest.second]; 
  }  // checks if move is valid

  char getAscii() const override {
    if (color_ == white) {
      return 'N';
    } else {
      return 'n';
    }
  };

  void colorAttackFields(ChessboardMatrix& matrix, const PieceMap& pieces) const override {
    std::vector<Coordinates> potential_fields;

    potential_fields.push_back({coordinates_.first + 2, coordinates_.second + 1});
    potential_fields.push_back({coordinates_.first + 2, coordinates_.second - 1});
    potential_fields.push_back({coordinates_.first + 1, coordinates_.second + 2});
    potential_fields.push_back({coordinates_.first + 1, coordinates_.second - 2});
    potential_fields.push_back({coordinates_.first - 1, coordinates_.second + 2});
    potential_fields.push_back({coordinates_.first - 1, coordinates_.second - 2});
    potential_fields.push_back({coordinates_.first - 2, coordinates_.second + 1});
    potential_fields.push_back({coordinates_.first - 2, coordinates_.second - 1});

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
      } else {
        matrix[field.first][field.second] = true;
      }
    }

    return; 
  }
};  // class Knight

};  // namespace chess
