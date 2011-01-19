// GENERATED CODE! Edit at your own risk!
#if !defined(DOXYGEN)
/**
A helper class for forwarding JS arguments to member functions
taking 1 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,1>
{
private:
    typedef MemFuncForwarder<1> Proxy;
public:
    static const int Arity = 1;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0>( MemFunc, argv );
    }

    template <typename RV,  typename A0>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0>( obj, MemFunc , argv );
    }

    template < typename A0>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0>( MemFunc, argv );
    }

    template < typename A0>
    static Handle<Value> Call( void (Type::*MemFunc)( A0), Arguments const & argv )
    {
        return Proxy::Call< A0>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0>( obj, MemFunc, argv );
    }

    template < typename A0 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0>( MemFunc, argv );
    }

    template < typename A0 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0>( MemFunc, argv );
    }

    template <typename RV,  typename A0, RV(Type::*MemFunc)( A0) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, MemFunc>( argv );
    }

    template <typename RV,  typename A0, RV(Type::*MemFunc)( A0) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0, VoidType (Type::*MemFunc)( A0) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0, VoidType (Type::*MemFunc)( A0) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 2 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,2>
{
private:
    typedef MemFuncForwarder<2> Proxy;
public:
    static const int Arity = 2;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1>( MemFunc, argv );
    }

    template < typename A0,  typename A1>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1), Arguments const & argv )
    {
        return Proxy::Call< A0, A1>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1>( MemFunc, argv );
    }

    template < typename A0,  typename A1 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1, RV(Type::*MemFunc)( A0, A1) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1, RV(Type::*MemFunc)( A0, A1) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1, VoidType (Type::*MemFunc)( A0, A1) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1, VoidType (Type::*MemFunc)( A0, A1) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 3 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,3>
{
private:
    typedef MemFuncForwarder<3> Proxy;
public:
    static const int Arity = 3;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1, A2>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2), Arguments const & argv )
    {
        return Proxy::Call< A0, A1, A2>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2, RV(Type::*MemFunc)( A0, A1, A2) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2, RV(Type::*MemFunc)( A0, A1, A2) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2, VoidType (Type::*MemFunc)( A0, A1, A2) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2, VoidType (Type::*MemFunc)( A0, A1, A2) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 4 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,4>
{
private:
    typedef MemFuncForwarder<4> Proxy;
public:
    static const int Arity = 4;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1, A2, A3>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3), Arguments const & argv )
    {
        return Proxy::Call< A0, A1, A2, A3>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV(Type::*MemFunc)( A0, A1, A2, A3) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3, RV(Type::*MemFunc)( A0, A1, A2, A3) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3, VoidType (Type::*MemFunc)( A0, A1, A2, A3) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3, VoidType (Type::*MemFunc)( A0, A1, A2, A3) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 5 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,5>
{
private:
    typedef MemFuncForwarder<5> Proxy;
public:
    static const int Arity = 5;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1, A2, A3, A4>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4), Arguments const & argv )
    {
        return Proxy::Call< A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV(Type::*MemFunc)( A0, A1, A2, A3, A4) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, RV(Type::*MemFunc)( A0, A1, A2, A3, A4) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 6 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,6>
{
private:
    typedef MemFuncForwarder<6> Proxy;
public:
    static const int Arity = 6;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1, A2, A3, A4, A5>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5), Arguments const & argv )
    {
        return Proxy::Call< A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 7 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,7>
{
private:
    typedef MemFuncForwarder<7> Proxy;
public:
    static const int Arity = 7;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5, A6>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1, A2, A3, A4, A5, A6>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6), Arguments const & argv )
    {
        return Proxy::Call< A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5, A6>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5, A6>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, A6, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, A6,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 8 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,8>
{
private:
    typedef MemFuncForwarder<8> Proxy;
public:
    static const int Arity = 8;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1, A2, A3, A4, A5, A6, A7>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7), Arguments const & argv )
    {
        return Proxy::Call< A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5, A6, A7>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5, A6, A7>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 9 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,9>
{
private:
    typedef MemFuncForwarder<9> Proxy;
public:
    static const int Arity = 9;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1, A2, A3, A4, A5, A6, A7, A8>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8), Arguments const & argv )
    {
        return Proxy::Call< A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5, A6, A7, A8>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5, A6, A7, A8>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8,MemFunc>( argv );
    }

};
/**
A helper class for forwarding JS arguments to member functions
taking 10 arguments.

@implements InvocableInterface
*/
template <typename T>
struct TMemFuncForwarder<T,10>
{
private:
    typedef MemFuncForwarder<10> Proxy;
public:
    static const int Arity = 10;
    typedef typename TypeInfo<T>::Type Type;

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( T * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( obj, MemFunc, argv );
    }
    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( Type const * obj, RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>(obj,MemFunc,argv);
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( RV (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        return Proxy::Call<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( obj, MemFunc , argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( Type * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        return Proxy::Call<Type,void, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9>
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Arguments const & argv )
    {
        return Proxy::Call< A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        return Proxy::CallVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( obj, MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> Call( Type const * obj, void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( obj, MemFunc, argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> CallVoid( VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        return Proxy::Call<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template < typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9 >
    static Handle<Value> Call( void (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Arguments const & argv )
    {
        return Proxy::Call<Type, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>( MemFunc, argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, MemFunc>( argv );
    }

    template <typename RV,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, RV(Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const >
    static Handle<Value> Invocable( Arguments const & argv )
    {
        return Proxy::Invocable<Type,RV, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9,MemFunc>( argv );
    }

    template <typename VoidType,  typename A0,  typename A1,  typename A2,  typename A3,  typename A4,  typename A5,  typename A6,  typename A7,  typename A8,  typename A9, VoidType (Type::*MemFunc)( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const >
    static Handle<Value> InvocableVoid( Arguments const & argv )
    {
        return Proxy::InvocableVoid<Type,VoidType, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9,MemFunc>( argv );
    }

};
#endif // if !defined(DOXYGEN)
