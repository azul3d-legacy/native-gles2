// Copyright 2014 The Azul3D Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
//
// This source file was automatically generated using glwrap.
// +build arm android
// +build !opengl_debug

// Package gles2 implements Go bindings to OpenGL ES.
//
// Debugging OpenGL applications is made easy by using the build tag for this
// package "opengl_debug", that is:
//
// go install -tags "opengl_debug" my/package/path
//
// Debugging using this build tag has both advantages and disadvantages:
//
// Advantage: glGetError() is ran directly after each OpenGL function call for
// you, and in the event of an error a panic will occur in addition to a full
// OpenGL stack trace being dumped to stdout before the panic occurs.
//
// Advantage: Batching cannot be turned on, this can help identify batching
// related bugs (due to incorrect memory management).
//
// Disadvantage: Applications compiled with the opengl_debug build tag are slow
// and will not run at full speed due to both disabled batching and the
// additional glGetError call for each OpenGL call.
//
package gles2

/*
#cgo linux LDFLAGS: -lGL
#include "gl.h"
*/
import "C"

import (
	"strconv"
	"strings"
	"unsafe"
)

// Context represents a single OpenGL context's API access.
//
// Since CGO (Go to C) calls are expensive in large quantities as they require
// a context switch due to Go's and C's incompatibile ABI, and since even
// modern OpenGL applications can make several hundred thousands of calls per
// frame, it can become a large bottleneck.
//
// To help remedy this specific bottleneck, batching can be used. When OpenGL
// calls are made and batching is turned on, instead of calls being executed
// immedietly they are stored in a queue and executed later upon a single call
// to the Execute() method.
//
// When batching is turned off and OpenGL calls are made, they are executed
// immedietly, the Execute() method is no-op, and large amounts of OpenGL calls
// will suffer from the performance degration described above.
//
// Additionally, batching may be turned on or off at runtime (even in-between
// OpenGL calls) using the SetBatching() method at runtime.
//
// Note that since batched OpenGL calls are only truly made upon invocation of
// the Execute() method, the memory for pointer arguments to OpenGL function
// calls must remain valid at least untill Execute() is called or else memory
// corruption is possible.
//
// Also note that OpenGL functions which return anything, such as the GetString
// function, cannot be queued for batching because they require that the value
// be immedietly returned. Also, if the function in question relies on previous
// OpenGL commands being executed first, you are responsible for calling the
// Execute() method.
//
// Since batching requires some extra effort on the programmer's side, and
// since debugging applications with batching turned on is more difficult, it
// is by default turned off.
type Context struct {
	c                                       *C.gl_wrap_context
	batch                                   []C.gl_wrap_batch_func
	batching                                bool
	loadedShaderVersion, loadedVersion      bool
	major, minor, release                   int
	shaderMajor, shaderMinor, shaderRelease int
	vendorVersion, vendorShaderVersion      string
	extensions                              map[string]bool
}

// New returns a new initialized Context with batching turned on.
func New() *Context {
	c := new(Context)
	c.c = new(C.gl_wrap_context)
	c.batching = false
	return c
}

// SetBatching turns on or off batching of this Context.
//
// If turning off batching using SetBatching(false), then an implicit call to
// Execute() which executes all the currently pending OpenGL function calls on
// this Context occurs.
//
// Default value is off (false).
func (c *Context) SetBatching(batching bool) {
	if !batching && len(c.batch) > 0 {
		c.Execute()
	}
	c.batching = batching
}

// Batching tells whether or not batching is on or off for this Context.
func (c *Context) Batching() bool {
	return c.batching
}

func (c *Context) push(f C.gl_wrap_batch_func) {
	c.batch = append(c.batch, f)
}

// Execute executes all the currently pending OpenGL function calls for this
// Context.
//
// This function executes pending calls regardless of whether or not batching
// is turned on.
func (c *Context) Execute() {
	if len(c.batch) > 0 {
		C.gl_wrap_batch_exec(
			c.c,
			(*C.gl_wrap_batch_func)(unsafe.Pointer(&c.batch[0])),
			C.int(len(c.batch)),
		)

		// Re-slice the batch
		c.batch = c.batch[:0]
	}
}

func (c *Context) parseVersionString(ver string) (major, minor, release int, vendor string) {
	if len(ver) == 0 {
		// Version string must not be empty
		return
	}

	// According to http://www.opengl.org/sdk/docs/man/xhtml/glGetString.xml
	//
	// the string returned may be 'major.minor' or 'major.minor.release'
	// and may be following by a space and any vendor specific information.

	// First locate a proper version string without vendor specific
	// information.
	var (
		versionString string
		err           error
	)
	if strings.Contains(ver, " ") {
		// It must have vendor information
		split := strings.Split(ver, " ")
		if len(split) > 0 || len(split[0]) > 0 {
			// Everything looks good.
			versionString = split[0]
		} else {
			// Something must be wrong with their vendor string.
			return
		}

		// Store the vendor version information.
		vendor = ver[len(versionString):]
	} else {
		// No vendor information.
		versionString = ver
	}

	// We have a proper version string now without vendor information.
	dots := strings.Count(versionString, ".")
	if dots == 1 {
		// It's a 'major.minor' style string
		versions := strings.Split(versionString, ".")
		if len(versions) == 2 {
			major, err = strconv.Atoi(versions[0])
			if err != nil {
				return
			}

			minor, err = strconv.Atoi(versions[1])
			if err != nil {
				return
			}

		} else {
			return
		}

	} else if dots == 2 {
		// It's a 'major.minor.release' style string
		versions := strings.Split(versionString, ".")
		if len(versions) == 3 {
			major, err = strconv.Atoi(versions[0])
			if err != nil {
				return
			}

			minor, err = strconv.Atoi(versions[1])
			if err != nil {
				return
			}

			release, err = strconv.Atoi(versions[2])
			if err != nil {
				return
			}
		} else {
			return
		}
	}
	return
}

func (c *Context) initVersion() {
	c.loadedVersion = true
	versionString := String(c.GetString(VERSION))
	c.major, c.minor, c.release, c.vendorVersion = c.parseVersionString(versionString)
}

func (c *Context) initShaderVersion() {
	c.loadedShaderVersion = true
	versionString := String(c.GetString(SHADING_LANGUAGE_VERSION))
	c.shaderMajor, c.shaderMinor, c.shaderRelease, c.vendorShaderVersion = c.parseVersionString(versionString)
}

// Version returns the major and minor OpenGL version supported by the
// implementation.
//
// Additionally provided is the vendor-specific release version (E.g. a driver
// version number).
func (c *Context) Version() (major, minor, release int) {
	if !c.loadedVersion {
		c.initVersion()
	}
	return c.major, c.minor, c.release
}

// AtLeastVersion tells if the major and minor OpenGL version reported by
// c.Version() is at least minMajor, minMinor.
//
// It is implemented as:
//
//  if major > minMajor {
//      return true
//  } else if major == minMajor && minor >= minMinor {
//      return true
//  }
//  return false
//
func (c *Context) AtLeastVersion(minMajor, minMinor int) bool {
	if !c.loadedVersion {
		c.initVersion()
	}
	major, minor := c.major, c.minor
	if major > minMajor {
		return true
	} else if major == minMajor && minor >= minMinor {
		return true
	}
	return false
}

// AtLeastRelease tells if the release OpenGL version reported by c.Version()
// is at least minRelease.
//
// It is implemented as:
//
//  if release == 0 {
//      return true
//  } else if release >= minRelease {
//      return true
//  }
//  return false
//
func (c *Context) AtLeastRelease(minRelease int) bool {
	if !c.loadedVersion {
		c.initVersion()
	}
	release := c.release
	if release == 0 {
		return true
	} else if release >= minRelease {
		return true
	}
	return false
}

// VendorVersion returns the vendor-specific OpenGL version information.
//
// This string depends on the vendor of the graphics card/driver.
func (c *Context) VendorVersion() string {
	if !c.loadedVersion {
		c.initVersion()
	}
	return c.vendorVersion
}

// ShaderVersion returns the major and minor version of the supported GLSL
// shading language per the OpenGL implementation.
//
// Additionally provided is the vendor-specific release version (E.g. a driver
// version number).
func (c *Context) ShaderVersion() (major, minor, release int) {
	if !c.loadedShaderVersion {
		c.initShaderVersion()
	}
	return c.shaderMajor, c.shaderMinor, c.shaderRelease
}

// AtLeastShaderVersion tells if the major and minor GLSL version reported by
// c.ShaderVersion() is at least minMajor, minMinor.
//
// It is implemented as:
//
//  if major > minMajor {
//      return true
//  } else if major == minMajor && minor >= minMinor {
//      return true
//  }
//  return false
//
func (c *Context) AtLeastShaderVersion(minMajor, minMinor int) bool {
	if !c.loadedShaderVersion {
		c.initShaderVersion()
	}
	major, minor := c.shaderMajor, c.shaderMinor
	if major > minMajor {
		return true
	} else if major == minMajor && minor >= minMinor {
		return true
	}
	return false
}

// AtLeastShaderRelease tells if the release GLSL version reported by
// c.ShaderVersion() is at least minRelease.
//
// It is implemented as:
//
//  if release == 0 {
//      return true
//  } else if release >= minRelease {
//      return true
//  }
//  return false
//
func (c *Context) AtLeastShaderRelease(minRelease int) bool {
	if !c.loadedShaderVersion {
		c.initShaderVersion()
	}
	release := c.shaderRelease
	if release == 0 {
		return true
	} else if release >= minRelease {
		return true
	}
	return false
}

// VendorShaderVersion returns the vendor-specific shading language version
// information.
//
// This string depends on the vendor of the graphics card/driver.
func (c *Context) VendorShaderVersion() string {
	if !c.loadedShaderVersion {
		c.initShaderVersion()
	}
	return c.vendorShaderVersion
}

func (c *Context) initExtensions() {
	// Initialize extensions map
	extString := String(c.GetString(EXTENSIONS))
	if len(extString) > 0 {
		split := strings.Split(extString, " ")
		c.extensions = make(map[string]bool, len(split))
		for _, ext := range split {
			if len(ext) > 0 {
				c.extensions[ext] = true
			}
		}
	} else {
		c.extensions = make(map[string]bool)
	}
}

// Extensions returns a slice of strings which represents all the extensions
// supported by the OpenGL implementation.
//
// Internally a map is used to store them, so a copy in the form of a slice is
// returned.
func (c *Context) Extensions() []string {
	if c.extensions == nil {
		c.initExtensions()
	}
	cpy := make([]string, len(c.extensions))
	i := 0
	for ext, _ := range c.extensions {
		cpy[i] = ext
		i++
	}
	return cpy
}

// Extension tells if the specified extension is supported by the OpenGL
// implementation.
func (c *Context) Extension(name string) (supported bool) {
	if c.extensions == nil {
		c.initExtensions()
	}
	_, supported = c.extensions[name]
	return
}

// Declare non-batchable functions

func (c *Context) CheckFramebufferStatus(target int32) int32 {
	return int32(C.gl_wrap_context_glCheckFramebufferStatus(c.c, C.GLenum(target)))
}

func (c *Context) CreateProgram() uint32 {
	return uint32(C.gl_wrap_context_glCreateProgram(c.c))
}

func (c *Context) CreateShader(pType int32) uint32 {
	return uint32(C.gl_wrap_context_glCreateShader(c.c, C.GLenum(pType)))
}

func (c *Context) GetAttribLocation(program uint32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetAttribLocation(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetError() int32 {
	return int32(C.gl_wrap_context_glGetError(c.c))
}

func (c *Context) GetString(name int32) *uint8 {
	return (*uint8)(unsafe.Pointer(C.gl_wrap_context_glGetString(c.c, C.GLenum(name))))
}

func (c *Context) GetUniformLocation(program uint32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetUniformLocation(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) IsBuffer(buffer uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsBuffer(c.c, C.GLuint(buffer)))
}

func (c *Context) IsEnabled(cap int32) uint8 {
	return uint8(C.gl_wrap_context_glIsEnabled(c.c, C.GLenum(cap)))
}

func (c *Context) IsFramebuffer(framebuffer uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsFramebuffer(c.c, C.GLuint(framebuffer)))
}

func (c *Context) IsProgram(program uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsProgram(c.c, C.GLuint(program)))
}

func (c *Context) IsRenderbuffer(renderbuffer uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsRenderbuffer(c.c, C.GLuint(renderbuffer)))
}

func (c *Context) IsShader(shader uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsShader(c.c, C.GLuint(shader)))
}

func (c *Context) IsTexture(texture uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsTexture(c.c, C.GLuint(texture)))
}

func (c *Context) IsQuery(id uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsQuery(c.c, C.GLuint(id)))
}

func (c *Context) UnmapBuffer(target int32) uint8 {
	return uint8(C.gl_wrap_context_glUnmapBuffer(c.c, C.GLenum(target)))
}

func (c *Context) IsVertexArray(array uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsVertexArray(c.c, C.GLuint(array)))
}

func (c *Context) GetFragDataLocation(program uint32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetFragDataLocation(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetStringi(name int32, index uint32) *uint8 {
	return (*uint8)(unsafe.Pointer(C.gl_wrap_context_glGetStringi(c.c, C.GLenum(name), C.GLuint(index))))
}

func (c *Context) GetUniformBlockIndex(program uint32, uniformBlockName *byte) uint32 {
	return uint32(C.gl_wrap_context_glGetUniformBlockIndex(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(uniformBlockName))))
}

func (c *Context) FenceSync(condition int32, flags uint32) Sync {
	return Sync(C.gl_wrap_context_glFenceSync(c.c, C.GLenum(condition), C.GLbitfield(flags)))
}

func (c *Context) IsSync(sync Sync) uint8 {
	return uint8(C.gl_wrap_context_glIsSync(c.c, C.GLsync(sync)))
}

func (c *Context) ClientWaitSync(sync Sync, flags uint32, timeout uint64) int32 {
	return int32(C.gl_wrap_context_glClientWaitSync(c.c, C.GLsync(sync), C.GLbitfield(flags), C.GLuint64(timeout)))
}

func (c *Context) IsSampler(sampler uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsSampler(c.c, C.GLuint(sampler)))
}

func (c *Context) IsTransformFeedback(id uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsTransformFeedback(c.c, C.GLuint(id)))
}

func (c *Context) GetProgramResourceIndex(program uint32, programInterface int32, name *byte) uint32 {
	return uint32(C.gl_wrap_context_glGetProgramResourceIndex(c.c, C.GLuint(program), C.GLenum(programInterface), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetProgramResourceLocation(program uint32, programInterface int32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetProgramResourceLocation(c.c, C.GLuint(program), C.GLenum(programInterface), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) CreateShaderProgramv(pType int32, count uint32, strings **byte) uint32 {
	return uint32(C.gl_wrap_context_glCreateShaderProgramv(c.c, C.GLenum(pType), C.GLsizei(count), (**C.GLchar)(unsafe.Pointer(strings))))
}

func (c *Context) IsProgramPipeline(pipeline uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsProgramPipeline(c.c, C.GLuint(pipeline)))
}

// Declare batchable functions

func (c *Context) ActiveTexture(texture int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glActiveTexture_args
		glWrapHandlerArgs.texture = C.GLenum(texture)

		c.push(C.gl_wrap_batch_func{
			jump_index: 0,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glActiveTexture(c.c, C.GLenum(texture))
	}
}

func (c *Context) AttachShader(program uint32, shader uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glAttachShader_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.shader = C.GLuint(shader)

		c.push(C.gl_wrap_batch_func{
			jump_index: 1,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glAttachShader(c.c, C.GLuint(program), C.GLuint(shader))
	}
}

func (c *Context) BindAttribLocation(program uint32, index uint32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindAttribLocation_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 2,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindAttribLocation(c.c, C.GLuint(program), C.GLuint(index), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) BindBuffer(target int32, buffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindBuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 3,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindBuffer(c.c, C.GLenum(target), C.GLuint(buffer))
	}
}

func (c *Context) BindFramebuffer(target int32, framebuffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindFramebuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.framebuffer = C.GLuint(framebuffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 4,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindFramebuffer(c.c, C.GLenum(target), C.GLuint(framebuffer))
	}
}

func (c *Context) BindRenderbuffer(target int32, renderbuffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindRenderbuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.renderbuffer = C.GLuint(renderbuffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 5,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindRenderbuffer(c.c, C.GLenum(target), C.GLuint(renderbuffer))
	}
}

func (c *Context) BindTexture(target int32, texture uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindTexture_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.texture = C.GLuint(texture)

		c.push(C.gl_wrap_batch_func{
			jump_index: 6,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindTexture(c.c, C.GLenum(target), C.GLuint(texture))
	}
}

func (c *Context) BlendColor(red float32, green float32, blue float32, alpha float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendColor_args
		glWrapHandlerArgs.red = C.GLfloat(red)
		glWrapHandlerArgs.green = C.GLfloat(green)
		glWrapHandlerArgs.blue = C.GLfloat(blue)
		glWrapHandlerArgs.alpha = C.GLfloat(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 7,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendColor(c.c, C.GLfloat(red), C.GLfloat(green), C.GLfloat(blue), C.GLfloat(alpha))
	}
}

func (c *Context) BlendEquation(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendEquation_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 8,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendEquation(c.c, C.GLenum(mode))
	}
}

func (c *Context) BlendEquationSeparate(modeRGB int32, modeAlpha int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendEquationSeparate_args
		glWrapHandlerArgs.modeRGB = C.GLenum(modeRGB)
		glWrapHandlerArgs.modeAlpha = C.GLenum(modeAlpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 9,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendEquationSeparate(c.c, C.GLenum(modeRGB), C.GLenum(modeAlpha))
	}
}

func (c *Context) BlendFunc(sfactor int32, dfactor int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendFunc_args
		glWrapHandlerArgs.sfactor = C.GLenum(sfactor)
		glWrapHandlerArgs.dfactor = C.GLenum(dfactor)

		c.push(C.gl_wrap_batch_func{
			jump_index: 10,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendFunc(c.c, C.GLenum(sfactor), C.GLenum(dfactor))
	}
}

func (c *Context) BlendFuncSeparate(sfactorRGB int32, dfactorRGB int32, sfactorAlpha int32, dfactorAlpha int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendFuncSeparate_args
		glWrapHandlerArgs.sfactorRGB = C.GLenum(sfactorRGB)
		glWrapHandlerArgs.dfactorRGB = C.GLenum(dfactorRGB)
		glWrapHandlerArgs.sfactorAlpha = C.GLenum(sfactorAlpha)
		glWrapHandlerArgs.dfactorAlpha = C.GLenum(dfactorAlpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 11,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendFuncSeparate(c.c, C.GLenum(sfactorRGB), C.GLenum(dfactorRGB), C.GLenum(sfactorAlpha), C.GLenum(dfactorAlpha))
	}
}

func (c *Context) BufferData(target int32, size uintptr, data unsafe.Pointer, usage int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBufferData_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)
		glWrapHandlerArgs.data = data
		glWrapHandlerArgs.usage = C.GLenum(usage)

		c.push(C.gl_wrap_batch_func{
			jump_index: 12,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBufferData(c.c, C.GLenum(target), C.GLsizeiptr(size), data, C.GLenum(usage))
	}
}

func (c *Context) BufferSubData(target int32, offset uintptr, size uintptr, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBufferSubData_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 13,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBufferSubData(c.c, C.GLenum(target), C.GLintptr(offset), C.GLsizeiptr(size), data)
	}
}

func (c *Context) Clear(mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClear_args
		glWrapHandlerArgs.mask = C.GLbitfield(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 14,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClear(c.c, C.GLbitfield(mask))
	}
}

func (c *Context) ClearColor(red float32, green float32, blue float32, alpha float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearColor_args
		glWrapHandlerArgs.red = C.GLfloat(red)
		glWrapHandlerArgs.green = C.GLfloat(green)
		glWrapHandlerArgs.blue = C.GLfloat(blue)
		glWrapHandlerArgs.alpha = C.GLfloat(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 15,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearColor(c.c, C.GLfloat(red), C.GLfloat(green), C.GLfloat(blue), C.GLfloat(alpha))
	}
}

func (c *Context) ClearDepthf(d float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearDepthf_args
		glWrapHandlerArgs.d = C.GLfloat(d)

		c.push(C.gl_wrap_batch_func{
			jump_index: 16,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearDepthf(c.c, C.GLfloat(d))
	}
}

func (c *Context) ClearStencil(s int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearStencil_args
		glWrapHandlerArgs.s = C.GLint(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 17,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearStencil(c.c, C.GLint(s))
	}
}

func (c *Context) ColorMask(red uint8, green uint8, blue uint8, alpha uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorMask_args
		glWrapHandlerArgs.red = C.GLboolean(red)
		glWrapHandlerArgs.green = C.GLboolean(green)
		glWrapHandlerArgs.blue = C.GLboolean(blue)
		glWrapHandlerArgs.alpha = C.GLboolean(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 18,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorMask(c.c, C.GLboolean(red), C.GLboolean(green), C.GLboolean(blue), C.GLboolean(alpha))
	}
}

func (c *Context) CompileShader(shader uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompileShader_args
		glWrapHandlerArgs.shader = C.GLuint(shader)

		c.push(C.gl_wrap_batch_func{
			jump_index: 19,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompileShader(c.c, C.GLuint(shader))
	}
}

func (c *Context) CompressedTexImage2D(target int32, level int32, internalformat int32, width uint32, height uint32, border int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 20,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLint(border), C.GLsizei(imageSize), data)
	}
}

func (c *Context) CompressedTexSubImage2D(target int32, level int32, xoffset int32, yoffset int32, width uint32, height uint32, format int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexSubImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 21,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexSubImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLsizei(width), C.GLsizei(height), C.GLenum(format), C.GLsizei(imageSize), data)
	}
}

func (c *Context) CopyTexImage2D(target int32, level int32, internalformat int32, x int32, y int32, width uint32, height uint32, border int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyTexImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.border = C.GLint(border)

		c.push(C.gl_wrap_batch_func{
			jump_index: 22,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyTexImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLenum(internalformat), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height), C.GLint(border))
	}
}

func (c *Context) CopyTexSubImage2D(target int32, level int32, xoffset int32, yoffset int32, x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyTexSubImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 23,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyTexSubImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) CullFace(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCullFace_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 24,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCullFace(c.c, C.GLenum(mode))
	}
}

func (c *Context) DeleteBuffers(n uint32, buffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteBuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.buffers = (*C.GLuint)(unsafe.Pointer(buffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 25,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteBuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(buffers)))
	}
}

func (c *Context) DeleteFramebuffers(n uint32, framebuffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteFramebuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.framebuffers = (*C.GLuint)(unsafe.Pointer(framebuffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 26,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteFramebuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(framebuffers)))
	}
}

func (c *Context) DeleteProgram(program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteProgram_args
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 27,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteProgram(c.c, C.GLuint(program))
	}
}

func (c *Context) DeleteRenderbuffers(n uint32, renderbuffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteRenderbuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.renderbuffers = (*C.GLuint)(unsafe.Pointer(renderbuffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 28,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteRenderbuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(renderbuffers)))
	}
}

func (c *Context) DeleteShader(shader uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteShader_args
		glWrapHandlerArgs.shader = C.GLuint(shader)

		c.push(C.gl_wrap_batch_func{
			jump_index: 29,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteShader(c.c, C.GLuint(shader))
	}
}

func (c *Context) DeleteTextures(n uint32, textures *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteTextures_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.textures = (*C.GLuint)(unsafe.Pointer(textures))

		c.push(C.gl_wrap_batch_func{
			jump_index: 30,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteTextures(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(textures)))
	}
}

func (c *Context) DepthFunc(pFunc int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthFunc_args
		glWrapHandlerArgs._func = C.GLenum(pFunc)

		c.push(C.gl_wrap_batch_func{
			jump_index: 31,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthFunc(c.c, C.GLenum(pFunc))
	}
}

func (c *Context) DepthMask(flag uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthMask_args
		glWrapHandlerArgs.flag = C.GLboolean(flag)

		c.push(C.gl_wrap_batch_func{
			jump_index: 32,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthMask(c.c, C.GLboolean(flag))
	}
}

func (c *Context) DepthRangef(n float32, f float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthRangef_args
		glWrapHandlerArgs.n = C.GLfloat(n)
		glWrapHandlerArgs.f = C.GLfloat(f)

		c.push(C.gl_wrap_batch_func{
			jump_index: 33,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthRangef(c.c, C.GLfloat(n), C.GLfloat(f))
	}
}

func (c *Context) DetachShader(program uint32, shader uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDetachShader_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.shader = C.GLuint(shader)

		c.push(C.gl_wrap_batch_func{
			jump_index: 34,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDetachShader(c.c, C.GLuint(program), C.GLuint(shader))
	}
}

func (c *Context) Disable(cap int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDisable_args
		glWrapHandlerArgs.cap = C.GLenum(cap)

		c.push(C.gl_wrap_batch_func{
			jump_index: 35,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDisable(c.c, C.GLenum(cap))
	}
}

func (c *Context) DisableVertexAttribArray(index uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDisableVertexAttribArray_args
		glWrapHandlerArgs.index = C.GLuint(index)

		c.push(C.gl_wrap_batch_func{
			jump_index: 36,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDisableVertexAttribArray(c.c, C.GLuint(index))
	}
}

func (c *Context) DrawArrays(mode int32, first int32, count uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawArrays_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.first = C.GLint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)

		c.push(C.gl_wrap_batch_func{
			jump_index: 37,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawArrays(c.c, C.GLenum(mode), C.GLint(first), C.GLsizei(count))
	}
}

func (c *Context) DrawElements(mode int32, count uint32, pType int32, indices unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElements_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices

		c.push(C.gl_wrap_batch_func{
			jump_index: 38,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElements(c.c, C.GLenum(mode), C.GLsizei(count), C.GLenum(pType), indices)
	}
}

func (c *Context) Enable(cap int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEnable_args
		glWrapHandlerArgs.cap = C.GLenum(cap)

		c.push(C.gl_wrap_batch_func{
			jump_index: 39,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEnable(c.c, C.GLenum(cap))
	}
}

func (c *Context) EnableVertexAttribArray(index uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEnableVertexAttribArray_args
		glWrapHandlerArgs.index = C.GLuint(index)

		c.push(C.gl_wrap_batch_func{
			jump_index: 40,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEnableVertexAttribArray(c.c, C.GLuint(index))
	}
}

func (c *Context) Finish() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFinish_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 41,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFinish(c.c)
	}
}

func (c *Context) Flush() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFlush_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 42,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFlush(c.c)
	}
}

func (c *Context) FramebufferRenderbuffer(target int32, attachment int32, renderbuffertarget int32, renderbuffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferRenderbuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.renderbuffertarget = C.GLenum(renderbuffertarget)
		glWrapHandlerArgs.renderbuffer = C.GLuint(renderbuffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 43,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferRenderbuffer(c.c, C.GLenum(target), C.GLenum(attachment), C.GLenum(renderbuffertarget), C.GLuint(renderbuffer))
	}
}

func (c *Context) FramebufferTexture2D(target int32, attachment int32, textarget int32, texture uint32, level int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferTexture2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.textarget = C.GLenum(textarget)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)

		c.push(C.gl_wrap_batch_func{
			jump_index: 44,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferTexture2D(c.c, C.GLenum(target), C.GLenum(attachment), C.GLenum(textarget), C.GLuint(texture), C.GLint(level))
	}
}

func (c *Context) FrontFace(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFrontFace_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 45,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFrontFace(c.c, C.GLenum(mode))
	}
}

func (c *Context) GenBuffers(n uint32, buffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenBuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.buffers = (*C.GLuint)(unsafe.Pointer(buffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 46,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenBuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(buffers)))
	}
}

func (c *Context) GenerateMipmap(target int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenerateMipmap_args
		glWrapHandlerArgs.target = C.GLenum(target)

		c.push(C.gl_wrap_batch_func{
			jump_index: 47,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenerateMipmap(c.c, C.GLenum(target))
	}
}

func (c *Context) GenFramebuffers(n uint32, framebuffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenFramebuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.framebuffers = (*C.GLuint)(unsafe.Pointer(framebuffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 48,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenFramebuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(framebuffers)))
	}
}

func (c *Context) GenRenderbuffers(n uint32, renderbuffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenRenderbuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.renderbuffers = (*C.GLuint)(unsafe.Pointer(renderbuffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 49,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenRenderbuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(renderbuffers)))
	}
}

func (c *Context) GenTextures(n uint32, textures *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenTextures_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.textures = (*C.GLuint)(unsafe.Pointer(textures))

		c.push(C.gl_wrap_batch_func{
			jump_index: 50,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenTextures(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(textures)))
	}
}

func (c *Context) GetActiveAttrib(program uint32, index uint32, bufSize uint32, length *uint32, size *int32, pType *int32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveAttrib_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.size = (*C.GLint)(unsafe.Pointer(size))
		glWrapHandlerArgs._type = (*C.GLenum)(unsafe.Pointer(pType))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 51,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveAttrib(c.c, C.GLuint(program), C.GLuint(index), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLint)(unsafe.Pointer(size)), (*C.GLenum)(unsafe.Pointer(pType)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) GetActiveUniform(program uint32, index uint32, bufSize uint32, length *uint32, size *int32, pType *int32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniform_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.size = (*C.GLint)(unsafe.Pointer(size))
		glWrapHandlerArgs._type = (*C.GLenum)(unsafe.Pointer(pType))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 52,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniform(c.c, C.GLuint(program), C.GLuint(index), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLint)(unsafe.Pointer(size)), (*C.GLenum)(unsafe.Pointer(pType)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) GetAttachedShaders(program uint32, maxCount uint32, count *uint32, shaders *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetAttachedShaders_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.maxCount = C.GLsizei(maxCount)
		glWrapHandlerArgs.count = (*C.GLsizei)(unsafe.Pointer(count))
		glWrapHandlerArgs.shaders = (*C.GLuint)(unsafe.Pointer(shaders))

		c.push(C.gl_wrap_batch_func{
			jump_index: 53,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetAttachedShaders(c.c, C.GLuint(program), C.GLsizei(maxCount), (*C.GLsizei)(unsafe.Pointer(count)), (*C.GLuint)(unsafe.Pointer(shaders)))
	}
}

func (c *Context) GetBooleanv(pname int32, data *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBooleanv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLboolean)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 54,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBooleanv(c.c, C.GLenum(pname), (*C.GLboolean)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetBufferParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBufferParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 55,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBufferParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetFloatv(pname int32, data *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetFloatv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLfloat)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 56,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetFloatv(c.c, C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetFramebufferAttachmentParameteriv(target int32, attachment int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetFramebufferAttachmentParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 57,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetFramebufferAttachmentParameteriv(c.c, C.GLenum(target), C.GLenum(attachment), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetIntegerv(pname int32, data *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetIntegerv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLint)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 58,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetIntegerv(c.c, C.GLenum(pname), (*C.GLint)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetProgramiv(program uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 59,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramiv(c.c, C.GLuint(program), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetProgramInfoLog(program uint32, bufSize uint32, length *uint32, infoLog *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramInfoLog_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.infoLog = (*C.GLchar)(unsafe.Pointer(infoLog))

		c.push(C.gl_wrap_batch_func{
			jump_index: 60,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramInfoLog(c.c, C.GLuint(program), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(infoLog)))
	}
}

func (c *Context) GetRenderbufferParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetRenderbufferParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 61,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetRenderbufferParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetShaderiv(shader uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetShaderiv_args
		glWrapHandlerArgs.shader = C.GLuint(shader)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 62,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetShaderiv(c.c, C.GLuint(shader), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetShaderInfoLog(shader uint32, bufSize uint32, length *uint32, infoLog *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetShaderInfoLog_args
		glWrapHandlerArgs.shader = C.GLuint(shader)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.infoLog = (*C.GLchar)(unsafe.Pointer(infoLog))

		c.push(C.gl_wrap_batch_func{
			jump_index: 63,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetShaderInfoLog(c.c, C.GLuint(shader), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(infoLog)))
	}
}

func (c *Context) GetShaderPrecisionFormat(shadertype int32, precisiontype int32, pRange *int32, precision *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetShaderPrecisionFormat_args
		glWrapHandlerArgs.shadertype = C.GLenum(shadertype)
		glWrapHandlerArgs.precisiontype = C.GLenum(precisiontype)
		glWrapHandlerArgs._range = (*C.GLint)(unsafe.Pointer(pRange))
		glWrapHandlerArgs.precision = (*C.GLint)(unsafe.Pointer(precision))

		c.push(C.gl_wrap_batch_func{
			jump_index: 64,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetShaderPrecisionFormat(c.c, C.GLenum(shadertype), C.GLenum(precisiontype), (*C.GLint)(unsafe.Pointer(pRange)), (*C.GLint)(unsafe.Pointer(precision)))
	}
}

func (c *Context) GetShaderSource(shader uint32, bufSize uint32, length *uint32, source *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetShaderSource_args
		glWrapHandlerArgs.shader = C.GLuint(shader)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.source = (*C.GLchar)(unsafe.Pointer(source))

		c.push(C.gl_wrap_batch_func{
			jump_index: 65,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetShaderSource(c.c, C.GLuint(shader), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(source)))
	}
}

func (c *Context) GetTexParameterfv(target int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexParameterfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 66,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexParameterfv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 67,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetUniformfv(program uint32, location int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformfv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 68,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformfv(c.c, C.GLuint(program), C.GLint(location), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetUniformiv(program uint32, location int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 69,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformiv(c.c, C.GLuint(program), C.GLint(location), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribfv(index uint32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribfv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 70,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribfv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribiv(index uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 71,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribiv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribPointerv(index uint32, pname int32, pointer *unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribPointerv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 72,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribPointerv(c.c, C.GLuint(index), C.GLenum(pname), pointer)
	}
}

func (c *Context) Hint(target int32, mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glHint_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 73,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glHint(c.c, C.GLenum(target), C.GLenum(mode))
	}
}

func (c *Context) LineWidth(width float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLineWidth_args
		glWrapHandlerArgs.width = C.GLfloat(width)

		c.push(C.gl_wrap_batch_func{
			jump_index: 74,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLineWidth(c.c, C.GLfloat(width))
	}
}

func (c *Context) LinkProgram(program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLinkProgram_args
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 75,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLinkProgram(c.c, C.GLuint(program))
	}
}

func (c *Context) PixelStorei(pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelStorei_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 76,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelStorei(c.c, C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) PolygonOffset(factor float32, units float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPolygonOffset_args
		glWrapHandlerArgs.factor = C.GLfloat(factor)
		glWrapHandlerArgs.units = C.GLfloat(units)

		c.push(C.gl_wrap_batch_func{
			jump_index: 77,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPolygonOffset(c.c, C.GLfloat(factor), C.GLfloat(units))
	}
}

func (c *Context) ReadPixels(x int32, y int32, width uint32, height uint32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glReadPixels_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 78,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glReadPixels(c.c, C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) ReleaseShaderCompiler() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glReleaseShaderCompiler_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 79,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glReleaseShaderCompiler(c.c)
	}
}

func (c *Context) RenderbufferStorage(target int32, internalformat int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRenderbufferStorage_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 80,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRenderbufferStorage(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) SampleCoverage(value float32, invert uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSampleCoverage_args
		glWrapHandlerArgs.value = C.GLfloat(value)
		glWrapHandlerArgs.invert = C.GLboolean(invert)

		c.push(C.gl_wrap_batch_func{
			jump_index: 81,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSampleCoverage(c.c, C.GLfloat(value), C.GLboolean(invert))
	}
}

func (c *Context) Scissor(x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glScissor_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 82,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glScissor(c.c, C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) ShaderBinary(count uint32, shaders *uint32, binaryformat int32, binary unsafe.Pointer, length uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glShaderBinary_args
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.shaders = (*C.GLuint)(unsafe.Pointer(shaders))
		glWrapHandlerArgs.binaryformat = C.GLenum(binaryformat)
		glWrapHandlerArgs.binary = binary
		glWrapHandlerArgs.length = C.GLsizei(length)

		c.push(C.gl_wrap_batch_func{
			jump_index: 83,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glShaderBinary(c.c, C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(shaders)), C.GLenum(binaryformat), binary, C.GLsizei(length))
	}
}

func (c *Context) ShaderSource(shader uint32, count uint32, string **byte, length *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glShaderSource_args
		glWrapHandlerArgs.shader = C.GLuint(shader)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.string = (**C.GLchar)(unsafe.Pointer(string))
		glWrapHandlerArgs.length = (*C.GLint)(unsafe.Pointer(length))

		c.push(C.gl_wrap_batch_func{
			jump_index: 84,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glShaderSource(c.c, C.GLuint(shader), C.GLsizei(count), (**C.GLchar)(unsafe.Pointer(string)), (*C.GLint)(unsafe.Pointer(length)))
	}
}

func (c *Context) StencilFunc(pFunc int32, ref int32, mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilFunc_args
		glWrapHandlerArgs._func = C.GLenum(pFunc)
		glWrapHandlerArgs.ref = C.GLint(ref)
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 85,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilFunc(c.c, C.GLenum(pFunc), C.GLint(ref), C.GLuint(mask))
	}
}

func (c *Context) StencilFuncSeparate(face int32, pFunc int32, ref int32, mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilFuncSeparate_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs._func = C.GLenum(pFunc)
		glWrapHandlerArgs.ref = C.GLint(ref)
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 86,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilFuncSeparate(c.c, C.GLenum(face), C.GLenum(pFunc), C.GLint(ref), C.GLuint(mask))
	}
}

func (c *Context) StencilMask(mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilMask_args
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 87,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilMask(c.c, C.GLuint(mask))
	}
}

func (c *Context) StencilMaskSeparate(face int32, mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilMaskSeparate_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 88,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilMaskSeparate(c.c, C.GLenum(face), C.GLuint(mask))
	}
}

func (c *Context) StencilOp(fail int32, zfail int32, zpass int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilOp_args
		glWrapHandlerArgs.fail = C.GLenum(fail)
		glWrapHandlerArgs.zfail = C.GLenum(zfail)
		glWrapHandlerArgs.zpass = C.GLenum(zpass)

		c.push(C.gl_wrap_batch_func{
			jump_index: 89,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilOp(c.c, C.GLenum(fail), C.GLenum(zfail), C.GLenum(zpass))
	}
}

func (c *Context) StencilOpSeparate(face int32, sfail int32, dpfail int32, dppass int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilOpSeparate_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.sfail = C.GLenum(sfail)
		glWrapHandlerArgs.dpfail = C.GLenum(dpfail)
		glWrapHandlerArgs.dppass = C.GLenum(dppass)

		c.push(C.gl_wrap_batch_func{
			jump_index: 90,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilOpSeparate(c.c, C.GLenum(face), C.GLenum(sfail), C.GLenum(dpfail), C.GLenum(dppass))
	}
}

func (c *Context) TexImage2D(target int32, level int32, internalformat int32, width uint32, height uint32, border int32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLint(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 91,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLint(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLint(border), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) TexParameterf(target int32, pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameterf_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 92,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameterf(c.c, C.GLenum(target), C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) TexParameterfv(target int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameterfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 93,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameterfv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexParameteri(target int32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameteri_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 94,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameteri(c.c, C.GLenum(target), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) TexParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 95,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexSubImage2D(target int32, level int32, xoffset int32, yoffset int32, width uint32, height uint32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexSubImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 96,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexSubImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLsizei(width), C.GLsizei(height), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) Uniform1f(location int32, v0 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1f_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 97,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1f(c.c, C.GLint(location), C.GLfloat(v0))
	}
}

func (c *Context) Uniform1fv(location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 98,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1fv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform1i(location int32, v0 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1i_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 99,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1i(c.c, C.GLint(location), C.GLint(v0))
	}
}

func (c *Context) Uniform1iv(location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1iv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 100,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1iv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform2f(location int32, v0 float32, v1 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2f_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 101,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2f(c.c, C.GLint(location), C.GLfloat(v0), C.GLfloat(v1))
	}
}

func (c *Context) Uniform2fv(location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 102,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2fv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform2i(location int32, v0 int32, v1 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2i_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 103,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2i(c.c, C.GLint(location), C.GLint(v0), C.GLint(v1))
	}
}

func (c *Context) Uniform2iv(location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2iv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 104,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2iv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform3f(location int32, v0 float32, v1 float32, v2 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3f_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 105,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3f(c.c, C.GLint(location), C.GLfloat(v0), C.GLfloat(v1), C.GLfloat(v2))
	}
}

func (c *Context) Uniform3fv(location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 106,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3fv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform3i(location int32, v0 int32, v1 int32, v2 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3i_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)
		glWrapHandlerArgs.v2 = C.GLint(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 107,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3i(c.c, C.GLint(location), C.GLint(v0), C.GLint(v1), C.GLint(v2))
	}
}

func (c *Context) Uniform3iv(location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3iv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 108,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3iv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform4f(location int32, v0 float32, v1 float32, v2 float32, v3 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4f_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)
		glWrapHandlerArgs.v3 = C.GLfloat(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 109,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4f(c.c, C.GLint(location), C.GLfloat(v0), C.GLfloat(v1), C.GLfloat(v2), C.GLfloat(v3))
	}
}

func (c *Context) Uniform4fv(location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 110,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4fv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform4i(location int32, v0 int32, v1 int32, v2 int32, v3 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4i_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)
		glWrapHandlerArgs.v2 = C.GLint(v2)
		glWrapHandlerArgs.v3 = C.GLint(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 111,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4i(c.c, C.GLint(location), C.GLint(v0), C.GLint(v1), C.GLint(v2), C.GLint(v3))
	}
}

func (c *Context) Uniform4iv(location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4iv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 112,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4iv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix2fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 113,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 114,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 115,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UseProgram(program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUseProgram_args
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 116,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUseProgram(c.c, C.GLuint(program))
	}
}

func (c *Context) ValidateProgram(program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glValidateProgram_args
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 117,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glValidateProgram(c.c, C.GLuint(program))
	}
}

func (c *Context) VertexAttrib1f(index uint32, x float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib1f_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)

		c.push(C.gl_wrap_batch_func{
			jump_index: 118,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib1f(c.c, C.GLuint(index), C.GLfloat(x))
	}
}

func (c *Context) VertexAttrib1fv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib1fv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 119,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib1fv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib2f(index uint32, x float32, y float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib2f_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 120,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib2f(c.c, C.GLuint(index), C.GLfloat(x), C.GLfloat(y))
	}
}

func (c *Context) VertexAttrib2fv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib2fv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 121,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib2fv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib3f(index uint32, x float32, y float32, z float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib3f_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 122,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib3f(c.c, C.GLuint(index), C.GLfloat(x), C.GLfloat(y), C.GLfloat(z))
	}
}

func (c *Context) VertexAttrib3fv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib3fv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 123,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib3fv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4f(index uint32, x float32, y float32, z float32, w float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4f_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)
		glWrapHandlerArgs.w = C.GLfloat(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 124,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4f(c.c, C.GLuint(index), C.GLfloat(x), C.GLfloat(y), C.GLfloat(z), C.GLfloat(w))
	}
}

func (c *Context) VertexAttrib4fv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4fv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 125,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4fv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribPointer(index uint32, size int32, pType int32, normalized uint8, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribPointer_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 126,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribPointer(c.c, C.GLuint(index), C.GLint(size), C.GLenum(pType), C.GLboolean(normalized), C.GLsizei(stride), pointer)
	}
}

func (c *Context) Viewport(x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glViewport_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 127,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glViewport(c.c, C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) ReadBuffer(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glReadBuffer_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 128,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glReadBuffer(c.c, C.GLenum(mode))
	}
}

func (c *Context) DrawRangeElements(mode int32, start uint32, end uint32, count uint32, pType int32, indices unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawRangeElements_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.start = C.GLuint(start)
		glWrapHandlerArgs.end = C.GLuint(end)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices

		c.push(C.gl_wrap_batch_func{
			jump_index: 129,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawRangeElements(c.c, C.GLenum(mode), C.GLuint(start), C.GLuint(end), C.GLsizei(count), C.GLenum(pType), indices)
	}
}

func (c *Context) TexImage3D(target int32, level int32, internalformat int32, width uint32, height uint32, depth uint32, border int32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLint(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 130,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLint(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLint(border), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) TexSubImage3D(target int32, level int32, xoffset int32, yoffset int32, zoffset int32, width uint32, height uint32, depth uint32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexSubImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 131,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexSubImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(zoffset), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) CopyTexSubImage3D(target int32, level int32, xoffset int32, yoffset int32, zoffset int32, x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyTexSubImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 132,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyTexSubImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(zoffset), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) CompressedTexImage3D(target int32, level int32, internalformat int32, width uint32, height uint32, depth uint32, border int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 133,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLint(border), C.GLsizei(imageSize), data)
	}
}

func (c *Context) CompressedTexSubImage3D(target int32, level int32, xoffset int32, yoffset int32, zoffset int32, width uint32, height uint32, depth uint32, format int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexSubImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 134,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexSubImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(zoffset), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLenum(format), C.GLsizei(imageSize), data)
	}
}

func (c *Context) GenQueries(n uint32, ids *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenQueries_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))

		c.push(C.gl_wrap_batch_func{
			jump_index: 135,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenQueries(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(ids)))
	}
}

func (c *Context) DeleteQueries(n uint32, ids *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteQueries_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))

		c.push(C.gl_wrap_batch_func{
			jump_index: 136,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteQueries(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(ids)))
	}
}

func (c *Context) BeginQuery(target int32, id uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBeginQuery_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.id = C.GLuint(id)

		c.push(C.gl_wrap_batch_func{
			jump_index: 137,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBeginQuery(c.c, C.GLenum(target), C.GLuint(id))
	}
}

func (c *Context) EndQuery(target int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEndQuery_args
		glWrapHandlerArgs.target = C.GLenum(target)

		c.push(C.gl_wrap_batch_func{
			jump_index: 138,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEndQuery(c.c, C.GLenum(target))
	}
}

func (c *Context) GetQueryiv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetQueryiv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 139,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetQueryiv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetQueryObjectuiv(id uint32, pname int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetQueryObjectuiv_args
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 140,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetQueryObjectuiv(c.c, C.GLuint(id), C.GLenum(pname), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetBufferPointerv(target int32, pname int32, params *unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBufferPointerv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = params

		c.push(C.gl_wrap_batch_func{
			jump_index: 141,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBufferPointerv(c.c, C.GLenum(target), C.GLenum(pname), params)
	}
}

func (c *Context) DrawBuffers(n uint32, bufs *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawBuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.bufs = (*C.GLenum)(unsafe.Pointer(bufs))

		c.push(C.gl_wrap_batch_func{
			jump_index: 142,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawBuffers(c.c, C.GLsizei(n), (*C.GLenum)(unsafe.Pointer(bufs)))
	}
}

func (c *Context) UniformMatrix2x3fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2x3fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 143,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2x3fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3x2fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3x2fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 144,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3x2fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix2x4fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2x4fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 145,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2x4fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4x2fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4x2fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 146,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4x2fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3x4fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3x4fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 147,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3x4fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4x3fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4x3fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 148,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4x3fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) BlitFramebuffer(srcX0 int32, srcY0 int32, srcX1 int32, srcY1 int32, dstX0 int32, dstY0 int32, dstX1 int32, dstY1 int32, mask uint32, filter int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlitFramebuffer_args
		glWrapHandlerArgs.srcX0 = C.GLint(srcX0)
		glWrapHandlerArgs.srcY0 = C.GLint(srcY0)
		glWrapHandlerArgs.srcX1 = C.GLint(srcX1)
		glWrapHandlerArgs.srcY1 = C.GLint(srcY1)
		glWrapHandlerArgs.dstX0 = C.GLint(dstX0)
		glWrapHandlerArgs.dstY0 = C.GLint(dstY0)
		glWrapHandlerArgs.dstX1 = C.GLint(dstX1)
		glWrapHandlerArgs.dstY1 = C.GLint(dstY1)
		glWrapHandlerArgs.mask = C.GLbitfield(mask)
		glWrapHandlerArgs.filter = C.GLenum(filter)

		c.push(C.gl_wrap_batch_func{
			jump_index: 149,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlitFramebuffer(c.c, C.GLint(srcX0), C.GLint(srcY0), C.GLint(srcX1), C.GLint(srcY1), C.GLint(dstX0), C.GLint(dstY0), C.GLint(dstX1), C.GLint(dstY1), C.GLbitfield(mask), C.GLenum(filter))
	}
}

func (c *Context) RenderbufferStorageMultisample(target int32, samples uint32, internalformat int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRenderbufferStorageMultisample_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.samples = C.GLsizei(samples)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 150,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRenderbufferStorageMultisample(c.c, C.GLenum(target), C.GLsizei(samples), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) FramebufferTextureLayer(target int32, attachment int32, texture uint32, level int32, layer int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferTextureLayer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.layer = C.GLint(layer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 151,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferTextureLayer(c.c, C.GLenum(target), C.GLenum(attachment), C.GLuint(texture), C.GLint(level), C.GLint(layer))
	}
}

func (c *Context) MapBufferRange(target int32, offset uintptr, length uintptr, access uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMapBufferRange_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.length = C.GLsizeiptr(length)
		glWrapHandlerArgs.access = C.GLbitfield(access)

		c.push(C.gl_wrap_batch_func{
			jump_index: 152,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMapBufferRange(c.c, C.GLenum(target), C.GLintptr(offset), C.GLsizeiptr(length), C.GLbitfield(access))
	}
}

func (c *Context) FlushMappedBufferRange(target int32, offset uintptr, length uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFlushMappedBufferRange_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.length = C.GLsizeiptr(length)

		c.push(C.gl_wrap_batch_func{
			jump_index: 153,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFlushMappedBufferRange(c.c, C.GLenum(target), C.GLintptr(offset), C.GLsizeiptr(length))
	}
}

func (c *Context) BindVertexArray(array uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindVertexArray_args
		glWrapHandlerArgs.array = C.GLuint(array)

		c.push(C.gl_wrap_batch_func{
			jump_index: 154,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindVertexArray(c.c, C.GLuint(array))
	}
}

func (c *Context) DeleteVertexArrays(n uint32, arrays *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteVertexArrays_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.arrays = (*C.GLuint)(unsafe.Pointer(arrays))

		c.push(C.gl_wrap_batch_func{
			jump_index: 155,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteVertexArrays(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(arrays)))
	}
}

func (c *Context) GenVertexArrays(n uint32, arrays *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenVertexArrays_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.arrays = (*C.GLuint)(unsafe.Pointer(arrays))

		c.push(C.gl_wrap_batch_func{
			jump_index: 156,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenVertexArrays(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(arrays)))
	}
}

func (c *Context) GetIntegeri_v(target int32, index uint32, data *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetIntegeri_v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.data = (*C.GLint)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 157,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetIntegeri_v(c.c, C.GLenum(target), C.GLuint(index), (*C.GLint)(unsafe.Pointer(data)))
	}
}

func (c *Context) BeginTransformFeedback(primitiveMode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBeginTransformFeedback_args
		glWrapHandlerArgs.primitiveMode = C.GLenum(primitiveMode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 158,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBeginTransformFeedback(c.c, C.GLenum(primitiveMode))
	}
}

func (c *Context) EndTransformFeedback() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEndTransformFeedback_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 159,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEndTransformFeedback(c.c)
	}
}

func (c *Context) BindBufferRange(target int32, index uint32, buffer uint32, offset uintptr, size uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindBufferRange_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)

		c.push(C.gl_wrap_batch_func{
			jump_index: 160,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindBufferRange(c.c, C.GLenum(target), C.GLuint(index), C.GLuint(buffer), C.GLintptr(offset), C.GLsizeiptr(size))
	}
}

func (c *Context) BindBufferBase(target int32, index uint32, buffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindBufferBase_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 161,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindBufferBase(c.c, C.GLenum(target), C.GLuint(index), C.GLuint(buffer))
	}
}

func (c *Context) TransformFeedbackVaryings(program uint32, count uint32, varyings **byte, bufferMode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTransformFeedbackVaryings_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.varyings = (**C.GLchar)(unsafe.Pointer(varyings))
		glWrapHandlerArgs.bufferMode = C.GLenum(bufferMode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 162,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTransformFeedbackVaryings(c.c, C.GLuint(program), C.GLsizei(count), (**C.GLchar)(unsafe.Pointer(varyings)), C.GLenum(bufferMode))
	}
}

func (c *Context) GetTransformFeedbackVarying(program uint32, index uint32, bufSize uint32, length *uint32, size *uint32, pType *int32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTransformFeedbackVarying_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.size = (*C.GLsizei)(unsafe.Pointer(size))
		glWrapHandlerArgs._type = (*C.GLenum)(unsafe.Pointer(pType))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 163,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTransformFeedbackVarying(c.c, C.GLuint(program), C.GLuint(index), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLsizei)(unsafe.Pointer(size)), (*C.GLenum)(unsafe.Pointer(pType)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) VertexAttribIPointer(index uint32, size int32, pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribIPointer_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 164,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribIPointer(c.c, C.GLuint(index), C.GLint(size), C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) GetVertexAttribIiv(index uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribIiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 165,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribIiv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribIuiv(index uint32, pname int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribIuiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 166,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribIuiv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) VertexAttribI4i(index uint32, x int32, y int32, z int32, w int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4i_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.z = C.GLint(z)
		glWrapHandlerArgs.w = C.GLint(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 167,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4i(c.c, C.GLuint(index), C.GLint(x), C.GLint(y), C.GLint(z), C.GLint(w))
	}
}

func (c *Context) VertexAttribI4ui(index uint32, x uint32, y uint32, z uint32, w uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLuint(x)
		glWrapHandlerArgs.y = C.GLuint(y)
		glWrapHandlerArgs.z = C.GLuint(z)
		glWrapHandlerArgs.w = C.GLuint(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 168,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4ui(c.c, C.GLuint(index), C.GLuint(x), C.GLuint(y), C.GLuint(z), C.GLuint(w))
	}
}

func (c *Context) VertexAttribI4iv(index uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4iv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 169,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4iv(c.c, C.GLuint(index), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI4uiv(index uint32, v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 170,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4uiv(c.c, C.GLuint(index), (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) GetUniformuiv(program uint32, location int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformuiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 171,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformuiv(c.c, C.GLuint(program), C.GLint(location), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) Uniform1ui(location int32, v0 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1ui_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 172,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1ui(c.c, C.GLint(location), C.GLuint(v0))
	}
}

func (c *Context) Uniform2ui(location int32, v0 uint32, v1 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2ui_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 173,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2ui(c.c, C.GLint(location), C.GLuint(v0), C.GLuint(v1))
	}
}

func (c *Context) Uniform3ui(location int32, v0 uint32, v1 uint32, v2 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3ui_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)
		glWrapHandlerArgs.v2 = C.GLuint(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 174,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3ui(c.c, C.GLint(location), C.GLuint(v0), C.GLuint(v1), C.GLuint(v2))
	}
}

func (c *Context) Uniform4ui(location int32, v0 uint32, v1 uint32, v2 uint32, v3 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4ui_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)
		glWrapHandlerArgs.v2 = C.GLuint(v2)
		glWrapHandlerArgs.v3 = C.GLuint(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 175,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4ui(c.c, C.GLint(location), C.GLuint(v0), C.GLuint(v1), C.GLuint(v2), C.GLuint(v3))
	}
}

func (c *Context) Uniform1uiv(location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1uiv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 176,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1uiv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform2uiv(location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2uiv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 177,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2uiv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform3uiv(location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3uiv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 178,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3uiv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform4uiv(location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4uiv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 179,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4uiv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ClearBufferiv(buffer int32, drawbuffer int32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferiv_args
		glWrapHandlerArgs.buffer = C.GLenum(buffer)
		glWrapHandlerArgs.drawbuffer = C.GLint(drawbuffer)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 180,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferiv(c.c, C.GLenum(buffer), C.GLint(drawbuffer), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ClearBufferuiv(buffer int32, drawbuffer int32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferuiv_args
		glWrapHandlerArgs.buffer = C.GLenum(buffer)
		glWrapHandlerArgs.drawbuffer = C.GLint(drawbuffer)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 181,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferuiv(c.c, C.GLenum(buffer), C.GLint(drawbuffer), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ClearBufferfv(buffer int32, drawbuffer int32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferfv_args
		glWrapHandlerArgs.buffer = C.GLenum(buffer)
		glWrapHandlerArgs.drawbuffer = C.GLint(drawbuffer)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 182,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferfv(c.c, C.GLenum(buffer), C.GLint(drawbuffer), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ClearBufferfi(buffer int32, drawbuffer int32, depth float32, stencil int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferfi_args
		glWrapHandlerArgs.buffer = C.GLenum(buffer)
		glWrapHandlerArgs.drawbuffer = C.GLint(drawbuffer)
		glWrapHandlerArgs.depth = C.GLfloat(depth)
		glWrapHandlerArgs.stencil = C.GLint(stencil)

		c.push(C.gl_wrap_batch_func{
			jump_index: 183,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferfi(c.c, C.GLenum(buffer), C.GLint(drawbuffer), C.GLfloat(depth), C.GLint(stencil))
	}
}

func (c *Context) CopyBufferSubData(readTarget int32, writeTarget int32, readOffset uintptr, writeOffset uintptr, size uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyBufferSubData_args
		glWrapHandlerArgs.readTarget = C.GLenum(readTarget)
		glWrapHandlerArgs.writeTarget = C.GLenum(writeTarget)
		glWrapHandlerArgs.readOffset = C.GLintptr(readOffset)
		glWrapHandlerArgs.writeOffset = C.GLintptr(writeOffset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)

		c.push(C.gl_wrap_batch_func{
			jump_index: 184,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyBufferSubData(c.c, C.GLenum(readTarget), C.GLenum(writeTarget), C.GLintptr(readOffset), C.GLintptr(writeOffset), C.GLsizeiptr(size))
	}
}

func (c *Context) GetUniformIndices(program uint32, uniformCount uint32, uniformNames **byte, uniformIndices *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformIndices_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformCount = C.GLsizei(uniformCount)
		glWrapHandlerArgs.uniformNames = (**C.GLchar)(unsafe.Pointer(uniformNames))
		glWrapHandlerArgs.uniformIndices = (*C.GLuint)(unsafe.Pointer(uniformIndices))

		c.push(C.gl_wrap_batch_func{
			jump_index: 185,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformIndices(c.c, C.GLuint(program), C.GLsizei(uniformCount), (**C.GLchar)(unsafe.Pointer(uniformNames)), (*C.GLuint)(unsafe.Pointer(uniformIndices)))
	}
}

func (c *Context) GetActiveUniformsiv(program uint32, uniformCount uint32, uniformIndices *uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniformsiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformCount = C.GLsizei(uniformCount)
		glWrapHandlerArgs.uniformIndices = (*C.GLuint)(unsafe.Pointer(uniformIndices))
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 186,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniformsiv(c.c, C.GLuint(program), C.GLsizei(uniformCount), (*C.GLuint)(unsafe.Pointer(uniformIndices)), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetActiveUniformBlockiv(program uint32, uniformBlockIndex uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniformBlockiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformBlockIndex = C.GLuint(uniformBlockIndex)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 187,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniformBlockiv(c.c, C.GLuint(program), C.GLuint(uniformBlockIndex), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetActiveUniformBlockName(program uint32, uniformBlockIndex uint32, bufSize uint32, length *uint32, uniformBlockName *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniformBlockName_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformBlockIndex = C.GLuint(uniformBlockIndex)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.uniformBlockName = (*C.GLchar)(unsafe.Pointer(uniformBlockName))

		c.push(C.gl_wrap_batch_func{
			jump_index: 188,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniformBlockName(c.c, C.GLuint(program), C.GLuint(uniformBlockIndex), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(uniformBlockName)))
	}
}

func (c *Context) UniformBlockBinding(program uint32, uniformBlockIndex uint32, uniformBlockBinding uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformBlockBinding_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformBlockIndex = C.GLuint(uniformBlockIndex)
		glWrapHandlerArgs.uniformBlockBinding = C.GLuint(uniformBlockBinding)

		c.push(C.gl_wrap_batch_func{
			jump_index: 189,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformBlockBinding(c.c, C.GLuint(program), C.GLuint(uniformBlockIndex), C.GLuint(uniformBlockBinding))
	}
}

func (c *Context) DrawArraysInstanced(mode int32, first int32, count uint32, instancecount uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawArraysInstanced_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.first = C.GLint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)

		c.push(C.gl_wrap_batch_func{
			jump_index: 190,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawArraysInstanced(c.c, C.GLenum(mode), C.GLint(first), C.GLsizei(count), C.GLsizei(instancecount))
	}
}

func (c *Context) DrawElementsInstanced(mode int32, count uint32, pType int32, indices unsafe.Pointer, instancecount uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElementsInstanced_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)

		c.push(C.gl_wrap_batch_func{
			jump_index: 191,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElementsInstanced(c.c, C.GLenum(mode), C.GLsizei(count), C.GLenum(pType), indices, C.GLsizei(instancecount))
	}
}

func (c *Context) DeleteSync(sync Sync) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteSync_args
		glWrapHandlerArgs.sync = C.GLsync(sync)

		c.push(C.gl_wrap_batch_func{
			jump_index: 192,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteSync(c.c, C.GLsync(sync))
	}
}

func (c *Context) WaitSync(sync Sync, flags uint32, timeout uint64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWaitSync_args
		glWrapHandlerArgs.sync = C.GLsync(sync)
		glWrapHandlerArgs.flags = C.GLbitfield(flags)
		glWrapHandlerArgs.timeout = C.GLuint64(timeout)

		c.push(C.gl_wrap_batch_func{
			jump_index: 193,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWaitSync(c.c, C.GLsync(sync), C.GLbitfield(flags), C.GLuint64(timeout))
	}
}

func (c *Context) GetInteger64v(pname int32, data *int64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetInteger64v_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLint64)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 194,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetInteger64v(c.c, C.GLenum(pname), (*C.GLint64)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetSynciv(sync Sync, pname int32, bufSize uint32, length *uint32, values *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetSynciv_args
		glWrapHandlerArgs.sync = C.GLsync(sync)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.values = (*C.GLint)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 195,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetSynciv(c.c, C.GLsync(sync), C.GLenum(pname), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLint)(unsafe.Pointer(values)))
	}
}

func (c *Context) GetInteger64i_v(target int32, index uint32, data *int64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetInteger64i_v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.data = (*C.GLint64)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 196,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetInteger64i_v(c.c, C.GLenum(target), C.GLuint(index), (*C.GLint64)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetBufferParameteri64v(target int32, pname int32, params *int64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBufferParameteri64v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint64)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 197,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBufferParameteri64v(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint64)(unsafe.Pointer(params)))
	}
}

func (c *Context) GenSamplers(count uint32, samplers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenSamplers_args
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.samplers = (*C.GLuint)(unsafe.Pointer(samplers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 198,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenSamplers(c.c, C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(samplers)))
	}
}

func (c *Context) DeleteSamplers(count uint32, samplers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteSamplers_args
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.samplers = (*C.GLuint)(unsafe.Pointer(samplers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 199,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteSamplers(c.c, C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(samplers)))
	}
}

func (c *Context) BindSampler(unit uint32, sampler uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindSampler_args
		glWrapHandlerArgs.unit = C.GLuint(unit)
		glWrapHandlerArgs.sampler = C.GLuint(sampler)

		c.push(C.gl_wrap_batch_func{
			jump_index: 200,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindSampler(c.c, C.GLuint(unit), C.GLuint(sampler))
	}
}

func (c *Context) SamplerParameteri(sampler uint32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameteri_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 201,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameteri(c.c, C.GLuint(sampler), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) SamplerParameteriv(sampler uint32, pname int32, param *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameteriv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = (*C.GLint)(unsafe.Pointer(param))

		c.push(C.gl_wrap_batch_func{
			jump_index: 202,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameteriv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(param)))
	}
}

func (c *Context) SamplerParameterf(sampler uint32, pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameterf_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 203,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameterf(c.c, C.GLuint(sampler), C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) SamplerParameterfv(sampler uint32, pname int32, param *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameterfv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = (*C.GLfloat)(unsafe.Pointer(param))

		c.push(C.gl_wrap_batch_func{
			jump_index: 204,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameterfv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(param)))
	}
}

func (c *Context) GetSamplerParameteriv(sampler uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetSamplerParameteriv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 205,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetSamplerParameteriv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetSamplerParameterfv(sampler uint32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetSamplerParameterfv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 206,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetSamplerParameterfv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) VertexAttribDivisor(index uint32, divisor uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribDivisor_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.divisor = C.GLuint(divisor)

		c.push(C.gl_wrap_batch_func{
			jump_index: 207,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribDivisor(c.c, C.GLuint(index), C.GLuint(divisor))
	}
}

func (c *Context) BindTransformFeedback(target int32, id uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindTransformFeedback_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.id = C.GLuint(id)

		c.push(C.gl_wrap_batch_func{
			jump_index: 208,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindTransformFeedback(c.c, C.GLenum(target), C.GLuint(id))
	}
}

func (c *Context) DeleteTransformFeedbacks(n uint32, ids *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteTransformFeedbacks_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))

		c.push(C.gl_wrap_batch_func{
			jump_index: 209,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteTransformFeedbacks(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(ids)))
	}
}

func (c *Context) GenTransformFeedbacks(n uint32, ids *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenTransformFeedbacks_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))

		c.push(C.gl_wrap_batch_func{
			jump_index: 210,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenTransformFeedbacks(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(ids)))
	}
}

func (c *Context) PauseTransformFeedback() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPauseTransformFeedback_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 211,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPauseTransformFeedback(c.c)
	}
}

func (c *Context) ResumeTransformFeedback() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glResumeTransformFeedback_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 212,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glResumeTransformFeedback(c.c)
	}
}

func (c *Context) GetProgramBinary(program uint32, bufSize uint32, length *uint32, binaryFormat *int32, binary unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramBinary_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.binaryFormat = (*C.GLenum)(unsafe.Pointer(binaryFormat))
		glWrapHandlerArgs.binary = binary

		c.push(C.gl_wrap_batch_func{
			jump_index: 213,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramBinary(c.c, C.GLuint(program), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLenum)(unsafe.Pointer(binaryFormat)), binary)
	}
}

func (c *Context) ProgramBinary(program uint32, binaryFormat int32, binary unsafe.Pointer, length uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramBinary_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.binaryFormat = C.GLenum(binaryFormat)
		glWrapHandlerArgs.binary = binary
		glWrapHandlerArgs.length = C.GLsizei(length)

		c.push(C.gl_wrap_batch_func{
			jump_index: 214,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramBinary(c.c, C.GLuint(program), C.GLenum(binaryFormat), binary, C.GLsizei(length))
	}
}

func (c *Context) ProgramParameteri(program uint32, pname int32, value int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramParameteri_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.value = C.GLint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 215,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramParameteri(c.c, C.GLuint(program), C.GLenum(pname), C.GLint(value))
	}
}

func (c *Context) InvalidateFramebuffer(target int32, numAttachments uint32, attachments *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInvalidateFramebuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.numAttachments = C.GLsizei(numAttachments)
		glWrapHandlerArgs.attachments = (*C.GLenum)(unsafe.Pointer(attachments))

		c.push(C.gl_wrap_batch_func{
			jump_index: 216,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInvalidateFramebuffer(c.c, C.GLenum(target), C.GLsizei(numAttachments), (*C.GLenum)(unsafe.Pointer(attachments)))
	}
}

func (c *Context) InvalidateSubFramebuffer(target int32, numAttachments uint32, attachments *int32, x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInvalidateSubFramebuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.numAttachments = C.GLsizei(numAttachments)
		glWrapHandlerArgs.attachments = (*C.GLenum)(unsafe.Pointer(attachments))
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 217,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInvalidateSubFramebuffer(c.c, C.GLenum(target), C.GLsizei(numAttachments), (*C.GLenum)(unsafe.Pointer(attachments)), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) TexStorage2D(target int32, levels uint32, internalformat int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexStorage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.levels = C.GLsizei(levels)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 218,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexStorage2D(c.c, C.GLenum(target), C.GLsizei(levels), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) TexStorage3D(target int32, levels uint32, internalformat int32, width uint32, height uint32, depth uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexStorage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.levels = C.GLsizei(levels)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)

		c.push(C.gl_wrap_batch_func{
			jump_index: 219,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexStorage3D(c.c, C.GLenum(target), C.GLsizei(levels), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth))
	}
}

func (c *Context) GetInternalformativ(target int32, internalformat int32, pname int32, bufSize uint32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetInternalformativ_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 220,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetInternalformativ(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLenum(pname), C.GLsizei(bufSize), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) DispatchCompute(num_groups_x uint32, num_groups_y uint32, num_groups_z uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDispatchCompute_args
		glWrapHandlerArgs.num_groups_x = C.GLuint(num_groups_x)
		glWrapHandlerArgs.num_groups_y = C.GLuint(num_groups_y)
		glWrapHandlerArgs.num_groups_z = C.GLuint(num_groups_z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 221,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDispatchCompute(c.c, C.GLuint(num_groups_x), C.GLuint(num_groups_y), C.GLuint(num_groups_z))
	}
}

func (c *Context) DispatchComputeIndirect(indirect uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDispatchComputeIndirect_args
		glWrapHandlerArgs.indirect = C.GLintptr(indirect)

		c.push(C.gl_wrap_batch_func{
			jump_index: 222,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDispatchComputeIndirect(c.c, C.GLintptr(indirect))
	}
}

func (c *Context) DrawArraysIndirect(mode int32, indirect unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawArraysIndirect_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.indirect = indirect

		c.push(C.gl_wrap_batch_func{
			jump_index: 223,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawArraysIndirect(c.c, C.GLenum(mode), indirect)
	}
}

func (c *Context) DrawElementsIndirect(mode int32, pType int32, indirect unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElementsIndirect_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indirect = indirect

		c.push(C.gl_wrap_batch_func{
			jump_index: 224,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElementsIndirect(c.c, C.GLenum(mode), C.GLenum(pType), indirect)
	}
}

func (c *Context) FramebufferParameteri(target int32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferParameteri_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 225,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferParameteri(c.c, C.GLenum(target), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) GetFramebufferParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetFramebufferParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 226,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetFramebufferParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetProgramInterfaceiv(program uint32, programInterface int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramInterfaceiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.programInterface = C.GLenum(programInterface)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 227,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramInterfaceiv(c.c, C.GLuint(program), C.GLenum(programInterface), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetProgramResourceName(program uint32, programInterface int32, index uint32, bufSize uint32, length *uint32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramResourceName_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.programInterface = C.GLenum(programInterface)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 228,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramResourceName(c.c, C.GLuint(program), C.GLenum(programInterface), C.GLuint(index), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) GetProgramResourceiv(program uint32, programInterface int32, index uint32, propCount uint32, props *int32, bufSize uint32, length *uint32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramResourceiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.programInterface = C.GLenum(programInterface)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.propCount = C.GLsizei(propCount)
		glWrapHandlerArgs.props = (*C.GLenum)(unsafe.Pointer(props))
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 229,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramResourceiv(c.c, C.GLuint(program), C.GLenum(programInterface), C.GLuint(index), C.GLsizei(propCount), (*C.GLenum)(unsafe.Pointer(props)), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) UseProgramStages(pipeline uint32, stages uint32, program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUseProgramStages_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)
		glWrapHandlerArgs.stages = C.GLbitfield(stages)
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 230,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUseProgramStages(c.c, C.GLuint(pipeline), C.GLbitfield(stages), C.GLuint(program))
	}
}

func (c *Context) ActiveShaderProgram(pipeline uint32, program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glActiveShaderProgram_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 231,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glActiveShaderProgram(c.c, C.GLuint(pipeline), C.GLuint(program))
	}
}

func (c *Context) BindProgramPipeline(pipeline uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindProgramPipeline_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)

		c.push(C.gl_wrap_batch_func{
			jump_index: 232,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindProgramPipeline(c.c, C.GLuint(pipeline))
	}
}

func (c *Context) DeleteProgramPipelines(n uint32, pipelines *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteProgramPipelines_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.pipelines = (*C.GLuint)(unsafe.Pointer(pipelines))

		c.push(C.gl_wrap_batch_func{
			jump_index: 233,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteProgramPipelines(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(pipelines)))
	}
}

func (c *Context) GenProgramPipelines(n uint32, pipelines *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenProgramPipelines_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.pipelines = (*C.GLuint)(unsafe.Pointer(pipelines))

		c.push(C.gl_wrap_batch_func{
			jump_index: 234,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenProgramPipelines(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(pipelines)))
	}
}

func (c *Context) GetProgramPipelineiv(pipeline uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramPipelineiv_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 235,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramPipelineiv(c.c, C.GLuint(pipeline), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) ProgramUniform1i(program uint32, location int32, v0 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1i_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 236,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1i(c.c, C.GLuint(program), C.GLint(location), C.GLint(v0))
	}
}

func (c *Context) ProgramUniform2i(program uint32, location int32, v0 int32, v1 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2i_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 237,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2i(c.c, C.GLuint(program), C.GLint(location), C.GLint(v0), C.GLint(v1))
	}
}

func (c *Context) ProgramUniform3i(program uint32, location int32, v0 int32, v1 int32, v2 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3i_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)
		glWrapHandlerArgs.v2 = C.GLint(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 238,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3i(c.c, C.GLuint(program), C.GLint(location), C.GLint(v0), C.GLint(v1), C.GLint(v2))
	}
}

func (c *Context) ProgramUniform4i(program uint32, location int32, v0 int32, v1 int32, v2 int32, v3 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4i_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)
		glWrapHandlerArgs.v2 = C.GLint(v2)
		glWrapHandlerArgs.v3 = C.GLint(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 239,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4i(c.c, C.GLuint(program), C.GLint(location), C.GLint(v0), C.GLint(v1), C.GLint(v2), C.GLint(v3))
	}
}

func (c *Context) ProgramUniform1ui(program uint32, location int32, v0 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1ui_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 240,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1ui(c.c, C.GLuint(program), C.GLint(location), C.GLuint(v0))
	}
}

func (c *Context) ProgramUniform2ui(program uint32, location int32, v0 uint32, v1 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2ui_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 241,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2ui(c.c, C.GLuint(program), C.GLint(location), C.GLuint(v0), C.GLuint(v1))
	}
}

func (c *Context) ProgramUniform3ui(program uint32, location int32, v0 uint32, v1 uint32, v2 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3ui_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)
		glWrapHandlerArgs.v2 = C.GLuint(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 242,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3ui(c.c, C.GLuint(program), C.GLint(location), C.GLuint(v0), C.GLuint(v1), C.GLuint(v2))
	}
}

func (c *Context) ProgramUniform4ui(program uint32, location int32, v0 uint32, v1 uint32, v2 uint32, v3 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4ui_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)
		glWrapHandlerArgs.v2 = C.GLuint(v2)
		glWrapHandlerArgs.v3 = C.GLuint(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 243,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4ui(c.c, C.GLuint(program), C.GLint(location), C.GLuint(v0), C.GLuint(v1), C.GLuint(v2), C.GLuint(v3))
	}
}

func (c *Context) ProgramUniform1f(program uint32, location int32, v0 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1f_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 244,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1f(c.c, C.GLuint(program), C.GLint(location), C.GLfloat(v0))
	}
}

func (c *Context) ProgramUniform2f(program uint32, location int32, v0 float32, v1 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2f_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 245,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2f(c.c, C.GLuint(program), C.GLint(location), C.GLfloat(v0), C.GLfloat(v1))
	}
}

func (c *Context) ProgramUniform3f(program uint32, location int32, v0 float32, v1 float32, v2 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3f_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 246,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3f(c.c, C.GLuint(program), C.GLint(location), C.GLfloat(v0), C.GLfloat(v1), C.GLfloat(v2))
	}
}

func (c *Context) ProgramUniform4f(program uint32, location int32, v0 float32, v1 float32, v2 float32, v3 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4f_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)
		glWrapHandlerArgs.v3 = C.GLfloat(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 247,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4f(c.c, C.GLuint(program), C.GLint(location), C.GLfloat(v0), C.GLfloat(v1), C.GLfloat(v2), C.GLfloat(v3))
	}
}

func (c *Context) ProgramUniform1iv(program uint32, location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1iv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 248,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1iv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform2iv(program uint32, location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2iv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 249,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2iv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform3iv(program uint32, location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3iv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 250,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3iv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform4iv(program uint32, location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4iv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 251,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4iv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform1uiv(program uint32, location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1uiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 252,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1uiv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform2uiv(program uint32, location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2uiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 253,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2uiv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform3uiv(program uint32, location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3uiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 254,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3uiv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform4uiv(program uint32, location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4uiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 255,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4uiv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform1fv(program uint32, location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 256,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform2fv(program uint32, location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 257,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform3fv(program uint32, location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 258,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform4fv(program uint32, location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 259,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 260,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 261,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 262,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2x3fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2x3fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 263,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2x3fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3x2fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3x2fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 264,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3x2fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2x4fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2x4fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 265,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2x4fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4x2fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4x2fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 266,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4x2fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3x4fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3x4fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 267,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3x4fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4x3fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4x3fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 268,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4x3fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ValidateProgramPipeline(pipeline uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glValidateProgramPipeline_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)

		c.push(C.gl_wrap_batch_func{
			jump_index: 269,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glValidateProgramPipeline(c.c, C.GLuint(pipeline))
	}
}

func (c *Context) GetProgramPipelineInfoLog(pipeline uint32, bufSize uint32, length *uint32, infoLog *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramPipelineInfoLog_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.infoLog = (*C.GLchar)(unsafe.Pointer(infoLog))

		c.push(C.gl_wrap_batch_func{
			jump_index: 270,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramPipelineInfoLog(c.c, C.GLuint(pipeline), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(infoLog)))
	}
}

func (c *Context) BindImageTexture(unit uint32, texture uint32, level int32, layered uint8, layer int32, access int32, format int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindImageTexture_args
		glWrapHandlerArgs.unit = C.GLuint(unit)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.layered = C.GLboolean(layered)
		glWrapHandlerArgs.layer = C.GLint(layer)
		glWrapHandlerArgs.access = C.GLenum(access)
		glWrapHandlerArgs.format = C.GLenum(format)

		c.push(C.gl_wrap_batch_func{
			jump_index: 271,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindImageTexture(c.c, C.GLuint(unit), C.GLuint(texture), C.GLint(level), C.GLboolean(layered), C.GLint(layer), C.GLenum(access), C.GLenum(format))
	}
}

func (c *Context) GetBooleani_v(target int32, index uint32, data *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBooleani_v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.data = (*C.GLboolean)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 272,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBooleani_v(c.c, C.GLenum(target), C.GLuint(index), (*C.GLboolean)(unsafe.Pointer(data)))
	}
}

func (c *Context) MemoryBarrier(barriers uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMemoryBarrier_args
		glWrapHandlerArgs.barriers = C.GLbitfield(barriers)

		c.push(C.gl_wrap_batch_func{
			jump_index: 273,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMemoryBarrier(c.c, C.GLbitfield(barriers))
	}
}

func (c *Context) MemoryBarrierByRegion(barriers uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMemoryBarrierByRegion_args
		glWrapHandlerArgs.barriers = C.GLbitfield(barriers)

		c.push(C.gl_wrap_batch_func{
			jump_index: 274,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMemoryBarrierByRegion(c.c, C.GLbitfield(barriers))
	}
}

func (c *Context) TexStorage2DMultisample(target int32, samples uint32, internalformat int32, width uint32, height uint32, fixedsamplelocations uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexStorage2DMultisample_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.samples = C.GLsizei(samples)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.fixedsamplelocations = C.GLboolean(fixedsamplelocations)

		c.push(C.gl_wrap_batch_func{
			jump_index: 275,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexStorage2DMultisample(c.c, C.GLenum(target), C.GLsizei(samples), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLboolean(fixedsamplelocations))
	}
}

func (c *Context) GetMultisamplefv(pname int32, index uint32, val *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetMultisamplefv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.val = (*C.GLfloat)(unsafe.Pointer(val))

		c.push(C.gl_wrap_batch_func{
			jump_index: 276,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetMultisamplefv(c.c, C.GLenum(pname), C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(val)))
	}
}

func (c *Context) SampleMaski(maskNumber uint32, mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSampleMaski_args
		glWrapHandlerArgs.maskNumber = C.GLuint(maskNumber)
		glWrapHandlerArgs.mask = C.GLbitfield(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 277,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSampleMaski(c.c, C.GLuint(maskNumber), C.GLbitfield(mask))
	}
}

func (c *Context) GetTexLevelParameteriv(target int32, level int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexLevelParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 278,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexLevelParameteriv(c.c, C.GLenum(target), C.GLint(level), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexLevelParameterfv(target int32, level int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexLevelParameterfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 279,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexLevelParameterfv(c.c, C.GLenum(target), C.GLint(level), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) BindVertexBuffer(bindingindex uint32, buffer uint32, offset uintptr, stride uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindVertexBuffer_args
		glWrapHandlerArgs.bindingindex = C.GLuint(bindingindex)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.stride = C.GLsizei(stride)

		c.push(C.gl_wrap_batch_func{
			jump_index: 280,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindVertexBuffer(c.c, C.GLuint(bindingindex), C.GLuint(buffer), C.GLintptr(offset), C.GLsizei(stride))
	}
}

func (c *Context) VertexAttribFormat(attribindex uint32, size int32, pType int32, normalized uint8, relativeoffset uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribFormat_args
		glWrapHandlerArgs.attribindex = C.GLuint(attribindex)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.relativeoffset = C.GLuint(relativeoffset)

		c.push(C.gl_wrap_batch_func{
			jump_index: 281,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribFormat(c.c, C.GLuint(attribindex), C.GLint(size), C.GLenum(pType), C.GLboolean(normalized), C.GLuint(relativeoffset))
	}
}

func (c *Context) VertexAttribIFormat(attribindex uint32, size int32, pType int32, relativeoffset uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribIFormat_args
		glWrapHandlerArgs.attribindex = C.GLuint(attribindex)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.relativeoffset = C.GLuint(relativeoffset)

		c.push(C.gl_wrap_batch_func{
			jump_index: 282,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribIFormat(c.c, C.GLuint(attribindex), C.GLint(size), C.GLenum(pType), C.GLuint(relativeoffset))
	}
}

func (c *Context) VertexAttribBinding(attribindex uint32, bindingindex uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribBinding_args
		glWrapHandlerArgs.attribindex = C.GLuint(attribindex)
		glWrapHandlerArgs.bindingindex = C.GLuint(bindingindex)

		c.push(C.gl_wrap_batch_func{
			jump_index: 283,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribBinding(c.c, C.GLuint(attribindex), C.GLuint(bindingindex))
	}
}

func (c *Context) VertexBindingDivisor(bindingindex uint32, divisor uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexBindingDivisor_args
		glWrapHandlerArgs.bindingindex = C.GLuint(bindingindex)
		glWrapHandlerArgs.divisor = C.GLuint(divisor)

		c.push(C.gl_wrap_batch_func{
			jump_index: 284,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexBindingDivisor(c.c, C.GLuint(bindingindex), C.GLuint(divisor))
	}
}
