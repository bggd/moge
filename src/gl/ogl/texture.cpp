#include "texture.hpp"
#include "bind.hpp"

void moge::gl::createTextureOGL(moge::gl::ContextOGL&, moge::gl::TextureOGL& tex, moge::gl::TextureDecl& decl) {
  MOGE_ASSERT(!tex.id);
  MOGE_ASSERT(decl.data);
  MOGE_ASSERT(decl.width);
  MOGE_ASSERT(decl.height);
  MOGE_ASSERT(decl.image_format);
  MOGE_ASSERT(decl.min_filter);
  MOGE_ASSERT(decl.mag_filter);

  GLuint id;
  MOGE_GL_CHECK(glGenTextures(1, &id));
  MOGE_ASSERT(id);
  MOGE_GL_CHECK(glBindTexture(GL_TEXTURE_2D, id));

  bool ok;
  MOGE_GL_CHECK(ok = glIsTexture(id));
  MOGE_ASSERT(ok);

  static const GLint _filters[3] = {
      0, GL_LINEAR, GL_NEAREST};

  GLint filter;
  filter = _filters[decl.min_filter];
  MOGE_GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter));

  filter = _filters[decl.mag_filter];
  MOGE_GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter));

  static const GLint _internal_formats[3] = {
      0, GL_RGB8, GL_RGBA8};
  static const GLenum _formats[3] = {
      0, GL_RGB, GL_RGBA};

  GLint internal_fmt = _internal_formats[decl.image_format];
  GLenum fmt = _formats[decl.image_format];

  MOGE_GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internal_fmt, decl.width, decl.height, 0, fmt, GL_UNSIGNED_BYTE, decl.data));

  tex.id = id;
}

void moge::gl::destroyTextureOGL(TextureOGL& tex) {
  MOGE_ASSERT(tex.id);

  bool ok;
  MOGE_GL_CHECK(ok = glIsTexture(tex.id));
  MOGE_ASSERT(ok);

  MOGE_GL_CHECK(glDeleteTextures(1, &tex.id));

  tex.id = 0;
}
