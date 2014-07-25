// Copyright 2014 The Azul3D Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
//
// This source file was automatically generated using glwrap.

#include "gl.h"

typedef void (*__glwrap_func_ptr)(void);

#if defined(__WIN32) || defined(__WIN64)
	typedef void* HMODULE;
	typedef int (*FARPROC)(void);
	typedef int (*PROC)(void);

	//extern PROC wglGetProcAddress(const char* name);
	extern HMODULE LoadLibraryA(const char* name);
	extern FARPROC GetProcAddress(HMODULE, const char*);

	HMODULE glwrap_OpenGL32;


	typedef PROC (*__glwrap_PFNWGLGETPROCADDRESS)(const char*);
	__glwrap_PFNWGLGETPROCADDRESS __glwrap_wglGetProcAddressPtr;
	inline PROC __glwrap_wglGetProcAddress(const char* name) {
		if(__glwrap_wglGetProcAddressPtr == NULL) {
			if(glwrap_OpenGL32 == NULL) {
				glwrap_OpenGL32 = LoadLibraryA("opengl32.dll");
			}
			__glwrap_wglGetProcAddressPtr = (__glwrap_PFNWGLGETPROCADDRESS)GetProcAddress(glwrap_OpenGL32, "wglGetProcAddress");
		}
		return __glwrap_wglGetProcAddressPtr(name);
	}

#elif defined(__linux) || defined(__unix) || defined(__posix)
	// See http://dri.freedesktop.org/wiki/glXGetProcAddressNeverReturnsNULL
	//
	// glXGetProcAddressARB is *required* to be statically defined in libGL,
	// but glXGetProcAddress is not, and will fail to be found in nvidia's
	// libGL
	extern __glwrap_func_ptr glXGetProcAddressARB(const GLubyte * procName);

#elif defined(__APPLE__)
	// Todo: OS X support.
#endif

inline __glwrap_func_ptr gl_wrap_get_pointer(const char* name) {
	#if defined(__WIN32) || defined(__WIN64)
		void* ptr = __glwrap_wglGetProcAddress(name);
		intptr_t iptr = (intptr_t)ptr;

		if(iptr == 0 || iptr == 1 || iptr == 2 || iptr == 3 || iptr == -1) {
			// Could be a core function, then.

			// No need for this: because it's done in wglGetProcAddress()
			//if(glwrap_OpenGL32 == NULL) {
			//	glwrap_OpenGL32 = LoadLibraryA("opengl32.dll");
			//}
			return (__glwrap_func_ptr)GetProcAddress(glwrap_OpenGL32, name);
		}

		return ptr;

	#elif defined(__linux) || defined(__unix) || defined(__posix)
		return glXGetProcAddressARB(name);

	#elif defined(__APPLE__)
		// Todo: OS X support.
	#endif
}

// Function definition for each appropriate OpenGL function.
//
// If the pointer in the context for the function is null; it is loaded
// immedietly (as such this is effectively lazy-loading).
void gl_wrap_context_glActiveTexture(gl_wrap_context* ctx, GLenum texture) {
	if(ctx->glActiveTextureProc == NULL) {
		ctx->glActiveTextureProc = (PFNGLACTIVETEXTUREPROC)gl_wrap_get_pointer("glActiveTexture");
	}
	ctx->glActiveTextureProc(texture);
};
void gl_wrap_context_glAttachShader(gl_wrap_context* ctx, GLuint program, GLuint shader) {
	if(ctx->glAttachShaderProc == NULL) {
		ctx->glAttachShaderProc = (PFNGLATTACHSHADERPROC)gl_wrap_get_pointer("glAttachShader");
	}
	ctx->glAttachShaderProc(program, shader);
};
void gl_wrap_context_glBindAttribLocation(gl_wrap_context* ctx, GLuint program, GLuint index, GLchar* name) {
	if(ctx->glBindAttribLocationProc == NULL) {
		ctx->glBindAttribLocationProc = (PFNGLBINDATTRIBLOCATIONPROC)gl_wrap_get_pointer("glBindAttribLocation");
	}
	ctx->glBindAttribLocationProc(program, index, name);
};
void gl_wrap_context_glBindBuffer(gl_wrap_context* ctx, GLenum target, GLuint buffer) {
	if(ctx->glBindBufferProc == NULL) {
		ctx->glBindBufferProc = (PFNGLBINDBUFFERPROC)gl_wrap_get_pointer("glBindBuffer");
	}
	ctx->glBindBufferProc(target, buffer);
};
void gl_wrap_context_glBindFramebuffer(gl_wrap_context* ctx, GLenum target, GLuint framebuffer) {
	if(ctx->glBindFramebufferProc == NULL) {
		ctx->glBindFramebufferProc = (PFNGLBINDFRAMEBUFFERPROC)gl_wrap_get_pointer("glBindFramebuffer");
	}
	ctx->glBindFramebufferProc(target, framebuffer);
};
void gl_wrap_context_glBindRenderbuffer(gl_wrap_context* ctx, GLenum target, GLuint renderbuffer) {
	if(ctx->glBindRenderbufferProc == NULL) {
		ctx->glBindRenderbufferProc = (PFNGLBINDRENDERBUFFERPROC)gl_wrap_get_pointer("glBindRenderbuffer");
	}
	ctx->glBindRenderbufferProc(target, renderbuffer);
};
void gl_wrap_context_glBindTexture(gl_wrap_context* ctx, GLenum target, GLuint texture) {
	if(ctx->glBindTextureProc == NULL) {
		ctx->glBindTextureProc = (PFNGLBINDTEXTUREPROC)gl_wrap_get_pointer("glBindTexture");
	}
	ctx->glBindTextureProc(target, texture);
};
void gl_wrap_context_glBlendColor(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	if(ctx->glBlendColorProc == NULL) {
		ctx->glBlendColorProc = (PFNGLBLENDCOLORPROC)gl_wrap_get_pointer("glBlendColor");
	}
	ctx->glBlendColorProc(red, green, blue, alpha);
};
void gl_wrap_context_glBlendEquation(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glBlendEquationProc == NULL) {
		ctx->glBlendEquationProc = (PFNGLBLENDEQUATIONPROC)gl_wrap_get_pointer("glBlendEquation");
	}
	ctx->glBlendEquationProc(mode);
};
void gl_wrap_context_glBlendEquationSeparate(gl_wrap_context* ctx, GLenum modeRGB, GLenum modeAlpha) {
	if(ctx->glBlendEquationSeparateProc == NULL) {
		ctx->glBlendEquationSeparateProc = (PFNGLBLENDEQUATIONSEPARATEPROC)gl_wrap_get_pointer("glBlendEquationSeparate");
	}
	ctx->glBlendEquationSeparateProc(modeRGB, modeAlpha);
};
void gl_wrap_context_glBlendFunc(gl_wrap_context* ctx, GLenum sfactor, GLenum dfactor) {
	if(ctx->glBlendFuncProc == NULL) {
		ctx->glBlendFuncProc = (PFNGLBLENDFUNCPROC)gl_wrap_get_pointer("glBlendFunc");
	}
	ctx->glBlendFuncProc(sfactor, dfactor);
};
void gl_wrap_context_glBlendFuncSeparate(gl_wrap_context* ctx, GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
	if(ctx->glBlendFuncSeparateProc == NULL) {
		ctx->glBlendFuncSeparateProc = (PFNGLBLENDFUNCSEPARATEPROC)gl_wrap_get_pointer("glBlendFuncSeparate");
	}
	ctx->glBlendFuncSeparateProc(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
};
void gl_wrap_context_glBufferData(gl_wrap_context* ctx, GLenum target, GLsizeiptr size, void* data, GLenum usage) {
	if(ctx->glBufferDataProc == NULL) {
		ctx->glBufferDataProc = (PFNGLBUFFERDATAPROC)gl_wrap_get_pointer("glBufferData");
	}
	ctx->glBufferDataProc(target, size, data, usage);
};
void gl_wrap_context_glBufferSubData(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr size, void* data) {
	if(ctx->glBufferSubDataProc == NULL) {
		ctx->glBufferSubDataProc = (PFNGLBUFFERSUBDATAPROC)gl_wrap_get_pointer("glBufferSubData");
	}
	ctx->glBufferSubDataProc(target, offset, size, data);
};
GLenum gl_wrap_context_glCheckFramebufferStatus(gl_wrap_context* ctx, GLenum target) {
	if(ctx->glCheckFramebufferStatusProc == NULL) {
		ctx->glCheckFramebufferStatusProc = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)gl_wrap_get_pointer("glCheckFramebufferStatus");
	}
	return ctx->glCheckFramebufferStatusProc(target);
};
void gl_wrap_context_glClear(gl_wrap_context* ctx, GLbitfield mask) {
	if(ctx->glClearProc == NULL) {
		ctx->glClearProc = (PFNGLCLEARPROC)gl_wrap_get_pointer("glClear");
	}
	ctx->glClearProc(mask);
};
void gl_wrap_context_glClearColor(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	if(ctx->glClearColorProc == NULL) {
		ctx->glClearColorProc = (PFNGLCLEARCOLORPROC)gl_wrap_get_pointer("glClearColor");
	}
	ctx->glClearColorProc(red, green, blue, alpha);
};
void gl_wrap_context_glClearDepthf(gl_wrap_context* ctx, GLfloat d) {
	if(ctx->glClearDepthfProc == NULL) {
		ctx->glClearDepthfProc = (PFNGLCLEARDEPTHFPROC)gl_wrap_get_pointer("glClearDepthf");
	}
	ctx->glClearDepthfProc(d);
};
void gl_wrap_context_glClearStencil(gl_wrap_context* ctx, GLint s) {
	if(ctx->glClearStencilProc == NULL) {
		ctx->glClearStencilProc = (PFNGLCLEARSTENCILPROC)gl_wrap_get_pointer("glClearStencil");
	}
	ctx->glClearStencilProc(s);
};
void gl_wrap_context_glColorMask(gl_wrap_context* ctx, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
	if(ctx->glColorMaskProc == NULL) {
		ctx->glColorMaskProc = (PFNGLCOLORMASKPROC)gl_wrap_get_pointer("glColorMask");
	}
	ctx->glColorMaskProc(red, green, blue, alpha);
};
void gl_wrap_context_glCompileShader(gl_wrap_context* ctx, GLuint shader) {
	if(ctx->glCompileShaderProc == NULL) {
		ctx->glCompileShaderProc = (PFNGLCOMPILESHADERPROC)gl_wrap_get_pointer("glCompileShader");
	}
	ctx->glCompileShaderProc(shader);
};
void gl_wrap_context_glCompressedTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexImage2DProc == NULL) {
		ctx->glCompressedTexImage2DProc = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)gl_wrap_get_pointer("glCompressedTexImage2D");
	}
	ctx->glCompressedTexImage2DProc(target, level, internalformat, width, height, border, imageSize, data);
};
void gl_wrap_context_glCompressedTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexSubImage2DProc == NULL) {
		ctx->glCompressedTexSubImage2DProc = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)gl_wrap_get_pointer("glCompressedTexSubImage2D");
	}
	ctx->glCompressedTexSubImage2DProc(target, level, xoffset, yoffset, width, height, format, imageSize, data);
};
void gl_wrap_context_glCopyTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
	if(ctx->glCopyTexImage2DProc == NULL) {
		ctx->glCopyTexImage2DProc = (PFNGLCOPYTEXIMAGE2DPROC)gl_wrap_get_pointer("glCopyTexImage2D");
	}
	ctx->glCopyTexImage2DProc(target, level, internalformat, x, y, width, height, border);
};
void gl_wrap_context_glCopyTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glCopyTexSubImage2DProc == NULL) {
		ctx->glCopyTexSubImage2DProc = (PFNGLCOPYTEXSUBIMAGE2DPROC)gl_wrap_get_pointer("glCopyTexSubImage2D");
	}
	ctx->glCopyTexSubImage2DProc(target, level, xoffset, yoffset, x, y, width, height);
};
GLuint gl_wrap_context_glCreateProgram(gl_wrap_context* ctx) {
	if(ctx->glCreateProgramProc == NULL) {
		ctx->glCreateProgramProc = (PFNGLCREATEPROGRAMPROC)gl_wrap_get_pointer("glCreateProgram");
	}
	return ctx->glCreateProgramProc();
};
GLuint gl_wrap_context_glCreateShader(gl_wrap_context* ctx, GLenum type) {
	if(ctx->glCreateShaderProc == NULL) {
		ctx->glCreateShaderProc = (PFNGLCREATESHADERPROC)gl_wrap_get_pointer("glCreateShader");
	}
	return ctx->glCreateShaderProc(type);
};
void gl_wrap_context_glCullFace(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glCullFaceProc == NULL) {
		ctx->glCullFaceProc = (PFNGLCULLFACEPROC)gl_wrap_get_pointer("glCullFace");
	}
	ctx->glCullFaceProc(mode);
};
void gl_wrap_context_glDeleteBuffers(gl_wrap_context* ctx, GLsizei n, GLuint* buffers) {
	if(ctx->glDeleteBuffersProc == NULL) {
		ctx->glDeleteBuffersProc = (PFNGLDELETEBUFFERSPROC)gl_wrap_get_pointer("glDeleteBuffers");
	}
	ctx->glDeleteBuffersProc(n, buffers);
};
void gl_wrap_context_glDeleteFramebuffers(gl_wrap_context* ctx, GLsizei n, GLuint* framebuffers) {
	if(ctx->glDeleteFramebuffersProc == NULL) {
		ctx->glDeleteFramebuffersProc = (PFNGLDELETEFRAMEBUFFERSPROC)gl_wrap_get_pointer("glDeleteFramebuffers");
	}
	ctx->glDeleteFramebuffersProc(n, framebuffers);
};
void gl_wrap_context_glDeleteProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glDeleteProgramProc == NULL) {
		ctx->glDeleteProgramProc = (PFNGLDELETEPROGRAMPROC)gl_wrap_get_pointer("glDeleteProgram");
	}
	ctx->glDeleteProgramProc(program);
};
void gl_wrap_context_glDeleteRenderbuffers(gl_wrap_context* ctx, GLsizei n, GLuint* renderbuffers) {
	if(ctx->glDeleteRenderbuffersProc == NULL) {
		ctx->glDeleteRenderbuffersProc = (PFNGLDELETERENDERBUFFERSPROC)gl_wrap_get_pointer("glDeleteRenderbuffers");
	}
	ctx->glDeleteRenderbuffersProc(n, renderbuffers);
};
void gl_wrap_context_glDeleteShader(gl_wrap_context* ctx, GLuint shader) {
	if(ctx->glDeleteShaderProc == NULL) {
		ctx->glDeleteShaderProc = (PFNGLDELETESHADERPROC)gl_wrap_get_pointer("glDeleteShader");
	}
	ctx->glDeleteShaderProc(shader);
};
void gl_wrap_context_glDeleteTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures) {
	if(ctx->glDeleteTexturesProc == NULL) {
		ctx->glDeleteTexturesProc = (PFNGLDELETETEXTURESPROC)gl_wrap_get_pointer("glDeleteTextures");
	}
	ctx->glDeleteTexturesProc(n, textures);
};
void gl_wrap_context_glDepthFunc(gl_wrap_context* ctx, GLenum func) {
	if(ctx->glDepthFuncProc == NULL) {
		ctx->glDepthFuncProc = (PFNGLDEPTHFUNCPROC)gl_wrap_get_pointer("glDepthFunc");
	}
	ctx->glDepthFuncProc(func);
};
void gl_wrap_context_glDepthMask(gl_wrap_context* ctx, GLboolean flag) {
	if(ctx->glDepthMaskProc == NULL) {
		ctx->glDepthMaskProc = (PFNGLDEPTHMASKPROC)gl_wrap_get_pointer("glDepthMask");
	}
	ctx->glDepthMaskProc(flag);
};
void gl_wrap_context_glDepthRangef(gl_wrap_context* ctx, GLfloat n, GLfloat f) {
	if(ctx->glDepthRangefProc == NULL) {
		ctx->glDepthRangefProc = (PFNGLDEPTHRANGEFPROC)gl_wrap_get_pointer("glDepthRangef");
	}
	ctx->glDepthRangefProc(n, f);
};
void gl_wrap_context_glDetachShader(gl_wrap_context* ctx, GLuint program, GLuint shader) {
	if(ctx->glDetachShaderProc == NULL) {
		ctx->glDetachShaderProc = (PFNGLDETACHSHADERPROC)gl_wrap_get_pointer("glDetachShader");
	}
	ctx->glDetachShaderProc(program, shader);
};
void gl_wrap_context_glDisable(gl_wrap_context* ctx, GLenum cap) {
	if(ctx->glDisableProc == NULL) {
		ctx->glDisableProc = (PFNGLDISABLEPROC)gl_wrap_get_pointer("glDisable");
	}
	ctx->glDisableProc(cap);
};
void gl_wrap_context_glDisableVertexAttribArray(gl_wrap_context* ctx, GLuint index) {
	if(ctx->glDisableVertexAttribArrayProc == NULL) {
		ctx->glDisableVertexAttribArrayProc = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)gl_wrap_get_pointer("glDisableVertexAttribArray");
	}
	ctx->glDisableVertexAttribArrayProc(index);
};
void gl_wrap_context_glDrawArrays(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count) {
	if(ctx->glDrawArraysProc == NULL) {
		ctx->glDrawArraysProc = (PFNGLDRAWARRAYSPROC)gl_wrap_get_pointer("glDrawArrays");
	}
	ctx->glDrawArraysProc(mode, first, count);
};
void gl_wrap_context_glDrawElements(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices) {
	if(ctx->glDrawElementsProc == NULL) {
		ctx->glDrawElementsProc = (PFNGLDRAWELEMENTSPROC)gl_wrap_get_pointer("glDrawElements");
	}
	ctx->glDrawElementsProc(mode, count, type, indices);
};
void gl_wrap_context_glEnable(gl_wrap_context* ctx, GLenum cap) {
	if(ctx->glEnableProc == NULL) {
		ctx->glEnableProc = (PFNGLENABLEPROC)gl_wrap_get_pointer("glEnable");
	}
	ctx->glEnableProc(cap);
};
void gl_wrap_context_glEnableVertexAttribArray(gl_wrap_context* ctx, GLuint index) {
	if(ctx->glEnableVertexAttribArrayProc == NULL) {
		ctx->glEnableVertexAttribArrayProc = (PFNGLENABLEVERTEXATTRIBARRAYPROC)gl_wrap_get_pointer("glEnableVertexAttribArray");
	}
	ctx->glEnableVertexAttribArrayProc(index);
};
void gl_wrap_context_glFinish(gl_wrap_context* ctx) {
	if(ctx->glFinishProc == NULL) {
		ctx->glFinishProc = (PFNGLFINISHPROC)gl_wrap_get_pointer("glFinish");
	}
	ctx->glFinishProc();
};
void gl_wrap_context_glFlush(gl_wrap_context* ctx) {
	if(ctx->glFlushProc == NULL) {
		ctx->glFlushProc = (PFNGLFLUSHPROC)gl_wrap_get_pointer("glFlush");
	}
	ctx->glFlushProc();
};
void gl_wrap_context_glFramebufferRenderbuffer(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
	if(ctx->glFramebufferRenderbufferProc == NULL) {
		ctx->glFramebufferRenderbufferProc = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)gl_wrap_get_pointer("glFramebufferRenderbuffer");
	}
	ctx->glFramebufferRenderbufferProc(target, attachment, renderbuffertarget, renderbuffer);
};
void gl_wrap_context_glFramebufferTexture2D(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
	if(ctx->glFramebufferTexture2DProc == NULL) {
		ctx->glFramebufferTexture2DProc = (PFNGLFRAMEBUFFERTEXTURE2DPROC)gl_wrap_get_pointer("glFramebufferTexture2D");
	}
	ctx->glFramebufferTexture2DProc(target, attachment, textarget, texture, level);
};
void gl_wrap_context_glFrontFace(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glFrontFaceProc == NULL) {
		ctx->glFrontFaceProc = (PFNGLFRONTFACEPROC)gl_wrap_get_pointer("glFrontFace");
	}
	ctx->glFrontFaceProc(mode);
};
void gl_wrap_context_glGenBuffers(gl_wrap_context* ctx, GLsizei n, GLuint* buffers) {
	if(ctx->glGenBuffersProc == NULL) {
		ctx->glGenBuffersProc = (PFNGLGENBUFFERSPROC)gl_wrap_get_pointer("glGenBuffers");
	}
	ctx->glGenBuffersProc(n, buffers);
};
void gl_wrap_context_glGenerateMipmap(gl_wrap_context* ctx, GLenum target) {
	if(ctx->glGenerateMipmapProc == NULL) {
		ctx->glGenerateMipmapProc = (PFNGLGENERATEMIPMAPPROC)gl_wrap_get_pointer("glGenerateMipmap");
	}
	ctx->glGenerateMipmapProc(target);
};
void gl_wrap_context_glGenFramebuffers(gl_wrap_context* ctx, GLsizei n, GLuint* framebuffers) {
	if(ctx->glGenFramebuffersProc == NULL) {
		ctx->glGenFramebuffersProc = (PFNGLGENFRAMEBUFFERSPROC)gl_wrap_get_pointer("glGenFramebuffers");
	}
	ctx->glGenFramebuffersProc(n, framebuffers);
};
void gl_wrap_context_glGenRenderbuffers(gl_wrap_context* ctx, GLsizei n, GLuint* renderbuffers) {
	if(ctx->glGenRenderbuffersProc == NULL) {
		ctx->glGenRenderbuffersProc = (PFNGLGENRENDERBUFFERSPROC)gl_wrap_get_pointer("glGenRenderbuffers");
	}
	ctx->glGenRenderbuffersProc(n, renderbuffers);
};
void gl_wrap_context_glGenTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures) {
	if(ctx->glGenTexturesProc == NULL) {
		ctx->glGenTexturesProc = (PFNGLGENTEXTURESPROC)gl_wrap_get_pointer("glGenTextures");
	}
	ctx->glGenTexturesProc(n, textures);
};
void gl_wrap_context_glGetActiveAttrib(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) {
	if(ctx->glGetActiveAttribProc == NULL) {
		ctx->glGetActiveAttribProc = (PFNGLGETACTIVEATTRIBPROC)gl_wrap_get_pointer("glGetActiveAttrib");
	}
	ctx->glGetActiveAttribProc(program, index, bufSize, length, size, type, name);
};
void gl_wrap_context_glGetActiveUniform(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) {
	if(ctx->glGetActiveUniformProc == NULL) {
		ctx->glGetActiveUniformProc = (PFNGLGETACTIVEUNIFORMPROC)gl_wrap_get_pointer("glGetActiveUniform");
	}
	ctx->glGetActiveUniformProc(program, index, bufSize, length, size, type, name);
};
void gl_wrap_context_glGetAttachedShaders(gl_wrap_context* ctx, GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders) {
	if(ctx->glGetAttachedShadersProc == NULL) {
		ctx->glGetAttachedShadersProc = (PFNGLGETATTACHEDSHADERSPROC)gl_wrap_get_pointer("glGetAttachedShaders");
	}
	ctx->glGetAttachedShadersProc(program, maxCount, count, shaders);
};
GLint gl_wrap_context_glGetAttribLocation(gl_wrap_context* ctx, GLuint program, GLchar* name) {
	if(ctx->glGetAttribLocationProc == NULL) {
		ctx->glGetAttribLocationProc = (PFNGLGETATTRIBLOCATIONPROC)gl_wrap_get_pointer("glGetAttribLocation");
	}
	return ctx->glGetAttribLocationProc(program, name);
};
void gl_wrap_context_glGetBooleanv(gl_wrap_context* ctx, GLenum pname, GLboolean* data) {
	if(ctx->glGetBooleanvProc == NULL) {
		ctx->glGetBooleanvProc = (PFNGLGETBOOLEANVPROC)gl_wrap_get_pointer("glGetBooleanv");
	}
	ctx->glGetBooleanvProc(pname, data);
};
void gl_wrap_context_glGetBufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetBufferParameterivProc == NULL) {
		ctx->glGetBufferParameterivProc = (PFNGLGETBUFFERPARAMETERIVPROC)gl_wrap_get_pointer("glGetBufferParameteriv");
	}
	ctx->glGetBufferParameterivProc(target, pname, params);
};
GLenum gl_wrap_context_glGetError(gl_wrap_context* ctx) {
	if(ctx->glGetErrorProc == NULL) {
		ctx->glGetErrorProc = (PFNGLGETERRORPROC)gl_wrap_get_pointer("glGetError");
	}
	return ctx->glGetErrorProc();
};
void gl_wrap_context_glGetFloatv(gl_wrap_context* ctx, GLenum pname, GLfloat* data) {
	if(ctx->glGetFloatvProc == NULL) {
		ctx->glGetFloatvProc = (PFNGLGETFLOATVPROC)gl_wrap_get_pointer("glGetFloatv");
	}
	ctx->glGetFloatvProc(pname, data);
};
void gl_wrap_context_glGetFramebufferAttachmentParameteriv(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum pname, GLint* params) {
	if(ctx->glGetFramebufferAttachmentParameterivProc == NULL) {
		ctx->glGetFramebufferAttachmentParameterivProc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)gl_wrap_get_pointer("glGetFramebufferAttachmentParameteriv");
	}
	ctx->glGetFramebufferAttachmentParameterivProc(target, attachment, pname, params);
};
void gl_wrap_context_glGetIntegerv(gl_wrap_context* ctx, GLenum pname, GLint* data) {
	if(ctx->glGetIntegervProc == NULL) {
		ctx->glGetIntegervProc = (PFNGLGETINTEGERVPROC)gl_wrap_get_pointer("glGetIntegerv");
	}
	ctx->glGetIntegervProc(pname, data);
};
void gl_wrap_context_glGetProgramiv(gl_wrap_context* ctx, GLuint program, GLenum pname, GLint* params) {
	if(ctx->glGetProgramivProc == NULL) {
		ctx->glGetProgramivProc = (PFNGLGETPROGRAMIVPROC)gl_wrap_get_pointer("glGetProgramiv");
	}
	ctx->glGetProgramivProc(program, pname, params);
};
void gl_wrap_context_glGetProgramInfoLog(gl_wrap_context* ctx, GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
	if(ctx->glGetProgramInfoLogProc == NULL) {
		ctx->glGetProgramInfoLogProc = (PFNGLGETPROGRAMINFOLOGPROC)gl_wrap_get_pointer("glGetProgramInfoLog");
	}
	ctx->glGetProgramInfoLogProc(program, bufSize, length, infoLog);
};
void gl_wrap_context_glGetRenderbufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetRenderbufferParameterivProc == NULL) {
		ctx->glGetRenderbufferParameterivProc = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)gl_wrap_get_pointer("glGetRenderbufferParameteriv");
	}
	ctx->glGetRenderbufferParameterivProc(target, pname, params);
};
void gl_wrap_context_glGetShaderiv(gl_wrap_context* ctx, GLuint shader, GLenum pname, GLint* params) {
	if(ctx->glGetShaderivProc == NULL) {
		ctx->glGetShaderivProc = (PFNGLGETSHADERIVPROC)gl_wrap_get_pointer("glGetShaderiv");
	}
	ctx->glGetShaderivProc(shader, pname, params);
};
void gl_wrap_context_glGetShaderInfoLog(gl_wrap_context* ctx, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
	if(ctx->glGetShaderInfoLogProc == NULL) {
		ctx->glGetShaderInfoLogProc = (PFNGLGETSHADERINFOLOGPROC)gl_wrap_get_pointer("glGetShaderInfoLog");
	}
	ctx->glGetShaderInfoLogProc(shader, bufSize, length, infoLog);
};
void gl_wrap_context_glGetShaderPrecisionFormat(gl_wrap_context* ctx, GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) {
	if(ctx->glGetShaderPrecisionFormatProc == NULL) {
		ctx->glGetShaderPrecisionFormatProc = (PFNGLGETSHADERPRECISIONFORMATPROC)gl_wrap_get_pointer("glGetShaderPrecisionFormat");
	}
	ctx->glGetShaderPrecisionFormatProc(shadertype, precisiontype, range, precision);
};
void gl_wrap_context_glGetShaderSource(gl_wrap_context* ctx, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source) {
	if(ctx->glGetShaderSourceProc == NULL) {
		ctx->glGetShaderSourceProc = (PFNGLGETSHADERSOURCEPROC)gl_wrap_get_pointer("glGetShaderSource");
	}
	ctx->glGetShaderSourceProc(shader, bufSize, length, source);
};
GLubyte* gl_wrap_context_glGetString(gl_wrap_context* ctx, GLenum name) {
	if(ctx->glGetStringProc == NULL) {
		ctx->glGetStringProc = (PFNGLGETSTRINGPROC)gl_wrap_get_pointer("glGetString");
	}
	return ctx->glGetStringProc(name);
};
void gl_wrap_context_glGetTexParameterfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params) {
	if(ctx->glGetTexParameterfvProc == NULL) {
		ctx->glGetTexParameterfvProc = (PFNGLGETTEXPARAMETERFVPROC)gl_wrap_get_pointer("glGetTexParameterfv");
	}
	ctx->glGetTexParameterfvProc(target, pname, params);
};
void gl_wrap_context_glGetTexParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetTexParameterivProc == NULL) {
		ctx->glGetTexParameterivProc = (PFNGLGETTEXPARAMETERIVPROC)gl_wrap_get_pointer("glGetTexParameteriv");
	}
	ctx->glGetTexParameterivProc(target, pname, params);
};
void gl_wrap_context_glGetUniformfv(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat* params) {
	if(ctx->glGetUniformfvProc == NULL) {
		ctx->glGetUniformfvProc = (PFNGLGETUNIFORMFVPROC)gl_wrap_get_pointer("glGetUniformfv");
	}
	ctx->glGetUniformfvProc(program, location, params);
};
void gl_wrap_context_glGetUniformiv(gl_wrap_context* ctx, GLuint program, GLint location, GLint* params) {
	if(ctx->glGetUniformivProc == NULL) {
		ctx->glGetUniformivProc = (PFNGLGETUNIFORMIVPROC)gl_wrap_get_pointer("glGetUniformiv");
	}
	ctx->glGetUniformivProc(program, location, params);
};
GLint gl_wrap_context_glGetUniformLocation(gl_wrap_context* ctx, GLuint program, GLchar* name) {
	if(ctx->glGetUniformLocationProc == NULL) {
		ctx->glGetUniformLocationProc = (PFNGLGETUNIFORMLOCATIONPROC)gl_wrap_get_pointer("glGetUniformLocation");
	}
	return ctx->glGetUniformLocationProc(program, name);
};
void gl_wrap_context_glGetVertexAttribfv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLfloat* params) {
	if(ctx->glGetVertexAttribfvProc == NULL) {
		ctx->glGetVertexAttribfvProc = (PFNGLGETVERTEXATTRIBFVPROC)gl_wrap_get_pointer("glGetVertexAttribfv");
	}
	ctx->glGetVertexAttribfvProc(index, pname, params);
};
void gl_wrap_context_glGetVertexAttribiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLint* params) {
	if(ctx->glGetVertexAttribivProc == NULL) {
		ctx->glGetVertexAttribivProc = (PFNGLGETVERTEXATTRIBIVPROC)gl_wrap_get_pointer("glGetVertexAttribiv");
	}
	ctx->glGetVertexAttribivProc(index, pname, params);
};
void gl_wrap_context_glGetVertexAttribPointerv(gl_wrap_context* ctx, GLuint index, GLenum pname, void** pointer) {
	if(ctx->glGetVertexAttribPointervProc == NULL) {
		ctx->glGetVertexAttribPointervProc = (PFNGLGETVERTEXATTRIBPOINTERVPROC)gl_wrap_get_pointer("glGetVertexAttribPointerv");
	}
	ctx->glGetVertexAttribPointervProc(index, pname, pointer);
};
void gl_wrap_context_glHint(gl_wrap_context* ctx, GLenum target, GLenum mode) {
	if(ctx->glHintProc == NULL) {
		ctx->glHintProc = (PFNGLHINTPROC)gl_wrap_get_pointer("glHint");
	}
	ctx->glHintProc(target, mode);
};
GLboolean gl_wrap_context_glIsBuffer(gl_wrap_context* ctx, GLuint buffer) {
	if(ctx->glIsBufferProc == NULL) {
		ctx->glIsBufferProc = (PFNGLISBUFFERPROC)gl_wrap_get_pointer("glIsBuffer");
	}
	return ctx->glIsBufferProc(buffer);
};
GLboolean gl_wrap_context_glIsEnabled(gl_wrap_context* ctx, GLenum cap) {
	if(ctx->glIsEnabledProc == NULL) {
		ctx->glIsEnabledProc = (PFNGLISENABLEDPROC)gl_wrap_get_pointer("glIsEnabled");
	}
	return ctx->glIsEnabledProc(cap);
};
GLboolean gl_wrap_context_glIsFramebuffer(gl_wrap_context* ctx, GLuint framebuffer) {
	if(ctx->glIsFramebufferProc == NULL) {
		ctx->glIsFramebufferProc = (PFNGLISFRAMEBUFFERPROC)gl_wrap_get_pointer("glIsFramebuffer");
	}
	return ctx->glIsFramebufferProc(framebuffer);
};
GLboolean gl_wrap_context_glIsProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glIsProgramProc == NULL) {
		ctx->glIsProgramProc = (PFNGLISPROGRAMPROC)gl_wrap_get_pointer("glIsProgram");
	}
	return ctx->glIsProgramProc(program);
};
GLboolean gl_wrap_context_glIsRenderbuffer(gl_wrap_context* ctx, GLuint renderbuffer) {
	if(ctx->glIsRenderbufferProc == NULL) {
		ctx->glIsRenderbufferProc = (PFNGLISRENDERBUFFERPROC)gl_wrap_get_pointer("glIsRenderbuffer");
	}
	return ctx->glIsRenderbufferProc(renderbuffer);
};
GLboolean gl_wrap_context_glIsShader(gl_wrap_context* ctx, GLuint shader) {
	if(ctx->glIsShaderProc == NULL) {
		ctx->glIsShaderProc = (PFNGLISSHADERPROC)gl_wrap_get_pointer("glIsShader");
	}
	return ctx->glIsShaderProc(shader);
};
GLboolean gl_wrap_context_glIsTexture(gl_wrap_context* ctx, GLuint texture) {
	if(ctx->glIsTextureProc == NULL) {
		ctx->glIsTextureProc = (PFNGLISTEXTUREPROC)gl_wrap_get_pointer("glIsTexture");
	}
	return ctx->glIsTextureProc(texture);
};
void gl_wrap_context_glLineWidth(gl_wrap_context* ctx, GLfloat width) {
	if(ctx->glLineWidthProc == NULL) {
		ctx->glLineWidthProc = (PFNGLLINEWIDTHPROC)gl_wrap_get_pointer("glLineWidth");
	}
	ctx->glLineWidthProc(width);
};
void gl_wrap_context_glLinkProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glLinkProgramProc == NULL) {
		ctx->glLinkProgramProc = (PFNGLLINKPROGRAMPROC)gl_wrap_get_pointer("glLinkProgram");
	}
	ctx->glLinkProgramProc(program);
};
void gl_wrap_context_glPixelStorei(gl_wrap_context* ctx, GLenum pname, GLint param) {
	if(ctx->glPixelStoreiProc == NULL) {
		ctx->glPixelStoreiProc = (PFNGLPIXELSTOREIPROC)gl_wrap_get_pointer("glPixelStorei");
	}
	ctx->glPixelStoreiProc(pname, param);
};
void gl_wrap_context_glPolygonOffset(gl_wrap_context* ctx, GLfloat factor, GLfloat units) {
	if(ctx->glPolygonOffsetProc == NULL) {
		ctx->glPolygonOffsetProc = (PFNGLPOLYGONOFFSETPROC)gl_wrap_get_pointer("glPolygonOffset");
	}
	ctx->glPolygonOffsetProc(factor, units);
};
void gl_wrap_context_glReadPixels(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) {
	if(ctx->glReadPixelsProc == NULL) {
		ctx->glReadPixelsProc = (PFNGLREADPIXELSPROC)gl_wrap_get_pointer("glReadPixels");
	}
	ctx->glReadPixelsProc(x, y, width, height, format, type, pixels);
};
void gl_wrap_context_glReleaseShaderCompiler(gl_wrap_context* ctx) {
	if(ctx->glReleaseShaderCompilerProc == NULL) {
		ctx->glReleaseShaderCompilerProc = (PFNGLRELEASESHADERCOMPILERPROC)gl_wrap_get_pointer("glReleaseShaderCompiler");
	}
	ctx->glReleaseShaderCompilerProc();
};
void gl_wrap_context_glRenderbufferStorage(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
	if(ctx->glRenderbufferStorageProc == NULL) {
		ctx->glRenderbufferStorageProc = (PFNGLRENDERBUFFERSTORAGEPROC)gl_wrap_get_pointer("glRenderbufferStorage");
	}
	ctx->glRenderbufferStorageProc(target, internalformat, width, height);
};
void gl_wrap_context_glSampleCoverage(gl_wrap_context* ctx, GLfloat value, GLboolean invert) {
	if(ctx->glSampleCoverageProc == NULL) {
		ctx->glSampleCoverageProc = (PFNGLSAMPLECOVERAGEPROC)gl_wrap_get_pointer("glSampleCoverage");
	}
	ctx->glSampleCoverageProc(value, invert);
};
void gl_wrap_context_glScissor(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glScissorProc == NULL) {
		ctx->glScissorProc = (PFNGLSCISSORPROC)gl_wrap_get_pointer("glScissor");
	}
	ctx->glScissorProc(x, y, width, height);
};
void gl_wrap_context_glShaderBinary(gl_wrap_context* ctx, GLsizei count, GLuint* shaders, GLenum binaryformat, void* binary, GLsizei length) {
	if(ctx->glShaderBinaryProc == NULL) {
		ctx->glShaderBinaryProc = (PFNGLSHADERBINARYPROC)gl_wrap_get_pointer("glShaderBinary");
	}
	ctx->glShaderBinaryProc(count, shaders, binaryformat, binary, length);
};
void gl_wrap_context_glShaderSource(gl_wrap_context* ctx, GLuint shader, GLsizei count, GLchar** string, GLint* length) {
	if(ctx->glShaderSourceProc == NULL) {
		ctx->glShaderSourceProc = (PFNGLSHADERSOURCEPROC)gl_wrap_get_pointer("glShaderSource");
	}
	ctx->glShaderSourceProc(shader, count, string, length);
};
void gl_wrap_context_glStencilFunc(gl_wrap_context* ctx, GLenum func, GLint ref, GLuint mask) {
	if(ctx->glStencilFuncProc == NULL) {
		ctx->glStencilFuncProc = (PFNGLSTENCILFUNCPROC)gl_wrap_get_pointer("glStencilFunc");
	}
	ctx->glStencilFuncProc(func, ref, mask);
};
void gl_wrap_context_glStencilFuncSeparate(gl_wrap_context* ctx, GLenum face, GLenum func, GLint ref, GLuint mask) {
	if(ctx->glStencilFuncSeparateProc == NULL) {
		ctx->glStencilFuncSeparateProc = (PFNGLSTENCILFUNCSEPARATEPROC)gl_wrap_get_pointer("glStencilFuncSeparate");
	}
	ctx->glStencilFuncSeparateProc(face, func, ref, mask);
};
void gl_wrap_context_glStencilMask(gl_wrap_context* ctx, GLuint mask) {
	if(ctx->glStencilMaskProc == NULL) {
		ctx->glStencilMaskProc = (PFNGLSTENCILMASKPROC)gl_wrap_get_pointer("glStencilMask");
	}
	ctx->glStencilMaskProc(mask);
};
void gl_wrap_context_glStencilMaskSeparate(gl_wrap_context* ctx, GLenum face, GLuint mask) {
	if(ctx->glStencilMaskSeparateProc == NULL) {
		ctx->glStencilMaskSeparateProc = (PFNGLSTENCILMASKSEPARATEPROC)gl_wrap_get_pointer("glStencilMaskSeparate");
	}
	ctx->glStencilMaskSeparateProc(face, mask);
};
void gl_wrap_context_glStencilOp(gl_wrap_context* ctx, GLenum fail, GLenum zfail, GLenum zpass) {
	if(ctx->glStencilOpProc == NULL) {
		ctx->glStencilOpProc = (PFNGLSTENCILOPPROC)gl_wrap_get_pointer("glStencilOp");
	}
	ctx->glStencilOpProc(fail, zfail, zpass);
};
void gl_wrap_context_glStencilOpSeparate(gl_wrap_context* ctx, GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
	if(ctx->glStencilOpSeparateProc == NULL) {
		ctx->glStencilOpSeparateProc = (PFNGLSTENCILOPSEPARATEPROC)gl_wrap_get_pointer("glStencilOpSeparate");
	}
	ctx->glStencilOpSeparateProc(face, sfail, dpfail, dppass);
};
void gl_wrap_context_glTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexImage2DProc == NULL) {
		ctx->glTexImage2DProc = (PFNGLTEXIMAGE2DPROC)gl_wrap_get_pointer("glTexImage2D");
	}
	ctx->glTexImage2DProc(target, level, internalformat, width, height, border, format, type, pixels);
};
void gl_wrap_context_glTexParameterf(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat param) {
	if(ctx->glTexParameterfProc == NULL) {
		ctx->glTexParameterfProc = (PFNGLTEXPARAMETERFPROC)gl_wrap_get_pointer("glTexParameterf");
	}
	ctx->glTexParameterfProc(target, pname, param);
};
void gl_wrap_context_glTexParameterfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params) {
	if(ctx->glTexParameterfvProc == NULL) {
		ctx->glTexParameterfvProc = (PFNGLTEXPARAMETERFVPROC)gl_wrap_get_pointer("glTexParameterfv");
	}
	ctx->glTexParameterfvProc(target, pname, params);
};
void gl_wrap_context_glTexParameteri(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param) {
	if(ctx->glTexParameteriProc == NULL) {
		ctx->glTexParameteriProc = (PFNGLTEXPARAMETERIPROC)gl_wrap_get_pointer("glTexParameteri");
	}
	ctx->glTexParameteriProc(target, pname, param);
};
void gl_wrap_context_glTexParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glTexParameterivProc == NULL) {
		ctx->glTexParameterivProc = (PFNGLTEXPARAMETERIVPROC)gl_wrap_get_pointer("glTexParameteriv");
	}
	ctx->glTexParameterivProc(target, pname, params);
};
void gl_wrap_context_glTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexSubImage2DProc == NULL) {
		ctx->glTexSubImage2DProc = (PFNGLTEXSUBIMAGE2DPROC)gl_wrap_get_pointer("glTexSubImage2D");
	}
	ctx->glTexSubImage2DProc(target, level, xoffset, yoffset, width, height, format, type, pixels);
};
void gl_wrap_context_glUniform1f(gl_wrap_context* ctx, GLint location, GLfloat v0) {
	if(ctx->glUniform1fProc == NULL) {
		ctx->glUniform1fProc = (PFNGLUNIFORM1FPROC)gl_wrap_get_pointer("glUniform1f");
	}
	ctx->glUniform1fProc(location, v0);
};
void gl_wrap_context_glUniform1fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glUniform1fvProc == NULL) {
		ctx->glUniform1fvProc = (PFNGLUNIFORM1FVPROC)gl_wrap_get_pointer("glUniform1fv");
	}
	ctx->glUniform1fvProc(location, count, value);
};
void gl_wrap_context_glUniform1i(gl_wrap_context* ctx, GLint location, GLint v0) {
	if(ctx->glUniform1iProc == NULL) {
		ctx->glUniform1iProc = (PFNGLUNIFORM1IPROC)gl_wrap_get_pointer("glUniform1i");
	}
	ctx->glUniform1iProc(location, v0);
};
void gl_wrap_context_glUniform1iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value) {
	if(ctx->glUniform1ivProc == NULL) {
		ctx->glUniform1ivProc = (PFNGLUNIFORM1IVPROC)gl_wrap_get_pointer("glUniform1iv");
	}
	ctx->glUniform1ivProc(location, count, value);
};
void gl_wrap_context_glUniform2f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1) {
	if(ctx->glUniform2fProc == NULL) {
		ctx->glUniform2fProc = (PFNGLUNIFORM2FPROC)gl_wrap_get_pointer("glUniform2f");
	}
	ctx->glUniform2fProc(location, v0, v1);
};
void gl_wrap_context_glUniform2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glUniform2fvProc == NULL) {
		ctx->glUniform2fvProc = (PFNGLUNIFORM2FVPROC)gl_wrap_get_pointer("glUniform2fv");
	}
	ctx->glUniform2fvProc(location, count, value);
};
void gl_wrap_context_glUniform2i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1) {
	if(ctx->glUniform2iProc == NULL) {
		ctx->glUniform2iProc = (PFNGLUNIFORM2IPROC)gl_wrap_get_pointer("glUniform2i");
	}
	ctx->glUniform2iProc(location, v0, v1);
};
void gl_wrap_context_glUniform2iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value) {
	if(ctx->glUniform2ivProc == NULL) {
		ctx->glUniform2ivProc = (PFNGLUNIFORM2IVPROC)gl_wrap_get_pointer("glUniform2iv");
	}
	ctx->glUniform2ivProc(location, count, value);
};
void gl_wrap_context_glUniform3f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
	if(ctx->glUniform3fProc == NULL) {
		ctx->glUniform3fProc = (PFNGLUNIFORM3FPROC)gl_wrap_get_pointer("glUniform3f");
	}
	ctx->glUniform3fProc(location, v0, v1, v2);
};
void gl_wrap_context_glUniform3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glUniform3fvProc == NULL) {
		ctx->glUniform3fvProc = (PFNGLUNIFORM3FVPROC)gl_wrap_get_pointer("glUniform3fv");
	}
	ctx->glUniform3fvProc(location, count, value);
};
void gl_wrap_context_glUniform3i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1, GLint v2) {
	if(ctx->glUniform3iProc == NULL) {
		ctx->glUniform3iProc = (PFNGLUNIFORM3IPROC)gl_wrap_get_pointer("glUniform3i");
	}
	ctx->glUniform3iProc(location, v0, v1, v2);
};
void gl_wrap_context_glUniform3iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value) {
	if(ctx->glUniform3ivProc == NULL) {
		ctx->glUniform3ivProc = (PFNGLUNIFORM3IVPROC)gl_wrap_get_pointer("glUniform3iv");
	}
	ctx->glUniform3ivProc(location, count, value);
};
void gl_wrap_context_glUniform4f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
	if(ctx->glUniform4fProc == NULL) {
		ctx->glUniform4fProc = (PFNGLUNIFORM4FPROC)gl_wrap_get_pointer("glUniform4f");
	}
	ctx->glUniform4fProc(location, v0, v1, v2, v3);
};
void gl_wrap_context_glUniform4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glUniform4fvProc == NULL) {
		ctx->glUniform4fvProc = (PFNGLUNIFORM4FVPROC)gl_wrap_get_pointer("glUniform4fv");
	}
	ctx->glUniform4fvProc(location, count, value);
};
void gl_wrap_context_glUniform4i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
	if(ctx->glUniform4iProc == NULL) {
		ctx->glUniform4iProc = (PFNGLUNIFORM4IPROC)gl_wrap_get_pointer("glUniform4i");
	}
	ctx->glUniform4iProc(location, v0, v1, v2, v3);
};
void gl_wrap_context_glUniform4iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value) {
	if(ctx->glUniform4ivProc == NULL) {
		ctx->glUniform4ivProc = (PFNGLUNIFORM4IVPROC)gl_wrap_get_pointer("glUniform4iv");
	}
	ctx->glUniform4ivProc(location, count, value);
};
void gl_wrap_context_glUniformMatrix2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix2fvProc == NULL) {
		ctx->glUniformMatrix2fvProc = (PFNGLUNIFORMMATRIX2FVPROC)gl_wrap_get_pointer("glUniformMatrix2fv");
	}
	ctx->glUniformMatrix2fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix3fvProc == NULL) {
		ctx->glUniformMatrix3fvProc = (PFNGLUNIFORMMATRIX3FVPROC)gl_wrap_get_pointer("glUniformMatrix3fv");
	}
	ctx->glUniformMatrix3fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix4fvProc == NULL) {
		ctx->glUniformMatrix4fvProc = (PFNGLUNIFORMMATRIX4FVPROC)gl_wrap_get_pointer("glUniformMatrix4fv");
	}
	ctx->glUniformMatrix4fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUseProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glUseProgramProc == NULL) {
		ctx->glUseProgramProc = (PFNGLUSEPROGRAMPROC)gl_wrap_get_pointer("glUseProgram");
	}
	ctx->glUseProgramProc(program);
};
void gl_wrap_context_glValidateProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glValidateProgramProc == NULL) {
		ctx->glValidateProgramProc = (PFNGLVALIDATEPROGRAMPROC)gl_wrap_get_pointer("glValidateProgram");
	}
	ctx->glValidateProgramProc(program);
};
void gl_wrap_context_glVertexAttrib1f(gl_wrap_context* ctx, GLuint index, GLfloat x) {
	if(ctx->glVertexAttrib1fProc == NULL) {
		ctx->glVertexAttrib1fProc = (PFNGLVERTEXATTRIB1FPROC)gl_wrap_get_pointer("glVertexAttrib1f");
	}
	ctx->glVertexAttrib1fProc(index, x);
};
void gl_wrap_context_glVertexAttrib1fv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glVertexAttrib1fvProc == NULL) {
		ctx->glVertexAttrib1fvProc = (PFNGLVERTEXATTRIB1FVPROC)gl_wrap_get_pointer("glVertexAttrib1fv");
	}
	ctx->glVertexAttrib1fvProc(index, v);
};
void gl_wrap_context_glVertexAttrib2f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y) {
	if(ctx->glVertexAttrib2fProc == NULL) {
		ctx->glVertexAttrib2fProc = (PFNGLVERTEXATTRIB2FPROC)gl_wrap_get_pointer("glVertexAttrib2f");
	}
	ctx->glVertexAttrib2fProc(index, x, y);
};
void gl_wrap_context_glVertexAttrib2fv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glVertexAttrib2fvProc == NULL) {
		ctx->glVertexAttrib2fvProc = (PFNGLVERTEXATTRIB2FVPROC)gl_wrap_get_pointer("glVertexAttrib2fv");
	}
	ctx->glVertexAttrib2fvProc(index, v);
};
void gl_wrap_context_glVertexAttrib3f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z) {
	if(ctx->glVertexAttrib3fProc == NULL) {
		ctx->glVertexAttrib3fProc = (PFNGLVERTEXATTRIB3FPROC)gl_wrap_get_pointer("glVertexAttrib3f");
	}
	ctx->glVertexAttrib3fProc(index, x, y, z);
};
void gl_wrap_context_glVertexAttrib3fv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glVertexAttrib3fvProc == NULL) {
		ctx->glVertexAttrib3fvProc = (PFNGLVERTEXATTRIB3FVPROC)gl_wrap_get_pointer("glVertexAttrib3fv");
	}
	ctx->glVertexAttrib3fvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	if(ctx->glVertexAttrib4fProc == NULL) {
		ctx->glVertexAttrib4fProc = (PFNGLVERTEXATTRIB4FPROC)gl_wrap_get_pointer("glVertexAttrib4f");
	}
	ctx->glVertexAttrib4fProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttrib4fv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glVertexAttrib4fvProc == NULL) {
		ctx->glVertexAttrib4fvProc = (PFNGLVERTEXATTRIB4FVPROC)gl_wrap_get_pointer("glVertexAttrib4fv");
	}
	ctx->glVertexAttrib4fvProc(index, v);
};
void gl_wrap_context_glVertexAttribPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void* pointer) {
	if(ctx->glVertexAttribPointerProc == NULL) {
		ctx->glVertexAttribPointerProc = (PFNGLVERTEXATTRIBPOINTERPROC)gl_wrap_get_pointer("glVertexAttribPointer");
	}
	ctx->glVertexAttribPointerProc(index, size, type, normalized, stride, pointer);
};
void gl_wrap_context_glViewport(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glViewportProc == NULL) {
		ctx->glViewportProc = (PFNGLVIEWPORTPROC)gl_wrap_get_pointer("glViewport");
	}
	ctx->glViewportProc(x, y, width, height);
};
void gl_wrap_context_glReadBuffer(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glReadBufferProc == NULL) {
		ctx->glReadBufferProc = (PFNGLREADBUFFERPROC)gl_wrap_get_pointer("glReadBuffer");
	}
	ctx->glReadBufferProc(mode);
};
void gl_wrap_context_glDrawRangeElements(gl_wrap_context* ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices) {
	if(ctx->glDrawRangeElementsProc == NULL) {
		ctx->glDrawRangeElementsProc = (PFNGLDRAWRANGEELEMENTSPROC)gl_wrap_get_pointer("glDrawRangeElements");
	}
	ctx->glDrawRangeElementsProc(mode, start, end, count, type, indices);
};
void gl_wrap_context_glTexImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexImage3DProc == NULL) {
		ctx->glTexImage3DProc = (PFNGLTEXIMAGE3DPROC)gl_wrap_get_pointer("glTexImage3D");
	}
	ctx->glTexImage3DProc(target, level, internalformat, width, height, depth, border, format, type, pixels);
};
void gl_wrap_context_glTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexSubImage3DProc == NULL) {
		ctx->glTexSubImage3DProc = (PFNGLTEXSUBIMAGE3DPROC)gl_wrap_get_pointer("glTexSubImage3D");
	}
	ctx->glTexSubImage3DProc(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
};
void gl_wrap_context_glCopyTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glCopyTexSubImage3DProc == NULL) {
		ctx->glCopyTexSubImage3DProc = (PFNGLCOPYTEXSUBIMAGE3DPROC)gl_wrap_get_pointer("glCopyTexSubImage3D");
	}
	ctx->glCopyTexSubImage3DProc(target, level, xoffset, yoffset, zoffset, x, y, width, height);
};
void gl_wrap_context_glCompressedTexImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexImage3DProc == NULL) {
		ctx->glCompressedTexImage3DProc = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)gl_wrap_get_pointer("glCompressedTexImage3D");
	}
	ctx->glCompressedTexImage3DProc(target, level, internalformat, width, height, depth, border, imageSize, data);
};
void gl_wrap_context_glCompressedTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexSubImage3DProc == NULL) {
		ctx->glCompressedTexSubImage3DProc = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)gl_wrap_get_pointer("glCompressedTexSubImage3D");
	}
	ctx->glCompressedTexSubImage3DProc(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
};
void gl_wrap_context_glGenQueries(gl_wrap_context* ctx, GLsizei n, GLuint* ids) {
	if(ctx->glGenQueriesProc == NULL) {
		ctx->glGenQueriesProc = (PFNGLGENQUERIESPROC)gl_wrap_get_pointer("glGenQueries");
	}
	ctx->glGenQueriesProc(n, ids);
};
void gl_wrap_context_glDeleteQueries(gl_wrap_context* ctx, GLsizei n, GLuint* ids) {
	if(ctx->glDeleteQueriesProc == NULL) {
		ctx->glDeleteQueriesProc = (PFNGLDELETEQUERIESPROC)gl_wrap_get_pointer("glDeleteQueries");
	}
	ctx->glDeleteQueriesProc(n, ids);
};
GLboolean gl_wrap_context_glIsQuery(gl_wrap_context* ctx, GLuint id) {
	if(ctx->glIsQueryProc == NULL) {
		ctx->glIsQueryProc = (PFNGLISQUERYPROC)gl_wrap_get_pointer("glIsQuery");
	}
	return ctx->glIsQueryProc(id);
};
void gl_wrap_context_glBeginQuery(gl_wrap_context* ctx, GLenum target, GLuint id) {
	if(ctx->glBeginQueryProc == NULL) {
		ctx->glBeginQueryProc = (PFNGLBEGINQUERYPROC)gl_wrap_get_pointer("glBeginQuery");
	}
	ctx->glBeginQueryProc(target, id);
};
void gl_wrap_context_glEndQuery(gl_wrap_context* ctx, GLenum target) {
	if(ctx->glEndQueryProc == NULL) {
		ctx->glEndQueryProc = (PFNGLENDQUERYPROC)gl_wrap_get_pointer("glEndQuery");
	}
	ctx->glEndQueryProc(target);
};
void gl_wrap_context_glGetQueryiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetQueryivProc == NULL) {
		ctx->glGetQueryivProc = (PFNGLGETQUERYIVPROC)gl_wrap_get_pointer("glGetQueryiv");
	}
	ctx->glGetQueryivProc(target, pname, params);
};
void gl_wrap_context_glGetQueryObjectuiv(gl_wrap_context* ctx, GLuint id, GLenum pname, GLuint* params) {
	if(ctx->glGetQueryObjectuivProc == NULL) {
		ctx->glGetQueryObjectuivProc = (PFNGLGETQUERYOBJECTUIVPROC)gl_wrap_get_pointer("glGetQueryObjectuiv");
	}
	ctx->glGetQueryObjectuivProc(id, pname, params);
};
GLboolean gl_wrap_context_glUnmapBuffer(gl_wrap_context* ctx, GLenum target) {
	if(ctx->glUnmapBufferProc == NULL) {
		ctx->glUnmapBufferProc = (PFNGLUNMAPBUFFERPROC)gl_wrap_get_pointer("glUnmapBuffer");
	}
	return ctx->glUnmapBufferProc(target);
};
void gl_wrap_context_glGetBufferPointerv(gl_wrap_context* ctx, GLenum target, GLenum pname, void** params) {
	if(ctx->glGetBufferPointervProc == NULL) {
		ctx->glGetBufferPointervProc = (PFNGLGETBUFFERPOINTERVPROC)gl_wrap_get_pointer("glGetBufferPointerv");
	}
	ctx->glGetBufferPointervProc(target, pname, params);
};
void gl_wrap_context_glDrawBuffers(gl_wrap_context* ctx, GLsizei n, GLenum* bufs) {
	if(ctx->glDrawBuffersProc == NULL) {
		ctx->glDrawBuffersProc = (PFNGLDRAWBUFFERSPROC)gl_wrap_get_pointer("glDrawBuffers");
	}
	ctx->glDrawBuffersProc(n, bufs);
};
void gl_wrap_context_glUniformMatrix2x3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix2x3fvProc == NULL) {
		ctx->glUniformMatrix2x3fvProc = (PFNGLUNIFORMMATRIX2X3FVPROC)gl_wrap_get_pointer("glUniformMatrix2x3fv");
	}
	ctx->glUniformMatrix2x3fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3x2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix3x2fvProc == NULL) {
		ctx->glUniformMatrix3x2fvProc = (PFNGLUNIFORMMATRIX3X2FVPROC)gl_wrap_get_pointer("glUniformMatrix3x2fv");
	}
	ctx->glUniformMatrix3x2fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix2x4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix2x4fvProc == NULL) {
		ctx->glUniformMatrix2x4fvProc = (PFNGLUNIFORMMATRIX2X4FVPROC)gl_wrap_get_pointer("glUniformMatrix2x4fv");
	}
	ctx->glUniformMatrix2x4fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4x2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix4x2fvProc == NULL) {
		ctx->glUniformMatrix4x2fvProc = (PFNGLUNIFORMMATRIX4X2FVPROC)gl_wrap_get_pointer("glUniformMatrix4x2fv");
	}
	ctx->glUniformMatrix4x2fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3x4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix3x4fvProc == NULL) {
		ctx->glUniformMatrix3x4fvProc = (PFNGLUNIFORMMATRIX3X4FVPROC)gl_wrap_get_pointer("glUniformMatrix3x4fv");
	}
	ctx->glUniformMatrix3x4fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4x3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix4x3fvProc == NULL) {
		ctx->glUniformMatrix4x3fvProc = (PFNGLUNIFORMMATRIX4X3FVPROC)gl_wrap_get_pointer("glUniformMatrix4x3fv");
	}
	ctx->glUniformMatrix4x3fvProc(location, count, transpose, value);
};
void gl_wrap_context_glBlitFramebuffer(gl_wrap_context* ctx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
	if(ctx->glBlitFramebufferProc == NULL) {
		ctx->glBlitFramebufferProc = (PFNGLBLITFRAMEBUFFERPROC)gl_wrap_get_pointer("glBlitFramebuffer");
	}
	ctx->glBlitFramebufferProc(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
};
void gl_wrap_context_glRenderbufferStorageMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
	if(ctx->glRenderbufferStorageMultisampleProc == NULL) {
		ctx->glRenderbufferStorageMultisampleProc = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)gl_wrap_get_pointer("glRenderbufferStorageMultisample");
	}
	ctx->glRenderbufferStorageMultisampleProc(target, samples, internalformat, width, height);
};
void gl_wrap_context_glFramebufferTextureLayer(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
	if(ctx->glFramebufferTextureLayerProc == NULL) {
		ctx->glFramebufferTextureLayerProc = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)gl_wrap_get_pointer("glFramebufferTextureLayer");
	}
	ctx->glFramebufferTextureLayerProc(target, attachment, texture, level, layer);
};
void gl_wrap_context_glMapBufferRange(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
	if(ctx->glMapBufferRangeProc == NULL) {
		ctx->glMapBufferRangeProc = (PFNGLMAPBUFFERRANGEPROC)gl_wrap_get_pointer("glMapBufferRange");
	}
	ctx->glMapBufferRangeProc(target, offset, length, access);
};
void gl_wrap_context_glFlushMappedBufferRange(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr length) {
	if(ctx->glFlushMappedBufferRangeProc == NULL) {
		ctx->glFlushMappedBufferRangeProc = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)gl_wrap_get_pointer("glFlushMappedBufferRange");
	}
	ctx->glFlushMappedBufferRangeProc(target, offset, length);
};
void gl_wrap_context_glBindVertexArray(gl_wrap_context* ctx, GLuint array) {
	if(ctx->glBindVertexArrayProc == NULL) {
		ctx->glBindVertexArrayProc = (PFNGLBINDVERTEXARRAYPROC)gl_wrap_get_pointer("glBindVertexArray");
	}
	ctx->glBindVertexArrayProc(array);
};
void gl_wrap_context_glDeleteVertexArrays(gl_wrap_context* ctx, GLsizei n, GLuint* arrays) {
	if(ctx->glDeleteVertexArraysProc == NULL) {
		ctx->glDeleteVertexArraysProc = (PFNGLDELETEVERTEXARRAYSPROC)gl_wrap_get_pointer("glDeleteVertexArrays");
	}
	ctx->glDeleteVertexArraysProc(n, arrays);
};
void gl_wrap_context_glGenVertexArrays(gl_wrap_context* ctx, GLsizei n, GLuint* arrays) {
	if(ctx->glGenVertexArraysProc == NULL) {
		ctx->glGenVertexArraysProc = (PFNGLGENVERTEXARRAYSPROC)gl_wrap_get_pointer("glGenVertexArrays");
	}
	ctx->glGenVertexArraysProc(n, arrays);
};
GLboolean gl_wrap_context_glIsVertexArray(gl_wrap_context* ctx, GLuint array) {
	if(ctx->glIsVertexArrayProc == NULL) {
		ctx->glIsVertexArrayProc = (PFNGLISVERTEXARRAYPROC)gl_wrap_get_pointer("glIsVertexArray");
	}
	return ctx->glIsVertexArrayProc(array);
};
void gl_wrap_context_glGetIntegeri_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLint* data) {
	if(ctx->glGetIntegeri_vProc == NULL) {
		ctx->glGetIntegeri_vProc = (PFNGLGETINTEGERI_VPROC)gl_wrap_get_pointer("glGetIntegeri_v");
	}
	ctx->glGetIntegeri_vProc(target, index, data);
};
void gl_wrap_context_glBeginTransformFeedback(gl_wrap_context* ctx, GLenum primitiveMode) {
	if(ctx->glBeginTransformFeedbackProc == NULL) {
		ctx->glBeginTransformFeedbackProc = (PFNGLBEGINTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glBeginTransformFeedback");
	}
	ctx->glBeginTransformFeedbackProc(primitiveMode);
};
void gl_wrap_context_glEndTransformFeedback(gl_wrap_context* ctx) {
	if(ctx->glEndTransformFeedbackProc == NULL) {
		ctx->glEndTransformFeedbackProc = (PFNGLENDTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glEndTransformFeedback");
	}
	ctx->glEndTransformFeedbackProc();
};
void gl_wrap_context_glBindBufferRange(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
	if(ctx->glBindBufferRangeProc == NULL) {
		ctx->glBindBufferRangeProc = (PFNGLBINDBUFFERRANGEPROC)gl_wrap_get_pointer("glBindBufferRange");
	}
	ctx->glBindBufferRangeProc(target, index, buffer, offset, size);
};
void gl_wrap_context_glBindBufferBase(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint buffer) {
	if(ctx->glBindBufferBaseProc == NULL) {
		ctx->glBindBufferBaseProc = (PFNGLBINDBUFFERBASEPROC)gl_wrap_get_pointer("glBindBufferBase");
	}
	ctx->glBindBufferBaseProc(target, index, buffer);
};
void gl_wrap_context_glTransformFeedbackVaryings(gl_wrap_context* ctx, GLuint program, GLsizei count, GLchar** varyings, GLenum bufferMode) {
	if(ctx->glTransformFeedbackVaryingsProc == NULL) {
		ctx->glTransformFeedbackVaryingsProc = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)gl_wrap_get_pointer("glTransformFeedbackVaryings");
	}
	ctx->glTransformFeedbackVaryingsProc(program, count, varyings, bufferMode);
};
void gl_wrap_context_glGetTransformFeedbackVarying(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) {
	if(ctx->glGetTransformFeedbackVaryingProc == NULL) {
		ctx->glGetTransformFeedbackVaryingProc = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)gl_wrap_get_pointer("glGetTransformFeedbackVarying");
	}
	ctx->glGetTransformFeedbackVaryingProc(program, index, bufSize, length, size, type, name);
};
void gl_wrap_context_glVertexAttribIPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glVertexAttribIPointerProc == NULL) {
		ctx->glVertexAttribIPointerProc = (PFNGLVERTEXATTRIBIPOINTERPROC)gl_wrap_get_pointer("glVertexAttribIPointer");
	}
	ctx->glVertexAttribIPointerProc(index, size, type, stride, pointer);
};
void gl_wrap_context_glGetVertexAttribIiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLint* params) {
	if(ctx->glGetVertexAttribIivProc == NULL) {
		ctx->glGetVertexAttribIivProc = (PFNGLGETVERTEXATTRIBIIVPROC)gl_wrap_get_pointer("glGetVertexAttribIiv");
	}
	ctx->glGetVertexAttribIivProc(index, pname, params);
};
void gl_wrap_context_glGetVertexAttribIuiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLuint* params) {
	if(ctx->glGetVertexAttribIuivProc == NULL) {
		ctx->glGetVertexAttribIuivProc = (PFNGLGETVERTEXATTRIBIUIVPROC)gl_wrap_get_pointer("glGetVertexAttribIuiv");
	}
	ctx->glGetVertexAttribIuivProc(index, pname, params);
};
void gl_wrap_context_glVertexAttribI4i(gl_wrap_context* ctx, GLuint index, GLint x, GLint y, GLint z, GLint w) {
	if(ctx->glVertexAttribI4iProc == NULL) {
		ctx->glVertexAttribI4iProc = (PFNGLVERTEXATTRIBI4IPROC)gl_wrap_get_pointer("glVertexAttribI4i");
	}
	ctx->glVertexAttribI4iProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttribI4ui(gl_wrap_context* ctx, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
	if(ctx->glVertexAttribI4uiProc == NULL) {
		ctx->glVertexAttribI4uiProc = (PFNGLVERTEXATTRIBI4UIPROC)gl_wrap_get_pointer("glVertexAttribI4ui");
	}
	ctx->glVertexAttribI4uiProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttribI4iv(gl_wrap_context* ctx, GLuint index, GLint* v) {
	if(ctx->glVertexAttribI4ivProc == NULL) {
		ctx->glVertexAttribI4ivProc = (PFNGLVERTEXATTRIBI4IVPROC)gl_wrap_get_pointer("glVertexAttribI4iv");
	}
	ctx->glVertexAttribI4ivProc(index, v);
};
void gl_wrap_context_glVertexAttribI4uiv(gl_wrap_context* ctx, GLuint index, GLuint* v) {
	if(ctx->glVertexAttribI4uivProc == NULL) {
		ctx->glVertexAttribI4uivProc = (PFNGLVERTEXATTRIBI4UIVPROC)gl_wrap_get_pointer("glVertexAttribI4uiv");
	}
	ctx->glVertexAttribI4uivProc(index, v);
};
void gl_wrap_context_glGetUniformuiv(gl_wrap_context* ctx, GLuint program, GLint location, GLuint* params) {
	if(ctx->glGetUniformuivProc == NULL) {
		ctx->glGetUniformuivProc = (PFNGLGETUNIFORMUIVPROC)gl_wrap_get_pointer("glGetUniformuiv");
	}
	ctx->glGetUniformuivProc(program, location, params);
};
GLint gl_wrap_context_glGetFragDataLocation(gl_wrap_context* ctx, GLuint program, GLchar* name) {
	if(ctx->glGetFragDataLocationProc == NULL) {
		ctx->glGetFragDataLocationProc = (PFNGLGETFRAGDATALOCATIONPROC)gl_wrap_get_pointer("glGetFragDataLocation");
	}
	return ctx->glGetFragDataLocationProc(program, name);
};
void gl_wrap_context_glUniform1ui(gl_wrap_context* ctx, GLint location, GLuint v0) {
	if(ctx->glUniform1uiProc == NULL) {
		ctx->glUniform1uiProc = (PFNGLUNIFORM1UIPROC)gl_wrap_get_pointer("glUniform1ui");
	}
	ctx->glUniform1uiProc(location, v0);
};
void gl_wrap_context_glUniform2ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1) {
	if(ctx->glUniform2uiProc == NULL) {
		ctx->glUniform2uiProc = (PFNGLUNIFORM2UIPROC)gl_wrap_get_pointer("glUniform2ui");
	}
	ctx->glUniform2uiProc(location, v0, v1);
};
void gl_wrap_context_glUniform3ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1, GLuint v2) {
	if(ctx->glUniform3uiProc == NULL) {
		ctx->glUniform3uiProc = (PFNGLUNIFORM3UIPROC)gl_wrap_get_pointer("glUniform3ui");
	}
	ctx->glUniform3uiProc(location, v0, v1, v2);
};
void gl_wrap_context_glUniform4ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
	if(ctx->glUniform4uiProc == NULL) {
		ctx->glUniform4uiProc = (PFNGLUNIFORM4UIPROC)gl_wrap_get_pointer("glUniform4ui");
	}
	ctx->glUniform4uiProc(location, v0, v1, v2, v3);
};
void gl_wrap_context_glUniform1uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glUniform1uivProc == NULL) {
		ctx->glUniform1uivProc = (PFNGLUNIFORM1UIVPROC)gl_wrap_get_pointer("glUniform1uiv");
	}
	ctx->glUniform1uivProc(location, count, value);
};
void gl_wrap_context_glUniform2uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glUniform2uivProc == NULL) {
		ctx->glUniform2uivProc = (PFNGLUNIFORM2UIVPROC)gl_wrap_get_pointer("glUniform2uiv");
	}
	ctx->glUniform2uivProc(location, count, value);
};
void gl_wrap_context_glUniform3uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glUniform3uivProc == NULL) {
		ctx->glUniform3uivProc = (PFNGLUNIFORM3UIVPROC)gl_wrap_get_pointer("glUniform3uiv");
	}
	ctx->glUniform3uivProc(location, count, value);
};
void gl_wrap_context_glUniform4uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glUniform4uivProc == NULL) {
		ctx->glUniform4uivProc = (PFNGLUNIFORM4UIVPROC)gl_wrap_get_pointer("glUniform4uiv");
	}
	ctx->glUniform4uivProc(location, count, value);
};
void gl_wrap_context_glClearBufferiv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLint* value) {
	if(ctx->glClearBufferivProc == NULL) {
		ctx->glClearBufferivProc = (PFNGLCLEARBUFFERIVPROC)gl_wrap_get_pointer("glClearBufferiv");
	}
	ctx->glClearBufferivProc(buffer, drawbuffer, value);
};
void gl_wrap_context_glClearBufferuiv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLuint* value) {
	if(ctx->glClearBufferuivProc == NULL) {
		ctx->glClearBufferuivProc = (PFNGLCLEARBUFFERUIVPROC)gl_wrap_get_pointer("glClearBufferuiv");
	}
	ctx->glClearBufferuivProc(buffer, drawbuffer, value);
};
void gl_wrap_context_glClearBufferfv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLfloat* value) {
	if(ctx->glClearBufferfvProc == NULL) {
		ctx->glClearBufferfvProc = (PFNGLCLEARBUFFERFVPROC)gl_wrap_get_pointer("glClearBufferfv");
	}
	ctx->glClearBufferfvProc(buffer, drawbuffer, value);
};
void gl_wrap_context_glClearBufferfi(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
	if(ctx->glClearBufferfiProc == NULL) {
		ctx->glClearBufferfiProc = (PFNGLCLEARBUFFERFIPROC)gl_wrap_get_pointer("glClearBufferfi");
	}
	ctx->glClearBufferfiProc(buffer, drawbuffer, depth, stencil);
};
GLubyte* gl_wrap_context_glGetStringi(gl_wrap_context* ctx, GLenum name, GLuint index) {
	if(ctx->glGetStringiProc == NULL) {
		ctx->glGetStringiProc = (PFNGLGETSTRINGIPROC)gl_wrap_get_pointer("glGetStringi");
	}
	return ctx->glGetStringiProc(name, index);
};
void gl_wrap_context_glCopyBufferSubData(gl_wrap_context* ctx, GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
	if(ctx->glCopyBufferSubDataProc == NULL) {
		ctx->glCopyBufferSubDataProc = (PFNGLCOPYBUFFERSUBDATAPROC)gl_wrap_get_pointer("glCopyBufferSubData");
	}
	ctx->glCopyBufferSubDataProc(readTarget, writeTarget, readOffset, writeOffset, size);
};
void gl_wrap_context_glGetUniformIndices(gl_wrap_context* ctx, GLuint program, GLsizei uniformCount, GLchar** uniformNames, GLuint* uniformIndices) {
	if(ctx->glGetUniformIndicesProc == NULL) {
		ctx->glGetUniformIndicesProc = (PFNGLGETUNIFORMINDICESPROC)gl_wrap_get_pointer("glGetUniformIndices");
	}
	ctx->glGetUniformIndicesProc(program, uniformCount, uniformNames, uniformIndices);
};
void gl_wrap_context_glGetActiveUniformsiv(gl_wrap_context* ctx, GLuint program, GLsizei uniformCount, GLuint* uniformIndices, GLenum pname, GLint* params) {
	if(ctx->glGetActiveUniformsivProc == NULL) {
		ctx->glGetActiveUniformsivProc = (PFNGLGETACTIVEUNIFORMSIVPROC)gl_wrap_get_pointer("glGetActiveUniformsiv");
	}
	ctx->glGetActiveUniformsivProc(program, uniformCount, uniformIndices, pname, params);
};
GLuint gl_wrap_context_glGetUniformBlockIndex(gl_wrap_context* ctx, GLuint program, GLchar* uniformBlockName) {
	if(ctx->glGetUniformBlockIndexProc == NULL) {
		ctx->glGetUniformBlockIndexProc = (PFNGLGETUNIFORMBLOCKINDEXPROC)gl_wrap_get_pointer("glGetUniformBlockIndex");
	}
	return ctx->glGetUniformBlockIndexProc(program, uniformBlockName);
};
void gl_wrap_context_glGetActiveUniformBlockiv(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params) {
	if(ctx->glGetActiveUniformBlockivProc == NULL) {
		ctx->glGetActiveUniformBlockivProc = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)gl_wrap_get_pointer("glGetActiveUniformBlockiv");
	}
	ctx->glGetActiveUniformBlockivProc(program, uniformBlockIndex, pname, params);
};
void gl_wrap_context_glGetActiveUniformBlockName(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) {
	if(ctx->glGetActiveUniformBlockNameProc == NULL) {
		ctx->glGetActiveUniformBlockNameProc = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)gl_wrap_get_pointer("glGetActiveUniformBlockName");
	}
	ctx->glGetActiveUniformBlockNameProc(program, uniformBlockIndex, bufSize, length, uniformBlockName);
};
void gl_wrap_context_glUniformBlockBinding(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {
	if(ctx->glUniformBlockBindingProc == NULL) {
		ctx->glUniformBlockBindingProc = (PFNGLUNIFORMBLOCKBINDINGPROC)gl_wrap_get_pointer("glUniformBlockBinding");
	}
	ctx->glUniformBlockBindingProc(program, uniformBlockIndex, uniformBlockBinding);
};
void gl_wrap_context_glDrawArraysInstanced(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
	if(ctx->glDrawArraysInstancedProc == NULL) {
		ctx->glDrawArraysInstancedProc = (PFNGLDRAWARRAYSINSTANCEDPROC)gl_wrap_get_pointer("glDrawArraysInstanced");
	}
	ctx->glDrawArraysInstancedProc(mode, first, count, instancecount);
};
void gl_wrap_context_glDrawElementsInstanced(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount) {
	if(ctx->glDrawElementsInstancedProc == NULL) {
		ctx->glDrawElementsInstancedProc = (PFNGLDRAWELEMENTSINSTANCEDPROC)gl_wrap_get_pointer("glDrawElementsInstanced");
	}
	ctx->glDrawElementsInstancedProc(mode, count, type, indices, instancecount);
};
GLsync gl_wrap_context_glFenceSync(gl_wrap_context* ctx, GLenum condition, GLbitfield flags) {
	if(ctx->glFenceSyncProc == NULL) {
		ctx->glFenceSyncProc = (PFNGLFENCESYNCPROC)gl_wrap_get_pointer("glFenceSync");
	}
	return ctx->glFenceSyncProc(condition, flags);
};
GLboolean gl_wrap_context_glIsSync(gl_wrap_context* ctx, GLsync sync) {
	if(ctx->glIsSyncProc == NULL) {
		ctx->glIsSyncProc = (PFNGLISSYNCPROC)gl_wrap_get_pointer("glIsSync");
	}
	return ctx->glIsSyncProc(sync);
};
void gl_wrap_context_glDeleteSync(gl_wrap_context* ctx, GLsync sync) {
	if(ctx->glDeleteSyncProc == NULL) {
		ctx->glDeleteSyncProc = (PFNGLDELETESYNCPROC)gl_wrap_get_pointer("glDeleteSync");
	}
	ctx->glDeleteSyncProc(sync);
};
GLenum gl_wrap_context_glClientWaitSync(gl_wrap_context* ctx, GLsync sync, GLbitfield flags, GLuint64 timeout) {
	if(ctx->glClientWaitSyncProc == NULL) {
		ctx->glClientWaitSyncProc = (PFNGLCLIENTWAITSYNCPROC)gl_wrap_get_pointer("glClientWaitSync");
	}
	return ctx->glClientWaitSyncProc(sync, flags, timeout);
};
void gl_wrap_context_glWaitSync(gl_wrap_context* ctx, GLsync sync, GLbitfield flags, GLuint64 timeout) {
	if(ctx->glWaitSyncProc == NULL) {
		ctx->glWaitSyncProc = (PFNGLWAITSYNCPROC)gl_wrap_get_pointer("glWaitSync");
	}
	ctx->glWaitSyncProc(sync, flags, timeout);
};
void gl_wrap_context_glGetInteger64v(gl_wrap_context* ctx, GLenum pname, GLint64* data) {
	if(ctx->glGetInteger64vProc == NULL) {
		ctx->glGetInteger64vProc = (PFNGLGETINTEGER64VPROC)gl_wrap_get_pointer("glGetInteger64v");
	}
	ctx->glGetInteger64vProc(pname, data);
};
void gl_wrap_context_glGetSynciv(gl_wrap_context* ctx, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) {
	if(ctx->glGetSyncivProc == NULL) {
		ctx->glGetSyncivProc = (PFNGLGETSYNCIVPROC)gl_wrap_get_pointer("glGetSynciv");
	}
	ctx->glGetSyncivProc(sync, pname, bufSize, length, values);
};
void gl_wrap_context_glGetInteger64i_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLint64* data) {
	if(ctx->glGetInteger64i_vProc == NULL) {
		ctx->glGetInteger64i_vProc = (PFNGLGETINTEGER64I_VPROC)gl_wrap_get_pointer("glGetInteger64i_v");
	}
	ctx->glGetInteger64i_vProc(target, index, data);
};
void gl_wrap_context_glGetBufferParameteri64v(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint64* params) {
	if(ctx->glGetBufferParameteri64vProc == NULL) {
		ctx->glGetBufferParameteri64vProc = (PFNGLGETBUFFERPARAMETERI64VPROC)gl_wrap_get_pointer("glGetBufferParameteri64v");
	}
	ctx->glGetBufferParameteri64vProc(target, pname, params);
};
void gl_wrap_context_glGenSamplers(gl_wrap_context* ctx, GLsizei count, GLuint* samplers) {
	if(ctx->glGenSamplersProc == NULL) {
		ctx->glGenSamplersProc = (PFNGLGENSAMPLERSPROC)gl_wrap_get_pointer("glGenSamplers");
	}
	ctx->glGenSamplersProc(count, samplers);
};
void gl_wrap_context_glDeleteSamplers(gl_wrap_context* ctx, GLsizei count, GLuint* samplers) {
	if(ctx->glDeleteSamplersProc == NULL) {
		ctx->glDeleteSamplersProc = (PFNGLDELETESAMPLERSPROC)gl_wrap_get_pointer("glDeleteSamplers");
	}
	ctx->glDeleteSamplersProc(count, samplers);
};
GLboolean gl_wrap_context_glIsSampler(gl_wrap_context* ctx, GLuint sampler) {
	if(ctx->glIsSamplerProc == NULL) {
		ctx->glIsSamplerProc = (PFNGLISSAMPLERPROC)gl_wrap_get_pointer("glIsSampler");
	}
	return ctx->glIsSamplerProc(sampler);
};
void gl_wrap_context_glBindSampler(gl_wrap_context* ctx, GLuint unit, GLuint sampler) {
	if(ctx->glBindSamplerProc == NULL) {
		ctx->glBindSamplerProc = (PFNGLBINDSAMPLERPROC)gl_wrap_get_pointer("glBindSampler");
	}
	ctx->glBindSamplerProc(unit, sampler);
};
void gl_wrap_context_glSamplerParameteri(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint param) {
	if(ctx->glSamplerParameteriProc == NULL) {
		ctx->glSamplerParameteriProc = (PFNGLSAMPLERPARAMETERIPROC)gl_wrap_get_pointer("glSamplerParameteri");
	}
	ctx->glSamplerParameteriProc(sampler, pname, param);
};
void gl_wrap_context_glSamplerParameteriv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* param) {
	if(ctx->glSamplerParameterivProc == NULL) {
		ctx->glSamplerParameterivProc = (PFNGLSAMPLERPARAMETERIVPROC)gl_wrap_get_pointer("glSamplerParameteriv");
	}
	ctx->glSamplerParameterivProc(sampler, pname, param);
};
void gl_wrap_context_glSamplerParameterf(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat param) {
	if(ctx->glSamplerParameterfProc == NULL) {
		ctx->glSamplerParameterfProc = (PFNGLSAMPLERPARAMETERFPROC)gl_wrap_get_pointer("glSamplerParameterf");
	}
	ctx->glSamplerParameterfProc(sampler, pname, param);
};
void gl_wrap_context_glSamplerParameterfv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat* param) {
	if(ctx->glSamplerParameterfvProc == NULL) {
		ctx->glSamplerParameterfvProc = (PFNGLSAMPLERPARAMETERFVPROC)gl_wrap_get_pointer("glSamplerParameterfv");
	}
	ctx->glSamplerParameterfvProc(sampler, pname, param);
};
void gl_wrap_context_glGetSamplerParameteriv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* params) {
	if(ctx->glGetSamplerParameterivProc == NULL) {
		ctx->glGetSamplerParameterivProc = (PFNGLGETSAMPLERPARAMETERIVPROC)gl_wrap_get_pointer("glGetSamplerParameteriv");
	}
	ctx->glGetSamplerParameterivProc(sampler, pname, params);
};
void gl_wrap_context_glGetSamplerParameterfv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat* params) {
	if(ctx->glGetSamplerParameterfvProc == NULL) {
		ctx->glGetSamplerParameterfvProc = (PFNGLGETSAMPLERPARAMETERFVPROC)gl_wrap_get_pointer("glGetSamplerParameterfv");
	}
	ctx->glGetSamplerParameterfvProc(sampler, pname, params);
};
void gl_wrap_context_glVertexAttribDivisor(gl_wrap_context* ctx, GLuint index, GLuint divisor) {
	if(ctx->glVertexAttribDivisorProc == NULL) {
		ctx->glVertexAttribDivisorProc = (PFNGLVERTEXATTRIBDIVISORPROC)gl_wrap_get_pointer("glVertexAttribDivisor");
	}
	ctx->glVertexAttribDivisorProc(index, divisor);
};
void gl_wrap_context_glBindTransformFeedback(gl_wrap_context* ctx, GLenum target, GLuint id) {
	if(ctx->glBindTransformFeedbackProc == NULL) {
		ctx->glBindTransformFeedbackProc = (PFNGLBINDTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glBindTransformFeedback");
	}
	ctx->glBindTransformFeedbackProc(target, id);
};
void gl_wrap_context_glDeleteTransformFeedbacks(gl_wrap_context* ctx, GLsizei n, GLuint* ids) {
	if(ctx->glDeleteTransformFeedbacksProc == NULL) {
		ctx->glDeleteTransformFeedbacksProc = (PFNGLDELETETRANSFORMFEEDBACKSPROC)gl_wrap_get_pointer("glDeleteTransformFeedbacks");
	}
	ctx->glDeleteTransformFeedbacksProc(n, ids);
};
void gl_wrap_context_glGenTransformFeedbacks(gl_wrap_context* ctx, GLsizei n, GLuint* ids) {
	if(ctx->glGenTransformFeedbacksProc == NULL) {
		ctx->glGenTransformFeedbacksProc = (PFNGLGENTRANSFORMFEEDBACKSPROC)gl_wrap_get_pointer("glGenTransformFeedbacks");
	}
	ctx->glGenTransformFeedbacksProc(n, ids);
};
GLboolean gl_wrap_context_glIsTransformFeedback(gl_wrap_context* ctx, GLuint id) {
	if(ctx->glIsTransformFeedbackProc == NULL) {
		ctx->glIsTransformFeedbackProc = (PFNGLISTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glIsTransformFeedback");
	}
	return ctx->glIsTransformFeedbackProc(id);
};
void gl_wrap_context_glPauseTransformFeedback(gl_wrap_context* ctx) {
	if(ctx->glPauseTransformFeedbackProc == NULL) {
		ctx->glPauseTransformFeedbackProc = (PFNGLPAUSETRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glPauseTransformFeedback");
	}
	ctx->glPauseTransformFeedbackProc();
};
void gl_wrap_context_glResumeTransformFeedback(gl_wrap_context* ctx) {
	if(ctx->glResumeTransformFeedbackProc == NULL) {
		ctx->glResumeTransformFeedbackProc = (PFNGLRESUMETRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glResumeTransformFeedback");
	}
	ctx->glResumeTransformFeedbackProc();
};
void gl_wrap_context_glGetProgramBinary(gl_wrap_context* ctx, GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary) {
	if(ctx->glGetProgramBinaryProc == NULL) {
		ctx->glGetProgramBinaryProc = (PFNGLGETPROGRAMBINARYPROC)gl_wrap_get_pointer("glGetProgramBinary");
	}
	ctx->glGetProgramBinaryProc(program, bufSize, length, binaryFormat, binary);
};
void gl_wrap_context_glProgramBinary(gl_wrap_context* ctx, GLuint program, GLenum binaryFormat, void* binary, GLsizei length) {
	if(ctx->glProgramBinaryProc == NULL) {
		ctx->glProgramBinaryProc = (PFNGLPROGRAMBINARYPROC)gl_wrap_get_pointer("glProgramBinary");
	}
	ctx->glProgramBinaryProc(program, binaryFormat, binary, length);
};
void gl_wrap_context_glProgramParameteri(gl_wrap_context* ctx, GLuint program, GLenum pname, GLint value) {
	if(ctx->glProgramParameteriProc == NULL) {
		ctx->glProgramParameteriProc = (PFNGLPROGRAMPARAMETERIPROC)gl_wrap_get_pointer("glProgramParameteri");
	}
	ctx->glProgramParameteriProc(program, pname, value);
};
void gl_wrap_context_glInvalidateFramebuffer(gl_wrap_context* ctx, GLenum target, GLsizei numAttachments, GLenum* attachments) {
	if(ctx->glInvalidateFramebufferProc == NULL) {
		ctx->glInvalidateFramebufferProc = (PFNGLINVALIDATEFRAMEBUFFERPROC)gl_wrap_get_pointer("glInvalidateFramebuffer");
	}
	ctx->glInvalidateFramebufferProc(target, numAttachments, attachments);
};
void gl_wrap_context_glInvalidateSubFramebuffer(gl_wrap_context* ctx, GLenum target, GLsizei numAttachments, GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glInvalidateSubFramebufferProc == NULL) {
		ctx->glInvalidateSubFramebufferProc = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)gl_wrap_get_pointer("glInvalidateSubFramebuffer");
	}
	ctx->glInvalidateSubFramebufferProc(target, numAttachments, attachments, x, y, width, height);
};
void gl_wrap_context_glTexStorage2D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {
	if(ctx->glTexStorage2DProc == NULL) {
		ctx->glTexStorage2DProc = (PFNGLTEXSTORAGE2DPROC)gl_wrap_get_pointer("glTexStorage2D");
	}
	ctx->glTexStorage2DProc(target, levels, internalformat, width, height);
};
void gl_wrap_context_glTexStorage3D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) {
	if(ctx->glTexStorage3DProc == NULL) {
		ctx->glTexStorage3DProc = (PFNGLTEXSTORAGE3DPROC)gl_wrap_get_pointer("glTexStorage3D");
	}
	ctx->glTexStorage3DProc(target, levels, internalformat, width, height, depth);
};
void gl_wrap_context_glGetInternalformativ(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params) {
	if(ctx->glGetInternalformativProc == NULL) {
		ctx->glGetInternalformativProc = (PFNGLGETINTERNALFORMATIVPROC)gl_wrap_get_pointer("glGetInternalformativ");
	}
	ctx->glGetInternalformativProc(target, internalformat, pname, bufSize, params);
};
void gl_wrap_context_glDispatchCompute(gl_wrap_context* ctx, GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) {
	if(ctx->glDispatchComputeProc == NULL) {
		ctx->glDispatchComputeProc = (PFNGLDISPATCHCOMPUTEPROC)gl_wrap_get_pointer("glDispatchCompute");
	}
	ctx->glDispatchComputeProc(num_groups_x, num_groups_y, num_groups_z);
};
void gl_wrap_context_glDispatchComputeIndirect(gl_wrap_context* ctx, GLintptr indirect) {
	if(ctx->glDispatchComputeIndirectProc == NULL) {
		ctx->glDispatchComputeIndirectProc = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)gl_wrap_get_pointer("glDispatchComputeIndirect");
	}
	ctx->glDispatchComputeIndirectProc(indirect);
};
void gl_wrap_context_glDrawArraysIndirect(gl_wrap_context* ctx, GLenum mode, void* indirect) {
	if(ctx->glDrawArraysIndirectProc == NULL) {
		ctx->glDrawArraysIndirectProc = (PFNGLDRAWARRAYSINDIRECTPROC)gl_wrap_get_pointer("glDrawArraysIndirect");
	}
	ctx->glDrawArraysIndirectProc(mode, indirect);
};
void gl_wrap_context_glDrawElementsIndirect(gl_wrap_context* ctx, GLenum mode, GLenum type, void* indirect) {
	if(ctx->glDrawElementsIndirectProc == NULL) {
		ctx->glDrawElementsIndirectProc = (PFNGLDRAWELEMENTSINDIRECTPROC)gl_wrap_get_pointer("glDrawElementsIndirect");
	}
	ctx->glDrawElementsIndirectProc(mode, type, indirect);
};
void gl_wrap_context_glFramebufferParameteri(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param) {
	if(ctx->glFramebufferParameteriProc == NULL) {
		ctx->glFramebufferParameteriProc = (PFNGLFRAMEBUFFERPARAMETERIPROC)gl_wrap_get_pointer("glFramebufferParameteri");
	}
	ctx->glFramebufferParameteriProc(target, pname, param);
};
void gl_wrap_context_glGetFramebufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetFramebufferParameterivProc == NULL) {
		ctx->glGetFramebufferParameterivProc = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)gl_wrap_get_pointer("glGetFramebufferParameteriv");
	}
	ctx->glGetFramebufferParameterivProc(target, pname, params);
};
void gl_wrap_context_glGetProgramInterfaceiv(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLenum pname, GLint* params) {
	if(ctx->glGetProgramInterfaceivProc == NULL) {
		ctx->glGetProgramInterfaceivProc = (PFNGLGETPROGRAMINTERFACEIVPROC)gl_wrap_get_pointer("glGetProgramInterfaceiv");
	}
	ctx->glGetProgramInterfaceivProc(program, programInterface, pname, params);
};
GLuint gl_wrap_context_glGetProgramResourceIndex(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name) {
	if(ctx->glGetProgramResourceIndexProc == NULL) {
		ctx->glGetProgramResourceIndexProc = (PFNGLGETPROGRAMRESOURCEINDEXPROC)gl_wrap_get_pointer("glGetProgramResourceIndex");
	}
	return ctx->glGetProgramResourceIndexProc(program, programInterface, name);
};
void gl_wrap_context_glGetProgramResourceName(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name) {
	if(ctx->glGetProgramResourceNameProc == NULL) {
		ctx->glGetProgramResourceNameProc = (PFNGLGETPROGRAMRESOURCENAMEPROC)gl_wrap_get_pointer("glGetProgramResourceName");
	}
	ctx->glGetProgramResourceNameProc(program, programInterface, index, bufSize, length, name);
};
void gl_wrap_context_glGetProgramResourceiv(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params) {
	if(ctx->glGetProgramResourceivProc == NULL) {
		ctx->glGetProgramResourceivProc = (PFNGLGETPROGRAMRESOURCEIVPROC)gl_wrap_get_pointer("glGetProgramResourceiv");
	}
	ctx->glGetProgramResourceivProc(program, programInterface, index, propCount, props, bufSize, length, params);
};
GLint gl_wrap_context_glGetProgramResourceLocation(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name) {
	if(ctx->glGetProgramResourceLocationProc == NULL) {
		ctx->glGetProgramResourceLocationProc = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)gl_wrap_get_pointer("glGetProgramResourceLocation");
	}
	return ctx->glGetProgramResourceLocationProc(program, programInterface, name);
};
void gl_wrap_context_glUseProgramStages(gl_wrap_context* ctx, GLuint pipeline, GLbitfield stages, GLuint program) {
	if(ctx->glUseProgramStagesProc == NULL) {
		ctx->glUseProgramStagesProc = (PFNGLUSEPROGRAMSTAGESPROC)gl_wrap_get_pointer("glUseProgramStages");
	}
	ctx->glUseProgramStagesProc(pipeline, stages, program);
};
void gl_wrap_context_glActiveShaderProgram(gl_wrap_context* ctx, GLuint pipeline, GLuint program) {
	if(ctx->glActiveShaderProgramProc == NULL) {
		ctx->glActiveShaderProgramProc = (PFNGLACTIVESHADERPROGRAMPROC)gl_wrap_get_pointer("glActiveShaderProgram");
	}
	ctx->glActiveShaderProgramProc(pipeline, program);
};
GLuint gl_wrap_context_glCreateShaderProgramv(gl_wrap_context* ctx, GLenum type, GLsizei count, GLchar** strings) {
	if(ctx->glCreateShaderProgramvProc == NULL) {
		ctx->glCreateShaderProgramvProc = (PFNGLCREATESHADERPROGRAMVPROC)gl_wrap_get_pointer("glCreateShaderProgramv");
	}
	return ctx->glCreateShaderProgramvProc(type, count, strings);
};
void gl_wrap_context_glBindProgramPipeline(gl_wrap_context* ctx, GLuint pipeline) {
	if(ctx->glBindProgramPipelineProc == NULL) {
		ctx->glBindProgramPipelineProc = (PFNGLBINDPROGRAMPIPELINEPROC)gl_wrap_get_pointer("glBindProgramPipeline");
	}
	ctx->glBindProgramPipelineProc(pipeline);
};
void gl_wrap_context_glDeleteProgramPipelines(gl_wrap_context* ctx, GLsizei n, GLuint* pipelines) {
	if(ctx->glDeleteProgramPipelinesProc == NULL) {
		ctx->glDeleteProgramPipelinesProc = (PFNGLDELETEPROGRAMPIPELINESPROC)gl_wrap_get_pointer("glDeleteProgramPipelines");
	}
	ctx->glDeleteProgramPipelinesProc(n, pipelines);
};
void gl_wrap_context_glGenProgramPipelines(gl_wrap_context* ctx, GLsizei n, GLuint* pipelines) {
	if(ctx->glGenProgramPipelinesProc == NULL) {
		ctx->glGenProgramPipelinesProc = (PFNGLGENPROGRAMPIPELINESPROC)gl_wrap_get_pointer("glGenProgramPipelines");
	}
	ctx->glGenProgramPipelinesProc(n, pipelines);
};
GLboolean gl_wrap_context_glIsProgramPipeline(gl_wrap_context* ctx, GLuint pipeline) {
	if(ctx->glIsProgramPipelineProc == NULL) {
		ctx->glIsProgramPipelineProc = (PFNGLISPROGRAMPIPELINEPROC)gl_wrap_get_pointer("glIsProgramPipeline");
	}
	return ctx->glIsProgramPipelineProc(pipeline);
};
void gl_wrap_context_glGetProgramPipelineiv(gl_wrap_context* ctx, GLuint pipeline, GLenum pname, GLint* params) {
	if(ctx->glGetProgramPipelineivProc == NULL) {
		ctx->glGetProgramPipelineivProc = (PFNGLGETPROGRAMPIPELINEIVPROC)gl_wrap_get_pointer("glGetProgramPipelineiv");
	}
	ctx->glGetProgramPipelineivProc(pipeline, pname, params);
};
void gl_wrap_context_glProgramUniform1i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0) {
	if(ctx->glProgramUniform1iProc == NULL) {
		ctx->glProgramUniform1iProc = (PFNGLPROGRAMUNIFORM1IPROC)gl_wrap_get_pointer("glProgramUniform1i");
	}
	ctx->glProgramUniform1iProc(program, location, v0);
};
void gl_wrap_context_glProgramUniform2i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1) {
	if(ctx->glProgramUniform2iProc == NULL) {
		ctx->glProgramUniform2iProc = (PFNGLPROGRAMUNIFORM2IPROC)gl_wrap_get_pointer("glProgramUniform2i");
	}
	ctx->glProgramUniform2iProc(program, location, v0, v1);
};
void gl_wrap_context_glProgramUniform3i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1, GLint v2) {
	if(ctx->glProgramUniform3iProc == NULL) {
		ctx->glProgramUniform3iProc = (PFNGLPROGRAMUNIFORM3IPROC)gl_wrap_get_pointer("glProgramUniform3i");
	}
	ctx->glProgramUniform3iProc(program, location, v0, v1, v2);
};
void gl_wrap_context_glProgramUniform4i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
	if(ctx->glProgramUniform4iProc == NULL) {
		ctx->glProgramUniform4iProc = (PFNGLPROGRAMUNIFORM4IPROC)gl_wrap_get_pointer("glProgramUniform4i");
	}
	ctx->glProgramUniform4iProc(program, location, v0, v1, v2, v3);
};
void gl_wrap_context_glProgramUniform1ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0) {
	if(ctx->glProgramUniform1uiProc == NULL) {
		ctx->glProgramUniform1uiProc = (PFNGLPROGRAMUNIFORM1UIPROC)gl_wrap_get_pointer("glProgramUniform1ui");
	}
	ctx->glProgramUniform1uiProc(program, location, v0);
};
void gl_wrap_context_glProgramUniform2ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1) {
	if(ctx->glProgramUniform2uiProc == NULL) {
		ctx->glProgramUniform2uiProc = (PFNGLPROGRAMUNIFORM2UIPROC)gl_wrap_get_pointer("glProgramUniform2ui");
	}
	ctx->glProgramUniform2uiProc(program, location, v0, v1);
};
void gl_wrap_context_glProgramUniform3ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) {
	if(ctx->glProgramUniform3uiProc == NULL) {
		ctx->glProgramUniform3uiProc = (PFNGLPROGRAMUNIFORM3UIPROC)gl_wrap_get_pointer("glProgramUniform3ui");
	}
	ctx->glProgramUniform3uiProc(program, location, v0, v1, v2);
};
void gl_wrap_context_glProgramUniform4ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
	if(ctx->glProgramUniform4uiProc == NULL) {
		ctx->glProgramUniform4uiProc = (PFNGLPROGRAMUNIFORM4UIPROC)gl_wrap_get_pointer("glProgramUniform4ui");
	}
	ctx->glProgramUniform4uiProc(program, location, v0, v1, v2, v3);
};
void gl_wrap_context_glProgramUniform1f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0) {
	if(ctx->glProgramUniform1fProc == NULL) {
		ctx->glProgramUniform1fProc = (PFNGLPROGRAMUNIFORM1FPROC)gl_wrap_get_pointer("glProgramUniform1f");
	}
	ctx->glProgramUniform1fProc(program, location, v0);
};
void gl_wrap_context_glProgramUniform2f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1) {
	if(ctx->glProgramUniform2fProc == NULL) {
		ctx->glProgramUniform2fProc = (PFNGLPROGRAMUNIFORM2FPROC)gl_wrap_get_pointer("glProgramUniform2f");
	}
	ctx->glProgramUniform2fProc(program, location, v0, v1);
};
void gl_wrap_context_glProgramUniform3f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
	if(ctx->glProgramUniform3fProc == NULL) {
		ctx->glProgramUniform3fProc = (PFNGLPROGRAMUNIFORM3FPROC)gl_wrap_get_pointer("glProgramUniform3f");
	}
	ctx->glProgramUniform3fProc(program, location, v0, v1, v2);
};
void gl_wrap_context_glProgramUniform4f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
	if(ctx->glProgramUniform4fProc == NULL) {
		ctx->glProgramUniform4fProc = (PFNGLPROGRAMUNIFORM4FPROC)gl_wrap_get_pointer("glProgramUniform4f");
	}
	ctx->glProgramUniform4fProc(program, location, v0, v1, v2, v3);
};
void gl_wrap_context_glProgramUniform1iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value) {
	if(ctx->glProgramUniform1ivProc == NULL) {
		ctx->glProgramUniform1ivProc = (PFNGLPROGRAMUNIFORM1IVPROC)gl_wrap_get_pointer("glProgramUniform1iv");
	}
	ctx->glProgramUniform1ivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform2iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value) {
	if(ctx->glProgramUniform2ivProc == NULL) {
		ctx->glProgramUniform2ivProc = (PFNGLPROGRAMUNIFORM2IVPROC)gl_wrap_get_pointer("glProgramUniform2iv");
	}
	ctx->glProgramUniform2ivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform3iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value) {
	if(ctx->glProgramUniform3ivProc == NULL) {
		ctx->glProgramUniform3ivProc = (PFNGLPROGRAMUNIFORM3IVPROC)gl_wrap_get_pointer("glProgramUniform3iv");
	}
	ctx->glProgramUniform3ivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform4iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value) {
	if(ctx->glProgramUniform4ivProc == NULL) {
		ctx->glProgramUniform4ivProc = (PFNGLPROGRAMUNIFORM4IVPROC)gl_wrap_get_pointer("glProgramUniform4iv");
	}
	ctx->glProgramUniform4ivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform1uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glProgramUniform1uivProc == NULL) {
		ctx->glProgramUniform1uivProc = (PFNGLPROGRAMUNIFORM1UIVPROC)gl_wrap_get_pointer("glProgramUniform1uiv");
	}
	ctx->glProgramUniform1uivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform2uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glProgramUniform2uivProc == NULL) {
		ctx->glProgramUniform2uivProc = (PFNGLPROGRAMUNIFORM2UIVPROC)gl_wrap_get_pointer("glProgramUniform2uiv");
	}
	ctx->glProgramUniform2uivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform3uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glProgramUniform3uivProc == NULL) {
		ctx->glProgramUniform3uivProc = (PFNGLPROGRAMUNIFORM3UIVPROC)gl_wrap_get_pointer("glProgramUniform3uiv");
	}
	ctx->glProgramUniform3uivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform4uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glProgramUniform4uivProc == NULL) {
		ctx->glProgramUniform4uivProc = (PFNGLPROGRAMUNIFORM4UIVPROC)gl_wrap_get_pointer("glProgramUniform4uiv");
	}
	ctx->glProgramUniform4uivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform1fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glProgramUniform1fvProc == NULL) {
		ctx->glProgramUniform1fvProc = (PFNGLPROGRAMUNIFORM1FVPROC)gl_wrap_get_pointer("glProgramUniform1fv");
	}
	ctx->glProgramUniform1fvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glProgramUniform2fvProc == NULL) {
		ctx->glProgramUniform2fvProc = (PFNGLPROGRAMUNIFORM2FVPROC)gl_wrap_get_pointer("glProgramUniform2fv");
	}
	ctx->glProgramUniform2fvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glProgramUniform3fvProc == NULL) {
		ctx->glProgramUniform3fvProc = (PFNGLPROGRAMUNIFORM3FVPROC)gl_wrap_get_pointer("glProgramUniform3fv");
	}
	ctx->glProgramUniform3fvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glProgramUniform4fvProc == NULL) {
		ctx->glProgramUniform4fvProc = (PFNGLPROGRAMUNIFORM4FVPROC)gl_wrap_get_pointer("glProgramUniform4fv");
	}
	ctx->glProgramUniform4fvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniformMatrix2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix2fvProc == NULL) {
		ctx->glProgramUniformMatrix2fvProc = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2fv");
	}
	ctx->glProgramUniformMatrix2fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix3fvProc == NULL) {
		ctx->glProgramUniformMatrix3fvProc = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3fv");
	}
	ctx->glProgramUniformMatrix3fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix4fvProc == NULL) {
		ctx->glProgramUniformMatrix4fvProc = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4fv");
	}
	ctx->glProgramUniformMatrix4fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix2x3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix2x3fvProc == NULL) {
		ctx->glProgramUniformMatrix2x3fvProc = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2x3fv");
	}
	ctx->glProgramUniformMatrix2x3fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3x2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix3x2fvProc == NULL) {
		ctx->glProgramUniformMatrix3x2fvProc = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3x2fv");
	}
	ctx->glProgramUniformMatrix3x2fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix2x4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix2x4fvProc == NULL) {
		ctx->glProgramUniformMatrix2x4fvProc = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2x4fv");
	}
	ctx->glProgramUniformMatrix2x4fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4x2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix4x2fvProc == NULL) {
		ctx->glProgramUniformMatrix4x2fvProc = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4x2fv");
	}
	ctx->glProgramUniformMatrix4x2fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3x4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix3x4fvProc == NULL) {
		ctx->glProgramUniformMatrix3x4fvProc = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3x4fv");
	}
	ctx->glProgramUniformMatrix3x4fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4x3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix4x3fvProc == NULL) {
		ctx->glProgramUniformMatrix4x3fvProc = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4x3fv");
	}
	ctx->glProgramUniformMatrix4x3fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glValidateProgramPipeline(gl_wrap_context* ctx, GLuint pipeline) {
	if(ctx->glValidateProgramPipelineProc == NULL) {
		ctx->glValidateProgramPipelineProc = (PFNGLVALIDATEPROGRAMPIPELINEPROC)gl_wrap_get_pointer("glValidateProgramPipeline");
	}
	ctx->glValidateProgramPipelineProc(pipeline);
};
void gl_wrap_context_glGetProgramPipelineInfoLog(gl_wrap_context* ctx, GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
	if(ctx->glGetProgramPipelineInfoLogProc == NULL) {
		ctx->glGetProgramPipelineInfoLogProc = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)gl_wrap_get_pointer("glGetProgramPipelineInfoLog");
	}
	ctx->glGetProgramPipelineInfoLogProc(pipeline, bufSize, length, infoLog);
};
void gl_wrap_context_glBindImageTexture(gl_wrap_context* ctx, GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) {
	if(ctx->glBindImageTextureProc == NULL) {
		ctx->glBindImageTextureProc = (PFNGLBINDIMAGETEXTUREPROC)gl_wrap_get_pointer("glBindImageTexture");
	}
	ctx->glBindImageTextureProc(unit, texture, level, layered, layer, access, format);
};
void gl_wrap_context_glGetBooleani_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLboolean* data) {
	if(ctx->glGetBooleani_vProc == NULL) {
		ctx->glGetBooleani_vProc = (PFNGLGETBOOLEANI_VPROC)gl_wrap_get_pointer("glGetBooleani_v");
	}
	ctx->glGetBooleani_vProc(target, index, data);
};
void gl_wrap_context_glMemoryBarrier(gl_wrap_context* ctx, GLbitfield barriers) {
	if(ctx->glMemoryBarrierProc == NULL) {
		ctx->glMemoryBarrierProc = (PFNGLMEMORYBARRIERPROC)gl_wrap_get_pointer("glMemoryBarrier");
	}
	ctx->glMemoryBarrierProc(barriers);
};
void gl_wrap_context_glMemoryBarrierByRegion(gl_wrap_context* ctx, GLbitfield barriers) {
	if(ctx->glMemoryBarrierByRegionProc == NULL) {
		ctx->glMemoryBarrierByRegionProc = (PFNGLMEMORYBARRIERBYREGIONPROC)gl_wrap_get_pointer("glMemoryBarrierByRegion");
	}
	ctx->glMemoryBarrierByRegionProc(barriers);
};
void gl_wrap_context_glTexStorage2DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
	if(ctx->glTexStorage2DMultisampleProc == NULL) {
		ctx->glTexStorage2DMultisampleProc = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)gl_wrap_get_pointer("glTexStorage2DMultisample");
	}
	ctx->glTexStorage2DMultisampleProc(target, samples, internalformat, width, height, fixedsamplelocations);
};
void gl_wrap_context_glGetMultisamplefv(gl_wrap_context* ctx, GLenum pname, GLuint index, GLfloat* val) {
	if(ctx->glGetMultisamplefvProc == NULL) {
		ctx->glGetMultisamplefvProc = (PFNGLGETMULTISAMPLEFVPROC)gl_wrap_get_pointer("glGetMultisamplefv");
	}
	ctx->glGetMultisamplefvProc(pname, index, val);
};
void gl_wrap_context_glSampleMaski(gl_wrap_context* ctx, GLuint maskNumber, GLbitfield mask) {
	if(ctx->glSampleMaskiProc == NULL) {
		ctx->glSampleMaskiProc = (PFNGLSAMPLEMASKIPROC)gl_wrap_get_pointer("glSampleMaski");
	}
	ctx->glSampleMaskiProc(maskNumber, mask);
};
void gl_wrap_context_glGetTexLevelParameteriv(gl_wrap_context* ctx, GLenum target, GLint level, GLenum pname, GLint* params) {
	if(ctx->glGetTexLevelParameterivProc == NULL) {
		ctx->glGetTexLevelParameterivProc = (PFNGLGETTEXLEVELPARAMETERIVPROC)gl_wrap_get_pointer("glGetTexLevelParameteriv");
	}
	ctx->glGetTexLevelParameterivProc(target, level, pname, params);
};
void gl_wrap_context_glGetTexLevelParameterfv(gl_wrap_context* ctx, GLenum target, GLint level, GLenum pname, GLfloat* params) {
	if(ctx->glGetTexLevelParameterfvProc == NULL) {
		ctx->glGetTexLevelParameterfvProc = (PFNGLGETTEXLEVELPARAMETERFVPROC)gl_wrap_get_pointer("glGetTexLevelParameterfv");
	}
	ctx->glGetTexLevelParameterfvProc(target, level, pname, params);
};
void gl_wrap_context_glBindVertexBuffer(gl_wrap_context* ctx, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) {
	if(ctx->glBindVertexBufferProc == NULL) {
		ctx->glBindVertexBufferProc = (PFNGLBINDVERTEXBUFFERPROC)gl_wrap_get_pointer("glBindVertexBuffer");
	}
	ctx->glBindVertexBufferProc(bindingindex, buffer, offset, stride);
};
void gl_wrap_context_glVertexAttribFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) {
	if(ctx->glVertexAttribFormatProc == NULL) {
		ctx->glVertexAttribFormatProc = (PFNGLVERTEXATTRIBFORMATPROC)gl_wrap_get_pointer("glVertexAttribFormat");
	}
	ctx->glVertexAttribFormatProc(attribindex, size, type, normalized, relativeoffset);
};
void gl_wrap_context_glVertexAttribIFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
	if(ctx->glVertexAttribIFormatProc == NULL) {
		ctx->glVertexAttribIFormatProc = (PFNGLVERTEXATTRIBIFORMATPROC)gl_wrap_get_pointer("glVertexAttribIFormat");
	}
	ctx->glVertexAttribIFormatProc(attribindex, size, type, relativeoffset);
};
void gl_wrap_context_glVertexAttribBinding(gl_wrap_context* ctx, GLuint attribindex, GLuint bindingindex) {
	if(ctx->glVertexAttribBindingProc == NULL) {
		ctx->glVertexAttribBindingProc = (PFNGLVERTEXATTRIBBINDINGPROC)gl_wrap_get_pointer("glVertexAttribBinding");
	}
	ctx->glVertexAttribBindingProc(attribindex, bindingindex);
};
void gl_wrap_context_glVertexBindingDivisor(gl_wrap_context* ctx, GLuint bindingindex, GLuint divisor) {
	if(ctx->glVertexBindingDivisorProc == NULL) {
		ctx->glVertexBindingDivisorProc = (PFNGLVERTEXBINDINGDIVISORPROC)gl_wrap_get_pointer("glVertexBindingDivisor");
	}
	ctx->glVertexBindingDivisorProc(bindingindex, divisor);
};



// Handler functions are defined for each OpenGL call; each handler function
// takes the OpenGL context struct and a pointer to the same OpenGL function's
// arguments stored in a struct.
//
// Each handler function is responsible for invoking the OpenGL function with
// the proper parameters.
//
// All function handlers are placed with respect to order in the defined jump
// table (see below), which allows batched OpenGL calls to be made without
// using a large (and costly) switch statement.
//
// Handler functions are not defined for OpenGL functions which return any
// value, as these function calls cannot be batched (see the Go documentation
// for this package, which explains this in more detail).
inline void gl_wrap_handler_glActiveTexture(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glActiveTexture_args args = *(gl_wrap_handler_glActiveTexture_args*)argsPtr;
	gl_wrap_context_glActiveTexture(ctx, args.texture);
}

inline void gl_wrap_handler_glAttachShader(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glAttachShader_args args = *(gl_wrap_handler_glAttachShader_args*)argsPtr;
	gl_wrap_context_glAttachShader(ctx, args.program, args.shader);
}

inline void gl_wrap_handler_glBindAttribLocation(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindAttribLocation_args args = *(gl_wrap_handler_glBindAttribLocation_args*)argsPtr;
	gl_wrap_context_glBindAttribLocation(ctx, args.program, args.index, args.name);
}

inline void gl_wrap_handler_glBindBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindBuffer_args args = *(gl_wrap_handler_glBindBuffer_args*)argsPtr;
	gl_wrap_context_glBindBuffer(ctx, args.target, args.buffer);
}

inline void gl_wrap_handler_glBindFramebuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindFramebuffer_args args = *(gl_wrap_handler_glBindFramebuffer_args*)argsPtr;
	gl_wrap_context_glBindFramebuffer(ctx, args.target, args.framebuffer);
}

inline void gl_wrap_handler_glBindRenderbuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindRenderbuffer_args args = *(gl_wrap_handler_glBindRenderbuffer_args*)argsPtr;
	gl_wrap_context_glBindRenderbuffer(ctx, args.target, args.renderbuffer);
}

inline void gl_wrap_handler_glBindTexture(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindTexture_args args = *(gl_wrap_handler_glBindTexture_args*)argsPtr;
	gl_wrap_context_glBindTexture(ctx, args.target, args.texture);
}

inline void gl_wrap_handler_glBlendColor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendColor_args args = *(gl_wrap_handler_glBlendColor_args*)argsPtr;
	gl_wrap_context_glBlendColor(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glBlendEquation(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendEquation_args args = *(gl_wrap_handler_glBlendEquation_args*)argsPtr;
	gl_wrap_context_glBlendEquation(ctx, args.mode);
}

inline void gl_wrap_handler_glBlendEquationSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendEquationSeparate_args args = *(gl_wrap_handler_glBlendEquationSeparate_args*)argsPtr;
	gl_wrap_context_glBlendEquationSeparate(ctx, args.modeRGB, args.modeAlpha);
}

inline void gl_wrap_handler_glBlendFunc(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendFunc_args args = *(gl_wrap_handler_glBlendFunc_args*)argsPtr;
	gl_wrap_context_glBlendFunc(ctx, args.sfactor, args.dfactor);
}

inline void gl_wrap_handler_glBlendFuncSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendFuncSeparate_args args = *(gl_wrap_handler_glBlendFuncSeparate_args*)argsPtr;
	gl_wrap_context_glBlendFuncSeparate(ctx, args.sfactorRGB, args.dfactorRGB, args.sfactorAlpha, args.dfactorAlpha);
}

inline void gl_wrap_handler_glBufferData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBufferData_args args = *(gl_wrap_handler_glBufferData_args*)argsPtr;
	gl_wrap_context_glBufferData(ctx, args.target, args.size, args.data, args.usage);
}

inline void gl_wrap_handler_glBufferSubData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBufferSubData_args args = *(gl_wrap_handler_glBufferSubData_args*)argsPtr;
	gl_wrap_context_glBufferSubData(ctx, args.target, args.offset, args.size, args.data);
}

inline void gl_wrap_handler_glClear(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClear_args args = *(gl_wrap_handler_glClear_args*)argsPtr;
	gl_wrap_context_glClear(ctx, args.mask);
}

inline void gl_wrap_handler_glClearColor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearColor_args args = *(gl_wrap_handler_glClearColor_args*)argsPtr;
	gl_wrap_context_glClearColor(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glClearDepthf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearDepthf_args args = *(gl_wrap_handler_glClearDepthf_args*)argsPtr;
	gl_wrap_context_glClearDepthf(ctx, args.d);
}

inline void gl_wrap_handler_glClearStencil(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearStencil_args args = *(gl_wrap_handler_glClearStencil_args*)argsPtr;
	gl_wrap_context_glClearStencil(ctx, args.s);
}

inline void gl_wrap_handler_glColorMask(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorMask_args args = *(gl_wrap_handler_glColorMask_args*)argsPtr;
	gl_wrap_context_glColorMask(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glCompileShader(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompileShader_args args = *(gl_wrap_handler_glCompileShader_args*)argsPtr;
	gl_wrap_context_glCompileShader(ctx, args.shader);
}

inline void gl_wrap_handler_glCompressedTexImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexImage2D_args args = *(gl_wrap_handler_glCompressedTexImage2D_args*)argsPtr;
	gl_wrap_context_glCompressedTexImage2D(ctx, args.target, args.level, args.internalformat, args.width, args.height, args.border, args.imageSize, args.data);
}

inline void gl_wrap_handler_glCompressedTexSubImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexSubImage2D_args args = *(gl_wrap_handler_glCompressedTexSubImage2D_args*)argsPtr;
	gl_wrap_context_glCompressedTexSubImage2D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.width, args.height, args.format, args.imageSize, args.data);
}

inline void gl_wrap_handler_glCopyTexImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyTexImage2D_args args = *(gl_wrap_handler_glCopyTexImage2D_args*)argsPtr;
	gl_wrap_context_glCopyTexImage2D(ctx, args.target, args.level, args.internalformat, args.x, args.y, args.width, args.height, args.border);
}

inline void gl_wrap_handler_glCopyTexSubImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyTexSubImage2D_args args = *(gl_wrap_handler_glCopyTexSubImage2D_args*)argsPtr;
	gl_wrap_context_glCopyTexSubImage2D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glCullFace(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCullFace_args args = *(gl_wrap_handler_glCullFace_args*)argsPtr;
	gl_wrap_context_glCullFace(ctx, args.mode);
}

inline void gl_wrap_handler_glDeleteBuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteBuffers_args args = *(gl_wrap_handler_glDeleteBuffers_args*)argsPtr;
	gl_wrap_context_glDeleteBuffers(ctx, args.n, args.buffers);
}

inline void gl_wrap_handler_glDeleteFramebuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteFramebuffers_args args = *(gl_wrap_handler_glDeleteFramebuffers_args*)argsPtr;
	gl_wrap_context_glDeleteFramebuffers(ctx, args.n, args.framebuffers);
}

inline void gl_wrap_handler_glDeleteProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteProgram_args args = *(gl_wrap_handler_glDeleteProgram_args*)argsPtr;
	gl_wrap_context_glDeleteProgram(ctx, args.program);
}

inline void gl_wrap_handler_glDeleteRenderbuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteRenderbuffers_args args = *(gl_wrap_handler_glDeleteRenderbuffers_args*)argsPtr;
	gl_wrap_context_glDeleteRenderbuffers(ctx, args.n, args.renderbuffers);
}

inline void gl_wrap_handler_glDeleteShader(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteShader_args args = *(gl_wrap_handler_glDeleteShader_args*)argsPtr;
	gl_wrap_context_glDeleteShader(ctx, args.shader);
}

inline void gl_wrap_handler_glDeleteTextures(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteTextures_args args = *(gl_wrap_handler_glDeleteTextures_args*)argsPtr;
	gl_wrap_context_glDeleteTextures(ctx, args.n, args.textures);
}

inline void gl_wrap_handler_glDepthFunc(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthFunc_args args = *(gl_wrap_handler_glDepthFunc_args*)argsPtr;
	gl_wrap_context_glDepthFunc(ctx, args.func);
}

inline void gl_wrap_handler_glDepthMask(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthMask_args args = *(gl_wrap_handler_glDepthMask_args*)argsPtr;
	gl_wrap_context_glDepthMask(ctx, args.flag);
}

inline void gl_wrap_handler_glDepthRangef(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthRangef_args args = *(gl_wrap_handler_glDepthRangef_args*)argsPtr;
	gl_wrap_context_glDepthRangef(ctx, args.n, args.f);
}

inline void gl_wrap_handler_glDetachShader(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDetachShader_args args = *(gl_wrap_handler_glDetachShader_args*)argsPtr;
	gl_wrap_context_glDetachShader(ctx, args.program, args.shader);
}

inline void gl_wrap_handler_glDisable(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDisable_args args = *(gl_wrap_handler_glDisable_args*)argsPtr;
	gl_wrap_context_glDisable(ctx, args.cap);
}

inline void gl_wrap_handler_glDisableVertexAttribArray(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDisableVertexAttribArray_args args = *(gl_wrap_handler_glDisableVertexAttribArray_args*)argsPtr;
	gl_wrap_context_glDisableVertexAttribArray(ctx, args.index);
}

inline void gl_wrap_handler_glDrawArrays(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawArrays_args args = *(gl_wrap_handler_glDrawArrays_args*)argsPtr;
	gl_wrap_context_glDrawArrays(ctx, args.mode, args.first, args.count);
}

inline void gl_wrap_handler_glDrawElements(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElements_args args = *(gl_wrap_handler_glDrawElements_args*)argsPtr;
	gl_wrap_context_glDrawElements(ctx, args.mode, args.count, args.type, args.indices);
}

inline void gl_wrap_handler_glEnable(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEnable_args args = *(gl_wrap_handler_glEnable_args*)argsPtr;
	gl_wrap_context_glEnable(ctx, args.cap);
}

inline void gl_wrap_handler_glEnableVertexAttribArray(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEnableVertexAttribArray_args args = *(gl_wrap_handler_glEnableVertexAttribArray_args*)argsPtr;
	gl_wrap_context_glEnableVertexAttribArray(ctx, args.index);
}

inline void gl_wrap_handler_glFinish(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFinish_args args = *(gl_wrap_handler_glFinish_args*)argsPtr;
	gl_wrap_context_glFinish(ctx);
}

inline void gl_wrap_handler_glFlush(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFlush_args args = *(gl_wrap_handler_glFlush_args*)argsPtr;
	gl_wrap_context_glFlush(ctx);
}

inline void gl_wrap_handler_glFramebufferRenderbuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferRenderbuffer_args args = *(gl_wrap_handler_glFramebufferRenderbuffer_args*)argsPtr;
	gl_wrap_context_glFramebufferRenderbuffer(ctx, args.target, args.attachment, args.renderbuffertarget, args.renderbuffer);
}

inline void gl_wrap_handler_glFramebufferTexture2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferTexture2D_args args = *(gl_wrap_handler_glFramebufferTexture2D_args*)argsPtr;
	gl_wrap_context_glFramebufferTexture2D(ctx, args.target, args.attachment, args.textarget, args.texture, args.level);
}

inline void gl_wrap_handler_glFrontFace(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFrontFace_args args = *(gl_wrap_handler_glFrontFace_args*)argsPtr;
	gl_wrap_context_glFrontFace(ctx, args.mode);
}

inline void gl_wrap_handler_glGenBuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenBuffers_args args = *(gl_wrap_handler_glGenBuffers_args*)argsPtr;
	gl_wrap_context_glGenBuffers(ctx, args.n, args.buffers);
}

inline void gl_wrap_handler_glGenerateMipmap(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenerateMipmap_args args = *(gl_wrap_handler_glGenerateMipmap_args*)argsPtr;
	gl_wrap_context_glGenerateMipmap(ctx, args.target);
}

inline void gl_wrap_handler_glGenFramebuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenFramebuffers_args args = *(gl_wrap_handler_glGenFramebuffers_args*)argsPtr;
	gl_wrap_context_glGenFramebuffers(ctx, args.n, args.framebuffers);
}

inline void gl_wrap_handler_glGenRenderbuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenRenderbuffers_args args = *(gl_wrap_handler_glGenRenderbuffers_args*)argsPtr;
	gl_wrap_context_glGenRenderbuffers(ctx, args.n, args.renderbuffers);
}

inline void gl_wrap_handler_glGenTextures(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenTextures_args args = *(gl_wrap_handler_glGenTextures_args*)argsPtr;
	gl_wrap_context_glGenTextures(ctx, args.n, args.textures);
}

inline void gl_wrap_handler_glGetActiveAttrib(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveAttrib_args args = *(gl_wrap_handler_glGetActiveAttrib_args*)argsPtr;
	gl_wrap_context_glGetActiveAttrib(ctx, args.program, args.index, args.bufSize, args.length, args.size, args.type, args.name);
}

inline void gl_wrap_handler_glGetActiveUniform(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniform_args args = *(gl_wrap_handler_glGetActiveUniform_args*)argsPtr;
	gl_wrap_context_glGetActiveUniform(ctx, args.program, args.index, args.bufSize, args.length, args.size, args.type, args.name);
}

inline void gl_wrap_handler_glGetAttachedShaders(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetAttachedShaders_args args = *(gl_wrap_handler_glGetAttachedShaders_args*)argsPtr;
	gl_wrap_context_glGetAttachedShaders(ctx, args.program, args.maxCount, args.count, args.shaders);
}

inline void gl_wrap_handler_glGetBooleanv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBooleanv_args args = *(gl_wrap_handler_glGetBooleanv_args*)argsPtr;
	gl_wrap_context_glGetBooleanv(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetBufferParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBufferParameteriv_args args = *(gl_wrap_handler_glGetBufferParameteriv_args*)argsPtr;
	gl_wrap_context_glGetBufferParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetFloatv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetFloatv_args args = *(gl_wrap_handler_glGetFloatv_args*)argsPtr;
	gl_wrap_context_glGetFloatv(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetFramebufferAttachmentParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetFramebufferAttachmentParameteriv_args args = *(gl_wrap_handler_glGetFramebufferAttachmentParameteriv_args*)argsPtr;
	gl_wrap_context_glGetFramebufferAttachmentParameteriv(ctx, args.target, args.attachment, args.pname, args.params);
}

inline void gl_wrap_handler_glGetIntegerv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetIntegerv_args args = *(gl_wrap_handler_glGetIntegerv_args*)argsPtr;
	gl_wrap_context_glGetIntegerv(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetProgramiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramiv_args args = *(gl_wrap_handler_glGetProgramiv_args*)argsPtr;
	gl_wrap_context_glGetProgramiv(ctx, args.program, args.pname, args.params);
}

inline void gl_wrap_handler_glGetProgramInfoLog(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramInfoLog_args args = *(gl_wrap_handler_glGetProgramInfoLog_args*)argsPtr;
	gl_wrap_context_glGetProgramInfoLog(ctx, args.program, args.bufSize, args.length, args.infoLog);
}

inline void gl_wrap_handler_glGetRenderbufferParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetRenderbufferParameteriv_args args = *(gl_wrap_handler_glGetRenderbufferParameteriv_args*)argsPtr;
	gl_wrap_context_glGetRenderbufferParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetShaderiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetShaderiv_args args = *(gl_wrap_handler_glGetShaderiv_args*)argsPtr;
	gl_wrap_context_glGetShaderiv(ctx, args.shader, args.pname, args.params);
}

inline void gl_wrap_handler_glGetShaderInfoLog(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetShaderInfoLog_args args = *(gl_wrap_handler_glGetShaderInfoLog_args*)argsPtr;
	gl_wrap_context_glGetShaderInfoLog(ctx, args.shader, args.bufSize, args.length, args.infoLog);
}

inline void gl_wrap_handler_glGetShaderPrecisionFormat(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetShaderPrecisionFormat_args args = *(gl_wrap_handler_glGetShaderPrecisionFormat_args*)argsPtr;
	gl_wrap_context_glGetShaderPrecisionFormat(ctx, args.shadertype, args.precisiontype, args.range, args.precision);
}

inline void gl_wrap_handler_glGetShaderSource(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetShaderSource_args args = *(gl_wrap_handler_glGetShaderSource_args*)argsPtr;
	gl_wrap_context_glGetShaderSource(ctx, args.shader, args.bufSize, args.length, args.source);
}

inline void gl_wrap_handler_glGetTexParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexParameterfv_args args = *(gl_wrap_handler_glGetTexParameterfv_args*)argsPtr;
	gl_wrap_context_glGetTexParameterfv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexParameteriv_args args = *(gl_wrap_handler_glGetTexParameteriv_args*)argsPtr;
	gl_wrap_context_glGetTexParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetUniformfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformfv_args args = *(gl_wrap_handler_glGetUniformfv_args*)argsPtr;
	gl_wrap_context_glGetUniformfv(ctx, args.program, args.location, args.params);
}

inline void gl_wrap_handler_glGetUniformiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformiv_args args = *(gl_wrap_handler_glGetUniformiv_args*)argsPtr;
	gl_wrap_context_glGetUniformiv(ctx, args.program, args.location, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribfv_args args = *(gl_wrap_handler_glGetVertexAttribfv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribfv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribiv_args args = *(gl_wrap_handler_glGetVertexAttribiv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribiv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribPointerv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribPointerv_args args = *(gl_wrap_handler_glGetVertexAttribPointerv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribPointerv(ctx, args.index, args.pname, args.pointer);
}

inline void gl_wrap_handler_glHint(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glHint_args args = *(gl_wrap_handler_glHint_args*)argsPtr;
	gl_wrap_context_glHint(ctx, args.target, args.mode);
}

inline void gl_wrap_handler_glLineWidth(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLineWidth_args args = *(gl_wrap_handler_glLineWidth_args*)argsPtr;
	gl_wrap_context_glLineWidth(ctx, args.width);
}

inline void gl_wrap_handler_glLinkProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLinkProgram_args args = *(gl_wrap_handler_glLinkProgram_args*)argsPtr;
	gl_wrap_context_glLinkProgram(ctx, args.program);
}

inline void gl_wrap_handler_glPixelStorei(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelStorei_args args = *(gl_wrap_handler_glPixelStorei_args*)argsPtr;
	gl_wrap_context_glPixelStorei(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glPolygonOffset(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPolygonOffset_args args = *(gl_wrap_handler_glPolygonOffset_args*)argsPtr;
	gl_wrap_context_glPolygonOffset(ctx, args.factor, args.units);
}

inline void gl_wrap_handler_glReadPixels(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glReadPixels_args args = *(gl_wrap_handler_glReadPixels_args*)argsPtr;
	gl_wrap_context_glReadPixels(ctx, args.x, args.y, args.width, args.height, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glReleaseShaderCompiler(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glReleaseShaderCompiler_args args = *(gl_wrap_handler_glReleaseShaderCompiler_args*)argsPtr;
	gl_wrap_context_glReleaseShaderCompiler(ctx);
}

inline void gl_wrap_handler_glRenderbufferStorage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRenderbufferStorage_args args = *(gl_wrap_handler_glRenderbufferStorage_args*)argsPtr;
	gl_wrap_context_glRenderbufferStorage(ctx, args.target, args.internalformat, args.width, args.height);
}

inline void gl_wrap_handler_glSampleCoverage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSampleCoverage_args args = *(gl_wrap_handler_glSampleCoverage_args*)argsPtr;
	gl_wrap_context_glSampleCoverage(ctx, args.value, args.invert);
}

inline void gl_wrap_handler_glScissor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glScissor_args args = *(gl_wrap_handler_glScissor_args*)argsPtr;
	gl_wrap_context_glScissor(ctx, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glShaderBinary(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glShaderBinary_args args = *(gl_wrap_handler_glShaderBinary_args*)argsPtr;
	gl_wrap_context_glShaderBinary(ctx, args.count, args.shaders, args.binaryformat, args.binary, args.length);
}

inline void gl_wrap_handler_glShaderSource(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glShaderSource_args args = *(gl_wrap_handler_glShaderSource_args*)argsPtr;
	gl_wrap_context_glShaderSource(ctx, args.shader, args.count, args.string, args.length);
}

inline void gl_wrap_handler_glStencilFunc(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilFunc_args args = *(gl_wrap_handler_glStencilFunc_args*)argsPtr;
	gl_wrap_context_glStencilFunc(ctx, args.func, args.ref, args.mask);
}

inline void gl_wrap_handler_glStencilFuncSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilFuncSeparate_args args = *(gl_wrap_handler_glStencilFuncSeparate_args*)argsPtr;
	gl_wrap_context_glStencilFuncSeparate(ctx, args.face, args.func, args.ref, args.mask);
}

inline void gl_wrap_handler_glStencilMask(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilMask_args args = *(gl_wrap_handler_glStencilMask_args*)argsPtr;
	gl_wrap_context_glStencilMask(ctx, args.mask);
}

inline void gl_wrap_handler_glStencilMaskSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilMaskSeparate_args args = *(gl_wrap_handler_glStencilMaskSeparate_args*)argsPtr;
	gl_wrap_context_glStencilMaskSeparate(ctx, args.face, args.mask);
}

inline void gl_wrap_handler_glStencilOp(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilOp_args args = *(gl_wrap_handler_glStencilOp_args*)argsPtr;
	gl_wrap_context_glStencilOp(ctx, args.fail, args.zfail, args.zpass);
}

inline void gl_wrap_handler_glStencilOpSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilOpSeparate_args args = *(gl_wrap_handler_glStencilOpSeparate_args*)argsPtr;
	gl_wrap_context_glStencilOpSeparate(ctx, args.face, args.sfail, args.dpfail, args.dppass);
}

inline void gl_wrap_handler_glTexImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexImage2D_args args = *(gl_wrap_handler_glTexImage2D_args*)argsPtr;
	gl_wrap_context_glTexImage2D(ctx, args.target, args.level, args.internalformat, args.width, args.height, args.border, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glTexParameterf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameterf_args args = *(gl_wrap_handler_glTexParameterf_args*)argsPtr;
	gl_wrap_context_glTexParameterf(ctx, args.target, args.pname, args.param);
}

inline void gl_wrap_handler_glTexParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameterfv_args args = *(gl_wrap_handler_glTexParameterfv_args*)argsPtr;
	gl_wrap_context_glTexParameterfv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glTexParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameteri_args args = *(gl_wrap_handler_glTexParameteri_args*)argsPtr;
	gl_wrap_context_glTexParameteri(ctx, args.target, args.pname, args.param);
}

inline void gl_wrap_handler_glTexParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameteriv_args args = *(gl_wrap_handler_glTexParameteriv_args*)argsPtr;
	gl_wrap_context_glTexParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glTexSubImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexSubImage2D_args args = *(gl_wrap_handler_glTexSubImage2D_args*)argsPtr;
	gl_wrap_context_glTexSubImage2D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.width, args.height, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glUniform1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1f_args args = *(gl_wrap_handler_glUniform1f_args*)argsPtr;
	gl_wrap_context_glUniform1f(ctx, args.location, args.v0);
}

inline void gl_wrap_handler_glUniform1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1fv_args args = *(gl_wrap_handler_glUniform1fv_args*)argsPtr;
	gl_wrap_context_glUniform1fv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform1i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1i_args args = *(gl_wrap_handler_glUniform1i_args*)argsPtr;
	gl_wrap_context_glUniform1i(ctx, args.location, args.v0);
}

inline void gl_wrap_handler_glUniform1iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1iv_args args = *(gl_wrap_handler_glUniform1iv_args*)argsPtr;
	gl_wrap_context_glUniform1iv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2f_args args = *(gl_wrap_handler_glUniform2f_args*)argsPtr;
	gl_wrap_context_glUniform2f(ctx, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glUniform2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2fv_args args = *(gl_wrap_handler_glUniform2fv_args*)argsPtr;
	gl_wrap_context_glUniform2fv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2i_args args = *(gl_wrap_handler_glUniform2i_args*)argsPtr;
	gl_wrap_context_glUniform2i(ctx, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glUniform2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2iv_args args = *(gl_wrap_handler_glUniform2iv_args*)argsPtr;
	gl_wrap_context_glUniform2iv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3f_args args = *(gl_wrap_handler_glUniform3f_args*)argsPtr;
	gl_wrap_context_glUniform3f(ctx, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glUniform3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3fv_args args = *(gl_wrap_handler_glUniform3fv_args*)argsPtr;
	gl_wrap_context_glUniform3fv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3i_args args = *(gl_wrap_handler_glUniform3i_args*)argsPtr;
	gl_wrap_context_glUniform3i(ctx, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glUniform3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3iv_args args = *(gl_wrap_handler_glUniform3iv_args*)argsPtr;
	gl_wrap_context_glUniform3iv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4f_args args = *(gl_wrap_handler_glUniform4f_args*)argsPtr;
	gl_wrap_context_glUniform4f(ctx, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glUniform4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4fv_args args = *(gl_wrap_handler_glUniform4fv_args*)argsPtr;
	gl_wrap_context_glUniform4fv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4i_args args = *(gl_wrap_handler_glUniform4i_args*)argsPtr;
	gl_wrap_context_glUniform4i(ctx, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glUniform4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4iv_args args = *(gl_wrap_handler_glUniform4iv_args*)argsPtr;
	gl_wrap_context_glUniform4iv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniformMatrix2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2fv_args args = *(gl_wrap_handler_glUniformMatrix2fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3fv_args args = *(gl_wrap_handler_glUniformMatrix3fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4fv_args args = *(gl_wrap_handler_glUniformMatrix4fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUseProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUseProgram_args args = *(gl_wrap_handler_glUseProgram_args*)argsPtr;
	gl_wrap_context_glUseProgram(ctx, args.program);
}

inline void gl_wrap_handler_glValidateProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glValidateProgram_args args = *(gl_wrap_handler_glValidateProgram_args*)argsPtr;
	gl_wrap_context_glValidateProgram(ctx, args.program);
}

inline void gl_wrap_handler_glVertexAttrib1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib1f_args args = *(gl_wrap_handler_glVertexAttrib1f_args*)argsPtr;
	gl_wrap_context_glVertexAttrib1f(ctx, args.index, args.x);
}

inline void gl_wrap_handler_glVertexAttrib1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib1fv_args args = *(gl_wrap_handler_glVertexAttrib1fv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib1fv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib2f_args args = *(gl_wrap_handler_glVertexAttrib2f_args*)argsPtr;
	gl_wrap_context_glVertexAttrib2f(ctx, args.index, args.x, args.y);
}

inline void gl_wrap_handler_glVertexAttrib2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib2fv_args args = *(gl_wrap_handler_glVertexAttrib2fv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib2fv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib3f_args args = *(gl_wrap_handler_glVertexAttrib3f_args*)argsPtr;
	gl_wrap_context_glVertexAttrib3f(ctx, args.index, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertexAttrib3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib3fv_args args = *(gl_wrap_handler_glVertexAttrib3fv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib3fv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4f_args args = *(gl_wrap_handler_glVertexAttrib4f_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4f(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttrib4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4fv_args args = *(gl_wrap_handler_glVertexAttrib4fv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4fv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribPointer_args args = *(gl_wrap_handler_glVertexAttribPointer_args*)argsPtr;
	gl_wrap_context_glVertexAttribPointer(ctx, args.index, args.size, args.type, args.normalized, args.stride, args.pointer);
}

inline void gl_wrap_handler_glViewport(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glViewport_args args = *(gl_wrap_handler_glViewport_args*)argsPtr;
	gl_wrap_context_glViewport(ctx, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glReadBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glReadBuffer_args args = *(gl_wrap_handler_glReadBuffer_args*)argsPtr;
	gl_wrap_context_glReadBuffer(ctx, args.mode);
}

inline void gl_wrap_handler_glDrawRangeElements(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawRangeElements_args args = *(gl_wrap_handler_glDrawRangeElements_args*)argsPtr;
	gl_wrap_context_glDrawRangeElements(ctx, args.mode, args.start, args.end, args.count, args.type, args.indices);
}

inline void gl_wrap_handler_glTexImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexImage3D_args args = *(gl_wrap_handler_glTexImage3D_args*)argsPtr;
	gl_wrap_context_glTexImage3D(ctx, args.target, args.level, args.internalformat, args.width, args.height, args.depth, args.border, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glTexSubImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexSubImage3D_args args = *(gl_wrap_handler_glTexSubImage3D_args*)argsPtr;
	gl_wrap_context_glTexSubImage3D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.zoffset, args.width, args.height, args.depth, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glCopyTexSubImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyTexSubImage3D_args args = *(gl_wrap_handler_glCopyTexSubImage3D_args*)argsPtr;
	gl_wrap_context_glCopyTexSubImage3D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.zoffset, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glCompressedTexImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexImage3D_args args = *(gl_wrap_handler_glCompressedTexImage3D_args*)argsPtr;
	gl_wrap_context_glCompressedTexImage3D(ctx, args.target, args.level, args.internalformat, args.width, args.height, args.depth, args.border, args.imageSize, args.data);
}

inline void gl_wrap_handler_glCompressedTexSubImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexSubImage3D_args args = *(gl_wrap_handler_glCompressedTexSubImage3D_args*)argsPtr;
	gl_wrap_context_glCompressedTexSubImage3D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.zoffset, args.width, args.height, args.depth, args.format, args.imageSize, args.data);
}

inline void gl_wrap_handler_glGenQueries(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenQueries_args args = *(gl_wrap_handler_glGenQueries_args*)argsPtr;
	gl_wrap_context_glGenQueries(ctx, args.n, args.ids);
}

inline void gl_wrap_handler_glDeleteQueries(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteQueries_args args = *(gl_wrap_handler_glDeleteQueries_args*)argsPtr;
	gl_wrap_context_glDeleteQueries(ctx, args.n, args.ids);
}

inline void gl_wrap_handler_glBeginQuery(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBeginQuery_args args = *(gl_wrap_handler_glBeginQuery_args*)argsPtr;
	gl_wrap_context_glBeginQuery(ctx, args.target, args.id);
}

inline void gl_wrap_handler_glEndQuery(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEndQuery_args args = *(gl_wrap_handler_glEndQuery_args*)argsPtr;
	gl_wrap_context_glEndQuery(ctx, args.target);
}

inline void gl_wrap_handler_glGetQueryiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetQueryiv_args args = *(gl_wrap_handler_glGetQueryiv_args*)argsPtr;
	gl_wrap_context_glGetQueryiv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetQueryObjectuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetQueryObjectuiv_args args = *(gl_wrap_handler_glGetQueryObjectuiv_args*)argsPtr;
	gl_wrap_context_glGetQueryObjectuiv(ctx, args.id, args.pname, args.params);
}

inline void gl_wrap_handler_glGetBufferPointerv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBufferPointerv_args args = *(gl_wrap_handler_glGetBufferPointerv_args*)argsPtr;
	gl_wrap_context_glGetBufferPointerv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glDrawBuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawBuffers_args args = *(gl_wrap_handler_glDrawBuffers_args*)argsPtr;
	gl_wrap_context_glDrawBuffers(ctx, args.n, args.bufs);
}

inline void gl_wrap_handler_glUniformMatrix2x3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2x3fv_args args = *(gl_wrap_handler_glUniformMatrix2x3fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2x3fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3x2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3x2fv_args args = *(gl_wrap_handler_glUniformMatrix3x2fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3x2fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix2x4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2x4fv_args args = *(gl_wrap_handler_glUniformMatrix2x4fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2x4fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4x2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4x2fv_args args = *(gl_wrap_handler_glUniformMatrix4x2fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4x2fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3x4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3x4fv_args args = *(gl_wrap_handler_glUniformMatrix3x4fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3x4fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4x3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4x3fv_args args = *(gl_wrap_handler_glUniformMatrix4x3fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4x3fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glBlitFramebuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlitFramebuffer_args args = *(gl_wrap_handler_glBlitFramebuffer_args*)argsPtr;
	gl_wrap_context_glBlitFramebuffer(ctx, args.srcX0, args.srcY0, args.srcX1, args.srcY1, args.dstX0, args.dstY0, args.dstX1, args.dstY1, args.mask, args.filter);
}

inline void gl_wrap_handler_glRenderbufferStorageMultisample(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRenderbufferStorageMultisample_args args = *(gl_wrap_handler_glRenderbufferStorageMultisample_args*)argsPtr;
	gl_wrap_context_glRenderbufferStorageMultisample(ctx, args.target, args.samples, args.internalformat, args.width, args.height);
}

inline void gl_wrap_handler_glFramebufferTextureLayer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferTextureLayer_args args = *(gl_wrap_handler_glFramebufferTextureLayer_args*)argsPtr;
	gl_wrap_context_glFramebufferTextureLayer(ctx, args.target, args.attachment, args.texture, args.level, args.layer);
}

inline void gl_wrap_handler_glMapBufferRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMapBufferRange_args args = *(gl_wrap_handler_glMapBufferRange_args*)argsPtr;
	gl_wrap_context_glMapBufferRange(ctx, args.target, args.offset, args.length, args.access);
}

inline void gl_wrap_handler_glFlushMappedBufferRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFlushMappedBufferRange_args args = *(gl_wrap_handler_glFlushMappedBufferRange_args*)argsPtr;
	gl_wrap_context_glFlushMappedBufferRange(ctx, args.target, args.offset, args.length);
}

inline void gl_wrap_handler_glBindVertexArray(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindVertexArray_args args = *(gl_wrap_handler_glBindVertexArray_args*)argsPtr;
	gl_wrap_context_glBindVertexArray(ctx, args.array);
}

inline void gl_wrap_handler_glDeleteVertexArrays(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteVertexArrays_args args = *(gl_wrap_handler_glDeleteVertexArrays_args*)argsPtr;
	gl_wrap_context_glDeleteVertexArrays(ctx, args.n, args.arrays);
}

inline void gl_wrap_handler_glGenVertexArrays(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenVertexArrays_args args = *(gl_wrap_handler_glGenVertexArrays_args*)argsPtr;
	gl_wrap_context_glGenVertexArrays(ctx, args.n, args.arrays);
}

inline void gl_wrap_handler_glGetIntegeri_v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetIntegeri_v_args args = *(gl_wrap_handler_glGetIntegeri_v_args*)argsPtr;
	gl_wrap_context_glGetIntegeri_v(ctx, args.target, args.index, args.data);
}

inline void gl_wrap_handler_glBeginTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBeginTransformFeedback_args args = *(gl_wrap_handler_glBeginTransformFeedback_args*)argsPtr;
	gl_wrap_context_glBeginTransformFeedback(ctx, args.primitiveMode);
}

inline void gl_wrap_handler_glEndTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEndTransformFeedback_args args = *(gl_wrap_handler_glEndTransformFeedback_args*)argsPtr;
	gl_wrap_context_glEndTransformFeedback(ctx);
}

inline void gl_wrap_handler_glBindBufferRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindBufferRange_args args = *(gl_wrap_handler_glBindBufferRange_args*)argsPtr;
	gl_wrap_context_glBindBufferRange(ctx, args.target, args.index, args.buffer, args.offset, args.size);
}

inline void gl_wrap_handler_glBindBufferBase(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindBufferBase_args args = *(gl_wrap_handler_glBindBufferBase_args*)argsPtr;
	gl_wrap_context_glBindBufferBase(ctx, args.target, args.index, args.buffer);
}

inline void gl_wrap_handler_glTransformFeedbackVaryings(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTransformFeedbackVaryings_args args = *(gl_wrap_handler_glTransformFeedbackVaryings_args*)argsPtr;
	gl_wrap_context_glTransformFeedbackVaryings(ctx, args.program, args.count, args.varyings, args.bufferMode);
}

inline void gl_wrap_handler_glGetTransformFeedbackVarying(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTransformFeedbackVarying_args args = *(gl_wrap_handler_glGetTransformFeedbackVarying_args*)argsPtr;
	gl_wrap_context_glGetTransformFeedbackVarying(ctx, args.program, args.index, args.bufSize, args.length, args.size, args.type, args.name);
}

inline void gl_wrap_handler_glVertexAttribIPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribIPointer_args args = *(gl_wrap_handler_glVertexAttribIPointer_args*)argsPtr;
	gl_wrap_context_glVertexAttribIPointer(ctx, args.index, args.size, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glGetVertexAttribIiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribIiv_args args = *(gl_wrap_handler_glGetVertexAttribIiv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribIiv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribIuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribIuiv_args args = *(gl_wrap_handler_glGetVertexAttribIuiv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribIuiv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glVertexAttribI4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4i_args args = *(gl_wrap_handler_glVertexAttribI4i_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4i(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttribI4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4ui_args args = *(gl_wrap_handler_glVertexAttribI4ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4ui(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttribI4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4iv_args args = *(gl_wrap_handler_glVertexAttribI4iv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4iv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4uiv_args args = *(gl_wrap_handler_glVertexAttribI4uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4uiv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glGetUniformuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformuiv_args args = *(gl_wrap_handler_glGetUniformuiv_args*)argsPtr;
	gl_wrap_context_glGetUniformuiv(ctx, args.program, args.location, args.params);
}

inline void gl_wrap_handler_glUniform1ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1ui_args args = *(gl_wrap_handler_glUniform1ui_args*)argsPtr;
	gl_wrap_context_glUniform1ui(ctx, args.location, args.v0);
}

inline void gl_wrap_handler_glUniform2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2ui_args args = *(gl_wrap_handler_glUniform2ui_args*)argsPtr;
	gl_wrap_context_glUniform2ui(ctx, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glUniform3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3ui_args args = *(gl_wrap_handler_glUniform3ui_args*)argsPtr;
	gl_wrap_context_glUniform3ui(ctx, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glUniform4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4ui_args args = *(gl_wrap_handler_glUniform4ui_args*)argsPtr;
	gl_wrap_context_glUniform4ui(ctx, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glUniform1uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1uiv_args args = *(gl_wrap_handler_glUniform1uiv_args*)argsPtr;
	gl_wrap_context_glUniform1uiv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2uiv_args args = *(gl_wrap_handler_glUniform2uiv_args*)argsPtr;
	gl_wrap_context_glUniform2uiv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3uiv_args args = *(gl_wrap_handler_glUniform3uiv_args*)argsPtr;
	gl_wrap_context_glUniform3uiv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4uiv_args args = *(gl_wrap_handler_glUniform4uiv_args*)argsPtr;
	gl_wrap_context_glUniform4uiv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glClearBufferiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferiv_args args = *(gl_wrap_handler_glClearBufferiv_args*)argsPtr;
	gl_wrap_context_glClearBufferiv(ctx, args.buffer, args.drawbuffer, args.value);
}

inline void gl_wrap_handler_glClearBufferuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferuiv_args args = *(gl_wrap_handler_glClearBufferuiv_args*)argsPtr;
	gl_wrap_context_glClearBufferuiv(ctx, args.buffer, args.drawbuffer, args.value);
}

inline void gl_wrap_handler_glClearBufferfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferfv_args args = *(gl_wrap_handler_glClearBufferfv_args*)argsPtr;
	gl_wrap_context_glClearBufferfv(ctx, args.buffer, args.drawbuffer, args.value);
}

inline void gl_wrap_handler_glClearBufferfi(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferfi_args args = *(gl_wrap_handler_glClearBufferfi_args*)argsPtr;
	gl_wrap_context_glClearBufferfi(ctx, args.buffer, args.drawbuffer, args.depth, args.stencil);
}

inline void gl_wrap_handler_glCopyBufferSubData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyBufferSubData_args args = *(gl_wrap_handler_glCopyBufferSubData_args*)argsPtr;
	gl_wrap_context_glCopyBufferSubData(ctx, args.readTarget, args.writeTarget, args.readOffset, args.writeOffset, args.size);
}

inline void gl_wrap_handler_glGetUniformIndices(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformIndices_args args = *(gl_wrap_handler_glGetUniformIndices_args*)argsPtr;
	gl_wrap_context_glGetUniformIndices(ctx, args.program, args.uniformCount, args.uniformNames, args.uniformIndices);
}

inline void gl_wrap_handler_glGetActiveUniformsiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniformsiv_args args = *(gl_wrap_handler_glGetActiveUniformsiv_args*)argsPtr;
	gl_wrap_context_glGetActiveUniformsiv(ctx, args.program, args.uniformCount, args.uniformIndices, args.pname, args.params);
}

inline void gl_wrap_handler_glGetActiveUniformBlockiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniformBlockiv_args args = *(gl_wrap_handler_glGetActiveUniformBlockiv_args*)argsPtr;
	gl_wrap_context_glGetActiveUniformBlockiv(ctx, args.program, args.uniformBlockIndex, args.pname, args.params);
}

inline void gl_wrap_handler_glGetActiveUniformBlockName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniformBlockName_args args = *(gl_wrap_handler_glGetActiveUniformBlockName_args*)argsPtr;
	gl_wrap_context_glGetActiveUniformBlockName(ctx, args.program, args.uniformBlockIndex, args.bufSize, args.length, args.uniformBlockName);
}

inline void gl_wrap_handler_glUniformBlockBinding(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformBlockBinding_args args = *(gl_wrap_handler_glUniformBlockBinding_args*)argsPtr;
	gl_wrap_context_glUniformBlockBinding(ctx, args.program, args.uniformBlockIndex, args.uniformBlockBinding);
}

inline void gl_wrap_handler_glDrawArraysInstanced(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawArraysInstanced_args args = *(gl_wrap_handler_glDrawArraysInstanced_args*)argsPtr;
	gl_wrap_context_glDrawArraysInstanced(ctx, args.mode, args.first, args.count, args.instancecount);
}

inline void gl_wrap_handler_glDrawElementsInstanced(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElementsInstanced_args args = *(gl_wrap_handler_glDrawElementsInstanced_args*)argsPtr;
	gl_wrap_context_glDrawElementsInstanced(ctx, args.mode, args.count, args.type, args.indices, args.instancecount);
}

inline void gl_wrap_handler_glDeleteSync(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteSync_args args = *(gl_wrap_handler_glDeleteSync_args*)argsPtr;
	gl_wrap_context_glDeleteSync(ctx, args.sync);
}

inline void gl_wrap_handler_glWaitSync(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWaitSync_args args = *(gl_wrap_handler_glWaitSync_args*)argsPtr;
	gl_wrap_context_glWaitSync(ctx, args.sync, args.flags, args.timeout);
}

inline void gl_wrap_handler_glGetInteger64v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetInteger64v_args args = *(gl_wrap_handler_glGetInteger64v_args*)argsPtr;
	gl_wrap_context_glGetInteger64v(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetSynciv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetSynciv_args args = *(gl_wrap_handler_glGetSynciv_args*)argsPtr;
	gl_wrap_context_glGetSynciv(ctx, args.sync, args.pname, args.bufSize, args.length, args.values);
}

inline void gl_wrap_handler_glGetInteger64i_v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetInteger64i_v_args args = *(gl_wrap_handler_glGetInteger64i_v_args*)argsPtr;
	gl_wrap_context_glGetInteger64i_v(ctx, args.target, args.index, args.data);
}

inline void gl_wrap_handler_glGetBufferParameteri64v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBufferParameteri64v_args args = *(gl_wrap_handler_glGetBufferParameteri64v_args*)argsPtr;
	gl_wrap_context_glGetBufferParameteri64v(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGenSamplers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenSamplers_args args = *(gl_wrap_handler_glGenSamplers_args*)argsPtr;
	gl_wrap_context_glGenSamplers(ctx, args.count, args.samplers);
}

inline void gl_wrap_handler_glDeleteSamplers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteSamplers_args args = *(gl_wrap_handler_glDeleteSamplers_args*)argsPtr;
	gl_wrap_context_glDeleteSamplers(ctx, args.count, args.samplers);
}

inline void gl_wrap_handler_glBindSampler(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindSampler_args args = *(gl_wrap_handler_glBindSampler_args*)argsPtr;
	gl_wrap_context_glBindSampler(ctx, args.unit, args.sampler);
}

inline void gl_wrap_handler_glSamplerParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameteri_args args = *(gl_wrap_handler_glSamplerParameteri_args*)argsPtr;
	gl_wrap_context_glSamplerParameteri(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glSamplerParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameteriv_args args = *(gl_wrap_handler_glSamplerParameteriv_args*)argsPtr;
	gl_wrap_context_glSamplerParameteriv(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glSamplerParameterf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameterf_args args = *(gl_wrap_handler_glSamplerParameterf_args*)argsPtr;
	gl_wrap_context_glSamplerParameterf(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glSamplerParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameterfv_args args = *(gl_wrap_handler_glSamplerParameterfv_args*)argsPtr;
	gl_wrap_context_glSamplerParameterfv(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glGetSamplerParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetSamplerParameteriv_args args = *(gl_wrap_handler_glGetSamplerParameteriv_args*)argsPtr;
	gl_wrap_context_glGetSamplerParameteriv(ctx, args.sampler, args.pname, args.params);
}

inline void gl_wrap_handler_glGetSamplerParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetSamplerParameterfv_args args = *(gl_wrap_handler_glGetSamplerParameterfv_args*)argsPtr;
	gl_wrap_context_glGetSamplerParameterfv(ctx, args.sampler, args.pname, args.params);
}

inline void gl_wrap_handler_glVertexAttribDivisor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribDivisor_args args = *(gl_wrap_handler_glVertexAttribDivisor_args*)argsPtr;
	gl_wrap_context_glVertexAttribDivisor(ctx, args.index, args.divisor);
}

inline void gl_wrap_handler_glBindTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindTransformFeedback_args args = *(gl_wrap_handler_glBindTransformFeedback_args*)argsPtr;
	gl_wrap_context_glBindTransformFeedback(ctx, args.target, args.id);
}

inline void gl_wrap_handler_glDeleteTransformFeedbacks(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteTransformFeedbacks_args args = *(gl_wrap_handler_glDeleteTransformFeedbacks_args*)argsPtr;
	gl_wrap_context_glDeleteTransformFeedbacks(ctx, args.n, args.ids);
}

inline void gl_wrap_handler_glGenTransformFeedbacks(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenTransformFeedbacks_args args = *(gl_wrap_handler_glGenTransformFeedbacks_args*)argsPtr;
	gl_wrap_context_glGenTransformFeedbacks(ctx, args.n, args.ids);
}

inline void gl_wrap_handler_glPauseTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPauseTransformFeedback_args args = *(gl_wrap_handler_glPauseTransformFeedback_args*)argsPtr;
	gl_wrap_context_glPauseTransformFeedback(ctx);
}

inline void gl_wrap_handler_glResumeTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glResumeTransformFeedback_args args = *(gl_wrap_handler_glResumeTransformFeedback_args*)argsPtr;
	gl_wrap_context_glResumeTransformFeedback(ctx);
}

inline void gl_wrap_handler_glGetProgramBinary(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramBinary_args args = *(gl_wrap_handler_glGetProgramBinary_args*)argsPtr;
	gl_wrap_context_glGetProgramBinary(ctx, args.program, args.bufSize, args.length, args.binaryFormat, args.binary);
}

inline void gl_wrap_handler_glProgramBinary(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramBinary_args args = *(gl_wrap_handler_glProgramBinary_args*)argsPtr;
	gl_wrap_context_glProgramBinary(ctx, args.program, args.binaryFormat, args.binary, args.length);
}

inline void gl_wrap_handler_glProgramParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramParameteri_args args = *(gl_wrap_handler_glProgramParameteri_args*)argsPtr;
	gl_wrap_context_glProgramParameteri(ctx, args.program, args.pname, args.value);
}

inline void gl_wrap_handler_glInvalidateFramebuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInvalidateFramebuffer_args args = *(gl_wrap_handler_glInvalidateFramebuffer_args*)argsPtr;
	gl_wrap_context_glInvalidateFramebuffer(ctx, args.target, args.numAttachments, args.attachments);
}

inline void gl_wrap_handler_glInvalidateSubFramebuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInvalidateSubFramebuffer_args args = *(gl_wrap_handler_glInvalidateSubFramebuffer_args*)argsPtr;
	gl_wrap_context_glInvalidateSubFramebuffer(ctx, args.target, args.numAttachments, args.attachments, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glTexStorage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexStorage2D_args args = *(gl_wrap_handler_glTexStorage2D_args*)argsPtr;
	gl_wrap_context_glTexStorage2D(ctx, args.target, args.levels, args.internalformat, args.width, args.height);
}

inline void gl_wrap_handler_glTexStorage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexStorage3D_args args = *(gl_wrap_handler_glTexStorage3D_args*)argsPtr;
	gl_wrap_context_glTexStorage3D(ctx, args.target, args.levels, args.internalformat, args.width, args.height, args.depth);
}

inline void gl_wrap_handler_glGetInternalformativ(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetInternalformativ_args args = *(gl_wrap_handler_glGetInternalformativ_args*)argsPtr;
	gl_wrap_context_glGetInternalformativ(ctx, args.target, args.internalformat, args.pname, args.bufSize, args.params);
}

inline void gl_wrap_handler_glDispatchCompute(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDispatchCompute_args args = *(gl_wrap_handler_glDispatchCompute_args*)argsPtr;
	gl_wrap_context_glDispatchCompute(ctx, args.num_groups_x, args.num_groups_y, args.num_groups_z);
}

inline void gl_wrap_handler_glDispatchComputeIndirect(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDispatchComputeIndirect_args args = *(gl_wrap_handler_glDispatchComputeIndirect_args*)argsPtr;
	gl_wrap_context_glDispatchComputeIndirect(ctx, args.indirect);
}

inline void gl_wrap_handler_glDrawArraysIndirect(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawArraysIndirect_args args = *(gl_wrap_handler_glDrawArraysIndirect_args*)argsPtr;
	gl_wrap_context_glDrawArraysIndirect(ctx, args.mode, args.indirect);
}

inline void gl_wrap_handler_glDrawElementsIndirect(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElementsIndirect_args args = *(gl_wrap_handler_glDrawElementsIndirect_args*)argsPtr;
	gl_wrap_context_glDrawElementsIndirect(ctx, args.mode, args.type, args.indirect);
}

inline void gl_wrap_handler_glFramebufferParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferParameteri_args args = *(gl_wrap_handler_glFramebufferParameteri_args*)argsPtr;
	gl_wrap_context_glFramebufferParameteri(ctx, args.target, args.pname, args.param);
}

inline void gl_wrap_handler_glGetFramebufferParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetFramebufferParameteriv_args args = *(gl_wrap_handler_glGetFramebufferParameteriv_args*)argsPtr;
	gl_wrap_context_glGetFramebufferParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetProgramInterfaceiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramInterfaceiv_args args = *(gl_wrap_handler_glGetProgramInterfaceiv_args*)argsPtr;
	gl_wrap_context_glGetProgramInterfaceiv(ctx, args.program, args.programInterface, args.pname, args.params);
}

inline void gl_wrap_handler_glGetProgramResourceName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramResourceName_args args = *(gl_wrap_handler_glGetProgramResourceName_args*)argsPtr;
	gl_wrap_context_glGetProgramResourceName(ctx, args.program, args.programInterface, args.index, args.bufSize, args.length, args.name);
}

inline void gl_wrap_handler_glGetProgramResourceiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramResourceiv_args args = *(gl_wrap_handler_glGetProgramResourceiv_args*)argsPtr;
	gl_wrap_context_glGetProgramResourceiv(ctx, args.program, args.programInterface, args.index, args.propCount, args.props, args.bufSize, args.length, args.params);
}

inline void gl_wrap_handler_glUseProgramStages(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUseProgramStages_args args = *(gl_wrap_handler_glUseProgramStages_args*)argsPtr;
	gl_wrap_context_glUseProgramStages(ctx, args.pipeline, args.stages, args.program);
}

inline void gl_wrap_handler_glActiveShaderProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glActiveShaderProgram_args args = *(gl_wrap_handler_glActiveShaderProgram_args*)argsPtr;
	gl_wrap_context_glActiveShaderProgram(ctx, args.pipeline, args.program);
}

inline void gl_wrap_handler_glBindProgramPipeline(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindProgramPipeline_args args = *(gl_wrap_handler_glBindProgramPipeline_args*)argsPtr;
	gl_wrap_context_glBindProgramPipeline(ctx, args.pipeline);
}

inline void gl_wrap_handler_glDeleteProgramPipelines(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteProgramPipelines_args args = *(gl_wrap_handler_glDeleteProgramPipelines_args*)argsPtr;
	gl_wrap_context_glDeleteProgramPipelines(ctx, args.n, args.pipelines);
}

inline void gl_wrap_handler_glGenProgramPipelines(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenProgramPipelines_args args = *(gl_wrap_handler_glGenProgramPipelines_args*)argsPtr;
	gl_wrap_context_glGenProgramPipelines(ctx, args.n, args.pipelines);
}

inline void gl_wrap_handler_glGetProgramPipelineiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramPipelineiv_args args = *(gl_wrap_handler_glGetProgramPipelineiv_args*)argsPtr;
	gl_wrap_context_glGetProgramPipelineiv(ctx, args.pipeline, args.pname, args.params);
}

inline void gl_wrap_handler_glProgramUniform1i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1i_args args = *(gl_wrap_handler_glProgramUniform1i_args*)argsPtr;
	gl_wrap_context_glProgramUniform1i(ctx, args.program, args.location, args.v0);
}

inline void gl_wrap_handler_glProgramUniform2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2i_args args = *(gl_wrap_handler_glProgramUniform2i_args*)argsPtr;
	gl_wrap_context_glProgramUniform2i(ctx, args.program, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glProgramUniform3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3i_args args = *(gl_wrap_handler_glProgramUniform3i_args*)argsPtr;
	gl_wrap_context_glProgramUniform3i(ctx, args.program, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glProgramUniform4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4i_args args = *(gl_wrap_handler_glProgramUniform4i_args*)argsPtr;
	gl_wrap_context_glProgramUniform4i(ctx, args.program, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glProgramUniform1ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1ui_args args = *(gl_wrap_handler_glProgramUniform1ui_args*)argsPtr;
	gl_wrap_context_glProgramUniform1ui(ctx, args.program, args.location, args.v0);
}

inline void gl_wrap_handler_glProgramUniform2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2ui_args args = *(gl_wrap_handler_glProgramUniform2ui_args*)argsPtr;
	gl_wrap_context_glProgramUniform2ui(ctx, args.program, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glProgramUniform3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3ui_args args = *(gl_wrap_handler_glProgramUniform3ui_args*)argsPtr;
	gl_wrap_context_glProgramUniform3ui(ctx, args.program, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glProgramUniform4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4ui_args args = *(gl_wrap_handler_glProgramUniform4ui_args*)argsPtr;
	gl_wrap_context_glProgramUniform4ui(ctx, args.program, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glProgramUniform1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1f_args args = *(gl_wrap_handler_glProgramUniform1f_args*)argsPtr;
	gl_wrap_context_glProgramUniform1f(ctx, args.program, args.location, args.v0);
}

inline void gl_wrap_handler_glProgramUniform2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2f_args args = *(gl_wrap_handler_glProgramUniform2f_args*)argsPtr;
	gl_wrap_context_glProgramUniform2f(ctx, args.program, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glProgramUniform3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3f_args args = *(gl_wrap_handler_glProgramUniform3f_args*)argsPtr;
	gl_wrap_context_glProgramUniform3f(ctx, args.program, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glProgramUniform4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4f_args args = *(gl_wrap_handler_glProgramUniform4f_args*)argsPtr;
	gl_wrap_context_glProgramUniform4f(ctx, args.program, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glProgramUniform1iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1iv_args args = *(gl_wrap_handler_glProgramUniform1iv_args*)argsPtr;
	gl_wrap_context_glProgramUniform1iv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2iv_args args = *(gl_wrap_handler_glProgramUniform2iv_args*)argsPtr;
	gl_wrap_context_glProgramUniform2iv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3iv_args args = *(gl_wrap_handler_glProgramUniform3iv_args*)argsPtr;
	gl_wrap_context_glProgramUniform3iv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4iv_args args = *(gl_wrap_handler_glProgramUniform4iv_args*)argsPtr;
	gl_wrap_context_glProgramUniform4iv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform1uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1uiv_args args = *(gl_wrap_handler_glProgramUniform1uiv_args*)argsPtr;
	gl_wrap_context_glProgramUniform1uiv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2uiv_args args = *(gl_wrap_handler_glProgramUniform2uiv_args*)argsPtr;
	gl_wrap_context_glProgramUniform2uiv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3uiv_args args = *(gl_wrap_handler_glProgramUniform3uiv_args*)argsPtr;
	gl_wrap_context_glProgramUniform3uiv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4uiv_args args = *(gl_wrap_handler_glProgramUniform4uiv_args*)argsPtr;
	gl_wrap_context_glProgramUniform4uiv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1fv_args args = *(gl_wrap_handler_glProgramUniform1fv_args*)argsPtr;
	gl_wrap_context_glProgramUniform1fv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2fv_args args = *(gl_wrap_handler_glProgramUniform2fv_args*)argsPtr;
	gl_wrap_context_glProgramUniform2fv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3fv_args args = *(gl_wrap_handler_glProgramUniform3fv_args*)argsPtr;
	gl_wrap_context_glProgramUniform3fv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4fv_args args = *(gl_wrap_handler_glProgramUniform4fv_args*)argsPtr;
	gl_wrap_context_glProgramUniform4fv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2fv_args args = *(gl_wrap_handler_glProgramUniformMatrix2fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3fv_args args = *(gl_wrap_handler_glProgramUniformMatrix3fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4fv_args args = *(gl_wrap_handler_glProgramUniformMatrix4fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2x3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2x3fv_args args = *(gl_wrap_handler_glProgramUniformMatrix2x3fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2x3fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3x2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3x2fv_args args = *(gl_wrap_handler_glProgramUniformMatrix3x2fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3x2fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2x4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2x4fv_args args = *(gl_wrap_handler_glProgramUniformMatrix2x4fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2x4fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4x2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4x2fv_args args = *(gl_wrap_handler_glProgramUniformMatrix4x2fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4x2fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3x4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3x4fv_args args = *(gl_wrap_handler_glProgramUniformMatrix3x4fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3x4fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4x3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4x3fv_args args = *(gl_wrap_handler_glProgramUniformMatrix4x3fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4x3fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glValidateProgramPipeline(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glValidateProgramPipeline_args args = *(gl_wrap_handler_glValidateProgramPipeline_args*)argsPtr;
	gl_wrap_context_glValidateProgramPipeline(ctx, args.pipeline);
}

inline void gl_wrap_handler_glGetProgramPipelineInfoLog(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramPipelineInfoLog_args args = *(gl_wrap_handler_glGetProgramPipelineInfoLog_args*)argsPtr;
	gl_wrap_context_glGetProgramPipelineInfoLog(ctx, args.pipeline, args.bufSize, args.length, args.infoLog);
}

inline void gl_wrap_handler_glBindImageTexture(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindImageTexture_args args = *(gl_wrap_handler_glBindImageTexture_args*)argsPtr;
	gl_wrap_context_glBindImageTexture(ctx, args.unit, args.texture, args.level, args.layered, args.layer, args.access, args.format);
}

inline void gl_wrap_handler_glGetBooleani_v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBooleani_v_args args = *(gl_wrap_handler_glGetBooleani_v_args*)argsPtr;
	gl_wrap_context_glGetBooleani_v(ctx, args.target, args.index, args.data);
}

inline void gl_wrap_handler_glMemoryBarrier(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMemoryBarrier_args args = *(gl_wrap_handler_glMemoryBarrier_args*)argsPtr;
	gl_wrap_context_glMemoryBarrier(ctx, args.barriers);
}

inline void gl_wrap_handler_glMemoryBarrierByRegion(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMemoryBarrierByRegion_args args = *(gl_wrap_handler_glMemoryBarrierByRegion_args*)argsPtr;
	gl_wrap_context_glMemoryBarrierByRegion(ctx, args.barriers);
}

inline void gl_wrap_handler_glTexStorage2DMultisample(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexStorage2DMultisample_args args = *(gl_wrap_handler_glTexStorage2DMultisample_args*)argsPtr;
	gl_wrap_context_glTexStorage2DMultisample(ctx, args.target, args.samples, args.internalformat, args.width, args.height, args.fixedsamplelocations);
}

inline void gl_wrap_handler_glGetMultisamplefv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetMultisamplefv_args args = *(gl_wrap_handler_glGetMultisamplefv_args*)argsPtr;
	gl_wrap_context_glGetMultisamplefv(ctx, args.pname, args.index, args.val);
}

inline void gl_wrap_handler_glSampleMaski(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSampleMaski_args args = *(gl_wrap_handler_glSampleMaski_args*)argsPtr;
	gl_wrap_context_glSampleMaski(ctx, args.maskNumber, args.mask);
}

inline void gl_wrap_handler_glGetTexLevelParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexLevelParameteriv_args args = *(gl_wrap_handler_glGetTexLevelParameteriv_args*)argsPtr;
	gl_wrap_context_glGetTexLevelParameteriv(ctx, args.target, args.level, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexLevelParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexLevelParameterfv_args args = *(gl_wrap_handler_glGetTexLevelParameterfv_args*)argsPtr;
	gl_wrap_context_glGetTexLevelParameterfv(ctx, args.target, args.level, args.pname, args.params);
}

inline void gl_wrap_handler_glBindVertexBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindVertexBuffer_args args = *(gl_wrap_handler_glBindVertexBuffer_args*)argsPtr;
	gl_wrap_context_glBindVertexBuffer(ctx, args.bindingindex, args.buffer, args.offset, args.stride);
}

inline void gl_wrap_handler_glVertexAttribFormat(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribFormat_args args = *(gl_wrap_handler_glVertexAttribFormat_args*)argsPtr;
	gl_wrap_context_glVertexAttribFormat(ctx, args.attribindex, args.size, args.type, args.normalized, args.relativeoffset);
}

inline void gl_wrap_handler_glVertexAttribIFormat(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribIFormat_args args = *(gl_wrap_handler_glVertexAttribIFormat_args*)argsPtr;
	gl_wrap_context_glVertexAttribIFormat(ctx, args.attribindex, args.size, args.type, args.relativeoffset);
}

inline void gl_wrap_handler_glVertexAttribBinding(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribBinding_args args = *(gl_wrap_handler_glVertexAttribBinding_args*)argsPtr;
	gl_wrap_context_glVertexAttribBinding(ctx, args.attribindex, args.bindingindex);
}

inline void gl_wrap_handler_glVertexBindingDivisor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexBindingDivisor_args args = *(gl_wrap_handler_glVertexBindingDivisor_args*)argsPtr;
	gl_wrap_context_glVertexBindingDivisor(ctx, args.bindingindex, args.divisor);
}

// This is the jump table used for executing each batched OpenGL function
// without doing a large (approx. 1k cases) and costly switch statement.
gl_wrap_jump_handler gl_wrap_jump_table[] = {
	gl_wrap_handler_glActiveTexture,
	gl_wrap_handler_glAttachShader,
	gl_wrap_handler_glBindAttribLocation,
	gl_wrap_handler_glBindBuffer,
	gl_wrap_handler_glBindFramebuffer,
	gl_wrap_handler_glBindRenderbuffer,
	gl_wrap_handler_glBindTexture,
	gl_wrap_handler_glBlendColor,
	gl_wrap_handler_glBlendEquation,
	gl_wrap_handler_glBlendEquationSeparate,
	gl_wrap_handler_glBlendFunc,
	gl_wrap_handler_glBlendFuncSeparate,
	gl_wrap_handler_glBufferData,
	gl_wrap_handler_glBufferSubData,
	gl_wrap_handler_glClear,
	gl_wrap_handler_glClearColor,
	gl_wrap_handler_glClearDepthf,
	gl_wrap_handler_glClearStencil,
	gl_wrap_handler_glColorMask,
	gl_wrap_handler_glCompileShader,
	gl_wrap_handler_glCompressedTexImage2D,
	gl_wrap_handler_glCompressedTexSubImage2D,
	gl_wrap_handler_glCopyTexImage2D,
	gl_wrap_handler_glCopyTexSubImage2D,
	gl_wrap_handler_glCullFace,
	gl_wrap_handler_glDeleteBuffers,
	gl_wrap_handler_glDeleteFramebuffers,
	gl_wrap_handler_glDeleteProgram,
	gl_wrap_handler_glDeleteRenderbuffers,
	gl_wrap_handler_glDeleteShader,
	gl_wrap_handler_glDeleteTextures,
	gl_wrap_handler_glDepthFunc,
	gl_wrap_handler_glDepthMask,
	gl_wrap_handler_glDepthRangef,
	gl_wrap_handler_glDetachShader,
	gl_wrap_handler_glDisable,
	gl_wrap_handler_glDisableVertexAttribArray,
	gl_wrap_handler_glDrawArrays,
	gl_wrap_handler_glDrawElements,
	gl_wrap_handler_glEnable,
	gl_wrap_handler_glEnableVertexAttribArray,
	gl_wrap_handler_glFinish,
	gl_wrap_handler_glFlush,
	gl_wrap_handler_glFramebufferRenderbuffer,
	gl_wrap_handler_glFramebufferTexture2D,
	gl_wrap_handler_glFrontFace,
	gl_wrap_handler_glGenBuffers,
	gl_wrap_handler_glGenerateMipmap,
	gl_wrap_handler_glGenFramebuffers,
	gl_wrap_handler_glGenRenderbuffers,
	gl_wrap_handler_glGenTextures,
	gl_wrap_handler_glGetActiveAttrib,
	gl_wrap_handler_glGetActiveUniform,
	gl_wrap_handler_glGetAttachedShaders,
	gl_wrap_handler_glGetBooleanv,
	gl_wrap_handler_glGetBufferParameteriv,
	gl_wrap_handler_glGetFloatv,
	gl_wrap_handler_glGetFramebufferAttachmentParameteriv,
	gl_wrap_handler_glGetIntegerv,
	gl_wrap_handler_glGetProgramiv,
	gl_wrap_handler_glGetProgramInfoLog,
	gl_wrap_handler_glGetRenderbufferParameteriv,
	gl_wrap_handler_glGetShaderiv,
	gl_wrap_handler_glGetShaderInfoLog,
	gl_wrap_handler_glGetShaderPrecisionFormat,
	gl_wrap_handler_glGetShaderSource,
	gl_wrap_handler_glGetTexParameterfv,
	gl_wrap_handler_glGetTexParameteriv,
	gl_wrap_handler_glGetUniformfv,
	gl_wrap_handler_glGetUniformiv,
	gl_wrap_handler_glGetVertexAttribfv,
	gl_wrap_handler_glGetVertexAttribiv,
	gl_wrap_handler_glGetVertexAttribPointerv,
	gl_wrap_handler_glHint,
	gl_wrap_handler_glLineWidth,
	gl_wrap_handler_glLinkProgram,
	gl_wrap_handler_glPixelStorei,
	gl_wrap_handler_glPolygonOffset,
	gl_wrap_handler_glReadPixels,
	gl_wrap_handler_glReleaseShaderCompiler,
	gl_wrap_handler_glRenderbufferStorage,
	gl_wrap_handler_glSampleCoverage,
	gl_wrap_handler_glScissor,
	gl_wrap_handler_glShaderBinary,
	gl_wrap_handler_glShaderSource,
	gl_wrap_handler_glStencilFunc,
	gl_wrap_handler_glStencilFuncSeparate,
	gl_wrap_handler_glStencilMask,
	gl_wrap_handler_glStencilMaskSeparate,
	gl_wrap_handler_glStencilOp,
	gl_wrap_handler_glStencilOpSeparate,
	gl_wrap_handler_glTexImage2D,
	gl_wrap_handler_glTexParameterf,
	gl_wrap_handler_glTexParameterfv,
	gl_wrap_handler_glTexParameteri,
	gl_wrap_handler_glTexParameteriv,
	gl_wrap_handler_glTexSubImage2D,
	gl_wrap_handler_glUniform1f,
	gl_wrap_handler_glUniform1fv,
	gl_wrap_handler_glUniform1i,
	gl_wrap_handler_glUniform1iv,
	gl_wrap_handler_glUniform2f,
	gl_wrap_handler_glUniform2fv,
	gl_wrap_handler_glUniform2i,
	gl_wrap_handler_glUniform2iv,
	gl_wrap_handler_glUniform3f,
	gl_wrap_handler_glUniform3fv,
	gl_wrap_handler_glUniform3i,
	gl_wrap_handler_glUniform3iv,
	gl_wrap_handler_glUniform4f,
	gl_wrap_handler_glUniform4fv,
	gl_wrap_handler_glUniform4i,
	gl_wrap_handler_glUniform4iv,
	gl_wrap_handler_glUniformMatrix2fv,
	gl_wrap_handler_glUniformMatrix3fv,
	gl_wrap_handler_glUniformMatrix4fv,
	gl_wrap_handler_glUseProgram,
	gl_wrap_handler_glValidateProgram,
	gl_wrap_handler_glVertexAttrib1f,
	gl_wrap_handler_glVertexAttrib1fv,
	gl_wrap_handler_glVertexAttrib2f,
	gl_wrap_handler_glVertexAttrib2fv,
	gl_wrap_handler_glVertexAttrib3f,
	gl_wrap_handler_glVertexAttrib3fv,
	gl_wrap_handler_glVertexAttrib4f,
	gl_wrap_handler_glVertexAttrib4fv,
	gl_wrap_handler_glVertexAttribPointer,
	gl_wrap_handler_glViewport,
	gl_wrap_handler_glReadBuffer,
	gl_wrap_handler_glDrawRangeElements,
	gl_wrap_handler_glTexImage3D,
	gl_wrap_handler_glTexSubImage3D,
	gl_wrap_handler_glCopyTexSubImage3D,
	gl_wrap_handler_glCompressedTexImage3D,
	gl_wrap_handler_glCompressedTexSubImage3D,
	gl_wrap_handler_glGenQueries,
	gl_wrap_handler_glDeleteQueries,
	gl_wrap_handler_glBeginQuery,
	gl_wrap_handler_glEndQuery,
	gl_wrap_handler_glGetQueryiv,
	gl_wrap_handler_glGetQueryObjectuiv,
	gl_wrap_handler_glGetBufferPointerv,
	gl_wrap_handler_glDrawBuffers,
	gl_wrap_handler_glUniformMatrix2x3fv,
	gl_wrap_handler_glUniformMatrix3x2fv,
	gl_wrap_handler_glUniformMatrix2x4fv,
	gl_wrap_handler_glUniformMatrix4x2fv,
	gl_wrap_handler_glUniformMatrix3x4fv,
	gl_wrap_handler_glUniformMatrix4x3fv,
	gl_wrap_handler_glBlitFramebuffer,
	gl_wrap_handler_glRenderbufferStorageMultisample,
	gl_wrap_handler_glFramebufferTextureLayer,
	gl_wrap_handler_glMapBufferRange,
	gl_wrap_handler_glFlushMappedBufferRange,
	gl_wrap_handler_glBindVertexArray,
	gl_wrap_handler_glDeleteVertexArrays,
	gl_wrap_handler_glGenVertexArrays,
	gl_wrap_handler_glGetIntegeri_v,
	gl_wrap_handler_glBeginTransformFeedback,
	gl_wrap_handler_glEndTransformFeedback,
	gl_wrap_handler_glBindBufferRange,
	gl_wrap_handler_glBindBufferBase,
	gl_wrap_handler_glTransformFeedbackVaryings,
	gl_wrap_handler_glGetTransformFeedbackVarying,
	gl_wrap_handler_glVertexAttribIPointer,
	gl_wrap_handler_glGetVertexAttribIiv,
	gl_wrap_handler_glGetVertexAttribIuiv,
	gl_wrap_handler_glVertexAttribI4i,
	gl_wrap_handler_glVertexAttribI4ui,
	gl_wrap_handler_glVertexAttribI4iv,
	gl_wrap_handler_glVertexAttribI4uiv,
	gl_wrap_handler_glGetUniformuiv,
	gl_wrap_handler_glUniform1ui,
	gl_wrap_handler_glUniform2ui,
	gl_wrap_handler_glUniform3ui,
	gl_wrap_handler_glUniform4ui,
	gl_wrap_handler_glUniform1uiv,
	gl_wrap_handler_glUniform2uiv,
	gl_wrap_handler_glUniform3uiv,
	gl_wrap_handler_glUniform4uiv,
	gl_wrap_handler_glClearBufferiv,
	gl_wrap_handler_glClearBufferuiv,
	gl_wrap_handler_glClearBufferfv,
	gl_wrap_handler_glClearBufferfi,
	gl_wrap_handler_glCopyBufferSubData,
	gl_wrap_handler_glGetUniformIndices,
	gl_wrap_handler_glGetActiveUniformsiv,
	gl_wrap_handler_glGetActiveUniformBlockiv,
	gl_wrap_handler_glGetActiveUniformBlockName,
	gl_wrap_handler_glUniformBlockBinding,
	gl_wrap_handler_glDrawArraysInstanced,
	gl_wrap_handler_glDrawElementsInstanced,
	gl_wrap_handler_glDeleteSync,
	gl_wrap_handler_glWaitSync,
	gl_wrap_handler_glGetInteger64v,
	gl_wrap_handler_glGetSynciv,
	gl_wrap_handler_glGetInteger64i_v,
	gl_wrap_handler_glGetBufferParameteri64v,
	gl_wrap_handler_glGenSamplers,
	gl_wrap_handler_glDeleteSamplers,
	gl_wrap_handler_glBindSampler,
	gl_wrap_handler_glSamplerParameteri,
	gl_wrap_handler_glSamplerParameteriv,
	gl_wrap_handler_glSamplerParameterf,
	gl_wrap_handler_glSamplerParameterfv,
	gl_wrap_handler_glGetSamplerParameteriv,
	gl_wrap_handler_glGetSamplerParameterfv,
	gl_wrap_handler_glVertexAttribDivisor,
	gl_wrap_handler_glBindTransformFeedback,
	gl_wrap_handler_glDeleteTransformFeedbacks,
	gl_wrap_handler_glGenTransformFeedbacks,
	gl_wrap_handler_glPauseTransformFeedback,
	gl_wrap_handler_glResumeTransformFeedback,
	gl_wrap_handler_glGetProgramBinary,
	gl_wrap_handler_glProgramBinary,
	gl_wrap_handler_glProgramParameteri,
	gl_wrap_handler_glInvalidateFramebuffer,
	gl_wrap_handler_glInvalidateSubFramebuffer,
	gl_wrap_handler_glTexStorage2D,
	gl_wrap_handler_glTexStorage3D,
	gl_wrap_handler_glGetInternalformativ,
	gl_wrap_handler_glDispatchCompute,
	gl_wrap_handler_glDispatchComputeIndirect,
	gl_wrap_handler_glDrawArraysIndirect,
	gl_wrap_handler_glDrawElementsIndirect,
	gl_wrap_handler_glFramebufferParameteri,
	gl_wrap_handler_glGetFramebufferParameteriv,
	gl_wrap_handler_glGetProgramInterfaceiv,
	gl_wrap_handler_glGetProgramResourceName,
	gl_wrap_handler_glGetProgramResourceiv,
	gl_wrap_handler_glUseProgramStages,
	gl_wrap_handler_glActiveShaderProgram,
	gl_wrap_handler_glBindProgramPipeline,
	gl_wrap_handler_glDeleteProgramPipelines,
	gl_wrap_handler_glGenProgramPipelines,
	gl_wrap_handler_glGetProgramPipelineiv,
	gl_wrap_handler_glProgramUniform1i,
	gl_wrap_handler_glProgramUniform2i,
	gl_wrap_handler_glProgramUniform3i,
	gl_wrap_handler_glProgramUniform4i,
	gl_wrap_handler_glProgramUniform1ui,
	gl_wrap_handler_glProgramUniform2ui,
	gl_wrap_handler_glProgramUniform3ui,
	gl_wrap_handler_glProgramUniform4ui,
	gl_wrap_handler_glProgramUniform1f,
	gl_wrap_handler_glProgramUniform2f,
	gl_wrap_handler_glProgramUniform3f,
	gl_wrap_handler_glProgramUniform4f,
	gl_wrap_handler_glProgramUniform1iv,
	gl_wrap_handler_glProgramUniform2iv,
	gl_wrap_handler_glProgramUniform3iv,
	gl_wrap_handler_glProgramUniform4iv,
	gl_wrap_handler_glProgramUniform1uiv,
	gl_wrap_handler_glProgramUniform2uiv,
	gl_wrap_handler_glProgramUniform3uiv,
	gl_wrap_handler_glProgramUniform4uiv,
	gl_wrap_handler_glProgramUniform1fv,
	gl_wrap_handler_glProgramUniform2fv,
	gl_wrap_handler_glProgramUniform3fv,
	gl_wrap_handler_glProgramUniform4fv,
	gl_wrap_handler_glProgramUniformMatrix2fv,
	gl_wrap_handler_glProgramUniformMatrix3fv,
	gl_wrap_handler_glProgramUniformMatrix4fv,
	gl_wrap_handler_glProgramUniformMatrix2x3fv,
	gl_wrap_handler_glProgramUniformMatrix3x2fv,
	gl_wrap_handler_glProgramUniformMatrix2x4fv,
	gl_wrap_handler_glProgramUniformMatrix4x2fv,
	gl_wrap_handler_glProgramUniformMatrix3x4fv,
	gl_wrap_handler_glProgramUniformMatrix4x3fv,
	gl_wrap_handler_glValidateProgramPipeline,
	gl_wrap_handler_glGetProgramPipelineInfoLog,
	gl_wrap_handler_glBindImageTexture,
	gl_wrap_handler_glGetBooleani_v,
	gl_wrap_handler_glMemoryBarrier,
	gl_wrap_handler_glMemoryBarrierByRegion,
	gl_wrap_handler_glTexStorage2DMultisample,
	gl_wrap_handler_glGetMultisamplefv,
	gl_wrap_handler_glSampleMaski,
	gl_wrap_handler_glGetTexLevelParameteriv,
	gl_wrap_handler_glGetTexLevelParameterfv,
	gl_wrap_handler_glBindVertexBuffer,
	gl_wrap_handler_glVertexAttribFormat,
	gl_wrap_handler_glVertexAttribIFormat,
	gl_wrap_handler_glVertexAttribBinding,
	gl_wrap_handler_glVertexBindingDivisor,
};

// Executes the functions in a batch for a given context.
void gl_wrap_batch_exec(gl_wrap_context* ctx, gl_wrap_batch_func* funcs, int numFuncs) {
	int i;
	for(i = 0; i < numFuncs; i++) {
		// Grab the function from the array
		gl_wrap_batch_func func = funcs[i];

		// Locate the handler function in the jump table at jump_index, execute
		// it using the context and function arguments.
		gl_wrap_jump_table[func.jump_index](ctx, func.args);
	}
}
