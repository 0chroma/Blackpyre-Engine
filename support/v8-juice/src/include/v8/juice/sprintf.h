#ifndef CODE_GOOD_COM_P_V8_JUICE_SPRINTF_H_INCLUDED_
#define CODE_GOOD_COM_P_V8_JUICE_SPRINTF_H_INCLUDED_ 1
#include <stdarg.h>

#include <v8.h>

namespace v8 {
namespace juice {

    /**
       This function installs a JS-side sprintf() function into the
       given object. See the sprintf() docs for full details.
    */
    ::v8::Handle< ::v8::Value > SetupSprintf( ::v8::Handle< Object > target );

    /**
       This function works similarly to classical printf
       implementations, but returns the result as a javascript string.

       The first argument must be a printf-style format string (with some
       extensions - see below). The optional second (and subsequent)
       arguments are arbitrary values.

       If passed fewer arguments than there are format specifiers, it will
       throw a JS-side exception.

       PRINTF EXTENSIONS:

       %%h (HTML) works like %s but converts certain characters (like '<' and '&' to
       their HTML escaped equivalents.

       %%t (URL encode) works like %%s but converts certain characters into a representation
       suitable for use in an HTTP URL. (e.g. ' ' gets converted to %%20)

       %%T (URL decode) does the opposite of %t - it decodes URL-encoded
       strings.

       %%r requires an int and renders it in "ordinal form". That is,
       the number 1 converts to "1st" and 398 converts to "398th".

       %%q quotes a string as required for SQL. That is, '\'' characters get
       doubled.

       %%Q as %%q, but includes the outer '\'' characters and null pointers
       replaced by SQL NULL.

       (The %%q and %%Q specifiers are options inherited from this printf
       implementation's sqlite3 genes.)

       These extensions may be disabled by setting certain macros when
       compiling this code.


       BUGS:

       - Using a numeric specifier (e.g. %%d) and a corresponding value
       which is not strictly a numeric type, the conversion will likely
       result in a literal 0. This _might_ be fixable in this code.

       - Using padding parameters with %%s, e.g. %%20s, apparently doesn't
       work.

       - The %%n specifier is not supported, as we have no intuitive way
       of getting the value back to the caller.
    */
    ::v8::Handle< ::v8::Value > sprintf( int argc, Handle<Value> argv[] );

    /**
       A v8::InvocationCallback function for registration with JS code. See the
       two-arg overload for the complete docs. Two forms of this function are
       provided so that we can re-use the main sprintf() implementation from
       other routines.
    */
    ::v8::Handle< ::v8::Value > sprintf( ::v8::Arguments const & argv );


}} // namespaces

#endif /* CODE_GOOD_COM_P_V8_JUICE_SPRINTF_H_INCLUDED_ */
