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

enum MOGE_GL_UNIFORM_ARRAY_TYPE {
  MOGE_GL_UNIFORM_ARRAY_TYPE_UNDEFINED = 0,
  MOGE_GL_UNIFORM_ARRAY_TYPE_FLOAT4
};

enum MOGE_GL_TEXTURE_FORMAT {
  MOGE_GL_TEXTURE_FORMAT_UNDEFINED = 0,
  MOGE_GL_TEXTURE_FORMAT_RGB,
  MOGE_GL_TEXTURE_FORMAT_RGBA
};

enum MOGE_GL_TEXTURE_FILTER {
  MOGE_GL_TEXTURE_FILTER_UNDEFINED = 0,
  MOGE_GL_TEXTURE_FILTER_LINEAR,
  MOGE_GL_TEXTURE_FILTER_NEAREST
};

enum MOGE_GL_DRAW_PRIMITIVE {
  MOGE_GL_DRAW_PRIMITIVE_UNDEFINED = 0,
  MOGE_GL_DRAW_PRIMITIVE_TRIANGLES
};

namespace moge {
namespace gl {

struct ShaderDecl {
  struct InputLayout {
    const char* glsl_name;
    uint32_t glsl_index;
    const char* semantic_name;
    uint32_t semantic_index;
    uint32_t num_float;
  };

  InputLayout* input_ary;
  uint32_t num_input;
  const char* vertex_shader;
  const char* pixel_shader;
  size_t num_byte_of_vertex_shader;
  size_t num_byte_of_pixel_shader;
};

struct UniformArrayDecl {
  const char* name;
  enum MOGE_GL_SHADER_STAGE stage;
  enum MOGE_GL_UNIFORM_ARRAY_TYPE type;
  uint32_t num_element;
};

struct TextureDecl {
  const void* data;
  uint32_t width;
  uint32_t height;
  enum MOGE_GL_TEXTURE_FORMAT image_format;
  enum MOGE_GL_TEXTURE_FILTER min_filter;
  enum MOGE_GL_TEXTURE_FILTER mag_filter;
};

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_GL_HPP_INCLUDED
