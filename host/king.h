#pragma once

#include "ipiece.h"

namespace chess {

class King : public IPiece {
 public:

  ~King() override = default;

  IPiece* create_copy() const override {
    King* copy = new King();
    copy->setCoords(coordinates_);
    copy->setColor(color_);

    return copy;
  };

  int move(Coordinates dest, const PieceMap& pieces) const override {
    ChessboardMatrix possible_moves_matrix(8, std::vector<bool>(8, false));
    colorAttackFields(possible_moves_matrix, pieces);

    if (color_ == white && coordinates_ == Coordinates{0,4}) { 
      if (pieces.find({0, 5}) == pieces.end() && // short castling, whites
          pieces.find({0, 6}) == pieces.end() &&
          pieces.find({0, 7}) != pieces.end())
      {
        possible_moves_matrix[0][6] = true;
      } else if (pieces.find({0, 3}) == pieces.end() && // long castling, whites
          pieces.find({0, 2}) == pieces.end() &&
          pieces.find({0, 1}) == pieces.end() &&
          pieces.find({0, 0}) != pieces.end()) 
      {
        possible_moves_matrix[0][2] = true;
      }
    } else if (color_ == black && coordinates_ == Coordinates{7, 4}) {
      if (pieces.find({7, 5}) == pieces.end() && // short castling, black
          pieces.find({7, 6}) == pieces.end() &&
          pieces.find({7, 7}) != pieces.end())
      {
        possible_moves_matrix[7][6] = true;
      } else if (pieces.find({7, 3}) == pieces.end() && // long castling, black
          pieces.find({7, 2}) == pieces.end() &&
          pieces.find({7, 1}) == pieces.end() &&
          pieces.find({7, 0}) != pieces.end()) 
      {
        possible_moves_matrix[7][2] = true;
      }
    }

    return possible_moves_matrix[dest.first][dest.second];
  }  // checks if move is valid

  char getAscii() const override {
    if (color_ == white) {
      return 'K';
    } else {
      return 'k';
    }
  };

  void colorAttackFields(ChessboardMatrix& matrix, const PieceMap& pieces) const override {
    std::vector<Coordinates> potential_fields;

    potential_fields.push_back({coordinates_.first + 1, coordinates_.second + 1});
    potential_fields.push_back({coordinates_.first + 1, coordinates_.second - 1});
    potential_fields.push_back({coordinates_.first + 1, coordinates_.second});
    potential_fields.push_back({coordinates_.first, coordinates_.second + 1});
    potential_fields.push_back({coordinates_.first, coordinates_.second - 1});
    potential_fields.push_back({coordinates_.first - 1, coordinates_.second + 1});
    potential_fields.push_back({coordinates_.first - 1, coordinates_.second - 1});
    potential_fields.push_back({coordinates_.first - 1, coordinates_.second});

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
};  // class King

};  // namespace chess
