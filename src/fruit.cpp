//
// Created by Chirag Gupta on 4/26/20.
//

#include "fruit_grabber/fruit.h"

#include <cinder/gl/gl.h>

using namespace cinder;

Fruit::Fruit(const Location& location, const int type) : location_(location) {
  type_ = type;
  is_visible_ = true;
  colors_ =
      {       cinder::Color(1, 0, 0),
             cinder::Color(0, 1, 0),
              cinder::Color(0, 0, 1),
              cinder::Color(1, 0, 1),
      };
}

void Fruit::Step() {
  location_ = location_ + Location{0,15};
}

void Fruit::Draw() {
  gl::color(colors_.at(type_));
  gl::drawSolidEllipse(glm::vec2{(location_.Row()),
                                 (location_.Col())},32, 32);
  gl::color(1,1,1);
}

Location Fruit::GetLocation() const { return location_; }

int Fruit::GetType() const { return type_; }

Fruit::Fruit(const Fruit& fruit) = default;

Fruit::Fruit(Fruit&& fruit) noexcept = default;

Fruit& Fruit::operator=(const Fruit& fruit) = default;

Fruit& Fruit::operator=(Fruit&& fruit) noexcept = default;

Fruit::~Fruit() = default;