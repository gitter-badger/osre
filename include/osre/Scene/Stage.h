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

#include <osre/Common/Object.h>

namespace OSRE {

namespace Common {
    class Ids;
}

namespace RenderBackend {
    struct TransformBlock;

    class RenderBackendService;
}

namespace Scene {

class Node;
class View;

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief
//-------------------------------------------------------------------------------------------------
struct TransformBlockCache {
    ui32 m_numBlocks;
    RenderBackend::TransformBlock *m_blocks;

    TransformBlockCache( ui32 numIniBlocks );
    ~TransformBlockCache();

private:
    TransformBlockCache() = delete;
    TransformBlockCache( const TransformBlockCache & ) = delete;
    TransformBlockCache &operator = ( const TransformBlockCache & ) = delete;
};

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief
//-------------------------------------------------------------------------------------------------
class OSRE_EXPORT Stage : public Common::Object {
public:
    Stage( const String &name, RenderBackend::RenderBackendService *rbService );
    virtual ~Stage();
    virtual void setRoot( Node *root );
    virtual Node *getRoot() const;
    virtual Node *addNode( const String &name, Node *parent );
    virtual Node *findNode( const String &name ) const;
    virtual View *addView( const String &name, Node *node );
    virtual void clear();
    virtual void update();
    virtual void setIdContainer( Common::Ids &ids );
    
private:
    Node *m_root;
    CPPCore::TArray<View*> m_views;
    TransformBlockCache m_transformBlocks;
    RenderBackend::RenderBackendService *m_rbService;
    Common::Ids *m_ids;
};

} // Namespace Scene
} // namespace OSRE
