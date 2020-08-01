#include "gl.hpp"
#include "ogl/context.hpp"

#include "../handle_pool.hpp"

#if defined(MOGE_USE_OPENGL)
#include "ogl/bind.hpp"
#include "ogl/context.hpp"
#include "ogl/shader.hpp"
#include "ogl/uniform_array.hpp"
#include "ogl/vertex_buffer.hpp"
#include "ogl/texture.hpp"

#include "ogl/bind.cpp"
#include "ogl/context.cpp"
#include "ogl/shader.cpp"
#include "ogl/uniform_array.cpp"
#include "ogl/vertex_buffer.cpp"
#include "ogl/texture.cpp"
#elif defined(MOGE_USE_DIRECT3D11)
#include "d3d11/context.hpp"
#include "d3d11/shader.hpp"
#include "d3d11/uniform_array.hpp"
#include "d3d11/vertex_buffer.hpp"
#include "d3d11/texture.hpp"

#include "d3d11/context.cpp"
#include "d3d11/shader.cpp"
#include "d3d11/uniform_array.cpp"
#include "d3d11/vertex_buffer.cpp"
#include "d3d11/texture.cpp"
#endif

#define MOGE_GL_GET_CONTEXT(ctx) ctx.pimpl->ctx

#if defined(MOGE_USE_OPENGL)
typedef moge::gl::ContextOGL MogeGLCtx;
typedef moge::gl::ShaderOGL MogeGLShader;
typedef moge::gl::UniformArrayOGL MogeGLUniformArray;
typedef moge::gl::VertexBufferOGL MogeGLVBO;
typedef moge::gl::TextureOGL MogeGLTexture;
#define MOGE_GL_CREATE_CONTEXT(ctx) moge::gl::createContextOGL(ctx)
#define MOGE_GL_DESTROY_CONTEXT(ctx) moge::gl::destroyContextOGL(ctx)
#define MOGE_GL_RESIZE_BACK_BUFFER(ctx) moge::gl::resizeBackBufferOGL(MOGE_GL_GET_CONTEXT(ctx))
#define MOGE_GL_CREATE_SHADER(ctx, shdr, decl) moge::gl::createShaderOGL(MOGE_GL_GET_CONTEXT(ctx), shdr, decl)
#define MOGE_GL_DESTROY_SHADER(shdr) moge::gl::destroyShaderOGL(shdr)
#define MOGE_GL_CREATE_UNIFORM_ARRAY(ctx, shdr, uary, decl) moge::gl::createUniformArrayOGL(MOGE_GL_GET_CONTEXT(ctx), shdr, uary, decl)
#define MOGE_GL_DESTROY_UNIFORM_ARRAY(uary) moge::gl::destroyUniformArrayOGL(uary)
#define MOGE_GL_UPDATE_UNIFORM_ARRAY(ctx, uary, data, numbytes) moge::gl::uploadUniformArrayOGL(MOGE_GL_GET_CONTEXT(ctx), uary, data, numbytes)
#define MOGE_GL_CREATE_VERTEX_BUFFER(ctx, vbo, num_bytes) moge::gl::createVertexBufferOGL(MOGE_GL_GET_CONTEXT(ctx), vbo, num_bytes)
#define MOGE_GL_DESTROY_VERTEX_BUFFER(vbo) moge::gl::destroyVertexBufferOGL(vbo)
#define MOGE_GL_UPDATE_VERTEX_BUFFER(ctx, vbo, vertices, numbytes) moge::gl::uploadVertexBufferOGL(MOGE_GL_GET_CONTEXT(ctx), vbo, vertices, numbytes)
#define MOGE_GL_CREATE_TEXTURE(ctx, tex, decl) moge::gl::createTextureOGL(MOGE_GL_GET_CONTEXT(ctx), tex, decl)
#define MOGE_GL_DESTROY_TEXTURE(tex) moge::gl::destroyTextureOGL(tex)
#elif defined(MOGE_USE_DIRECT3D11)
typedef moge::gl::ContextD3D11 MogeGLCtx;
typedef moge::gl::ShaderD3D11 MogeGLShader;
typedef moge::gl::UniformArrayD3D11 MogeGLUniformArray;
typedef moge::gl::VertexBufferD3D11 MogeGLVBO;
typedef moge::gl::TextureD3D11 MogeGLTexture;
#define MOGE_GL_CREATE_CONTEXT(ctx) moge::gl::createContextD3D11(ctx)
#define MOGE_GL_DESTROY_CONTEXT(ctx) moge::gl::destroyContextD3D11(ctx)
#define MOGE_GL_RESIZE_BACK_BUFFER(ctx) moge::gl::resizeBackBufferD3D11(MOGE_GL_GET_CONTEXT(ctx))
#define MOGE_GL_CREATE_SHADER(ctx, shdr, decl) moge::gl::createShaderD3D11(MOGE_GL_GET_CONTEXT(ctx), shdr, decl)
#define MOGE_GL_DESTROY_SHADER(shdr) moge::gl::destroyShaderD3D11(shdr)
#define MOGE_GL_CREATE_UNIFORM_ARRAY(ctx, shdr, uary, decl) moge::gl::createUniformArrayD3D11(MOGE_GL_GET_CONTEXT(ctx), shdr, uary, decl)
#define MOGE_GL_DESTROY_UNIFORM_ARRAY(uary) moge::gl::destroyUniformArrayD3D11(uary)
#define MOGE_GL_UPDATE_UNIFORM_ARRAY(ctx, uary, data, numbytes) moge::gl::uploadUniformArrayD3D11(MOGE_GL_GET_CONTEXT(ctx), uary, data, numbytes)
#define MOGE_GL_CREATE_VERTEX_BUFFER(ctx, vbo, num_bytes) moge::gl::createVertexBufferD3D11(MOGE_GL_GET_CONTEXT(ctx), vbo, num_bytes)
#define MOGE_GL_DESTROY_VERTEX_BUFFER(vbo) moge::gl::destroyVertexBufferD3D11(vbo)
#define MOGE_GL_UPDATE_VERTEX_BUFFER(ctx, vbo, vertices, numbytes) moge::gl::uploadVertexBufferD3D11(MOGE_GL_GET_CONTEXT(ctx), vbo, vertices, numbytes)
#define MOGE_GL_CREATE_TEXTURE(ctx, tex, decl) moge::gl::createTextureD3D11(MOGE_GL_GET_CONTEXT(ctx), tex, decl)
#define MOGE_GL_DESTROY_TEXTURE(tex) moge::gl::destroyTextureD3D11(tex)
#endif

struct moge::gl::Context::ContextImpl {

  struct ResourcePool {
    moge::HandlePool<MogeGLShader> shdr_pool;
    moge::HandlePool<MogeGLUniformArray> uary_pool;
    moge::HandlePool<MogeGLVBO> vbo_pool;
    moge::HandlePool<MogeGLTexture> tex_pool;
  };

  ResourcePool pool;
  MogeGLCtx ctx;

  void getPool(moge::HandlePool<MogeGLShader>* out_pool);
  void getPool(moge::HandlePool<MogeGLUniformArray>* out_pool);
  void getPool(moge::HandlePool<MogeGLVBO>* out_pool);
  void getPool(moge::HandlePool<MogeGLTexture>* out_pool);
};

void moge::gl::Context::ContextImpl::getPool(moge::HandlePool<MogeGLShader>* out_pool) {
  out_pool = &this->pool.shdr_pool;
}

void moge::gl::Context::ContextImpl::getPool(moge::HandlePool<MogeGLUniformArray>* out_pool) {
  out_pool = &this->pool.uary_pool;
}

void moge::gl::Context::ContextImpl::getPool(moge::HandlePool<MogeGLVBO>* out_pool) {
  out_pool = &this->pool.vbo_pool;
}

void moge::gl::Context::ContextImpl::getPool(moge::HandlePool<MogeGLTexture>* out_pool) {
  out_pool = &this->pool.tex_pool;
}

namespace moge {
namespace gl {
namespace detail {

template <typename HandleType, typename ObjectType>
void insertObject(Context& ctx, ObjectType& obj, HandleType& out);

template <typename ObjectType, typename HandleType>
ObjectType* getObject(Context& ctx, HandleType& handle);

template <typename ObjectType, typename HandleType>
void removeHandle(Context& ctx, HandleType& handle);

} // namespace detail
} // namespace gl
} // namespace moge

template <typename HandleType, typename ObjectType>
void moge::gl::detail::insertObject(moge::gl::Context& ctx, ObjectType& obj, HandleType& out) {
  moge::HandlePool<ObjectType>* pool = NULL;
  ctx.pimpl->getPool(pool);
  MOGE_ASSERT(pool);
  out.handle = pool->insertObject(obj);
}

template <typename ObjectType, typename HandleType>
ObjectType* moge::gl::detail::getObject(moge::gl::Context& ctx, HandleType& handle) {
  moge::HandlePool<ObjectType>* pool = NULL;
  ctx.pimpl->getPool(pool);
  MOGE_ASSERT(pool);
  return pool->getObject(handle.handle);
}

template <typename ObjectType, typename HandleType>
void moge::gl::detail::removeHandle(moge::gl::Context& ctx, HandleType& handle) {
  moge::HandlePool<ObjectType>* pool = NULL;
  ctx.pimpl->getPool(pool);
  MOGE_ASSERT(pool);
  pool->removeHandle(handle.handle);
}

moge::gl::Context moge::gl::createContext(moge::gl::ContextDecl& decl) {
  MOGE_ASSERT(decl.maxShaders);
  MOGE_ASSERT(decl.maxUniformArrays);
  MOGE_ASSERT(decl.maxVertexBuffers);
  MOGE_ASSERT(decl.maxTextures);

  Context ctx;

  ctx.pimpl = static_cast<moge::gl::Context::ContextImpl*>(MOGE_MALLOC(sizeof(moge::gl::Context::ContextImpl)));
  MOGE_ASSERT(ctx.pimpl);

  moge::HandlePool<MogeGLShader> shdr_pool = {};
  moge::HandlePool<MogeGLUniformArray> uary_pool = {};
  moge::HandlePool<MogeGLVBO> vbo_pool = {};
  moge::HandlePool<MogeGLTexture> tex_pool = {};

  ctx.pimpl->pool.shdr_pool = shdr_pool;
  ctx.pimpl->pool.uary_pool = uary_pool;
  ctx.pimpl->pool.vbo_pool = vbo_pool;
  ctx.pimpl->pool.tex_pool = tex_pool;

  MogeGLCtx glctx = {};
#if defined(MOGE_USE_DIRECT3D11)
  MOGE_ASSERT(decl.hwnd);
  glctx.hwnd = static_cast<HWND>(decl.hwnd);
#else
  MOGE_ASSERT(decl.hwnd == NULL);
#endif

  ctx.pimpl->ctx = glctx;

  ctx.pimpl->pool.shdr_pool.createHandlePool(decl.maxShaders);
  ctx.pimpl->pool.uary_pool.createHandlePool(decl.maxUniformArrays);
  ctx.pimpl->pool.vbo_pool.createHandlePool(decl.maxVertexBuffers);
  ctx.pimpl->pool.tex_pool.createHandlePool(decl.maxTextures);
  MOGE_GL_CREATE_CONTEXT(ctx.pimpl->ctx);

  return ctx;
}

void moge::gl::destroyContext(Context& ctx) {
  MOGE_ASSERT(ctx.pimpl);

  ctx.pimpl->pool.tex_pool.destroyHandlePool();
  ctx.pimpl->pool.vbo_pool.destroyHandlePool();
  ctx.pimpl->pool.uary_pool.destroyHandlePool();
  ctx.pimpl->pool.shdr_pool.destroyHandlePool();
  MOGE_GL_DESTROY_CONTEXT(ctx.pimpl->ctx);

  MOGE_FREE(ctx.pimpl);

  ctx.pimpl = NULL;
}

void moge::gl::resizeBackBuffer(moge::gl::Context& ctx) {
  MOGE_ASSERT(ctx.pimpl);

  MOGE_GL_RESIZE_BACK_BUFFER(ctx);
}

moge::gl::Shader moge::gl::createShader(moge::gl::Context& ctx, moge::gl::ShaderDecl& decl) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLShader shdr = {};
  MOGE_GL_CREATE_SHADER(ctx, shdr, decl);
  moge::gl::Shader handle;
  moge::gl::detail::insertObject(ctx, shdr, handle);
  return handle;
}

void moge::gl::destroyShader(moge::gl::Context& ctx, moge::gl::Shader shdr) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLShader* p = moge::gl::detail::getObject<MogeGLShader>(ctx, shdr);
  MOGE_GL_DESTROY_SHADER(*p);
  moge::gl::detail::removeHandle<MogeGLShader>(ctx, shdr);
}

moge::gl::UniformArray moge::gl::createUniformArray(moge::gl::Context& ctx, moge::gl::Shader& shdr, moge::gl::UniformArrayDecl& decl) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLShader* p = moge::gl::detail::getObject<MogeGLShader>(ctx, shdr);
  MogeGLUniformArray uary = {};
  MOGE_GL_CREATE_UNIFORM_ARRAY(ctx, *p, uary, decl);
  moge::gl::UniformArray handle;
  moge::gl::detail::insertObject(ctx, uary, handle);
  return handle;
}

void moge::gl::destroyUniformArray(moge::gl::Context& ctx, moge::gl::UniformArray& uary) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLUniformArray* p = moge::gl::detail::getObject<MogeGLUniformArray>(ctx, uary);
  MOGE_GL_DESTROY_UNIFORM_ARRAY(*p);
  moge::gl::detail::removeHandle<MogeGLUniformArray>(ctx, uary);
}

void moge::gl::updateUniformArray(moge::gl::Context& ctx, moge::gl::UniformArray& uary, const void* data, size_t num_bytes) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLUniformArray* p = moge::gl::detail::getObject<MogeGLUniformArray>(ctx, uary);
  MOGE_GL_UPDATE_UNIFORM_ARRAY(ctx, *p, data, num_bytes);
}

moge::gl::VertexBuffer moge::gl::createVertexBuffer(moge::gl::Context& ctx, uint32_t num_bytes) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLVBO vbo = {};
  MOGE_GL_CREATE_VERTEX_BUFFER(ctx, vbo, num_bytes);
  moge::gl::VertexBuffer handle;
  moge::gl::detail::insertObject(ctx, vbo, handle);
  return handle;
}

void moge::gl::destroyVertexBuffer(moge::gl::Context& ctx, moge::gl::VertexBuffer& vbo) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLVBO* p = moge::gl::detail::getObject<MogeGLVBO>(ctx, vbo);
  MOGE_GL_DESTROY_VERTEX_BUFFER(*p);
  moge::gl::detail::removeHandle<MogeGLVBO>(ctx, vbo);
}

void moge::gl::updateVertexBuffer(moge::gl::Context& ctx, moge::gl::VertexBuffer& vbo, const void* vertices, size_t num_bytes) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLVBO* p = moge::gl::detail::getObject<MogeGLVBO>(ctx, vbo);
  MOGE_GL_UPDATE_VERTEX_BUFFER(ctx, *p, vertices, num_bytes);
}

moge::gl::Texture moge::gl::createTexture(moge::gl::Context& ctx, moge::gl::TextureDecl& decl) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLTexture tex = {};
  MOGE_GL_CREATE_TEXTURE(ctx, tex, decl);
  moge::gl::Texture handle;
  moge::gl::detail::insertObject(ctx, tex, handle);
  return handle;
}

void moge::gl::destroyTexture(moge::gl::Context& ctx, moge::gl::Texture& tex) {
  MOGE_ASSERT(ctx.pimpl);

  MogeGLTexture* p = moge::gl::detail::getObject<MogeGLTexture>(ctx, tex);
  MOGE_GL_DESTROY_TEXTURE(*p);
  moge::gl::detail::removeHandle<MogeGLTexture>(ctx, tex);
}
