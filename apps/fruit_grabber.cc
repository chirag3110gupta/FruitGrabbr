// Copyright (c) 2020 [Your Name]. All rights reserved.
#include "fruit_grabber.h"

#include <cinder/app/App.h>
#include <gflags/gflags.h>

#include <opencv2/opencv.hpp>

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/draw.h"
#include "cinder/gl/gl.h"

using std::chrono::system_clock;
using namespace cinder;

DECLARE_uint32(size);
DECLARE_uint32(tilesize);
DECLARE_uint32(speed);
DECLARE_string(name);

namespace myapp {

using cinder::app::KeyEvent;
const char kBoldFont[] = "Arial Bold";
const int kTextBuffer = 50;

MyApp::MyApp()
: engine_(FLAGS_size, FLAGS_size)
 {
  vid_ = new cv::VideoCapture(0);
 }

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  if (!vid_->isOpened()) {
    return;
  }
  audio::SourceFileRef sourceFile = audio::load(
      app::loadAsset( "bg.mp3" ) );
  music_ = audio::Voice::create( sourceFile );
}

void MyApp::update() {

    if (vid_->read(frame_)) {
      // flips matrix
      cv::Mat flipped;
      cv::flip(frame_, flipped, 1);

      // converts rgb to hsv
      cv::Mat hsv;
      cv::cvtColor(flipped, hsv, cv::COLOR_BGR2HSV);

      // gets green color and sets as background
      cv::Mat container;
      cv::inRange(hsv, cv::Scalar(30, 100, 50),
          cv::Scalar(70, 255, 255), container);
      cv::imwrite("/Users/chiraggupta/CLionProjects/cinder_0.9.2_mac"
                  "/my-projects/myapp-chiragg4/assets/fram.jpg", container);
      background_ =  cinder::gl::Texture2d::create(loadImage
          ( loadAsset( "fram.jpg" ) ));

      // updates game
      const auto time = system_clock::now();
      if (time - last_time_ > std::chrono::milliseconds(FLAGS_speed) &&
      engine_.getGameState() == Engine::GameState::kPlaying) {
        if (!music_->isPlaying()) {
          music_->start();
        }
        MakeContainer(container);
        engine_.Step();
        last_time_ = time;
      }

    }
}

void MyApp::draw() {
  cinder::gl::clear();
  gl::enableDepthRead();
  gl::enableDepthWrite();

  if (engine_.getGameState() == Engine::GameState::kPlaying) {
    engine_.Draw();
    gl::draw(background_);
    DrawLogo();
  } else if (engine_.getGameState() == Engine::GameState::kPaused) {
    DrawPauseScreen();
  } else {
    DrawGameOver();
  }
  DrawScore();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {

    case KeyEvent::KEY_RETURN:
      if (engine_.getGameState() == Engine::GameState::kPaused)  {
        engine_.setGameState(Engine::GameState::kPlaying);
      }
      if (engine_.getGameState() == Engine::GameState::kGameOver)  {
        engine_.Reset();
        engine_.setGameState(Engine::GameState::kPlaying);
      }
      break;

    case KeyEvent::KEY_p:
      if (engine_.getGameState() == Engine::GameState::kPlaying)  {
        engine_.setGameState(Engine::GameState::kPaused);
      }
  }
}

void MyApp::DrawScore() {
  glm::vec2 loc;
  loc.x = 2 * kTextBuffer;
  loc.y = getWindowHeight() - kTextBuffer;
  const cinder::vec2 location = loc;
  const cinder::ivec2 size = {500, 50};
  const cinder::Color color = cinder::Color::white();
  PrintText("Score: " + std::to_string(engine_.GetScore()),
      color, size, location);
}

void MyApp::DrawLogo() {
  cinder::gl::Texture2dRef logo = cinder::gl::Texture2d::create
      (loadImage( loadAsset( "logo.jpg" ) ));
  cinder::gl::draw(logo,cinder::Rectf(
      getWindowCenter().x - 1.5 * kTextBuffer,
      getWindowHeight() - 1.5 * kTextBuffer,
      getWindowCenter().x +  1.5 * kTextBuffer,
      getWindowHeight()));
}

template <typename C>
void MyApp::PrintText(const std::string& text, const C& color,
    const cinder::ivec2& size, const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font(kBoldFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA(0,
                              0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2,
                             loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::MakeContainer(cv::Mat locations) {
  loc_green_ = {};
  for (int i = 0; i < locations.cols; i++ ) {
    for (int j = 0; j < locations.rows; j++) {
      if (locations.at<uchar>(j, i) > 0) {
        loc_green_.emplace_back(i,j);     // Do your operations
      }
    }
  }
  engine_.setContainer(loc_green_);
}

void MyApp::DrawPauseScreen() {
  cinder::gl::Texture2dRef logo = cinder::gl::Texture2d::create
      (loadImage( loadAsset( "logo.jpg" ) ));
  cinder::gl::draw(logo,cinder::Rectf(
      getWindowCenter().x - 5 * kTextBuffer,
      getWindowCenter().y - 2.5 * kTextBuffer - 100,
      getWindowCenter().x +  5 * kTextBuffer,
      getWindowCenter().y + 2.5 * kTextBuffer - 100));
  glm::vec2 loc;
  loc.x = getWindowCenter().x;
  loc.y = getWindowHeight() - 300;
  const cinder::vec2 location = loc;
  const cinder::ivec2 size = {500, 50};
  const cinder::Color color = cinder::Color::white();
  PrintText("Press return to start the game ", color, size, location);
}

void MyApp::DrawGameOver() {
  cinder::gl::Texture2dRef logo = cinder::gl::Texture2d::create
      (loadImage(
          loadAsset( "gameover.jpg")));
  cinder::gl::draw(logo,cinder::Rectf(
      getWindowCenter().x - 5 * kTextBuffer,
      getWindowCenter().y - 3 * kTextBuffer - 100,
      getWindowCenter().x +  5 * kTextBuffer,
      getWindowCenter().y + 3 * kTextBuffer - 100));
  glm::vec2 loc;
  loc.x = getWindowCenter().x;
  loc.y = getWindowHeight() - 300;
  const cinder::vec2 location = loc;
  const cinder::ivec2 size = {500, 50};
  const cinder::Color color = cinder::Color::white();
  PrintText("Press return to start the game ", color, size, location);
}
}  // namespace myapp
