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
#include <gtest/gtest.h>
#include <osre/Scene/GeometryBuilder.h>
#include <osre/RenderBackend/RenderCommon.h>

namespace OSRE {
namespace UnitTest {

using namespace ::OSRE::Scene;
using namespace ::OSRE::RenderBackend;

class GeometryBuilderTest : public ::testing::Test {
    // empty
};

TEST_F( GeometryBuilderTest, allocEmptyGeometryTest ) {
    StaticGeometry *geoArray = Scene::GeometryBuilder::allocEmptyGeometry( ColorVertex, 2 );
    EXPECT_NE( geoArray, nullptr );

    for ( ui32 i = 0; i < 2; i++ ) {
        StaticGeometry &currentGeo( geoArray[ i ] );
        EXPECT_EQ( currentGeo.m_vertextype, ColorVertex );
    }
    StaticGeometry::destroy( &geoArray );
}

TEST_F( GeometryBuilderTest, allocTrianglesTest ) {
    StaticGeometry *geo = Scene::GeometryBuilder::allocTriangles( ColorVertex );
    EXPECT_NE( geo, nullptr );
    EXPECT_EQ( geo->m_vertextype, ColorVertex );
    EXPECT_NE( geo->m_vb, nullptr );
    EXPECT_NE( geo->m_ib, nullptr );
    EXPECT_NE( geo->m_material, nullptr );
    StaticGeometry::destroy( &geo );
}

} // Namespace UnitTest
} // Namespace OSRE
