// Copyright (c) 2020 [Your Name]. All rights reserved.
#include <opencv2/opencv.hpp>
#include "my_app.h"
#include <Box2D/Common/b2Math.h>
#include <cinder/app/App.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/draw.h"


namespace myapp {

using cinder::app::KeyEvent;
const char kBoldFont[] = "Arial Bold";
const int kTextBuffer = 50;

MyApp::MyApp() {
  gravity_.x = (0.0f);
  gravity_.y = (-10.0f);
  world_ = new b2World(gravity_);
  vid_ = new cv::VideoCapture(0);
  currentscore_ = 0;
}

void MyApp::setup() {
  if (!vid_->isOpened()) {
    return;
  }
}

void MyApp::update() {
    if (vid_->read(frame_)) {
        cv::Mat flipped;
        cv::flip(frame_, flipped, 1);
        cv::imwrite("/Users/chiraggupta/CLionProjects/cinder_0.9.2_mac"
                    "/my-projects/myapp-chiragg4/assets/fram.jpg", flipped);
        background_ =  cinder::gl::Texture2d::create(loadImage
            ( loadAsset( "fram.jpg" ) ));
    }
}

void MyApp::draw() {
  cinder::gl::clear();
  cinder::gl::draw(background_);
  DrawScore();
  DrawLogo();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawScore() {
  glm::vec2 loc;
  loc.x = 2 * kTextBuffer;
  loc.y = getWindowHeight() - kTextBuffer;
  const cinder::vec2 location = loc;
  const cinder::ivec2 size = {500, 50};
  const cinder::Color color = cinder::Color::white();
  PrintText("Score: " + std::to_string(currentscore_), color, size, location);
}

void MyApp::DrawLogo() {
  glm::vec2 upperleft, bottomright;
  const cinder::ivec2 size = {500, 50};
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
}  // namespace myapp
