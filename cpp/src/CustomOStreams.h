#include "Game.cpp"
#include <fstream>
#include <iostream>

namespace std {
template <typename T> ostream &operator<<(ostream &wrapped, const std::vector<T> &item) {
  const std::string open = "{", close = "}", sep = ",", empty = "";
  wrapped << open;
  bool first = true;
  for (auto const &element : item) {
    wrapped << (!first ? sep : empty) << element;
    first = false;
  }
  return wrapped << close;
}

ostream &operator<<(ostream &wrapped, const Game &game) {
  wrapped << "State:\n";
  wrapped << game.toString() << std::endl;

  wrapped << "Move Count: " << game.getNumMoves() << "\n";
  return wrapped;
}

} // namespace std