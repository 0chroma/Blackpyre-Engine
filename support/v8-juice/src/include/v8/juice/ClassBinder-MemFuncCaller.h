// GENERATED CODE! Edit at your own risk!
#if !defined(DOXYGEN)
template <>
struct WeakMemFuncCaller<1> : v8::juice::convert::MemFuncForwarder<1>
{
    enum { Arity = 1 };

    template <typename WeakWrappedType, typename RV,  typename A0 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<1>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<1>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<1>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<1>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<2> : v8::juice::convert::MemFuncForwarder<2>
{
    enum { Arity = 2 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<2>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<2>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<2>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<2>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<3> : v8::juice::convert::MemFuncForwarder<3>
{
    enum { Arity = 3 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1, A2), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<3>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1, A2) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<3>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1, A2), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<3>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1, A2) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<3>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<4> : v8::juice::convert::MemFuncForwarder<4>
{
    enum { Arity = 4 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1, A2, A3), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<4>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1, A2, A3) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<4>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1, A2, A3), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<4>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1, A2, A3) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<4>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<5> : v8::juice::convert::MemFuncForwarder<5>
{
    enum { Arity = 5 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<5>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<5>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<5>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<5>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<6> : v8::juice::convert::MemFuncForwarder<6>
{
    enum { Arity = 6 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<6>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<6>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<6>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<6>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<7> : v8::juice::convert::MemFuncForwarder<7>
{
    enum { Arity = 7 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<7>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<7>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<7>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<7>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<8> : v8::juice::convert::MemFuncForwarder<8>
{
    enum { Arity = 8 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<8>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<8>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<8>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<8>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<9> : v8::juice::convert::MemFuncForwarder<9>
{
    enum { Arity = 9 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<9>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<9>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<9>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<9>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
template <>
struct WeakMemFuncCaller<10> : v8::juice::convert::MemFuncForwarder<10>
{
    enum { Arity = 10 };

    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<10>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<10>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<10>::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<10>::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
#endif // if !defined(DOXYGEN)
