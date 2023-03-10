/*
 * Copyright (c) 2012, 2022, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#ifndef _Prism_es2_defs_h_
#define _Prism_es2_defs_h_

#if defined(SOLARIS) || defined(LINUX) || defined(ANDROID_NDK) /* SOLARIS || LINUX */
#define GLX_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES
#define UNIX
#if defined(IS_EGLX11) || defined(IS_EGLFB)
#define IS_EGL
#else
#define IS_GLX
#endif

#include <limits.h>

#ifndef ANDROID_NDK
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#endif

#include <GL/gl.h>
#include <GL/glext.h>

#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <dlfcn.h>

#define jlong_to_ptr(value) ((void*)((long)value))
#define ptr_to_jlong(value) (jlong)((long)(value))

/* Max lenght of value, attr pair plus a None */
#define  MAX_GLX_ATTRS_LENGTH 50

#ifdef IS_EGL
#include <EGL/egl.h>
#include "eglWrapper/eglWrapper.h"
#endif

#endif /* SOLARIS || LINUX */

#ifdef __APPLE__
#include <TargetConditionals.h>

#define jlong_to_ptr(value) (intptr_t)(value)
#define ptr_to_jlong(value) (jlong)((intptr_t)(value))

#if TARGET_OS_IPHONE /* iOS */
#include <GL/gl.h>
#include <GL/glext.h>
#include "ios/ios-window-system.h"
#define IS_EGL

#elif TARGET_OS_MAC /* MacOSX */
/* Include the OpenGL headers */
#include <GL/gl.h>
#include <GL/glext.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/CGLTypes.h>
#include "macosx-window-system.h"

/* Max length of value, attr pair plus a None */
#define MAX_PF_ATTRS_LENGTH 50
#endif /* MacOSX */
#endif /* __APPLE__ */

#ifdef WIN32 /* WIN32 */
#include <windows.h>
#include <GL/gl.h>
#include <GL/wglext.h>
#include <GL/glext.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#ifndef _WIN64
typedef int intptr_t;
#endif

#define jlong_to_ptr(value) (intptr_t)(value)
#define ptr_to_jlong(value) (jlong)((intptr_t)(value))
#endif /* WIN32 */

/* platform independent .h files generated by javah */
#include "com_sun_prism_es2_GLContext.h"
#include "com_sun_prism_es2_GLFactory.h"
#include "com_sun_prism_es2_GLPixelFormat_Attributes.h"

/*
 * These match the constants in GLPixelFormat
 */
#define RED_SIZE        com_sun_prism_es2_GLPixelFormat_Attributes_RED_SIZE
#define GREEN_SIZE      com_sun_prism_es2_GLPixelFormat_Attributes_GREEN_SIZE
#define BLUE_SIZE       com_sun_prism_es2_GLPixelFormat_Attributes_BLUE_SIZE
#define ALPHA_SIZE      com_sun_prism_es2_GLPixelFormat_Attributes_ALPHA_SIZE
#define DEPTH_SIZE      com_sun_prism_es2_GLPixelFormat_Attributes_DEPTH_SIZE
#define DOUBLEBUFFER    com_sun_prism_es2_GLPixelFormat_Attributes_DOUBLEBUFFER
#define ONSCREEN        com_sun_prism_es2_GLPixelFormat_Attributes_ONSCREEN
#define NUM_ITEMS       com_sun_prism_es2_GLPixelFormat_Attributes_NUM_ITEMS

#ifdef ANDROID_NDK

#include "com_sun_prism_es2_GLPixelFormat_Attributes.h"

typedef EGLNativeDisplayType Display;
typedef EGLNativeWindowType  Window;
typedef EGLConfig            GLXFBConfig;
typedef unsigned long        Colormap;
typedef unsigned long        PFNGLXSWAPINTERVALSGIPROC;

#include <android/log.h>
#include <string.h>
#define TAG "javafx"
#define printf(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define fprintf(IGNORE, ...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))
#endif

/* Typedef for pixelformat properties struct */
typedef struct PixelFormatInfoRec PixelFormatInfo;

/* define the structure to hold the resources and proerties of pixelformat */
struct PixelFormatInfoRec {
#ifdef WIN32 /* WIN32 */
    int pixelFormat;
    HWND dummyHwnd;
    HDC dummyHdc;
    LPCTSTR dummySzAppName;
#endif /* WIN32 */

#ifdef UNIX /* LINUX || SOLARIS */
    Display *display;
    GLXFBConfig fbConfig;
    Window dummyWin;
    Colormap dummyCmap;
#endif

#ifdef MACOSX /* MACOSX */
    jlong pixelFormat;
#endif
};

/* Typedef for drawable properties struct */
typedef struct DrawableInfoRec DrawableInfo;

/* define the structure to hold the resources and proerties of drawable */
struct DrawableInfoRec {
    jboolean onScreen;

#ifdef WIN32 /* WIN32 */
    HDC hdc;
    HWND hwnd;
#endif /* WIN32 */

#ifdef UNIX /* LINUX || SOLARIS */
#ifdef IS_EGL
    EGLDisplay *egldisplay;
    EGLSurface eglsurface;
#endif
#ifndef IS_EGLFB
    Display *display;
    Window win;
#endif
#endif

#ifdef __APPLE__
    jlong win;
#endif /* __APPLE__ */
};

/* Typedef for state properties struct */
typedef struct StateInfoRec StateInfo;

/* define the structure to hold the states of context */
struct StateInfoRec {
    /* For state caching */
    jboolean depthWritesEnabled;
    jboolean scissorEnabled;
    GLclampf clearColor[4];
    jboolean vSyncEnabled;

    /* For 3d state caching */
    GLboolean cullEnable;
    GLenum cullMode;
    GLenum fillMode;

    /* Currently bound fbo */
    GLuint fbo;
};

/* Typedef for context properties struct */
typedef struct ContextInfoRec ContextInfo;

/* define the structure to hold the properties of graphics context */
struct ContextInfoRec {
#ifdef WIN32 /* WIN32 */
    HGLRC hglrc;
#endif /* WIN32 */

#ifdef UNIX /* LINUX || SOLARIS */
    Display *display;
#ifdef IS_EGL
    EGLContext context;
    EGLDisplay *egldisplay;
    EGLSurface eglsurface;
#else
     GLXContext context;
#endif

#if defined(IS_GLX) || defined( IS_EGLX11)
    /*
     * display screen and visualID are cached
     * for Factory to pass to Glass
     */
    int screen;
    int visualID;
#endif
#endif

#ifdef __APPLE__
    jlong context;
#endif /* __APPLE__ */

    /* version and extension info */
    char *versionStr;
    char *vendorStr;
    char *rendererStr;
    char *glExtensionStr;
    int versionNumbers[2];

    /* platform specific extension string and function pointers */
#ifdef WIN32 /* WIN32 */
    char *wglExtensionStr;
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
#endif /* WIN32 */

#ifdef UNIX /* LINUX || SOLARIS */
    char *glxExtensionStr;
    PFNGLXSWAPINTERVALSGIPROC glXSwapIntervalSGI;
#endif /* LINUX || SOLARIS */

    /* gl function pointers */
    PFNGLACTIVETEXTUREPROC glActiveTexture;
    PFNGLATTACHSHADERPROC glAttachShader;
    PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
    PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
    PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
    PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
    PFNGLCOMPILESHADERPROC glCompileShader;
    PFNGLCREATEPROGRAMPROC glCreateProgram;
    PFNGLCREATESHADERPROC glCreateShader;
    PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
    PFNGLDELETEPROGRAMPROC glDeleteProgram;
    PFNGLDELETESHADERPROC glDeleteShader;
    PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
    PFNGLDETACHSHADERPROC glDetachShader;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
    PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
    PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
    PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
    PFNGLGETPROGRAMIVPROC glGetProgramiv;
    PFNGLGETSHADERIVPROC glGetShaderiv;
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    PFNGLLINKPROGRAMPROC glLinkProgram;
    PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
    PFNGLSHADERSOURCEPROC glShaderSource;
    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    PFNGLBUFFERSUBDATAPROC glBufferSubData;
    PFNGLUNIFORM1FPROC glUniform1f;
    PFNGLUNIFORM2FPROC glUniform2f;
    PFNGLUNIFORM3FPROC glUniform3f;
    PFNGLUNIFORM4FPROC glUniform4f;
    PFNGLUNIFORM4FVPROC glUniform4fv;
    PFNGLUNIFORM1IPROC glUniform1i;
    PFNGLUNIFORM2IPROC glUniform2i;
    PFNGLUNIFORM3IPROC glUniform3i;
    PFNGLUNIFORM4IPROC glUniform4i;
    PFNGLUNIFORM4IVPROC glUniform4iv;
    PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
    PFNGLUSEPROGRAMPROC glUseProgram;
    PFNGLVALIDATEPROGRAMPROC glValidateProgram;
    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

    PFNGLGENBUFFERSPROC glGenBuffers;
    PFNGLBINDBUFFERPROC glBindBuffer;
    PFNGLBUFFERDATAPROC glBufferData;
    PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;
    PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;
    PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;

    /* For state caching */
    StateInfo state;

    /* this pointers represent cached values of glVertexAttribPointer values */
    /* they should be properly updated in case of glVertexAttribPointer call */
    /* see setVertexAttributePointers */
    float *vbFloatData;
    char  *vbByteData;
    jboolean gl2;

    /* Caching properties passed down from Java */
    jboolean vSyncRequested;
};

// extern declarations for core functions
extern int isExtensionSupported(const char *allExtensions, const char *extension);
extern void extractVersionInfo(char *versionStr, int *numbers);
extern void initializeCtxInfo(ContextInfo *ctxInfo);
extern void initializePixelFormatInfo(PixelFormatInfo *pfInfo);
extern void initState(ContextInfo *ctxInfo);
extern void deletePixelFormatInfo(PixelFormatInfo *pfInfo);

/* Define 3D Primitive data type */
/* define constants and structures to hold the resources of 3D primitive and rendering
 * attributes */
#define VC_3D_INDEX 0
#define TC_3D_INDEX 1
#define NC_3D_INDEX 2
#define VC_3D_SIZE 3  /* x, y, z */
#define TC_3D_SIZE 2  /* tu, tv */
#define NC_3D_SIZE 4  /* nx, ny, nz, nw */
#define VERT_3D_SIZE (VC_3D_SIZE + TC_3D_SIZE + NC_3D_SIZE)
#define VERT_3D_STRIDE (sizeof(GLfloat) * VERT_3D_SIZE)

#define MESH_VERTEXBUFFER 0
#define MESH_INDEXBUFFER 1
#define MESH_MAX_BUFFERS 2

typedef struct MeshInfoRec MeshInfo;
struct MeshInfoRec {
    // vboIDArray[MESH_VERTEXBUFFER] used to store interleave points and tex. coords.
    // vboIDArray[MESH_INDEXBUFFER] used to store element indices
    GLuint vboIDArray[MESH_MAX_BUFFERS];
    GLuint indexBufferSize;
    GLenum indexBufferType;
};

typedef struct PhongMaterialInfoRec PhongMaterialInfo;
struct PhongMaterialInfoRec {
   GLfloat diffuseColor[4]; // in the order of rgba
   GLuint maps[4];
};

typedef struct MeshViewInfoRec MeshViewInfo;
struct MeshViewInfoRec {
    MeshInfo *meshInfo;
    PhongMaterialInfo *phongMaterialInfo;
    GLfloat ambientLightColor[3];
    GLuint lightIndex;
    GLfloat lightColor[3];
    GLfloat lightPosition[3];
    GLfloat lightWeight;
    GLfloat lightAttenuation[4];
    GLfloat lightMaxRange;
    GLfloat lightDir[3];
    GLfloat lightInnerAngle;
    GLfloat lightOuterAngle;
    GLfloat lightFalloff;
    GLboolean cullEnable;
    GLenum cullMode;
    GLenum fillMode;
};

/*
 * General purpose assertion macro
 */
#define PRISMES2_ASSERT(expr) \
    if (!(expr)) { \
        fprintf(stderr, \
            "\nAssertion failed in module '%s' at line %d\n", \
            __FILE__, __LINE__); \
        fprintf(stderr, "\t%s\n\n", #expr);     \
    }

#endif /* _Prism_es2_defs_h_ */
