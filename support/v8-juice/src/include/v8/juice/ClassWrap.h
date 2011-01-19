#if !defined(V8_JUICE_CLASSWRAP_H_INCLUDED)
#define V8_JUICE_CLASSWRAP_H_INCLUDED
/************************************************************************
  ClassWrap is one approach to binding C++ classes to JS...
************************************************************************/
#include <v8/juice/static_assert.h>
#include <v8/juice/forwarding.h>
#include <v8/juice/TypeList.h>
#include <v8/juice/JSClassCreator.h>

#include <sstream>
#include <stdexcept>
#include <vector>
#include <set>

#ifndef DBGSTREAM
#include <iostream> /* only for debuggering */
// only for internal debuggering
#if 0
#  define DBGSTREAM std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#else
#  define DBGSTREAM if(0) std::cerr
#endif
#endif

namespace v8 {
namespace juice {

/**
   The cw namespace houses a policy-based class binding mechanism. The
   base interface is the cw::ClassWrap class, which works by doling
   out most work to various classes. Template specializations of the
   proxies take care of the class-specific parts of the binding
   process.


   The policy interfaces, and their purposes are:

   - Factory: creating and destroying T objects.
   
   - Extract<T>: extracts native data from JS objects and converts the
   v8-bound (void*) to (T*).

   - ToNative<T>: a back-end for convert::JSToNative<T> specialization.
   Most of the work is done by Extract, actually, and this policy
   has become a tad bit superfluous.

   - ToJS<T>: converts (T*) to JS objects. This operation is not possible
   for the generic case, but certain policy sets provide the infrastructure
   needed to support this operation.

   - ClassName<T>: defines the JS name of T.

   - InternalFields<T>: defines how many internal fields are allocated for
   each native, and the index at which the (T*-as-void*) is stored in the
   internal field list.

   - AllCtorWithoutNew<T>: specifies whether JS-side invocations of "T()"
   will work without the "new" operator.

   
   
*/
namespace cw {
    namespace convert = v8::juice::convert;
#if !defined(DOXYGEN)
    namespace Detail
    {
        template <typename T1,typename T2>
        struct IsSameType
        {
            static const bool Value = false;
        };
        template <typename T1>
        struct IsSameType<T1,T1>
        {
            static const bool Value = true;
        };
        template <typename T1,typename T2>
        struct HasParent
        {
            static const bool Value = !IsSameType<T1,T2>::Value;
        };
    }
#endif // DOXYGEN
    
    /**
       Base class for static ClassWrap options.
     */
    template <typename ValT, ValT Val>
    struct Opt_ConstVal
    {
        typedef ValT Type;
        //static Type const Value = Val; // giving me an undefined ref error?
        static Type const Value;
    };
    template <typename ValT, ValT Val>
    const ValT Opt_ConstVal<ValT,Val>::Value = Val;

    /**
       Base class for static integer ClassWrap options.
    */
    template <int Val>
    struct Opt_Int : Opt_ConstVal<int,Val>
    {};

    /**
       Base class for static boolean ClassWrap options.
    */
    template <bool Val>
    struct Opt_Bool : Opt_ConstVal<bool,Val>
    {};
    
    
    /**
       EXPERIMENTAL/INCOMPLETE!
       
       A base implementation for Inheritance policy
       specializations, which may subclass this type, passing some
       base type of T as the ParentType_ parameter. This adds ClassWrap
       inheritance information, which may someday be used to help support
       cross-JS/Native inheritance features.
    */
    template <typename T,typename ParentType_ = T>
    struct Inheritance_Base
    {
        //! Not required to be defined by specializations.
        typedef convert::TypeInfo<T> TypeInfo;
        //! Not required to be defined by specializations.
        typedef convert::TypeInfo<ParentType_> ParentTypeInfo;
        //! Required to be defined by specializations.
        typedef typename TypeInfo::Type Type;
        //! Required to be defined by specializations.
        typedef typename ParentTypeInfo::Type ParentType;
        //! Required to be defined by specializations.
        static const bool HasParent = Detail::HasParent<Type,ParentType>::Value;
    private:
    protected:
        /**
           Tries to statically assert that (T*) can be implicitly
           converted to (ParentType*) (which implies that T and
           ParentType are the same class or T subclasses ParentType).
        */
        Inheritance_Base()
        {
            const typename ParentTypeInfo::NativeHandle * P = 0;
            const typename TypeInfo::NativeHandle * X = 0;
            /**
               If a compiler error led you here, it means that T is
               neither ParentType nor derived from ParentType.
            */
            P = /* See the comments above!!! */ X;
        }
    };

    //! Experimental/incomplete.
    template <typename T>
    struct Inheritance : Inheritance_Base<T,T>
    {};
    
    
    /**
       A ClassWrap policy class for defining a class name to the JS
       counterpart of T.
    */
    template <typename T>
    struct ClassName
    {
        /**
           Must return a valid, unqualified JS class name string. e.g.
           "MyClass" is legal but neither null nor "my.Class" are.

           The default implementation is useless, and will result in
           a compile-time error if static assertions are enabled.
         */
        static char const * Value()
        {
            JUICE_STATIC_ASSERT(false,
                                ClassName_MustBeSpecialized);
            return 0;
        }
    };
    /** Specialization equivalent to ClassName<T>. */
    template <typename T>
    struct ClassName<T*> : ClassName<T> {};
    /** Specialization equivalent to ClassName<T>. */
    template <typename T>
    struct ClassName<T &> : ClassName<T> {};
    /** Specialization equivalent to ClassName<T>. */
    template <typename T>
    struct ClassName<T const &> : ClassName<T> {};
    /** Specialization equivalent to ClassName<T>. */
    template <typename T>
    struct ClassName<T const *> : ClassName<T> {};

    /**
       Convenience base type for InternalFields
       implementations.

       See the member documentation for the meaning of
       HowMany and Index.
    */
    template <typename T,int HowMany = 1, int Index = 0>
    struct InternalFields_Base
    {
        /**
           Total number of internal fields assigned to JS-side T
           objects.
        */
        static const int Count = HowMany;

        /**
           The internal field index at which ClassWrap policies should
           expect the native object to be found in any given JS object.
           It must be 0 or greater, and must be less than Value.
        */
        static const int NativeIndex = Index;
    };

    /**
       The ClassWrap policy which sets the number of internal fields
       reserved for JS objects and the internal field index at which
       the native object is stored. The Count value must be
       greater than 0 and greater than the NativeIndex member.

       ACHTUNG SUBCLASSERS:

       When using a heirarchy of native types, more than one of which
       is bound using ClassWrap, conversions from subtype to base type
       will fail unless all use the same internal field placement.

       If a given parent type uses a custom InternalFields
       specialization then to ensure that subclasses always have the
       same placement, they "should" define their own policy like
       this:

       @code
       template <>
       struct InternalFields< SubType >
           : InternalFields< ParentType >
          {};
       @endcode

       That prohibits special internal field handling in the subtypes,
       but experience hasn't shown that subclasses need their own
       internal fields. Normaly a single internal field is all we need
       when binding native data. And when i say "normally", i mean
       "almost always." i haven't yet seen a use case which would benefit
       from more, though i can conceive of a couple.

       This attribute is partially a side-effect of the library internally
       using the field count as a santiy check before trying to extract
       data from internal fields.
    */
    template <typename T>
    struct InternalFields : InternalFields_Base<T,1,0>
    {
    };

    /**
       A policy class which can be specialized to enable or disable
       certain internal debuggering features/messages of ClassWrap.

       Intended mainly for testing some error handling cases
       in ClassWrap.

       Conventional meanings of the Value member:

       0 == no debuggering output

       1 == serious problems.

       2 == potentially interesting warnings.

       3 == trivial information/noise
    */
    template <typename T>
    struct DebugLevel : Opt_Int<2>
    {
    };
    
    namespace Detail
    {
        /**
           Performs a compile-time assertion for the parameters of the
           given type, which must conform to the
           InternalFields interface.
        */
        template <typename InternalFields>
        void assert_internal_fields()
        {
            typedef InternalFields IFT;
            JUICE_STATIC_ASSERT((IFT::Count>0),
                                InternalFields_Value_MayNotBeNegative);
            JUICE_STATIC_ASSERT((IFT::NativeIndex>=0),
                                InternalFields_NativeIndex_MayNotBeNegative);
            JUICE_STATIC_ASSERT((IFT::Count>IFT::NativeIndex),
                                InternalFields_Value_IsTooSmallForNativeIndex);
        }
    }
    
    /**
       A ClassWrap policy/options class responsible specifying whether
       or not a ClassWrap-bound class should allow "Foo()" and "new
       Foo()" to behave the same or not. If the Value member is false
       (the default) then "Foo()" is not allowed to behave as a
       constructor call (it will generate an error), otherwise it will
       be treated exactly as if "new Foo()" had been called.
    */
    template <typename T>
    struct AllowCtorWithoutNew : Opt_Bool<false>
    {};


    /**
       The ClassWrap Policy class responsible for instantiating and
       destroying convert::TypeInfo<T>::NativeHandle objects.

       The default implementation will not compile if static
       assertions are enabled - it must be specialized (or subclass
       from a concrete specialization) to be useful. If static
       assertions are disabled it will compile but will do nothing
       useful.
    */
    template <typename T>
    struct Factory
    {
        /**
           Specifies the templatized type.
        */
        typedef typename convert::TypeInfo<T>::Type Type;
        /**
           Specifies the "native handle" typed used for
           passing around native objects.
        */
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
	/**
	   This will be called in response to calling
	   "new WrappedType(...)" in JS code. It should:

	   - Create a new native object.

	   - If successful, return that object.

	   - On error, return 0 and optionally populate the (ostream &)
	   argument with an informative error message (e.g. "requires
	   arguments (String,Integer)").

	   If the client is using any "supplemental" garbage
	   collection (e.g. the v8::juice::cleanup API) or class
	   binding mechanism, then they should register the object in
	   this function and deregister it in Destruct().
	*/
	static NativeHandle Instantiate( Arguments const &  /*argv*/,
                                         std::ostream & exceptionText )
	{
            JUICE_STATIC_ASSERT(false,Factory_T_MustBeSpecialized);
	    exceptionText << "Factory<"
                          << ClassName<T>::Value()
                          << ">::Instantiate() not implemented!";
	    return NativeHandle(0);
	}
	/**
	   Must "destroy" the given object, though the exact meaning
	   of "destroy", and mechanism of destruction, is
	   type-specific.

	   Most implementations must simply call "delete", which
	   is fine for many types, but opaque types and types
	   allocated via something other than 'new' will need a
	   different implementation. A destructor functor for shared,
	   static, or stack-allocated objects should simply do nothing
	   (or maybe clear the object to some empty/default state).

	   If the client is using any "supplemental" garbage
	   collection (e.g. the v8::juice::cleanup API) or class
	   binding mechanism then they should deregister the object in
	   this function or in their WeakWrap<T>::Unwrap()
	   specialization.

           Normally the jself argument, which refers to the JS-side representation
           of this native (and which still contains it interally)
           can be ignored by specializations. However, if you don't wish
           to simply ignore it...
           
           When this function is called, if jself.IsEmpty() then there
           is not yet an associated JS object. This is normally the
           result of an error which happens in Instantiate() after the
           native has been constructed but before it is bound to JS,
           and the native needs to be cleaned up in that case.
           Specializations should clean up the native without regard for jself
           in that case.

           If !jself.IsEmpty() then the client may (if needed by T's internal
           policies) clean up the contents of the object's internal fields.
           HOWEVER, be aware that the jself object might not be the real
           object which contains the nself pointer (and is not the same
           object in the face of inheritance). The FindHolder() function
           can be used to get access to the actual JS object which is holding
           the nobj pointer.The framework internally sets the framework-specified
           internal field of jself to v8::Null() after Destruct() returns, so there
           is no need to do so in specializations.
	*/
	static void Destruct( v8::Handle<v8::Object> jself, NativeHandle nself )
	{
            JUICE_STATIC_ASSERT(false,Factory_T_MustBeSpecialized);
	}

        /**
           Should be the approximate amount of native memory allocated
           to each bound object. The purpose of this is to allow
           ClassWrap to tell v8 about the memory cost (a metric it
           theoretically uses in figuring out when to garbage
           collect). It need not be a definitive value, and sizeof(T)
           is a suitable value for most cases. It is legal to be 0, in
           which case no memory adjustment is made.

           Note that it is a const, and not a function, because the
           sizes _must_ be the same at construction and destruction or
           we risk corrupting the memory size state.

           When the ClassWrap API constructs/destructs objects, it
           adjusts v8's memory usage metrics up or down by this
           amount.
        */
        static const size_t AllocatedMemoryCost = 0;
    };

    /**
       A concrete Factory policy implementation which
       uses new/delete to create/destroy objects, but requires
       a default constructor.
    */
    template <typename T>
    struct Factory_NewDelete
    {
        /** Required by Factory interface. */
        typedef typename convert::TypeInfo<T>::Type Type;
        /** Required by Factory interface. */
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        /**
           Returns (new Type).
        */
	static NativeHandle Instantiate( Arguments const &  /*ignored*/,
                                         std::ostream & exceptionText )
	{
            return new Type;
        }
        /**
           Calls (delete obj).
        */
	static void Destruct( v8::Handle<v8::Object> /*ignored*/, NativeHandle obj )
	{
            delete obj;
        }
        /** Required by Factory interface. */
        static const size_t AllocatedMemoryCost = sizeof(Type);
    };

    
    /**
       A ClassWrap policy option class used by certain JS-to-Native
       conversions to determine whether they should search the
       prototype object chain for the native object if it is not found
       in the current JS object. Such a lookup is required for finding
       the native if a JS class inherits the bound class, otherwise
       they are not generally needed.

       Note: in any case, cross-JS/Native inheritance has subtle
       gotchas and problems. Extra C++-side infrastructure (in the
       related ClassWrap policies) can get around some of these problems,
       but cross-space inheritance is not likely to work 100% intuively
       script-side.
    */
    template <typename T>
    struct ToNative_SearchPrototypesForNative : Opt_Bool<true>
    {};

 
    /**
       An Extract policy base class for "unwrapping" JS
       object handles, extracting their native bound data.

       This implementation should be suitable as a base class for
       most, if not all, cases.

       The Extract interface is responsible for:

       - Extracting (void*) handles from JS object.

       - Converting (void*) to native handles.

       But this base only implements the first part, leaving the
       second part to concrete subclasses.
    */
    template <typename T>
    struct Extract_Base
    {
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        /**
           Required part of the Extract interface.
           
           Looks for a JS value stored in the N'th internal field of
           the given object (where N ==
           InternalFields<T>::NativeIndex).

           If it finds one, it the value is extracted to get its
           native (void *). If one is found it is returned.

           Ownership of the returned object is not modified by this
           call.

           If searchPrototypes is true and any of the following apply:

           * (jo->InternalFieldCount() != InternalFields<T>::Value)

           * The field count matches, but no native is found at that index

           Then this function is called recursively on
           jo->GetPrototype(). This feature is necessary if JS-side
           classes must inherit the bound class, as without it they
           cannot find their native members. But it also doesn't work
           intuitively in conjunction with certain types of inherited
           bound functions.

           Maintenance reminder: searchPrototypes has no default
           because there is philosophically no good one. This routine
           is useful in some (limited) contexts where we explicitly do
           not want to search through prototypes, so it was decided
           not to make that a policy value.
        */
        static void * ExtractVoid( v8::Handle<v8::Object> const & jo,
                                   bool searchPrototypes )
        {
            if( jo.IsEmpty() ) return 0;
            typedef InternalFields<T> IFT;
            { static bool inited = (Detail::assert_internal_fields<IFT>(),true); (void)inited;}
            void * ext = 0;
            if( jo->InternalFieldCount() == IFT::Count )
            // ^^^^ TODO: consider using >= instead of ==, so subclasses can use larger lists.
            {
                ext = jo->GetPointerFromInternalField( IFT::NativeIndex );
            }
            if( searchPrototypes && !ext )
            {
                //DBGSTREAM << "Searching in prototype chain for "<<ClassName<T>::Value()<<"...\n";
                v8::Local<v8::Value> proto = jo->GetPrototype();
//                 if( !proto.IsEmpty() && proto->IsObject() )
//                 {
//                     return ExtractVoid( v8::Local<v8::Object>( v8::Object::Cast( *proto ), true );
//                 }
                while( !proto.IsEmpty() && proto->IsObject() )
                {
                    v8::Local<v8::Object> lo( v8::Object::Cast( *proto ) );
                    ext = ExtractVoid( lo, true );
                    if( ! ext ) proto = lo->GetPrototype();
                    else break;
                }
            }
            return ext;
        }

    };

    /**
       A concrete Extract implementation which uses static_cast() to
       convert between (void*) and (T*).  It takes a certain, but not
       infallible, deal of care in ensuring that the (void*) is
       actually a native object of the proper type.
    */
    template <typename T>
    struct Extract_StaticCast : Extract_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;

        /**
           Required part of the Extract
           interface. Implementations must, if possible, return a
           NativeHandle equivalent for x. If it is not possible, they
           must return 0.

           This implementation returns static_cast<NativeHandle>(x).

           Specializations are free to use the (void*) as a lookup key
           to find, in a type-safe manner, an associated native.
        */
        static NativeHandle VoidToNative( void * x )
        {
            return x ? static_cast<NativeHandle>( x ) : 0;
        }
    };

    /**
       The ClassWrap policy responsible for "unwrapping" JS object
       handles, extracting their native bound data.

       The default implementation should be suitable for most cases.

       Reminder: The Extract policy acts as the basis of ToNative.
    */
    template <typename T>
    struct Extract : Extract_StaticCast<T>
    {};

    /**
       Don't use this from client code until this note goes away.

       Utility class for use by ClassWrap policies which need
       to support inheritance of one bound class from another.
       
       This approach has some limitations, and is not _quite_ what i
       want. Subject to change.
    */
    template <typename T>
    class NativeInheritance
    {
    public:
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        /**
           A function which can (somehow) determine if x is really
           a subclass instance of T. In the generic case this cannot
           be safely determined, but certain policy implementations
           store enough type information to allow this to work.
           (Actually... we could use dynamic_cast() for the generic
           case... coudln't we?)

           On success (the function is a subclass) then it should
           return a pointer to that derived object. On error (no
           match) then 0 should be returned. These functions should
           not throw.
        */
        typedef NativeHandle (*CheckIsSubclass)( void * x );
    private:
        typedef std::set<CheckIsSubclass> SubToBaseList;
        static SubToBaseList & list()
        {
            static SubToBaseList bob;
            return bob;
        }
        /** Implements CheckIsSubclass() for SubT. */
        template <typename SubT>
        static NativeHandle VoidToNative_Sub( void * x )
        {
            typedef Extract<SubT> XT;
            return XT::VoidToNative( x );
        }
    public:
        /**
           Registers a function which is presumed to be able to tell
           if a (void *) is actually an instance of a subclass of T.
        */
        template <typename SubT>
        static void RegisterSubclass( CheckIsSubclass pf )
        {
#if 0
            DBGSTREAM << "Registering "<<ClassName<SubT>::Value()<<" as "
                 << "native subclasss of "<<ClassName<T>::Value()<<'\n';
#endif
            typedef typename convert::TypeInfo<SubT>::NativeHandle STH;
            const STH y = 0;
            NativeHandle x;
            x = y;
            /** ^^^ if your compiler led you here then SubT does not derive from T! */
            list().insert( pf );
        }
        /**
           Registers a default class check function which simply calls
           Extract<SubT>::VoidToNative(). This is NOT
           safe unless that function is explicitly implemented to
           handle (void*)-to-SubT-instance mapping, or can otherwise
           do something other than static_cast().
        */
        template <typename SubT>
        static void RegisterSubclass()
        {
            RegisterSubclass<SubT>( VoidToNative_Sub<SubT> );
        }

        /**
           For each registered CheckIsSubclass routine, ext is passed
           to it.  The return value is that of the last check
           performed, or 0 if no match is found.
        */
        static NativeHandle CheckForSubclass( void * const ext )
        {
#if 0
            DBGSTREAM << "Doing native subtype lookup for Base Type "
                 << ClassName<T>::Value() << '\n';
#endif
            typename SubToBaseList::const_iterator it = list().begin();
            typename SubToBaseList::const_iterator et = list().end();
            NativeHandle x = 0;
            for( ; !x && (et != it); ++it )
            {
                x = (*it)( ext );
            }
            return x;
        }

        /**
           Implements a JS-to-Native conversion, and can be used as
           a basis for ToNative::Value() implementations.

           Uses Extract<T>::ExtractVoid() to extract an object from
           h. If none is found, 0 is returned. If one is found
           Extract<T>::VoidToNative() is used to convert it to a
           NativeHandle. If that routine returns 0 then
           CheckForSubclasses() is called to see if the fetched
           (void*) happens to be an object from a registered
           subclass. On success, a new NativeHandle (or a subclass of
           it) is returned, else 0 is returned.
        */
        static NativeHandle ToNativeOrSubclass( v8::Handle<v8::Object> const & h )
        {
            typedef Extract<T> XT;
            const bool searchProto =
                ToNative_SearchPrototypesForNative<T>::Value;
            void * ext = XT::ExtractVoid( h, searchProto );
            if( ! ext ) return 0;
            NativeHandle x = XT::VoidToNative( ext );
            return x
                ? x
                : CheckForSubclass( ext );
        }
    };
   
    /**
       A base class for ToNative implementations. The template
       argument T is the native type being bound.
       
       ToNative_SearchPrototypesForNative<T>::Value
       internally is used as the second parameter to
       ExtractPolicy::ExtractVoid().
    */
    template <typename T>
    struct ToNative_Base
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        typedef Extract<T> ExtractPolicy;
        /**
           Uses Extract<T>::ExtractVoid(jo) to extract a
           native pointer. If it finds one, it returns
           VoidToNative(ptr), else it returns 0.

           Ownership of the returned object is not modified by this
           call.

           The second argument passed to ExtractPolicy::ExtractVoid()
           is ToNative_SearchPrototypesForNative<T>::Value.
        */
        static NativeHandle Value( v8::Handle<v8::Object> const jo )
        {
            void * ext = ExtractPolicy::ExtractVoid( jo,
                                                     ToNative_SearchPrototypesForNative<T>::Value
                                                     );
            return ext
                ? ExtractPolicy::VoidToNative( ext )
                : 0;
            /** Reminder to self:

            If one bound type inherits another...
            
            Policy sets which do "type safe binding" (e.g. JuiceBind
            and TwoWay) will, without specific infrastructure to
            support it, return 0 from VoidToNative(). The problem is
            that they look for the exact type only, and must be made
            specifically aware of subtypes.

            For the generic VoidToNative() impl ((static_cast<>()),
            inheritance in this way "just happens to work", but that
            is just a happy accident.
            */
        }
    };
    

    /**
       A concrete ToNative policy class which uses
       NativeInheritance<T>::ToNativeOrSubclass() to
       try to convert JS objects to natives.
     */
    template <typename T>
    struct ToNative_WithNativeSubclassCheck
    {
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        /**
           Returns NativeInheritance<T>::ToNativeOrSubclass(jo).
        */
        static NativeHandle Value( v8::Handle<v8::Object> const jo )
        {
            return NativeInheritance<T>::ToNativeOrSubclass( jo );
        }
    };

    
    /**
       The ClassWrap policy type responsible for converting
       v8 Value handles to convert::TypeInfo<T>::NativeHandle objects.

       This class can (and should) be used to implement a
       specialization of convert::JSToNative<T>.

       The default implementation is designed to work with the other
       default ClassWrap policies, and may need to be specialized if
       any the Extract<T> policy is specialized.
    */
    template <typename T>
    struct ToNative :
        //ToNative_StaticCast<T>
        //ToNative_WithNativeSubclassCheck<T>
        ToNative_Base<T>
    {};

  
    /**
       The ClassWrap policy type responsible for converting
       convert::TypeInfo<T>::NativeHandle to v8::Objects. The default
       instantiation will cause a compile-time error, as Native-to-JS
       is not possible in the generic case (it requires an extra level
       of binding info, which can be provided via custom ClassWrap
       policy specializations).
    */
    template <typename T>
    struct ToJS
    {
    public:
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        /**
           Converts the given handle to a JS object. If it cannot it
           should return an empty handle. It may throw a JS exception
           if a failed conversion is deemed to be a serious error, but
           this is not generally recommended.
           
           TODO: determine whether throwing a JS exception from here is
           really all that reasonable.

           The default implementation causes a compile-time assertion
           (if they are enabled) or returns an empty handle (if
           compile-time assertions are disabled).
        */
        static v8::Handle<v8::Object> Value( const NativeHandle )
        {
            JUICE_STATIC_ASSERT(false,T_ToJS_CannotWorkForTheGeneralCase);
            return v8::Handle<v8::Object>();
        }
    };

    /**
       The ClassWrap policy class responsible for doing optional
       class-specific binding-related work as part of the JS/Native
       object construction process.

       The default specialization does nothing (which is okay for the
       general case) but defines the interface which specializations
       must implement.
    */
    template <typename T>
    struct WeakWrap
    {
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        /**
           This operation is called one time from ClassWrap for each
           new object, directly after the native has been connected to
           a Persistent handle.
   
           Note that the ClassWrap code which calls this has already
           taken care of connecting nativeSelf to jsSelf. Client
           specializations of this policy may opt to add their own
           binding mechanisms, e.g. to allow CastToJS<T>() to work.

           Clients should do any bindings-related cleanup in
           Factory::Destruct() or Unwrap(), as appropriate for their
           case.

           Ownership of the objects is unchanged by calling this.

           On error, this function may throw a native exception. If
           that happens, ClassWrap will call
           Factory<T>::Destruct(nativeSelf) to clean up, and will then
           propagate the exception.
        */
        static void Wrap( v8::Persistent<v8::Object> const & jsSelf, NativeHandle nativeSelf )
        {
            return;
        }

        /**
           This is called from the ClassWrap-generated destructor,
           just before the native destructor is called.
        
           Specializations may use this to clean up data stored in
           other internal fields of the object (_not_ the one used to
           hold the native itself - that is removed by the
           framework). Optionally, such cleanup may be done in the
           corresponding Factory::Destruct() routine, and must be done
           there if the dtor will need access to such data.

           Note that when this is called, jsSelf and nativeSelf are
           about to be destroyed, so do not do anything crazy with the
           contents of jsSelf and DO NOT destroy nativeSelf.

           Ownership of the objects is unchanged by calling this.
        */
        static void Unwrap( v8::Handle<v8::Object> const & jsSelf, NativeHandle nativeSelf )
        {
            return;
        }
    };

    /**
       A utility function primarily intended to support various
       ClassWrap policy implementations.

       This function tries to extract a native from jo using
       Extract<T>.  If a native is found, and
       Extract<T>::VoidToNative() says that it is the same as nh, then
       jo is returned. If none is found, jo's prototype object is
       searched, recursively, until either nh is found in the
       prototype chain or the end of the chain is reached. If a match
       is found, the object in which the data were found is returned.

       If nh is found nowhere in the chain, an empty handle is returned.

       Note that because the function signature uses a typename, the T
       template parameter may not be omitted from calls to this
       function.
       
       Required ClassWrap policies:

       - Extract<T>
    */
    template <typename T>
    v8::Handle<v8::Object> FindHolder( v8::Handle<v8::Object> jo,
                                       typename convert::TypeInfo<T>::NativeHandle nh )
    {
        if( jo.IsEmpty() || ! jo->IsObject() ) return v8::Handle<v8::Object>();
        typedef convert::TypeInfo<T> TI;
        typedef Extract<T> XT;
        typedef typename TI::NativeHandle NH;
        // FIXME: refactor this to use iteration instead of recursion.
        void * ext = XT::ExtractVoid( jo, false );
        if( ! ext )
        {
            v8::Local<v8::Value> proto = jo->GetPrototype();
            if( !proto.IsEmpty() && proto->IsObject() )
            {
                return FindHolder<T>( v8::Local<v8::Object>( v8::Object::Cast( *proto ) ), nh );
            }
            return v8::Handle<v8::Object>();
        }
        if( ext == nh ) return jo; // shortcut
        NH xnh = XT::VoidToNative( ext );
        if( xnh != nh )
        { // Bound native, but the wrong one. Keep looking...
            v8::Local<v8::Value> proto = jo->GetPrototype();
            if( !proto.IsEmpty() && proto->IsObject() )
            {
                return FindHolder<T>( v8::Local<v8::Object>( v8::Object::Cast( *proto ) ), nh );
            }
            return v8::Handle<v8::Object>();
        }
        else
        {
            return jo;
        }
    }
    
    /**
       A policy-based native-to-JS class binder, such that T
       object can be accessed via JS. This class is only
       a very thin wrapper around:

       - JSClassCreator (its base class)
       - Various policy classes.


       This class handles the more mundane details of creating a new
       JS class, and this provides the weak pointer binding for
       wrapped classes. The T-specific policy classes define how
       certain aspects of the binding are handled, e.g. how to convert
       a JS object handle back into a T object.

       The policies required by this type are defined as typedefs in
       this class, and it is up to the client to ensure that all
       policy specializations (if needed) are in place. Most policies
       have reasonable defaults, but some do not (most notably
       ClassName and ToJS).


       MISFEATURES AND SIGNIFICANT CAVEATS:

       Cross-JS/Native inheritance introduces several problems, some
       of them subtle, some of them not. Some of them can be solved
       via specific policy sets. The notable problems one might
       encounter, for which there are workarounds:

       - When inheriting a bound class from JS space, be sure that the
       ToNative_SearchPrototypesForNative<T>::Value is specialized to
       hold a true value, to ensure that lookups for the native object
       can work when accessing bound members via a JS-side derived
       class.

       - When inheriting one bound class from another, be sure to call
       ClassWrap<T>::InheritNative<ParentType>() when wrapping the
       second class. For this to work, to ToNative<T> policy should be
       a subclass of ToNative_WithNativeSubclassCheck<T> (or something
       behaviourly equivalent).
    */
    template <typename T>
    class ClassWrap : public JSClassCreator
    {
    public:
        /**
           Basic type info.
        */
        typedef convert::TypeInfo<T> TypeInfo;
        /**
           The real native wrapped type. In some weird cases is may
           differ from T!
         */
        typedef typename TypeInfo::Type Type;

        /**
           A native object handle, typically (T*) but _theoretically_
           could be a pointer-like wrapper like a smart pointer (but
           that's untested).
        */
        typedef typename TypeInfo::NativeHandle NativeHandle;

        /**
           The JS-side class name.
        */
        typedef v8::juice::cw::ClassName<T> ClassName;

        /**
           The native ctor/dtor routines which are called from
           JS.
        */
        typedef v8::juice::cw::Factory<T> Factory;

//         /**
//            The Native-to-JS cast operation. Not possible for the
//            generic case. We do not typedef it here so we do not end up
//            instantiating it, because there is no default
//            specialization and this operation is not needed by this
//            class.
//         */
        //typedef ToJS<T> CastToJS;

        /**
           The JS-to-Native cast operation.
           See ClassWrap-CastOps.h for an easy way to generate
           this for a given type.
        */
        typedef v8::juice::cw::ToNative<T> ToNative;
        
        /**
           This operation is called one time after a native has been
           connected to a Persistent handle. Client specializations of
           this policy may perform their own binding mechanisms,
           e.g. to allow Native-to-JS conversions to work.
        */
        typedef v8::juice::cw::WeakWrap<T> WeakWrap;

        /**
           Information about the "internal fields" (which holds native
           data inside the JS object representation). The fields are:

           - Value = the number of internal fields.

           - NativeIndex = the index at which the bound native object
           is stored within the list. Must be less than Value.
        */
        typedef v8::juice::cw::InternalFields<T> InternalFields;

        /**
           A boolean option specifying whether the JS code "Foo()"
           should be treated like "new Foo()". If false, the former will cause
           a JS exception.
        */
        typedef v8::juice::cw::AllowCtorWithoutNew<T> AllowCtorWithoutNew;

        /**
           Convenience typedef for accessing a property binder utility
           class.
        */
        typedef ::v8::juice::convert::PropertyBinder<T> PB;
        
    private:
        typedef DebugLevel<T> DBG;
#define DBGOUT(LVL) if( DBG::Value >= LVL ) DBGSTREAM << "ClassWrap<"<<ClassName::Value()<<">::" <<__FUNCTION__<<"() "
        /** Checks a few static assertions. */
        static void check_assertions()
        {
            Detail::assert_internal_fields<InternalFields>();
        }
        /**
           Called by v8 when pv should be destructed. This function
           removes the native handle from the JS object, desposes of
           the persistent handle, and calls Factory::Destruct() to
           destroy the object.
        */
	static void weak_callback(Persistent< Value > pv, void * nobj)
	{
	    DBGOUT(3) << "native @"<<(void const *)nobj<<"\n";
            if( pv.IsEmpty() || ! pv->IsObject() )
            {
                DBGOUT(2) << "WARNING: was passed an empty or non-object handle!\n";
                return;
            }
	    Local<Object> jobj( Object::Cast(*pv) );
            NativeHandle nh = ToNative::Value( jobj );
            if( nh != nobj )
            {
                if( ! nh )
                {
                    /**
                       Blithely assume that the native was removed via outside measures, e.g.
                       a call to a member Close() method.

                       When we trigger this function via
                       DestroyObject() (or similar), i'm finding that
                       v8 later calls this function again (at the
                       proper cleanup time), but the native has been
                       unbound and triggers this condition.

                       [Later on...]

                       i believe the above-mentioned dual calls
                       condition has been fixed, but need to test it
                       more before removing this if() block.
                    */
                    DBGOUT(0) << "ACHTUNG: ClassWrap<"<<ClassName::Value()<<">::weak_callback(): "
                              << "Possibly called twice? "
                              << "From JS=@"<<(void const *)nobj
                              << ", Converted to Native=@"<<(void const *)nh
                              << '\n'
                        ;
                    pv.Dispose();
                    pv.Clear();
                    return;
                }
                DBGOUT(1) << "SERIOUS INTERNAL ERROR:\n"
                          << "ClassWrap<"<<ClassName::Value()<<">::weak_callback() was passed "
                          << "two different values for the native object:\n"
                          << "From JS=@"<<(void const *)nobj
                          << ", Converted to Native=@"<<(void const *)nh
                          << "\nSKIPPING DESTRUCTION! NOT DOING ANYTHING!! LEAKING MEMORY!!!\n"
                    ;
                return;
            }
            WeakWrap::Unwrap( jobj, nh );
            /**
               Reminder: the FindHolder() bits are here to
               assist when the bound native exists somewhere in the
               prototype chain other than jobj itself. In that case,
               jobj is valid but we cannot clear out the native handle
               internal field on it because it has no internal fields
               (or none that belong to us).

               To fix this properly we have to be able to know
               _exactly_ which JS object in the prototype chain nh is
               bound to.
            */
            v8::Handle<v8::Object> nholder = FindHolder<Type>( jobj, nh );
            v8::V8::AdjustAmountOfExternalAllocatedMemory( -static_cast<int>( Factory::AllocatedMemoryCost ) );
            if( nholder.IsEmpty() || (nholder->InternalFieldCount() != InternalFields::Count) )
            {
                DBGOUT(1) << "SERIOUS INTERNAL ERROR:\n"
                          << "ClassWrap<"<<ClassName::Value()<<">::weak_callback() "
                          << "validated that the JS/Native belong together, but "
                          << "FindHolder() returned an "
                          << (nholder.IsEmpty() ? "empty" : "invalid")
                          << "handle!\n"
                          << "From JS=@"<<(void const *)nobj
                          << ", Converted to Native=@"<<(void const *)nh
                          << "\nTHIS MAY LEAD TO A CRASH IF THIS JS HANDLE IS USED AGAIN!!!\n"
                    ;
                Factory::Destruct( jobj, nh );
                return;
            }
            else
            {
                /**
                   Reminder: we call Destruct() before cleaning up the
                   JS-side fields for the case that the bound class actually
                   does tinker with the JS space directly.
                */
                Factory::Destruct( jobj, nh );
                /**
                   We have to ensure that we have no dangling External
                   in JS space. This is so that member functions
                   called via the JS handle after the native is gone
                   do not get a dangling pointer. Without this, such
                   uses will cause a crash (or a mis-direction to
                   another object allocated at the same address).
                */
                nholder->SetInternalField(InternalFields::NativeIndex,Null());
            }
	}

        /**
           Makes a weak pointer from _self and sets obj as the N's internal field
           of _self, where N is InternalFields::NativeIndex. Returns the new
           weak pointer handle.

           On error, this function may propagate a native
           exception. If that happens, we will call
           Factory::Destruct(nativeSelf) to clean up before
           propagating the exception. This behaviour is a documented
           part of the WeakWrap policy, so don't go changing it.
        */
	static Persistent<Object> wrap_native( Handle<Object> _self, NativeHandle obj )
	{
            //DBGSTREAM << ClassName::Value() <<"::wrap_native(@"<<(void const *)obj<<") Binding to internal field #"<<InternalFields::NativeIndex<<"\n";
            v8::V8::AdjustAmountOfExternalAllocatedMemory( static_cast<int>( Factory::AllocatedMemoryCost ) );
	    Persistent<Object> self( Persistent<Object>::New(_self) );
	    self.MakeWeak( obj, weak_callback );
	    self->SetPointerInInternalField( InternalFields::NativeIndex, obj );
            try
            {
                WeakWrap::Wrap( self, obj );
            }
            catch(...)
            {
                self.ClearWeak();
                self->SetInternalField( InternalFields::NativeIndex, v8::Null() );
                Factory::Destruct( _self, obj );
                throw;
            }
	    return self;
	}

        /**
           Tries to instantiate a new NativeHandle object by calling
           Factory::Instantiate(). On success, the returned handle
           points to a weak-pointer handle to that object. On error
           a JS exception is triggered and the return value is
           theoretically empty.
        */
	static Handle<Value> ctor_proxy( const Arguments & argv )
	{
            if( AllowCtorWithoutNew::Value )
            {
                /**
                   Allow construction without 'new' by forcing this
                   function to be called in a ctor context...
                */
                if (!argv.IsConstructCall()) 
                {
                    const int argc = argv.Length();
                    Handle<Function> ctor( Function::Cast(*argv.Callee()));
                    std::vector< v8::Handle<v8::Value> > av(static_cast<size_t>(argc),Undefined());
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
                    convert::StringBuffer msg;
                    msg << "The "<< ClassName::Value()
                        << " constructor cannot be called as function. "
                        << "It requires the 'new' operator!";
                    //return ThrowException(String::New(os.str().c_str()));
                    return v8::ThrowException(msg);
                }
            }
	    DBGOUT(3) << "\n";
	    NativeHandle obj = NativeHandle(0);
            std::string err;
            {
                std::ostringstream errstr;
                try
                {
                    obj = Factory::Instantiate( argv, errstr );
                }
                catch(std::exception const & ex)
                {
                    return v8::ThrowException(v8::String::New(ex.what()));
                }
                catch(...)
                {
                    return v8::ThrowException(v8::String::New("Native constructor threw an unknown native exception type!"));
                }
                err = errstr.str();
            }
	    if( ! err.empty() )
	    {
		if( obj )
		{
		    Factory::Destruct(v8::Handle<v8::Object>(),obj);
		    obj = NativeHandle(0);
		}
		return v8::ThrowException(v8::String::New(err.c_str(),static_cast<int>(err.size())));
	    }
	    if( ! obj )
	    {
		return v8::ThrowException(v8::String::New("Native constructor failed for an unspecified reason!"));
	    }
	    return wrap_native( argv.This(), obj );
	}
       
        /**
           Inititalizes the binding of T as a JS class which will
           become a member of the given target object.

           @see v8::juice::JSClassCreator::JSClassCreator()
        */
        explicit ClassWrap( Handle<Object> target)
	    : JSClassCreator( ClassName::Value(),
			      target,
			      ctor_proxy,
			      InternalFields::Count )
	{
            check_assertions();
	}
        /**
           Inititalizes the binding of T, but AddClassTo() must be
           used to install the class in a JS object.

           @see v8::juice::JSClassCreator::JSClassCreator()
        */
        ClassWrap()
	    : JSClassCreator( ClassName::Value(),
			      ctor_proxy,
			      InternalFields::Count )
	{
            check_assertions();
	}

    public:

        /**
           See v8::juice::convert::PropertyBinder::BindMemVar().
        */
        template <typename PropertyType, PropertyType Type::*MemVar>
        void BindMemVar( char const * name )
        {
            PB::template BindMemVar<PropertyType,MemVar>( name, this->Prototype() );
            return;
        }

        /**
           See v8::juice::convert::PropertyBinder::BindMemVarRO().
        */
        template <typename PropertyType, PropertyType Type::*MemVar>
        void BindMemVarRO( char const * name )
        {
            PB::template BindMemVarRO<PropertyType,MemVar>( name, this->Prototype() );
            return;
        }

        /**
           See v8::juice::convert::PropertyBinder::BindGetterSetter().
        */
        template <typename RV,
                  RV (Type::*Getter)(),
                  typename SetRV,
                  typename ArgV,
                  SetRV (Type::*Setter)(ArgV)
            >
        void BindGetterSetter( char const * propName )
        {
            PB::template BindGetterSetter<RV,Getter,SetRV,ArgV,Setter>( propName, this->Prototype() );
        }

        /** Overload to support a const Getter. */
        template <typename RV,
                  RV (Type::*Getter)() const,
                  typename SetRV,
                  typename ArgV,
                  SetRV (Type::*Setter)(ArgV)
            >
        void BindGetterSetter( char const * propName )
        {
            PB::template BindGetterSetter<RV,Getter,SetRV,ArgV,Setter>( propName, this->Prototype() );
        }
        
        /**
           See v8::juice::convert::PropertyBinder::BindGetter().
        */
        template <typename RV, RV (Type::*Getter)()>
        void BindGetter( char const * propName )
	{
            PB::template BindGetter<RV,Getter>( propName, this->Prototype() );
        }

        /** Overload to support a free-function Getter. */
        template <typename RV, RV (*Getter)()>
        void BindGetter( char const * propName )
	{
            PB::template BindGetter<RV,Getter>( propName, this->Prototype() );
        }

        /** Overload to support a const Getter. */
        template <typename RV, RV (Type::*Getter)() const>
        void BindGetter( char const * propName )
	{
            PB::template BindGetter<RV,Getter>( propName, this->Prototype() );
        }

        /**
           See v8::juice::convert::PropertyBinder::BindStaticVar().
        */
        template <typename VarType, VarType * SharedVar>
        void BindStaticVar( char const * name )
        {
            PB::template BindStaticVar<VarType,SharedVar>( name, this->Prototype() );
        }

        /**
           See v8::juice::convert::PropertyBinder::BindStaticVarRO().
        */
        template <typename VarType, VarType const * SharedVar>
        void BindStaticVarRO( char const * name )
        {
            PB::template BindStaticVarRO<VarType,SharedVar>( name, this->Prototype() );
        }
        
        
        /**
           Destroys the given object by disconnecting its associated
           native object and calling the native destructor function
           for it.

           If jo cannot be converted to a NativeHandle then false is
           returned. Otherwise the true is returned and the native
           object referenced by jo is no longer valid (it should not
           be used by JS code).

           Native functions bound to that object should take care to
           bail out with an exception once the native pointer is gone,
           as opposed to blindly stepping on its null/dangling pointer
           (which _might_ have been re-allocated to a different
           object, even of a different type, in the mean time).
        */
	static bool DestroyObject( Handle<Object> const & jo )
	{
	    NativeHandle t = ToNative::Value(jo);
            DBGOUT(3) << "Native = @"<<(void const *)t<<'\n';
	    if( ! t ) return false;
	    v8::Persistent<v8::Object> p( v8::Persistent<v8::Object>::New( jo ) );
            p.ClearWeak(); // avoid a second call to weak_callback() via gc!
	    weak_callback( p, t );
	    return true;
	}

        /**
           If jv is empty or !jv->IsObject() then 0 is returned,
           otherwise it returns the result of
           DestroyObject(Handle<Object>).
        */
        static bool DestroyObject( Handle<Value> const & jv )
	{
            return (jv.IsEmpty() || !jv->IsObject())
                ? 0
                : DestroyObject( Handle<Object>( Object::Cast(*jv) ) );
	}

        /**
           An InvocationCallback implementation which calls
           DestroyObject( argv.Holder() ).

           It is intended to be used as a "manual destructor" for
           classes which need it. The canonical examples are
           Stream.close() and Database.close().
        */
	static v8::Handle<v8::Value> DestroyObject( v8::Arguments const & argv )
	{
            return convert::CastToJS( DestroyObject(argv.This()) );
	}

        /**
           Returns a shared instance of this class.

           Important usage notes:

           First, each ClassWrap instance must only be populated
           one time, and Seal() must be called to close the binding
           process.

           Secondly, one must call AddClassTo() to add the generated
           class to a target JS object (typically the global object).

           Once the shared ClassWrap instance has been populated and
           sealed, client code can use Instance().NewInstance() to
           create new JS instances of the bound class.
        */
        static ClassWrap & Instance()
        {
            static ClassWrap bob;
            return bob;
        }

        /**
           Works like the inherited Inherit() function but also
           registers T with NativeInheritance<ParentT>.
        */
        template <typename ParentT>
        ClassWrap & InheritNative( ClassWrap<ParentT> const & p )
        {
            if(1)
            {// static type check
                typedef typename ClassWrap<ParentT>::NativeHandle PH;
                NativeHandle n = 0;
                PH p;
                p = n;
                /** ^^^ If your compiler brought you here, T does not inherit from ParentT. */
            }
            this->JSClassCreator::Inherit( p );
            typedef NativeInheritance<ParentT> CNI;
            CNI::template RegisterSubclass<Type>();
            return *this;
        }
#undef DBGOUT
    };

#if !defined(DOXYGEN)
    namespace Detail
    {
        /**
           A base class for the Factory_CtorForwarder#
           family of classes.
        */
        template <typename T>
        struct Factory_CtorForwarder_Base
        {
            typedef typename convert::TypeInfo<T>::Type Type;
            typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
            static void Destruct( v8::Handle<v8::Object> jself, NativeHandle nself )
            {
                delete nself;
            }
            static const size_t AllocatedMemoryCost = sizeof(Type);
        protected:
            /**
               If argv.Length() >= Arity then this function ignores errmsg and
               returns true, otherwise it writes a descriptive error message
               to errmsg and return false.
            */
            static bool argv_check( v8::Arguments const & argv, int Arity, std::ostream & errmsg )
            {
                if( argv.Length() >= Arity ) return true;
                else
                {
                    errmsg << ClassName<T>::Value() << " constructor requires "
                           << Arity << " arguments!"; 
                    return false;
                }
            }
        };

        /**
           Internal dispatch routine. CTOR _must_ be a convert::CtorForwardN implementation,
           where N is 0..N.
        */
        template <typename T,typename CTOR>
        struct CtorFwdDispatch
        {
            typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
            static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
            {
                if( CTOR::Arity == argv.Length() )
                {
                    return CTOR::Ctor( argv );
                }
                return 0;
            }
        };
        /**
           Internal dispatch end-of-list routine.
        */
        template <typename T>
        struct CtorFwdDispatch<T,v8::juice::tmp::NilType>
        {
            typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
            static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
            {
                return 0;
            }
        };
        /**
           Internal type to dispatch a v8::Arguments list to one of
           several a bound native constructors, depending on on the
           argument count.
        
           List MUST be a tmp::TypeList< ... > containing ONLY
           convert::CtorFowarderXXX implementations, where XXX is an
           integer value.
        */
        template <typename T,typename List>
        struct CtorFwdDispatchList
        {
            typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
            /**
               Tries to dispatch Arguments to one of the constructors
               in the List type, based on the argument count.
             */
            static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
            {
                typedef typename List::Head CTOR;
                typedef typename List::Tail Tail;
                return ( CTOR::Arity == argv.Length() )
                    ?  CtorFwdDispatch< T, CTOR >::Instantiate( argv, errmsg )
                    : CtorFwdDispatchList<T,Tail>::Instantiate(argv,errmsg);
            }
        };
        /**
           End-of-list specialization.
        */
        template <typename T>
        struct CtorFwdDispatchList<T,v8::juice::tmp::NilType>
        {
            typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
            /** Writes an error message to errmsg and returns 0. */
            static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
            {
                errmsg << "No native "<< v8::juice::cw::ClassName<T>::Value()
                       << "() constructor was defined for "<<argv.Length()<<" arguments!\n";
                return 0;
            }
        };
    }
#endif // !DOXYGEN
    
    /**
       A concrete ClassWrap factory implementation which binds one or more
       natve ctors, each requiring a different number of arguments.

       Usage:

       CtorForwarderList _MUST_ be a v8::juice::tmp::TypeList of
       v8::juice::convert::CtorForwardXXX instances, where XXX is a
       number. They must also all take a different number of
       arguments, as we can only differentiate the calls from JS based
       on the argument count and not their types.

       This class is used like so:

       Assume we have the JS-bound class MyClass and that it has 3 constructors:
       MyClass(), MyClass(int), and MyClass(int,double).

       We can set up the ClassWrap factory for those with:
       
       @code
       template <>
        struct Factory<MyClass> :
          Factory_CtorForwarder<MyClass,
                              tmp::TypeList<
                              convert::CtorForwarder0<MyClass>,
                              convert::CtorForwarder2<MyClass,int,double>,
                              convert::CtorForwarder1<MyClass,int>
                              > >
        {};
       @endcode
    */
    template <typename T,typename CtorForwarderList>
    struct Factory_CtorForwarder : Detail::Factory_CtorForwarder_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
	static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
	{
            //typedef typename CtorForwarderList::Head Head;
            return Detail::CtorFwdDispatchList<T,CtorForwarderList>::Instantiate( argv, errmsg );
	}
    };

    /**
       A concrete Factory which creates objects by calling
       the default ctor and destroys them with 'delete'.
    */
    template <typename T>
    struct Factory_CtorForwarder0 : Detail::Factory_CtorForwarder_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
	static NativeHandle Instantiate( Arguments const &  argv,
                                         std::ostream & )
	{
            return convert::CtorForwarder<Type,0>::Ctor(argv);
	}
    };

//! Short-lived internal convenience macro.
#define CtorForwarder_ArgvCheck_Prep(N)    \
    if( ! Detail::Factory_CtorForwarder_Base<T>::argv_check( argv, N, errmsg ) ) return NativeHandle(0); \
        typedef convert::CtorForwarder<Type,N> CF
 
    /**
       A concrete Factory which creates objects by calling
       a 2-argument ctor and destroys them with 'delete'.

       A0 is the first argument type of the ctor.
    */
    template <typename T,typename A0>
    struct Factory_CtorForwarder1 : Detail::Factory_CtorForwarder_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
	static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
	{
            CtorForwarder_ArgvCheck_Prep(1);
            return CF::template Ctor<A0>(argv);
	}
    };

    /**
       A concrete Factory which creates objects by calling
       a 2-argument ctor and destroys them with 'delete'.

       A0 is the first argument type of the ctor. A1 is the second...
    */
    template <typename T,typename A0,typename A1>
    struct Factory_CtorForwarder2 : Detail::Factory_CtorForwarder_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
	static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
	{
            CtorForwarder_ArgvCheck_Prep(2);
            return CF::template Ctor<A0,A1>(argv);
	}
    };

    /**
       A concrete Factory which creates objects by calling
       a 3-argument ctor and destroys them with 'delete'.

       A0 is the first argument type of the ctor. A1 is the second...
    */
    template <typename T, typename A0, typename A1, typename A2 >
    struct Factory_CtorForwarder3 : public Detail::Factory_CtorForwarder_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
        {
            CtorForwarder_ArgvCheck_Prep(3);
            return CF::template Ctor< A0, A1, A2 >(argv);
        }
    };
    /**
       A concrete Factory which creates objects by calling
       a 4-argument ctor and destroys them with 'delete'.

       A0 is the first argument type of the ctor. A1 is the second...
    */
    template <typename T, typename A0, typename A1, typename A2, typename A3 >
    struct Factory_CtorForwarder4 : public Detail::Factory_CtorForwarder_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
        {
            CtorForwarder_ArgvCheck_Prep(4);
            return CF::template Ctor< A0, A1, A2, A3 >(argv);
        }
    };

    /**
       A concrete ClassWrap_Factory which creates objects by calling
       the 5-argument ctor and destroys them with 'delete'.

       A0 is the first argument type of the ctor. A1 is the second...
    */
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4 >
    struct Factory_CtorForwarder5 : public Detail::Factory_CtorForwarder_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
        {
            CtorForwarder_ArgvCheck_Prep(5);
            return CF::template Ctor< A0, A1, A2, A3, A4 >(argv);
        }
    };
    
    /**
       A concrete ClassWrap_Factory which creates objects by calling
       the 6-argument ctor and destroys them with 'delete'.

       A0 is the first argument type of the ctor. A1 is the second...
    */
    template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5 >
    struct Factory_CtorForwarder6 : public Detail::Factory_CtorForwarder_Base<T>
    {
        typedef typename convert::TypeInfo<T>::Type Type;
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
        {
            CtorForwarder_ArgvCheck_Prep(6);
            return CF::template Ctor< A0, A1, A2, A3, A4, A5 >(argv);
        }
    };
#undef CtorForwarder_ArgvCheck_Prep

    /**
       This class can be used to create
       v8::juice::convert::JSToNative<T> specializations for classes
       wrapped with ClassWrap.
       
       @code
       namespace v8 { namespace juice { namespace convert {
           template <>
           struct JSToNative<MyType> : v8::juice::cw::JSToNativeImpl<T>
           {};
       } } }
       @endcode
    */
    template <typename T>
    struct JSToNativeImpl
    {
        /**
           Required by JSToNative interface.
         */
        typedef typename convert::TypeInfo<T>::NativeHandle ResultType;
        /**
           If h is empty or not an Object then 0 is returned,
           otherwise the result of ToNative<T>::Value() is
           returned.
        */
        ResultType operator()( v8::Handle<v8::Value> const h ) const
        {
            if( h.IsEmpty() || !h->IsObject() )
            {
                return 0;
            }
            else
            {
                typedef ToNative<T> Caster;
                v8::Local<Object> const jo( v8::Object::Cast( *h ) );
                return Caster::Value(jo);
            }
        }
    };
//     template <typename T>
//     struct JSToNativeImpl<T*> : JSToNativeImpl<T> {};
//     template <typename T>
//     struct JSToNativeImpl<T const *> : JSToNativeImpl<T> {};
//     template <typename T>
//     struct JSToNativeImpl<T &> : JSToNativeImpl<T> {};
//     template <typename T>
//     struct JSToNativeImpl<T const &> : JSToNativeImpl<T> {};

    /**
       This class can be used to create
       v8::juice::convert::NativeToJS<T> specializations for classes
       wrapped with ClassWrap.

       @code
       namespace v8 { namespace juice { namespace convert {
           template <>
           struct NativeToJS<MyType> : v8::juice::cw::NativeToJSImpl<T>
           {};
       } } }
       @endcode
    */
    template <typename T>
    struct NativeToJSImpl
    {
        typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
        //typedef T * NativeHandle;
        typedef T const * ArgType; // const'ing NativeHandle isn't working form me?
        //typedef const typename convert::TypeInfo<T>::NativeHandle ArgType;
        /**
           If h is empty or not an Object then 0 is returned,
           otherwise the result of ToJS<T>::Value(p) is
           returned.
        */
        v8::Handle<v8::Value> operator()( ArgType p ) const
        {
            typedef ToJS< T > Cast;
            if( p ) return Cast::Value(p);
            else return v8::Handle<v8::Value>();
        }
    };

    /**
       HIGHLY EXPERIMENTAL! DON'T USE IN CLIENT CODE!

       This class defines an (optional) interface for installing class
       bindings for ClassWrap-bound types.
       
       SetupBindings() must run the C++ parts of the ClassWrap<T> binding
       process, e.g. binding member functions and whatnot.

    */
    template <typename T>
    struct Installer
    {
    public:
        /**
           This routine is responsible for installing any bindings it
           would like into the given object.

           Requirements:

           - Fetches the singleton ClassWrap<T> object via
           ClassWrap<T>::Instance().

           - Runs any binding-related operations on that instance.

           - Throws a _native_ exception on error.

           General guidelines:

           If ClassWrap<T>::Instance().IsSealed() then this function
           should call ClassWrap<T>::Instance().AddClassTo(globalObj)
           and return without performing the bindings (which are
           assumed to have already been installed via a previous
           call).
        */
        static void SetupBindings( ::v8::Handle< ::v8::Object> globalObj );
    };

#undef DBGSTREAM   
} } } // namespaces

/**
   Macro to create a v8::juice::convert::JSToNative<Type>
   specialization. Must be called from global scope!
   Type must be a type supported by ClassWrap and friends.
 */
#define JUICE_CLASSWRAP_JSTONATIVE(Type) \
       namespace v8 { namespace juice { namespace convert { \
           template <> \
           struct JSToNative< Type > : v8::juice::cw::JSToNativeImpl< Type > \
           {}; \
       } } }

/**
   Macro to create a v8::juice::cw::ClassName<Type>
   specialization. Must be called from global scope!
   Type must be a type supported by ClassWrap and friends.
*/
#define JUICE_CLASSWRAP_CLASSNAME(Type,Name)        \
       namespace v8 { namespace juice { namespace cw { \
           template <> \
           struct ClassName< Type >  \
           { static char const * Value() {return Name;} };      \
       } } }


#endif // V8_JUICE_CLASSWRAP_H_INCLUDED
