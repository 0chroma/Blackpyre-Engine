#if !defined(CODE_GOOGLE_COM_P_V8_JUICE_CLASSBINDER_H_INCLUDED)
#define CODE_GOOGLE_COM_P_V8_JUICE_CLASSBINDER_H_INCLUDED 1
/*
   A JS/C++ class binding mechanism based on the juice::convert framework.

   Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)

   License: Public Domain
*/

#include <v8.h>
#include <v8/juice/convert.h>
#include <v8/juice/WeakJSClassCreator.h>
#include <v8/juice/forwarding.h>
#include <stdexcept>
namespace v8 {
namespace juice {

#if !defined(DOXYGEN)
    namespace Detail
    {
	using namespace v8;
	using namespace v8::juice;
	using namespace v8::juice::convert;

        /**
           Useless base instantiation - See the 0-specialization for details.
        */
        template <int Arity>
	struct WeakMemFuncCaller
        {};
	/**
	   A helper type for forwarding function calls on objects bound via WeakJSClassCreator
	   through native member functions. This type supports only nullary functions, and
	   the generated classes WeakMemFuncCaller(1..N) each provide support for a different
	   number of arguments.
	*/
        template <>
	struct WeakMemFuncCaller<0> : v8::juice::convert::MemFuncForwarder<0>
	{
	    template <typename WeakWrappedType, typename RV>
	    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)(), Arguments const & argv )
	    {
		typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
		//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
                typedef typename Wrapper::WrappedType WT;
                WT * obj = CastFromJS<WT>( argv.This() );
		if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<0>::Call() could not find native 'this' object!"));
		return Call( obj, func, argv );
	    }

	    template <typename WeakWrappedType, typename RV>
	    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)() const, Arguments const & argv )
	    {
		typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
		//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
                typedef typename Wrapper::WrappedType WT;
                WT * obj = CastFromJS<WT>( argv.This() );
		if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<0>::Call() could not find native 'this' object!"));
		return Call( obj, func, argv );
	    }

	    template <typename WeakWrappedType>
	    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)(), Arguments const & argv )
	    {
		typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
		//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
                typedef typename Wrapper::WrappedType WT;
                WT * obj = CastFromJS<WT>( argv.This() );
		if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<0>::Call() could not find native 'this' object!"));
		return Call( obj, func, argv );
	    }

	    template <typename WeakWrappedType>
	    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)() const, Arguments const & argv )
	    {
		typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
		//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
                typedef typename Wrapper::WrappedType WT;
                WT * obj = CastFromJS<WT>( argv.This() );
		if( ! obj ) return ThrowException(String::New("WeakMemFuncCaller<0>::Call() could not find native 'this' object!"));
		return Call( obj, func, argv );
	    }
	};

#include "ClassBinder-MemFuncCaller.h" // generated code

	/** An internal helper type for converting v8::Arguments to native args
	    and passing them on to the given native member function. This type
	    supports only functions with no arguments. The generated classes
	    MemFuncCallOp(1..N) add support for various argument counts.
	*/
	template <typename T, typename RV, RV (T::*Func)()  >
	struct MemFuncCallOp0
	{
	    typedef T Type;
	    enum { Arity = 0 };
	    typedef RV (T::*FuncSig)();
	    typedef WeakMemFuncCaller<0> OpBase;
	    static Handle<Value> Call( Type * obj, Arguments const & argv )
	    {
		return OpBase::Call( obj, Func, argv );
	    }
	    static Handle<Value> CallOnWeakSelf( Arguments const & argv )
	    {
		return OpBase::CallOnWeakSelf<Type>( Func, argv );
	    }
	};

	/** Specializations for const members. */
	template <typename T, typename RV, RV (T::*Func)() const>
	struct MemFuncCallOp0<const T,RV,Func>
	{
	    typedef T Type;
	    enum { Arity = 0 };
	    typedef WeakMemFuncCaller<0> OpBase;
	    static Handle<Value> Call( Type const * obj, Arguments const & argv )
	    {
		if( ! obj ) return ThrowException(String::New("MemFuncCallOp0::Call(): Native object is null!"));
		return convert::CastToJS( (RV) (obj->*Func)() );
	    }
	    static Handle<Value> CallOnWeakSelf( Arguments const & argv )
	    {
		return OpBase::CallOnWeakSelf<const Type>( Func, argv );
	    }
	};

	/** Specializations for members returning void. */
	template <typename T, void (T::*Func)()>
	struct MemFuncCallOp0<T, void, Func >
	{
	    typedef T Type;
	    typedef WeakMemFuncCaller<0> OpBase;
	    static Handle<Value> Call( Type * obj, Arguments const & argv )
	    {
		//if( ! obj ) return ThrowException(String::New("MemFuncCallOp0::Call(): Native object is null!"));
		return OpBase::Call( obj, Func, argv );
	    }
	    static Handle<Value> CallOnWeakSelf( Arguments const & argv )
	    {
		return OpBase::CallOnWeakSelf<Type>( Func, argv );
	    }
	};

	/** Specializations for const members returning void. */
	template <typename T, void (T::*Func)() const>
	struct MemFuncCallOp0<const T, void, Func >
	{
	    typedef T Type;
	    typedef WeakMemFuncCaller<0> OpBase;
	    static Handle<Value> Call( Type const * obj, Arguments const & argv )
	    {
		return OpBase::Call( obj, Func, argv );
	    }
	    static Handle<Value> CallOnWeakSelf( Arguments const & argv )
	    {
		return OpBase::CallOnWeakSelf<const Type>( Func, argv );
	    }
	};

#include "ClassBinder-MemFuncCallOps.h" // generated code

	/**
	   Helper used by ClassBinder::AddMemberFunc(). CallOpType
	   must be an existing MemFuncCallOpN type, where N is an
	   integer value.
	*/
	template <typename CallOpType>
	struct MemFuncCallOp
	{
            /**
               Tries to forward argv on via
               CallOpType::CallOnWeakSelf().  If that function throws
               or propagates a native exception, this routine will
               catch it and convert it into a JS exception.
            */
	    static Handle<Value> Call( Arguments const & argv )
	    {
                try
                {
                    return CallOpType::CallOnWeakSelf( argv );
                }
                catch( std::exception const & ex )
                {
                    return ThrowException(String::New(ex.what()));
                }
                catch( ... )
                {
                    return ThrowException(String::New("Native function threw an unknown native exception type!"));
                }
                return Undefined(); // cannot be reached.
	    }
	};
    }
#endif // DOXYGEN

#if 0 // not yet read for prime-time
    /**
    */
    template <typename WrappedType, typename RV, RV (WrappedType::*Func)()>
    void WeakBindMemFunc( WeakJSClassCreator<WrappedType> & tgt, char const * name )
    {
	typedef Detail::MemFuncCallOp0< WrappedType, RV, Func > Caller;
	tgt.Set(name, Detail::MemFuncCallOp<Caller>::Call );
    }
    
    /**
       Overloaded to handle const member functions.
    */
    template <typename WrappedType,typename RV, RV (WrappedType::*Func)() const>
    void WeakBindMemFunc( WeakJSClassCreator<WrappedType> & tgt, char const * name )
    {
	typedef Detail::MemFuncCallOp0< const typename WeakJSClassCreator<WrappedType>::WrappedType, RV, Func > Caller;
	tgt.Set(name, Detail::MemFuncCallOp<Caller>::Call );
    }

    template <typename NativeType, typename RV>
    Handle<Value> CallWeakMemFunc( RV (NativeType::*MemFunc)(), Arguments const & argv  )
    {
	typedef Detail::WeakMemFuncCaller<0> Caller;
	return Caller::CallOnWeakSelf<NativeType>( MemFunc, argv );
    }
    template <typename NativeType, typename RV>
    Handle<Value> CallWeakMemFunc( const RV (NativeType::*MemFunc)() const, Arguments const & argv )
    {
	typedef Detail::WeakMemFuncCaller<0> Caller;
	return Caller::CallOnWeakSelf<const NativeType>( MemFunc, argv );
    }
#endif


    /**
       This template can be used as an argument to
       v8::ObjectTemplate::SetAccessor()'s Getter parameter to
       generically tie a native member variable to a JS value.

       Requirements:

       - (WrappedType*) must be convertible via CastFromJS<WrappedType>().
       - PropertyType must be convertible via CastToJS<PropertyType>().

       If the underlying native This object cannot be found then this
       routine will trigger a JS exception.

       Example:

       Assume we have a native type Foo with a std::string member
       called str. We can bind the member variable with:

       \code
       myObjectTemplate.SetAccessor("foo",
               MemberVarGetter<Foo,std::string,&Foo::str>,
               MemberVarSetter<Foo,std::string,&Foo::str> );
       \endcode

       When using the JSClassWrapper interface, these can be passed to the
       Set() overload which takes accessor information. e.g.:

       \code
       wrapper.Set( "str",
                    MemberVarGetter<Foo,std::string, &Foo::str>,
                    MemberVarSetter<Foo,std::string, &Foo::str> );
       \endcode

       In almost 10 years of C++ coding, this is the first time i've ever had
       a use for a pointer-to-member.
    */
    template <typename WrappedType, typename PropertyType, PropertyType WrappedType::*MemVar>
    Handle<Value> MemberVarGetter(Local<String> property, const AccessorInfo &info)
    {
        WrappedType * self = convert::CastFromJS<WrappedType>( info.This() );
        if( ! self ) return v8::ThrowException( v8::String::New( "Native member property getter could not access native This object!" ) );
        return convert::CastToJS( (self->*MemVar) );
    }

    /**
       This is the Setter counterpart of MemberVarGetter(). See
       that function for most of the details.

       Requirements:

       - (WrappedType*) must be convertible via CastFromJS<WrappedType>().
       - PropertyType must be convertible via CastFromJS<PropertyType>().

       If the underlying native This object cannot be found then this
       routine will trigger a JS exception, though it is currently
       unclear whether this is actually legal in v8 (and difficult to
       test, since the native bindings work so well ;).
    */
    template <typename WrappedType, typename PropertyType, PropertyType WrappedType::*MemVar>
    void MemberVarSetter(Local<String> property, Local<Value> value, const AccessorInfo& info)
    {
        WrappedType * self = convert::CastFromJS<WrappedType>( info.This() );
        if( self )
        {
            self->*MemVar = convert::CastFromJS<PropertyType>( value );
        }
        else
        {
            // It is legal to do this from here?
            ::v8::ThrowException(v8::String::New("Native member property setter could not access native This object!"));
        }
    }

    /**
       ClassBinder is a WeakJSClassCreator subclass which adds some
       binding features which required other v8::juice APIs (as opposed
       to WeakJSClassCreator, which requires only core v8 functionality).

       The extended functionality includes support for binding member
       functions of the wrapped type. It has some limitations on the
       automatic type conversion (see convert::CastToJS() and
       convert::CastFromJS(), as those are used for all casting).
       It does handle void return values, though CastFromJS()
       does not.

       Example (see also: WeakJSClassCreator)

       \code
       typedef ClassBinder<MyType> WC;
       WC c( "MyType", objectToAddClassTo );
       c.Set(...)
         .BindMemFunc<void,&MyType::doSomething>("doSomething")
         .Seal(); // must be the last call made on this object.
       \endcode

       That's all there is to it. More functionality is provided via
       the base classes.

       If you've got some weird arguments which cannot be used through
       the casting system, you may be able to partially work around it
       by creating a very thin wrapper class around the to-be-wrapped
       type, make the appropriate conversions there, and use that
       proxy to access the real object.

       Tip: if a compiler error tells you that there's "no matching
       function BindMemFunc()" then one or more of the template types
       passed to BindMemFunc() does not match the exact function
       signature of the function pointer template parameter.
    */
    template <typename WrappedT>
    class ClassBinder : public WeakJSClassCreator<WrappedT>
    {
    public:
	/** Convenience typedef. */
	typedef WeakJSClassCreator<WrappedT> ParentType;
	/**
	   The actual wrapped native type, which may differ from the
	   WrappedT template parameter. It is always the same as
	   WeakJSClassCreatorOps<WrappedT>::WrappedType.

	   It is sometimes useful to hide some internal native type
	   (or opaque pointer type) via a marker class, in which case
	   this type would be passed MyMarkerClass as the template
	   type and the ops specialization would define WrappedType
	   to be the internal type. This has proven useful in the
	   i/o plugin, where we don't want to expose the underlying
	   i/o library implementation to potential users.
	*/
	typedef typename ParentType::WrappedType WrappedType;
	/**
	   Convenience typedef. Always the same as
	   WeakJSClassCreatorOps<WrappedT>.
	*/
	typedef typename ParentType::ClassOpsType ClassOpsType;

	/**
	   Identical to the parent class ctor with the same signature.
	*/
	explicit ClassBinder( Handle<Object> target )
	    : ParentType( target )
	{
	}

	/**
	   Identical to the parent class ctor with the same signature.
	*/
	explicit ClassBinder()
	    : ParentType()
	{
	}

        /** Does nothing. Is virtual to satisfy inheritance rules and please my compiler. */
	virtual ~ClassBinder() {}

        /** Experimental - don't use. */
        static ClassBinder & Instance()
        {
            static ClassBinder shared_inst;
            return shared_inst;
        }

        /**
           Binds the member specified as a template parameter. Note that
           the signature is that defined by the convert::InvocationCallbackMember
           type.
        */
        template < Handle<Value> (WrappedType::*Func)( Arguments const & ) >
        ClassBinder & BindMemFunc( char const * name )
        {
            this->Set(name, convert::InvocationCallbackMember<WrappedType,Func>::Invocable );
            return *this;
        }

        /**
           Binds automatically-generated getter/setter functions to the given
           member variable. See MemberVarGetter() and MemberVarSetter()
           for the requirements of the templatized types.

           If you only want to bind one of the getter OR the setter then
           use the 5-argument variant of Set() instead and pass MemberVarGetter
           or MemberVarGetter, as appropriate, to that function.
        */
        template <typename VarType, VarType WrappedType::*MemVar >
        ClassBinder & BindMemVar( char const * name,
                                  AccessControl settings = v8::PROHIBITS_OVERWRITING,
                                  PropertyAttribute attribute = v8::DontDelete
                                  )
        {
            this->Set( name,
                       MemberVarGetter<WrappedType,VarType,MemVar>,
                       MemberVarSetter<WrappedType,VarType,MemVar>,
                       v8::Handle< v8::Value >(), settings, attribute );
            return *this;
        }

	/**
	   Binds the member function Func to the given name.
	*/
	template <typename RV, RV (WrappedType::*Func)()>
	ClassBinder & BindMemFunc( char const * name )
	{
	    typedef Detail::MemFuncCallOp0< WrappedType, RV, Func > Caller;
	    this->Set(name, Detail::MemFuncCallOp<Caller>::Call );
	    return *this;
	}

	/**
	   Overload requiring a WrappedType const member function taking no
	   arg and returning RV.
	*/
	template <typename RV, RV (WrappedType::*Func)() const>
	ClassBinder & BindMemFunc( char const * name )
	{
	    typedef Detail::MemFuncCallOp0< const WrappedType, RV, Func > Caller;
	    this->Set(name, Detail::MemFuncCallOp<Caller>::Call );
	    return *this;
	}

    private:
        /**
            Internal implementation helper for BindPropToAccessors() and
            BindPropToGetter().

            Implements v8::AccessorGetter interface to proxy a given
            property through a WrappedType member function.
        */
	template <typename RV, RV (WrappedType::*Func)() const>
        static Handle<Value> propGetter( Local< String > /*ignored*/, const AccessorInfo & info )
        {
            WrappedType * self = convert::CastFromJS<WrappedType>( info.This() );
            if( ! self ) return v8::ThrowException( v8::String::New( "Native member property getter could not access native This object!" ) );
            return convert::CastToJS( (self->*Func)() );
        }
        /**
           Overload to allow a non-const getter.
        */
	template <typename RV, RV (WrappedType::*Func)()>
        static Handle<Value> propGetter( Local< String > /*ignored*/, const AccessorInfo & info )
        {
            WrappedType * self = convert::CastFromJS<WrappedType>( info.This() );
            if( ! self ) return v8::ThrowException( v8::String::New( "Native member property getter could not access native This object!" ) );
            return convert::CastToJS( (self->*Func)() );
        }

        /**
            Internal implementation helper for BindPropToAccessors() and
            BindPropToGetter().

            Implements v8::AccessorSetter interface to proxy a given
            property through a WrappedType member function.
        */
        template <typename RV, typename ArgT, RV (WrappedType::*Func)(ArgT)>
        static void propSetter(v8::Local< v8::String > property, v8::Local< v8::Value > value, const v8::AccessorInfo &info)
        {
            WrappedType * self = convert::CastFromJS<WrappedType>( info.This() );
            if( ! self )
            {
                v8::ThrowException( v8::String::New( "Native member property getter could not access native This object!" ) );
                return;
            }
            (self->*Func)( convert::CastFromJS<ArgT>( value ) );
            return;
        }

    public:
        /**
           EXPERIMENTAL!

           Binds the given JS property to a pair of WrappedType member
           functions, such that these functions will be called in
           place of get/set operations for the property.
           
           The native member functions must follow conventional
           accessor signatures:

           - Getter: T getter() const
           - Setter: [T1 or void] setter( T2 )

           For the setter, T1 may differ from T2 and T1 may be
           void. However, any return value is ignored by the JS engine
           for purposes of setting the value.

           For the getter, an overload of this function is provided which
           supports a non-const getter.

           TODOs:

           - Various convenience overloads for the case that the
           getter/setter deal strictly with the same arg types.
        */
	template <typename RV,
                  RV (WrappedType::*Getter)() const,
                  typename SetRV,
                  typename ArgV,
                  SetRV (WrappedType::*Setter)(ArgV)
            >
	ClassBinder & BindPropToAccessors( char const * propName )
	{
	    this->Prototype()->SetAccessor( v8::String::New( propName ),
                                            propGetter<RV,Getter>,
                                            propSetter<SetRV,ArgV,Setter>
                                           );
	    return *this;
	}

        /**
           Overload to allow a non-const getter.
        */
	template <typename RV,
                  RV (WrappedType::*Getter)(),
                  typename SetRV,
                  typename ArgV,
                  SetRV (WrappedType::*Setter)(ArgV)
            >
	ClassBinder & BindPropToAccessors( char const * propName )
	{
	    this->Prototype()->SetAccessor( v8::String::New( propName ),
                                            propGetter<RV,Getter>,
                                            propSetter<SetRV,ArgV,Setter>
                                           );
	    return *this;
	}

        /**
           This is like BindPropToAccessors(), but MUST NOT be used in
           conjunction with that function: use EITHER this function
           (to only set a getter), OR BindPropToAccessors() to set
           both a getter and a setter. It is not possible to apply
           only a setter because v8 craps out on read access to the
           property if we do that.
        */
	template <typename RV, RV (WrappedType::*Getter)() const >
	ClassBinder & BindPropToGetter( char const * propName )
	{
	    this->Prototype()->SetAccessor( v8::String::New( propName ),
                                            propGetter<RV,Getter>
                                           );
	    return *this;
	}
        /**
           Overload to allow non-const getter.
        */
	template <typename RV, RV (WrappedType::*Getter)() >
	ClassBinder & BindPropToGetter( char const * propName )
	{
	    this->Prototype()->SetAccessor( v8::String::New( propName ),
                                            propGetter<RV,Getter>
                                           );
	    return *this;
	}

#if 0
#error "This cannot work because we MUST have a getter to bind to or get a crash in v8 on read access to the property."
        template <typename RV,
                  typename ArgT,
                  RV (WrappedType::*Setter)(ArgT)
            >
	ClassBinder & BindPropToSetter( char const * propName )
	{
	    this->Prototype()->SetAccessor( v8::String::New( propName ),
                                            0,
                                            propSetter<RV,ArgT,Setter>
                                           );
	    return *this;
	}
#endif

#include "ClassBinder-BindMemFunc.h" // generated code

    }; // class ClassBinder


}} /* namespaces */

#endif /* CODE_GOOGLE_COM_P_V8_JUICE_CLASSBINDER_H_INCLUDED */
