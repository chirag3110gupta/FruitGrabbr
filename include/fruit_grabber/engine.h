//
// Created by Chirag Gupta on 4/26/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "location.h"
#include "fruit.h"
#include <vector>
class Engine {
 public:
  // Creates a new game of the given size.
  Engine(size_t width, size_t height);

  // Executes a time step: moves the fruits, etc.
  void Step();

  void Draw();

  // Start the game over.
  void Reset();

  int GetScore() const;
 private:
  Location GetRandomLocation();
 private:
  int score_;
  std::vector<Location> container_;
  std::vector<Fruit> fruits_;
  bool is_game_over;
  const size_t width_;
  const size_t height_;
};



#endif  // FINALPROJECT_ENGINE_H
