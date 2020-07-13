#ifndef MOGE_SRC_GL_OGL_BIND_HPP_INCLUDED
#define MOGE_SRC_GL_OGL_BIND_HPP_INCLUDED

#include <stdint.h>

typedef unsigned char GLboolean;
typedef void GLvoid;
typedef char GLbyte;
typedef char GLchar;
typedef unsigned char GLubyte;
typedef int16_t GLshort;
typedef uint16_t GLushort;
typedef int32_t GLint;
typedef uint32_t GLuint;
typedef uint32_t GLenum;
typedef uint32_t GLsizei;
typedef intptr_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef uint32_t GLbitfield;
typedef float GLfloat;
typedef double GLdouble;

#define GL_FALSE 0
#define GL_TRUE 1

#define GL_COLOR_BUFFER_BIT 0x00004000

#define GL_VENDOR 0x1f00
#define GL_RENDERER 0x1f01
#define GL_VERSION 0x1f02
#define GL_SHADING_LANGUAGE_VERSION 0x8b8c

#define GL_TEXTURE_2D 0x0de1
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601

#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_RGB8 0x8051
#define GL_RGBA8 0x8058

#define GL_UNSIGNED_BYTE 0x1401
#define GL_FLOAT 0x1406

#define GL_NO_ERROR 0
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_VALUE 0x0501
#define GL_INVALID_OPERATION 0x0502
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_OUT_OF_MEMORY 0x0505
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#define GL_CONTEXT_LOST 0x0507

#define GL_ARRAY_BUFFER 0x8892
#define GL_STREAM_DRAW 0x88e0
#define GL_STATIC_DRAW 0x88e4
#define GL_DYNAMIC_DRAW 0x88e8
#define GL_BUFFER_SIZE 0x8764

#define GL_TRIANGLES 0x0004

#define GL_COMPILE_STATUS 0x8b81
#define GL_LINK_STATUS 0x8b82

#define GL_FRAGMENT_SHADER 0x8b30
#define GL_VERTEX_SHADER 0x8b31

#define MOGE_OGL_DEF(ret, name, ...) extern ret (*gl##name)(__VA_ARGS__);

#define MOGE_OGL_GLES2                                                                                         \
  MOGE_OGL_DEF(GLenum, GetError, GLvoid)                                                                       \
  MOGE_OGL_DEF(GLubyte*, GetString, GLenum)                                                                    \
  MOGE_OGL_DEF(void, Clear, GLbitfield)                                                                        \
  MOGE_OGL_DEF(void, GenTextures, GLsizei, GLuint*)                                                            \
  MOGE_OGL_DEF(void, BindTexture, GLenum, GLuint)                                                              \
  MOGE_OGL_DEF(GLboolean, IsTexture, GLuint)                                                                   \
  MOGE_OGL_DEF(void, TexParameteri, GLenum, GLenum, GLint)                                                     \
  MOGE_OGL_DEF(void, TexImage2D, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*) \
  MOGE_OGL_DEF(void, DeleteTextures, GLsizei, const GLuint*)                                                   \
  MOGE_OGL_DEF(void, GenBuffers, GLsizei, GLuint*)                                                             \
  MOGE_OGL_DEF(void, BindBuffer, GLenum, GLuint)                                                               \
  MOGE_OGL_DEF(GLboolean, IsBuffer, GLuint)                                                                    \
  MOGE_OGL_DEF(void, BufferData, GLenum, GLsizeiptr size, const GLvoid*, GLenum)                               \
  MOGE_OGL_DEF(void, GetBufferParameteriv, GLenum, GLenum, GLint*)                                             \
  MOGE_OGL_DEF(void, DeleteBuffers, GLsizei, const GLuint*)                                                    \
  MOGE_OGL_DEF(void, VertexAttribPointer, GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*)            \
  MOGE_OGL_DEF(void, EnableVertexAttribArray, GLuint)                                                          \
  MOGE_OGL_DEF(void, DrawArrays, GLenum, GLint, GLsizei)                                                       \
  MOGE_OGL_DEF(GLuint, CreateProgram, GLvoid)                                                                  \
  MOGE_OGL_DEF(GLboolean, IsProgram, GLuint)                                                                   \
  MOGE_OGL_DEF(GLuint, CreateShader, GLenum)                                                                   \
  MOGE_OGL_DEF(void, ShaderSource, GLuint, GLsizei, const GLchar**, const GLint*)                              \
  MOGE_OGL_DEF(void, CompileShader, GLuint)                                                                    \
  MOGE_OGL_DEF(void, GetShaderiv, GLuint, GLenum, GLint*)                                                      \
  MOGE_OGL_DEF(GLint, GetUniformLocation, GLuint, const GLchar*)                                               \
  MOGE_OGL_DEF(void, BindAttribLocation, GLuint, GLuint, const GLchar*)                                        \
  MOGE_OGL_DEF(void, AttachShader, GLuint, GLuint)                                                             \
  MOGE_OGL_DEF(void, LinkProgram, GLuint)                                                                      \
  MOGE_OGL_DEF(void, GetProgramiv, GLuint, GLenum, GLint*)                                                     \
  MOGE_OGL_DEF(void, DetachShader, GLuint, GLuint)                                                             \
  MOGE_OGL_DEF(void, DeleteProgram, GLuint)                                                                    \
  MOGE_OGL_DEF(void, ClearColor, GLfloat, GLfloat, GLfloat, GLfloat)                                           \
  MOGE_OGL_DEF(void, UseProgram, GLuint)                                                                       \
  MOGE_OGL_DEF(void, Viewport, GLint, GLint, GLsizei, GLsizei)                                                 \
  MOGE_OGL_DEF(void, Uniform4fv, GLint, GLsizei, const GLfloat*)

MOGE_OGL_GLES2

#define MOGE_OGL_VAO                                    \
  MOGE_OGL_DEF(void, GenVertexArrays, GLsizei, GLuint*) \
  MOGE_OGL_DEF(void, BindVertexArray, GLuint)           \
  MOGE_OGL_DEF(GLboolean, IsVertexArray, GLuint)        \
  MOGE_OGL_DEF(void, DeleteVertexArrays, GLsizei, const GLuint*)

MOGE_OGL_VAO

#define MOGE_GL_CHECK(stmt)                              \
  do {                                                   \
    stmt;                                                \
    moge::gl::check_gl_error(#stmt, __FILE__, __LINE__); \
  } while (0);

typedef void* (*MogeGLGetFunc)(const char* name);

namespace moge {
namespace gl {

void load_opengl_functions(MogeGLGetFunc getproc);
void check_gl_error(const char* stmt, const char* file, unsigned int line);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_OGL_BIND_HPP_INCLUDED
