//
// Created by Chirag Gupta on 4/26/20.
//

#include "fruit_grabber/fruit.h"

#include <cinder/gl/gl.h>

using namespace cinder;

Fruit::Fruit(const Location& location, const int type) : location_(location) {
  type_ = type;
  is_visible_ = true;
}

Location Fruit::GetLocation() const { return location_; }
void Fruit::Step() {
  location_ = location_ + Location{0,1};
}

void Fruit::Draw() {
//  auto img = cinder::loadImage("fruit_textures/orange.jpg");
//  background_ = cinder::gl::Texture::create( img );
//  background_->bind();
//  auto shader = cinder::gl::ShaderDef().texture().lambert();
//  mGlsl_ = cinder::gl::getStockShader( shader );
//  auto sphere = cinder::geom::Sphere().subdivisions( 50 );
//  sphere.radius(8);
//  mSphere_ = cinder::gl::Batch::create( sphere, mGlsl_ );
//  mSphere_->draw();
//
//  cinder::CameraPersp cam;
//  cam.lookAt( cinder::vec3( 3, 3, 3 ), cinder::vec3( 0 ) );
//  cinder::gl::setMatrices( cam );
//
//  auto lambert = gl::ShaderDef().lambert();
//  auto shader = gl::getStockShader( lambert );
//  shader->bind();
  //gl::drawSphere( vec3(), 0.2, 40 );
  //gl::clear();
  gl::drawSolidEllipse(glm::vec2{(location_.Row() * 50) + 8, (location_.Col() * 50) + 8},32, 32);
}

Fruit::Fruit(const Fruit& fruit) = default;
Fruit::Fruit(Fruit&& fruit) noexcept = default;
Fruit& Fruit::operator=(const Fruit& fruit) = default;
Fruit& Fruit::operator=(Fruit&& fruit) noexcept = default;
Fruit::~Fruit() = default;