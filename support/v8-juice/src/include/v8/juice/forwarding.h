#if !defined(CODE_GOOGLE_COM_P_V8_V8_FORWARDING_H_INCLUDED)
#define CODE_GOOGLE_COM_P_V8_V8_FORWARDING_H_INCLUDED 1
/*
   A mini-framework to simplify casting between v8 JavaScript and
   C++ native objects. Requires the v8-juice bind.h and convert.h
   parts.

   v8: http://code.google.com/p/v8/

   Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)

   License: same as v8 (see below)
*/
// Copyright 2007-2008 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <vector>
#include "convert.h"
namespace v8 { namespace juice { namespace convert {
    using namespace v8;

#if ! defined(DOXYGEN)
    /** Internal library details. */
    namespace Detail
    {

    }
#endif // !DOXYGEN


    /**
       This class is not implemented, but exists solely to document
       the interface expected by many of the function binding
       templates.
    */
    struct InvocableInterface
    {
        /**
           A v8::InvocationCallback function.
        */
        static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv );
        /**
           Must hold the number of arguments expected by this handler.
           In some special cases it may be negative, but not in the
           general case.

           This _should_ be an enum instead of a static int, but when i
           do that, the member is not found (don't understand why) in
           many algorithms!
        */
        static const int Arity = 0;
    };

    /**
       Base instantiation of a helper to forward v8::Arguments
       to arbitrary functors. Must be specialized to be useful.

       Arity is the minimum number of arguments the functor expects.
       RV is the return type. A partial specializations void RV=void
       is installed to support functions which return void.
    */
    template <int Arity_,typename RV>
    struct FunctorForwarder
    {
        enum { Arity = Arity_ };
    };

    /** Specialization for functors taking no arguments. */
    template <typename RV>
    struct FunctorForwarder<0,RV>
    {
        enum { Arity = 0 };
        template <typename Func>
        static Handle<Value> Call( Func f )
        {
            try
            {
                return CastToJS<RV>( f() );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("Native function threw an unknown native exception type!"));
            }
            return Undefined(); // cannot be reached.
        }
        template <typename Func>
        static Handle<Value> Call( Func f, ::v8::Arguments const & /*ignored*/ )
        {
            return Call( f );
        }
    };

    /** Specialization for functor taking no arguments and returning void. */
    template <>
    struct FunctorForwarder<0,void>
    {
        enum { Arity = 0 };
        template <typename Func>
        static Handle<Value> Call( Func f )
        {
            try
            {
                f();
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("Native function threw an unknown native exception type!"));
            }
            return Undefined(); // cannot be reached.
        }
        template <typename Func>
        static Handle<Value> Call( Func f, v8::Arguments const & argv )
        {
            return Call( f );
        }
    };


    /**
       This is the documentation for the whole family of FwdToFuncN()
       functions, where N is some positive integer.

       Uses CastFromJS() to convert function arguments for the given
       function. The return result is then cast to JS using
       CastToJS(), and returned.

       This routine will only work with types which work with
       CastFromJS() and CastToJS().

       For all functions of this family (FwdToFunc2(), etc.), if
       argv.Length() is not *exactly* the correct number then a
       JS-side exception is thrown - the return value will be that of
       ::v8::ThrowException() (what exactly that return value is,
       isn't really documented :/).

       Notable limitations:

       - Can only convert argument types handled by CastFromJS().

       Some of the related limitations (e.g. can't handle void
       returns) can be solved by adding another level or two of
       template-based indirection. Maybe that will happen someday,
       maybe not.
    */
    template <typename ReturnT, typename Func>
    ::v8::Handle< ::v8::Value > FwdToFunc0( Func func, ::v8::Arguments const & argv )
    {
        return FunctorForwarder<0,ReturnT>::Call( func, argv );
    }

    /**
       Functionally identical to FwdToFunc0(), but the return type can
       be deduced by the compiler.
    */
    template <typename ReturnT>
    ::v8::Handle< ::v8::Value > FwdToFunc( ReturnT (*func)(), ::v8::Arguments const & /*ignored*/ )
    {
        return FunctorForwarder<0,ReturnT>::Call( func );
    }

#if !defined(DOXYGEN)
#include "forwarding-FunctorForwarder.h" // generated specializations for FunctorForwarder
#endif
    
    /**
       Useless base instantiation - See the 0-specialization for details.
    */
    template <int Arity_>
    struct MemFuncForwarder
    {
        enum { Arity = Arity_ };
    };


    /**
       A helper type for forwarding JS arguments to native member
       functions taking 0 arguments. The classes
       MemFuncForwarder<1..N> are generated code and follow this
       class' API.

       Each specialization of this class handles the cases for N
       arguments, where N is the templatized value, or arity of the
       functions.
       
       All variants of this class except the 0-arity one throw a
       JS-side exception if the argument list does not have at least
       the required number of parameters.


       The various Call() overloads can be used to forward JS calls to
       member functions.

       The Invocable() members can be used with
       v8::FunctionTemplate::New(FunctionForwarder<N>::Invocable<...>)
       to bind member functions to JS objects. For this to work,
       CastFromJS<T*>(argv.This()) must be able to return a native
       "this" object to call the function on.


       FIXME: add try/catch wrappers and convert native exceptions to
       JS exceptions.
    */
    template <>
    struct MemFuncForwarder<0>
    {
        enum { Arity = 0 };
        
        /**
           Calls (obj->*MemFunc)() and returns its to-JS-converted
           value. If !obj then a JS exception is triggered.
        */
        template <typename T, typename RV>
        static Handle<Value> Call( T * obj, RV (T::*MemFunc)(), Arguments const & argv )
        {
            if( ! obj ) return ThrowException(String::New("MemFuncForwarder<0>::Call(): Native object is null!"));
            //else if( argv.Length() < Arity ) return ThrowException(String::New("${callBase}::Call(): wrong argument count!"));
            try
            {
                return CastToJS<RV>( (obj->*MemFunc)() );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<0>::Call() Native function threw an unknown native exception type!"));
            }
        }

        /**
           Tries to extract a (T*) from argv using
           CastFromJS(argv.This()). On success, it calls Call(
           thatObject, MemFunc, argv ). On error (e.g. !obj) it throws
           a JS-side exception.
           
        */
        template <typename T, typename RV>
        static Handle<Value> Call( RV (T::*MemFunc)(), Arguments const & argv )
        {
            T * obj = CastFromJS<T*>( argv.This() );
            if( ! obj ) return ThrowException(String::New("MemFuncForwarder<0>::Call(): Native object is null!"));
            return Call( obj, MemFunc, argv );
        }
        
        /**
           Const overload. See the non-const variant for the docs.
        */
        template <typename T, typename RV>
        static Handle<Value> Call( T const * obj, RV (T::*MemFunc)() const, Arguments const & argv )
        {
            if( ! obj ) return ThrowException(String::New("MemFuncForwarder<0>::Call(): Native object is null!"));
            try
            {
                return CastToJS<RV>( (obj->*MemFunc)() );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("MemFuncForwarder<0>::Call() Native function threw an unknown native exception type!"));
            }
        }

        /**
           Tries to extract a (T*) from argv using CastFromJS(argv.This()). On success, it calls
           Call( thatObject, MemFunc, argv ). On error it throws a JS-side exception.
        */
        template <typename T, typename RV>
        static Handle<Value> Call( RV (T::*MemFunc)() const, Arguments const & argv )
        {
            T const * obj = CastFromJS<T*>( argv.This() );
            if( ! obj ) return ThrowException(String::New("MemFuncForwarder<0>::Call(): Native object is null!"));
            return Call( obj, MemFunc, argv );
        }

        /**
           Calls (obj->*MemFunc()) and discards the return value. If
           !obj then a JS exception is triggered.
        */
        template <typename T, typename VoidType>
        static Handle<Value> CallVoid( T * obj, VoidType (T::*MemFunc)(), Arguments const & argv )
        {
            if( ! obj ) return ThrowException(String::New("MemFuncForwarder<0>::Call(): Native object is null!"));
            (obj->*MemFunc)();
            return Undefined();
        }

        /**
           Identical to CallVoid(), and only exists because it
           incidentally allows the Invocable() function to work
           properly when RV==void.
        */
        template <typename T>
        static Handle<Value> Call( T * obj, void (T::*MemFunc)(), Arguments const & argv )
        {
            return CallVoid<T,void>( obj, MemFunc, argv );
        }


        /**
           Tries to extract a (T*) from argv using
           CastFromJS(argv.This()). On success, it calls
           Call(thatObject,MemFunc,argv). On error it throws a JS-side
           exception. The return value of the native function is
           discarded, and it need not be a CastToJS()'able type.
        */
        template <typename T,typename VoidType>
        static Handle<Value> CallVoid( VoidType (T::*MemFunc)(), Arguments const & argv )
        {
            T * obj = CastFromJS<T*>( argv.This() );
            if( ! obj ) return ThrowException(String::New("MemFuncForwarder<0>::Call(): Native object is null!"));
            Call( obj, MemFunc, argv );
            return v8::Undefined();
        }

        /**
           Identical to CallVoid(), and only exists because it
           incidentally allows the Invocable() function to work
           properly when RV==void.
        */
        template <typename T>
        static Handle<Value> Call( void (T::*MemFunc)(), Arguments const & argv )
        {
            return CallVoid<T,void>( MemFunc, argv );
        }

        /**
           Const overload. See the non-const variant for the docs.
        */
        template <typename T, typename VoidType>
        static Handle<Value> CallVoid( T const * obj, VoidType (T::*MemFunc)() const, Arguments const & argv )
        {
            if( ! obj ) return ThrowException(String::New("MemFuncForwarder<0>::Call(): Native object is null!"));
            //else if( argv.Length() < Arity ) return ThrowException(String::New("${callBase}::Call(): wrong argument count!"));
            (obj->*MemFunc)();
            return Undefined();
        }
        /**
           Identical to CallVoid(), and only exists because it
           incidentally allows the Invocable() function to work
           properly when RV==void.
        */
        template <typename T>
        static Handle<Value> Call( T const * obj, void (T::*MemFunc)() const, Arguments const & argv )
        {
            return CallVoid<T,void>( obj, MemFunc, argv );
        }

        /**
           Tries to extract a (T*) from argv using
           CastFromJS(argv.This()). On success, it calls Call(
           thatObject, MemFunc, argv ). On error it throws a JS-side
           exception. It discards the native return value and returns
           JS Undefined.
        */
        template <typename T, typename VoidType>
        static Handle<Value> CallVoid( VoidType (T::*MemFunc)() const, Arguments const & argv )
        {
            T const * obj = CastFromJS<T*>( argv.This() );
            if( ! obj ) return ThrowException(String::New("MemFuncForwarder<0>::Call(): Native object is null!"));
            Call( obj, MemFunc, argv );
            return v8::Undefined();
        }
        /**
           Identical to CallVoid(), and only exists because it
           incidentally allows the Invocable() function to work
           properly when RV==void.
        */
        template <typename T>
        static Handle<Value> Call( void (T::*MemFunc)() const, Arguments const & argv )
        {
            return CallVoid<T,void>( MemFunc, argv );
        }

        /**
           Calls Call( MemFunc, argv ). Implements the
           v8::InvocationCallback interface.
        */
        template <typename T, typename RV, RV (T::*MemFunc)() >
        static Handle<Value> Invocable( Arguments const & argv )
        {
            return Call( MemFunc, argv );
        }

        /**
           Calls Call( MemFunc, argv ). Implements the
           v8::InvocationCallback interface.
        */
        template <typename T, typename RV, RV (T::*MemFunc)() const >
        static Handle<Value> Invocable( Arguments const & argv )
        {
            return Call<T,RV>( MemFunc, argv );
        }

        /**
           Calls CallVoid( MemFunc, argv ). Implements the
           v8::InvocationCallback interface.
        */
        template <typename T, typename VoidType, VoidType (T::*MemFunc)() >
        static Handle<Value> InvocableVoid( Arguments const & argv )
        {
            return Call<T,VoidType>( MemFunc, argv );
        }

        /**
           Calls CallVoid( MemFunc, argv ). Implements the
           v8::InvocationCallback interface.
        */
        template <typename T, typename VoidType, VoidType (T::*MemFunc)() const >
        static Handle<Value> InvocableVoid( Arguments const & argv )
        {
            return CallVoid<T,VoidType>( MemFunc, argv );
        }
    };

    /**
       A helper class for storing type information for JS member
       function call forwarding.

       RV is the return value type of the templatized function.
     */
    template <typename T,typename RV, RV (T::*Func)()>
    struct InvocableMemFunc0
    {
        /**
           The number of arguments Func requires.
         */
        static const int Arity = 0;
        /** Returns FunctionForwarder<Arity>::Call<T>( Func, argv ). */
        static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
        {
            return MemFuncForwarder<Arity>::Call<T,RV>( Func, argv );
        }
        /** Returns FunctionForwarder<Arity>::CallVoid<T>( Func, argv ). */
        static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
        {
            return MemFuncForwarder<Arity>::CallVoid<T,RV>( Func, argv );
        }
    };

    /**
       An variant of InvocableMemFunc0 which is unfortunately
       necessary for handling const member functions.
    */
    template <typename T,typename RV,RV (T::*Func)() const>
    struct InvocableConstMemFunc0
    {
        /**
           The number of arguments Func requires.
         */
        static const int Arity = 0;
        /** Returns FunctionForwarder<Arity>::Call<T>( Func, argv ). */
        static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
        {
            return MemFuncForwarder<Arity>::Call<T,RV>( Func, argv );
        }
        /** Returns FunctionForwarder<Arity>::CallVoid<T>( Func, argv ). */
        static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
        {
            return MemFuncForwarder<Arity>::CallVoid<T,RV>( Func, argv );
        }
    };

//#if !defined(DOXYGEN)
#include "forwarding-MemFuncForwarder.h" // generated specializations for MemFuncForwarder
//#endif
    /**
       Useless base instantiation. See TMemFuncForwarder<0> for the
       docs.
    */
    template <typename T, int Arity_>
    struct TMemFuncForwarder
    {
        enum { Arity = -1 };
    };

    /**
       This type works exactly like MemFuncForwarder, but is
       templatized on both T and the function arity, whereas
       MemFuncForwarder is only templatized on arity.

       All functions in this intereface correspond 1-to-1 to
       MemFuncForwarder functions, and have the same signatures minus
       the initial T template argument.
    */
    template <typename T>
    struct TMemFuncForwarder<T,0>
    {
    public:
        enum { Arity = 0 };
        typedef typename TypeInfo<T>::Type Type;
    private:
        // WTF?? leads to compile errors: typedef MemFuncForwarder<Arity> Proxy;
        typedef MemFuncForwarder<0> Proxy;
    public:

        template <typename RV>
        static v8::Handle<v8::Value> Call( Type * obj, RV (Type::*MemFunc)(), Arguments const & argv )
        {
            return Proxy::Call<Type,RV>( obj, MemFunc, argv );
        }

        template <typename RV>
        static v8::Handle<v8::Value> Call( RV (Type::*MemFunc)(), Arguments const & argv )
        {
            return Proxy::Call<Type,RV>( MemFunc, argv );
        }
        
        template <typename RV>
        static v8::Handle<v8::Value> Call( Type const * obj, RV (Type::*MemFunc)() const, Arguments const & argv )
        {
            return Proxy::Call<Type,RV>( obj, MemFunc, argv );
        }

        template <typename RV>
        static v8::Handle<v8::Value> Call( RV (Type::*MemFunc)() const, Arguments const & argv )
        {
            return Proxy::Call<Type,RV>( MemFunc, argv );
        }

        template <typename VoidType>
        static v8::Handle<v8::Value> CallVoid( Type * obj, VoidType (Type::*MemFunc)(), Arguments const & argv )
        {
            return Proxy::CallVoid<Type,VoidType>( obj, MemFunc, argv );
        }

        static v8::Handle<v8::Value> Call( Type * obj, void (Type::*MemFunc)(), Arguments const & argv )
        {
            return Proxy::Call<Type>( obj, MemFunc, argv );
        }

        template <typename VoidType>
        static v8::Handle<v8::Value> CallVoid( VoidType (Type::*MemFunc)(), Arguments const & argv )
        {
            return Proxy::CallVoid<VoidType>( MemFunc, argv );
        }

        static v8::Handle<v8::Value> Call( void (Type::*MemFunc)(), Arguments const & argv )
        {
            return Proxy::Call( MemFunc, argv );
        }

        template <typename VoidType>
        static v8::Handle<v8::Value> CallVoid( Type const * obj, VoidType (Type::*MemFunc)() const, Arguments const & argv )
        {
            return Proxy::Call<Type,VoidType>( obj, MemFunc, argv );
        }

        static v8::Handle<v8::Value> Call( Type const * obj, void (Type::*MemFunc)() const, Arguments const & argv )
        {
            return Proxy::Call<Type>( obj, MemFunc, argv );
        }

        template <typename VoidType>
        static v8::Handle<v8::Value> CallVoid( VoidType (Type::*MemFunc)() const, Arguments const & argv )
        {
            return Proxy::CallVoid<Type,VoidType>( MemFunc, argv );
        }

        static v8::Handle<v8::Value> Call( void (Type::*MemFunc)() const, Arguments const & argv )
        {
            return Proxy::Call<Type>( MemFunc, argv );
        }

        template <typename RV, RV (Type::*MemFunc)() >
        static v8::Handle<v8::Value> Invocable( Arguments const & argv )
        {
            return Proxy::Invocable<Type,RV,MemFunc>( argv );
        }

        template <typename RV, RV (Type::*MemFunc)() const >
        static v8::Handle<v8::Value> Invocable( Arguments const & argv )
        {
            return Proxy::Invocable<Type,RV,MemFunc>( argv );
        }

        template <typename VoidType, VoidType (Type::*MemFunc)() >
        static v8::Handle<v8::Value> InvocableVoid( Arguments const & argv )
        {
            return Proxy::InvocableVoid<Type,VoidType,MemFunc>( argv );
        }

        template <typename VoidType, VoidType (Type::*MemFunc)() const >
        static v8::Handle<v8::Value> InvocableVoid( Arguments const & argv )
        {
            return Proxy::InvocableVoid<Type,VoidType,MemFunc>( argv );
        }
    };
#if !defined(DOXYGEN)
#include "forwarding-TMemFuncForwarder.h" // generated specializations for TMemFuncForwarder
#endif
    /**
       A useless base instantiation. See FunctionForwarder<0> for the
       full docs.
    */
    template <int Arity_>
    struct FunctionForwarder
    {
        enum { Arity = Arity_ };
    };

    /**
       A helper type for forwarding JS arguments to native
       functions taking 0 arguments. The classes
       FunctionForwarder<1..N> are generated code and follow this
       class' API.

       Each specialization of this class handles the cases for N
       arguments, where N is the templatized value, or arity of the
       functions.
       
       All variants of this class except the 0-arity one throw a
       JS-side exception if the argument list does not have at least
       the required number of parameters.

       This functions can support functions taking or returning any
       argument type which is convertible using CastToJS() and
       CastFromJS().

       The various Call() overloads can be used to forward JS calls to
       member functions.

       The Invocable() members can be used with
       v8::FunctionTemplate::New(FunctionForwarder<N>::Invocable<...>)
       to bind functions to JS objects.
    */
    template <>
    struct FunctionForwarder<0>
    {
        enum { Arity = 0 };
        /**
           Calls Func() and returns the function's value, converted to
           JS. If Func throws a native exception then it is
           transformed into a JS exception.
        */
        template <typename RV>
        static v8::Handle<v8::Value> Call( RV (*Func)(), Arguments const & /*ignored*/ )
        {
            try
            {
                return CastToJS<RV>( Func() );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<${count}>::Call() Native function threw an unknown native exception type!"));
            }
        }
        
        /**
           Calls Func(), ignoring the return value. If Func throws a native
           exception then it is transformed into a JS exception.

           Note that VoidType is not required to be CastFromJS()'able,
           so that JSToNative<VoidType> is not instantiated by this
           call.
        */
        template <typename VoidType>//, VoidType (*FuncT)() >
        static v8::Handle<v8::Value> CallVoid( VoidType (*Func)(), Arguments const & /*ignored*/ )
        {
            try
            {
                Func();
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("FunctionForwarder<${count}>::Call() Native function threw an unknown native exception type!"));
            }
            return v8::Undefined();
        }
        /**
           Identical to CallVoid(), and only exists because it
           incidentally allows the Invocable() function to work
           properly when RV==void.
        */
        template < typename VoidType >
        static v8::Handle<v8::Value> Call( void (*Func)(), ::v8::Arguments const & argv )
        {
            return CallVoid<VoidType>( Func, argv );
        }

        /**
           Calls Call( Func, argv ). Implements v8::InvocationCallback
           interface.
        */
        template <typename RV, RV (*Func)() >
        static v8::Handle<v8::Value> Invocable( Arguments const & argv )
        {
            return Call<RV>( Func, argv );
        }
        /**
           Calls Call( Func, argv ). Implements v8::InvocationCallback
           interface.
        */
        template <typename VoidType,VoidType (*Func)() >
        static v8::Handle<v8::Value> InvocableVoid( Arguments const & argv )
        {
            return CallVoid<VoidType>( Func, argv );
        }
    };

    /**
       A helper class for storing type information for JS function
       call forwarding.

       RV is the return value type of the templatized function.
     */
    template <typename RV, RV (*Func)()>
    struct InvocableFunction0
    {
        static const int Arity = 0;
        /** Returns FunctionForwarder<Arity>::Call<RV>( Func, argv ). */
        static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
        {
            return FunctionForwarder<Arity>::Call<RV>( Func, argv );
        }
        /** Returns FunctionForwarder<Arity>::CallVoid<RV>( Func, argv ). */
        static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
        {
            return FunctionForwarder<Arity>::CallVoid<RV>( Func, argv );
        }
    };

#if !defined(DOXYGEN)
#include "forwarding-FunctionForwarder.h" // generated specializations for MemFuncForwarder
#endif


    
    /**
       Possibly a utility class, though it's utility is in question,
       this is a helper for using the FunctionForwarder and
       MemFuncForwarder types.

       The following example binds the Unix sleep(3) function to a JS object:

       @code
       v8::InvocationCallback fp =
          InvocationCallbackCreator::F1::Invocable<unsigned int,unsigned int,sleep>;
       jsObject->Set(v8::String::New("sleep"), v8::FunctionTemplate::New(fp)->GetFunction() );
       @endcode

       If jsObject can be converted to a (T*) via CastFromJS<T*>() then the following will also work
       if (std::string T::toString()) is defined:
       
       @code
       v8::InvocationCallback fp =
          InvocationCallbackCreator::M0::Invocable<std::string,&T::toString>;
       jsObject->Set(v8::String::New("toString"), v8::FunctionTemplate::New(fp)->GetFunction() );
       @endcode

    */
    class InvocationCallbackCreator
    // leads to function ambiguity: : public FunctionForwarder<0>, public MemFuncForwarder<0>...<N>
    // as does   : public FunctionForwarder<0>, public FunctionForwarder<1>
    // Damn.
    {
    public:
        /**
           InvocationCallback generator for functions taking 0 arguments.
        */
        typedef FunctionForwarder<0> F0;
        /**
           InvocationCallback generator for member functions taking 0 arguments.
        */
        typedef MemFuncForwarder<0> M0;
        /**
           InvocationCallback generator for functions taking 1 argument.
        */
        typedef FunctionForwarder<1> F1;
        /**
           InvocationCallback generator for member functions taking 1 argument.
        */
        typedef MemFuncForwarder<1> M1;
        /**
           InvocationCallback generator for functions taking 2 arguments.
        */
        typedef FunctionForwarder<2> F2;
        /**
           InvocationCallback generator for member functions taking 2 arguments.
        */
        typedef MemFuncForwarder<2> M2;
        /**
           InvocationCallback generator for functions taking 3 arguments.
        */
        typedef FunctionForwarder<3> F3;
        /**
           InvocationCallback generator for member functions taking 3 arguments.
        */
        typedef MemFuncForwarder<3> M3;
        /**
           InvocationCallback generator for functions taking 4 arguments.
        */
        typedef FunctionForwarder<4> F4;
        /**
           InvocationCallback generator for member functions taking 4 arguments.
        */
        typedef MemFuncForwarder<4> M4;
        /**
           InvocationCallback generator for functions taking 5 arguments.
        */
        typedef FunctionForwarder<5> F5;
        /**
           InvocationCallback generator for member functions taking 5 arguments.
        */
        typedef MemFuncForwarder<5> M5;
        /**
           InvocationCallback generator for functions taking 6 arguments.
        */
        typedef FunctionForwarder<6> F6;
        /**
           InvocationCallback generator for member functions taking 6 arguments.
        */
        typedef MemFuncForwarder<6> M6;
        /**
           InvocationCallback generator for functions taking 7 arguments.
        */
        typedef FunctionForwarder<7> F7;
        /**
           InvocationCallback generator for member functions taking 7 arguments.
        */
        typedef MemFuncForwarder<7> M7;
        /**
           InvocationCallback generator for functions taking 8 arguments.
        */
        typedef FunctionForwarder<8> F8;
        /**
           InvocationCallback generator for member functions taking 8 arguments.
        */
        typedef MemFuncForwarder<8> M8;
        /**
           InvocationCallback generator for functions taking 9 arguments.
        */
        typedef FunctionForwarder<9> F9;
        /**
           InvocationCallback generator for member functions taking 9 arguments.
        */
        typedef MemFuncForwarder<9> M9;
    };

    /**
       This class is used just like InvocationCallbackCreator, but is
       templatized on the type containing the member functions.
    */
    template <typename T>
    class MemFuncInvocationCallbackCreator
    {
    public:
        /**
           InvocationCallback generator for member functions taking 0 arguments.
        */
        typedef TMemFuncForwarder<T,0> M0;
        /**
           InvocationCallback generator for member functions taking 1 argument.
        */
        typedef TMemFuncForwarder<T,1> M1;
        /**
           InvocationCallback generator for member functions taking 2 arguments.
        */
        typedef TMemFuncForwarder<T,2> M2;
        /**
           InvocationCallback generator for member functions taking 3 arguments.
        */
        typedef TMemFuncForwarder<T,3> M3;
        /**
           InvocationCallback generator for member functions taking 4 arguments.
        */
        typedef TMemFuncForwarder<T,4> M4;
        /**
           InvocationCallback generator for member functions taking 5 arguments.
        */
        typedef TMemFuncForwarder<T,5> M5;
        /**
           InvocationCallback generator for member functions taking 6 arguments.
        */
        typedef TMemFuncForwarder<T,6> M6;
        /**
           InvocationCallback generator for member functions taking 7 arguments.
        */
        typedef TMemFuncForwarder<T,7> M7;
        /**
           InvocationCallback generator for member functions taking 8 arguments.
        */
        typedef TMemFuncForwarder<T,8> M8;
        /**
           InvocationCallback generator for member functions taking 9 arguments.
        */
        typedef TMemFuncForwarder<T,9> M9;
    };

    
    /**
       See InvocationCallbackToArgv for details.
    */
    typedef ::v8::Handle< ::v8::Value > (*InvocationCallbackWithArray)( Handle<Object> self, int argc, v8::Handle<v8::Value> argv[] );

    /**
       A helper to allow re-use of certain JS/C++ functions. It's a
       bit of a long story...

       v8 defines the basic JS/C++ callback type as
       InvocationCallback, which takes a v8::Arguments list as its
       only argument. Since client code cannot create their own
       Arguments lists (only v8 can do that), it is impossible to
       re-use a subset of the arguments and pass them to another
       InvocationHandler. Such forwarding is often useful when
       implementing related functions which share a common basis, but
       v8's callback convention makes it impossible.

       So now the workaround:

       Instead of defining a callback as an InvocationCallback, it can
       be defined as a InvocationCallbackWithArray, and this type can
       be used to do the conversion.  For example, in conjunction with
       the WeakJSClassCreator:

       \code
       myobj->Set(String::New("func"),
          FunctionTemplate::New(InvocationCallbackToArgv<MyCallback>::Invocable)->GetFunction());
       \endcode

       This is of course less efficient than directly calling an
       InvocationCallback, because we must synthesize an array of
       Value handles.

       The optional skipArgN parameter tells Invocable() than it should skip
       over the first N arguments in the list, which can be useful when
       stripping a first argument for personal use then passing on the
       rest of the args.
    */
    template <InvocationCallbackWithArray proxy, int skipArgN = 0>
    struct InvocationCallbackToArgv
    {
	/**
	   Synthesizes an array of Value handles and calls
	   proxy(argv.This(),argCount,argsArray). If skipArgN is
	   greater than or equal to argv.Length() then
	   proxy(argv.This(),0,0) is called.
	*/
	static ::v8::Handle< ::v8::Value > Invocable( ::v8::Arguments const & argv )
	{
	    typedef v8::Handle<v8::Value> HV;
	    if( skipArgN >= argv.Length() )
	    { // Is this sensible? Should we throw instead? Hmm.
		return proxy( argv.This(), 0, 0 );
	    }
	    const int argc = argv.Length() - skipArgN;
	    std::vector< HV > vec( static_cast<size_t>(argc), Null() );
	    int pos = 0;
	    for( int i = skipArgN; i < argc; ++i, ++pos )
	    {
		vec[pos] = argv[i];
	    }
            v8::Handle<v8::Value> * ar = vec.empty() ? &vec[0] : 0;
	    return proxy( argv.This(), argc, ar );
	}
    };

    /**
       InvocationCallbackMember is a helper type for binding
       InvocationCallback-like member functions. It requires that T be
       supported by CastFromJS(). The Func template parameter is the
       member invocation callback which we want to proxy.

       Note that because bound objects are never const in a JS
       context, the member function should not be const.
    */
    template <typename T,
              ::v8::Handle< ::v8::Value > (T::*Func)( ::v8::Arguments const & argv )
              >
    struct InvocationCallbackMember
    {
	/**
           Extracts a native T object from argv using
           CastFromJS(argv.This()) and passes the call on to
           obj->Func(). If no object can be found it throws a JS
           exception, otherwise it returns the result of the proxied
           call.
	*/
	static ::v8::Handle< ::v8::Value > Invocable( ::v8::Arguments const & argv )
	{
            T * self = CastFromJS<T*>( argv.This() );
            if( ! self ) return v8::ThrowException(v8::String::New("InvocationCallbackMember could not find native 'this' object in argv!"));
            return (self->*Func)( argv );
	}
    };

    /**
       A helper class for binding JS properties to native code, in particular
       for when JS objects are bound to native T objects.

       It contains utility functions to simplify the process of binding
       JS properties to native member functions or native properties.
       
       Requirements:

       - T must be of class type.

       - JSToNative<T> must be implemented for T.

       - TypeInfo<T>::NativeHandle must be usable in a boolean context
       to determine whether the JS-to-Native converted object is null
       or not.
    */
    template <typename T>
    struct PropertyBinder
    {
        typedef typename TypeInfo<T>::Type Type;
        typedef typename JSToNative<T>::ResultType NativeHandle;

        /**
           This template can be used as an argument to
           v8::ObjectTemplate::SetAccessor()'s Getter parameter to
           generically tie a native member variable to a named JS
           property.

           Requirements:

           - Type must be convertible to NativeHandle via CastFromJS<NativeHandle>().

           - PropertyType must be convertible via CastToJS<PropertyType>().

           If the underlying native This object cannot be found (that
           is, if CastFromJS<NativeHandle>() fails) then this routine will
           trigger a JS exception.

           Example:

           Assume we have a native type Foo with a std::string member
           called str. We can bind the member variable with:

           \code
           myObjectTemplate.SetAccessor("foo",
           MemVarGetter<Foo,std::string,&Foo::str>,
           MemVarSetter<Foo,std::string,&Foo::str> );
           \endcode

           In 10 years of C++ coding, this is the first time i've ever
           had a use for a pointer-to-member.
        */
        template <typename PropertyType, PropertyType Type::*MemVar>
        static v8::Handle<v8::Value> MemVarGetter(v8::Local<v8::String> property, const AccessorInfo &info)
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( ! self ) return v8::ThrowException( v8::String::New( "Native member property getter could not access native This object!" ) );
            try
            {
                return CastToJS( (self->*MemVar) );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("Native member property getter threw an unknown native exception type!"));
            }
        }

        /**
           This is the Setter counterpart of MemVarGetter(). See
           that function for most of the details.

           Requirements:

           - MemVar must be an accessible member of Type.
           - PropertyType must be convertible via CastFromJS<PropertyType>().

           If the underlying native This object cannot be found then this
           routine will trigger a JS exception, though it is currently
           unclear whether this is actually legal in v8 (and difficult to
           test, since the native bindings work so well ;).
        */
        template <typename PropertyType, PropertyType Type::*MemVar>
        static void MemVarSetter(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( self )
            {
                self->*MemVar = CastFromJS<PropertyType>( value );
            }
            else
            {
                ::v8::ThrowException(v8::String::New("Native member property setter could not access native This object!"));
            }
        }

        /**
           This template can be used as an argument to
           v8::ObjectTemplate::SetAccessor()'s Getter parameter to
           generically tie a static variable to a named JS property.

           SharedVar must be pointer to a static variable and must not
           be 0.

           CastToJS<PropertyType>() must be legal.
        */
        template <typename PropertyType, PropertyType const * SharedVar>
        static v8::Handle<v8::Value> StaticVarGetter(v8::Local<v8::String> property, const AccessorInfo &info)
        {
            return CastToJS<PropertyType>( *SharedVar );
        }
        /**
           The setter counterpart of StaticVarGetter().

           SharedVar must be pointer to a static variable and must not
           be 0.

           CastFromJS<PropertyType> must be legal.
        */
        template <typename PropertyType, PropertyType * SharedVar>
        static void StaticVarSetter(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
        {
            *SharedVar = CastFromJS<PropertyType>( value );
        }

        /**
           Binds the given static variable to a JS property, such that
           get/set access will go through
           StaticVarGetter<VarType,SharedVar> and
           StaticVarSetter<VarType,SharedVar>.
        */
        template <typename VarType, VarType * SharedVar>
        static void BindStaticVar( char const * name,
                                   v8::Handle<v8::ObjectTemplate> const & prototype,
                                   v8::AccessControl settings = v8::PROHIBITS_OVERWRITING,
                                   v8::PropertyAttribute attribute = v8::DontDelete
                         )
        {
            if( ! prototype.IsEmpty() )
            {
                prototype->SetAccessor( v8::String::New(name),
                                        StaticVarGetter<VarType,SharedVar>,
                                        StaticVarSetter<VarType,SharedVar>,
                                        v8::Handle< v8::Value >(),
                                        settings,
                                        attribute );
            }
        }

        /**
           Binds the given static variable to a JS property, such that
           read access will go through
           StaticVarGetter<VarType,SharedVar> and set access will be
           ignored (it will not change SharedVar).
        */
        template <typename VarType, VarType const * SharedVar>
        static void BindStaticVarRO( char const * name,
                                     v8::Handle<v8::ObjectTemplate> const & prototype,
                                     v8::AccessControl settings = v8::PROHIBITS_OVERWRITING,
                                     v8::PropertyAttribute attribute = v8::DontDelete
                         )
        {
            if( ! prototype.IsEmpty() )
            {
                prototype->SetAccessor( v8::String::New(name),
                                        StaticVarGetter<VarType,SharedVar>,
                                        0,
                                        v8::Handle< v8::Value >(),
                                        settings,
                                        attribute );
            }
        }

        
        /**
           Binds automatically-generated getter/setter functions to the given
           member variable. See MemVarGetter() and MemVarSetter()
           for the requirements of the templatized types.

           If you only want to bind one of the getter OR the setter then
           use the 5-argument variant of Set() instead and pass MemVarGetter
           or MemVarGetter, as appropriate, to that function.
        */
        template <typename VarType, VarType Type::*MemVar>
        static void BindMemVar( char const * name,
                                v8::Handle<v8::ObjectTemplate> const & prototype,
                                v8::AccessControl settings = v8::PROHIBITS_OVERWRITING,
                                v8::PropertyAttribute attribute = v8::DontDelete
                         )
        {
            if( ! prototype.IsEmpty() )
            {
                prototype->SetAccessor( v8::String::New(name),
                                        MemVarGetter<VarType,MemVar>,
                                        MemVarSetter<VarType,MemVar>,
                                        v8::Handle< v8::Value >(),
                                        settings,
                                        attribute );
            }
        }

        /**
           Binds the given JS property to MemVar, such that read/get
           operations will work but write/set operations will be
           ignored (that is, will not affect the value returned by the
           getter).
        */
        template <typename VarType, VarType Type::*MemVar>
        static void BindMemVarRO( char const * name,
                                  v8::Handle<v8::ObjectTemplate> const & prototype )
        {
            if( ! prototype.IsEmpty() )
            {
                prototype->SetAccessor( v8::String::New(name),
                                        MemVarGetter<VarType,MemVar>,
                                        0,
                                        v8::Handle< v8::Value >(),
                                        v8::PROHIBITS_OVERWRITING,
                                        v8::DontDelete );
            }
        }
        
        /**
           Implements the v8::AccessorGetter interface to bind a JS
           member property to a native getter function. This function
           can be used as the getter parameter to
           v8::ObjectTemplate::SetAccessor().
        */
	template <typename RV, RV (Type::*Func)()>
        static v8::Handle<v8::Value> PropGetterFunc( Local< String > /*ignored*/, const AccessorInfo & info )
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( ! self ) return v8::ThrowException( v8::String::New( "Native member property getter could not access native This object!" ) );
            try
            {
                return convert::CastToJS( (self->*Func)() );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("Native property getter function threw an unknown native exception type!"));
            }
        }
        /**
           Overload for const native getter functions.
        */
	template <typename RV, RV (Type::*Func)() const>
        static v8::Handle<v8::Value> PropGetterFunc( Local< String > /*ignored*/, const AccessorInfo & info )
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( ! self ) return v8::ThrowException( v8::String::New( "Native member property getter could not access native This object!" ) );
            try
            {
                return convert::CastToJS( (self->*Func)() );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("Native property getter function threw an unknown native exception type!"));
            }
        }

        /** Overload which takes a free function as the getter. */
	template <typename RV, RV (*Func)()>
        static v8::Handle<v8::Value> PropGetterFunc( Local< String > /*ignored*/, const AccessorInfo & info )
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( ! self ) return v8::ThrowException( v8::String::New( "Native member property getter could not access native This object!" ) );
            try
            {
                return convert::CastToJS( Func() );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("Native property getter function threw an unknown native exception type!"));
            }
        }

        /**
            Implements v8::AccessorSetter interface to proxy a JS
            member property through a native member setter function.

            The RV parameter is ignored by the conversion, and does
            not invoke a conversion operation.

             This function can be used as the setter parameter to
             v8::ObjectTemplate::SetAccessor().
        */
        template <typename RV, typename ArgT, RV (Type::*Func)(ArgT)>
        static void PropSetterFunc(v8::Local< v8::String > property, v8::Local< v8::Value > value, const v8::AccessorInfo &info)
        {
            NativeHandle self = CastFromJS<NativeHandle>( info.This() );
            if( ! self )
            {
                v8::ThrowException( v8::String::New( "Native member property setter could not access native This object!" ) );
                return;
            }
            else try
            { 
                (self->*Func)( CastFromJS<ArgT>( value ) );
            }
            catch( std::exception const & ex )
            {
                ::v8::ThrowException( ::v8::String::New(ex.what()) );
            }
            catch( ... )
            {
                ::v8::ThrowException( ::v8::String::New("Native property setter function threw an unknown native exception type!"));
            }
            return;
        }

        /**
           Binds the given JS property to a pair of T member
           functions, such that these functions will be called in
           place of get/set operations for the property.
           
           The native member functions must follow conventional
           accessor signatures:

           - Getter: T1 getter() [const]
           - Setter: [AnyType] setter( T2 )

           For the setter, T1 may differ from T2. T1 may be void but
           T2 may not be. Any return value from the setter is ignored
           by the JS engine.

           For the getter, an overload of this function is provided which
           supports a non-const getter.
         */
        template <typename RV,
                  RV (Type::*Getter)(),
                  typename SetRV,
                  typename ArgV,
                  SetRV (Type::*Setter)(ArgV)
            >
        static void BindGetterSetter( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
            if( ! prototype.IsEmpty() )
                prototype->SetAccessor( v8::String::New( propName ),
                                        PropGetterFunc<RV,Getter>,
                                        PropSetterFunc<SetRV,ArgV,Setter>
                                        );
	}

        /**
           Overload to allow a const getter function. Member setter functions
           are not, by nature, const.
         */
        template <typename RV,
                  RV (Type::*Getter)() const,
                  typename SetRV,
                  typename ArgV,
                  SetRV (Type::*Setter)(ArgV)
            >
        static void BindGetterSetter( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
            if( ! prototype.IsEmpty() )
                prototype->SetAccessor( v8::String::New( propName ),
                                        PropGetterFunc<RV,Getter>,
                                        PropSetterFunc<SetRV,ArgV,Setter>
                                        );
	}

        /**
           Binds the templatized getter function to the given JS property of the
           given prototype object, such that JS-side read access to the property
           will return the value of that member function.
         */
        template <typename RV, RV (Type::*Getter)()>
        static void BindGetter( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
	    prototype->SetAccessor( v8::String::New( propName ),
                                   PropGetterFunc<RV,Getter> );
	}

        /**
           Overload too support const getters.
        */
        template <typename RV, RV (Type::*Getter)() const>
        static void BindGetter( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
	    prototype->SetAccessor( v8::String::New( propName ),
                                   PropGetterFunc<RV,Getter> );
	}

        /**
           Overload too support free-function getters.
        */
        template <typename RV, RV (*Getter)()>
        static void BindGetter( char const * propName, v8::Handle<v8::ObjectTemplate> const & prototype )
	{
	    prototype->SetAccessor( v8::String::New( propName ),
                                    PropGetterFunc<RV,Getter> );
	}
    };

    /**
       Must be specialized (or partially specialized) to be useful.

       Requirements:

       - (new T) must be legal, taking a number of arguments equal
       to the Arity parameter.

       - All arguments to the native ctor must be convertible
       using CastFromJS().

       - CastToJS<T*>() must be legal (i.e. it must return an object
       or throw).

       This type is intended to assist in the creation of ctor
       functions for JS-bound C++ classes.

       They are used something like:

       @code
       T * x = 0;
       if( argv.Length() < 1 ) x = CtorForwarder<T,0>::Ctor(argv);
       else if( argv.Length() < 3 ) x = CtorForwarder<T,2>::Ctor<int,int>(argv);
       ...
       @endcode
    */
    template <typename T, int Arity_>
    struct CtorForwarder
    {
        enum { Arity = Arity_ };
        typedef typename TypeInfo<T>::Type Type;
        typedef typename TypeInfo<T>::NativeHandle NativeHandle;
        /**
           Must be specialized.

           For all specializations, the caller owns the returned
           object.

           On error the function may trigger a v8 exception
           or if it likes.
        */
        static NativeHandle Ctor( v8::Arguments const & );
    };

    /**
       Partial specialization for default constructors.
     */
    template <typename T>
    struct CtorForwarder<T,0>
    {
        enum { Arity = 0 };
        typedef typename TypeInfo<T>::Type Type;
        typedef typename TypeInfo<T>::NativeHandle NativeHandle;
        /**
           Returns (new Type). The caller owns the returned object.
        */
        static NativeHandle Ctor( v8::Arguments const & )
        {
            return new Type;
        }
    };

    /** Identical to CtorForward<T,0>. */
    template <typename T>
    struct CtorForwarder0 : CtorForwarder<T,0>
    {
    };
#if !defined(DOXYGEN)
#include "forwarding-CtorForwarder.h" /* generated code for specializations taking 1+ args */
#endif

    /**
       This class converts a v8::InvocationCallback function into an
       InvocableInterface class.  It may seem useless, but has uses
       (or _a_ use) in binding overloaded native functions to classes.

       The Arity argument is a hint as to how many arguments the
       function requires. If it is zero or higher then this type
       enforces that it is passed exactly that many arguments,
       throwing a JS exception if there is a mismatch. If it is
       negative then this class ignores the argument count, leaving
       enforcement to a lower-level proxy function (which will likely
       throw a JS exception if the arg count does not match the
       requirements).
    */
    template < int Arity_, v8::Handle<v8::Value> (*Func)( v8::Arguments const & ) >
    struct InvocableCallback
    {
        static const int Arity = Arity_; // if i make this an enum it is not found???
        /**
           If Arity is negative then it calls Func(argv). Otherwise it
           calls Func() only if argv.Length()==Arity, throwing a JS
           exception if the argument count does not match.
        */
        static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
        {
            if( Arity>=0 )
            {
                if( argv.Length() != Arity )
                {
                    StringBuffer msg;
                    msg << "InvocableCallback<>::Invocable(): "
                        << argv.Callee()->GetName()
                        << "() was passed "<<argv.Length()<<" arguments, but "
                        << "expects "<< Arity<<"!\n";
                    return v8::ThrowException( msg );
                }
            }
            return Func( argv );
        }
        /**
           Just like Invocable(), but discards the return value from
           Func().  It always returns v8::Undefined() on success and a
           JS exception on error (argument count mismatch).
        */
        static v8::Handle<v8::Value> InvocableVoid( v8::Arguments const & argv )
        {
            if( Arity>=0 )
            {
                if( argv.Length() != Arity )
                {
                    StringBuffer msg;
                    msg << "InvocableCallback<>::InvocableVoid(): "
                        << argv.Callee()->GetName()
                        << "() was passed "<<argv.Length()<<" arguments, but "
                        << "expects "<< Arity<<"!\n";
                    return v8::ThrowException( msg );
                }
            }
            Func( argv );
            return v8::Undefined();
        }
    };

    /**
       This is an adapter type for types implementing
       InvocableInterface.  It converts the call into a
       v8::InvocationCallback which returns Undefined(). That is, it
       discards the return value. Note that this is slighlty different
       from MemFuncForwarder::InvocableVoid() and friends in that this
       adapter must invoke the conversion template for the return
       value type, which is not legal (compile-time error) if there is
       no conversion in place.
    */
    template < typename InvocableT >
    struct DiscardInvocableReturnVal
    {
        static const int Arity = InvocableT::Arity;
        /**
           Just like InvocableCallback::Invocable(), but
           discards the return value from Func().  It always returns
           v8::Undefined() on success and a JS exception on error.
        */
        static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
        {
            if( Arity>=0 )
            {
                if( argv.Length() != Arity )
                {
                    StringBuffer msg;
                    msg << "DiscardInvocableReturnVal<>::Invocable(): "
                        << argv.Callee()->GetName()
                        << "() was passed "<<argv.Length()<<" arguments, but "
                        << "expects "<< Arity<<"!\n";
                    return v8::ThrowException( msg );
                }
            }
            InvocableT::Invocable( argv );
            return v8::Undefined();
        }
    };

    /**
       This works just like DiscardInvocableReturnVal but takes a
       v8::InvocationCallback pointer. i don't seem to be able to
       unify them into one interface :/.
    */
    template < int Arity, v8::Handle<v8::Value> (*Func)( v8::Arguments const & ) >
    struct DiscardInvocableCallback :
        DiscardInvocableReturnVal< InvocableCallback<Arity, Func> >
    {
    };

    /**
       An InvocableInterface implementation which requires a
       v8::InvocationCallback as an argument. It acts as a proxy
       but catches native exceptions. See the Invocable() member
       for details.

       The Arity argument is part of the InvocableInterface.
       When proxying "raw" InvocationCallbacks, this should be
       set to -1. When proxying callback created by
       other InvocableInterface types then this value should be
       set to that type's Arity. Failing to do so may confuse
       certain algorithms (notably OverloadInvocables<>).

       If Arity is 0 or greater then this type enforces that the
       argument count given to it is _exactly_ that number. If Arity
       is negative then this type ignores the argument count of
       the call.

       Note that most, if not all of the other InvocableInterface
       types perform native-to-JS exception conversion, so this
       type is not necessary for use with them. It is intended for
       use with "plain" v8::InvocationCallback implementations.
    */
    template <int Arity_,  v8::InvocationCallback CB>
    struct InvocationCallbackCatcher
    {
        //! Required by InvocableInterface.
        static const int Arity = Arity_;
        /**
           This type acts identically to the templatized function CB,
           except: if CB() passes on a native exception, this type
           converts it to a JS exception, then discards the native
           exception.
        */
        static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
        {
            if( (Arity>=0) && (argv.Length() != Arity) )
            {
                StringBuffer msg;
                msg << argv.Callee()->GetName()
                    << "() requires "<< Arity<< " arguments.";
                return v8::ThrowException(msg);
            }
            try
            { 
                return CB( argv );
            }
            catch( std::exception const & ex )
            {
                return ::v8::ThrowException( CastToJS( ex.what() ) );
            }
            catch( ... )
            {
                return ::v8::ThrowException( ::v8::String::New("Exception::Invocable() caught unknown native exception type!"));
            }
        }
    };

    namespace Detail
    {
	namespace cv = v8::juice::convert;
        namespace tmp = v8::juice::tmp;
        template <typename FWD>
        struct FwdInvocableOne
        {
            static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
            {
                if( (FWD::Arity<0) || (FWD::Arity == argv.Length()) )
                {
                    return FWD::Invocable( argv );
                }
                else
                {
                    cv::StringBuffer msg;
                    msg << "FwdInvocableOne<>::Invocable(): "
                        << argv.Callee()->GetName()
                        << "() called with "<<argv.Length()<<" arguments, "
                        << "but requires "<<FWD::Arity<<"!\n";
                    return v8::ThrowException(msg);
                }
            }
        };
        /**
           Internal dispatch end-of-list routine.
        */
        template <>
        struct FwdInvocableOne<tmp::NilType>
        {
            static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
            {
                return v8::ThrowException(v8::String::New("FwdInvocableOne<> end-of-list specialization should not have been called!"));
            }
        };

        /**
           FwdList must be-a TypeList of FuncOverloadForwardXXX classes,
           where XXX is an integer value (the function arity).

        */
        template <typename List>
        struct FwdInvocableList
        {
            static v8::Handle<v8::Value> Dispatch( v8::Arguments const & argv )
            {
                typedef typename List::Head FWD;
                typedef typename List::Tail Tail;
                if( (FWD::Arity == argv.Length()) || (FWD::Arity<0) )
                {
                    return FwdInvocableOne< FWD >::Invocable( argv );
                }
                {
                    return FwdInvocableList< Tail >::Dispatch(argv);
                }
                return v8::Undefined(); // can't get this far.
            }
        };

        /**
           End-of-list specialization.
        */
        template <>
        struct FwdInvocableList<tmp::NilType>
        {
            static v8::Handle<v8::Value> Dispatch( v8::Arguments const & argv )
            {
                StringBuffer msg;
                msg << "FwdInvocableList<>::Dispatch() there is no overload for "
                    << argv.Callee()->GetName()
                    << "() taking "<<argv.Length()<<" arguments!\n";
                return v8::ThrowException( msg );
            }
        };

    }
    /**
       A helper class which allows us to dispatch to multiple
       overloaded native functions from JS, depending on the argument
       count.

       FwdList must be-a TypeList containing elements which have
       the following function:

       static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv );

       And a static const integer value called Arity, which must specify the
       expected number of arguments, or be negative specify that the function
       accepts any number.

       In other words, all entries in FwdList must implement the
       InvocableInterface.
    */
    template < typename FwdList >
    struct OverloadInvocables
    {
        // arguable: static const Arity = -1;
        /**
           Tries to dispatch argv to one of the bound functions defined
           in FwdList, based on the number of arguments in argv and
           the Arity 

           Implements the v8::InvocationCallback interface.
        */
        static v8::Handle<v8::Value> Invocable( v8::Arguments const & argv )
        {
            typedef Detail::FwdInvocableList<FwdList> X;
            return X::Dispatch( argv );
        }
    };
    
}}} /* namespaces */

#endif /* CODE_GOOGLE_COM_P_V8_V8_FORWARDING_H_INCLUDED */
