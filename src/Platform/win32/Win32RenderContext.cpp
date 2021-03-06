/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2015-2016 OSRE ( Open Source Render Engine ) by Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------*/
#include <src/Platform/win32/Win32RenderContext.h>
#include <GL/glew.h>
#include "GL/wglew.h"


#include <osre/Common/Logger.h>
#include <osre/Platform/PlatformInterface.h>
#include <src/Platform/win32/Win32Surface.h>


#include <iostream>

namespace OSRE {
namespace Platform {

static const String Tag = "Win32RenderContext";

//-------------------------------------------------------------------------------------------------
void APIENTRY DebugLog( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar *msg, GLvoid *userParam ) {

    std::cout << "---------------------opengl-callback-start------------" << std::endl;
    std::cout << "message: " << msg << std::endl;
    std::cout << "type: ";
    switch( type ) {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "OTHER";
        break;
    }
    std::cout << std::endl;

    std::cout << "id: " << id << "severity: ";
    switch( severity ){
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "HIGH";
        break;
    }
    std::cout << std::endl;
    std::cout << "---------------------opengl-callback-end--------------" << std::endl;
    osre_info( Tag, "DebugLog" );
}

//-------------------------------------------------------------------------------------------------
Win32RenderContext::Win32RenderContext( )
: AbstractRenderContext()
, m_active( false ) {
    ::memset( m_OpenGLVersion, 0, sizeof( i32 ) * 2 );
}

//-------------------------------------------------------------------------------------------------
Win32RenderContext::~Win32RenderContext( ) {
    // empty
}

//-------------------------------------------------------------------------------------------------
bool Win32RenderContext::onCreate( AbstractSurface *pSurface )  {
    Win32Surface *pWin32Surface = reinterpret_cast< Win32Surface* >( pSurface );
    if( !pWin32Surface ) {
        osre_error( Tag, "Invalid pointer to window." );
        return false;
    }
    HDC dc = pWin32Surface->getDeviceContext();
    if( !dc ) {
        osre_error( Tag, "Invalid device context." );
        return false;
    }

    PIXELFORMATDESCRIPTOR pfd;
    ::memset( &pfd, 0, sizeof( PIXELFORMATDESCRIPTOR ) );
    pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    i32 pixelFormat = ::ChoosePixelFormat( dc, &pfd );
    if( 0 == pixelFormat ) {
        osre_error( Tag, "Invalid pixel format chosen." );
        return false;
    }

    BOOL bResult = ::SetPixelFormat( dc, pixelFormat, &pfd );
    if( FALSE == bResult ) {
        osre_error( Tag, "Cannot set pixel format." );
        return false;
    }

    HGLRC tempContext = wglCreateContext( dc );
    bResult = wglMakeCurrent( dc, tempContext );
    if( FALSE == bResult ) {
        osre_error( Tag, "Calling wglMakeCurrent failed." );
        return false;
    }

    GLenum err = glewInit();
    if( GLEW_OK != err ) {
        osre_error( Tag, "GLEW is not initialized!" );
        return false;
    }

    int attribs[] = {
        WGL_CONTEXT_FLAGS_ARB,
#ifdef _DEBUG
#   ifdef OSRE_WINDOWS
        WGL_CONTEXT_DEBUG_BIT_ARB,
#   else
        0,
#   endif
#else
        0,
#endif
        0
    };

#if _DEBUG
    if( glDebugMessageCallback ){
        std::cout << "Register OpenGL debug callback " << std::endl;
        glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
        //glDebugMessageCallback( ::OSRE::Platform::DebugLog, nullptr );
        GLuint unusedIds = 0;
        glDebugMessageControl( GL_DONT_CARE,
            GL_DONT_CARE,
            GL_DONT_CARE,
            0,
            &unusedIds,
            true );
    } else {
        std::cout << "glDebugMessageCallback not available" << std::endl;
    }
#endif

    HGLRC rc;
    if( wglewIsSupported( "WGL_ARB_create_context" ) == 1 ) {
        rc = wglCreateContextAttribsARB( dc, 0, attribs );
        wglMakeCurrent( NULL, NULL );
        wglDeleteContext( tempContext );
        bResult = wglMakeCurrent( dc, rc );
        if( !bResult ) {
            osre_error( Tag, "wglMakeCurrent failed." );
            return false;
        }
    }
    else {
        // It's not possible to make a GL 3.x context. Use the old style context (GL 2.1 and before)
        rc = tempContext;
    }

    if( !rc ) {
        return false;
    }

    // checking the supported GL version
    const char *GLVersionString = ( const char* ) glGetString( GL_VERSION );
    if( GLVersionString ) {
        String version( GLVersionString );
        osre_info( Tag, version );
    }

    // or better yet, use the GL4.x way to get the version number
    glGetIntegerv( GL_MAJOR_VERSION, &m_OpenGLVersion[ 0 ] );
    glGetIntegerv( GL_MINOR_VERSION, &m_OpenGLVersion[ 1 ] );

    m_dc = dc;
    m_rc = rc;

    glEnable( GL_TEXTURE_2D );
    glEnable( GL_TEXTURE_3D );
    glDisable( GL_LIGHTING );

    return true;
}

//-------------------------------------------------------------------------------------------------
bool Win32RenderContext::onDestroy( ) {
    if( nullptr == m_rc ) {
        return false;
    }

    wglDeleteContext( m_rc );
    m_rc = nullptr;

    return true;
}

//-------------------------------------------------------------------------------------------------
bool Win32RenderContext::onUpdate( ) {
    if( TRUE == ::SwapBuffers( m_dc ) ) {
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------
bool Win32RenderContext::onActivate( ) {
    if( m_active ) {
        return true;
    }

    if( FALSE == wglMakeCurrent( m_dc, m_rc ) ) {
        osre_debug( Tag, "Error while update render context." );
        return false;
    }
    m_active = true;

    return true;
}

//-------------------------------------------------------------------------------------------------

} // Namespace Platform
} // Namespace OSRE
