#include "shader.hpp"
#include "bind.hpp"

void moge::gl::createShaderOGL(ContextOGL&, ShaderOGL& shdr, ShaderDesc& desc) {
  MOGE_ASSERT(!shdr.id);

  GLuint id;
  MOGE_GL_CHECK(id = glCreateProgram());
  MOGE_ASSERT(id);

  for (uint32_t i = 0; i < desc.numInput; ++i) {
    MOGE_ASSERT(desc.inputArray[i].glslAttributeName);
    MOGE_ASSERT(desc.inputArray[i].numFloat > 0);
    MOGE_ASSERT(desc.inputArray[i].numFloat < 5);

    MOGE_GL_CHECK(glBindAttribLocation(id, desc.inputArray[i].glslAttributeLocation, desc.inputArray[i].glslAttributeName));
  }

  GLuint vs, fs;
  MOGE_GL_CHECK(vs = glCreateShader(GL_VERTEX_SHADER));
  MOGE_ASSERT(vs);
  MOGE_GL_CHECK(glShaderSource(vs, 1, &desc.vertexShader, NULL));
  MOGE_GL_CHECK(glCompileShader(vs));

  GLint status;
  MOGE_GL_CHECK(glGetShaderiv(vs, GL_COMPILE_STATUS, &status));
  MOGE_ASSERT(status);

  MOGE_GL_CHECK(fs = glCreateShader(GL_FRAGMENT_SHADER));
  MOGE_ASSERT(fs);
  MOGE_GL_CHECK(glShaderSource(fs, 1, &desc.pixelShader, NULL));
  MOGE_GL_CHECK(glCompileShader(fs));

  MOGE_GL_CHECK(glGetShaderiv(fs, GL_COMPILE_STATUS, &status));
  MOGE_ASSERT(status);

  MOGE_GL_CHECK(glAttachShader(id, vs));
  MOGE_GL_CHECK(glAttachShader(id, fs));

  MOGE_GL_CHECK(glGetProgramiv(id, GL_LINK_STATUS, &status));
  MOGE_ASSERT(status);

  MOGE_GL_CHECK(glDetachShader(id, vs));
  MOGE_GL_CHECK(glDetachShader(id, fs));

  shdr.id = id;
}

void moge::gl::destroyShaderOGL(moge::gl::ShaderOGL& shdr) {
  MOGE_ASSERT(shdr.id);

  bool ok;
  MOGE_GL_CHECK(ok = glIsProgram(shdr.id));
  MOGE_ASSERT(ok);

  MOGE_GL_CHECK(glDeleteProgram(shdr.id));

  shdr.id = 0;
}
