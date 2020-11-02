#ifndef MOGE_SRC_GL_GL_HPP_INCLUDED
#define MOGE_SRC_GL_GL_HPP_INCLUDED

#include "../trivial.hpp"
#include "../handle.hpp"

#ifndef MOGE_GL_INPUT_ELEMENT_MAX
#define MOGE_GL_INPUT_ELEMENT_MAX (8)
#endif

enum MOGE_GL_BACKEND {
  MOGE_GL_BACKEND_UNDEFINED = 0,
  MOGE_GL_BACKEND_D3D11,
  MOGE_GL_BACKEND_OGL
};

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
  MOGE_GL_TEXTURE_FORMAT_RGBA8
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

struct InputLayout {
  const char* glslAttributeName;
  uint32_t glslAttributeLocation;
  const char* hlslSemanticName;
  uint32_t hlslSemanticIndex;
  uint32_t numFloat;
};


struct ShaderDesc {
  InputLayout* inputArray;
  uint32_t numInput;
  const char* vertexShader;
  const char* pixelShader;
  size_t numByteOfVertexShader;
  size_t numByteOfPixelShader;
};

struct UniformArrayDesc {
  const char* name;
  enum MOGE_GL_SHADER_STAGE stage;
  enum MOGE_GL_UNIFORM_ARRAY_TYPE type;
  uint32_t numElement;
};

struct TextureDesc {
  const void* data;
  uint32_t width;
  uint32_t height;
  enum MOGE_GL_TEXTURE_FORMAT imageFormat;
  enum MOGE_GL_TEXTURE_FILTER minFilter;
  enum MOGE_GL_TEXTURE_FILTER magFilter;
};

struct Shader {
  Handle handle;
};

struct UniformArray {
  Handle handle;
};

struct VertexBuffer {
  Handle handle;
};

struct Texture {
  Handle handle;
};

struct Context {
  struct ContextImpl;
  ContextImpl* pimpl;
};

struct ContextDesc {
  uint32_t maxShaders;
  uint32_t maxUniformArrays;
  uint32_t maxVertexBuffers;
  uint32_t maxTextures;
  void* hwnd;
  void* (*getProcAddress)(const char*);
};

MOGE_GL_BACKEND getBackend();
Context createContext(ContextDesc& desc);
void destroyContext(Context& ctx);
void resizeBackBuffer(Context& ctx);
Shader createShader(Context& ctx, ShaderDesc& desc);
void destroyShader(Context& ctx, Shader shdr);
UniformArray createUniformArray(Context& ctx, Shader& shdr, UniformArrayDesc& desc);
void destroyUniformArray(Context& ctx, UniformArray& uary);
void updateUniformArray(Context& ctx, UniformArray& uary, const void* data, size_t num_bytes);
VertexBuffer createVertexBuffer(Context& ctx, uint32_t num_bytes);
void destroyVertexBuffer(Context& ctx, VertexBuffer& vbo);
void updateVertexBuffer(Context& ctx, VertexBuffer& vbo, const void* vertices, size_t num_bytes);
Texture createTexture(Context& ctx, TextureDesc& desc);
void destroyTexture(Context& ctx, Texture& tex);

void clear(Context& ctx, float R, float G, float B, float A);
void present(Context& ctx);
void setShader(Context& ctx, Shader& shdr);
void setUniformArray(Context& ctx, UniformArray& uary);
void setTexture(Context& ctx, Texture& tex);
void setVertexBuffer(Context& ctx, VertexBuffer& vbo);
void draw(Context& ctx, enum MOGE_GL_DRAW_PRIMITIVE topology, uint32_t count, uint16_t offset);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_GL_HPP_INCLUDED
