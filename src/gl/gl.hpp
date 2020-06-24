#ifndef MOGE_SRC_GL_GL_HPP_INCLUDED
#define MOGE_SRC_GL_GL_HPP_INCLUDED

#include "../trivial.hpp"

#ifndef MOGE_GL_INPUT_ELEMENT_MAX
#define MOGE_GL_INPUT_ELEMENT_MAX (8)
#endif

enum MOGE_GL_SHADER_STAGE {
  MOGE_GL_SHADER_STAGE_UNDEFINED = 0,
  MOGE_GL_SHADER_STAGE_VERTEX,
  MOGE_GL_SHADER_STAGE_PIXEL
};

namespace moge {
namespace gl {

struct ShaderDecl {
  struct InputLayout {
    const char* semantic_name;
    uint32_t semantic_index;
    uint32_t num_float;
  };

  InputLayout *input_ary;
  uint32_t num_input;
  const char* vertex_shader;
  const char* pixel_shader;
  size_t num_byte_of_vertex_shader;
  size_t num_byte_of_pixel_shader;
};

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_GL_HPP_INCLUDED
