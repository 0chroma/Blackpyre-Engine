/**
   This supermacro file creates full specializations of some
   ClassWrap<CLASSWRAP_BOUND_TYPE> option policies, deriving them from
   the ClassWrap<CLASSWRAP_BOUND_TYPE_INHERITS> policy.

   As is conventional for supermacros, this file undefines CLASSWRAP_BOUND_TYPE_INHERITS
   and CLASSWRAP_BOUND_TYPE before it returns.
*/
#if !defined(CLASSWRAP_BOUND_TYPE) || !defined(CLASSWRAP_BOUND_TYPE_INHERITS)
#  error "CLASSWRAP_BOUND_TYPE and CLASSWRAP_BOUND_TYPE_INHERITS must be defined before including this file!"
#endif
/** */ // just to avoid doxygen adding the above docs to the v8 namespace!
namespace v8 { namespace juice { namespace cw {

template <>
struct InternalFields< CLASSWRAP_BOUND_TYPE > :
    InternalFields< CLASSWRAP_BOUND_TYPE_INHERITS >
{};

template <>
struct ToNative_SearchPrototypesForNative< CLASSWRAP_BOUND_TYPE > :
    ToNative_SearchPrototypesForNative< CLASSWRAP_BOUND_TYPE_INHERITS >
{};

} } } // v8::juice::cw
#undef CLASSWRAP_BOUND_TYPE
#undef CLASSWRAP_BOUND_TYPE_INHERITS
