// Copyright (c) 2020 [Your Name]. All rights reserved.
#include "fruit_grabber.h"

#include <cinder/app/App.h>
#include <gflags/gflags.h>

#include <opencv2/opencv.hpp>

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/draw.h"
#include "cinder/gl/gl.h"

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
}

void MyApp::update() {
    if (vid_->read(frame_)) {
      cv::Mat flipped;
      cv::flip(frame_, flipped, 1);
      cv::imwrite("/Users/chiraggupta/CLionProjects/cinder_0.9.2_mac"
                  "/my-projects/myapp-chiragg4/assets/fram.jpg", flipped);
      background_ =  cinder::gl::Texture2d::create(loadImage
                                                       ( loadAsset( "fram.jpg" ) ));
      cv::Mat hsv;
      cv::cvtColor(flipped, hsv, cv::COLOR_BGR2HSV);
      cv::Mat container;
      cv::inRange(hsv, cv::Scalar(20, 100, 70), cv::Scalar(70, 255, 255), container);
      cv::Mat nonZeroCoordinates;
      findNonZero(container, nonZeroCoordinates);
      for (int i = 0; i < nonZeroCoordinates.total(); i++ ) {

      }
      engine_.Step();

//      cv::imwrite("/Users/chiraggupta/CLionProjects/cinder_0.9.2_mac"
//                  "/my-projects/myapp-chiragg4/assets/fram.jpg", container);
//      background_ =  cinder::gl::Texture2d::create(loadImage
//                                                       ( loadAsset( "fram.jpg" ) ));
    }
}

void MyApp::draw() {
  cinder::gl::clear();
  gl::enableDepthRead();
  gl::enableDepthWrite();

//  CameraPersp cam;
//  cam.lookAt( vec3( 400, 400 , 800), vec3( 400,400,0));
//  gl::setMatrices( cam );
//
//  auto lambert = gl::ShaderDef().lambert();
//  auto shader = gl::getStockShader( lambert );
//  shader->bind();
  engine_.Draw();
  gl::draw(background_);
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
  PrintText("Score: " + std::to_string(engine_.GetScore() - 1), color, size, location);
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
