#if !defined(CODE_GOOGLE_COM_P_V8_V8_WEAKCLASSGENERATOR_H_INCLUDED)
#define CODE_GOOGLE_COM_P_V8_V8_WEAKCLASSGENERATOR_H_INCLUDED 1
/*
   Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)

   License: same as v8 (see below)
*/
// Copyright 2009 Stephan Beal. All rights reserved.  Redistribution
// and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
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

#include <v8.h>

#include <v8/juice/JSClassCreator.h>
#include <string>
#include <stdexcept>
#include <map>
#include <set>
#include <sstream>

#if 0
#ifndef CERR
#include <iostream> /* only for debuggering */
#define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif
#endif

#if 0
#ifndef CERR
#include <iostream> /* only for debuggering */
#define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif
#endif

#if 1
/*
  Static assertion code taken from Alexandrescu's Modern C++ Design.

  Args:

  'test' is a compile-time condition which evaluates to true or
  false. If false, it triggers the instantiation of an incomplete
  class, with the error message encoded in the class name.

  'errormsg' is an identifier which forms the error text (no spaces!).
  e.g. Illegal_argument_combination.
*/

#   define JUICE_COMPILE_ASSERT(test, errormsg)                         \
    do {                                                        \
        struct ERROR_##errormsg {};                             \
        typedef ::v8::juice::Detail::compile_assert< (test) != 0 > tmplimpl; \
        tmplimpl aTemp = tmplimpl(ERROR_##errormsg());          \
        (void) sizeof(aTemp);                                    \
    } while (0)
#else
#   define JUICE_COMPILE_ASSERT(test, errormsg)                         \
    do {(void)1;} while (0)
#endif

namespace v8 {
namespace juice {

#if !defined(DOXYGEN)

    namespace Detail
    {
        template<bool> class compile_assert
        {
        public:
            compile_assert(...) {}
        };
        
        template<> class compile_assert<false>
        {
        };
    }
    namespace Detail
    {
	/**
	   An internal helper type for only use by WeakJSClassCreator.

	   WrappedT must be WeakJSClassCreator::WrappedType.
	*/
	template <typename WrappedT>
	struct WrapperMapper
	{
	    typedef WrappedT WrappedType;
	    
            typedef std::pair<WrappedType *,Persistent<Object> > ObjBindT;
	    typedef std::map<void const *,ObjBindT > OneOfUsT;
	    static OneOfUsT & Map()
	    {
		static OneOfUsT bob;
		return bob;
	    }
            
            static WrappedType * GetNative( void const * key )
            {
                typename OneOfUsT::iterator it = Map().find(key);
                return (Map().end() == it)
                      ? 0
                      : (*it).second.first;
            }
            
            static Handle<Object> GetJSObject( void const * key )
	    {
                typename OneOfUsT::iterator it = Map().find(key);
                if( Map().end() == it ) return Handle<Object>();
                else return (*it).second.second;
	    }
        };
    }
#endif // DOXYGEN
    /**
       Any type used with WeakJSClassCreator must provide a
       specialization of this type and provide all of the functions,
       typedefs, and constants described herein.
    */
    template <typename T>
    struct WeakJSClassCreatorOps
    {
	/**
	   This type's associated native type. In specializations,
	   T *may* differ from WrappedType, and WrappedType
	   is the definition that WeakJSClassCreator will use
	   as a parameter type. This has some odd uses, actually,
	   such as matching multiple logical JS types to a single
	   native data type.
	*/
	typedef T WrappedType;

	enum {
	/**
	   Must be defined to the number of internal fields
	   which client code will need for each instance
	   of the wrapped object.

	   WeakJSClassCreator will automatically allocate one
	   additional field and store the underlying native object in
	   the *last* internal field (so clients can work with fields
	   0..N as normal, without having to take too much care to not
	   step on this class' slot).
	*/
	ExtraInternalFieldCount = 0
	};

	/**
	   This will be called in response to calling
	   "new WrappedType(...)" in JS code. It should:

	   - Create a new native object.

	   - If successful, return that object.

	   - On error, return 0 and optionally populate the (string &)
	   argument with an informative error message (e.g. "requires
	   arguments (String,Integer)").

	   If the client is using any "supplemental" garbage collection
	   (e.g. the v8::juice::cleanup API) then they should
	   register the object in this function and deregister
           it in Dtor().
	*/
	static WrappedType * Ctor( Arguments const &  /*argv*/,
				   std::string & /*exceptionText*/);

	/**
	   Must "destroy" the given object, though the exact meaning
	   of "destroy", and mechanism of destruction, is
	   type-specific.

	   This function is responsible for destroying the native
	   object. Most implementations must simply call "delete obj",
	   which is fine for many types, but opaque types and types
	   allocated via something other than 'new' will need a
	   different implementation. A destructor functor for shared,
	   static, or stack-allocated objects should simply do nothing
	   (or maybe clear the object to some empty/default state).

	   If the client is using any "supplemental" garbage collection
	   (e.g. the v8::juice::cleanup API) then they should
	   deregister the object in this function.
	*/
	static void Dtor( WrappedType * obj );

	/**
	   Must return the JS-side class name of this type. It must be
	   a legal JS function name.

	   Design note: this is a static function instead of a static
	   string member because this requires much less code from
	   implementors (whereas a string string requires out-of-class
	   initialization).
	*/
	static char const * ClassName();
    };

    /** Required specialization for certain template type passing to work as expected. */
    template <typename T>
    struct WeakJSClassCreatorOps<T const> : WeakJSClassCreatorOps<T> {};
    /** Required specialization for certain template type passing to work as expected. */
    template <typename T>
    struct WeakJSClassCreatorOps<T *> : WeakJSClassCreatorOps<T> {};
    /** Required specialization for certain template type passing to work as expected. */
    template <typename T>
    struct WeakJSClassCreatorOps<T const *> : WeakJSClassCreatorOps<T> {};

    /**
       WeakOpsNoop is a helper for use in the early stages of
       implementing WeakJSClassCreatorOps specializations. The idea is
       that one's own WeakJSClassCreatorOps specialization inherits
       this type to get dummy/empty functionality, so it'll at least
       it'll compile before one has to implement the Ctor() and Dtor()
       members. Once the custom implementation has all of the required
       members, there is no need to inherit this class (unless one only
       wants to inherit the WrappedType typedef).

       Because there is no sensible default value for a class' name,
       the ClassName() member must be implemented even when subclassing
       this type.
    */
    template <typename T, int FieldCount = 0>
    struct WeakOpsNoop
    {
	/** See WeakJSClassCreatorOps::WrappedType. */
	typedef T WrappedType;
	/** See WeakJSClassCreatorOps::ExtraInternalFieldCount. */
	enum { ExtraInternalFieldCount = FieldCount };
	/** Triggers a "not yet implemented" exception. */
	static WrappedType * Ctor( Arguments const &  /*argv*/,
				   std::string & exceptionText)
	{
	    exceptionText = "WeakOpsNoop<T>::Ctor() not implemented!";
	    return 0;
	}
	/** Warning - Does Nothing! Implement this in specializations! */
	static void Dtor( WrappedType * obj )
	{
	    return 0;
	}
    };
    template <bool Val>
    struct WeakJSClassCreator_Opt_Bool
    {
        static const bool value = Val;
    };
    /**
       HIGHLY EXPERIMENTAL!

       Specializations may be defined for any type supported by
       WeakClassCreatorOps<T>.  If they define their "value" member to
       true then certain WeakJSClassCreator conversion operations will
       bypass the type-safe lookup table and will use static_cast<>()
       for the conversion, using the (void *) taken from
       External::Value() as the source. This is faster but cause
       certain problems in conjunction with inheritance (he says, very
       vaguely).

       Shallow-bound objects have (at least) the following
       limitations:

       - Conversions from Native-to-JS via the juice conversions API
       will not work, as the native has no notion of its JS
       representation.

       - Inheritance will not work properly in all cases where bound
       classes inherit other bound classes, or JS-side classes inherit
       bound classes. e.g. virtual members inherited from the native
       API may not be visible to the JS API.
    */
    template <typename T>
    struct WeakJSClassCreator_Opt_ShallowBind : WeakJSClassCreator_Opt_Bool<false>
    {};

    /**
       This template defines the default value of
       WeakJSClassCreator<T>::AllowCtorWithoutNew(). Specializations
       may redefine the inherited 'value' member.
    */
    template <typename T>
    struct WeakJSClassCreator_Opt_AllowCtorWithoutNew : WeakJSClassCreator_Opt_Bool<true>
    {};

    /**
       WeakJSClassCreator is a tool to simplify the creation of new
       wrapped classes, including addition of automatic cleanup handling
       via weak-pointer callbacks.

       It is used almost exactly like JSClassGenerator, but adds some
       features (and requirements) for handling JS weak pointers to
       arbitrary types. It combines three forms of deletion for bound
       objects:

       - Via v8's weak pointers, the native will be deleted *if* (BIG
       *if*) the gc is triggered and the pointer is due for deletion.
       An option is provided to support external garbage collection,
       in case calling dtors is an absolute must for your types.

       - If the client calls the static DestroyObject() function of
       this class. This also disposes the underlying weak pointers, so
       they won't point back to the object anymore. This allows us to
       implement member function which disconnect from the underlying native
       object (e.g. File.close()).

       The template argument, WrappedT, is the native type we will
       wrap, non-CVP qualified. It is actually legal to use a type other
       than the real native we will wrap, as long as the WeakJSClassCreatorOps
       specialization (see below) provides us with the real type.

       However, the client must also provide a specialization of WeakJSClassCreatorOps
       for the given type. That specialization must conform to the API defined
       in the base template definition (which is not implemented and cannot be
       instantiated).

       The WeakJSClassCreatorOps specialization is a helper which
       defines the core-most operations needed by this class. See the
       docs for WeakJSClassCreatorOps for how types consistent with
       its interface should behave.

       The wrapper works basically like this:

       When, in JS code, "new MyType(...)" is called, this call arranges
       to have a private constructor called. That contructor does the following:

       - Passes the Arguments array to ClassOpsType::Ctor(). If the
       ctor returns 0, the construction fails and throws and
       exception. If the exceptionText string (2nd parameter to
       ClassOpsType::Ctor()) is non-empty when the ctor returns, the
       private constructor will destroy the returned object (if
       necessary) using ClassOpsType::Dtor() and throw a JS exception
       using the exceptionText string.

       - The argv.This() argument passed to ClassOpsType::Ctor() is
       the "this" object of the "real" constructor.

       - If ClassOpsType::Ctor() succeeds (returns non-0) then the new
       object is bound to a weak pointer and gives the new weak
       pointer to v8. It will also add the native as an External in
       the Nth internal slot, where N is the
       WeakJSClassCreatorOps<WrappedT>::ExtraInternalFieldCount. This
       class reserves one extra slot at the end of the list for storing
       the native, so there will always be at least one slot.

       It's a lot simpler than it sounds and completely frees the caller of
       worry of setting up weak pointer callback handling.

       Example usage:

       First we need a custom WeakJSClassCreatorOps specialization. Here's
       a minimal (but functional) implementation:

       \code
       struct MyTypeOps
       {
           typedef MyClass WrappedType;
	   enum { ExtraInternalFieldCount = 0 };
           static MyType * Ctor( Arguments const & argv, std::string & exceptionText)
	   {
	       return new MyType;
	   }
	   static void Dtor( MyType * obj )
	   {
	       if(obj) delete obj;
	   }
	   static char const * ClassName()
	   {
	       return "MyClass";
	   }
       };
       namespace v8 { namespace juice {
           // Required specialization of WeakJSClassCreatorOps:
           template <>
           WeakJSClassCreatorOps<MyType> : MyTypeOps {};
	   // We could have done it without subclassing, but this is copy/paste code
	   // from a working implementation ;)
       }}
       \endcode

       Now we can use the class creator:

       \code
       ...
       // Add the class to JS:
       typedef WeakJSClassCreator<MyType> WC;
       WC c( "MyType", objectToAddClassTo );
       c.Set(...)
         .Set(...)
	 .Set(...)
	 .Set(...)
	 .Seal(); // must be the last setter call made on this object.
       \endcode

       That's all there is to it. More functionality is provided via
       the JSClassCreator base class, and there are several static
       member functions for "casting" between the JS/Native worlds
       and for destroying instances of the generated class.
    */
    template <typename WrappedT>
    class WeakJSClassCreator : public JSClassCreator
    {
    public:
        /**
           See WeakJSClassCreator_Opt_ShallowBind<> for the complete
           docs.
        */
        static const bool OptShallowBind = WeakJSClassCreator_Opt_ShallowBind<WrappedT>::value;

	/**
	   The WeakJSClassCreatorOps specialization used by this
	   class.
	*/
	typedef WeakJSClassCreatorOps<WrappedT> ClassOpsType;

	/**
	   The actual native type wrapped by this class, which may
	   be different from the WrappedT template parameter!
	*/
	typedef typename ClassOpsType::WrappedType WrappedType;

    private:
	enum Internal {
	/** The internal field number where we store the wrapped object. */
	NativeFieldIndex = ClassOpsType::ExtraInternalFieldCount,
	/** The number of internal fields. */
	FieldCount = NativeFieldIndex + 1
	};
        
        enum Options {
        OptSearchPrototypesForNative = 0,
        OptAllowCtorWithoutNew = 1,
        OptCount
        };

        static int* options()
        {
            static int bob[OptCount] =
                {
                0, // OptSearchPrototypesForNative
                WeakJSClassCreator_Opt_AllowCtorWithoutNew<WrappedT>::value ? 1 : 0  // OptAllowCtorWithoutNew
                };
            return bob;
        }

        typedef WrappedType * (*SubclassGetNative)( void const * );
        typedef std::set<SubclassGetNative> SubclassGetNatives;

        /** Internal helper to do subtype lookups for GetSelf(). */
        static SubclassGetNatives & subclassGettersN()
        {
            static SubclassGetNatives bob;
            return bob;
        }
        /** Internal helper to do subtype lookups for GetSelf().
            SubT MUST NOT be WrappedType, or an endless loop
            may lead to a stack overflow.
         */
        template <typename SubT>
        static WrappedType * GetInheritedNative( void const * key )
        {
            typedef WeakJSClassCreatorOps<SubT> OpsT;
            typedef typename OpsT::WrappedType RealT;
            return Detail::WrapperMapper<RealT>::GetNative( key );
        }

        typedef Handle<Object> (*SubclassGetJSObject)( void const * );
        typedef std::set<SubclassGetJSObject> SubclassGetJSObjects;

        /** Internal helper to do subtype lookups for GetJSObject(). */
        static SubclassGetJSObjects & subclassGettersJ()
        {
            static SubclassGetJSObjects bob;
            return bob;
        }

        /** Internal helper to do subtype lookups for GetJSObject(). */
        template <typename SubT>
        static Handle<Object> GetInheritedJSObject( void const * key )
        {
            typedef WeakJSClassCreatorOps<SubT> OpsT;
            typedef typename OpsT::WrappedType RealT;
            return Detail::WrapperMapper<RealT>::GetJSObject( key );
        }

        /**
           If h is-an Object then retun GetSelf( h->GetPrototype(),
           checkSubclasses ), else return 0.

           If options()[OptSearchPrototypesForNative] is 0 then this function
           always returns 0.
        */
	static WrappedType * GetSelfFromPrototype( Handle<Object> const & h, bool checkSubtypes = true )
        {
            if( options()[OptSearchPrototypesForNative] )
            {
                Local<Value> pv( h->GetPrototype() );
                if( pv.IsEmpty() || ! pv->IsObject() ) return 0;
                return GetSelf( Handle<Object>( Object::Cast(*pv) ), checkSubtypes );
            }
            else
            {
                return 0;
            }
        }

    public:
	/**
	   Starts the setup of a new class. It will be populated into
	   the target object when Seal() is called.  See the
	   JSClassCreator ctor for more information on that process.
	*/
	explicit WeakJSClassCreator( Handle<Object> target)
	    : JSClassCreator( ClassOpsType::ClassName(),
			      target,
			      ctor_proxy,
			      static_cast<int>(FieldCount) )
	{
	}

	/**
	   Identical to the 1-arg ctor except that it does not take a
	   target object. The implications of this are:

	   - The Target() member will return an empty handle.
	   - The caller must add this class to his chosen target manually,
	   as demonstrated here:

	   \code
	   target->Set( v8::String::New("ClassName"), myCreator.Seal() );
	   \endcode

	   That will "close off" the class creation process and add the new class
	   to the target object.
	*/
	WeakJSClassCreator()
	    : JSClassCreator( ClassOpsType::ClassName(),
			      ctor_proxy,
			      static_cast<int>(FieldCount) )
	{
	}
        /** Does nothing. Is virtual to satisfy inheritance rules and please my compiler. */
	virtual ~WeakJSClassCreator(){}
        
        /**
           Registers SubT as a subtype of WrappedType, but ONLY for
           purposes of GetSelf() and GetJSObject() lookups. When
           GetSelf() or GetJSObject() is called, if they can find no
           native object in the WrappedType pool they will check each
           type registered subtype here (in an inspecified order).

           Why? Because this allows us to properly get at the 'this'
           pointer from inherited member functions in wrapped classes,
           and do to do transparently using CastFromJS<WrappedType>().

           SubT must meet these requirements:

           - WeakJSClassCreator<SubT>::WrappedType must be a virtual subclass of WrappedType.

           - SubT must also be wrapped using WeakJSClassCreator.

           - The WeakJSClassCreatorOps specializations for SubT and
           WrappedType must have the same values for
           ExtraInternalFieldCount. This is a bug without a current
           workaround, and this function throws a native exception if
           the values do not match.

           If those conditions are met, then calls to GetSelf(),
           GetJSObject(), and GetNative() using type
           WeakJSClassCreator<WrappedT> might actually return an
           object of SubT instead.

           FIXME: use metatemplates to determine if SubT is the same
           type as WrappedType.
         */
        template <typename SubT>
        static void RegisterSelfSubclass()
        {
            JUICE_COMPILE_ASSERT((!OptShallowBind),RegisterSelfSubclass_cannot_work_because_OptShallowBind_is_true);
            typedef WeakJSClassCreatorOps<SubT> SubOpsT;
            if( static_cast<int>(SubOpsT::ExtraInternalFieldCount)
                != static_cast<int>(ClassOpsType::ExtraInternalFieldCount) )
            {
                /** reminder to self: the reason this cannot currently
                    work is because of how we stuff the native object
                    in the last-available internal field.
                 */
                throw std::runtime_error("WeakJSClassCreatorOps<WrappedT>::ExtraInternalFieldCount != WeakJSClassCreatorOps<SubT>::ExtraInternalFieldCount");
            }
            subclassGettersN().insert( GetInheritedNative<SubT> );
            subclassGettersJ().insert( GetInheritedJSObject<SubT> );
        }

        using JSClassCreator::Inherit;

        /**
           Reimplemented to throw a std::exception if OptShallowBind
           is true, as inheritance cannot work properly when the
           shallow binding optimization is enabled. To get a compile-time
           error in this case, use the non-inherited Inherit() overload
           or InheritNative().
        */
	virtual JSClassCreator & Inherit( v8::Handle< v8::FunctionTemplate > parent )
        {
            if( OptShallowBind )
            {
                //JUICE_COMPILE_ASSERT((OptShallowBind==false),WeakJSClassCreator_T_Inherit_cannot_work_because_WeakJSClassCreator_T_OptShallowBind_is_true);
                throw std::runtime_error("WeakJSClassCreator<T> cannot work for this type because WeakJSClassCreator<T>::OptShallowBind is true!");
            }
            return this->JSClassCreator::Inherit( parent );
        }
        
        /**
           This sets up "native" inheritance, such that bound
           WrappedType objects can be converted to a baser type.

           Calling this function will trigger a compile-time error if
           OptShallowBind is on, since inheritance cannot work in that
           case.
           
           ParentT must meet these requirements:

           - WeakJSClassCreatorOps<ParentT>::WrappedType must be a
           virtual base type of WrappedType.

           - ParentT must also be wrapped using WeakJSClassCreator.

           - The WeakJSClassCreatorOps specializations for ParentT and
           WrappedType must have the same values for
           ExtraInternalFieldCount. This is a bug without a current
           workaround, and this function throws a native exception if
           the values do not match.

           If those conditions are met, then calls to GetSelf(),
           GetJSObject(), and GetNative() using type
           WeakJSClassCreator<ParentT> might actually return an object
           of WrappedType instead.

           This function is basically a thin proxy for RegisterSelfSubclass(),
           except that it is called from the subclass instance, not the parent
           class.
        */
        template <typename ParentT>
        WeakJSClassCreator & InheritNative()
        {
            typedef WeakJSClassCreator<ParentT> ParT;
            ParT::template RegisterSelfSubclass< WrappedT >();
            return *this;
        }

        /**
           Like the inherited non-template member of the same name but
           also calls InheritNative<ParentT>().
        */
        template <typename ParentT>
        WeakJSClassCreator & Inherit( WeakJSClassCreator<ParentT> & parent )
        {
            JUICE_COMPILE_ASSERT((!OptShallowBind),Inherit_cannot_work_because_OptShallowBind_is_true);
            this->template InheritNative<ParentT>();
            this->Inherit( parent.CtorTemplate() );
            return *this;
        }

	/**
	   Returns the bound native for the given handle. The handle
	   is assumed to have been created using this class'
	   mechanisms. If it was not, this routine will return 0.

	   Ownership of the returned object remains unchanged.

	   Results are technically undefined if the given handle has
	   not created by this class, but this function makes every
	   effort to ensure that it doesn't do anything too stupid.

           If checkSubtypes is true (the default) and no WrappedType
           object can be found for h, then WeakJSClassCreator<X> is
           checked, where X is a subtype of WrappedType registered via
           RegisterSelfSubclass().  All such registered types are
           checked (in an unspecified order) until a match is found,
           and 0 is returned if no match is found.
	*/
	static WrappedType * GetSelf( Handle<Object> const & h, bool checkSubtypes = true )
	{
	    if( h.IsEmpty() ) return 0;
            if( h->InternalFieldCount() != FieldCount ) return GetSelfFromPrototype(h,checkSubtypes);
            /// ^^^^ reminder: that FieldCount check won't work with inheritance if subtypes have different counts :(
            /// we might have to start reserving slot 0 for ourselves, as opposed to the last slot. Hmmm. Ugly.
	    Local<Value> lv( h->GetInternalField(NativeFieldIndex) );
            if( lv.IsEmpty() || !lv->IsExternal() ) return GetSelfFromPrototype(h,checkSubtypes);
	    Local<External> ex( External::Cast(*lv) );
            if( OptShallowBind )
            {
                //CERR << "SHALLOW-CASTING GetSelf()!\n";
                WrappedType * obj = static_cast<WrappedType*>( ex->Value() );
#if 0
                /**
                   To consider: we could do a lookup in
                   bind::GetBoundNative(), as that would allow the
                   cases where the client explicitly bound the object.
                */
                if( ! obj )
                {
                    obj = ::v8::juice::bind::GetBoundNative<WrappedType>( ex->Value() );
                }
#endif
                return obj;
            }
            else
            {
                WrappedType * obj = TypeCheck::GetNative( ex->Value() );
                if( obj ) return obj;
                if( !checkSubtypes ) return GetSelfFromPrototype(h,checkSubtypes);
                typename SubclassGetNatives::iterator it = subclassGettersN().begin();
                typename SubclassGetNatives::iterator et = subclassGettersN().end();
                for( ; (!obj) && (et != it); ++it )
                {
                    obj = (*it)( ex->Value() );
                }
                return obj ? obj : GetSelfFromPrototype(h,checkSubtypes);
            }
	}

	/**
            Reimplemented to throw a native exception, as the number is defined
	    by the WeakJSClassCreatorOps specialization. When changing
	    it here, we lose the ability to know where the object
	    is in the list (since we store it at the end).
	*/
 	virtual WeakJSClassCreator & SetInternalFieldCount( int n )
 	{
	    //JSClassCreator::SetInternalFieldCount(n+1);
	    // gcc 4.3.2 won't allow this syntax: :-?
 	    //this->JSClassCreator::SetInteralFieldCount( n + 1 );
            throw ::std::runtime_error("SetInternalFieldCount() is not legal for WeakJSClassCreators because the field count is set via a WeakJSClassCreatorOps<> specialization.");
	    return *this; // avoid warning from some compilers, even though we throw
 	}

	/**
	   Like GetSelf(), but takes a Handle to a value. This can be
	   used for checking/converting arguments other than the
	   current This object (e.g., maybe the second argument to a
	   certain WrappedType member function is a different
	   WrappedType object).

	   This routine is more generic than GetSelf() and can always
	   be used in place of GetSelf(), but it does slightly more
	   work than GetSelf() has to.

           See GetSelf() for the explanation of the checkSubtypes
           argument.
	*/
        static WrappedType * GetNative( Handle<Value> const & h, bool checkSubtypes = true )
        {
            if( h.IsEmpty() || ! h->IsObject() ) return 0;
            Local<Object> obj( Object::Cast(*h) );
	    return GetSelf( obj, checkSubtypes );
        }

	/**
	   If jo "seems" to have been created via this class' mechanism,
	   then the behaviour is as-if the weak pointer callback has been
	   triggered. That will delete the bound native and dispose/clear the
	   persistent handle.

	   The reason this function exists is so that native implementations
	   of member functions can implement functions which logically destroy
	   the JS object. For example:

	   \code
	   var os = new OutStream(...);
	   ...
	   os.close();
	   \endcode

	   That code "should" destroy the underlying device and
	   disconnect the JS reference to that object, and it can use
	   this function to do so.

	   Returns true if it passes a native object to the
	   destructor, else false.

           BIG FAT HAIRY ACHTUNG:

           This function verifies the exact type of jo by calling
           GetSelf(jo,checkSubclasses). If checkSubclasses is true
           then it is the client's responsibility to ensure that the
           destructor functions (WeakJSClassCreatorOps<>::Dtor()) for
           both WrappedType and the actual registered subtype of the
           object are equivalent. What that means is: if the subtype's
           destructor simply calls "delete obj", and the base type
           destructor does the same thing, then it is safe for the
           subtype to use the base's destructor functions. If, on the
           other hand, the subtype's destructor needs to do some
           custom handling, then by all means use
           (checkSubclasses==false) to ensure that
           WeakJSClassCreator<WrappedType> will not try to pass a
           pointer of type WrappedSubType to
           WeakJSClassCreatorOps<WrappedType>::Dtor().
	*/
	static bool DestroyObject( Handle<Object> const & jo, bool checkSubclasses = false )
	{
	    WrappedType * t = GetSelf(jo,checkSubclasses); // sanity check
	    if( ! t ) return false;
	    Persistent<Object> p( Persistent<Object>::New( jo ) );
	    weak_callback( p, t );
	    return true;
	}

	/**
	   Like the other DestroyObject() overload, but takes a handle
	   to a generic value. If h is not an Object reference, false
	   is returned, otherwise the result of calling the other overload
	   is returned.
	*/
        static bool DestroyObject( Handle<Value> h )
        {
            return ( h.IsEmpty() || ! h->IsObject() )
		? false
		: DestroyObject( Handle<Object>(Object::Cast(*h)) );
        }

	/**
	   If obj was created via these bindings then this function
	   returns obj's JS object, otherwise it returns a
	   default-constructed (empty) handle.

           See GetSelf() for an explanation of the checkSubclasses
           parameter.
	*/
	static Handle<Object> GetJSObject( void const * obj, bool checkSubclasses = true )
	{
            if( OptShallowBind )
            {
                static char const * msg = "WeakJSClassCreator<T>::GetJSObject() cannot work for this type because WeakJSClassCreator<T>::OptShallowBind is true!";
                v8::ThrowException(v8::String::New(msg));
                /** Reminder: we cannot static assert here because
                    this code gets generated for all wrapped types,
                    but not all may actually USE these conversions.
                 */
                //JUICE_COMPILE_ASSERT((OptShallowBind==false),WeakJSClassCreator_T_GetJSObject_cannot_work_for_this_type_because_WeakJSClassCreator_T_OptShallowBind_is_true);
                return v8::Handle<v8::Object>();
            }
            else
            {
                Handle<Object> jo = TypeCheck::GetJSObject(obj);
                if( !checkSubclasses || !jo.IsEmpty() ) return jo;
                typename SubclassGetJSObjects::iterator it = subclassGettersJ().begin();
                typename SubclassGetJSObjects::iterator et = subclassGettersJ().end();
                for( ; (et != it) && jo.IsEmpty(); ++it )
                {
                    jo = (*it)( obj );
                }
                return jo;
            }
            // won't get here
	}

        // Without this, gcc isn't seeing the two-arg overload!
        using JSClassCreator::NewInstance;

	/**
	   Similar to the two-argument form of NewInstance(), but on
	   success it assigns obj to the new native object.
	*/
	Handle<Object> NewInstance( int argc, Handle<Value> argv[], WrappedType * & obj )
	{
	    Local<Object> ji = JSClassCreator::NewInstance( argc, argv );
	    if( ! ji.IsEmpty() && ji->IsObject() )
	    {
		obj = GetNative( ji );
	    }
	    return ji;
	}
//         /** Experimental. */
//         static WeakJSClassCreator & Instance()
//         {
//             static WeakJSClassCreator shared_inst;
//             return shared_inst;
//         }

        /**
           Setting this option to true changes GetSelf()'s behaviour
           somewhat. If the 'this' object cannot be associated with a
           native object, then this.prototype will be checked.  This
           option defaults to off because it is a performance hit on
           every call to GetSelf() and friends, and it is normally
           only useful when JS-side classes need to inherit a native
           type.
        */
        static void SearchPrototypesForNative( bool b )
        {
            options()[OptSearchPrototypesForNative] = (b ? 1 : 0);
        }

        /**
           If this option is set to true (it defaults to false)
           then calling 'MyWrappedType()' in JS code is the same
           as calling 'new MyWrappedType()'. If this option is false,
           the former syntax will cause an exception to be thrown.
        */
        static void AllowCtorWithoutNew( bool b )
        {
            options()[OptAllowCtorWithoutNew] = (b ? 1 : 0);
        }

    private:
	typedef Detail::WrapperMapper<WrappedType> TypeCheck;
	typedef typename TypeCheck::ObjBindT ObjBindT;
	typedef typename TypeCheck::OneOfUsT OneOfUsT;
	typedef typename OneOfUsT::iterator TypeCheckIter;
	static OneOfUsT & typeCheck()
	{
	    // We must use a map instance defined OUTSIDE of this class
	    // for this binding to work properly. More correctly,
	    // the instance of the map must depend only on WrappedType.
	    return TypeCheck::Map();
	}

	/**
	   Only called by v8 GC. It unbinds the native object from
           pv and calls ClassOpsType::Dtor() on it. After this call,
           pv will no longer contain a reference to the native.
	*/
	static void weak_callback(Persistent< Value > pv, void * nobj)
	{
	    //CERR << "weak callback @"<<nobj<<"\n";
            HandleScope handle_scope;
	    Local<Object> jobj( Object::Cast(*pv) );
	    if( jobj->InternalFieldCount() != (FieldCount) ) return; // how to warn about this?
	    Local<Value> lv( jobj->GetInternalField(NativeFieldIndex) );
	    if( lv.IsEmpty() || !lv->IsExternal() ) return; // how to warn about this?
            if( ! OptShallowBind )
            {
                TypeCheckIter it = typeCheck().find( nobj );
                if( typeCheck().end() == it ) // serious error
                {
                    return;
                }
                WrappedType * victim = (*it).second.first;
                typeCheck().erase(it);
                ClassOpsType::Dtor( victim );
            }
            else
            {
                //CERR << "SHALLOW-CAST DTOR!!!\n";
                ClassOpsType::Dtor( static_cast<WrappedType*>(nobj) );
            }
	    /**
	       We have to ensure that we have no dangling External in JS space. This
	       is so that functions like IODevice.close() can act safely with the
	       knowledge that member funcs called after that won't get a dangling
	       pointer. Without this, some code will crash in that case.
	    */
	    jobj->SetInternalField(NativeFieldIndex,Null());
	    pv.Dispose();
	    pv.Clear();
	}

	/**
	   "Wraps" a native pointer in a JS weak pointer. Returns the new
	   Persistent weak object, which is a wrapper for the self object.

	   Results are undefined if this function is called from anywhere
	   other than ctor_proxy().
	*/
	static Persistent<Object> wrap_native( Handle<Object> _self, WrappedType * obj )
	{
	    Persistent<Object> self( Persistent<Object>::New(_self) );
	    self.MakeWeak( obj, weak_callback );
	    self->SetInternalField( NativeFieldIndex, External::New(obj) );
            if( ! OptShallowBind )
            {
                typeCheck().insert( std::make_pair( obj, std::make_pair( obj, self ) ) );
            }
	    return self;
	}

	/**
	   Constructs a WrappedType by calling NativeConstructor. If it
	   succeeds, it returns wrap_native(), otherwise it throws.

	   Returns argv.This() unless it throws.
	 */
	static Handle<Value> ctor_proxy( const Arguments & argv )
	{
            if( options()[OptAllowCtorWithoutNew] )
            {
                /**
                   Allow construction without 'new' by forcing this
                   function to be called in a ctor context...
                */
                if (!argv.IsConstructCall()) 
                {
                    const int argc = argv.Length();
                    Handle<Function> ctor( Function::Cast(*argv.Callee()));
                    std::vector< Handle<Value> > av(static_cast<size_t>(argc),Undefined());
                    for( int i = 0; i < argc; ++i ) av[i] = argv[i];
                    return ctor->NewInstance( argc, &av[0] );
                }
            }
            else
            {
                /**
                   Why have this limitation? If we don't, v8 pukes when
                   the ctor is called, with
                   "v8::Object::SetInternalField() Writing internal field
                   out of bounds".
                */
                if (!argv.IsConstructCall()) 
                {
                    std::ostringstream os;
                    os << "The "<< ClassOpsType::ClassName() << " constructor cannot be called as function!";
                    return ThrowException(String::New(os.str().c_str()));
                }
            }
	    std::string err;
	    WrappedType * obj = 0;
	    try
	    {
		obj = ClassOpsType::Ctor( argv, err );
	    }
	    catch(std::exception const & ex)
	    {
		return ThrowException(String::New(ex.what()));
	    }
	    catch(...)
	    {
		return ThrowException(String::New("Native constructor threw an unknown native exception!"));
	    }
	    if( ! err.empty() )
	    {
		if( obj )
		{
		    ClassOpsType::Dtor(obj);
		    obj = 0;
		}
		return ThrowException(String::New(err.c_str(),static_cast<int>(err.size())));
	    }
	    if( ! obj )
	    {
		return ThrowException(String::New("Constructor failed for an unspecified reason!"));
	    }
	    return wrap_native( argv.This(), obj );
	}
    };

    
}} /* namespaces */

#endif /* CODE_GOOGLE_COM_P_V8_V8_WEAKCLASSGENERATOR_H_INCLUDED */

