#if !defined(DOXYGEN)
// auto-generated [Mon Oct 26 22:57:46 2009] by maketypelist.pl
struct TypeList_0 : TypeChain<NilType,NilType> {};

template <class T1>
struct TypeList_1 : TypeChain<T1,NilType> {};

template <class T1, class T2>
struct TypeList_2 : TypeChain<T1, TypeChain<T2, NilType> > {};

template <class T1, class T2, class T3 >
struct TypeList_3 : TypeChain<T1, TypeList_2< T2, T3 > > {};

template <class T1, class T2, class T3, class T4 >
struct TypeList_4 : TypeChain<T1, TypeList_3< T2, T3, T4 > > {};

template <class T1, class T2, class T3, class T4, class T5 >
struct TypeList_5 : TypeChain<T1, TypeList_4< T2, T3, T4, T5 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6 >
struct TypeList_6 : TypeChain<T1, TypeList_5< T2, T3, T4, T5, T6 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7 >
struct TypeList_7 : TypeChain<T1, TypeList_6< T2, T3, T4, T5, T6, T7 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
struct TypeList_8 : TypeChain<T1, TypeList_7< T2, T3, T4, T5, T6, T7, T8 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
struct TypeList_9 : TypeChain<T1, TypeList_8< T2, T3, T4, T5, T6, T7, T8, T9 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 >
struct TypeList_10 : TypeChain<T1, TypeList_9< T2, T3, T4, T5, T6, T7, T8, T9, T10 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11 >
struct TypeList_11 : TypeChain<T1, TypeList_10< T2, T3, T4, T5, T6, T7, T8, T9, T10, T11 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12 >
struct TypeList_12 : TypeChain<T1, TypeList_11< T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13 >
struct TypeList_13 : TypeChain<T1, TypeList_12< T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14 >
struct TypeList_14 : TypeChain<T1, TypeList_13< T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14 > > {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15 >
struct TypeList_15 : TypeChain<T1, TypeList_14< T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15 > > {};

template <class T1 = NilType, class T2 = NilType, class T3 = NilType, class T4 = NilType, class T5 = NilType, class T6 = NilType, class T7 = NilType, class T8 = NilType, class T9 = NilType, class T10 = NilType, class T11 = NilType, class T12 = NilType, class T13 = NilType, class T14 = NilType, class T15 = NilType>
struct TypeList : TypeList_15<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
struct TypeList <T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, NilType> : TypeList_14<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
struct TypeList <T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, NilType, NilType> : TypeList_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
struct TypeList <T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, NilType, NilType, NilType> : TypeList_12<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
struct TypeList <T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, NilType, NilType, NilType, NilType> : TypeList_11<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
struct TypeList <T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, NilType, NilType, NilType, NilType, NilType> : TypeList_10<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
struct TypeList <T1, T2, T3, T4, T5, T6, T7, T8, T9, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_9<T1, T2, T3, T4, T5, T6, T7, T8, T9> {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
struct TypeList <T1, T2, T3, T4, T5, T6, T7, T8, NilType, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_8<T1, T2, T3, T4, T5, T6, T7, T8> {};

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
struct TypeList <T1, T2, T3, T4, T5, T6, T7, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_7<T1, T2, T3, T4, T5, T6, T7> {};

template <class T1, class T2, class T3, class T4, class T5, class T6>
struct TypeList <T1, T2, T3, T4, T5, T6, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_6<T1, T2, T3, T4, T5, T6> {};

template <class T1, class T2, class T3, class T4, class T5>
struct TypeList <T1, T2, T3, T4, T5, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_5<T1, T2, T3, T4, T5> {};

template <class T1, class T2, class T3, class T4>
struct TypeList <T1, T2, T3, T4, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_4<T1, T2, T3, T4> {};

template <class T1, class T2, class T3>
struct TypeList <T1, T2, T3, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_3<T1, T2, T3> {};

template <class T1, class T2>
struct TypeList<T1, T2, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_2<T1,T2> {};

template <class T1>
struct TypeList<T1, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType, NilType> : TypeList_1<T1> {};

template <>
struct TypeList<> : TypeChain<NilType,NilType> {};

#endif // if !defined(DOXYGEN)
