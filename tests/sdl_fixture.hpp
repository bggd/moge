#ifndef MOGE_TEST_SDL_FIXTURE_HPP_INCLUDED
#define MOGE_TEST_SDL_FIXTURE_HPP_INCLUDED

#include <gtest/gtest.h>

#include "../src/sdl/sdl.hpp"

struct MogeSDLFixture : ::testing::Test {

  moge::sdl::SDLContext sdl_ctx;

  virtual void SetUp() override {
    moge::sdl::SDLContext ctx = {};
    sdl_ctx = ctx;
    moge::sdl::createSDL(sdl_ctx);
  }

  virtual void TearDown() override {
    moge::sdl::destroySDL(sdl_ctx);
  }

  HWND getHWND() {
    return moge::sdl::getHWND(sdl_ctx);
  }
};

#endif // MOGE_TEST_SDL_FIXTURE_HPP_INCLUDED
