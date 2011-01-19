#ifndef V8_JUICE_TYPELIST_HPP_INCLUDED
#define V8_JUICE_TYPELIST_HPP_INCLUDED

#include "tmp.h" // base metatemplate stuff
namespace v8 { namespace juice {
namespace tmp {

    /**
       A "null" type for use in marking the end of a TypeList.
       It must not appear in a TypeList (or TypeChain) anywhere
       other than the end (or after the end, in the case of
       TypeList).
    */
    struct NilType
    {
    };

    /** @struct TypeChain

       A base type for implementing a list of types, implemented as a
       Typelist, as described by Alexandrescu in "Modern C++
       Design". H may be any type. T _must_ be either NilType (to mark
       the end of the typelist) or another TypeChain.

       Client code will normally use the generated TypeList<> types
       instead of using this one directly.

       Unlike Alexandrescu's Typelists, which are implemented
       faithfully (with one small addition) by this class, our
       TypeList type is parameterized for some maximum number of
       arguments. This simplifies client-side usage but imposes (A) a
       hard-coded maximum on the number of items in the list and (B)
       another (internal) level of indirection for implementing the
       typelist algorithms described by Alexandrescu (length,
       index-of, etc.).
    */
    template <typename H, typename T>
    struct TypeChain
    {
	/**
	   Subtypes of this type should not override the ChainType
	   typedef, as it is used by the core lib to trick some
	   overloads into working, such that subclasses of
	   TypeChain will be picked up by specializations for
	   certain rules, as if they actually were a TypeChain.

	   There might be exceptions to the no-override rule, but none
	   come to mind. If it is overridden, it _must_ be-a
	   TypeChain<> type.
	*/
	typedef TypeChain<H,T> ChainType;
	/* First Type in the list. */
	typedef H Head;
	/* Second type in the list. MUST be either NilType or a
	   TypeChain<>.
	*/
	typedef T Tail;

    };

    template <typename ListT>
    struct LengthOf;

#if !defined(DOXYGEN)
    namespace Detail
    {
        namespace tmp = v8::juice::tmp;
        /** Internal impl of tmp::LengthOf. */
        template <typename T>
        struct LengthOfImpl
        {
            enum { Value = 1 };
        };
        template <>
        struct LengthOfImpl<tmp::NilType>
        {
            enum { Value = 0 };
        };
        template <typename H, typename T>
        struct LengthOfImpl< tmp::TypeChain<H,T> >
        {
            enum { Value = 1 +
                   //LengthOfImpl<T>::Value
                   LengthOf<T>::Value
            };
        };
    }
#endif

    /**
       A template metafunction to compute the length of a TypeList.
       ListT must conform to the TypeChain interface.
    */
    template <typename ListT>
    struct LengthOf
    {
        enum {
        /**
           The number of types in ListT.
        */
        Value =
        Detail::LengthOfImpl< typename ListT::Head >::Value
              + LengthOf< typename ListT::Tail >::Value
        // WTF does this not work? Detail::LengthOfImpl< TypeChain<typename ListT::Head, typename ListT::Tail > >::Value
        // nor this? Detail::LengthOfImpl< typename ListT::Head >::Value
        //      + Detail::LengthOfImpl< typename ListT::Tail >::Value
        };
    };

    /** Specialization for end-of-list. */
    template <>
    struct LengthOf<NilType>
    {
        enum { Value = 0 };
    };

    template <typename ListT, unsigned char Index>
    struct TypeAt;
#if !defined(DOXYGEN)
    namespace Detail
    {
        namespace tmp = v8::juice::tmp;
        /** Internal impl of tmp::TypeListIndexOf. */
        template <typename T, unsigned char I> struct TypeAtImpl;
        template <int I>
        struct TypeAtImpl< tmp::NilType,I>
        {
            typedef NilType Type;
        };
        template <typename H, typename T>
        struct TypeAtImpl< tmp::TypeChain<H,T>,0>
        {
            typedef H Type;
        };
        /** Special case for empty list. */
        template <unsigned char I>
        struct TypeAtImpl< tmp::TypeChain<tmp::NilType,tmp::NilType>, I >
        {
            typedef NilType Type;
        };
        template <typename H, typename T,unsigned char I>
        struct TypeAtImpl< tmp::TypeChain<H,T>, I>
        {
            typedef typename
            //TypeAtImpl<T, I - 1>::Type
            TypeAt<T,I-1>::Type
            Type;
        private:
            enum {
            Length = tmp::LengthOf< tmp::TypeChain<H,T> >::Value,
            /** If your compiler led you here then I is out of range. */
            SizeIsValid = tmp::Assertion< (I<Length) >::Value
            };
        };
    }
#endif

    /** @struct TypeAt
        
       A template metafunction to type at a specific offset in a TypeList.
       ListT must be a TypeList, or otherwise conform to the TypeChain
       interface.
    */
    template <typename ListT, unsigned char Index>
    struct TypeAt
    {
        /**
           The type at the given index in the list.
        */
        typedef typename 
        //Detail::TypeAtImpl< TypeChain<typename ListT::Head, typename ListT::Tail>, Index>::Type
        Detail::TypeAtImpl< typename ListT::ChainType, Index>::Type
        Type;
    };
    /** Specialization for end of list. */
    template <unsigned char Index>
    struct TypeAt<NilType,Index>
    {
        /**
           The type at the given index in the list.
        */
        typedef NilType Type;
    };


}}} // namespaces

#ifndef V8_JUICE_TYPELIST_MAX_ARGS
/** @def V8_JUICE_TYPELIST_MAX_ARGS
   Define V8_JUICE_TYPELIST_MAX_ARGS before including this file to set
   the maximum number of arguments which TypeList<> can accept. It
   defaults to "some reasonable number", and pre-generated versions
   are available for "some other reasonable number". For generating
   variants with higher arg counts, see the maketypelist.pl script in
   this code's source repo.

   ACHTUNG:

   Changing this number may require rebuilding any code compiled using
   a different number. The main template instantiations will be
   different for code generated with a different maximum arg count.
   So pick a number and stick with it.


   Maintenance note: we don't expect to have more than 4-6 types in
   the lists for most v8-juice use cases (passing function argument
   type info around), and 10 would be a fairly extreme case. Thus the
   default value forV8_JUICE_TYPELIST_MAX_ARGS is fairly low.

   Maintenance note: the script for generating the TypeList_NN.h files
   is in the source repo with TypeList.h, called maketypelist.pl.
*/
#define V8_JUICE_TYPELIST_MAX_ARGS 10
#endif
namespace v8 { namespace juice { namespace tmp {
    /** @struct TypeList
        
       The TypeList type is a quasi-variadic template type which is specialized to
       take up to some compile-time limit (see V8_JUICE_TYPELIST_MAX_ARGS) of _types_
       as arguments. All of the TypeList code is generated from a script.

       TypeList is simply a TypeChain<> type for which specializations
       restructure the template arguments to conform to the TypeChain
       interface. For algorithms which specifically require a
       TypeChain as a template argument (for specialization purposes),
       use TypeList::ChainType to "convert" the TypeList to a
       TypeChain.
    */
#if V8_JUICE_TYPELIST_MAX_ARGS < 6
// template <class T1, class T2, class T3, class T4, class T5>
// struct TypeList; // only here so Doxygen will list this type
#  define V8_JUICE_TYPELIST_HEADER "TypeList_05.h"
#elif V8_JUICE_TYPELIST_MAX_ARGS < 11
// template <class T1, class T2, class T3, class T4, class T5,
//           class T6, class T7, class T8, class T9, class T10>
// struct TypeList; // only here so Doxygen will list this type
#  define V8_JUICE_TYPELIST_HEADER "TypeList_10.h"
#elif V8_JUICE_TYPELIST_MAX_ARGS < 16
// template <class T1, class T2, class T3, class T4, class T5,
//           class T6, class T7, class T8, class T9, class T10,
//           class T11, class T12, class T13, class T14, class T15>
// struct TypeList; // only here so Doxygen will list this type
#  define V8_JUICE_TYPELIST_HEADER "TypeList_15.h"
#else
#    error "V8_JUICE_TYPELIST_MAX_ARGS is too high. See the docs above this code for details."
#endif

#include V8_JUICE_TYPELIST_HEADER
#undef V8_JUICE_TYPELIST_HEADER
#undef V8_JUICE_TYPELIST_MAX_ARGS

}}} // namespaces

namespace v8 { namespace juice { namespace tmp {

    /**
       A metatemplate who's Type member resolves to IF if Cond is
       true, or ELSE if Cond is false. Its Value member evaluates
       to 1 or 0, accordingly.
    */
    template <bool Cond, typename IF, typename ELSE>
    struct IfElse : TypeAt< TypeChain<IF, TypeChain<ELSE,NilType> >, Cond ? 0 : 1 >
    {
        enum { Value = Cond ? 1 : 0 };
    };


    
    template < typename ListT >
    struct Or;
#if !defined(DOXYGEN)
    namespace Detail
    {
        namespace tmp = v8::juice::tmp;
        /** Internal impl of tmp::TypeListIndexOf. */
        template <typename T> struct OrImpl
        {
            enum { Value = T::Value };
        };
        template <>
        struct OrImpl< tmp::NilType >
        {
            enum { Value = 0 };
        };
//         template <typename H>
//         struct OrImpl< tmp::TypeChain<H,tmp::NilType> >
//         {
//             enum { Value = OrImpl<H>::Value };
//         };
        /** Special case for empty list. */
        template <>
        struct OrImpl< tmp::TypeChain<tmp::NilType,tmp::NilType> > : tmp::BoolVal<false>
        {};

        template <typename H, typename T>
        struct OrImpl< tmp::TypeChain<H,T> >
        {
            enum { Value =
                   ((OrImpl<H>::Value || Or<T>::Value) ? 1 : 0)
            };
        };
    }
#endif
    /** @struct Or

       Metatemplate whos Value is true if any item in ListT is a
       metafunction with a true Value.

       ListT must be TypeChain-complaint and must contain only types
       which contain a bool-evaluable Value member.

       As a special case, an empty list evaluates to false.
    */
    template < typename ListT >
    struct Or
    {
        enum { Value =
               //Detail::OrImpl< TypeChain< typename ListT::Head, typename ListT::Tail > >::Value
               Detail::OrImpl< typename ListT::ChainType >::Value
        };
    };
    /** Specialization for end of list. */
    template <>
    struct Or<NilType> : BoolVal<false>
    {
    };

    template < typename ListT >
    struct And;
#if !defined(DOXYGEN)
    namespace Detail
    {
        namespace tmp = v8::juice::tmp;
        /** Internal impl of tmp::TypeListIndexOf. */
        template <typename T> struct AndImpl
        {
            enum { Value = T::Value };
        };
        template <>
        struct AndImpl< tmp::NilType >
        {
            enum { Value = 1 };
        };
        //! Special case for empty list.
        template <>
        struct AndImpl< tmp::TypeChain<tmp::NilType,tmp::NilType> > : tmp::BoolVal<false>
        {};
        template <typename H, typename T>
        struct AndImpl< tmp::TypeChain<H,T> >
        {
            enum { Value =
                   ((AndImpl<H>::Value && And<T>::Value) ? 1 : 0)
            };
        };
    }
#endif
    /** @struct And

       Metatemplate whos Value is true if ListT contains only
       metafunctions with a true Value, else false.

       ListT must be TypeChain-complaint and must contain only
       types which contain a bool-evaluable Value member.

       As a special case, an empty list evaluates to false.
    */
    template < typename ListT >
    struct And
    {
        enum { Value =
               //Detail::AndImpl< TypeChain< typename ListT::Head, typename ListT::Tail > >::Value
               Detail::AndImpl< typename ListT::ChainType >::Value
        };
    };
    /** Specialization for end of list. */
    template <> struct And<NilType> : BoolVal<true>
    {
    };
    
    
}}} // v8::juice::tmp

#endif // V8_JUICE_TYPELIST_HPP_INCLUDED
