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
#include <cppcore/Container/TArray.h>

namespace OSRE {

namespace Common {
    class Ids;
}

namespace RenderBackend {
    struct TransformBlock;
    struct StaticGeometry;

    class RenderBackendService;
}

namespace Scene {

class Component;
class RenderComponent;
class TransformComponent;

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief  This class is used to represents a simple node in the stage hierarchy. You can add  
///  several functionalities by adding components to is. Each component implements functionality 
/// like render geometry or transformation information.
//-------------------------------------------------------------------------------------------------
class OSRE_EXPORT Node : public Common::Object {
public:
    enum class ComponentType {
        RenderComponentType,
        TransformComponentType
    };

    enum class TraverseMode {
        FlatMode,
        RecursiveMode
    };

public:
    Node( const String &name, Common::Ids &ids, bool transformEnabled, bool renderEnabled, Node *parent = nullptr );
    virtual ~Node();
    virtual void setParent( Node *parent );
    virtual Node *getParent() const;
    virtual void addChild( Node *child );
    virtual bool removeChild( const String &name, TraverseMode mode );
    virtual Node *findChild( const String &name ) const;
    virtual ui32 getNumChilds() const;
    virtual Node *getChildAt( ui32 idx ) const;
    virtual void releaseChildren();
    virtual void addGeometry( RenderBackend::StaticGeometry *geo );
    virtual void update( RenderBackend::RenderBackendService *renderBackendSrv );

    Component *getComponent( ComponentType type ) const;
    void setActive( bool isActive );
    bool isActive() const;

private:
    CPPCore::TArray<Node*> m_childs;
    Node *m_parent;
    bool m_isActive;
    RenderBackend::TransformBlock *m_localTransform;
    RenderComponent *m_renderComp;
    TransformComponent *m_transformComp;
    CPPCore::TArray<Component*> m_components;
    Common::Ids *m_ids;
};

//-------------------------------------------------------------------------------------------------

} // Namespace Scene
} // namespace OSRE
