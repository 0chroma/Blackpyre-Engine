#ifndef CODE_GOOGLE_COM_V8_JUICE_STATIC_ASSERT_H_INCLUDED
#define CODE_GOOGLE_COM_V8_JUICE_STATIC_ASSERT_H_INCLUDED

#if 1
/*
  Static assertion code taken from Alexandrescu's Modern C++ Design
  and then twiddled a bit.

  Args:

  'test' is a compile-time condition which evaluates to true or
  false. If false, it triggers the instantiation of an incomplete
  class, with the error message encoded in the class name.

  'errormsg' is an identifier which forms the error text (no spaces!).
  e.g. Illegal_argument_combination.

  The error messages come out looking something like:

  @code
  my.cpp:196: error: no matching function for call to <unnamed>::compile_time_assertion<false>::
  compile_time_assertion(v8::juice::ClassWrap<T>::check_assertions()
      [with T = v8::juice::BoundNative]::
      STATIC_ASSERTION_ClassWrap_Ops_InternalFields_Value_Is_Too_Small)
  @endcode

*/

#   define JUICE_STATIC_ASSERT(test, errormsg)                         \
    do {                                                                \
        struct STATIC_ASSERTION_##errormsg {};                          \
        typedef compile_time_assertion< (test) ? true : false > tmplimpl; \
        tmplimpl aTemp = tmplimpl(STATIC_ASSERTION_##errormsg());       \
        (void) sizeof(aTemp);                                           \
    } while (0)
#else
#   define JUICE_STATIC_ASSERT(test, errormsg)                         \
    do {(void)1;} while (0)
#endif
namespace {
    /**
       Base instantiation of a static assertion class.
       It is not called static_assert because that name
       will be reserved in C++0x.
    */
    template<bool> class compile_time_assertion
    {
    public:
        compile_time_assertion(...) {}
    };

    /**
       Specialization for error cases. 
    */
    template<> class compile_time_assertion<false>
    {
    };
}

#endif // CODE_GOOGLE_COM_V8_JUICE_STATIC_ASSERT_H_INCLUDED
