#ifndef CPPES8_SRC_TEXTURE_HPP_INCLUDED
#define CPPES8_SRC_TEXTURE_HPP_INCLUDED

#include "cppes8.hpp"
#include "handle.hpp"
#include "../../src/render/texture2d_static_d3d11.hpp"

#include <stdint.h>
#include <assert.h>

namespace cppes8 {

namespace texture {

struct Texture {
  moge::Texture2DStaticD3D11 texture;
};

using TextureHandle = cppes8::handle::Handle;

struct TextureDecl {
  const uint8_t* rgba = nullptr;
  uint16_t width = 0;
  uint16_t height = 0;
};

TextureHandle create(CPPES8& gamelib, TextureDecl& texture_decl);
void destroy(CPPES8& gamelib, TextureHandle handle);

}
}

#endif // CPPES8_SRC_TEXTURE_HPP_INCLUDED
