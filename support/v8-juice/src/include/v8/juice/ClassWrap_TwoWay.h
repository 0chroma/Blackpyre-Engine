#if !defined(V8_JUICE_CLASSWRAP_TWOWAY_INCLUDED)
#define V8_JUICE_CLASSWRAP_TWOWAY_INCLUDED
/** @file ClassWrap_TwoWay.h
   This file has two uses:

   1) When included "normally", it defines a set of ClassWrap policies
   which work together to provide JS/Native conversions for the
   ClassWrap type.

   2) To act as a supermacro for use by clients which wish to use
   these policies, as is demonstrated here:


   @code
   // From global scope:
   #define CLASSWRAP_BOUND_TYPE MyType
   #define CLASSWRAP_BOUND_TYPE_NAME "MyType"
   // OPTIONAL: #define CLASSWRAP_BOUND_TYPE_INHERITS BoundBaseClass
   // ^^^^^ required if MyType sublcasses another bound native!
   #include <v8/juice/ClassWrap_TwoWay.h>
   @endcode
   
   That will install these policies as the defaults for
   ClassWrap<CLASSWRAP_BOUND_TYPE>, and then CLASSWRAP_BOUND_TYPE and
   CLASSWRAP_BOUND_TYPE_NAME will be undefined (so that this file can
   be directly included again).

   If MyType inherits from another bound type and
   CLASSWRAP_BOUND_TYPE_INHERITS is NOT set then the
   ToJS<CLASSWRAP_BOUND_TYPE> policy will not work properly (that is,
   converting from (T*) to JS will fail at runtime).  Or a
   compile-time error might be triggered, saying that cw::ToJS<T> must
   be specialized.
   
   Defining CLASSWRAP_BOUND_TYPE_NAME is optional, but if it is not done
   then one must provide his own ClassName<CLASSWRAP_BOUND_TYPE>
   specialization.

   The following ClassWrap policies are set up:

   - WeakWrap
   - Extract
   - ToNative
   - ToJS
   - ClassName if CLASSWRAP_BOUND_TYPE_NAME is set.


   If CLASSWRAP_BOUND_TYPE is defined:
   
   This file also sets up JSToNative and convert::NativeToJS
   specializations which use the ToNative/ToJS policies.

   If the following policies were customized by the INHERITED type,
   the subclass must also implement them identically:

   - ToNative_SearchPrototypesForNative<T>
   - InternalFields<T> 

   See ClassWrap-InheritOptions.h for one way to do that.
   
*/
namespace v8 { namespace juice { namespace cw {
    namespace convert = v8::juice::convert;
    namespace Detail
    {
	/**
	   An internal helper type for only use by certain ClassWrap
	   policy classes. It holds two-way bindings between
           JS and native objects.
	*/
	template <typename T>
	struct ClassWrapMapper
	{
            typedef ::v8::juice::convert::TypeInfo<T> TypeInfo;
            typedef typename TypeInfo::Type Type;
            /**
               The native type to bind to.
            */
            typedef typename TypeInfo::NativeHandle NativeHandle;
            /** The type for holding the JS 'this' object. */
            typedef v8::Persistent<v8::Object> JSObjHandle;
            //typedef v8::Handle<v8::Object> JSObjHandle; // Hmmm.
            typedef std::pair<NativeHandle,JSObjHandle> ObjBindT;
	    typedef std::map<void const *, ObjBindT> OneOfUsT;
            /** Maps (void const *) to ObjBindT. */
	    static OneOfUsT & Map()
	    {
		static OneOfUsT bob;
		return bob;
            }

            /** Maps obj as a lookup key for jself. Returns false if !obj,
             else true. */
            static bool Insert( //v8::Handle<v8::Object> const & jself,
                                JSObjHandle const & jself,
                                NativeHandle obj )
            {
                return obj
                    ? (Map().insert( std::make_pair( obj, std::make_pair( obj, jself ) ) ),true)
                    : 0;
            }

            /**
               Removes any mapping of the given key. Returns the
               mapped native, or 0 if none is found.
            */
            static NativeHandle Remove( void const * key )
            {
                typedef typename OneOfUsT::iterator Iterator;
                OneOfUsT & map( Map() );
                Iterator it = map.find( key );
                if( map.end() == it )
                {
                    return 0;
                }
                else
                {
                    NativeHandle victim = (*it).second.first;
                    map.erase(it);
                    return victim;
                }
            }

            /**
               Returns the native associated (via Insert())
               with key, or 0 if none is found.
            */
            static NativeHandle GetNative( void const * key )
            {
                if( ! key ) return 0;
                else
                {
                    typename OneOfUsT::iterator it = Map().find(key);
                    return (Map().end() == it)
                        ? 0
                        : (*it).second.first;
                }
            }

            /**
               Returns the JS object associated with key, or
               an empty handle if !key or no object is found.
            */
            static Handle<Object> GetJSObject( void const * key )
	    {
                if( ! key ) return Handle<Object>();
                typename OneOfUsT::iterator it = Map().find(key);
                if( Map().end() == it ) return Handle<Object>();
                else return (*it).second.second;
	    }
        };

    }

    
    /**
       A concrete WeakWrap policy which uses an internal
       native/js mapping for type-safe lookups later on.
    */
    template <typename T>
    struct TwoWayBind_WeakWrap
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        /**
           Installs a type-safe connection between jsSelf and nativeSelf.
        */
        static void Wrap( v8::Persistent<v8::Object> const & jsSelf, NativeHandle nativeSelf )
        {
            typedef Detail::ClassWrapMapper<T> Mapper;
            Mapper::Insert( jsSelf, nativeSelf );
            return;
        }
        /**
           Removes the type-safe connection between jsSelf and nativeSelf.
        */
        static void Unwrap( v8::Handle<v8::Object> const & /*jsSelf*/, NativeHandle nativeSelf )
        {
            typedef Detail::ClassWrapMapper<T> Mapper;
            Mapper::Remove( nativeSelf );
            return;
        }
    };

    /**
       A concrete ToNative policy which uses a type-safe
       native conversion.
    */
    template <typename T>
    struct TwoWayBind_Extract : Extract_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        /**
        */
        static NativeHandle VoidToNative( void * x )
        {
            typedef Detail::ClassWrapMapper<T> Mapper;
#if 1
            return Mapper::GetNative(x);
            /**
               The only works with native inheritance if
               CLASSWRAP_BOUND_TYPE_INHERITS is used!
            */
#else
            if( ! x ) return 0;
            else
            {
                NativeHandle y = Mapper::GetNative(x);
                if( ! y )
                {
                    y = NativeInheritance<T>::CheckForSubclass(x);
                    CERR << "VoidToNative( @"<<(void const *)x<<" ) subclass lookup got: @"<<(void const *)y<<"\n";
                }
                return y;
            }
#endif
        }
    };


    /**
       A concrete ToJS implementation which works with the other
       TwoWayBind policy classes to perform a type-safe conversion
       from T to JS.
    */
    template <typename T>
    struct TwoWayBind_ToJS
    {
    public:
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        typedef const Type * ArgType; // const'ing NativeHandle isn't working for me?
        /**
           Returns the JS object associated with nh, or an empty handle if
           none is found.
        */
        static v8::Handle<v8::Value> Value( ArgType nh )
        {
            typedef Detail::ClassWrapMapper<T> Mapper;
            return Mapper::GetJSObject( nh );
            /**
               Only works with inheritance if CLASSWRAP_BOUND_TYPE_INHERITS
               is used!
            */
        }
    };

} } }
#endif // V8_JUICE_CLASSWRAP_TWOWAY_INCLUDED

#if defined(CLASSWRAP_BOUND_TYPE)
////////////////////////////////////////////////////////////////////////
// Set up inheritance...
namespace v8 { namespace juice { namespace cw {

    template <>
    struct ToNative< CLASSWRAP_BOUND_TYPE > :
        ToNative_Base< CLASSWRAP_BOUND_TYPE >
    {
    };

    template <>
    struct Extract< CLASSWRAP_BOUND_TYPE > :
        TwoWayBind_Extract< CLASSWRAP_BOUND_TYPE > {};

    template <>
    struct ToJS< CLASSWRAP_BOUND_TYPE > :
        TwoWayBind_ToJS< CLASSWRAP_BOUND_TYPE > {};

#if defined(CLASSWRAP_BOUND_TYPE_NAME)
    template <>
    struct ClassName< CLASSWRAP_BOUND_TYPE >
    {
        static char const * Value()
        {
            return CLASSWRAP_BOUND_TYPE_NAME;
        }
    };
#undef CLASSWRAP_BOUND_TYPE_NAME
#endif


#if !defined(CLASSWRAP_BOUND_TYPE_INHERITS)
    template <>
    struct WeakWrap< CLASSWRAP_BOUND_TYPE > :
        TwoWayBind_WeakWrap< CLASSWRAP_BOUND_TYPE > {};
#else // We need to do some work to get ToJS and inheritance-based lookups working...
    /**
       Tells the bind system that objects of CLASSWRAP_BOUND_TYPE are
       also of type CLASSWRAP_BOUND_TYPE_INHERITS. And it only costs
       twice the memory of a single binding!
    */
    template <>
    struct WeakWrap< CLASSWRAP_BOUND_TYPE >
    {
        typedef CLASSWRAP_BOUND_TYPE T;
        typedef convert::TypeInfo<T>::Type Type;
        typedef convert::TypeInfo<T>::NativeHandle NativeHandle;
        typedef Detail::ClassWrapMapper<T> Mapper;
        typedef WeakWrap<CLASSWRAP_BOUND_TYPE_INHERITS> WB;
        /**
           Creates bindings for this object, such that it is both
           a CLASSWRAP_BOUND_TYPE and CLASSWRAP_BOUND_TYPE_INHERITED
           for type conversions purposes.
        */
        static void Wrap( v8::Persistent<v8::Object> const & jsSelf, NativeHandle nativeSelf )
        {
            WB::Wrap( jsSelf, nativeSelf );
            Mapper::Insert( jsSelf, nativeSelf );
            return;
        }
        /**
           Undoes the binding installed by Wrap().
        */
        static void Unwrap( v8::Handle<v8::Object> const & jsSelf, NativeHandle nativeSelf )
        {
            WB::Unwrap( jsSelf, nativeSelf );
            Mapper::Remove( nativeSelf );
            return;
        }
    };
#undef CLASSWRAP_BOUND_TYPE_INHERITS
#endif // CLASSWRAP_BOUND_TYPE_INHERITS

    
} // namespace cw


    namespace convert
    {
        /**
           NativeToJS<CLASSWRAP_BOUND_TYPE> specialization which uses
           the TwoWay ClassWrap policy set to implement the conversion.
         */
        template <>
        struct NativeToJS< CLASSWRAP_BOUND_TYPE > : v8::juice::cw::NativeToJSImpl< CLASSWRAP_BOUND_TYPE >
        {};
    }

} } // namespace v8::juice


// #if defined(CLASSWRAP_BOUND_TYPE_INHERITS)
// #  include "ClassWrap-InheritOptions.h"
// #  undef CLASSWRAP_BOUND_TYPE_INHERITS
// #endif

#include "ClassWrap-JSToNative.h" // will undefine CLASSWRAP_BOUND_TYPE
#endif //CLASSWRAP_BOUND_TYPE
