#include <gtest/gtest.h>

#define SDL_MAIN_HANDLED
#include "../src/sdl/sdl.hpp"

TEST(MogeSDL, SDL2) {
  moge::sdl::SDLContext ctx = {};
  ASSERT_TRUE(!ctx.window);
  moge::sdl::createSDL(ctx);
  ASSERT_TRUE(ctx.window);
  HWND hwnd = moge::sdl::getHWND(ctx);
  ASSERT_TRUE(hwnd);
  moge::sdl::destroySDL(ctx);
  ASSERT_TRUE(!ctx.window);
}

TEST(MogeSDLDeath, SDL2Death) {
  moge::sdl::SDLContext ctx = {};
  ASSERT_TRUE(!ctx.window);
  moge::sdl::createSDL(ctx);
  ASSERT_DEATH(moge::sdl::createSDL(ctx), "");
  moge::sdl::destroySDL(ctx);
  ASSERT_DEATH(moge::sdl::destroySDL(ctx), "");
  ASSERT_DEATH(moge::sdl::getHWND(ctx), "");
}
