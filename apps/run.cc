// Copyright (c) 2020 [Your Name]. All rights reserved.
#include "fruit_grabber.h"
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>



DEFINE_uint32(size, 16, "the number of tiles in each row and column");
DEFINE_uint32(tilesize, 50, "the size of each tile");
DEFINE_uint32(speed, 50, "the speed (delay) of the game");
DEFINE_string(name, "Chirag", "the name of the player");


using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("FruitGrabber");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
