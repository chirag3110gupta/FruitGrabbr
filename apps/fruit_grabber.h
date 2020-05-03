// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_
#include <opencv2/opencv.hpp>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/audio/audio.h>
#include "fruit_grabber/engine.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  // Constructor
  MyApp();

  // Called when the app starts
  void setup() override;

  // Called in each frame
  void update() override;

  // Called after update to display
  void draw() override;

  // Called when user presses a key
  void keyDown(cinder::app::KeyEvent) override;

 private:

  // Draws score
  void DrawScore();

  // Draws the fruitgrabber logo
  void DrawLogo();

  // Makes the pause screen
  void DrawPauseScreen();

  // Draws when Game ends
  void DrawGameOver();

  // Prints specified text
  template <typename C>
  void PrintText(const std::string& text, const C& color, const cinder::ivec2& size,
                 const cinder::vec2& loc);

  // Makes the location vector for the container
  void MakeContainer(cv::Mat locations);

  cv::Mat frame_;
  cv::VideoCapture* vid_;
  cinder::gl::Texture2dRef background_;
  ci::audio::VoiceRef music_;
  Engine engine_;
  std::vector<Location> loc_green_;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
