
#include <v8/juice/juice.h>

#ifndef CERR
#include <iostream>
#define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif

struct MyNative
{
    std::string str;
private:
    int proxied;
public:
    int propGetter() const
    {
        CERR << "MyNative::propGetter()\n";
        return this->proxied;
    }
    int propSetter(int v)
    {
        CERR << "MyNative::propSetter("<<v<<")\n";
        return this->proxied = v;
    }
    void propSetterVoid(int v)
    {
        CERR << "MyNative::propSetterVoid("<<v<<")\n";
        this->proxied = v;
        return;
    }
    int func1() { return 42; }
    int func2(int x) { return x*2; }
    double func3(int x,int y)
    {
        CERR << "func3("<<x<<","<<y<<")\n";
        return x*y;
    }
    std::string hi() { return "hi!"; }

    MyNative * me() { CERR << "MyNative::me()="<<this<<'\n';return this; }
    bool him(MyNative * him) { CERR << "MyNative::him("<<him<<")\n"; return 0 != him; }

    void avoid() {CERR << "MyNative::avoid()="<<this<<'\n'; }
    void avoid1(int x ) {CERR << "MyNative::avoid1("<<x<<")="<<this<<'\n'; }
    void avoid2(int x,double d ) {CERR << "MyNative::avoid2("<<x<<","<<d<<")="<<this<<'\n'; }

    double takes3(int x, int y, int z) { return x * y * z; }

    v8::Handle<v8::Value> forwarder( v8::Arguments const & );

    void someref1( MyNative & x )
    {
        CERR << "someref1("<<&x<<")\n";
        return;
    }
    V8_JUICE_BUG_NUMBER(11)
    MyNative & someref2( MyNative & x )
    {
        CERR << "someref2("<<&x<<")\n";
        return x;
    }
    V8_JUICE_BUG_NUMBER(11)
    MyNative const & someref3( MyNative const & x )
    {
        CERR << "someref3("<<&x<<")\n";
        return x;
    }

    MyNative * other;
    MyNative() : str(),
                  proxied(19),
                  other(0)
    {}
    MyNative * getOther() const
    {
        CERR << "MyNative::getOther() =="<<this->other<<"\n";
        return this->other;
    }
    void setOther(MyNative * o)
    {
        CERR << "MyNative::setOther("<<o<<")\n";
        this->other = o;
    }

    static bool SetupClass( v8::Handle<v8::Context> cx );
};

#include <v8/juice/convert.h>
#include <v8/juice/cleanup.h>
#include <v8/juice/WeakJSClassCreator.h>

namespace v8 { namespace juice {
    // An experiment: 
    //template <> struct WeakJSClassCreator_Opt_ShallowBind<MyNative> : WeakJSClassCreator_Opt_Bool<true> {};
    // ^^^ when enabled, breaks automatic conversions of JS-to-(MyNative*).
    template <> struct WeakJSClassCreator_Opt_AllowCtorWithoutNew<MyNative> : WeakJSClassCreator_Opt_Bool<false> {};
    template <>
    struct WeakJSClassCreatorOps<MyNative>
    {
    private:
	/** Callback for use with juice::cleanup::AddToCleanup(). */
	static void cleanup_callback( void * obj )
	{
	    Dtor( static_cast<WrappedType*>(obj) );
	}
    public:
	enum { ExtraInternalFieldCount = 0 };
	typedef MyNative WrappedType;
	static char const * ClassName() { return "MyNative"; }
	static WrappedType * Ctor( Arguments const & argv,
				   std::string & exceptionText)
	{
	    MyNative * obj = new MyNative;
	    obj->str = "hi, world";
	    CERR << "Ctor() create @"<<obj<<'\n';
	    ::v8::juice::cleanup::AddToCleanup(obj,cleanup_callback);
	    //bind::BindNative( 0, obj, obj );
	    return obj;
	}

	static void Dtor( WrappedType * obj )
	{
	    CERR << "Dtor() passing on @"<<obj<<'\n';
	    if( obj )
	    {
		//bind::UnbindNative( 0, obj, obj );
		::v8::juice::cleanup::RemoveFromCleanup(obj);
		delete obj;
	    }
	}
    };

}} // v8::juice

#define WEAK_CLASS_TYPE MyNative
#include <v8/juice/WeakJSClassCreator-CastOps.h>

