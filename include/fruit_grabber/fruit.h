//
// Created by Chirag Gupta on 4/26/20.
//

#ifndef FINALPROJECT_FRUIT_H
#define FINALPROJECT_FRUIT_H

#include <cinder/gl/Texture.h>
#include <cinder/gl/gl.h>

#include "location.h"
#include "string"

class Fruit {
 public:
  explicit Fruit(const Location&, const int type);

  // Rule of Five.
  Fruit(const Fruit&);
  Fruit(Fruit&&) noexcept;
  Fruit& operator=(const Fruit&);
  Fruit& operator=(Fruit&&) noexcept;
  ~Fruit();

  Location GetLocation() const;
  void Step();
  void Draw();

  bool is_visible_;

 private:
  Location location_;
  int type_;
  cinder::gl::TextureRef background_;
  cinder::gl::BatchRef	mSphere_;
  cinder::gl::GlslProgRef mGlsl_;
};

#endif  // FINALPROJECT_FRUIT_H
