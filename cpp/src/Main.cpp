#include "CustomOStreams.h"
#include "NegamaxBot.cpp"
#include <iostream>
#include <memory>

int main() {
  auto b = std::make_unique<NegamaxBot>();
  Game game("");
  std::vector<bool> isBot = {false, false};

  while (true) {
    std::cout << game << std::endl;

    int x;
    std::cin >> x;

    if (x == 7) {
      std::cout << "Bot is thinking...\n";
      int botMove = b->getBestMove(game);
      game.play(botMove);
    } else {
      game.play(x);
    }
  }
}