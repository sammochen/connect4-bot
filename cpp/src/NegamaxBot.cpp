#pragma once

#include "Game.cpp"
#include "TranspositionTable.cpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>

class NegamaxBot {
public:
  NegamaxBot() : table() {}

  int getBestMove(const Game &game) {
    assert(game.getNumMoves() < Game::HEIGHT * Game::WIDTH);

    // I need to choose the worst score for the opponent!
    int worstScore = 255;

    std::vector<int> worstMoves = {};
    for (int col = 0; col < Game::WIDTH; col++) {
      if (game.canPlay(col)) {
        Game nextGame = game;
        nextGame.play(col);
        int score = solve(nextGame);

        if (score < worstScore) {
          worstScore = score;
          worstMoves = {col};
        } else if (score == worstScore) {
          worstMoves.push_back(col);
        }
      }
    }
    assert(worstScore != 255);
    assert(worstMoves.size() != 0);

    std::cout << "worst moves:";

    for (int move : worstMoves) {
      std::cout << ' ' << move;
    }
    std::cout << std::endl;
    return worstMoves[0]; // TODO randomise
  }

  int solve(const Game &game) {
    int min = -(Game::WIDTH * Game::HEIGHT - game.getNumMoves()) / 2;
    int max = (Game::WIDTH * Game::HEIGHT + 1 - game.getNumMoves()) / 2;
    while (min < max) {
      int med = min + (max - min) / 2;
      if (med <= 0 && min / 2 < med) {
        med = min / 2;
      } else if (med >= 0 && max / 2 > med) {
        med = max / 2;
      }
      int r = negamax(game, med, med + 1);
      if (r <= med) {
        max = r;
      } else {
        min = r;
      }
    }
    return min;
  }

  // Returns everything within alpha and beta score
  int negamax(const Game &game, int alpha = -100, int beta = 100) {
    assert(alpha < beta);
    if (game.canWinNext()) {
      return (Game::WIDTH * Game::HEIGHT - 1 - game.getNumMoves()) / 2;
    }

    uint64_t nextPositions = game.possibleNonLosingPositions();

    if (nextPositions == 0) {
      // TODO to understand
      return -(Game::WIDTH * Game::HEIGHT - game.getNumMoves()) / 2;
    }

    // TODO to understand
    if (game.getNumMoves() >= Game::WIDTH * Game::HEIGHT - 2) {
      return 0;
    }

    // lower bound of score as opponent cannot win next move
    int min = -(Game::WIDTH * Game::HEIGHT - 2 - game.getNumMoves()) / 2;
    if (alpha < min) {
      // there is no need to keep beta above our max possible score.
      alpha = min;
      // prune the exploration if the [alpha;beta] window is empty.
      if (alpha >= beta) {
        return alpha;
      }
    }

    // upper bound of our score as we cannot win immediately
    int max = (Game::WIDTH * Game::HEIGHT - 1 - game.getNumMoves()) / 2;
    if (int val = table.get(game.getHash())) {
      max = val + Game::MIN_SCORE - 1;
    }
    if (beta > max) {
      // there is no need to keep beta above our max possible score.
      beta = max;
      // prune the exploration if the [alpha;beta] window is empty.
      if (alpha >= beta)
        return beta;
    }

    int bestScore = -Game::WIDTH * Game::HEIGHT;

    std::vector<std::pair<int, int>> nextCols; // returns the col, and score
    for (int col = 0; col < Game::WIDTH; col++) {
      const uint64_t nextPosition = nextPositions & Game::column_mask(col);
      if (nextPosition) {
        nextCols.push_back({col, game.moveScore(nextPosition)});
      }
    }
    std::sort(nextCols.begin(), nextCols.end(),
              [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
                return a.second == b.second
                           ? std::abs(Game::WIDTH / 2 - a.first) <
                                 std::abs(Game::WIDTH / 2 - b.first)
                           : a.second > b.second;
              });

    for (const auto &nextCol : nextCols) {
      Game nextGame = game; // makes a copy
      nextGame.play(nextCol.first);

      int nextGameScore = -negamax(nextGame, -beta, -alpha);

      if (nextGameScore >= beta) {
        return nextGameScore;
      }
      if (nextGameScore > alpha) {
        alpha = nextGameScore; // increase the lower bound
      }
    }

    table.put(game.getHash(), alpha - Game::MIN_SCORE + 1);
    return alpha;
  }

  TranspositionTable table;
};

#ifndef DEBUG
#include "nbind/nbind.h"

NBIND_CLASS(NegamaxBot) {
  construct<>();
  method(getBestMove);
}
#endif