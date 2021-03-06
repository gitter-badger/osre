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

#include <osre/Common/osre_common.h>

namespace OSRE {
namespace IO {

//-------------------------------------------------------------------------------------------------
///	@ingroup	Engine
///
///	@brief	This class represents a URI ( see
///	http://en.wikipedia.org/wiki/Uniform_Resource_Identifier ). You can use it to describe the
///	location of resources like:
///
///	file://c:/texture.jpg
///
/// For this example the schema is: file.
/// For this example the path is c:/.
/// For this example the resource name is texture.jpg.
//-------------------------------------------------------------------------------------------------
class OSRE_EXPORT Uri {
public:
    ///	@brief	The default class constructor.
    Uri();

    ///	@brief	The class constructor with a string containing a valid URI. If the string description
    ///			is not ok the URI representation will be empty.
    ///	@param	uri			[in] The string with the URI.
    Uri( const String &uri );

    ///	@brief	The copy class constructor.
    ///	@param	rhs		[in] Instance to copy.
    Uri( const Uri &rhs );

    ///	@brief	The class destructor.
    ~Uri();

    static String constructFromComps( const String &scheme, const String &path, const String &res );

    ///	@brief	Assigns a new uri string, the older data will be erased.
    ///	@param	uri			[in] The string with the URI.
    void setUri( const String &uri );

    ///	@brief	Returns the uri string.
    ///	@return	The uri string.
    const String &getUri() const;

    ///	@brief	Returns the scheme of the URI.
    ///	@return	A string containing the scheme.
    const String &getScheme() const;

    void setScheme( const String &scheme );

    ///	@brief	Returns the path of the URI.
    ///	@return	A string containing the path.
    const String &getPath() const;

    void setPath( const String &path );

    ///	@brief	Returns the resource name of the URI.
    ///	@return	A string containing the resource.
    const String &getAbsPath() const;

    ///	@brief	Returns the absolute path ( path + resource ) of the URI.
    ///	@return	A string containing the absolute path.
    const String &getResource() const;

    void setResource( const String &res );

    ///	@brief	Returns true, if the scheme is empty.
    ///	@return	true, if the URI is empty, false if not.
    bool isEmpty() const;

    ///	@brief	Parse the URI.
    ///	@return	true, if the URI is valid, false if not.
    bool parse();

    ///	@brief	Will return true, if the uri content is valid.
    ///	@return	true, if the uri itself is valid, false if not.
    bool isValid() const;

    ///	@brief	The URI representation will be cleared.
    void clear();

    ///	@brief	The assignment operator.
    Uri &operator = ( const Uri &rhs );

    ///	@brief	The compare operator.
    bool operator == ( const Uri &rhs ) const;

private:
    String m_URI;
    String m_Scheme;
    String m_Path;
    String m_AbsPath;
    String m_Resource;
};

//-------------------------------------------------------------------------------------------------

} // Namespace IO
} // Namespace OSRE
