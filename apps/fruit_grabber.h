// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_
#include <opencv2/opencv.hpp>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include "fruit_grabber/engine.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void DrawScore();
  void DrawLogo();
  template <typename C>
  void PrintText(const std::string& text, const C& color, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  cv::Mat frame_;
  cv::VideoCapture* vid_;
  cinder::gl::Texture2dRef background_;
  Engine engine_;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
