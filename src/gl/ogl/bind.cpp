#include "bind.hpp"
#include "../../trivial.hpp"

#include <stdio.h>

#undef MOGE_OGL_DEF
#define MOGE_OGL_DEF(ret, name, ...) ret (*gl##name)(__VA_ARGS__) = NULL;

MOGE_OGL_GLES2
MOGE_OGL_VAO

#undef MOGE_OGL_DEF
#define MOGE_OGL_DEF(ret, name, ...)                   \
  gl##name = (ret(*)(__VA_ARGS__))getproc("gl" #name); \
  if (gl##name == NULL) {                              \
    return false;                                      \
  }

static bool moge_gl_load_ogl_gles2(MogeGLGetFunc getproc) {
  MOGE_OGL_GLES2
  return true;
}

static bool moge_gl_load_ogl_vao(MogeGLGetFunc getproc) {
  MOGE_OGL_VAO
  return true;
}

void moge::gl::load_opengl_functions(MogeGLGetFunc getproc) {
  bool ok;
  ok = moge_gl_load_ogl_gles2(getproc);
  MOGE_ASSERT(ok);
  ok = moge_gl_load_ogl_vao(getproc);
  MOGE_ASSERT(ok);
}

static const char* opengl_err2str(GLenum err)
{
  switch (err) {
    case GL_NO_ERROR: return "GL_NO_ERROR";
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_CONTEXT_LOST: return "GL_CONTEXT_LOST";
  }
  return "Unknown Error";
}

void moge::gl::check_gl_error(const char* stmt, const char* file, unsigned int line) {
  GLenum err;
  err = glGetError();
  if (err != GL_NO_ERROR) {
    fprintf(stderr, "%s in %s [file : %s][line : %d]\n", opengl_err2str(err), stmt, file, line);
  }
}
