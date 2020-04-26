//
// Created by Chirag Gupta on 4/26/20.
//

#include "fruit_grabber/engine.h"

void Engine::Reset() {
  score_ = 1;
  fruits_ = {};
  is_game_over = false;
}

Engine::Engine(size_t width, size_t height)
    : width_{width},
      height_{height},
      container_(0,0),
      score_{1},
      is_game_over{false}
      {
  Reset();
}

void Engine::Step() {
  if (std::rand() % 4 == 0) {
    fruits_.push_back(*(new Fruit(GetRandomLocation(),
        std::rand() % 4)));
  }
  for (Fruit& fruit : fruits_) {
    if (fruit.is_visible_ && fruit.GetLocation() == container_) {
      fruit.is_visible_ = false;
      score_++;
    } else if (fruit.is_visible_) {
      fruit.Step();
    } else if (fruit.GetLocation().Row() == height_){
      is_game_over = true;
    }
  }
}

int Engine::GetScore() const { return score_; }

Location Engine::GetRandomLocation() {

  Location final_location(0, 0);

  for (size_t col = 0; col < width_; ++col) {
    Location loc( col, 0);
    if (std::rand() % 50== 0) {
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
