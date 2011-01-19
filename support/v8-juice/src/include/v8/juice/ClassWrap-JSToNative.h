/**
   A supermacro for creating JSToNative specializations for a given
   type.

   Using this file:

   @code
   #define CLASSWRAP_BOUND_TYPE MyType
   #include <v8/juice/ClassWrap-JSToNative.h>
   @endcode

   CLASSWRAP_BOUND_TYPE will be undefined by this file, as is conventional for
   supermacro arguments.
   
*/
#if ! defined(CLASSWRAP_BOUND_TYPE)
#error "You must define CLASSWRAP_BOUND_TYPE before including this file!"
#endif

#if !defined(DOXYGEN)
namespace v8 { namespace juice { namespace convert {
    /**
       JSToNative<> specialization which uses
       v8::juice::ToNative::Value() to convert from JS
       handles to CLASSWRAP_BOUND_TYPE objects.
       
       See NativeToJS<> for full details.
    */
    template <>
    struct JSToNative< CLASSWRAP_BOUND_TYPE > :
        v8::juice::cw::JSToNativeImpl< CLASSWRAP_BOUND_TYPE >
    {
    };

} } }
#endif // DOXYGEN

#undef CLASSWRAP_BOUND_TYPE
