#ifndef CPPES8_SRC_GFX_HPP_INCLUDED
#define CPPES8_SRC_GFX_HPP_INCLUDED

#include "cppes8.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include <stdint.h>

namespace cppes8 {

namespace gfx {

void clear(CPPES8& gamelib, float R, float G, float B, float A);
void present(CPPES8& gamelib);
void set_shader(CPPES8& gamelib, cppes8::shader::ShaderHandle handle);
void set_projection_matrix(CPPES8& gamelib, float matrix[16]);
void set_texture(CPPES8& gamelib, cppes8::texture::TextureHandle handle);
void draw_triangles(CPPES8& gamelib, float* vertices, size_t num_vertex);

} // namespace gfx
} // namespace cppes8

void cppes8::gfx::clear(cppes8::CPPES8& gamelib, float R, float G, float B, float A) {
  gamelib.render.d3d11.clear(R, G, B, A);
}

void cppes8::gfx::present(cppes8::CPPES8& gamelib) {
  gamelib.render.d3d11.present();
}

void cppes8::gfx::set_shader(cppes8::CPPES8& gamelib, cppes8::shader::ShaderHandle handle) {
  gamelib.state_gfx.current_shader_handle = handle;
}

void cppes8::gfx::set_projection_matrix(cppes8::CPPES8& gamelib, float matrix[16]) {
  gamelib.render.set_projection_matrix(matrix);
}

void cppes8::gfx::set_texture(cppes8::CPPES8& gamelib, cppes8::texture::TextureHandle handle) {
  gamelib.state_gfx.current_texture_handle = handle;
}

void cppes8::gfx::draw_triangles(cppes8::CPPES8& gamelib, float* vertices, size_t num_vertex) {
  cppes8::shader::Shader* shader = gamelib.shaders.get(gamelib.state_gfx.current_shader_handle);
  gamelib.render.set_shader(shader->vertex_shader, shader->pixel_shader);
  if (gamelib.state_gfx.current_texture_handle.id != UINT32_MAX) {
    cppes8::texture::Texture* texture = gamelib.textures.get(gamelib.state_gfx.current_texture_handle);
    gamelib.render.draw_triangles(texture->texture, vertices, sizeof(float) * num_vertex, sizeof(float) * shader->stride, shader->input_layout);
  }
  else {
    gamelib.render.draw_triangles_without_texture(vertices, sizeof(float) * num_vertex, sizeof(float) * shader->stride, shader->input_layout);
  }
}

#endif // CPPES8_SRC_GFX_HPP_INCLUDED
