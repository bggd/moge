#include "texture.hpp"

cppes8::texture::TextureHandle cppes8::texture::create(cppes8::CPPES8& gamelib, cppes8::texture::TextureDecl& texture_decl) {
  assert(texture_decl.rgba);
  assert(texture_decl.width);
  assert(texture_decl.height);

  cppes8::texture::Texture texture;
  texture.texture = gamelib.render.create_texture2d_static(texture_decl.rgba, texture_decl.width, texture_decl.height);

  return gamelib.textures.insert(texture);
}

void cppes8::texture::destroy(cppes8::CPPES8& gamelib, cppes8::texture::TextureHandle handle) {
  cppes8::texture::Texture* texture = gamelib.textures.get(handle);
  texture->texture.destroy();
  gamelib.textures.remove(handle);
}
