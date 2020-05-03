//
// Created by Chirag Gupta on 4/26/20.
//
#include "fruit_grabber/engine.h"

void Engine::Reset() {
  score_ = 0;
  fruits_ = {};
  gameState = GameState::kPaused;
}

Engine::Engine(size_t width, size_t height)
    : width_{width},
      height_{height},
      container_{},
      score_{1},
      gameState(GameState::kPaused)
      {
  Reset();
}

void Engine::Step() {
  // Makes a new fruit randomly
  if (std::rand() % 15 == 0) {
    fruits_.push_back(*(new Fruit(GetRandomLocation(),
        std::rand() % 4)));
  }

  for (Fruit& fruit : fruits_) {
    for (int i = 0; i < container_.size();i++) {
      // If fruit is caught
      if (fruit.is_visible_ && fruit.GetLocation() == container_.at(i)) {
        fruit.is_visible_ = false;
        score_++;
        break;
      }
    }

    // If fruit reaches the bottom
    if (fruit.GetLocation().Col() >= height_ && fruit.is_visible_) {
      gameState = GameState::kGameOver;
    } else if (fruit.is_visible_){
      fruit.Step();
    }
  }
}

int Engine::GetScore() const { return score_; }

Location Engine::GetRandomLocation() {
  Location final_location(0, 0);

  for (size_t col = 0; col < width_; ++col) {
    Location loc( col, 0);
    if (std::rand() % 400 == 0) {
      final_location = loc;
    }
  }
  return final_location;
}

void Engine::Draw() {
  for (Fruit& fruit : fruits_) {
    if (fruit.is_visible_) {
      fruit.Draw();
    }
  }
}

Engine::GameState Engine::getGameState() const { return gameState; }

void Engine::setGameState(Engine::GameState gameState) {
  Engine::gameState = gameState;
}

void Engine::setContainer(const std::vector<Location>& container) {
  container_ = container;
}
