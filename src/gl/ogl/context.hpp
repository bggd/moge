#ifndef MOGE_SRC_OGL_CONTEXT_HPP_INCLUDED
#define MOGE_SRC_OGL_CONTEXT_HPP_INCLUDED

namespace moge {
namespace gl {

struct ContextOGL {
};

void createContextOGL(ContextOGL& ctx);
void destroyContextOGL(ContextOGL& ctx);
void resizeBackBufferOGL(ContextOGL& ctx);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_OGL_CONTEXT_HPP_INCLUDED
