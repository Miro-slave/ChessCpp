#pragma once

#include "common.h"

#include <unordered_map>
#include <memory>

namespace chess {

class PiecePtr;


using PieceMap = std::unordered_map<Coordinates, PiecePtr, pairhash>;

class IPiece {
 public:
  //IPiece() = default;
  //IPiece(const IPiece&) = default;
  //IPiece& operator=(const IPiece&) = default;
  virtual ~IPiece() = default;
  virtual IPiece* create_copy() const = 0;
  virtual int move(Coordinates, const PieceMap&) const = 0;  // move piece if possible
  virtual void colorAttackFields(ChessboardMatrix&, const PieceMap&) const = 0;

  EColor getColor() const { return color_; };
  virtual char getAscii() const { return '?'; };
  void setCoords(Coordinates coordinates) { coordinates_ = coordinates; };
  void setColor(EColor color) { 
    color_ = color; 
  };
  // bool operator==(const IPiece&) const noexcept = default;
 protected:
  Coordinates coordinates_;
  EColor color_;
}; // class IPiece


class PiecePtr {
 public:
  PiecePtr(IPiece* ptr) : ptr_(ptr) {};

  PiecePtr(const PiecePtr& other)
      : ptr_(other.ptr_->create_copy()) {};

  const IPiece& operator*() const { return *ptr_; };

  IPiece* operator->() { return ptr_.get(); };

  const IPiece* operator->() const { return ptr_.get(); };

  IPiece& operator*() { return *ptr_; };

  bool operator==(const PiecePtr&) const noexcept = default;

 private:
  std::unique_ptr<IPiece> ptr_;
}; // class PiecePtr


};  // namespace chess
