#include <v8/juice/JuiceShell.h>
#include <v8/juice/convert.h>
#include <v8/juice/PathFinder-cw.h>

#include <v8/juice/sprintf.h>
#include <v8/juice/plugin.h>
#include <v8/juice/time.h>

#include <vector>
#include <string>
#include <iostream> // cout/cerr
#include <sstream>
#include <iterator>

#if 1
#ifndef CERR
#include <iostream>
#define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif
#endif

namespace v8 {
namespace juice {

    namespace Detail
    {
        static void DefaultErrorMessageReporter( char const * msg )
        {
            if( msg && *msg ) std::cerr << msg << '\n';
        }
        class JuiceShellImpl
        {
        public:
            //v8::HandleScope handle_scope;
            //v8::juice::cleanup::CleanupSentry cleaner;
            v8::Handle<v8::ObjectTemplate> globt;
            v8::Handle<v8::Context> context;
            v8::Context::Scope context_scope;
            v8::Handle<v8::Object> global;
            v8::juice::JuiceShell::ErrorMessageReporter reporter;
            JuiceShellImpl()
                :
                //handle_scope(),
                globt( v8::ObjectTemplate::New() ),
                context( v8::Context::New(NULL, globt) ),
                context_scope(context),
                global( context->Global() ),
                reporter( DefaultErrorMessageReporter )
            {
            }
            ~JuiceShellImpl()
            {
            }
        };
    }

    JuiceShell::JuiceShell( char const * globalObjectName )
        : impl( new Detail::JuiceShellImpl )
    {
        if( globalObjectName && *globalObjectName )
        {
            impl->global->Set( v8::String::New(globalObjectName), impl->global );
        }
    }
    JuiceShell::~JuiceShell()
    {
        delete this->impl;
    }

    void JuiceShell::ProcessMainArgv( int argc, char const * const * _argv, unsigned short offset )
    {
        if( (argc<1) || !_argv ) return;
        std::string const endofargs("--");
        typedef std::vector<std::string> ArgvList;
        ArgvList argv;
        int i = (int)offset;
        for( ; i < argc; ++i )
        {
            if( endofargs == _argv[i] )
            {
                ++i;
                break;
            }
        }
        for( ; i < argc; ++i )
        {
            argv.push_back( _argv[i] );
        }
        impl->global->Set( v8::String::New("arguments"), v8::juice::convert::CastToJS( argv ) );
    }

    void JuiceShell::AddGlobalFunc( char const * name, v8::Handle<v8::Function> const & f )
    {
        impl->global->Set( v8::String::New(name), f );
    }

    void JuiceShell::AddGlobalFunc( char const * name, v8::Handle<v8::FunctionTemplate> const & f )
    {
        this->AddGlobalFunc( name, f->GetFunction() );
    }

    void JuiceShell::AddGlobalFunc( char const * name, v8::InvocationCallback f )
    {
        this->AddGlobalFunc( name, FunctionTemplate::New(f) );
    }

    v8::Handle<v8::Object> JuiceShell::Global()
    {
        return impl->global;
    }
    v8::Handle<v8::Context> JuiceShell::Context()
    {
        return impl->context;
    }

    void JuiceShell::SetupJuiceEnvironment()
    {

#define BIND(K,V) this->AddGlobalFunc( K, V )
        BIND("include", v8::juice::IncludeScript );
        BIND("loadPlugin", v8::juice::plugin::LoadPlugin);
        BIND("sprintf", v8::juice::sprintf);
        BIND("sleep", v8::juice::sleep);
        BIND("mssleep", v8::juice::mssleep);
        BIND("usleep", v8::juice::usleep);
        BIND("wait", v8::juice::wait);
        BIND("mswait", v8::juice::mswait);
        BIND("uwait", v8::juice::uwait);
        BIND("setTimeout", v8::juice::setTimeout);
        BIND("setInterval", v8::juice::setInterval);
        BIND("clearTimeout", v8::juice::clearTimeout);
        BIND("clearInterval", v8::juice::clearInterval);
        BIND("spawnTimeoutThread", v8::juice::spawnTimeoutThread );
        BIND("spawnIntervalThread", v8::juice::spawnIntervalThread );
        BIND("clearTimeoutThread", v8::juice::clearTimeoutThread );
        BIND("clearIntervalThread", v8::juice::clearIntervalThread );
        BIND("print", PrintToCout);

        this->impl->global->Set( v8::String::New("v8JuiceVersion"),
                                 v8::Integer::New(v8_juice_LIBRARY_VERSION),
                                 v8::ReadOnly );
#undef BIND
        //v8::juice::SetupPathFinderClass( this->impl->global );
        v8::juice::cw::Installer<PathFinder>::SetupBindings( this->impl->global );
    }

    void JuiceShell::SetExecuteErrorReporter( ErrorMessageReporter r )
    {
        this->impl->reporter = r;
    }
    
    void JuiceShell::ReportException(v8::TryCatch* try_catch)
    {
        if( !try_catch || ! this->impl->reporter ) return;
        v8::HandleScope handle_scope;
        v8::String::Utf8Value exception(try_catch->Exception());
        //std::string const exception_stdstr = convert::CastFromJS<std::string>( exception
#define TOCSTR(X) (*X ? *X : "<exception string conversion failed!>")
        const char* exception_string = TOCSTR(exception);
        v8::Handle<v8::Message> message = try_catch->Message();
        std::ostringstream os;
        os << "JuiceShell::ReportException(): ";
        if (message.IsEmpty())
        {
            // V8 didn't provide any extra information about this error; just
            // print the exception.
            os << exception_string << '\n';
        }
        else
        {
            // Print (filename):(line number): (message).
            v8::String::Utf8Value filename(message->GetScriptResourceName());
            const char* filename_string = TOCSTR(filename);
            int linenum = message->GetLineNumber();
            os << filename_string << ':'
               << linenum << ": "
               << (exception_string ? exception_string : "") << '\n';
            // Print line of source code.
            v8::String::Utf8Value sourceline(message->GetSourceLine());
            const char* sourceline_string = TOCSTR(sourceline);
#undef TOCSTR
            os << sourceline_string << '\n';
            // Print wavy underline (GetUnderline is deprecated).
            int start = message->GetStartColumn();
            for (int i = 0; i < start; i++) {
                os << ' ';
            }
            int end = message->GetEndColumn();
            for (int i = start; i < end; i++) {
                os << '^';
            }
            os << '\n';
        }
        std::string const & str = os.str();
        this->impl->reporter( str.c_str() );
    }


    bool JuiceShell::ExecuteString(v8::Handle<v8::String> const & source,
                                   v8::Handle<v8::Value> name,
                                   v8::TryCatch * reportExceptions,
                                   std::ostream * out)
    {
        v8::HandleScope handle_scope;
        //v8::TryCatch try_catch;
        //try_catch.SetCaptureMessage(true);
        //try_catch.SetVerbose(true);

        v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
        if( reportExceptions && reportExceptions->HasCaught())//script.IsEmpty())
        {
            // Print errors that happened during compilation.
            if (reportExceptions)
                this->ReportException(reportExceptions);
            return false;
        }
        else
        {
            v8::Handle<v8::Value> result = script->Run();
            if( reportExceptions && reportExceptions->HasCaught())//(result.IsEmpty())
            {
                this->ReportException(reportExceptions);
                return false;
            }
            else
            {
                if (out && !result->IsUndefined())
                {
                    std::string str = convert::JSToStdString(result);
                    (*out) << str << '\n';
                }
                return true;
            }
        }
    }
    bool JuiceShell::ExecuteString(std::string const & source,
                                   std::string const & name,
                                   v8::TryCatch * reportExceptions,
                                   std::ostream * resultGoesTo )
    {
        v8::HandleScope scope;
        Local<v8::String> s( v8::String::New( source.c_str(), static_cast<int>(source.size()) ) );
        Local<v8::String> n( v8::String::New( name.c_str(), static_cast<int>(name.size()) ) );
        return this->ExecuteString( s, n, reportExceptions, resultGoesTo );
    }

    bool JuiceShell::ExecuteString(std::string const & source, v8::TryCatch * reportExceptions )
    {
        return this->ExecuteString(source,"JuiceShell::ExecuteString()", reportExceptions, 0);
    }

    bool JuiceShell::ExecuteString(v8::Handle<v8::String> source, v8::TryCatch * reportExceptions )
    {
        return this->ExecuteString(source,v8::String::New("JuiceShell::ExecuteString()"), reportExceptions, 0);
    }

    v8::Handle<v8::Value> JuiceShell::Include( char const * source,
                                              bool useSearchPath,
                                              v8::TryCatch * fence
                                              )
    {
#if 0
        return v8::juice::IncludeScript( source.c_str(), useSearchPath );
#else
        if( ! source || !*source )
        {
                return v8::ThrowException(v8::String::New("IncludeScript() requires a non-empty filename argument!"));
        }
        //v8::HandleScope hscope;
        v8::Handle<v8::Value> rc;
        rc = v8::juice::IncludeScript( source, useSearchPath );
        if( fence && fence->HasCaught()) //rc.IsEmpty() ) //
        {
            //exc = fence->Exception();
            this->ReportException( fence );
        }
        //return hscope.Close(rc);
        return rc;
#endif
    }
    
    void JuiceShell::StdinLineFetcher( std::string & dest, bool & breakOut )
    {
        breakOut = false;
        std::cout << "> ";
        std::cout.flush();
        std::ostringstream os;
        std::istream & is( std::cin );
        is >> std::noskipws;
        char x;
        size_t pos = 0;
        while(true)
        {
            is >> x;
            if( is.eof() )
            {
                breakOut = true;
                break;
            }
            if( ('\n' == x) || ('\r' == x) ) break;
            if( !(pos++) && !x )
            {
                breakOut = true;
                break;
            }
            os << x;
        }
        dest = os.str();
        return;
    }
    
    void JuiceShell::InputLoop( LineFetcher input,
                                v8::TryCatch * reportExceptions,
                                std::ostream * os )
    {
        std::string sbuf;
        bool dobreak = false;
        while( true )
        {
            sbuf.clear();
            input( sbuf, dobreak );
            if( dobreak )
            {
                break;
            }
            v8::HandleScope handle_scope;
            this->ExecuteString(sbuf, "(JuiceShell::InputLoop())", reportExceptions, os );
            if( reportExceptions ) reportExceptions->Reset(); // arguable!
        }
    }

    /**
       An v8::InvocationCallback implementation which implements a
       JS-conventional print() routine. If ToStdOut is true, the
       output goes to std::cout, otherwise it goes to std::cerr.
    */
    template <bool ToStdOut>
    static Handle<Value> PrintToStdOstream( Arguments const & argv )
    {
        bool first = true;
        std::ostream & os( ToStdOut ? std::cout : std::cerr );
        for (int i = 0; i < argv.Length(); i++)
        {
            v8::HandleScope handle_scope;
            if (first)
            {
                first = false;
            }
            else
            {
                os << ' ';
            }
            v8::String::Utf8Value str(argv[i]);
            const char* cstr = *str;
            if( cstr ) os << cstr;
        }
        os << '\n';
        os.flush();
        return v8::Undefined();
    }

    Handle<Value> JuiceShell::PrintToCout( Arguments const & argv )
    {
        return PrintToStdOstream<true>( argv );
    }
    Handle<Value> JuiceShell::PrintToCerr( Arguments const & argv )
    {
        return PrintToStdOstream<false>( argv );
    }

    
}} // namespaces
