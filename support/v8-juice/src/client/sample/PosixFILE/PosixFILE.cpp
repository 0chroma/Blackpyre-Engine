/************************************************************************
Author: Stephan Beal (http://wanderinghorse.net/home/stephan)

License: Public Domain

Test/demo code for the v8::juice::cw::ClassWrap class binding mechanism.

This code demonstrates a proxy for POSIX FILE handles. It operates in
two modes:

- As a class, with access via member functions.

- Using the C-standard FILE API, e.g. fopen(), fclose(), and friends,
work mostly like their native counterparts (where C/JS calling conventions
allow).

In particular, it demonstrates one way we can use the ClassWrap API to
bind two different natives to the same JS object, such that we can
type-convert to/from JS/Native and either native type, though we only
have one JS object.

************************************************************************/
#if !defined _POSIX_SOURCE
#define _POSIX_SOURCE 1 // for fileno()
#endif
#if !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200112L // for fsync()/fdatasync()
#endif

#include <v8/juice/ClassWrap.h>
#include <v8/juice/forwarding.h>
#include <v8/juice/plugin.h>
#include <v8/juice/juice.h>

#include <stdio.h> // FILE and friends
#include <errno.h>
#include <sstream>
#include <vector>
#ifndef CERR
#include <iostream> /* only for debuggering */
#define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif

using namespace v8::juice::tmp;

v8::Handle<v8::Value> PosixFILE_fopen( v8::Handle<v8::Value> const & fn, v8::Handle<v8::Value> const & fm );
std::string PosixFILE_fread( size_t len, size_t n, FILE * f );
size_t PosixFILE_fwrite( std::string const &, FILE * );
size_t PosixFILE_fwrite( std::string const &, size_t, FILE * );
size_t PosixFILE_fwrite( std::string const &, size_t, size_t, FILE * );

/**
   A FILE wrapper class for use with ClassWrap.
 */
struct PosixFILE
{
public:
    static bool enableDebug;
private:
    std::string fname;
    std::string fmode;
    FILE * fh;
#define DBGOUT if(PosixFILE::enableDebug) CERR
    bool open(std::string const & name, std::string const & mode)
    {
        if( this->fh )
        {
            this->close();
        }
        this->fname = name;
        this->fmode = mode;
        this->fh = ::fopen( name.c_str(), mode.c_str() );
        return 0 != this->fh;
    }
public:
    PosixFILE(std::string const & name, std::string const & mode)
        : fname(),fmode(),fh(0)
    {
        DBGOUT << "FILE("<<name<<", "<<mode<<")@"<<(void const *)this<<'\n';
        if( ! this->open( name, mode ) )
        {
            std::ostringstream os;
            os << "Open ("<<name<<", "<<mode<<") failed. errno="<< errno;
            throw std::runtime_error( os.str().c_str() );
        }
    }
    virtual ~PosixFILE()
    {
        DBGOUT << "~PosixFILE()@"<<(void const *)this<<'\n';
        this->close();
    }
    std::string name() const
    {
        return this->fname;
    }
    std::string mode() const
    {
        return this->fmode;
    }
    void close()
    {
        if( this->fh )
        {
            DBGOUT << "~PosixFILE()@"<<(void const *)this<<"->close()\n";
            this->flush();
            ::fclose( this->fh );
            this->fh = 0;
        }
    }
    /**
       Destroys this object via the JS engine.  Returns true if it can
       destroy this object, else false. If this object was not created
       via ClassWrap<PosixFILE>::Instance().NewInstance() (or
       equivalent) then destruction will fail.

       After this call, this object must not be used.
    */
    bool destroy();

    int eof()
    {
        return this->fh ? ::feof(this->fh) : 0;
    }

    int error()
    {
        return this->fh ? ::ferror(this->fh) : 0;
    }

    void clearerr()
    {
        if( this->fh ) ::clearerr(this->fh);
    }

    int truncate( int64_t off )
    {
        return this->fh
            ? ftruncate( this->fileno(), off )
            : -1;
    }
    
    uint64_t size()
    {
        int64_t pos = this->tell();
        int x = this->seek( 0L, SEEK_END );
        if( 0 != x ) return 0;
        int64_t npos = this->tell();
        this->seek( pos, SEEK_END );
        return npos;
    }
    
    /** Reads n objects of len bytes each and returns the result as a string.*/
    std::string read( size_t len, size_t n )
    {
        if( ! this->fh ) return "";
        return PosixFILE_fread( len, n, this->fh );
    }
    /** Reads len bytes and returns the result as a string.*/
    std::string read( size_t len )
    {
        return this->read( len, 1 );
    }
    /** Writes n objects of len bytes each from data. Returns the number of
        objects written.*/
    size_t write( std::string const & data, size_t len, size_t n )
    {
        return PosixFILE_fwrite( data, len, n, this->fh );
    }
    /** Equivalent to write(data,len,1). */
    size_t write( std::string const & data, size_t len )
    {
        return this->write( data, len, 1 );
    }
    /** Equivalent to write(data,data.size(),1). */
    size_t write( std::string const & data )
    {
        return this->write( data, data.size(), 1 );
    }

    int fileno() const
    {
        return this->fh ? ::fileno(this->fh) : -1;
    }
    
    int sync()
    {
        return fsync( this->fileno() );
    }

    int datasync()
    {
        return fdatasync( this->fileno() );
    }

    int flush()
    {
        return fflush( this->fh );
    }

    int64_t seek( int64_t off, int whence )
    {
        return ::fseek( this->fh, off, whence );
    }

    /** Equivalent to seek(off,SEEK_SET). */
    int64_t seek( int64_t off )
    {
        return this->seek( off, SEEK_SET );
    }

    void rewind()
    {
        if( this->fh) ::rewind( this->fh );
    }

    int64_t tell()
    {
        return ::ftell( this->fh );
    }

    /** Fetches errno. */
    int cerrno() const
    {
        return errno;
    }
    /** Sets errno and returns errno's previous value. */
    int cerrno( int e )
    {
        int x = errno;
        errno = e;
        return x;
    }

    int unlink()
    {
        return ::unlink( this->fname.c_str() );
    }

    /** toString() for JS. */
    std::string toString() const;

    /**
       Installs this class' bindings into dest.
    */
    static void SetupBindings( v8::Handle<v8::Object> dest );
private:
    /**
       Only for use in JS/(FILE*) conversion routines.
    */
    FILE * handle()
    {
        return this->fh;
    }
    friend class v8::juice::convert::JSToNative<FILE>;
    friend class v8::juice::cw::WeakWrap<PosixFILE>;
};
#include <v8/juice/ClassWrap_TwoWay.h>
////////////////////////////////////////////////////////////////////////
// Set up our ClassWrap policies...
namespace v8 { namespace juice { namespace cw
{
   
    template <> struct DebugLevel<PosixFILE> : Opt_Int<2> {};

    template <>
    struct ToNative_SearchPrototypesForNative<PosixFILE>
        : Opt_Bool<true>
    {};

    template <>
    struct AllowCtorWithoutNew<PosixFILE>
        : Opt_Bool<false>
    {};

    template <>
    struct InternalFields<PosixFILE>
        : InternalFields_Base<PosixFILE,1,0>
    {};

    template <>
    struct Factory<PosixFILE>
        : Factory_CtorForwarder2<PosixFILE,std::string const &,std::string const &>
    {};

    template <>
    struct Extract< PosixFILE > :
        TwoWayBind_Extract< PosixFILE > {};

    template <>
    struct ToNative< PosixFILE > :
        ToNative_Base< PosixFILE > {};
    
    template <>
    struct ToJS< PosixFILE > :
        TwoWayBind_ToJS< PosixFILE > {};

    template <>
    struct ClassName< PosixFILE >
    {
        static char const * Value()
        {
            return "FILE";
        }
    };

    template <>
    struct WeakWrap< PosixFILE >
    {
        typedef PosixFILE Type;
        typedef PosixFILE * NativeHandle;
        typedef Detail::ClassWrapMapper<FILE> FMapper;
        typedef TwoWayBind_WeakWrap<PosixFILE> WB;
        static void Wrap( v8::Persistent<v8::Object> const & jsSelf, NativeHandle nativeSelf )
        {
            WB::Wrap( jsSelf, nativeSelf );
            FMapper::Insert( jsSelf, nativeSelf->handle() );
            return;
        }
        static void Unwrap( v8::Handle<v8::Object> const & jsSelf, NativeHandle nativeSelf )
        {
            FMapper::Remove( nativeSelf->handle() );
            WB::Unwrap( jsSelf, nativeSelf );
            return;
        }
    };

    template <>
    struct Installer<PosixFILE>
    {
    public:
        /**
           Installs the bindings for PathFinder into the given object.
        */
        static void SetupBindings( ::v8::Handle< ::v8::Object> target )
        {
            PosixFILE::SetupBindings(target);
        }
    };
    
} } } // v8::juice::cw

bool PosixFILE::enableDebug = v8::juice::cw::DebugLevel<PosixFILE>::Value > 2;

namespace v8 { namespace juice { namespace convert
{

    template <>
    struct JSToNative< PosixFILE > : v8::juice::cw::JSToNativeImpl< PosixFILE >
    {};
    
    template <>
    struct NativeToJS< PosixFILE > : v8::juice::cw::NativeToJSImpl< PosixFILE >
    {};

    template <>
    struct JSToNative< FILE >
    {
	typedef FILE * ResultType;
	ResultType operator()( v8::Handle<v8::Value> const & h ) const
	{
	    typedef JSToNative<PosixFILE> Proxy;
            PosixFILE * p = Proxy()(h);
            return p ? p->handle() : 0;
	}
    };

    template <>
    struct NativeToJS< FILE >
    {
	typedef FILE const * ArgType;
	v8::Handle<v8::Value> operator()( ArgType h ) const
	{
            typedef v8::juice::cw::Detail::ClassWrapMapper<FILE> FMapper;
            return FMapper::GetJSObject( h );
	}
    };

} } } // v8::juice::convert


/************************************************************************
   Down here is where the runtime setup parts of the bindings take place...
************************************************************************/

bool PosixFILE::destroy()
{
    typedef v8::juice::cw::ClassWrap<PosixFILE> CW;
    this->close();
    return CW::DestroyObject( v8::juice::convert::CastToJS( this ) );
}

std::string PosixFILE::toString() const
{
    std::ostringstream os;
    os << "[object "
       << v8::juice::cw::ClassName<PosixFILE>::Value()
       << "@"<<(void const *)this
       <<" name="<<this->fname<<", "
       <<" mode="<<this->fmode<<"]";
    return os.str();
}


// Analogous to fopen( filename, mode )
v8::Handle<v8::Value> PosixFILE_fopen( v8::Handle<v8::Value> const & fn, v8::Handle<v8::Value> const & fm )
{
    typedef PosixFILE N;
    namespace cv = v8::juice::convert;
    std::vector< v8::Handle< v8::Value > > varg(2, v8::Undefined() );
    varg[0] = fn;
    varg[1] = fm;
    typedef v8::juice::cw::ClassWrap<N> CW;
    return CW::Instance().NewInstance(2,&varg[0]);
}

// Analogous to fread( buffer, len, n, FILE )
std::string PosixFILE_fread( size_t len, size_t n, FILE * f )
{
    if( ! n || !len ) return "";
    if( !f )
    {
        v8::ThrowException(v8::String::New("fread() final argument must be-a FILE."));
        return "";
    }
    typedef std::vector<unsigned char> VecType;
    VecType buffer( (len*n)+1, 0 );
    size_t rc = ::fread( &buffer[0], len, n, f );
    size_t x = rc * len;
    buffer[x] = 0;
    char const * cp = reinterpret_cast<char const *>( &buffer[0] );
    return std::string( cp ? cp : "" );
}

//! Equivalent to PosixFILE_fread( len, 1, f ).
std::string PosixFILE_fread( size_t len, FILE * f )
{
    return PosixFILE_fread( len, 1, f );
}
//! Almost analogous to ::fwrite( s.c_str(), len, n, f ).
size_t PosixFILE_fwrite( std::string const & s, size_t len, size_t n, FILE * f )
{
    if( ! n || !len ) return 0;
    if( !f )
    {
        v8::ThrowException(v8::String::New("fwrite() final argument must be-a FILE."));
        return 0;
    }
    char const * head = s.c_str();
#if 0
    char const * tail = head + s.size();
    char const * cp = head;
    size_t rc = 0;
    for( ; (cp<(tail-len)) && (n > 0); --n, cp += len, ++rc )
    {
        if( 1 != ::fwrite( cp, len, 1, f ) ) break;
    }
    return rc;
#else
    if( s.size() < (len*n) )
    {
        v8::juice::convert::StringBuffer msg;
        msg << "fwrite() input buffer is too small ("
            << s.size() << ") for the requested write of "
            << n << " objects of "<<len<<" bytes each!"
            ;
        v8::ThrowException(msg);
        return 0;
    }
    return ::fwrite( head, len, n, f );
#endif
}

//! Equivalent to PosixFILE_fwrite( s, len, 1, f ).
size_t PosixFILE_fwrite( std::string const & s, size_t len, FILE * f )
{
    return PosixFILE_fwrite( s, len, 1, f );
}

//! Equivalent to PosixFILE_fwrite( s, s.size(), 1, f ).
size_t PosixFILE_fwrite( std::string const & s, FILE * f )
{
    return PosixFILE_fwrite( s, s.size(), 1, f );
}

int PosixFILE_unlink( std::string const & s )
{
    return ::unlink( s.c_str() );
}

int PosixFILE_ftruncate( v8::Handle<v8::Value> const & h, int64_t off )
{
    PosixFILE * pf = v8::juice::convert::CastFromJS<PosixFILE>( h );
    if( pf ) return pf->truncate(off);
    else return ::ftruncate( v8::juice::convert::JSToInt32(h), off );
}

int PosixFILE_fsync( v8::Handle<v8::Value> const & h )
{
    PosixFILE * pf = v8::juice::convert::CastFromJS<PosixFILE>( h );
    if( pf ) return pf->sync();
    else return ::fsync( v8::juice::convert::JSToInt32(h) );
}

char const * cstring_test( char const * c )
{
    CERR << "cstring_test( @"<<(void const *)c<<") ["<<(c ? c : "<NULL>")<<"]\n";
    return c;
}

/**
   Sets up the Posix FILE-related bindings.

   The dest object gets a new member named posix which contains
   the following properties:

   Classes:
   
   - FILE

   Functions:
   
   - void clearerr(FILE)
   - bool fclose(FILE)
   - int fdatasync(int)
   - int feof(FILE)
   - int ferror(FILE)
   - int fileno(FILE)
   - int flush(FILE)
   - int ftell(FILE)
   - FILE fopen(string filename, string mode)
   - string fread( int sizeEach, int count, FILE )
   - string fread( int bytes, FILE )
   - int fseek(FILE,int,int)
   - int fsync(FILE | int)
   - int ftruncate(FILE | int, int)
   - int fwrite( string src, int sizeEach, int howMany, FILE )
   - int fwrite( string src, int bytes, FILE )
   - int fwrite( string src, FILE )
   - void rewind(FILE)
   - int unlink( string )

   Properties (read-only):

   - SEEK_SET
   - SEEK_CUR
   - SEEK_GET

*/
void PosixFILE::SetupBindings( v8::Handle<v8::Object> dest )
{
    using namespace v8;
    using namespace v8::juice;
    HandleScope scope;
    typedef PosixFILE N;
    typedef cw::ClassWrap<N> CW;
    CW & cw( CW::Instance() );
    DBGOUT <<"Binding class "<<CW::ClassName::Value()<<"...\n";
    typedef convert::InvocationCallbackCreator ICC;
    typedef convert::MemFuncInvocationCallbackCreator<N> ICM;

    // write(...) overloads:
    typedef tmp::TypeList<
        convert::InvocableMemFunc1<N,size_t,std::string const &,&N::write>,
        convert::InvocableMemFunc2<N,size_t,std::string const &,size_t,&N::write>
        > WriteList;
    // read(...) overloads:
    typedef tmp::TypeList<
        convert::InvocableMemFunc1<N,std::string,size_t,&N::read>,
        convert::InvocableMemFunc2<N,std::string,size_t,size_t,&N::read>
        > ReadList;
    // seek(...) overloads:
    typedef tmp::TypeList<
        convert::InvocableMemFunc1<N,int64_t,int64_t,&N::seek>,
        convert::InvocableMemFunc2<N,int64_t,int64_t,int,&N::seek>
        > SeekList;
    cw
        .Set( "clearerr", ICM::M0::Invocable<void,&N::clearerr> )
        .Set( "close", ICM::M0::Invocable<bool,&N::destroy> )
        //.Set( "destroy", ICM::M0::Invocable<bool,&N::destroy> )
        .Set( "datasync", ICM::M0::Invocable<int,&N::datasync> )
        .Set( "eof", ICM::M0::Invocable<int,&N::eof> )
        .Set( "error", ICM::M0::Invocable<int,&N::error> )
        .Set( "fileno", ICM::M0::Invocable<int,&N::fileno> )
        .Set( "flush", ICM::M0::Invocable<int,&N::flush> )
        .Set( "read", convert::OverloadInvocables<ReadList>::Invocable )
        .Set( "rewind", ICM::M0::Invocable<void,&N::rewind> )
        .Set( "seek", convert::OverloadInvocables<SeekList>::Invocable )
        .Set( "size", ICM::M0::Invocable<uint64_t,&N::size> )
        .Set( "sync", ICM::M0::Invocable<int,&N::sync> )
        .Set( "tell", ICM::M0::Invocable<int64_t,&N::tell> )
        .Set( "truncate", ICM::M1::Invocable<int,int64_t,&N::truncate> )
        .Set( "toString", ICM::M0::Invocable<std::string,&N::toString> )
        .Set( "unlink", ICM::M0::Invocable<int,&N::unlink> )
        .Set( "write", convert::OverloadInvocables<WriteList>::Invocable )
        ;
    cw.BindGetter<std::string,&N::name>("name");
    cw.BindGetter<std::string,&N::mode>("mode");
    cw.BindGetterSetter<int,&N::cerrno,int,int,&N::cerrno>("errno");
    cw.BindStaticVar<bool,&N::enableDebug>( "debug" );
    v8::Handle<v8::Function> ctor = cw.Seal();
    v8::Handle<v8::Object> posix = v8::juice::GetNamespaceObject( dest, "posix" );
    cw.AddClassTo( posix );
    
#define JF v8::FunctionTemplate::New(cb)->GetFunction()
#define JSTR(X) v8::String::New(X)
#define F(X) posix->Set( JSTR(X), JF )
    v8::InvocationCallback cb;

    cb = ICC::F1::Invocable<void,FILE*,::clearerr>;
    F("clearerr");

    cb =ICC::F1::Invocable<bool,v8::Handle<v8::Value> const &,CW::DestroyObject>;
    F("fclose");

    cb = ICC::F1::Invocable<int,int,::fdatasync>;
    F("fdatasync");

    cb = ICC::F1::Invocable<int,FILE*,::feof>;
    F("feof");

    cb = ICC::F1::Invocable<int,FILE*,::ferror>;
    F("ferror");

    cb = ICC::F1::Invocable<int,FILE*,::fileno>;
    F("fileno");

    cb = ICC::F1::Invocable<int,FILE*,::fflush>;
    F("fflush");

    cb = ICC::F1::Invocable<long,FILE*,::ftell>;
    F("ftell");

    cb = ICC::F2::Invocable< v8::Handle<v8::Value>,
        v8::Handle<v8::Value> const &,
        v8::Handle<v8::Value> const &,
        PosixFILE_fopen>;
    F("fopen");

    typedef tmp::TypeList<
        convert::InvocableFunction2<std::string,size_t,FILE*,PosixFILE_fread>,
        convert::InvocableFunction3<std::string,size_t,size_t,FILE*,PosixFILE_fread>
        > FReadList;
    cb = convert::OverloadInvocables<FReadList>::Invocable;
    F("fread");

    cb = ICC::F3::Invocable<int,FILE*,long,int,::fseek>;
    F("fseek");

    cb = ICC::F1::Invocable<int,v8::Handle<v8::Value> const &,PosixFILE_fsync>;
    F("fsync");

    cb = ICC::F2::Invocable<int,v8::Handle<v8::Value> const &,int64_t,::PosixFILE_ftruncate>;
    F("ftruncate");

    cb =
        //ICC::F1::Invocable<int,std::string const &,::PosixFILE_unlink>;
        ICC::F1::Invocable<int,char const *,::unlink>;
    F("unlink");

    cb =ICC::F1::Invocable<char const *,char const *,cstring_test>;
    F("cstr");

    
    typedef tmp::TypeList<
        convert::InvocableFunction2<size_t,std::string const &,FILE*,PosixFILE_fwrite>,
        convert::InvocableFunction3<size_t,std::string const &,size_t,FILE*,PosixFILE_fwrite>,
        convert::InvocableFunction4<size_t,std::string const &,size_t,size_t,FILE*,PosixFILE_fwrite>
        > FWriteList;
    cb = convert::OverloadInvocables<FWriteList>::Invocable;
    F("fwrite");

    cb = ICC::F1::Invocable<void,FILE*,::rewind>;
    F("rewind");
#undef JF
#undef F
    {
        v8::juice::convert::ObjectPropSetter ops(posix);
        ops( "SEEK_SET", SEEK_SET )
            ( "SEEK_CUR", SEEK_CUR )
            ( "SEEK_END", SEEK_END )
            ;
    }
    static const bool doDebug = (v8::juice::cw::DebugLevel<PosixFILE>::Value > 2);
#undef JSTR

    if(doDebug)
    { // try to create a few objects for testing/sanity checking...
        //v8::HandleScope hscope;
        namespace cv = v8::juice::convert;
        std::vector< v8::Handle< v8::Value > > varg(3, v8::Null() );
        varg[0] = cv::CastToJS("/dev/null");
        varg[1] = cv::CastToJS("w+");
        Handle<Object> jobj =
            CW::Instance().NewInstance(2,&varg[0])
            //ctor->NewInstance(2,&varg[0])
            ;
        N * bound = CW::ToNative::Value(jobj);
        DBGOUT << "bound (void *) == @"<<(void const *)bound<<'\n';
        DBGOUT << "bound (CastFromJS<T>(jsObj)) == @"<<convert::CastFromJS<N>( jobj )<<'\n';
        DBGOUT << "FILE* == @"<<cv::CastFromJS<FILE*>(jobj)<<'\n';
        N & boundRef = convert::CastFromJS<N&>( jobj );
        DBGOUT << "Cast to ref apparently works: @"<<&boundRef<<'\n';
        if( bound )
        {
            //Handle<Value> = MFF::Call( obj, PosixFILE::toString
            void * exh = jobj->GetPointerFromInternalField(CW::InternalFields::NativeIndex);
            DBGOUT << "fetched void* == "<<(const void *)exh<<'\n';
        }
        if(0)
        {
            v8::HandleScope hs;
            int level = 1;
            v8::Local<v8::Value> proto = jobj->GetPrototype();
            for( ; ! proto.IsEmpty() && proto->IsObject(); ++level )
            {
                DBGOUT << "Prototype level "<<level<<'\n';
                proto = Local<Object>( v8::Object::Cast(*proto) )->GetPrototype();
            }
        }

        if(1)
        {
            v8::Handle<v8::Object> so = cw::FindHolder<N>( jobj, bound );
            DBGOUT << "FindHolder() == [" << convert::CastFromJS<std::string>( so ) << "]\n";
        }

        CW::DestroyObject(jobj);
    }
    DBGOUT <<"Binding done.\n";
    return;
}
#undef DBGOUT


static v8::Handle<v8::Value> PosixFILE_plugin_init( v8::Handle<v8::Object> dest )
{
    v8::juice::cw::Installer<PosixFILE>::SetupBindings( dest );
    return dest;
}

V8_JUICE_PLUGIN_STATIC_INIT(PosixFILE_plugin_init);
