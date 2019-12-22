#ifndef CPPES8_SRC_SHADER_HPP_INCLUDED
#define CPPES8_SRC_SHADER_HPP_INCLUDED

#include "cppes8.hpp"
#include <stdint.h>

namespace cppes8 {
namespace shader {

struct Shader {
  void* input_layout = nullptr;
  void* vertex_shader = nullptr;
  void* pixel_shader = nullptr;
};

struct InputLayout {
  const char* semantic_name = nullptr;
  uint32_t semantic_index = 0;
  uint32_t num_float = 0;
};

struct ShaderDecl {
  const InputLayout* array_of_input_layout = nullptr;
  size_t num_array_of_input_layout = 0;
  const char* vertex_shader = nullptr;
  size_t vertex_shader_len = 0;
  const char* pixel_shader = nullptr;
  size_t pixel_shader_len = 0;
};

Shader create(CPPES8& gamelib, ShaderDecl& shader_decl);
void destroy(CPPES8& gamelib, Shader shader);

} // namespace shader
} // namespace cppes8

cppes8::shader::Shader cppes8::shader::create(cppes8::CPPES8& gamelib, cppes8::shader::ShaderDecl& shader_decl) {
  assert(shader_decl.array_of_input_layout);
  assert(shader_decl.num_array_of_input_layout < 8);
  assert(shader_decl.vertex_shader);
  assert(shader_decl.pixel_shader);

  moge::InputLayoutD3D11 input_layout = gamelib.render.create_input_layout((const moge::RenderMinimalInputLayoutD3D11*)shader_decl.array_of_input_layout, 1, shader_decl.vertex_shader, shader_decl.vertex_shader_len);
  moge::ShaderObjectD3D11 vertex_shader = gamelib.render.create_vertex_shader(shader_decl.vertex_shader, shader_decl.vertex_shader_len);
  moge::ShaderObjectD3D11 pixel_shader = gamelib.render.create_pixel_shader(shader_decl.pixel_shader, shader_decl.pixel_shader_len);

  cppes8::shader::Shader shader;
  shader.input_layout = input_layout.input_layout;
  shader.vertex_shader = vertex_shader.vs;
  shader.pixel_shader = pixel_shader.ps;
  return shader;
}

void cppes8::shader::destroy(cppes8::CPPES8& gamelib, Shader shader) {
  assert(shader.input_layout);
  assert(shader.vertex_shader);
  assert(shader.pixel_shader);

  moge::InputLayoutD3D11 input_layout;
  input_layout.input_layout = (decltype(input_layout.input_layout))shader.input_layout;
  input_layout.destroy();
  moge::ShaderObjectD3D11 vertex_shader;
  vertex_shader.type = moge::ShaderObjectD3D11::Type::VERTEX_SHADER;
  vertex_shader.vs = (decltype(vertex_shader.vs))shader.vertex_shader;
  vertex_shader.destroy();
  moge::ShaderObjectD3D11 pixel_shader;
  pixel_shader.type = moge::ShaderObjectD3D11::Type::PIXEL_SHADER;
  pixel_shader.ps = (decltype(pixel_shader.ps))shader.pixel_shader;
  pixel_shader.destroy();
}

#endif // CPPES8_SRC_SHADER_HPP_INCLUDED
