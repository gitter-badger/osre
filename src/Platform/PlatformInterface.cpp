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
#include <osre/Platform/PlatformInterface.h>
#include <src/Platform/PlatformPluginFactory.h>
#include <osre/Common/EventTriggerer.h>
#include <osre/Properties/Settings.h>
#ifdef OSRE_WINDOWS
#   include <src/Platform/win32/Win32Surface.h>
#   include <src/Platform/win32/Win32Eventhandler.h>
#   include <src/Platform/win32/Win32Timer.h>
#   include <src/Platform/win32/Win32RenderContext.h>
#   include <src//Platform/win32/Win32ThreadFactory.h>
#endif // OSRE_WINDOWS
#include <src/Platform/sdl2/SDL2Surface.h>
#include <src/Platform/sdl2/SDL2EventHandler.h>
#include <src/Platform/sdl2/SDL2RenderContext.h>
#include <src/Platform/sdl2/SDL2Timer.h>
#include <src/Platform/sdl2/SDL2ThreadFactory.h>

#include <GL/glew.h>
#include <SDL.h>

namespace OSRE {
namespace Platform {

using namespace ::OSRE::Common;
using namespace ::OSRE::Properties;

PlatformInterface *PlatformInterface::s_instance( nullptr );

static const String PlatformPluginName[ MaxPlugin ] = {
#ifdef OSRE_WINDOWS
    "WindowsPlugin",
#endif // OSRE_WINDOWS
    "SDL2Plugin"
};

static const String Tag = "PlatformInterface";

PlatformInterface::PlatformInterface( const Settings *config )
: AbstractService( "platform/platforminterface" )
, m_config( config )
#ifdef OSRE_WINDOWS
, m_type( WindowsPlugin )
#else
, m_type( SDL2Plugin )
#endif // OSRE_WINDOWS
, m_pRootSurface( nullptr )
, m_pOSEventHandler( nullptr )
, m_pTimer( nullptr )
, m_dynLoader( nullptr ) {
    // empty
}

PlatformInterface::~PlatformInterface() {
    delete m_config;
    m_config = nullptr;
}

PlatformInterface *PlatformInterface::create( const Settings *config ) {
    if( nullptr == s_instance ) {
        s_instance = new PlatformInterface( config );
    }

    return s_instance;
}

void PlatformInterface::destroy( ) {
    if( nullptr == s_instance ) {
        return;
    }

    s_instance->close();
    delete s_instance;
    s_instance = nullptr;
}

PlatformInterface *PlatformInterface::getInstance( ) {
    return s_instance;
}

AbstractPlatformEventHandler *PlatformInterface::getPlatformEventHandler() const {
    return m_pOSEventHandler;
}

AbstractRenderContext *PlatformInterface::getRenderContext() const {
    return m_pRenderContext;
}

AbstractSurface *PlatformInterface::getRootSurface() const {
    return m_pRootSurface;
}

AbstractTimer *PlatformInterface::getTimer() const {
    return m_pTimer;
}

AbstractDynamicLoader *PlatformInterface::getDynamicLoader() const {
    return m_dynLoader;
}

const String &PlatformInterface::getDefaultFontName() const {
    if ( nullptr == m_config ) {
        static const String dummy( "none" );
        return dummy;
    }

    static const String font( m_config->get( Settings::DefaultFont ).getString() );
    return font;
}

PluginType PlatformInterface::getOSPluginType() {
#ifdef OSRE_WINDOWS
    return WindowsPlugin;
#else 
    return SDL2Plugin;
#endif // OSRE_WINDOWS
}

String PlatformInterface::getOSPluginName( PluginType type ) {
    String name( "None" );
    switch( type ) {
#ifdef OSRE_WINDOWS
        case WindowsPlugin:
            name = PlatformPluginName[ WindowsPlugin ];
            break;
#endif // OSRE_WINDOWS

        case SDL2Plugin:
            name = PlatformPluginName[ SDL2Plugin ];
            break;
        default:
            break;
    }

    return name;
}

bool PlatformInterface::onOpen() {
    if( !m_config ) {
        assert( nullptr != m_config );
        osre_debug( Tag, "Invalid pointer to configuration." );
        return false;
    }

    Settings::WorkingModeType appType = 
        ( Settings::WorkingModeType ) m_config->get( Settings::AppType ).getInt();

    SurfaceProperties *props( nullptr );
    bool polls( false );
    if( appType == Settings::GfxApp ) {
        // get the configuration values for the window
        props = new SurfaceProperties;
        bool fullscreen = false;
        props->m_x = m_config->get( Settings::WinX ).getInt();
        props->m_y = m_config->get( Settings::WinY ).getInt();
        props->m_width = m_config->get( Settings::WinWidth ).getInt();
        props->m_height = m_config->get( Settings::WinHeight ).getInt();
        props->m_colordepth = m_config->get( Settings::BPP ).getInt();
        props->m_depthbufferdepth = m_config->get( Settings::DepthBufferDepth ).getInt();
        props->m_stencildepth = m_config->get( Settings::StencilBufferDepth ).getInt();
        props->m_fullscreen = fullscreen;
        props->m_resizable = m_config->get( Settings::WindowsResizable ).getBool();
        props->m_title = m_config->get( Settings::WindowsTitle ).getString();
        polls = m_config->get( Settings::PollingMode ).getBool();
    }

    String appName = "OSRE Applicaton";
    m_type = static_cast<PluginType>( m_config->get( Settings::PlatformPlugin ).getInt( ) );

    PlatformPluginFactory::init( m_type );
    osre_info( Tag, "Platform plugin created for " + PlatformInterface::getOSPluginName( m_type ) );

    m_dynLoader = PlatformPluginFactory::createDynmicLoader( m_type );

    PlatformPluginFactory::createThreadFactory( m_type );

    bool result( true );
    if( appType == Settings::GfxApp ) {
        result = setupGfx( props, polls );
    }

    return result;
}

//-------------------------------------------------------------------------------------------------
bool PlatformInterface::onClose( ) {
    PlatformPluginFactory::release( m_type );

    delete m_pOSEventHandler;
    m_pOSEventHandler = nullptr;

    if( nullptr != m_pRenderContext ) {
        m_pRenderContext->destroy();
        delete m_pRenderContext;
        m_pRenderContext = nullptr;
    }

    return true;
}

//-------------------------------------------------------------------------------------------------
bool PlatformInterface::onUpdate( d32 timediff ) {
    Common::Event ev( "none" );
    return m_pOSEventHandler->onEvent( ev, nullptr );
}

//-------------------------------------------------------------------------------------------------
bool PlatformInterface::setupGfx( SurfaceProperties *props, bool polls ) {
    // create the root surface
    m_pRootSurface = PlatformPluginFactory::createSurface( m_type, props );
    if( !m_pRootSurface->create() ) {
        delete m_pRootSurface;
        osre_error( Tag, "Error while creating platform root surface." );

        m_pRootSurface = nullptr;
        return false;
    }

    // install the platform event handler
    m_pOSEventHandler = PlatformPluginFactory::createPlatformEventHandler( m_type, m_pRootSurface );
    if( !m_pOSEventHandler ) {
        osre_error( Tag, "Error while creating platform event handler." );
        m_pRootSurface->destroy();
        m_pRootSurface = nullptr;
        return false;
    }
    m_pOSEventHandler->enablePolling( polls );
    m_pTimer = PlatformPluginFactory::createTimer( m_type );

    // setup the render context
    m_pRenderContext = PlatformPluginFactory::createRenderContext( m_type );

    return true;
}

//-------------------------------------------------------------------------------------------------

} // Namespace Platform
} // Namespace OSRE
