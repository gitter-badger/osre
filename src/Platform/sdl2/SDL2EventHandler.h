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

#include <osre/Platform/AbstractPlatformEventHandler.h>

#include <map>

struct SDL_Window;

namespace OSRE {
namespace Platform {

struct AbstractSDL2InputUpdate;

//-------------------------------------------------------------------------------------------------
///	@class		::OSRE::Platform::SDL2EventHandler
///	@ingroup	Engine
///
///	@brief  
//-------------------------------------------------------------------------------------------------
class SDL2EventHandler : public AbstractPlatformEventHandler {
public:
    SDL2EventHandler();
    virtual ~SDL2EventHandler();
    virtual bool onEvent( const Common::Event &event, const Common::EventData *pEventData );
    virtual void registerEventListener( const CPPCore::TArray<const Common::Event*> &events, OSEventListener *pListener );
    virtual void unregisterEventListener( const CPPCore::TArray<const Common::Event*> &events, OSEventListener *pListener );
    virtual void enablePolling( bool enabled );

protected:
    virtual bool onAttached( const Common::EventData *pEventData );
    virtual bool onDetached( const Common::EventData *pEventData );

private:
    static std::map<SDL_Window*, SDL2EventHandler*> s_windowsServerMap;
    bool m_isPolling;
    bool m_shutdownRequested;
    AbstractSDL2InputUpdate *m_pInputUpdate;
    Common::EventTriggerer *m_pEventTriggerer;
};

//-------------------------------------------------------------------------------------------------

} // Namespace Platform
} // Namespace OSRE
