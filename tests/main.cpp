#include <gtest/gtest.h>
#include "sdl.hpp"
#include "gl_context.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "uniform_array.hpp"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
