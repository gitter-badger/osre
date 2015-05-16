/* ZFX Community Engine 2  (ZFXCE2)
---------------------------------------------------------------------------------------------------
Copyright (c) 2011-2015, ZFXCE2 Development Team
All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the 
following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions 
  and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this list of conditions
  and the following disclaimer in the documentation and/or other materials provided with the 
  distribution.

* Neither the name of the ZFXCE2 team, nor the names of its contributors may be used to endorse or 
  promote products derived from this software without specific prior written permission of the 
  ZFXCE2 Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-------------------------------------------------------------------------------------------------*/
#include <osre/Common/Logger.h>
#include <osre/Properties/ConfigurationMap.h>
#include <osre/Platform/PlatformInterface.h>
#include <osre/Platform/AbstractTimer.h>
#include <osre/Common/TObjPtr.h>
#include <osre/Common/ArgumentParser.h>

#include "RenderTestSuite.h"

using namespace ::OSRE;
using namespace ::OSRE::RenderTest;
using namespace ::OSRE::Platform;

int main( int argc, char *argv[] ) {
    Common::ArgumentParser argParser( argc, argv, "api:media" );
    String renderAPI( "opengl" );
    if ( argParser.hasArgument( "api" ) ) {
        renderAPI = argParser.getArgument( "api" ); 
    }

    String mediaPath( "../../Media/" );
    if( argParser.hasArgument( "media" ) ) {
        mediaPath = argParser.getArgument( "media" );
    }

    RenderTestSuite *rtSuite = RenderTestSuite::create( "tests", renderAPI );
    RenderTestSuite::getInstance()->setRenderAPI( renderAPI );
    RenderTestSuite::getInstance( )->setMediaPath( mediaPath );
    
    AbstractTimer *pTimer( rtSuite->getTimer() );
    if( !pTimer ) {
        return 1;
    }

    while( rtSuite->update( pTimer->getTimeDiff( ) ) ) {
        rtSuite->startTests();
    }

    RenderTestSuite::kill();

    return 0;
}