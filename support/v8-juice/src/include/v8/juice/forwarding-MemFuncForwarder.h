// GENERATED CODE! Edit at your own risk!
#if !defined(DOXYGEN)
/**
A helper class for forwarding JS arguments to member functions
taking 1 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<1>
{
    static const int Arity = 1;
    template <typename T, typename RV,  typename A0>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0;  AC0 ac0;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<1>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0>
    static Handle<Value> Call( RV (T::*MemFunc)( A0), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0;  AC0 ac0;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<1>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0>
    static Handle<Value> Call( RV (T::*MemFunc)( A0) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0;  AC0 ac0;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<1>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0), Arguments const & argv )
    {
	return CallVoid<T,void, A0>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0>
    static Handle<Value> Call( void (T::*MemFunc)( A0), Arguments const & argv )
    {
        return CallVoid<T,void, A0>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0;  AC0 ac0;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<1>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0 >
    static Handle<Value> Call( void (T::*MemFunc)( A0) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0, RV(T::*MemFunc)( A0) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0, RV(T::*MemFunc)( A0) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0, VoidType (T::*MemFunc)( A0) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0, VoidType (T::*MemFunc)( A0) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0, RV (T::*Func)( A0) >
struct InvocableMemFunc1
{
    static const int Arity = 1;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0, RV (T::*Func)( A0) const>
struct InvocableConstMemFunc1
{
    static const int Arity = 1;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 2 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<2>
{
    static const int Arity = 2;
    template <typename T, typename RV,  typename A0,  typename A1>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1;  AC0 ac0; AC1 ac1;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<2>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1;  AC0 ac0; AC1 ac1;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<2>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1;  AC0 ac0; AC1 ac1;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<2>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1;  AC0 ac0; AC1 ac1;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<2>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1, RV(T::*MemFunc)( A0, A1) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1, RV(T::*MemFunc)( A0, A1) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1, VoidType (T::*MemFunc)( A0, A1) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1, VoidType (T::*MemFunc)( A0, A1) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1, RV (T::*Func)( A0, A1) >
struct InvocableMemFunc2
{
    static const int Arity = 2;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1, RV (T::*Func)( A0, A1) const>
struct InvocableConstMemFunc2
{
    static const int Arity = 2;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 3 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<3>
{
    static const int Arity = 3;
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2;  AC0 ac0; AC1 ac1; AC2 ac2;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<3>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2;  AC0 ac0; AC1 ac1; AC2 ac2;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<3>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2;  AC0 ac0; AC1 ac1; AC2 ac2;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<3>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1, A2>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2;  AC0 ac0; AC1 ac1; AC2 ac2;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<3>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2, RV(T::*MemFunc)( A0, A1, A2) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2, RV(T::*MemFunc)( A0, A1, A2) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2, VoidType (T::*MemFunc)( A0, A1, A2) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2, VoidType (T::*MemFunc)( A0, A1, A2) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2, RV (T::*Func)( A0, A1, A2) >
struct InvocableMemFunc3
{
    static const int Arity = 3;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2, RV (T::*Func)( A0, A1, A2) const>
struct InvocableConstMemFunc3
{
    static const int Arity = 3;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 4 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<4>
{
    static const int Arity = 4;
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<4>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<4>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<4>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1, A2, A3>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<4>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV(T::*MemFunc)( A0, A1, A2, A3) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV(T::*MemFunc)( A0, A1, A2, A3) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3, VoidType (T::*MemFunc)( A0, A1, A2, A3) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3, VoidType (T::*MemFunc)( A0, A1, A2, A3) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV (T::*Func)( A0, A1, A2, A3) >
struct InvocableMemFunc4
{
    static const int Arity = 4;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV (T::*Func)( A0, A1, A2, A3) const>
struct InvocableConstMemFunc4
{
    static const int Arity = 4;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 5 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<5>
{
    static const int Arity = 5;
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<5>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<5>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<5>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1, A2, A3, A4>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<5>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV(T::*MemFunc)( A0, A1, A2, A3, A4) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV(T::*MemFunc)( A0, A1, A2, A3, A4) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV (T::*Func)( A0, A1, A2, A3, A4) >
struct InvocableMemFunc5
{
    static const int Arity = 5;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV (T::*Func)( A0, A1, A2, A3, A4) const>
struct InvocableConstMemFunc5
{
    static const int Arity = 5;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 6 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<6>
{
    static const int Arity = 6;
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<6>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<6>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<6>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1, A2, A3, A4, A5>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<6>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV (T::*Func)( A0, A1, A2, A3, A4, A5) >
struct InvocableMemFunc6
{
    static const int Arity = 6;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV (T::*Func)( A0, A1, A2, A3, A4, A5) const>
struct InvocableConstMemFunc6
{
    static const int Arity = 6;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 7 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<7>
{
    static const int Arity = 7;
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<7>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<7>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<7>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<7>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV (T::*Func)( A0, A1, A2, A3, A4, A5, A6) >
struct InvocableMemFunc7
{
    static const int Arity = 7;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV (T::*Func)( A0, A1, A2, A3, A4, A5, A6) const>
struct InvocableConstMemFunc7
{
    static const int Arity = 7;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 8 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<8>
{
    static const int Arity = 8;
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<8>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<8>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<8>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<8>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV (T::*Func)( A0, A1, A2, A3, A4, A5, A6, A7) >
struct InvocableMemFunc8
{
    static const int Arity = 8;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV (T::*Func)( A0, A1, A2, A3, A4, A5, A6, A7) const>
struct InvocableConstMemFunc8
{
    static const int Arity = 8;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 9 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<9>
{
    static const int Arity = 9;
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<9>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<9>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<9>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7, A8>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<9>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7, A8>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV (T::*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8) >
struct InvocableMemFunc9
{
    static const int Arity = 9;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV (T::*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const>
struct InvocableConstMemFunc9
{
    static const int Arity = 9;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
/**
A helper class for forwarding JS arguments to member functions
taking 10 arguments.

@implements InvocableInterface
*/
template <>
struct MemFuncForwarder<10>
{
    static const int Arity = 10;
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( T * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8; typedef ArgCaster<A9> AC9;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8; AC9 ac9;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)(  ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]), ac9.ToNative(argv[9]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<10>::Call() Native function threw an unknown native exception type!"));
        }
    }
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    
    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( T const * obj, RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8; typedef ArgCaster<A9> AC9;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8; AC9 ac9;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            return CastToJS<RV>( (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]), ac9.ToNative(argv[9]) ) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<10>::Call() Native function threw an unknown native exception type!"));
        }
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( RV (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	return Call( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8; typedef ArgCaster<A9> AC9;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8; AC9 ac9;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]), ac9.ToNative(argv[9]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<10>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( T * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
	return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        T * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }


    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
         typedef ArgCaster<A0> AC0; typedef ArgCaster<A1> AC1; typedef ArgCaster<A2> AC2; typedef ArgCaster<A3> AC3; typedef ArgCaster<A4> AC4; typedef ArgCaster<A5> AC5; typedef ArgCaster<A6> AC6; typedef ArgCaster<A7> AC7; typedef ArgCaster<A8> AC8; typedef ArgCaster<A9> AC9;  AC0 ac0; AC1 ac1; AC2 ac2; AC3 ac3; AC4 ac4; AC5 ac5; AC6 ac6; AC7 ac7; AC8 ac8; AC9 ac9;
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
        try
        {
            (obj->*MemFunc)( ac0.ToNative(argv[0]), ac1.ToNative(argv[1]), ac2.ToNative(argv[2]), ac3.ToNative(argv[3]), ac4.ToNative(argv[4]), ac5.ToNative(argv[5]), ac6.ToNative(argv[6]), ac7.ToNative(argv[7]), ac8.ToNative(argv[8]), ac9.ToNative(argv[9]) );
        }
        catch( std::exception const & ex )
        {
            return ::v8::ThrowException( ::v8::String::New(ex.what()) );
        }
        catch( ... )
        {
            return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<10>::Call() Native function threw an unknown native exception type!"));
        }
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> Call( T const * obj, void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( obj, MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> CallVoid( VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        T const * obj = CastFromJS<T*>( argv.This() );
	if( ! obj ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): Native object is null!"));
	else if( argv.Length() < Arity ) return v8::ThrowException(v8::String::New("MemFuncForwarder::Call(): wrong argument count!"));
	Call( obj, MemFunc, argv );
	return Undefined();
    }
    template <typename T,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> Call( void (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        return CallVoid<T,void, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV(T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Call<T,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template <typename T, typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, VoidType (T::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return CallVoid<T,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV (T::*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) >
struct InvocableMemFunc10
{
    static const int Arity = 10;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
template <typename T, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV (T::*Func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const>
struct InvocableConstMemFunc10
{
    static const int Arity = 10;
    typedef MemFuncForwarder<Arity> Proxy;
    static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
    {
        return Proxy::template Call<T,RV>( Func, argv );
    }
    static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
    {
        return Proxy::template CallVoid<T,RV>( Func, argv );
    }
};
#endif // if !defined(DOXYGEN)
