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

#include "OGLCommon.h"

namespace OSRE {
namespace RenderBackend {

//-------------------------------------------------------------------------------------------------
///	@class		::OSRE::RenderBackend::OGLEnum
///	@ingroup	Engine
///
///	@brief  This utility class implements the OpenGL enum lookup.
//-------------------------------------------------------------------------------------------------
class OGLEnum {
public:
    ///	@brief  Translates the buffer type to OpenGL.
    static GLenum getGLBufferType( BufferType type );
    ///	@brief  Translates the access type to OpenGL.
    static GLenum getGLBufferAccessType( BufferAccessType type );
    ///	@brief  Translates the primitive type to OpenGL.
    static GLenum getGLPrimitiveType( PrimitiveType primType );
    ///	@brief  Translates the index type to OpenGL.
    static GLenum getGLIndexType( IndexType indexType );
    ///	@brief  Translates the texture type to OpenGL.
    static GLenum getGLTextureTarget( TextureTargetType type );
    ///	@brief  Translates the texture parameter type to OpenGL.
    static GLenum getGLTextureParameterName( TextureParameterName name );
    /// @brief  Translates the texture state to the corresponding GLenum type.
    static GLenum getGLTextureStage( TextureStageType texType );
    /// @brief  Translates the vertex format type to the corresponding GLenum type.
    static GLenum getOGLTypeForFormat( VertexFormat format );
    /// @brief  Translates the vertex format type to the corresponding size.
    static ui32 getOGLSizeForFormat( VertexFormat format );


private:
    OGLEnum();
    ~OGLEnum();
    OGLEnum( const OGLEnum & );
};

//-------------------------------------------------------------------------------------------------

} // Namespace RenderBackend
} // Namespace OSRE
