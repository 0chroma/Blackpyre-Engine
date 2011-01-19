// GENERATED CODE! Edit at your own risk!
#if !defined(DOXYGEN)
/**
   Overload requiring a WrappedType member function
   taking 1 args and returning RV.
*/
template < typename RV,  typename A0, RV (WrappedType::*Func)( A0)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp1< WrappedType, RV,  A0, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 1 args and returning RV.
*/
template < typename RV,  typename A0, RV (WrappedType::*Func)( A0)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp1< const WrappedType, RV,  A0, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 2 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1, RV (WrappedType::*Func)( A0, A1)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp2< WrappedType, RV,  A0, A1, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 2 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1, RV (WrappedType::*Func)( A0, A1)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp2< const WrappedType, RV,  A0, A1, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 3 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2, RV (WrappedType::*Func)( A0, A1, A2)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp3< WrappedType, RV,  A0, A1, A2, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 3 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2, RV (WrappedType::*Func)( A0, A1, A2)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp3< const WrappedType, RV,  A0, A1, A2, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 4 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV (WrappedType::*Func)( A0, A1, A2, A3)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp4< WrappedType, RV,  A0, A1, A2, A3, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 4 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV (WrappedType::*Func)( A0, A1, A2, A3)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp4< const WrappedType, RV,  A0, A1, A2, A3, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 5 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV (WrappedType::*Func)( A0, A1, A2, A3, A4)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp5< WrappedType, RV,  A0, A1, A2, A3, A4, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 5 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV (WrappedType::*Func)( A0, A1, A2, A3, A4)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp5< const WrappedType, RV,  A0, A1, A2, A3, A4, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 6 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp6< WrappedType, RV,  A0, A1, A2, A3, A4, A5, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 6 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp6< const WrappedType, RV,  A0, A1, A2, A3, A4, A5, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 7 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5, A6)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp7< WrappedType, RV,  A0, A1, A2, A3, A4, A5, A6, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 7 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5, A6)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp7< const WrappedType, RV,  A0, A1, A2, A3, A4, A5, A6, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 8 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5, A6, A7)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp8< WrappedType, RV,  A0, A1, A2, A3, A4, A5, A6, A7, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 8 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5, A6, A7)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp8< const WrappedType, RV,  A0, A1, A2, A3, A4, A5, A6, A7, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 9 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp9< WrappedType, RV,  A0, A1, A2, A3, A4, A5, A6, A7, A8, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 9 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp9< const WrappedType, RV,  A0, A1, A2, A3, A4, A5, A6, A7, A8, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType member function
   taking 10 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)  >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp10< WrappedType, RV,  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
/**
   Overload requiring a WrappedType const member function
   taking 10 args and returning RV.
*/
template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV (WrappedType::*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)  const >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::MemFuncCallOp10< const WrappedType, RV,  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
#endif // if !defined(DOXYGEN)
