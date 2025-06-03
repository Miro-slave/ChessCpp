#pragma once

#include "ipiece.h"

namespace chess {

class Queen : public IPiece {
 public:

  ~Queen() override = default;

  IPiece* create_copy() const override {
    Queen* copy = new Queen();
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
      return 'Q';
    } else {
      return 'q';
    }
  };

  void colorAttackFields(ChessboardMatrix& matrix, const PieceMap& pieces) const override {
    std::vector<Coordinates> potential_fields;

    Coordinates field;

    // diagonal
    for (size_t i = 1; i < 8; i++) {
      field = {coordinates_.first + i, coordinates_.second + i};

      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7)) 
      {
        break;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }

        break;
      }

      matrix[field.first][field.second] = true;
    }

    for (size_t i = 1; i < 8; i++) {
      field = {coordinates_.first + i, coordinates_.second - i};

      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7)) 
      {
        break;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }

        break;
      }

      matrix[field.first][field.second] = true;
    }

    for (size_t i = 1; i < 8; i++) {
      field = {coordinates_.first - i, coordinates_.second + i};

      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7)) 
      {
        break;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }

        break;
      }

      matrix[field.first][field.second] = true;
    }

    for (size_t i = 1; i < 8; i++) {
      field = {coordinates_.first - i, coordinates_.second - i};

      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7))
      {
        break;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }

        break;
      }

      matrix[field.first][field.second] = true;
    }

    // horizontal
    for (size_t i = 1; i < 8; i++) {
      field = {coordinates_.first, coordinates_.second + i};

      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7))
      {
        break;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }

        break;
      }

      matrix[field.first][field.second] = true;
    }

    for (size_t i = 1; i < 8; i++) {
      field = {coordinates_.first, coordinates_.second - i};

      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7)) {
        break;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }

        break;
      }

      matrix[field.first][field.second] = true;
    }

    // vertical
    for (size_t i = 1; i < 8; i++) {
      field = {coordinates_.first + i, coordinates_.second};

      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7)) {
        break;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }

        break;
      }

      matrix[field.first][field.second] = true;
    }

    for (size_t i = 1; i < 8; i++) {
      field = {coordinates_.first - i, coordinates_.second};

      if (field.first != std::clamp(field.first, (size_t)0, (size_t)7) ||
          field.second != std::clamp(field.second, (size_t)0, (size_t)7)) {
        break;
      }

      if (pieces.find(field) != pieces.end()) {
        EColor piece_color = pieces.at(field)->getColor();

        if (color_ != piece_color) {
          matrix[field.first][field.second] = true;
        }

        break;
      }

      matrix[field.first][field.second] = true;
    }

    return;
  }
};  // class Queen

};  // namespace chess
