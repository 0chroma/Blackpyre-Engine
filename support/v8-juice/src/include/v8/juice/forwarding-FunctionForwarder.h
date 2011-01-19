// GENERATED CODE! Edit at your own risk!
#if !defined(DOXYGEN)
/**
Specialization for functor taking 1 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<1>
{
    static const int Arity = 1;
    template < typename RV,  typename A0 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0;  AC0 ac0;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<1>::Call() expects at least 1 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<1>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0;  AC0 ac0;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<1>::Call() expects at least 1 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<1>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0>( Func, argv );
    }

    template <typename RV,  typename A0, RV (*Func)( A0) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0 >( Func, argv );
    }

    template <typename VoidType,  typename A0, VoidType (*Func)( A0) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0 >( Func, argv );
    }

};

/**
Specialization for function taking 1 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0, RV (*Func)( A0)>
struct InvocableFunction1
{
    static const int Arity = 1;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 2 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<2>
{
    static const int Arity = 2;
    template < typename RV,  typename A0,  typename A1 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1;  AC0 ac0; AC1 ac1;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<2>::Call() expects at least 2 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<2>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1;  AC0 ac0; AC1 ac1;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<2>::Call() expects at least 2 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<2>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1, RV (*Func)( A0, A1) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1, VoidType (*Func)( A0, A1) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1 >( Func, argv );
    }

};

/**
Specialization for function taking 2 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1, RV (*Func)( A0, A1)>
struct InvocableFunction2
{
    static const int Arity = 2;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 3 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<3>
{
    static const int Arity = 3;
    template < typename RV,  typename A0,  typename A1,  typename A2 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1, A2), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2;  AC0 ac0; AC1 ac1; AC2 ac2;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<3>::Call() expects at least 3 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<3>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1,  typename A2 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1, A2), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2;  AC0 ac0; AC1 ac1; AC2 ac2;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<3>::Call() expects at least 3 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<3>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1,  typename A2 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1, A2), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2, RV (*Func)( A0, A1, A2) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1, A2 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2, VoidType (*Func)( A0, A1, A2) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2 >( Func, argv );
    }

};

/**
Specialization for function taking 3 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1,  typename A2, RV (*Func)( A0, A1, A2)>
struct InvocableFunction3
{
    static const int Arity = 3;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 4 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<4>
{
    static const int Arity = 4;
    template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1, A2, A3), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<4>::Call() expects at least 4 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<4>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1, A2, A3), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<4>::Call() expects at least 4 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<4>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1, A2, A3), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV (*Func)( A0, A1, A2, A3) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1, A2, A3 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3, VoidType (*Func)( A0, A1, A2, A3) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3 >( Func, argv );
    }

};

/**
Specialization for function taking 4 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV (*Func)( A0, A1, A2, A3)>
struct InvocableFunction4
{
    static const int Arity = 4;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 5 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<5>
{
    static const int Arity = 5;
    template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1, A2, A3, A4), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<5>::Call() expects at least 5 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<5>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1, A2, A3, A4), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<5>::Call() expects at least 5 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<5>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1, A2, A3, A4), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV (*Func)( A0, A1, A2, A3, A4) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1, A2, A3, A4 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, VoidType (*Func)( A0, A1, A2, A3, A4) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4 >( Func, argv );
    }

};

/**
Specialization for function taking 5 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV (*Func)( A0, A1, A2, A3, A4)>
struct InvocableFunction5
{
    static const int Arity = 5;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 6 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<6>
{
    static const int Arity = 6;
    template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1, A2, A3, A4, A5), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<6>::Call() expects at least 6 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<6>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1, A2, A3, A4, A5), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<6>::Call() expects at least 6 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<6>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1, A2, A3, A4, A5), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV (*Func)( A0, A1, A2, A3, A4, A5) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1, A2, A3, A4, A5 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, VoidType (*Func)( A0, A1, A2, A3, A4, A5) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5 >( Func, argv );
    }

};

/**
Specialization for function taking 6 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV (*Func)( A0, A1, A2, A3, A4, A5)>
struct InvocableFunction6
{
    static const int Arity = 6;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 7 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<7>
{
    static const int Arity = 7;
    template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1, A2, A3, A4, A5, A6), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<7>::Call() expects at least 7 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<7>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1, A2, A3, A4, A5, A6), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<7>::Call() expects at least 7 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<7>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1, A2, A3, A4, A5, A6), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5, A6>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV (*Func)( A0, A1, A2, A3, A4, A5, A6) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1, A2, A3, A4, A5, A6 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, VoidType (*Func)( A0, A1, A2, A3, A4, A5, A6) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5, A6 >( Func, argv );
    }

};

/**
Specialization for function taking 7 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV (*Func)( A0, A1, A2, A3, A4, A5, A6)>
struct InvocableFunction7
{
    static const int Arity = 7;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 8 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<8>
{
    static const int Arity = 8;
    template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<8>::Call() expects at least 8 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<8>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1, A2, A3, A4, A5, A6, A7), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<8>::Call() expects at least 8 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<8>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1, A2, A3, A4, A5, A6, A7), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5, A6, A7>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1, A2, A3, A4, A5, A6, A7 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, VoidType (*Func)( A0, A1, A2, A3, A4, A5, A6, A7) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5, A6, A7 >( Func, argv );
    }

};

/**
Specialization for function taking 8 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7)>
struct InvocableFunction8
{
    static const int Arity = 8;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 9 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<9>
{
    static const int Arity = 9;
    template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<9>::Call() expects at least 9 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<9>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<9>::Call() expects at least 9 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<9>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5, A6, A7, A8>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1, A2, A3, A4, A5, A6, A7, A8 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, VoidType (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5, A6, A7, A8 >( Func, argv );
    }

};

/**
Specialization for function taking 9 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8)>
struct InvocableFunction9
{
    static const int Arity = 9;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


/**
Specialization for functor taking 10 arguments.

@implements InvocableInterface
*/
template <>
struct FunctionForwarder<10>
{
    static const int Arity = 10;
    template < typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static v8::Handle<v8::Value> Call( RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8; typedef ArgCaster<A9> AC9;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8; AC9 ac9;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<10>::Call() expects at least 10 JS arguments!"));
        try
        {
            return CastToJS<RV>( Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]), ac9.ToNative(argv[9]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<10>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static v8::Handle<v8::Value> CallVoid( VoidType (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), ::v8::Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8; typedef ArgCaster<A9> AC9;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8; AC9 ac9;
	if( argv.Length() < Arity ) return ::v8::ThrowException(::v8::String::New("FunctionForwarder<10>::Call() expects at least 10 JS arguments!"));
        try
        {
            Func(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]), ac9.ToNative(argv[9]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<10>::Call() Native function threw an unknown native exception type!"));
        }
        return Undefined();
    }
    template < typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static v8::Handle<v8::Value> Call( void (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), ::v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( Func, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) >
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Call<RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 >( Func, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, VoidType (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) >
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return CallVoid<VoidType,  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 >( Func, argv );
    }

};

/**
Specialization for function taking 10 arguments.

@implements InvocableInterface
*/
template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV (*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
struct InvocableFunction10
{
    static const int Arity = 10;

    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::Call<RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
    }
};


#endif // if !defined(DOXYGEN)
