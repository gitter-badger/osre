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
#pragma once

#include <string>
#include <string.h>
#include <stdio.h>
#include <cstddef>

#ifndef _WIN32
#  include <inttypes.h>
#endif 

namespace OSRE {

#if defined( _WIN32 ) || defined( _WIN64 )
#   define OSRE_WINDOWS
#   define _CRT_SECURE_NO_WARNINGS
#elif defined(__gnu_linux__)
#   define OSRE_GNU_LINUX
#endif

#ifdef OSRE_WINDOWS
#  define TAG_DLL_EXPORT __declspec(dllexport)
#  define TAG_DLL_IMPORT __declspec(dllimport )
#else
#  define OSRE_EXPORT
#  define OSRE_DLL_IMPORT
#endif 

#ifdef OSRE_WINDOWS
#   ifdef OSRE_BUILD_EXPORT
#       define OSRE_EXPORT TAG_DLL_EXPORT
#   else
#       define OSRE_EXPORT TAG_DLL_IMPORT
#   endif
#else
#   define OSRE_EXPORT
#endif

#if _MSC_VER >= 1200
#  pragma warning( disable : 4006 ) // Ignore double defined symbols warning
#  pragma warning( disable : 4786 )
#  pragma warning( disable : 4251 )
#  pragma warning( disable : 4275 )
#  pragma warning( disable : 4127 )	// Conditional expression is constant
#  pragma warning( disable : 4100 )
#  pragma warning( disable : 4201 ) // No standard extension
#  pragma warning( disable : 4316 )
#endif

// Declares thread-local data
#ifdef OSRE_WINDOWS
#   define ThreadLocal __declspec(thread)
#else
#   define ThreadLocal __thread
#endif

// Platform-specific data types
#if defined(__MINGW32__) || defined(__MINGW64__)
#   include <stdio.h>
    typedef int errno_t;
#endif

///	The data type unsigned char, 1 byte long.
typedef unsigned char uc8;

///	The data type signed char, 1 byte long.
typedef char c8;

///	The data type unsigned short, 2 byte long.
typedef unsigned short ui16;

///	The data type signed short, 2 byte long.
typedef signed short i16;

///	The data type signed int, 4 byte long.
typedef int	i32;

///	The data type unsigned int, 4 byte long.
typedef unsigned short ui16;

///	The data type signed int, 4 byte long.
typedef unsigned int ui32;

///	The data type for signed and unsigned int 8 bytes long.
#ifdef OSRE_WINDOWS
typedef __int64           i64;
typedef unsigned __int64  ui64;
#else
typedef int64_t           i64;
typedef uint64_t          ui64;
#endif

/// The data type for hash ids.
typedef unsigned long HashId;

///	The data type float, 4 byte long.
typedef float f32;

///	The data type double, 8 byte long.
typedef double d32;

///	The data type Object id.
typedef int ObjectId;

///	The data type for strings
typedef std::string String;

struct Handle {
    int m_idx;

    void init( int idx ) {
        m_idx = idx;
    }
};

///	@brief  Shortcut to avoid copy operations.
#define OSRE_NON_COPYABLE( NAME ) \
private: \
    NAME( const NAME & ) = delete;        \
    NAME& operator = ( const NAME & ) = delete;

///	@brief  Shortcut to get a OSRE-main function.
/// 
#define OSRE_MAIN( APPNAME ) \
int main( int argc, char *argv[] )  { \
    APPNAME myApp( argc, argv ); \
    if ( !myApp.create() ) { \
        return 1; \
    } \
    while ( myApp.handleEvents() ) { \
        myApp.update(); \
        myApp.requestNextFrame();\
    }\
    myApp.destroy();\
\
    return 0;\
}

} // Namespace OSRE
