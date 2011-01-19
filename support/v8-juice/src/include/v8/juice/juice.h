#ifndef CODE_GOOGLE_COM_V8_JUICE_JUICE_H_INCLUDED
#define CODE_GOOGLE_COM_V8_JUICE_JUICE_H_INCLUDED

#include <v8.h>
#include <string>
#include "juice-config.h"
/** @mainpage v8-juice

v8-juice is a C++ library providing extended functionality based on
Google's v8 JavaScript engine (http://code.google.com/p/v8).

The v8-juice home page is:

http://code.google.com/p/v8-juice


Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)


License: the core library is mostly New BSD with some Public Domain code.
Certain addons/extensions may have other licenses, in particular those which
use 3rd-party libraries with viral licenses (e.g. the GPL).


Where to start:


The wiki pages on the home page should be informative to new users. Aside
from that, there are tons of API docs here amongst the humble header files.

The more significant header files are:

- juice.h = the main library header.
- convert.h = JS to/from Native conversion routines and types.
- forwarding.h = (member) function binding utilities.
- TypeList.h = TypeList-related metaprogramming tools.
- tmp.h = base template metaprogramming tools.
*/
namespace {}

/**
   A macro which evaluates to nothing bug can be used to mark places
   which are known to be associated with (or the cause of) a certain
   bug number. The N parameter should be a number from the bug list
   on the home page:

   http://code.google.com/p/v8-juice/issues
*/
#define V8_JUICE_BUG_NUMBER(N)

namespace v8 {

/**
   The juice namespace is the top-most namespace used by the
   v8-juice toolkit.
*/
namespace juice {

	using ::v8::Handle;
	using ::v8::Value;

	/**
	   Do not use - it can lead to stack corruption
	   in some cases for unknown reasons. It's only
	   in the public API so i can use the existing client
	   code to track down the problem.

	   A convenience function to throw a v8 exception from a
	   printf-style formatted string.

	   The return value is the result of calling
	   v8::ThrowException(String::New(the_formatted_string)).

	   Example:

	   \code
	   return Toss("Error #%d while performing action %s!", errCode, actionType);
	   \endcode
	*/
	Handle<Value> ThrowException(char const * fmt,...);

    /**
       This can be registered as a JS function to provide an include()
       feature.  It reads the given file as JS, using the search path
       specified by ScriptsPath(). Returns the result of evaluting the
       file, throwing exception on error. The returned value will be
       IsEmpty() if an exception is thrown or propagated.
    */
    Handle<Value> IncludeScript( v8::Arguments const & argv );

    /**
       Works like the JS-bindable version, but takes a single script
       name as its argument. If useSearchPath is false then the
       ScriptsPath() path is not used for searching for the filename,
       and it is assumed to resolve as-is.
    */
    Handle<Value> IncludeScript( char const * filename, bool useSearchPath = true );
        
    /**
       Escapes all single-quote characters in the given string by inserting
       backslashes before them. Returns the escaped string, which may be
       the same as the original.
    */
    std::string StringJSEscape( std::string const & inp );

    /**
       Works like StringJSEscape(), but also adds outer quotes
       to the string. The type of quotes it adds is determined
       like so:

       - If s contains no single quotes, it gets quoted in single quotes. Else...
       - If s contains no double quotes, it gets quoted in double quotes. Else...
       - All single quotes get escaped and the string is quoted in single quotes.

       Returns the modified string.
    */
    std::string StringJSQuote( std::string const & s );

    /**
       Searches for a sub-object of the given object, creating it if
       needed. It is intended to be used like this:

       @code
       Handle<Object> ns = GetNamespaceObject( myGlobalObject, "foo.bar" );
       @endcode

       myGlobalObject is the top-most object in which to search for
       the namespace (e.g. the current global object).

       If myGlobalObject does not contain an object property named 'foo' then it is
       created, otherwise it is used as-is for the next search... If foo contains
       no a object named 'bar' then myGlobalObject.foo.bar is created.
       
       The ns parameter is a formatted string containing one or more
       object names making up the namespace.  The object names may be
       separated by '.', '/', or ':', so all of the following are
       legal and have the same meaning:

       - foo.bar.com
       - foo/bar::com
       - foo::bar::com
       

       The returned object will be an empty handle on error or the
       last object in the namespace list. Error conditions include:

       - !top->IsObject()
       - ns does not have any tokens.

       The intent is to allow multiple add-on classes/modules to use a
       common namespace for storing their features without having to
       know whether it's been created or not yet.
    */
    v8::Handle<v8::Object> GetNamespaceObject( v8::Handle<v8::Object> top, char const * ns );
    

}} // namespace

#endif // CODE_GOOGLE_COM_V8_JUICE_JUICE_H_INCLUDED
