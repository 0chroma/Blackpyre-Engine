// GENERATED CODE! Edit at your own risk!
#if !defined(DOXYGEN)
/** Specialization for functor taking 1 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<1,RV>
{
    static const int Arity = 1;
    template <  typename A0, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0;  AC0 ac0;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<1,RV>::Call() expects at least 1 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<1,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 1 arguments and returning void. */
template <>
struct FunctorForwarder<1,void>
{
    static const int Arity = 1;
    template <  typename A0, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0;  AC0 ac0;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<1,void>::Call() expects at least 1 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<1,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 1 argument(s).
*/
template <typename ReturnT,  typename A0, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc1( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<1,ReturnT>::template Call<  A0 >( func, argv );
}
/**
   Functionally identical to FwdToFunc1(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0), ::v8::Arguments const & argv )
{
    return FunctorForwarder<1,ReturnT>::template Call<  A0 >( func, argv );
}
/** Specialization for functor taking 2 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<2,RV>
{
    static const int Arity = 2;
    template <  typename A0,  typename A1, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1;  AC0 ac0; AC1 ac1;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<2,RV>::Call() expects at least 2 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<2,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 2 arguments and returning void. */
template <>
struct FunctorForwarder<2,void>
{
    static const int Arity = 2;
    template <  typename A0,  typename A1, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1;  AC0 ac0; AC1 ac1;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<2,void>::Call() expects at least 2 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<2,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 2 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc2( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<2,ReturnT>::template Call<  A0, A1 >( func, argv );
}
/**
   Functionally identical to FwdToFunc2(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1), ::v8::Arguments const & argv )
{
    return FunctorForwarder<2,ReturnT>::template Call<  A0, A1 >( func, argv );
}
/** Specialization for functor taking 3 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<3,RV>
{
    static const int Arity = 3;
    template <  typename A0,  typename A1,  typename A2, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2;  AC0 ac0; AC1 ac1; AC2 ac2;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<3,RV>::Call() expects at least 3 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<3,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 3 arguments and returning void. */
template <>
struct FunctorForwarder<3,void>
{
    static const int Arity = 3;
    template <  typename A0,  typename A1,  typename A2, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2;  AC0 ac0; AC1 ac1; AC2 ac2;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<3,void>::Call() expects at least 3 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<3,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 3 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc3( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<3,ReturnT>::template Call<  A0, A1, A2 >( func, argv );
}
/**
   Functionally identical to FwdToFunc3(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1, A2), ::v8::Arguments const & argv )
{
    return FunctorForwarder<3,ReturnT>::template Call<  A0, A1, A2 >( func, argv );
}
/** Specialization for functor taking 4 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<4,RV>
{
    static const int Arity = 4;
    template <  typename A0,  typename A1,  typename A2,  typename A3, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<4,RV>::Call() expects at least 4 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<4,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 4 arguments and returning void. */
template <>
struct FunctorForwarder<4,void>
{
    static const int Arity = 4;
    template <  typename A0,  typename A1,  typename A2,  typename A3, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<4,void>::Call() expects at least 4 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<4,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 4 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc4( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<4,ReturnT>::template Call<  A0, A1, A2, A3 >( func, argv );
}
/**
   Functionally identical to FwdToFunc4(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1, A2, A3), ::v8::Arguments const & argv )
{
    return FunctorForwarder<4,ReturnT>::template Call<  A0, A1, A2, A3 >( func, argv );
}
/** Specialization for functor taking 5 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<5,RV>
{
    static const int Arity = 5;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<5,RV>::Call() expects at least 5 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<5,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 5 arguments and returning void. */
template <>
struct FunctorForwarder<5,void>
{
    static const int Arity = 5;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<5,void>::Call() expects at least 5 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<5,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 5 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc5( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<5,ReturnT>::template Call<  A0, A1, A2, A3, A4 >( func, argv );
}
/**
   Functionally identical to FwdToFunc5(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1, A2, A3, A4), ::v8::Arguments const & argv )
{
    return FunctorForwarder<5,ReturnT>::template Call<  A0, A1, A2, A3, A4 >( func, argv );
}
/** Specialization for functor taking 6 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<6,RV>
{
    static const int Arity = 6;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<6,RV>::Call() expects at least 6 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<6,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 6 arguments and returning void. */
template <>
struct FunctorForwarder<6,void>
{
    static const int Arity = 6;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<6,void>::Call() expects at least 6 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<6,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 6 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc6( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<6,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5 >( func, argv );
}
/**
   Functionally identical to FwdToFunc6(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1, A2, A3, A4, A5), ::v8::Arguments const & argv )
{
    return FunctorForwarder<6,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5 >( func, argv );
}
/** Specialization for functor taking 7 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<7,RV>
{
    static const int Arity = 7;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<7,RV>::Call() expects at least 7 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<7,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 7 arguments and returning void. */
template <>
struct FunctorForwarder<7,void>
{
    static const int Arity = 7;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<7,void>::Call() expects at least 7 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<7,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 7 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc7( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<7,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5, A6 >( func, argv );
}
/**
   Functionally identical to FwdToFunc7(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1, A2, A3, A4, A5, A6), ::v8::Arguments const & argv )
{
    return FunctorForwarder<7,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5, A6 >( func, argv );
}
/** Specialization for functor taking 8 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<8,RV>
{
    static const int Arity = 8;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<8,RV>::Call() expects at least 8 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<8,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 8 arguments and returning void. */
template <>
struct FunctorForwarder<8,void>
{
    static const int Arity = 8;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<8,void>::Call() expects at least 8 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<8,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 8 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc8( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<8,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5, A6, A7 >( func, argv );
}
/**
   Functionally identical to FwdToFunc8(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1, A2, A3, A4, A5, A6, A7), ::v8::Arguments const & argv )
{
    return FunctorForwarder<8,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5, A6, A7 >( func, argv );
}
/** Specialization for functor taking 9 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<9,RV>
{
    static const int Arity = 9;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<9,RV>::Call() expects at least 9 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<9,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 9 arguments and returning void. */
template <>
struct FunctorForwarder<9,void>
{
    static const int Arity = 9;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<9,void>::Call() expects at least 9 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<9,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 9 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc9( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<9,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5, A6, A7, A8 >( func, argv );
}
/**
   Functionally identical to FwdToFunc9(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8), ::v8::Arguments const & argv )
{
    return FunctorForwarder<9,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5, A6, A7, A8 >( func, argv );
}
/** Specialization for functor taking 10 arguments.

@implements InvocableInterface
*/
template <typename RV>
struct FunctorForwarder<10,RV>
{
    static const int Arity = 10;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8; typedef ArgCaster<A9> AC9;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8; AC9 ac9;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<10,RV>::Call() expects at least 10 JS arguments!"));
        try
        {
            return CastToJS<RV>( f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]), ac9.ToNative(argv[9]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<10,ReturnType>: Native function threw an unknown native exception type!"));
        }
        return Undefined(); // cannot be reached.
    }
};
/** Specialization for functor taking 10 arguments and returning void. */
template <>
struct FunctorForwarder<10,void>
{
    static const int Arity = 10;
    template <  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, typename Func >
    static Handle<Value> Call( Func f, ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8; typedef ArgCaster<A9> AC9;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8; AC9 ac9;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctorForwarder<10,void>::Call() expects at least 10 JS arguments!"));
        try
        {
            f(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]), ac9.ToNative(argv[9]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctorForwarder<10,void>: Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
};

/**
   See the docs for FwdToFunc0(). This variant takes 10 argument(s).
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, typename Func>
::v8::Handle< ::v8::Value > FwdToFunc10( Func func, ::v8::Arguments const & argv )
{
    return FunctorForwarder<10,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 >( func, argv );
}
/**
   Functionally identical to FwdToFunc10(), but the templatized types can
   be deduced by the compiler.
*/
template <typename ReturnT,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), ::v8::Arguments const & argv )
{
    return FunctorForwarder<10,ReturnT>::template Call<  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 >( func, argv );
}
#endif // if !defined(DOXYGEN)
