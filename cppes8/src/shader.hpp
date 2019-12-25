#ifndef CPPES8_SRC_SHADER_HPP_INCLUDED
#define CPPES8_SRC_SHADER_HPP_INCLUDED

#include "../../src/render/render_minimal_d3d11.hpp"
#include "handle.hpp"
#include <stdint.h>

namespace cppes8 {
struct CPPES8;
}

namespace cppes8 {

namespace shader {

struct Shader {
  moge::InputLayoutD3D11 input_layout;
  moge::ShaderObjectD3D11 vertex_shader;
  moge::ShaderObjectD3D11 pixel_shader;
  uint32_t stride = 0;
};

using ShaderHandle = cppes8::handle::Handle;

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

ShaderHandle create(CPPES8& gamelib, ShaderDecl& shader_decl);
void destroy(CPPES8& gamelib, ShaderHandle handle);

} // namespace shader
} // namespace cppes8

#endif // CPPES8_SRC_SHADER_HPP_INCLUDED
