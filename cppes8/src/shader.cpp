#include "cppes8.hpp"
#include "shader.hpp"

cppes8::shader::ShaderHandle cppes8::shader::create(cppes8::CPPES8& gamelib, cppes8::shader::ShaderDecl& shader_decl) {
  assert(shader_decl.array_of_input_layout);
  assert(shader_decl.num_array_of_input_layout < 8);
  assert(shader_decl.vertex_shader);
  assert(shader_decl.pixel_shader);

  moge::InputLayoutD3D11 input_layout = gamelib.render.create_input_layout((const moge::RenderMinimalInputLayoutD3D11*)shader_decl.array_of_input_layout, shader_decl.num_array_of_input_layout, shader_decl.vertex_shader, shader_decl.vertex_shader_len);
  moge::ShaderObjectD3D11 vertex_shader = gamelib.render.create_vertex_shader(shader_decl.vertex_shader, shader_decl.vertex_shader_len);
  moge::ShaderObjectD3D11 pixel_shader = gamelib.render.create_pixel_shader(shader_decl.pixel_shader, shader_decl.pixel_shader_len);

  cppes8::shader::Shader shader;
  shader.input_layout = input_layout;
  shader.vertex_shader = vertex_shader;
  shader.pixel_shader = pixel_shader;

  for (size_t i = 0; i < shader_decl.num_array_of_input_layout; ++i) {
    shader.stride += shader_decl.array_of_input_layout[i].num_float;
  }

  return gamelib.shaders.insert(shader);
}

void cppes8::shader::destroy(cppes8::CPPES8& gamelib, cppes8::shader::ShaderHandle handle) {
  cppes8::shader::Shader* shader = gamelib.shaders.get(handle);
  shader->input_layout.destroy();
  shader->vertex_shader.destroy();
  shader->pixel_shader.destroy();
  gamelib.shaders.remove(handle);
}

