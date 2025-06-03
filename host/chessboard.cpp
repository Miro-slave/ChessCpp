#include "chessboard.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

#include <typeinfo>
#include <iostream>

namespace chess {

Chessboard::Chessboard(PieceMap pieces)
    : pieces_(pieces)
{
  for (auto& [coords, piece] : pieces_) {
    pieces_.at(coords)->setCoords(coords);

    if (coords.first < 2) {
      pieces_.at(coords)->setColor(white);
    } else {
      pieces_.at(coords)->setColor(black);
    }

    // std::cout << "***** " << pieces_.at(coords)->getColor() << '\n';
  }
}

int Chessboard::tryMove(Coordinates start, Coordinates dest) {
  if (!moveIsValid(start, dest)) {
    return 0;
  }

  PiecePtr& piece_ptr = pieces_.at(start);

  PieceMap temp_pieces = pieces_;

  temp_pieces.erase(start);
  temp_pieces.erase(dest);
  temp_pieces.insert(std::make_pair(dest, piece_ptr));

  EColor piece_color = piece_ptr->getColor();
  EColor enemy_color = (piece_color == white ? black : white);

  ChessboardMatrix attack_matrix = getAttackMatrix(temp_pieces, enemy_color);

  auto same_color_king_coords = tryFindKing(piece_color);
  auto enemy_king_coords = tryFindKing(enemy_color);

  if (!same_color_king_coords.has_value()) {
    std::clog << "cannot find current player's king\n";

    return 0;
  }

  if (!enemy_king_coords.has_value()) {
    std::clog << "cannot find current player's enemy king\n";

    return 0;
  }

  size_t king_coords_diff_height = std::max(same_color_king_coords.value().first, enemy_king_coords.value().first) -
                              std::min(same_color_king_coords.value().first, enemy_king_coords.value().first);

  size_t king_coords_diff_length = std::max(same_color_king_coords.value().second, enemy_king_coords.value().second) -
                              std::min(same_color_king_coords.value().second, enemy_king_coords.value().second);

  size_t total_diff = king_coords_diff_height + king_coords_diff_length;

  if (total_diff <= 2 && std::max(king_coords_diff_height, king_coords_diff_length) < 2) {
    std::clog << "there might be distance between kings\n";

    return 0;
  }

  if (isUnderAttack(attack_matrix, same_color_king_coords.value())) {
    std::clog << "king is under attack\n";

    return 0;
  }

  size_t move_coords_diff_length = std::max(start.second, dest.second) - std::min(start.second, dest.second);

  if (typeid(*piece_ptr) == typeid(Pawn)) { // pawn might became a queen
    std::unique_ptr<IPiece> new_queen(new Queen());
    new_queen->setColor(piece_color);

    if (piece_color == white && dest.first == 7) {
      temp_pieces.erase(dest);
      temp_pieces.insert(std::make_pair(dest, PiecePtr(new_queen.release())));
    } else if (piece_color == black && dest.first == 0) {
      temp_pieces.erase(dest);
      temp_pieces.insert(std::make_pair(dest, PiecePtr(new_queen.release())));
    }
  } else if (typeid(*piece_ptr) == typeid(King) && move_coords_diff_length == 2) { // castling check
    if (dest.second > start.second) { // short castling
      if (typeid(*pieces_.at({dest.first, 7})) == typeid(Rook)) {
        Coordinates old_rook_pos = {dest.first, 7};
        Coordinates new_rook_pos = {dest.first, 5};
        temp_pieces.insert(std::make_pair(new_rook_pos, pieces_.at(old_rook_pos)));
        temp_pieces.erase(old_rook_pos);
        temp_pieces.at(new_rook_pos)->setCoords(new_rook_pos);
      }
    } else { // long castling
      if (typeid(*pieces_.at({dest.first, 0})) == typeid(Rook)) {
        Coordinates old_rook_pos = {dest.first, 0};
        Coordinates new_rook_pos = {dest.first, 3};
        temp_pieces.insert(std::make_pair(new_rook_pos, pieces_.at(old_rook_pos)));
        temp_pieces.erase(old_rook_pos);
        temp_pieces.at(new_rook_pos)->setCoords(new_rook_pos);
      }
    }
  }

  pieces_ = std::move(temp_pieces);

  pieces_.at(dest)->setCoords(dest);

  return 1;
}

bool Chessboard::moveIsValid(Coordinates start, Coordinates dest) const {
  auto piece_iter = pieces_.find(start);

  if (piece_iter == pieces_.end()) {
    return false;
  }

  const PiecePtr& piece_ptr = piece_iter->second;

  auto other_piece_iter = pieces_.find(dest);

  if (other_piece_iter == pieces_.end()) {
    int move_res = piece_ptr->move(dest, pieces_);

    if (!move_res) {
      return false;
    }
  } else {
    const PiecePtr& other_piece_ptr = other_piece_iter->second;

    if (piece_ptr->getColor() == other_piece_ptr->getColor() ||
        typeid(other_piece_ptr) == typeid(King)) {
      return false;
    }
  }

  return true;
}

std::optional<EColor> Chessboard::tryGetColor(Coordinates coordinates) const {
  if (pieces_.find(coordinates) != pieces_.end()) {
    return {pieces_.at(coordinates)->getColor()};
  }

  return {};
}

const PieceMap& Chessboard::getPieces() const {
  return pieces_;
}

ChessboardMatrix Chessboard::getAttackMatrix(const PieceMap& pieces, EColor color) const {
  ChessboardMatrix chessboard_matrix(8, std::vector<bool>(8, false));

  for (const auto& [coords, piece] : pieces) {
    if (piece->getColor() == color) {
      piece->colorAttackFields(chessboard_matrix, pieces_);
    }
  }

  return chessboard_matrix;
}

bool Chessboard::isUnderAttack(const ChessboardMatrix& matrix, Coordinates coordinates) const {
  return matrix[coordinates.first][coordinates.second];
}

std::optional<Coordinates> Chessboard::tryFindKing(EColor color) const {
  for (const auto& [coordinates, piece] : pieces_) {
    if (typeid(*piece) == typeid(King) && color == piece->getColor()) {
      return { coordinates };
    }
  }

  return {};
}

};  // namespace chess
