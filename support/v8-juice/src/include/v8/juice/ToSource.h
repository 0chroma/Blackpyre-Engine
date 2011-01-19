#if !defined(CODE_GOOGLE_COM_P_V8_V8_TOSOURCE_H_INCLUDED)
#define CODE_GOOGLE_COM_P_V8_V8_TOSOURCE_H_INCLUDED 1
/*
   A mini-framework for adding toSource()-like features for native types

   Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)

   License: Public Domain

   Some of this code was derived from SpiderApe, where it is released
   using the MPL license. i wrote that code, and an re-licensing it
   here by dedicating it into the Public Domain.
*/
#include <stdint.h> // hope the client's platform is recent!
#include <string>
#include <sstream>
// #include <cstring>
#include <list>
#include <vector>
#include "convert.h"
namespace v8 {
namespace juice {

namespace convert {
    using namespace v8;

    /**
       Base instantiation for T-to-Source conversion functor. The default
       implementation simply uses std::ostream-style conversion (effectively
       a lexical cast).
    */
    template <typename NT>
    struct NativeToSource
    {
	template <typename X>
	std::string operator()( X const & x ) const
        {
            std::ostringstream os;
            os << x;
            return os.str();
        }
    };

    template <typename NT>
    struct NativeToSource<NT *> : NativeToSource<NT> {};

    template <typename NT>
    struct NativeToSource<NT &> : NativeToSource<NT> {};

    template <typename NT>
    struct NativeToSource<const NT &> : NativeToSource<NT> {};

    template <>
    struct NativeToSource<void>
    {
	/**
	   Returns "undefined".
	*/
	std::string operator()(...) const
	{
	    return "undefined";
	}
    };


    template <>
    struct NativeToSource<std::string>
    {
	std::string operator()( std::string const & v) const
	{
            return ::v8::juice::StringJSQuote(v);
	}
    };

    template <>
    struct NativeToSource<char const *>
    {
	std::string operator()( char const * v ) const
	{
            return (v && *v)
                ? ::v8::juice::StringJSQuote(v)
                : "''";
	}
    };

    template <>
    struct NativeToSource<bool>
    {
	std::string operator()( bool b ) const
        {
            return b ? "true" : "false";
        }
    };

    /**
       "Casts" v to a JS value using NativeToSource<T>.

       TODO: use template metaprogramming to figure out the
       exact parameter type, instead of using (T const &).
    */
    template <typename T>
    std::string ToSource( T const & v )
    {
	typedef NativeToSource<T> F;
	return F()( v );
    }

    /**
       Overload to avoid ambiguity in certain calls.
    */
    static inline std::string ToSource( char const * v )
    {
	typedef NativeToSource<char const *> F;
	return F()( v );
    }

    /**
       Specialization for Objects.

       BUGS:

       - Can (and will) infinitely loop if the object contains
       (however deeply) circular references to other objects.
    */
    template <>
    struct NativeToSource< ::v8::Object >
    {
        std::string operator()( Object * const v ) const
        {
            if( ! v ) return "null";
            v8::HandleScope sentry;
            std::ostringstream os;
            const bool isArray = v->IsArray();
            const char * sep = isArray ? "[]" : "{}";
            os << sep[0];
            Local<Array> ar( v->GetPropertyNames() );
            uint32_t len = ar->Length();
	    for( uint32_t ndx = 0; ndx < len; ++ndx )
	    {
                if( isArray )
                {
                    os << ToSource( v->Get(Integer::New(ndx)) );
                }
                else
                {
                    Local<Value> key( ar->Get(Integer::New(ndx)) );
                    os << CastFromJS<std::string>( key )
                        << ':'
                        << ToSource( v->Get( key ) );
                }
                if( (ndx+1) < len) os << ", ";
	    }
            os << sep[1];
	    return os.str();
        }
        /**
           Treats an array like an object, using key:value pairs
           in the output, instead of outputing a linear list.
           This is the only way to toSource arrays with non-numeric
           keys.
        */
        std::string ArrayAsObject( Array * const v ) const
        {
            return this->operator()( static_cast<Object * const>(v) );
        }

        template <typename HandleT>
        std::string operator()( HandleT const & h ) const
        {
            return h.IsEmpty()
                ? "undefined"
                : this->operator()( Object::Cast(h) );
        }
    };


    /**
       A ToSource implementation for Arrays. Simply
       loops over the length of the array and
       iteratively calls ToSource() on the entries.

       BUGS:

       - Only handles numeric indexes.
    */
    template <>
    struct NativeToSource< ::v8::Array >
    {
        std::string operator()( Array * const v ) const
        {
#if 0
            typedef NativeToSource< Object > PT;
            return PT().ArrayAsObject( v );
#else
            if( ! v ) return "null";
            std::ostringstream os;
            os << '[';
            uint32_t len = v->Length();
	    for( uint32_t ndx = 0; ndx < len; ++ndx )
	    {
                os << ToSource( v->Get(Integer::New(ndx)) );
                if( (ndx+1) < len) os << ", ";
	    }
            os << ']';
	    return os.str();
#endif
        }
        template <typename HandleT>
        std::string operator()( HandleT const & h ) const
        {
            return h.IsEmpty()
                ? "undefined"
                : this->operator()( Array::Cast(h) );
        }
    };

    template <>
    struct NativeToSource< ::v8::Function >
    {
        std::string operator()( Function * const v ) const
        {
            if( ! v ) return "null";
            std::string fname = CastFromJS<std::string>( v->GetName() );
            if( fname.empty() )
            {
                return CastFromJS<std::string>( v->ToString() );
            }
            return fname;
        }
        template <typename HandleT>
        std::string operator()( HandleT const & h ) const
        {
            return h.IsEmpty()
                ? "undefined"
                : this->operator()( Array::Cast(h) );
        }
    };

    /**
       Basic dispatcher for HandleType, which must be one of
       v8::Handle<>, v8::Local<>, or v8::Persistent<>. This
       implementation pawns off most work to other implementations,
       based on held JS type of a handle.
    */
    template <typename HandleType>
    struct NativeToSourceHandleImpl
    {
	std::string operator()( HandleType const & h ) const
	{
            if( h.IsEmpty() || h->IsUndefined() ) return "undefined";
            else if( h->IsNull() ) return "null";
            else if( h->IsString() ) return ToSource( CastFromJS<std::string>(h) );
            else if( h->IsBoolean() ) return ToSource( h->BooleanValue() );
            else if( h->IsInt32() ) return ToSource( CastFromJS<int32_t>(h) );
            else if( h->IsNumber() ) return ToSource( CastFromJS<double>(h) );
            else if( h->IsFunction() ) return ToSource( Function::Cast(*h) );
            else if( h->IsArray() ) return ToSource( Array::Cast(*h) );
            else if( h->IsObject() ) return ToSource( Object::Cast(*h) );
            return "'NativeToSource< Handle<T> > got an unhandled type!'";
	}
    };

    template <typename VT>
    struct NativeToSource< ::v8::Handle< VT > > : NativeToSourceHandleImpl< Handle<VT> >
    {};

    template <typename VT>
    struct NativeToSource< ::v8::Local< VT > > : NativeToSourceHandleImpl< Local<VT> >
    {};

    template <typename VT>
    struct NativeToSource< ::v8::Persistent< VT > > : NativeToSourceHandleImpl< Persistent<VT> >
    {};


//     template <>
//     struct NativeToSource< ::v8::Handle<Value> >
//     {
// 	typedef ::v8::Handle<Value> HandleType;
// 	std::string operator()( HandleType const & h ) const
// 	{
//             if( h.IsEmpty() || h->IsUndefined() ) return "undefined";
//             else if( h->IsNull() ) return "null";
//             else if( h->IsString() ) return ToSource( Handle<String>( String::Cast(*h) ) );
//             return "NYI";
// 	}
//     };

#if 0 // not yet...
    template <typename T>
    struct NativeToSource< ::v8::Handle<T> >
    {
	typedef ::v8::Handle<T> handle_type;
	std::string operator()( handle_type & li ) const
	{
	    return li.IsEmpty()
                ? std::string("undefined")
                : ::v8::juice::CastFromJS<std::string>(li);
	}
    };

    template <typename T>
    struct NativeToSource< ::v8::Local<T> >
    {
	typedef ::v8::Local<T> handle_type;
	std::string operator()( handle_type const & li ) const
	{
	    return li;
	}
    };

    template <typename T>
    struct NativeToSource< ::v8::Persistent<T> >
    {
	typedef ::v8::Persistent<T> handle_type;
	std::string operator()( handle_type const & li ) const
	{
	    return li;
	}
    };
#endif

    /**
       A basic ToSource-compatible implementation for std::list-like
       types which creates source for a JS
       array. ToSource<ListT::value_type> and ListT::const_iterator
       must be valid.
    */
    template <typename ListT>
    struct NativeToSourceListImpl
    {
        typedef ListT Type;
        std::string operator()( Type const & src ) const
        {
            if( src.empty() ) return "({})";
            std::ostringstream os;
            os << "[";
            size_t sz = src.size(); // shameful. only to get the commas right later on...
            typename Type::const_iterator it, et;
            it = src.begin();
            et = src.end();
            size_t at = 0;
            for( ; et != it; ++it )
            {
                os << ToSource( (*it) );
                if( ++at != sz ) os << ", ";
            }
            os << "]\n";
            return os.str();
        }
    };


    template <typename VT>
    struct NativeToSource< std::list<VT> > : NativeToSourceListImpl< std::list<VT> > {};

    template <typename VT>
    struct NativeToSource< std::vector<VT> > : NativeToSourceListImpl< std::vector<VT> > {};

//     template <typename VT>
//     struct ToSource< std::set<VT> > : ToSourceListImpl< std::set<VT> > {};

//     template <typename VT>
//     struct ToSource< std::multiset<VT> > : ToSourceListImpl< std::multiset<VT> > {};


    /**
       A JS-callable variant of ToSource(), but BEWARE OF BUGS.

       JS Usage:  string toString(expression)

       BUGS:

       - Everything is to-sourced by VALUE, not REFERENCE. We don't
       have a standard, generic way to embed references references in
       JS (do we?).

       - Circular object references will lead to infinite recursion.

       - Source created for Functions is: named functions evaluate to
       their name. Unnamed functions are assumed to be JS source and
       are toString()'d. This is about as close a comprimise as i can
       find.

       - For Arrays, only their numeric fields are traversed.
    */
    Handle<Value> ToSource( ::v8::Arguments const & argv );

}}} /* namespaces */

#endif /* CODE_GOOGLE_COM_P_V8_V8_TOSOURCE_H_INCLUDED */
