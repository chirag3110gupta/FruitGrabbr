//
// Created by Chirag Gupta on 4/26/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <vector>

#include "fruit.h"
#include "location.h"
class Engine {
 public:
  // Enum for the state of the game
  enum class GameState {
    kPaused,
    kPlaying,
    kGameOver
  };

  // Creates a new game of the given size.
  Engine(size_t width, size_t height);

  // Executes a time step: moves the fruits, etc.
  void Step();

  // Draws the game elements
  void Draw();

  // Start the game over.
  void Reset();

  // Gets Score
  int GetScore() const;

  // Sets the locations of the pixels of the container
  void setContainer(const std::vector<Location>& container);

  // Sets the game state
  void setGameState(GameState gameState);

  // Gets the game state
  GameState getGameState() const;

 private:
  // Gets a random location in the first row for the fruit
  Location GetRandomLocation();

  int score_;
  std::vector<Location> container_;
  std::vector<Fruit> fruits_;
  const size_t width_;
  const size_t height_;
  GameState gameState;


};



#endif  // FINALPROJECT_ENGINE_H
