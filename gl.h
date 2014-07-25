// Copyright 2014 The Azul3D Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
//
// This source file was automatically generated using glwrap.
// +build<no value>

#ifndef H_GLWRAP_OPENGL_ES_2
#define H_GLWRAP_OPENGL_ES_2


// OpenGL type definitions
#include <stddef.h>
#include <KHR/khrplatform.h>
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLclampx;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void *GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;
#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
typedef unsigned short GLhalfARB;
typedef unsigned short GLhalf;
typedef GLint GLfixed;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef ptrdiff_t GLintptrARB;
typedef ptrdiff_t GLsizeiptrARB;
typedef int64_t GLint64EXT;
typedef uint64_t GLuint64EXT;
typedef struct __GLsync *GLsync;
struct _cl_context;
struct _cl_event;
typedef void ( *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void ( *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void ( *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef khronos_int8_t GLbyte;
typedef khronos_uint8_t GLubyte;
typedef khronos_float_t GLfloat;
typedef khronos_float_t GLclampf;
typedef khronos_int32_t GLfixed;
typedef khronos_int64_t GLint64;
typedef khronos_uint64_t GLuint64;
typedef khronos_int64_t GLint64EXT;
typedef khronos_uint64_t GLuint64EXT;
typedef khronos_intptr_t GLintptr;
typedef khronos_ssize_t GLsizeiptr;
typedef void ( *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef unsigned short GLhalfNV;
typedef GLintptr GLvdpauSurfaceNV;



// Define GLAPIENTRY for platforms that need it.
#ifndef GLAPIENTRY
#define GLAPIENTRY
#endif


// Typedefs for each OpenGL pointer function; GLAPIENTRY is required on Windows
// OS (but for other platforms is simply nothing).
typedef void (GLAPIENTRY* PFNGLACTIVETEXTUREPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLATTACHSHADERPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLBINDATTRIBLOCATIONPROC) (GLuint, GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLBINDFRAMEBUFFERPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLBINDRENDERBUFFERPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLBINDTEXTUREPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLBLENDCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLBLENDEQUATIONPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLBLENDFUNCPROC) (GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLBLENDFUNCSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLBUFFERDATAPROC) (GLenum, GLsizeiptr, void*, GLenum);
typedef void (GLAPIENTRY* PFNGLBUFFERSUBDATAPROC) (GLenum, GLintptr, GLsizeiptr, void*);
typedef GLenum (GLAPIENTRY* PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLCLEARPROC) (GLbitfield);
typedef void (GLAPIENTRY* PFNGLCLEARCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLCLEARDEPTHFPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLCLEARSTENCILPROC) (GLint);
typedef void (GLAPIENTRY* PFNGLCOLORMASKPROC) (GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (GLAPIENTRY* PFNGLCOMPILESHADERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLCOPYTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
typedef void (GLAPIENTRY* PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef GLuint (GLAPIENTRY* PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (GLAPIENTRY* PFNGLCREATESHADERPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLCULLFACEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLDELETEBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLDELETEPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDELETERENDERBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLDELETESHADERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDELETETEXTURESPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLDEPTHFUNCPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLDEPTHMASKPROC) (GLboolean);
typedef void (GLAPIENTRY* PFNGLDEPTHRANGEFPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLDETACHSHADERPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLDISABLEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDRAWARRAYSPROC) (GLenum, GLint, GLsizei);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSPROC) (GLenum, GLsizei, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLENABLEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLFINISHPROC) (void);
typedef void (GLAPIENTRY* PFNGLFLUSHPROC) (void);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum, GLenum, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (GLAPIENTRY* PFNGLFRONTFACEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGENBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENERATEMIPMAPPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGENFRAMEBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENRENDERBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENTEXTURESPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEATTRIBPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETATTACHEDSHADERSPROC) (GLuint, GLsizei, GLsizei*, GLuint*);
typedef GLint (GLAPIENTRY* PFNGLGETATTRIBLOCATIONPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETBOOLEANVPROC) (GLenum, GLboolean*);
typedef void (GLAPIENTRY* PFNGLGETBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef GLenum (GLAPIENTRY* PFNGLGETERRORPROC) (void);
typedef void (GLAPIENTRY* PFNGLGETFLOATVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum, GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETINTEGERVPROC) (GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMINFOLOGPROC) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETSHADERIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETSHADERINFOLOGPROC) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum, GLenum, GLint*, GLint*);
typedef void (GLAPIENTRY* PFNGLGETSHADERSOURCEPROC) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef GLubyte* (GLAPIENTRY* PFNGLGETSTRINGPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGETTEXPARAMETERFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETTEXPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMFVPROC) (GLuint, GLint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMIVPROC) (GLuint, GLint, GLint*);
typedef GLint (GLAPIENTRY* PFNGLGETUNIFORMLOCATIONPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBFVPROC) (GLuint, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint, GLenum, void**);
typedef void (GLAPIENTRY* PFNGLHINTPROC) (GLenum, GLenum);
typedef GLboolean (GLAPIENTRY* PFNGLISBUFFERPROC) (GLuint);
typedef GLboolean (GLAPIENTRY* PFNGLISENABLEDPROC) (GLenum);
typedef GLboolean (GLAPIENTRY* PFNGLISFRAMEBUFFERPROC) (GLuint);
typedef GLboolean (GLAPIENTRY* PFNGLISPROGRAMPROC) (GLuint);
typedef GLboolean (GLAPIENTRY* PFNGLISRENDERBUFFERPROC) (GLuint);
typedef GLboolean (GLAPIENTRY* PFNGLISSHADERPROC) (GLuint);
typedef GLboolean (GLAPIENTRY* PFNGLISTEXTUREPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLLINEWIDTHPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLLINKPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLPIXELSTOREIPROC) (GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLPOLYGONOFFSETPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLREADPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLRELEASESHADERCOMPILERPROC) (void);
typedef void (GLAPIENTRY* PFNGLRENDERBUFFERSTORAGEPROC) (GLenum, GLenum, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLSAMPLECOVERAGEPROC) (GLfloat, GLboolean);
typedef void (GLAPIENTRY* PFNGLSCISSORPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLSHADERBINARYPROC) (GLsizei, GLuint*, GLenum, void*, GLsizei);
typedef void (GLAPIENTRY* PFNGLSHADERSOURCEPROC) (GLuint, GLsizei, GLchar**, GLint*);
typedef void (GLAPIENTRY* PFNGLSTENCILFUNCPROC) (GLenum, GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLSTENCILFUNCSEPARATEPROC) (GLenum, GLenum, GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLSTENCILMASKPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLSTENCILMASKSEPARATEPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLSTENCILOPPROC) (GLenum, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLSTENCILOPSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLTEXIMAGE2DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERFPROC) (GLenum, GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLUNIFORM1FPROC) (GLint, GLfloat);
typedef void (GLAPIENTRY* PFNGLUNIFORM1FVPROC) (GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORM1IPROC) (GLint, GLint);
typedef void (GLAPIENTRY* PFNGLUNIFORM1IVPROC) (GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM2FPROC) (GLint, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLUNIFORM2FVPROC) (GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORM2IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLUNIFORM2IVPROC) (GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM3FPROC) (GLint, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLUNIFORM3FVPROC) (GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORM3IPROC) (GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLUNIFORM3IVPROC) (GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM4FPROC) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLUNIFORM4FVPROC) (GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORM4IPROC) (GLint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLUNIFORM4IVPROC) (GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUSEPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLVALIDATEPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB1FPROC) (GLuint, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB1FVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB2FPROC) (GLuint, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB2FVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB3FPROC) (GLuint, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB3FVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4FPROC) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4FVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBPOINTERPROC) (GLuint, GLint, GLenum, GLboolean, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLVIEWPORTPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLREADBUFFERPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLDRAWRANGEELEMENTSPROC) (GLenum, GLuint, GLuint, GLsizei, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLTEXIMAGE3DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLGENQUERIESPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLDELETEQUERIESPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISQUERYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLBEGINQUERYPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLENDQUERYPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGETQUERYIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETQUERYOBJECTUIVPROC) (GLuint, GLenum, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLUNMAPBUFFERPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGETBUFFERPOINTERVPROC) (GLenum, GLenum, void**);
typedef void (GLAPIENTRY* PFNGLDRAWBUFFERSPROC) (GLsizei, GLenum*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2X3FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3X2FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2X4FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4X2FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3X4FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4X3FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLBLITFRAMEBUFFERPROC) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
typedef void (GLAPIENTRY* PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum, GLenum, GLuint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLMAPBUFFERRANGEPROC) (GLenum, GLintptr, GLsizeiptr, GLbitfield);
typedef void (GLAPIENTRY* PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum, GLintptr, GLsizeiptr);
typedef void (GLAPIENTRY* PFNGLBINDVERTEXARRAYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDELETEVERTEXARRAYSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENVERTEXARRAYSPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISVERTEXARRAYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLGETINTEGERI_VPROC) (GLenum, GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLENDTRANSFORMFEEDBACKPROC) (void);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERRANGEPROC) (GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERBASEPROC) (GLenum, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint, GLsizei, GLchar**, GLenum);
typedef void (GLAPIENTRY* PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint, GLint, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBIIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4IPROC) (GLuint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4UIPROC) (GLuint, GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4IVPROC) (GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4UIVPROC) (GLuint, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMUIVPROC) (GLuint, GLint, GLuint*);
typedef GLint (GLAPIENTRY* PFNGLGETFRAGDATALOCATIONPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLUNIFORM1UIPROC) (GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM2UIPROC) (GLint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM3UIPROC) (GLint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM4UIPROC) (GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM1UIVPROC) (GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM2UIVPROC) (GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM3UIVPROC) (GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM4UIVPROC) (GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERIVPROC) (GLenum, GLint, GLint*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERUIVPROC) (GLenum, GLint, GLuint*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERFVPROC) (GLenum, GLint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERFIPROC) (GLenum, GLint, GLfloat, GLint);
typedef GLubyte* (GLAPIENTRY* PFNGLGETSTRINGIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLCOPYBUFFERSUBDATAPROC) (GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMINDICESPROC) (GLuint, GLsizei, GLchar**, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint, GLsizei, GLuint*, GLenum, GLint*);
typedef GLuint (GLAPIENTRY* PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint, GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum, GLsizei, GLenum, void*, GLsizei);
typedef GLsync (GLAPIENTRY* PFNGLFENCESYNCPROC) (GLenum, GLbitfield);
typedef GLboolean (GLAPIENTRY* PFNGLISSYNCPROC) (GLsync);
typedef void (GLAPIENTRY* PFNGLDELETESYNCPROC) (GLsync);
typedef GLenum (GLAPIENTRY* PFNGLCLIENTWAITSYNCPROC) (GLsync, GLbitfield, GLuint64);
typedef void (GLAPIENTRY* PFNGLWAITSYNCPROC) (GLsync, GLbitfield, GLuint64);
typedef void (GLAPIENTRY* PFNGLGETINTEGER64VPROC) (GLenum, GLint64*);
typedef void (GLAPIENTRY* PFNGLGETSYNCIVPROC) (GLsync, GLenum, GLsizei, GLsizei*, GLint*);
typedef void (GLAPIENTRY* PFNGLGETINTEGER64I_VPROC) (GLenum, GLuint, GLint64*);
typedef void (GLAPIENTRY* PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum, GLenum, GLint64*);
typedef void (GLAPIENTRY* PFNGLGENSAMPLERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLDELETESAMPLERSPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISSAMPLERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLBINDSAMPLERPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERFPROC) (GLuint, GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERFVPROC) (GLuint, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBDIVISORPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISTRANSFORMFEEDBACKPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLPAUSETRANSFORMFEEDBACKPROC) (void);
typedef void (GLAPIENTRY* PFNGLRESUMETRANSFORMFEEDBACKPROC) (void);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMBINARYPROC) (GLuint, GLsizei, GLsizei*, GLenum*, void*);
typedef void (GLAPIENTRY* PFNGLPROGRAMBINARYPROC) (GLuint, GLenum, void*, GLsizei);
typedef void (GLAPIENTRY* PFNGLPROGRAMPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum, GLsizei, GLenum*);
typedef void (GLAPIENTRY* PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum, GLsizei, GLenum*, GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLTEXSTORAGE2DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLTEXSTORAGE3DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLGETINTERNALFORMATIVPROC) (GLenum, GLenum, GLenum, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLDISPATCHCOMPUTEPROC) (GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr);
typedef void (GLAPIENTRY* PFNGLDRAWARRAYSINDIRECTPROC) (GLenum, void*);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint, GLenum, GLenum, GLint*);
typedef GLuint (GLAPIENTRY* PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint, GLenum, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint, GLenum, GLuint, GLsizei, GLenum*, GLsizei, GLsizei*, GLint*);
typedef GLint (GLAPIENTRY* PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint, GLenum, GLchar*);
typedef void (GLAPIENTRY* PFNGLUSEPROGRAMSTAGESPROC) (GLuint, GLbitfield, GLuint);
typedef void (GLAPIENTRY* PFNGLACTIVESHADERPROGRAMPROC) (GLuint, GLuint);
typedef GLuint (GLAPIENTRY* PFNGLCREATESHADERPROGRAMVPROC) (GLenum, GLsizei, GLchar**);
typedef void (GLAPIENTRY* PFNGLBINDPROGRAMPIPELINEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENPROGRAMPIPELINESPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISPROGRAMPIPELINEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1IPROC) (GLuint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2IPROC) (GLuint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3IPROC) (GLuint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4IPROC) (GLuint, GLint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1UIPROC) (GLuint, GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2UIPROC) (GLuint, GLint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3UIPROC) (GLuint, GLint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4UIPROC) (GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1FPROC) (GLuint, GLint, GLfloat);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2FPROC) (GLuint, GLint, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3FPROC) (GLuint, GLint, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4FPROC) (GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1IVPROC) (GLuint, GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2IVPROC) (GLuint, GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3IVPROC) (GLuint, GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4IVPROC) (GLuint, GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint, GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint, GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint, GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint, GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1FVPROC) (GLuint, GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2FVPROC) (GLuint, GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3FVPROC) (GLuint, GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4FVPROC) (GLuint, GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLBINDIMAGETEXTUREPROC) (GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLGETBOOLEANI_VPROC) (GLenum, GLuint, GLboolean*);
typedef void (GLAPIENTRY* PFNGLMEMORYBARRIERPROC) (GLbitfield);
typedef void (GLAPIENTRY* PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield);
typedef void (GLAPIENTRY* PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
typedef void (GLAPIENTRY* PFNGLGETMULTISAMPLEFVPROC) (GLenum, GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLSAMPLEMASKIPROC) (GLuint, GLbitfield);
typedef void (GLAPIENTRY* PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum, GLint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum, GLint, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLBINDVERTEXBUFFERPROC) (GLuint, GLuint, GLintptr, GLsizei);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBFORMATPROC) (GLuint, GLint, GLenum, GLboolean, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBIFORMATPROC) (GLuint, GLint, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBBINDINGPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXBINDINGDIVISORPROC) (GLuint, GLuint);


// gl_wrap_context holds the loaded function pointers for a given OpenGL
// context. Pointers are lazily-loaded upon first invocation of each function.
// through their appropriate gl_wrap_context_glFunction() counterparts.
typedef struct {
	PFNGLACTIVETEXTUREPROC glActiveTextureProc;
	PFNGLATTACHSHADERPROC glAttachShaderProc;
	PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocationProc;
	PFNGLBINDBUFFERPROC glBindBufferProc;
	PFNGLBINDFRAMEBUFFERPROC glBindFramebufferProc;
	PFNGLBINDRENDERBUFFERPROC glBindRenderbufferProc;
	PFNGLBINDTEXTUREPROC glBindTextureProc;
	PFNGLBLENDCOLORPROC glBlendColorProc;
	PFNGLBLENDEQUATIONPROC glBlendEquationProc;
	PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparateProc;
	PFNGLBLENDFUNCPROC glBlendFuncProc;
	PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparateProc;
	PFNGLBUFFERDATAPROC glBufferDataProc;
	PFNGLBUFFERSUBDATAPROC glBufferSubDataProc;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatusProc;
	PFNGLCLEARPROC glClearProc;
	PFNGLCLEARCOLORPROC glClearColorProc;
	PFNGLCLEARDEPTHFPROC glClearDepthfProc;
	PFNGLCLEARSTENCILPROC glClearStencilProc;
	PFNGLCOLORMASKPROC glColorMaskProc;
	PFNGLCOMPILESHADERPROC glCompileShaderProc;
	PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2DProc;
	PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2DProc;
	PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2DProc;
	PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2DProc;
	PFNGLCREATEPROGRAMPROC glCreateProgramProc;
	PFNGLCREATESHADERPROC glCreateShaderProc;
	PFNGLCULLFACEPROC glCullFaceProc;
	PFNGLDELETEBUFFERSPROC glDeleteBuffersProc;
	PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffersProc;
	PFNGLDELETEPROGRAMPROC glDeleteProgramProc;
	PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffersProc;
	PFNGLDELETESHADERPROC glDeleteShaderProc;
	PFNGLDELETETEXTURESPROC glDeleteTexturesProc;
	PFNGLDEPTHFUNCPROC glDepthFuncProc;
	PFNGLDEPTHMASKPROC glDepthMaskProc;
	PFNGLDEPTHRANGEFPROC glDepthRangefProc;
	PFNGLDETACHSHADERPROC glDetachShaderProc;
	PFNGLDISABLEPROC glDisableProc;
	PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArrayProc;
	PFNGLDRAWARRAYSPROC glDrawArraysProc;
	PFNGLDRAWELEMENTSPROC glDrawElementsProc;
	PFNGLENABLEPROC glEnableProc;
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArrayProc;
	PFNGLFINISHPROC glFinishProc;
	PFNGLFLUSHPROC glFlushProc;
	PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbufferProc;
	PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2DProc;
	PFNGLFRONTFACEPROC glFrontFaceProc;
	PFNGLGENBUFFERSPROC glGenBuffersProc;
	PFNGLGENERATEMIPMAPPROC glGenerateMipmapProc;
	PFNGLGENFRAMEBUFFERSPROC glGenFramebuffersProc;
	PFNGLGENRENDERBUFFERSPROC glGenRenderbuffersProc;
	PFNGLGENTEXTURESPROC glGenTexturesProc;
	PFNGLGETACTIVEATTRIBPROC glGetActiveAttribProc;
	PFNGLGETACTIVEUNIFORMPROC glGetActiveUniformProc;
	PFNGLGETATTACHEDSHADERSPROC glGetAttachedShadersProc;
	PFNGLGETATTRIBLOCATIONPROC glGetAttribLocationProc;
	PFNGLGETBOOLEANVPROC glGetBooleanvProc;
	PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameterivProc;
	PFNGLGETERRORPROC glGetErrorProc;
	PFNGLGETFLOATVPROC glGetFloatvProc;
	PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivProc;
	PFNGLGETINTEGERVPROC glGetIntegervProc;
	PFNGLGETPROGRAMIVPROC glGetProgramivProc;
	PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLogProc;
	PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameterivProc;
	PFNGLGETSHADERIVPROC glGetShaderivProc;
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLogProc;
	PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormatProc;
	PFNGLGETSHADERSOURCEPROC glGetShaderSourceProc;
	PFNGLGETSTRINGPROC glGetStringProc;
	PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfvProc;
	PFNGLGETTEXPARAMETERIVPROC glGetTexParameterivProc;
	PFNGLGETUNIFORMFVPROC glGetUniformfvProc;
	PFNGLGETUNIFORMIVPROC glGetUniformivProc;
	PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocationProc;
	PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfvProc;
	PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribivProc;
	PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointervProc;
	PFNGLHINTPROC glHintProc;
	PFNGLISBUFFERPROC glIsBufferProc;
	PFNGLISENABLEDPROC glIsEnabledProc;
	PFNGLISFRAMEBUFFERPROC glIsFramebufferProc;
	PFNGLISPROGRAMPROC glIsProgramProc;
	PFNGLISRENDERBUFFERPROC glIsRenderbufferProc;
	PFNGLISSHADERPROC glIsShaderProc;
	PFNGLISTEXTUREPROC glIsTextureProc;
	PFNGLLINEWIDTHPROC glLineWidthProc;
	PFNGLLINKPROGRAMPROC glLinkProgramProc;
	PFNGLPIXELSTOREIPROC glPixelStoreiProc;
	PFNGLPOLYGONOFFSETPROC glPolygonOffsetProc;
	PFNGLREADPIXELSPROC glReadPixelsProc;
	PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompilerProc;
	PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorageProc;
	PFNGLSAMPLECOVERAGEPROC glSampleCoverageProc;
	PFNGLSCISSORPROC glScissorProc;
	PFNGLSHADERBINARYPROC glShaderBinaryProc;
	PFNGLSHADERSOURCEPROC glShaderSourceProc;
	PFNGLSTENCILFUNCPROC glStencilFuncProc;
	PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparateProc;
	PFNGLSTENCILMASKPROC glStencilMaskProc;
	PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparateProc;
	PFNGLSTENCILOPPROC glStencilOpProc;
	PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparateProc;
	PFNGLTEXIMAGE2DPROC glTexImage2DProc;
	PFNGLTEXPARAMETERFPROC glTexParameterfProc;
	PFNGLTEXPARAMETERFVPROC glTexParameterfvProc;
	PFNGLTEXPARAMETERIPROC glTexParameteriProc;
	PFNGLTEXPARAMETERIVPROC glTexParameterivProc;
	PFNGLTEXSUBIMAGE2DPROC glTexSubImage2DProc;
	PFNGLUNIFORM1FPROC glUniform1fProc;
	PFNGLUNIFORM1FVPROC glUniform1fvProc;
	PFNGLUNIFORM1IPROC glUniform1iProc;
	PFNGLUNIFORM1IVPROC glUniform1ivProc;
	PFNGLUNIFORM2FPROC glUniform2fProc;
	PFNGLUNIFORM2FVPROC glUniform2fvProc;
	PFNGLUNIFORM2IPROC glUniform2iProc;
	PFNGLUNIFORM2IVPROC glUniform2ivProc;
	PFNGLUNIFORM3FPROC glUniform3fProc;
	PFNGLUNIFORM3FVPROC glUniform3fvProc;
	PFNGLUNIFORM3IPROC glUniform3iProc;
	PFNGLUNIFORM3IVPROC glUniform3ivProc;
	PFNGLUNIFORM4FPROC glUniform4fProc;
	PFNGLUNIFORM4FVPROC glUniform4fvProc;
	PFNGLUNIFORM4IPROC glUniform4iProc;
	PFNGLUNIFORM4IVPROC glUniform4ivProc;
	PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fvProc;
	PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fvProc;
	PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fvProc;
	PFNGLUSEPROGRAMPROC glUseProgramProc;
	PFNGLVALIDATEPROGRAMPROC glValidateProgramProc;
	PFNGLVERTEXATTRIB1FPROC glVertexAttrib1fProc;
	PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fvProc;
	PFNGLVERTEXATTRIB2FPROC glVertexAttrib2fProc;
	PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fvProc;
	PFNGLVERTEXATTRIB3FPROC glVertexAttrib3fProc;
	PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fvProc;
	PFNGLVERTEXATTRIB4FPROC glVertexAttrib4fProc;
	PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fvProc;
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointerProc;
	PFNGLVIEWPORTPROC glViewportProc;
	PFNGLREADBUFFERPROC glReadBufferProc;
	PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElementsProc;
	PFNGLTEXIMAGE3DPROC glTexImage3DProc;
	PFNGLTEXSUBIMAGE3DPROC glTexSubImage3DProc;
	PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3DProc;
	PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3DProc;
	PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3DProc;
	PFNGLGENQUERIESPROC glGenQueriesProc;
	PFNGLDELETEQUERIESPROC glDeleteQueriesProc;
	PFNGLISQUERYPROC glIsQueryProc;
	PFNGLBEGINQUERYPROC glBeginQueryProc;
	PFNGLENDQUERYPROC glEndQueryProc;
	PFNGLGETQUERYIVPROC glGetQueryivProc;
	PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuivProc;
	PFNGLUNMAPBUFFERPROC glUnmapBufferProc;
	PFNGLGETBUFFERPOINTERVPROC glGetBufferPointervProc;
	PFNGLDRAWBUFFERSPROC glDrawBuffersProc;
	PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fvProc;
	PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fvProc;
	PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fvProc;
	PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fvProc;
	PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fvProc;
	PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fvProc;
	PFNGLBLITFRAMEBUFFERPROC glBlitFramebufferProc;
	PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisampleProc;
	PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayerProc;
	PFNGLMAPBUFFERRANGEPROC glMapBufferRangeProc;
	PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRangeProc;
	PFNGLBINDVERTEXARRAYPROC glBindVertexArrayProc;
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArraysProc;
	PFNGLGENVERTEXARRAYSPROC glGenVertexArraysProc;
	PFNGLISVERTEXARRAYPROC glIsVertexArrayProc;
	PFNGLGETINTEGERI_VPROC glGetIntegeri_vProc;
	PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedbackProc;
	PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedbackProc;
	PFNGLBINDBUFFERRANGEPROC glBindBufferRangeProc;
	PFNGLBINDBUFFERBASEPROC glBindBufferBaseProc;
	PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryingsProc;
	PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVaryingProc;
	PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointerProc;
	PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIivProc;
	PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuivProc;
	PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4iProc;
	PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4uiProc;
	PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4ivProc;
	PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uivProc;
	PFNGLGETUNIFORMUIVPROC glGetUniformuivProc;
	PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocationProc;
	PFNGLUNIFORM1UIPROC glUniform1uiProc;
	PFNGLUNIFORM2UIPROC glUniform2uiProc;
	PFNGLUNIFORM3UIPROC glUniform3uiProc;
	PFNGLUNIFORM4UIPROC glUniform4uiProc;
	PFNGLUNIFORM1UIVPROC glUniform1uivProc;
	PFNGLUNIFORM2UIVPROC glUniform2uivProc;
	PFNGLUNIFORM3UIVPROC glUniform3uivProc;
	PFNGLUNIFORM4UIVPROC glUniform4uivProc;
	PFNGLCLEARBUFFERIVPROC glClearBufferivProc;
	PFNGLCLEARBUFFERUIVPROC glClearBufferuivProc;
	PFNGLCLEARBUFFERFVPROC glClearBufferfvProc;
	PFNGLCLEARBUFFERFIPROC glClearBufferfiProc;
	PFNGLGETSTRINGIPROC glGetStringiProc;
	PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubDataProc;
	PFNGLGETUNIFORMINDICESPROC glGetUniformIndicesProc;
	PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsivProc;
	PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndexProc;
	PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockivProc;
	PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockNameProc;
	PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBindingProc;
	PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstancedProc;
	PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstancedProc;
	PFNGLFENCESYNCPROC glFenceSyncProc;
	PFNGLISSYNCPROC glIsSyncProc;
	PFNGLDELETESYNCPROC glDeleteSyncProc;
	PFNGLCLIENTWAITSYNCPROC glClientWaitSyncProc;
	PFNGLWAITSYNCPROC glWaitSyncProc;
	PFNGLGETINTEGER64VPROC glGetInteger64vProc;
	PFNGLGETSYNCIVPROC glGetSyncivProc;
	PFNGLGETINTEGER64I_VPROC glGetInteger64i_vProc;
	PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64vProc;
	PFNGLGENSAMPLERSPROC glGenSamplersProc;
	PFNGLDELETESAMPLERSPROC glDeleteSamplersProc;
	PFNGLISSAMPLERPROC glIsSamplerProc;
	PFNGLBINDSAMPLERPROC glBindSamplerProc;
	PFNGLSAMPLERPARAMETERIPROC glSamplerParameteriProc;
	PFNGLSAMPLERPARAMETERIVPROC glSamplerParameterivProc;
	PFNGLSAMPLERPARAMETERFPROC glSamplerParameterfProc;
	PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfvProc;
	PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameterivProc;
	PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfvProc;
	PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisorProc;
	PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedbackProc;
	PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacksProc;
	PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacksProc;
	PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedbackProc;
	PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedbackProc;
	PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedbackProc;
	PFNGLGETPROGRAMBINARYPROC glGetProgramBinaryProc;
	PFNGLPROGRAMBINARYPROC glProgramBinaryProc;
	PFNGLPROGRAMPARAMETERIPROC glProgramParameteriProc;
	PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebufferProc;
	PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebufferProc;
	PFNGLTEXSTORAGE2DPROC glTexStorage2DProc;
	PFNGLTEXSTORAGE3DPROC glTexStorage3DProc;
	PFNGLGETINTERNALFORMATIVPROC glGetInternalformativProc;
	PFNGLDISPATCHCOMPUTEPROC glDispatchComputeProc;
	PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirectProc;
	PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirectProc;
	PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirectProc;
	PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteriProc;
	PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameterivProc;
	PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceivProc;
	PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndexProc;
	PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceNameProc;
	PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceivProc;
	PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocationProc;
	PFNGLUSEPROGRAMSTAGESPROC glUseProgramStagesProc;
	PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgramProc;
	PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramvProc;
	PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipelineProc;
	PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelinesProc;
	PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelinesProc;
	PFNGLISPROGRAMPIPELINEPROC glIsProgramPipelineProc;
	PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineivProc;
	PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1iProc;
	PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2iProc;
	PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3iProc;
	PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4iProc;
	PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1uiProc;
	PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2uiProc;
	PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3uiProc;
	PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4uiProc;
	PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1fProc;
	PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2fProc;
	PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3fProc;
	PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4fProc;
	PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1ivProc;
	PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2ivProc;
	PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3ivProc;
	PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4ivProc;
	PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uivProc;
	PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uivProc;
	PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uivProc;
	PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uivProc;
	PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fvProc;
	PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fvProc;
	PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fvProc;
	PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fvProc;
	PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fvProc;
	PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fvProc;
	PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fvProc;
	PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fvProc;
	PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fvProc;
	PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fvProc;
	PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fvProc;
	PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fvProc;
	PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fvProc;
	PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipelineProc;
	PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLogProc;
	PFNGLBINDIMAGETEXTUREPROC glBindImageTextureProc;
	PFNGLGETBOOLEANI_VPROC glGetBooleani_vProc;
	PFNGLMEMORYBARRIERPROC glMemoryBarrierProc;
	PFNGLMEMORYBARRIERBYREGIONPROC glMemoryBarrierByRegionProc;
	PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisampleProc;
	PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefvProc;
	PFNGLSAMPLEMASKIPROC glSampleMaskiProc;
	PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameterivProc;
	PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfvProc;
	PFNGLBINDVERTEXBUFFERPROC glBindVertexBufferProc;
	PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormatProc;
	PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormatProc;
	PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBindingProc;
	PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisorProc;

} gl_wrap_context;

// Function prototype definitions for each appropriate OpenGL function.
inline void gl_wrap_context_glActiveTexture(gl_wrap_context* ctx, GLenum texture);
inline void gl_wrap_context_glAttachShader(gl_wrap_context* ctx, GLuint program, GLuint shader);
inline void gl_wrap_context_glBindAttribLocation(gl_wrap_context* ctx, GLuint program, GLuint index, GLchar* name);
inline void gl_wrap_context_glBindBuffer(gl_wrap_context* ctx, GLenum target, GLuint buffer);
inline void gl_wrap_context_glBindFramebuffer(gl_wrap_context* ctx, GLenum target, GLuint framebuffer);
inline void gl_wrap_context_glBindRenderbuffer(gl_wrap_context* ctx, GLenum target, GLuint renderbuffer);
inline void gl_wrap_context_glBindTexture(gl_wrap_context* ctx, GLenum target, GLuint texture);
inline void gl_wrap_context_glBlendColor(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
inline void gl_wrap_context_glBlendEquation(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glBlendEquationSeparate(gl_wrap_context* ctx, GLenum modeRGB, GLenum modeAlpha);
inline void gl_wrap_context_glBlendFunc(gl_wrap_context* ctx, GLenum sfactor, GLenum dfactor);
inline void gl_wrap_context_glBlendFuncSeparate(gl_wrap_context* ctx, GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
inline void gl_wrap_context_glBufferData(gl_wrap_context* ctx, GLenum target, GLsizeiptr size, void* data, GLenum usage);
inline void gl_wrap_context_glBufferSubData(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr size, void* data);
inline GLenum gl_wrap_context_glCheckFramebufferStatus(gl_wrap_context* ctx, GLenum target);
inline void gl_wrap_context_glClear(gl_wrap_context* ctx, GLbitfield mask);
inline void gl_wrap_context_glClearColor(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
inline void gl_wrap_context_glClearDepthf(gl_wrap_context* ctx, GLfloat d);
inline void gl_wrap_context_glClearStencil(gl_wrap_context* ctx, GLint s);
inline void gl_wrap_context_glColorMask(gl_wrap_context* ctx, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
inline void gl_wrap_context_glCompileShader(gl_wrap_context* ctx, GLuint shader);
inline void gl_wrap_context_glCompressedTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, void* data);
inline void gl_wrap_context_glCompressedTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, void* data);
inline void gl_wrap_context_glCopyTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
inline void gl_wrap_context_glCopyTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
inline GLuint gl_wrap_context_glCreateProgram(gl_wrap_context* ctxvoid);
inline GLuint gl_wrap_context_glCreateShader(gl_wrap_context* ctx, GLenum type);
inline void gl_wrap_context_glCullFace(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glDeleteBuffers(gl_wrap_context* ctx, GLsizei n, GLuint* buffers);
inline void gl_wrap_context_glDeleteFramebuffers(gl_wrap_context* ctx, GLsizei n, GLuint* framebuffers);
inline void gl_wrap_context_glDeleteProgram(gl_wrap_context* ctx, GLuint program);
inline void gl_wrap_context_glDeleteRenderbuffers(gl_wrap_context* ctx, GLsizei n, GLuint* renderbuffers);
inline void gl_wrap_context_glDeleteShader(gl_wrap_context* ctx, GLuint shader);
inline void gl_wrap_context_glDeleteTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures);
inline void gl_wrap_context_glDepthFunc(gl_wrap_context* ctx, GLenum func);
inline void gl_wrap_context_glDepthMask(gl_wrap_context* ctx, GLboolean flag);
inline void gl_wrap_context_glDepthRangef(gl_wrap_context* ctx, GLfloat n, GLfloat f);
inline void gl_wrap_context_glDetachShader(gl_wrap_context* ctx, GLuint program, GLuint shader);
inline void gl_wrap_context_glDisable(gl_wrap_context* ctx, GLenum cap);
inline void gl_wrap_context_glDisableVertexAttribArray(gl_wrap_context* ctx, GLuint index);
inline void gl_wrap_context_glDrawArrays(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count);
inline void gl_wrap_context_glDrawElements(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices);
inline void gl_wrap_context_glEnable(gl_wrap_context* ctx, GLenum cap);
inline void gl_wrap_context_glEnableVertexAttribArray(gl_wrap_context* ctx, GLuint index);
inline void gl_wrap_context_glFinish(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glFlush(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glFramebufferRenderbuffer(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
inline void gl_wrap_context_glFramebufferTexture2D(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
inline void gl_wrap_context_glFrontFace(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glGenBuffers(gl_wrap_context* ctx, GLsizei n, GLuint* buffers);
inline void gl_wrap_context_glGenerateMipmap(gl_wrap_context* ctx, GLenum target);
inline void gl_wrap_context_glGenFramebuffers(gl_wrap_context* ctx, GLsizei n, GLuint* framebuffers);
inline void gl_wrap_context_glGenRenderbuffers(gl_wrap_context* ctx, GLsizei n, GLuint* renderbuffers);
inline void gl_wrap_context_glGenTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures);
inline void gl_wrap_context_glGetActiveAttrib(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
inline void gl_wrap_context_glGetActiveUniform(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
inline void gl_wrap_context_glGetAttachedShaders(gl_wrap_context* ctx, GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
inline GLint gl_wrap_context_glGetAttribLocation(gl_wrap_context* ctx, GLuint program, GLchar* name);
inline void gl_wrap_context_glGetBooleanv(gl_wrap_context* ctx, GLenum pname, GLboolean* data);
inline void gl_wrap_context_glGetBufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline GLenum gl_wrap_context_glGetError(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glGetFloatv(gl_wrap_context* ctx, GLenum pname, GLfloat* data);
inline void gl_wrap_context_glGetFramebufferAttachmentParameteriv(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetIntegerv(gl_wrap_context* ctx, GLenum pname, GLint* data);
inline void gl_wrap_context_glGetProgramiv(gl_wrap_context* ctx, GLuint program, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetProgramInfoLog(gl_wrap_context* ctx, GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
inline void gl_wrap_context_glGetRenderbufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetShaderiv(gl_wrap_context* ctx, GLuint shader, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetShaderInfoLog(gl_wrap_context* ctx, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
inline void gl_wrap_context_glGetShaderPrecisionFormat(gl_wrap_context* ctx, GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
inline void gl_wrap_context_glGetShaderSource(gl_wrap_context* ctx, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);
inline GLubyte* gl_wrap_context_glGetString(gl_wrap_context* ctx, GLenum name);
inline void gl_wrap_context_glGetTexParameterfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetTexParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetUniformfv(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat* params);
inline void gl_wrap_context_glGetUniformiv(gl_wrap_context* ctx, GLuint program, GLint location, GLint* params);
inline GLint gl_wrap_context_glGetUniformLocation(gl_wrap_context* ctx, GLuint program, GLchar* name);
inline void gl_wrap_context_glGetVertexAttribfv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetVertexAttribiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetVertexAttribPointerv(gl_wrap_context* ctx, GLuint index, GLenum pname, void** pointer);
inline void gl_wrap_context_glHint(gl_wrap_context* ctx, GLenum target, GLenum mode);
inline GLboolean gl_wrap_context_glIsBuffer(gl_wrap_context* ctx, GLuint buffer);
inline GLboolean gl_wrap_context_glIsEnabled(gl_wrap_context* ctx, GLenum cap);
inline GLboolean gl_wrap_context_glIsFramebuffer(gl_wrap_context* ctx, GLuint framebuffer);
inline GLboolean gl_wrap_context_glIsProgram(gl_wrap_context* ctx, GLuint program);
inline GLboolean gl_wrap_context_glIsRenderbuffer(gl_wrap_context* ctx, GLuint renderbuffer);
inline GLboolean gl_wrap_context_glIsShader(gl_wrap_context* ctx, GLuint shader);
inline GLboolean gl_wrap_context_glIsTexture(gl_wrap_context* ctx, GLuint texture);
inline void gl_wrap_context_glLineWidth(gl_wrap_context* ctx, GLfloat width);
inline void gl_wrap_context_glLinkProgram(gl_wrap_context* ctx, GLuint program);
inline void gl_wrap_context_glPixelStorei(gl_wrap_context* ctx, GLenum pname, GLint param);
inline void gl_wrap_context_glPolygonOffset(gl_wrap_context* ctx, GLfloat factor, GLfloat units);
inline void gl_wrap_context_glReadPixels(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glReleaseShaderCompiler(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glRenderbufferStorage(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
inline void gl_wrap_context_glSampleCoverage(gl_wrap_context* ctx, GLfloat value, GLboolean invert);
inline void gl_wrap_context_glScissor(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glShaderBinary(gl_wrap_context* ctx, GLsizei count, GLuint* shaders, GLenum binaryformat, void* binary, GLsizei length);
inline void gl_wrap_context_glShaderSource(gl_wrap_context* ctx, GLuint shader, GLsizei count, GLchar** string, GLint* length);
inline void gl_wrap_context_glStencilFunc(gl_wrap_context* ctx, GLenum func, GLint ref, GLuint mask);
inline void gl_wrap_context_glStencilFuncSeparate(gl_wrap_context* ctx, GLenum face, GLenum func, GLint ref, GLuint mask);
inline void gl_wrap_context_glStencilMask(gl_wrap_context* ctx, GLuint mask);
inline void gl_wrap_context_glStencilMaskSeparate(gl_wrap_context* ctx, GLenum face, GLuint mask);
inline void gl_wrap_context_glStencilOp(gl_wrap_context* ctx, GLenum fail, GLenum zfail, GLenum zpass);
inline void gl_wrap_context_glStencilOpSeparate(gl_wrap_context* ctx, GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
inline void gl_wrap_context_glTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glTexParameterf(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat param);
inline void gl_wrap_context_glTexParameterfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glTexParameteri(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param);
inline void gl_wrap_context_glTexParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glUniform1f(gl_wrap_context* ctx, GLint location, GLfloat v0);
inline void gl_wrap_context_glUniform1fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glUniform1i(gl_wrap_context* ctx, GLint location, GLint v0);
inline void gl_wrap_context_glUniform1iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glUniform2f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1);
inline void gl_wrap_context_glUniform2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glUniform2i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1);
inline void gl_wrap_context_glUniform2iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glUniform3f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
inline void gl_wrap_context_glUniform3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glUniform3i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1, GLint v2);
inline void gl_wrap_context_glUniform3iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glUniform4f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
inline void gl_wrap_context_glUniform4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glUniform4i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
inline void gl_wrap_context_glUniform4iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glUniformMatrix2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUseProgram(gl_wrap_context* ctx, GLuint program);
inline void gl_wrap_context_glValidateProgram(gl_wrap_context* ctx, GLuint program);
inline void gl_wrap_context_glVertexAttrib1f(gl_wrap_context* ctx, GLuint index, GLfloat x);
inline void gl_wrap_context_glVertexAttrib1fv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glVertexAttrib2f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y);
inline void gl_wrap_context_glVertexAttrib2fv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glVertexAttrib3f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z);
inline void gl_wrap_context_glVertexAttrib3fv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glVertexAttrib4f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
inline void gl_wrap_context_glVertexAttrib4fv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glVertexAttribPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void* pointer);
inline void gl_wrap_context_glViewport(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glReadBuffer(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glDrawRangeElements(gl_wrap_context* ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices);
inline void gl_wrap_context_glTexImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glCopyTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glCompressedTexImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, void* data);
inline void gl_wrap_context_glCompressedTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, void* data);
inline void gl_wrap_context_glGenQueries(gl_wrap_context* ctx, GLsizei n, GLuint* ids);
inline void gl_wrap_context_glDeleteQueries(gl_wrap_context* ctx, GLsizei n, GLuint* ids);
inline GLboolean gl_wrap_context_glIsQuery(gl_wrap_context* ctx, GLuint id);
inline void gl_wrap_context_glBeginQuery(gl_wrap_context* ctx, GLenum target, GLuint id);
inline void gl_wrap_context_glEndQuery(gl_wrap_context* ctx, GLenum target);
inline void gl_wrap_context_glGetQueryiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetQueryObjectuiv(gl_wrap_context* ctx, GLuint id, GLenum pname, GLuint* params);
inline GLboolean gl_wrap_context_glUnmapBuffer(gl_wrap_context* ctx, GLenum target);
inline void gl_wrap_context_glGetBufferPointerv(gl_wrap_context* ctx, GLenum target, GLenum pname, void** params);
inline void gl_wrap_context_glDrawBuffers(gl_wrap_context* ctx, GLsizei n, GLenum* bufs);
inline void gl_wrap_context_glUniformMatrix2x3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix3x2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix2x4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix4x2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix3x4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix4x3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glBlitFramebuffer(gl_wrap_context* ctx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
inline void gl_wrap_context_glRenderbufferStorageMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
inline void gl_wrap_context_glFramebufferTextureLayer(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
inline void gl_wrap_context_glMapBufferRange(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
inline void gl_wrap_context_glFlushMappedBufferRange(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr length);
inline void gl_wrap_context_glBindVertexArray(gl_wrap_context* ctx, GLuint array);
inline void gl_wrap_context_glDeleteVertexArrays(gl_wrap_context* ctx, GLsizei n, GLuint* arrays);
inline void gl_wrap_context_glGenVertexArrays(gl_wrap_context* ctx, GLsizei n, GLuint* arrays);
inline GLboolean gl_wrap_context_glIsVertexArray(gl_wrap_context* ctx, GLuint array);
inline void gl_wrap_context_glGetIntegeri_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLint* data);
inline void gl_wrap_context_glBeginTransformFeedback(gl_wrap_context* ctx, GLenum primitiveMode);
inline void gl_wrap_context_glEndTransformFeedback(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glBindBufferRange(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
inline void gl_wrap_context_glBindBufferBase(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint buffer);
inline void gl_wrap_context_glTransformFeedbackVaryings(gl_wrap_context* ctx, GLuint program, GLsizei count, GLchar** varyings, GLenum bufferMode);
inline void gl_wrap_context_glGetTransformFeedbackVarying(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
inline void gl_wrap_context_glVertexAttribIPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glGetVertexAttribIiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetVertexAttribIuiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLuint* params);
inline void gl_wrap_context_glVertexAttribI4i(gl_wrap_context* ctx, GLuint index, GLint x, GLint y, GLint z, GLint w);
inline void gl_wrap_context_glVertexAttribI4ui(gl_wrap_context* ctx, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
inline void gl_wrap_context_glVertexAttribI4iv(gl_wrap_context* ctx, GLuint index, GLint* v);
inline void gl_wrap_context_glVertexAttribI4uiv(gl_wrap_context* ctx, GLuint index, GLuint* v);
inline void gl_wrap_context_glGetUniformuiv(gl_wrap_context* ctx, GLuint program, GLint location, GLuint* params);
inline GLint gl_wrap_context_glGetFragDataLocation(gl_wrap_context* ctx, GLuint program, GLchar* name);
inline void gl_wrap_context_glUniform1ui(gl_wrap_context* ctx, GLint location, GLuint v0);
inline void gl_wrap_context_glUniform2ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1);
inline void gl_wrap_context_glUniform3ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1, GLuint v2);
inline void gl_wrap_context_glUniform4ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
inline void gl_wrap_context_glUniform1uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glUniform2uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glUniform3uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glUniform4uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glClearBufferiv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLint* value);
inline void gl_wrap_context_glClearBufferuiv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLuint* value);
inline void gl_wrap_context_glClearBufferfv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLfloat* value);
inline void gl_wrap_context_glClearBufferfi(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
inline GLubyte* gl_wrap_context_glGetStringi(gl_wrap_context* ctx, GLenum name, GLuint index);
inline void gl_wrap_context_glCopyBufferSubData(gl_wrap_context* ctx, GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
inline void gl_wrap_context_glGetUniformIndices(gl_wrap_context* ctx, GLuint program, GLsizei uniformCount, GLchar** uniformNames, GLuint* uniformIndices);
inline void gl_wrap_context_glGetActiveUniformsiv(gl_wrap_context* ctx, GLuint program, GLsizei uniformCount, GLuint* uniformIndices, GLenum pname, GLint* params);
inline GLuint gl_wrap_context_glGetUniformBlockIndex(gl_wrap_context* ctx, GLuint program, GLchar* uniformBlockName);
inline void gl_wrap_context_glGetActiveUniformBlockiv(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetActiveUniformBlockName(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName);
inline void gl_wrap_context_glUniformBlockBinding(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
inline void gl_wrap_context_glDrawArraysInstanced(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
inline void gl_wrap_context_glDrawElementsInstanced(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount);
inline GLsync gl_wrap_context_glFenceSync(gl_wrap_context* ctx, GLenum condition, GLbitfield flags);
inline GLboolean gl_wrap_context_glIsSync(gl_wrap_context* ctx, GLsync sync);
inline void gl_wrap_context_glDeleteSync(gl_wrap_context* ctx, GLsync sync);
inline GLenum gl_wrap_context_glClientWaitSync(gl_wrap_context* ctx, GLsync sync, GLbitfield flags, GLuint64 timeout);
inline void gl_wrap_context_glWaitSync(gl_wrap_context* ctx, GLsync sync, GLbitfield flags, GLuint64 timeout);
inline void gl_wrap_context_glGetInteger64v(gl_wrap_context* ctx, GLenum pname, GLint64* data);
inline void gl_wrap_context_glGetSynciv(gl_wrap_context* ctx, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values);
inline void gl_wrap_context_glGetInteger64i_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLint64* data);
inline void gl_wrap_context_glGetBufferParameteri64v(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint64* params);
inline void gl_wrap_context_glGenSamplers(gl_wrap_context* ctx, GLsizei count, GLuint* samplers);
inline void gl_wrap_context_glDeleteSamplers(gl_wrap_context* ctx, GLsizei count, GLuint* samplers);
inline GLboolean gl_wrap_context_glIsSampler(gl_wrap_context* ctx, GLuint sampler);
inline void gl_wrap_context_glBindSampler(gl_wrap_context* ctx, GLuint unit, GLuint sampler);
inline void gl_wrap_context_glSamplerParameteri(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint param);
inline void gl_wrap_context_glSamplerParameteriv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* param);
inline void gl_wrap_context_glSamplerParameterf(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat param);
inline void gl_wrap_context_glSamplerParameterfv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat* param);
inline void gl_wrap_context_glGetSamplerParameteriv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetSamplerParameterfv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glVertexAttribDivisor(gl_wrap_context* ctx, GLuint index, GLuint divisor);
inline void gl_wrap_context_glBindTransformFeedback(gl_wrap_context* ctx, GLenum target, GLuint id);
inline void gl_wrap_context_glDeleteTransformFeedbacks(gl_wrap_context* ctx, GLsizei n, GLuint* ids);
inline void gl_wrap_context_glGenTransformFeedbacks(gl_wrap_context* ctx, GLsizei n, GLuint* ids);
inline GLboolean gl_wrap_context_glIsTransformFeedback(gl_wrap_context* ctx, GLuint id);
inline void gl_wrap_context_glPauseTransformFeedback(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glResumeTransformFeedback(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glGetProgramBinary(gl_wrap_context* ctx, GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary);
inline void gl_wrap_context_glProgramBinary(gl_wrap_context* ctx, GLuint program, GLenum binaryFormat, void* binary, GLsizei length);
inline void gl_wrap_context_glProgramParameteri(gl_wrap_context* ctx, GLuint program, GLenum pname, GLint value);
inline void gl_wrap_context_glInvalidateFramebuffer(gl_wrap_context* ctx, GLenum target, GLsizei numAttachments, GLenum* attachments);
inline void gl_wrap_context_glInvalidateSubFramebuffer(gl_wrap_context* ctx, GLenum target, GLsizei numAttachments, GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glTexStorage2D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
inline void gl_wrap_context_glTexStorage3D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
inline void gl_wrap_context_glGetInternalformativ(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params);
inline void gl_wrap_context_glDispatchCompute(gl_wrap_context* ctx, GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
inline void gl_wrap_context_glDispatchComputeIndirect(gl_wrap_context* ctx, GLintptr indirect);
inline void gl_wrap_context_glDrawArraysIndirect(gl_wrap_context* ctx, GLenum mode, void* indirect);
inline void gl_wrap_context_glDrawElementsIndirect(gl_wrap_context* ctx, GLenum mode, GLenum type, void* indirect);
inline void gl_wrap_context_glFramebufferParameteri(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param);
inline void gl_wrap_context_glGetFramebufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetProgramInterfaceiv(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLenum pname, GLint* params);
inline GLuint gl_wrap_context_glGetProgramResourceIndex(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name);
inline void gl_wrap_context_glGetProgramResourceName(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name);
inline void gl_wrap_context_glGetProgramResourceiv(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params);
inline GLint gl_wrap_context_glGetProgramResourceLocation(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name);
inline void gl_wrap_context_glUseProgramStages(gl_wrap_context* ctx, GLuint pipeline, GLbitfield stages, GLuint program);
inline void gl_wrap_context_glActiveShaderProgram(gl_wrap_context* ctx, GLuint pipeline, GLuint program);
inline GLuint gl_wrap_context_glCreateShaderProgramv(gl_wrap_context* ctx, GLenum type, GLsizei count, GLchar** strings);
inline void gl_wrap_context_glBindProgramPipeline(gl_wrap_context* ctx, GLuint pipeline);
inline void gl_wrap_context_glDeleteProgramPipelines(gl_wrap_context* ctx, GLsizei n, GLuint* pipelines);
inline void gl_wrap_context_glGenProgramPipelines(gl_wrap_context* ctx, GLsizei n, GLuint* pipelines);
inline GLboolean gl_wrap_context_glIsProgramPipeline(gl_wrap_context* ctx, GLuint pipeline);
inline void gl_wrap_context_glGetProgramPipelineiv(gl_wrap_context* ctx, GLuint pipeline, GLenum pname, GLint* params);
inline void gl_wrap_context_glProgramUniform1i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0);
inline void gl_wrap_context_glProgramUniform2i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1);
inline void gl_wrap_context_glProgramUniform3i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
inline void gl_wrap_context_glProgramUniform4i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
inline void gl_wrap_context_glProgramUniform1ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0);
inline void gl_wrap_context_glProgramUniform2ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1);
inline void gl_wrap_context_glProgramUniform3ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
inline void gl_wrap_context_glProgramUniform4ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
inline void gl_wrap_context_glProgramUniform1f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0);
inline void gl_wrap_context_glProgramUniform2f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1);
inline void gl_wrap_context_glProgramUniform3f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
inline void gl_wrap_context_glProgramUniform4f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
inline void gl_wrap_context_glProgramUniform1iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glProgramUniform2iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glProgramUniform3iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glProgramUniform4iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glProgramUniform1uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glProgramUniform2uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glProgramUniform3uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glProgramUniform4uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glProgramUniform1fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glProgramUniform2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glProgramUniform3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glProgramUniform4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix2x3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix3x2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix2x4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix4x2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix3x4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix4x3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glValidateProgramPipeline(gl_wrap_context* ctx, GLuint pipeline);
inline void gl_wrap_context_glGetProgramPipelineInfoLog(gl_wrap_context* ctx, GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
inline void gl_wrap_context_glBindImageTexture(gl_wrap_context* ctx, GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
inline void gl_wrap_context_glGetBooleani_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLboolean* data);
inline void gl_wrap_context_glMemoryBarrier(gl_wrap_context* ctx, GLbitfield barriers);
inline void gl_wrap_context_glMemoryBarrierByRegion(gl_wrap_context* ctx, GLbitfield barriers);
inline void gl_wrap_context_glTexStorage2DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
inline void gl_wrap_context_glGetMultisamplefv(gl_wrap_context* ctx, GLenum pname, GLuint index, GLfloat* val);
inline void gl_wrap_context_glSampleMaski(gl_wrap_context* ctx, GLuint maskNumber, GLbitfield mask);
inline void gl_wrap_context_glGetTexLevelParameteriv(gl_wrap_context* ctx, GLenum target, GLint level, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetTexLevelParameterfv(gl_wrap_context* ctx, GLenum target, GLint level, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glBindVertexBuffer(gl_wrap_context* ctx, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
inline void gl_wrap_context_glVertexAttribFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
inline void gl_wrap_context_glVertexAttribIFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
inline void gl_wrap_context_glVertexAttribBinding(gl_wrap_context* ctx, GLuint attribindex, GLuint bindingindex);
inline void gl_wrap_context_glVertexBindingDivisor(gl_wrap_context* ctx, GLuint bindingindex, GLuint divisor);


// Argument struct definitions for batch function handlers.
typedef struct {
	GLenum texture;
} gl_wrap_handler_glActiveTexture_args;

typedef struct {
	GLuint program;
	GLuint shader;
} gl_wrap_handler_glAttachShader_args;

typedef struct {
	GLuint program;
	GLuint index;
	GLchar* name;
} gl_wrap_handler_glBindAttribLocation_args;

typedef struct {
	GLenum target;
	GLuint buffer;
} gl_wrap_handler_glBindBuffer_args;

typedef struct {
	GLenum target;
	GLuint framebuffer;
} gl_wrap_handler_glBindFramebuffer_args;

typedef struct {
	GLenum target;
	GLuint renderbuffer;
} gl_wrap_handler_glBindRenderbuffer_args;

typedef struct {
	GLenum target;
	GLuint texture;
} gl_wrap_handler_glBindTexture_args;

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} gl_wrap_handler_glBlendColor_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glBlendEquation_args;

typedef struct {
	GLenum modeRGB;
	GLenum modeAlpha;
} gl_wrap_handler_glBlendEquationSeparate_args;

typedef struct {
	GLenum sfactor;
	GLenum dfactor;
} gl_wrap_handler_glBlendFunc_args;

typedef struct {
	GLenum sfactorRGB;
	GLenum dfactorRGB;
	GLenum sfactorAlpha;
	GLenum dfactorAlpha;
} gl_wrap_handler_glBlendFuncSeparate_args;

typedef struct {
	GLenum target;
	GLsizeiptr size;
	void* data;
	GLenum usage;
} gl_wrap_handler_glBufferData_args;

typedef struct {
	GLenum target;
	GLintptr offset;
	GLsizeiptr size;
	void* data;
} gl_wrap_handler_glBufferSubData_args;

typedef struct {
	GLbitfield mask;
} gl_wrap_handler_glClear_args;

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} gl_wrap_handler_glClearColor_args;

typedef struct {
	GLfloat d;
} gl_wrap_handler_glClearDepthf_args;

typedef struct {
	GLint s;
} gl_wrap_handler_glClearStencil_args;

typedef struct {
	GLboolean red;
	GLboolean green;
	GLboolean blue;
	GLboolean alpha;
} gl_wrap_handler_glColorMask_args;

typedef struct {
	GLuint shader;
} gl_wrap_handler_glCompileShader_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLint border;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexImage2D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexSubImage2D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
	GLint border;
} gl_wrap_handler_glCopyTexImage2D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glCopyTexSubImage2D_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glCullFace_args;

typedef struct {
	GLsizei n;
	GLuint* buffers;
} gl_wrap_handler_glDeleteBuffers_args;

typedef struct {
	GLsizei n;
	GLuint* framebuffers;
} gl_wrap_handler_glDeleteFramebuffers_args;

typedef struct {
	GLuint program;
} gl_wrap_handler_glDeleteProgram_args;

typedef struct {
	GLsizei n;
	GLuint* renderbuffers;
} gl_wrap_handler_glDeleteRenderbuffers_args;

typedef struct {
	GLuint shader;
} gl_wrap_handler_glDeleteShader_args;

typedef struct {
	GLsizei n;
	GLuint* textures;
} gl_wrap_handler_glDeleteTextures_args;

typedef struct {
	GLenum func;
} gl_wrap_handler_glDepthFunc_args;

typedef struct {
	GLboolean flag;
} gl_wrap_handler_glDepthMask_args;

typedef struct {
	GLfloat n;
	GLfloat f;
} gl_wrap_handler_glDepthRangef_args;

typedef struct {
	GLuint program;
	GLuint shader;
} gl_wrap_handler_glDetachShader_args;

typedef struct {
	GLenum cap;
} gl_wrap_handler_glDisable_args;

typedef struct {
	GLuint index;
} gl_wrap_handler_glDisableVertexAttribArray_args;

typedef struct {
	GLenum mode;
	GLint first;
	GLsizei count;
} gl_wrap_handler_glDrawArrays_args;

typedef struct {
	GLenum mode;
	GLsizei count;
	GLenum type;
	void* indices;
} gl_wrap_handler_glDrawElements_args;

typedef struct {
	GLenum cap;
} gl_wrap_handler_glEnable_args;

typedef struct {
	GLuint index;
} gl_wrap_handler_glEnableVertexAttribArray_args;

typedef struct {
} gl_wrap_handler_glFinish_args;

typedef struct {
} gl_wrap_handler_glFlush_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLenum renderbuffertarget;
	GLuint renderbuffer;
} gl_wrap_handler_glFramebufferRenderbuffer_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLenum textarget;
	GLuint texture;
	GLint level;
} gl_wrap_handler_glFramebufferTexture2D_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glFrontFace_args;

typedef struct {
	GLsizei n;
	GLuint* buffers;
} gl_wrap_handler_glGenBuffers_args;

typedef struct {
	GLenum target;
} gl_wrap_handler_glGenerateMipmap_args;

typedef struct {
	GLsizei n;
	GLuint* framebuffers;
} gl_wrap_handler_glGenFramebuffers_args;

typedef struct {
	GLsizei n;
	GLuint* renderbuffers;
} gl_wrap_handler_glGenRenderbuffers_args;

typedef struct {
	GLsizei n;
	GLuint* textures;
} gl_wrap_handler_glGenTextures_args;

typedef struct {
	GLuint program;
	GLuint index;
	GLsizei bufSize;
	GLsizei* length;
	GLint* size;
	GLenum* type;
	GLchar* name;
} gl_wrap_handler_glGetActiveAttrib_args;

typedef struct {
	GLuint program;
	GLuint index;
	GLsizei bufSize;
	GLsizei* length;
	GLint* size;
	GLenum* type;
	GLchar* name;
} gl_wrap_handler_glGetActiveUniform_args;

typedef struct {
	GLuint program;
	GLsizei maxCount;
	GLsizei* count;
	GLuint* shaders;
} gl_wrap_handler_glGetAttachedShaders_args;

typedef struct {
	GLenum pname;
	GLboolean* data;
} gl_wrap_handler_glGetBooleanv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetBufferParameteriv_args;

typedef struct {
	GLenum pname;
	GLfloat* data;
} gl_wrap_handler_glGetFloatv_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetFramebufferAttachmentParameteriv_args;

typedef struct {
	GLenum pname;
	GLint* data;
} gl_wrap_handler_glGetIntegerv_args;

typedef struct {
	GLuint program;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetProgramiv_args;

typedef struct {
	GLuint program;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* infoLog;
} gl_wrap_handler_glGetProgramInfoLog_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetRenderbufferParameteriv_args;

typedef struct {
	GLuint shader;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetShaderiv_args;

typedef struct {
	GLuint shader;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* infoLog;
} gl_wrap_handler_glGetShaderInfoLog_args;

typedef struct {
	GLenum shadertype;
	GLenum precisiontype;
	GLint* range;
	GLint* precision;
} gl_wrap_handler_glGetShaderPrecisionFormat_args;

typedef struct {
	GLuint shader;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* source;
} gl_wrap_handler_glGetShaderSource_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetTexParameterfv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetTexParameteriv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat* params;
} gl_wrap_handler_glGetUniformfv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint* params;
} gl_wrap_handler_glGetUniformiv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetVertexAttribfv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetVertexAttribiv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	void** pointer;
} gl_wrap_handler_glGetVertexAttribPointerv_args;

typedef struct {
	GLenum target;
	GLenum mode;
} gl_wrap_handler_glHint_args;

typedef struct {
	GLfloat width;
} gl_wrap_handler_glLineWidth_args;

typedef struct {
	GLuint program;
} gl_wrap_handler_glLinkProgram_args;

typedef struct {
	GLenum pname;
	GLint param;
} gl_wrap_handler_glPixelStorei_args;

typedef struct {
	GLfloat factor;
	GLfloat units;
} gl_wrap_handler_glPolygonOffset_args;

typedef struct {
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glReadPixels_args;

typedef struct {
} gl_wrap_handler_glReleaseShaderCompiler_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glRenderbufferStorage_args;

typedef struct {
	GLfloat value;
	GLboolean invert;
} gl_wrap_handler_glSampleCoverage_args;

typedef struct {
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glScissor_args;

typedef struct {
	GLsizei count;
	GLuint* shaders;
	GLenum binaryformat;
	void* binary;
	GLsizei length;
} gl_wrap_handler_glShaderBinary_args;

typedef struct {
	GLuint shader;
	GLsizei count;
	GLchar** string;
	GLint* length;
} gl_wrap_handler_glShaderSource_args;

typedef struct {
	GLenum func;
	GLint ref;
	GLuint mask;
} gl_wrap_handler_glStencilFunc_args;

typedef struct {
	GLenum face;
	GLenum func;
	GLint ref;
	GLuint mask;
} gl_wrap_handler_glStencilFuncSeparate_args;

typedef struct {
	GLuint mask;
} gl_wrap_handler_glStencilMask_args;

typedef struct {
	GLenum face;
	GLuint mask;
} gl_wrap_handler_glStencilMaskSeparate_args;

typedef struct {
	GLenum fail;
	GLenum zfail;
	GLenum zpass;
} gl_wrap_handler_glStencilOp_args;

typedef struct {
	GLenum face;
	GLenum sfail;
	GLenum dpfail;
	GLenum dppass;
} gl_wrap_handler_glStencilOpSeparate_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint internalformat;
	GLsizei width;
	GLsizei height;
	GLint border;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexImage2D_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glTexParameterf_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glTexParameterfv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glTexParameteri_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glTexParameteriv_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexSubImage2D_args;

typedef struct {
	GLint location;
	GLfloat v0;
} gl_wrap_handler_glUniform1f_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glUniform1fv_args;

typedef struct {
	GLint location;
	GLint v0;
} gl_wrap_handler_glUniform1i_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glUniform1iv_args;

typedef struct {
	GLint location;
	GLfloat v0;
	GLfloat v1;
} gl_wrap_handler_glUniform2f_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glUniform2fv_args;

typedef struct {
	GLint location;
	GLint v0;
	GLint v1;
} gl_wrap_handler_glUniform2i_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glUniform2iv_args;

typedef struct {
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
} gl_wrap_handler_glUniform3f_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glUniform3fv_args;

typedef struct {
	GLint location;
	GLint v0;
	GLint v1;
	GLint v2;
} gl_wrap_handler_glUniform3i_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glUniform3iv_args;

typedef struct {
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
	GLfloat v3;
} gl_wrap_handler_glUniform4f_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glUniform4fv_args;

typedef struct {
	GLint location;
	GLint v0;
	GLint v1;
	GLint v2;
	GLint v3;
} gl_wrap_handler_glUniform4i_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glUniform4iv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix2fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix3fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix4fv_args;

typedef struct {
	GLuint program;
} gl_wrap_handler_glUseProgram_args;

typedef struct {
	GLuint program;
} gl_wrap_handler_glValidateProgram_args;

typedef struct {
	GLuint index;
	GLfloat x;
} gl_wrap_handler_glVertexAttrib1f_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glVertexAttrib1fv_args;

typedef struct {
	GLuint index;
	GLfloat x;
	GLfloat y;
} gl_wrap_handler_glVertexAttrib2f_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glVertexAttrib2fv_args;

typedef struct {
	GLuint index;
	GLfloat x;
	GLfloat y;
	GLfloat z;
} gl_wrap_handler_glVertexAttrib3f_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glVertexAttrib3fv_args;

typedef struct {
	GLuint index;
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
} gl_wrap_handler_glVertexAttrib4f_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glVertexAttrib4fv_args;

typedef struct {
	GLuint index;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glVertexAttribPointer_args;

typedef struct {
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glViewport_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glReadBuffer_args;

typedef struct {
	GLenum mode;
	GLuint start;
	GLuint end;
	GLsizei count;
	GLenum type;
	void* indices;
} gl_wrap_handler_glDrawRangeElements_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLint border;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexImage3D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexSubImage3D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glCopyTexSubImage3D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLint border;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexImage3D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLenum format;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexSubImage3D_args;

typedef struct {
	GLsizei n;
	GLuint* ids;
} gl_wrap_handler_glGenQueries_args;

typedef struct {
	GLsizei n;
	GLuint* ids;
} gl_wrap_handler_glDeleteQueries_args;

typedef struct {
	GLenum target;
	GLuint id;
} gl_wrap_handler_glBeginQuery_args;

typedef struct {
	GLenum target;
} gl_wrap_handler_glEndQuery_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetQueryiv_args;

typedef struct {
	GLuint id;
	GLenum pname;
	GLuint* params;
} gl_wrap_handler_glGetQueryObjectuiv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	void** params;
} gl_wrap_handler_glGetBufferPointerv_args;

typedef struct {
	GLsizei n;
	GLenum* bufs;
} gl_wrap_handler_glDrawBuffers_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix2x3fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix3x2fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix2x4fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix4x2fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix3x4fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix4x3fv_args;

typedef struct {
	GLint srcX0;
	GLint srcY0;
	GLint srcX1;
	GLint srcY1;
	GLint dstX0;
	GLint dstY0;
	GLint dstX1;
	GLint dstY1;
	GLbitfield mask;
	GLenum filter;
} gl_wrap_handler_glBlitFramebuffer_args;

typedef struct {
	GLenum target;
	GLsizei samples;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glRenderbufferStorageMultisample_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLuint texture;
	GLint level;
	GLint layer;
} gl_wrap_handler_glFramebufferTextureLayer_args;

typedef struct {
	GLenum target;
	GLintptr offset;
	GLsizeiptr length;
	GLbitfield access;
} gl_wrap_handler_glMapBufferRange_args;

typedef struct {
	GLenum target;
	GLintptr offset;
	GLsizeiptr length;
} gl_wrap_handler_glFlushMappedBufferRange_args;

typedef struct {
	GLuint array;
} gl_wrap_handler_glBindVertexArray_args;

typedef struct {
	GLsizei n;
	GLuint* arrays;
} gl_wrap_handler_glDeleteVertexArrays_args;

typedef struct {
	GLsizei n;
	GLuint* arrays;
} gl_wrap_handler_glGenVertexArrays_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLint* data;
} gl_wrap_handler_glGetIntegeri_v_args;

typedef struct {
	GLenum primitiveMode;
} gl_wrap_handler_glBeginTransformFeedback_args;

typedef struct {
} gl_wrap_handler_glEndTransformFeedback_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLuint buffer;
	GLintptr offset;
	GLsizeiptr size;
} gl_wrap_handler_glBindBufferRange_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLuint buffer;
} gl_wrap_handler_glBindBufferBase_args;

typedef struct {
	GLuint program;
	GLsizei count;
	GLchar** varyings;
	GLenum bufferMode;
} gl_wrap_handler_glTransformFeedbackVaryings_args;

typedef struct {
	GLuint program;
	GLuint index;
	GLsizei bufSize;
	GLsizei* length;
	GLsizei* size;
	GLenum* type;
	GLchar* name;
} gl_wrap_handler_glGetTransformFeedbackVarying_args;

typedef struct {
	GLuint index;
	GLint size;
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glVertexAttribIPointer_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetVertexAttribIiv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLuint* params;
} gl_wrap_handler_glGetVertexAttribIuiv_args;

typedef struct {
	GLuint index;
	GLint x;
	GLint y;
	GLint z;
	GLint w;
} gl_wrap_handler_glVertexAttribI4i_args;

typedef struct {
	GLuint index;
	GLuint x;
	GLuint y;
	GLuint z;
	GLuint w;
} gl_wrap_handler_glVertexAttribI4ui_args;

typedef struct {
	GLuint index;
	GLint* v;
} gl_wrap_handler_glVertexAttribI4iv_args;

typedef struct {
	GLuint index;
	GLuint* v;
} gl_wrap_handler_glVertexAttribI4uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint* params;
} gl_wrap_handler_glGetUniformuiv_args;

typedef struct {
	GLint location;
	GLuint v0;
} gl_wrap_handler_glUniform1ui_args;

typedef struct {
	GLint location;
	GLuint v0;
	GLuint v1;
} gl_wrap_handler_glUniform2ui_args;

typedef struct {
	GLint location;
	GLuint v0;
	GLuint v1;
	GLuint v2;
} gl_wrap_handler_glUniform3ui_args;

typedef struct {
	GLint location;
	GLuint v0;
	GLuint v1;
	GLuint v2;
	GLuint v3;
} gl_wrap_handler_glUniform4ui_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glUniform1uiv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glUniform2uiv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glUniform3uiv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glUniform4uiv_args;

typedef struct {
	GLenum buffer;
	GLint drawbuffer;
	GLint* value;
} gl_wrap_handler_glClearBufferiv_args;

typedef struct {
	GLenum buffer;
	GLint drawbuffer;
	GLuint* value;
} gl_wrap_handler_glClearBufferuiv_args;

typedef struct {
	GLenum buffer;
	GLint drawbuffer;
	GLfloat* value;
} gl_wrap_handler_glClearBufferfv_args;

typedef struct {
	GLenum buffer;
	GLint drawbuffer;
	GLfloat depth;
	GLint stencil;
} gl_wrap_handler_glClearBufferfi_args;

typedef struct {
	GLenum readTarget;
	GLenum writeTarget;
	GLintptr readOffset;
	GLintptr writeOffset;
	GLsizeiptr size;
} gl_wrap_handler_glCopyBufferSubData_args;

typedef struct {
	GLuint program;
	GLsizei uniformCount;
	GLchar** uniformNames;
	GLuint* uniformIndices;
} gl_wrap_handler_glGetUniformIndices_args;

typedef struct {
	GLuint program;
	GLsizei uniformCount;
	GLuint* uniformIndices;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetActiveUniformsiv_args;

typedef struct {
	GLuint program;
	GLuint uniformBlockIndex;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetActiveUniformBlockiv_args;

typedef struct {
	GLuint program;
	GLuint uniformBlockIndex;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* uniformBlockName;
} gl_wrap_handler_glGetActiveUniformBlockName_args;

typedef struct {
	GLuint program;
	GLuint uniformBlockIndex;
	GLuint uniformBlockBinding;
} gl_wrap_handler_glUniformBlockBinding_args;

typedef struct {
	GLenum mode;
	GLint first;
	GLsizei count;
	GLsizei instancecount;
} gl_wrap_handler_glDrawArraysInstanced_args;

typedef struct {
	GLenum mode;
	GLsizei count;
	GLenum type;
	void* indices;
	GLsizei instancecount;
} gl_wrap_handler_glDrawElementsInstanced_args;

typedef struct {
	GLsync sync;
} gl_wrap_handler_glDeleteSync_args;

typedef struct {
	GLsync sync;
	GLbitfield flags;
	GLuint64 timeout;
} gl_wrap_handler_glWaitSync_args;

typedef struct {
	GLenum pname;
	GLint64* data;
} gl_wrap_handler_glGetInteger64v_args;

typedef struct {
	GLsync sync;
	GLenum pname;
	GLsizei bufSize;
	GLsizei* length;
	GLint* values;
} gl_wrap_handler_glGetSynciv_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLint64* data;
} gl_wrap_handler_glGetInteger64i_v_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint64* params;
} gl_wrap_handler_glGetBufferParameteri64v_args;

typedef struct {
	GLsizei count;
	GLuint* samplers;
} gl_wrap_handler_glGenSamplers_args;

typedef struct {
	GLsizei count;
	GLuint* samplers;
} gl_wrap_handler_glDeleteSamplers_args;

typedef struct {
	GLuint unit;
	GLuint sampler;
} gl_wrap_handler_glBindSampler_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glSamplerParameteri_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLint* param;
} gl_wrap_handler_glSamplerParameteriv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glSamplerParameterf_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLfloat* param;
} gl_wrap_handler_glSamplerParameterfv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetSamplerParameteriv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetSamplerParameterfv_args;

typedef struct {
	GLuint index;
	GLuint divisor;
} gl_wrap_handler_glVertexAttribDivisor_args;

typedef struct {
	GLenum target;
	GLuint id;
} gl_wrap_handler_glBindTransformFeedback_args;

typedef struct {
	GLsizei n;
	GLuint* ids;
} gl_wrap_handler_glDeleteTransformFeedbacks_args;

typedef struct {
	GLsizei n;
	GLuint* ids;
} gl_wrap_handler_glGenTransformFeedbacks_args;

typedef struct {
} gl_wrap_handler_glPauseTransformFeedback_args;

typedef struct {
} gl_wrap_handler_glResumeTransformFeedback_args;

typedef struct {
	GLuint program;
	GLsizei bufSize;
	GLsizei* length;
	GLenum* binaryFormat;
	void* binary;
} gl_wrap_handler_glGetProgramBinary_args;

typedef struct {
	GLuint program;
	GLenum binaryFormat;
	void* binary;
	GLsizei length;
} gl_wrap_handler_glProgramBinary_args;

typedef struct {
	GLuint program;
	GLenum pname;
	GLint value;
} gl_wrap_handler_glProgramParameteri_args;

typedef struct {
	GLenum target;
	GLsizei numAttachments;
	GLenum* attachments;
} gl_wrap_handler_glInvalidateFramebuffer_args;

typedef struct {
	GLenum target;
	GLsizei numAttachments;
	GLenum* attachments;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glInvalidateSubFramebuffer_args;

typedef struct {
	GLenum target;
	GLsizei levels;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glTexStorage2D_args;

typedef struct {
	GLenum target;
	GLsizei levels;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
} gl_wrap_handler_glTexStorage3D_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLenum pname;
	GLsizei bufSize;
	GLint* params;
} gl_wrap_handler_glGetInternalformativ_args;

typedef struct {
	GLuint num_groups_x;
	GLuint num_groups_y;
	GLuint num_groups_z;
} gl_wrap_handler_glDispatchCompute_args;

typedef struct {
	GLintptr indirect;
} gl_wrap_handler_glDispatchComputeIndirect_args;

typedef struct {
	GLenum mode;
	void* indirect;
} gl_wrap_handler_glDrawArraysIndirect_args;

typedef struct {
	GLenum mode;
	GLenum type;
	void* indirect;
} gl_wrap_handler_glDrawElementsIndirect_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glFramebufferParameteri_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetFramebufferParameteriv_args;

typedef struct {
	GLuint program;
	GLenum programInterface;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetProgramInterfaceiv_args;

typedef struct {
	GLuint program;
	GLenum programInterface;
	GLuint index;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* name;
} gl_wrap_handler_glGetProgramResourceName_args;

typedef struct {
	GLuint program;
	GLenum programInterface;
	GLuint index;
	GLsizei propCount;
	GLenum* props;
	GLsizei bufSize;
	GLsizei* length;
	GLint* params;
} gl_wrap_handler_glGetProgramResourceiv_args;

typedef struct {
	GLuint pipeline;
	GLbitfield stages;
	GLuint program;
} gl_wrap_handler_glUseProgramStages_args;

typedef struct {
	GLuint pipeline;
	GLuint program;
} gl_wrap_handler_glActiveShaderProgram_args;

typedef struct {
	GLuint pipeline;
} gl_wrap_handler_glBindProgramPipeline_args;

typedef struct {
	GLsizei n;
	GLuint* pipelines;
} gl_wrap_handler_glDeleteProgramPipelines_args;

typedef struct {
	GLsizei n;
	GLuint* pipelines;
} gl_wrap_handler_glGenProgramPipelines_args;

typedef struct {
	GLuint pipeline;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetProgramPipelineiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint v0;
} gl_wrap_handler_glProgramUniform1i_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint v0;
	GLint v1;
} gl_wrap_handler_glProgramUniform2i_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint v0;
	GLint v1;
	GLint v2;
} gl_wrap_handler_glProgramUniform3i_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint v0;
	GLint v1;
	GLint v2;
	GLint v3;
} gl_wrap_handler_glProgramUniform4i_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint v0;
} gl_wrap_handler_glProgramUniform1ui_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint v0;
	GLuint v1;
} gl_wrap_handler_glProgramUniform2ui_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint v0;
	GLuint v1;
	GLuint v2;
} gl_wrap_handler_glProgramUniform3ui_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint v0;
	GLuint v1;
	GLuint v2;
	GLuint v3;
} gl_wrap_handler_glProgramUniform4ui_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat v0;
} gl_wrap_handler_glProgramUniform1f_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat v0;
	GLfloat v1;
} gl_wrap_handler_glProgramUniform2f_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
} gl_wrap_handler_glProgramUniform3f_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
	GLfloat v3;
} gl_wrap_handler_glProgramUniform4f_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glProgramUniform1iv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glProgramUniform2iv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glProgramUniform3iv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glProgramUniform4iv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glProgramUniform1uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glProgramUniform2uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glProgramUniform3uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glProgramUniform4uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glProgramUniform1fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glProgramUniform2fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glProgramUniform3fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glProgramUniform4fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix2fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix3fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix4fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix2x3fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix3x2fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix2x4fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix4x2fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix3x4fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix4x3fv_args;

typedef struct {
	GLuint pipeline;
} gl_wrap_handler_glValidateProgramPipeline_args;

typedef struct {
	GLuint pipeline;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* infoLog;
} gl_wrap_handler_glGetProgramPipelineInfoLog_args;

typedef struct {
	GLuint unit;
	GLuint texture;
	GLint level;
	GLboolean layered;
	GLint layer;
	GLenum access;
	GLenum format;
} gl_wrap_handler_glBindImageTexture_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLboolean* data;
} gl_wrap_handler_glGetBooleani_v_args;

typedef struct {
	GLbitfield barriers;
} gl_wrap_handler_glMemoryBarrier_args;

typedef struct {
	GLbitfield barriers;
} gl_wrap_handler_glMemoryBarrierByRegion_args;

typedef struct {
	GLenum target;
	GLsizei samples;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLboolean fixedsamplelocations;
} gl_wrap_handler_glTexStorage2DMultisample_args;

typedef struct {
	GLenum pname;
	GLuint index;
	GLfloat* val;
} gl_wrap_handler_glGetMultisamplefv_args;

typedef struct {
	GLuint maskNumber;
	GLbitfield mask;
} gl_wrap_handler_glSampleMaski_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetTexLevelParameteriv_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetTexLevelParameterfv_args;

typedef struct {
	GLuint bindingindex;
	GLuint buffer;
	GLintptr offset;
	GLsizei stride;
} gl_wrap_handler_glBindVertexBuffer_args;

typedef struct {
	GLuint attribindex;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLuint relativeoffset;
} gl_wrap_handler_glVertexAttribFormat_args;

typedef struct {
	GLuint attribindex;
	GLint size;
	GLenum type;
	GLuint relativeoffset;
} gl_wrap_handler_glVertexAttribIFormat_args;

typedef struct {
	GLuint attribindex;
	GLuint bindingindex;
} gl_wrap_handler_glVertexAttribBinding_args;

typedef struct {
	GLuint bindingindex;
	GLuint divisor;
} gl_wrap_handler_glVertexBindingDivisor_args;



// Other custom definitions
typedef void (*gl_wrap_jump_handler)(gl_wrap_context* ctx, void* args);

typedef struct {
	int jump_index;
	void* args;
} gl_wrap_batch_func;

void gl_wrap_batch_exec(gl_wrap_context* ctx, gl_wrap_batch_func* funcs, int numFuncs);

#endif
