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

#include <osre/Platform/AbstractSurface.h>

struct SDL_Window;

namespace OSRE {
namespace Platform {

//-------------------------------------------------------------------------------------------------
///	@class		::OSRE::Platform::SDL2Surface
///	@ingroup	Engine
///
///	@brief
//-------------------------------------------------------------------------------------------------
class SDL2Surface : public AbstractSurface {
public:
    /// The class constructor.
    SDL2Surface( SurfaceProperties *props );
    /// The class destructor, virtual.
    virtual ~SDL2Surface();
    /// Will return a pointer showing to the SDL_Window.
    SDL_Window *getSDLSurface() const;

protected:
    /// The onCreate callback implementation.
    virtual bool onCreate();
    /// The onDestroy callback implementation.
    virtual bool onDestroy();
    /// The onUpdateProperies callback implementation.
    virtual bool onUpdateProperies();

private:
    SDL_Window *m_surface;
};

//-------------------------------------------------------------------------------------------------

} // Namespace Platform
} // Namespace OSRE
