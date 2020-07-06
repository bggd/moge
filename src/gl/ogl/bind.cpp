#include "bind.hpp"
#include "../../trivial.hpp"

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
