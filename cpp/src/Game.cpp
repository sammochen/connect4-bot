#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <bit>

class Game {
public:
  static const int WIDTH = 7;
  static const int HEIGHT = 6;
  static const int MIN_SCORE = -(WIDTH * HEIGHT) / 2 + 3;
  static const int MAX_SCORE = (WIDTH * HEIGHT + 1) / 2 - 3;

  Game(std::string sequence) : numMoves(0), playerMask(0), allMask(0) {
    playSequence(sequence);
  }

  /**
   * Plays one tile in column
   */
  void play(const int &col) {
    playerMask ^= allMask;                        // the perspective changes
    allMask |= allMask + bottom_column_mask(col); // adds 1 to the mask
    numMoves++;                                   // increment
  }

  /**
   * Plays the sequence
   */
  void playSequence(const std::string &sequence) {
    for (const auto &c : sequence) {
      play(c - '1');
    }
  }

  /**
   * Indicates whether a column is playable.
   * @param col: 0-based index of column to play
   * @return true if the column is playable, false if the column is already
   * full.
   */
  bool canPlay(const int &col) const {
    // Checks AND between allMask and the top of the column
    return (allMask & top_column_mask(col)) == 0;
  }

  int getNumMoves() const {
    return numMoves;
  }

  bool canWinNext() const {
    return winning_position() & possible();
  }

  uint64_t getHash() const {
    return playerMask + allMask;
  }

  int moveScore(uint64_t moveMask) const {
    const uint64_t winningPositions = compute_winning_position(playerMask | moveMask, allMask);
    return __builtin_popcountll(winningPositions);
  }

  /**
   * Return a
   */
  uint64_t possibleNonLosingPositions() const {
    assert(!canWinNext());
    // possible_mask is what you can play
    // opponent_win is what the opponent can play to win
    // forced moves are the possible positions you have to play, because
    // otherwise the opponent can play it

    uint64_t possible_mask = possible();
    uint64_t opponent_win = opponent_winning_position();

    uint64_t forced_moves = possible_mask & opponent_win;

    // if there are forced moves,
    if (forced_moves) {
      // if there are multiple forced moves, return 0 as you cannot stop them
      if (forced_moves & (forced_moves - 1))
        return 0;
      // otherwise, what is "possible" is the move you have to play
      else
        possible_mask = forced_moves;
    }
    // Play what you can, that does not give the opponent an immediate win after
    const uint64_t nonLosingPositions = possible_mask & ~(opponent_win >> 1);
    return nonLosingPositions;

    // uint64_t nonLosingColumns = 0;
    // for (int col = 0; col < WIDTH; col++) {
    //   if (column_mask(col) & nonLosingPositions) {
    //     nonLosingColumns |= (1LL << col);
    //   }
    // }
    // return nonLosingColumns;
  }

  // Return a bitmask 1 on all the cells of a given col
  static constexpr uint64_t column_mask(int col) {
    return ((UINT64_C(1) << HEIGHT) - 1) << col * (HEIGHT + 1);
  }

  std::string toString() const {
    std::string s;
    for (int row = 0; row < HEIGHT; row++) {
      for (int col = 0; col < WIDTH; col++) {
        int pos = HEIGHT - row - 1 + col * (HEIGHT + 1);
        uint64_t bit = (1LL << pos);

        if (bit & allMask) {
          if (bit & playerMask) {
            s.push_back(numMoves % 2 ? 'O' : 'X');
          } else {
            s.push_back(numMoves % 2 ? 'X' : 'O');
          }
        } else {
          s.push_back('-');
        }
      }
      s.push_back('\n');
    }
    return s;
  }

private:
  /**
   * Mask. 1 if the current player has a tile there.
   */
  uint64_t playerMask;
  /**
   * mask. 1 if some player has a tile there.
   */
  uint64_t allMask;
  /**
   * The number of total moves played.
   */
  int numMoves;

  /**
   * Indicates whether the current player wins by playing a given column.
   * This function should never be called on a non-playable column.
   * @param col: 0-based index of a playable column.
   * @return true if current player makes an alignment by playing the
   * corresponding column col.
   */
  bool isWinningMove(const int &col) const {
    // winning_position gives you all 1s in cells where you could win
    // possible gives you 1s where you could play
    // column_mask gives you 1s in that column
    return winning_position() & possible() & column_mask(col);
  }

  /**
   * Return a bitmask of the possible winning positions for the current player
   */
  uint64_t winning_position() const {
    return compute_winning_position(playerMask, allMask);
  }

  /**
   * Return a bitmask of the possible winning positions for the opponent
   */
  uint64_t opponent_winning_position() const {
    return compute_winning_position(playerMask ^ allMask, allMask);
  }

  /**
   * allMask + bottom_row makes
   *
   * 0000     1000
   * 1000  -> 0010
   * 1010     0101
   * 1111     0000
   *
   * ANDing that against board_mask gives you 1s where you can place
   */
  uint64_t possible() const {
    return (allMask + bottom_row_mask()) & board_mask();
  }

  /**
   * Given some position (playerMask) and mask (allMask),
   * Returns 1 at mask if they can win by having a tile there.
   */
  static uint64_t compute_winning_position(uint64_t position, uint64_t mask) {
    // vertical
    uint64_t r = (position << 1) & (position << 2) & (position << 3);

    // horizontal
    uint64_t p = (position << (HEIGHT + 1)) & (position << 2 * (HEIGHT + 1));
    r |= p & (position << 3 * (HEIGHT + 1));
    r |= p & (position >> (HEIGHT + 1));
    p = (position >> (HEIGHT + 1)) & (position >> 2 * (HEIGHT + 1));
    r |= p & (position << (HEIGHT + 1));
    r |= p & (position >> 3 * (HEIGHT + 1));

    // diagonal 1
    p = (position << HEIGHT) & (position << 2 * HEIGHT);
    r |= p & (position << 3 * HEIGHT);
    r |= p & (position >> HEIGHT);
    p = (position >> HEIGHT) & (position >> 2 * HEIGHT);
    r |= p & (position << HEIGHT);
    r |= p & (position >> 3 * HEIGHT);

    // diagonal 2
    p = (position << (HEIGHT + 2)) & (position << 2 * (HEIGHT + 2));
    r |= p & (position << 3 * (HEIGHT + 2));
    r |= p & (position >> (HEIGHT + 2));
    p = (position >> (HEIGHT + 2)) & (position >> 2 * (HEIGHT + 2));
    r |= p & (position << (HEIGHT + 2));
    r |= p & (position >> 3 * (HEIGHT + 2));

    return r & (board_mask() ^ mask);
  }

  /**
   * Returns a bitmask 1 on the bottom row
   */
  static uint64_t bottom_row_mask() {
    uint64_t res = 0;
    for (int col = 0; col < WIDTH; col++) {
      res |= bottom_column_mask(col);
    }
    return res;
  }

  /**
   * Returns a bitmask full of 1s for the HEIGHT*WIDTH grid
   */
  static uint64_t board_mask() {
    return bottom_row_mask() * ((1LL << HEIGHT) - 1);
  }

  // Return a bitmask containing a single 1 at the top cell of col
  static constexpr uint64_t top_column_mask(int col) {
    return UINT64_C(1) << ((HEIGHT - 1) + col * (HEIGHT + 1));
  }

  // Return a bitmask containing a single 1 at the bottom cell of col
  static constexpr uint64_t bottom_column_mask(int col) {
    return UINT64_C(1) << col * (HEIGHT + 1);
  }
};

#ifndef DEBUG
#include "nbind/nbind.h"

NBIND_CLASS(Game) {
  construct<std::string>();
  method(play);
}
#endif