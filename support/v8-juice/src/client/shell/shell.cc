#if defined(NDEBUG)
#undef NDEBUG
#endif
#include <cassert>
// Copyright 2008 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
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
/************************************************************************
This code is based off of the shell.cc sample application in the v8
source tree. It has been mangled to become the default shell for the
v8-juice project.

Some changes from the original shell:

- Binds most of the v8-juice add-on functions by default.

- If the argv list contains "--", all arguments after that are ignored
by the shell but passed on to each script which it runs. Each script
gets a global arguments object, where arguments[0] is the name of the
shell (it SHOULD be the name of the script, but it's not), and arguments
1..N are those after the "--"

 ************************************************************************/

/**

BUG_NUMBER() is a marker which should be interpreted as:

http://code.google.com/p/v8-juice/issues/detail?id=N

*/
#define BUG_NUMBER(N)

#include <v8.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <iostream>

#ifndef CERR
#define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif
#ifndef COUT
#define COUT std::cout << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif

#include <v8/juice/juice.h>
#include <v8/juice/convert.h>
#include <v8/juice/bind.h>
#include <v8/juice/time.h>
#include <v8/juice/sprintf.h>
#include <v8/juice/plugin.h>
#include <v8/juice/PathFinder.h>
#include <v8/juice/cleanup.h>
#include <v8/juice/forwarding.h>
#include <v8/juice/WeakJSClassCreator.h>
#include <v8/juice/ToSource.h>
#include <v8/juice/JuiceShell.h>
#include <v8/juice/ClassBinder.h>

namespace bind = ::v8::juice::bind;

void RunShell(v8::juice::JuiceShell & shell, std::ostream * out );
v8::Handle<v8::Value> Quit(const v8::Arguments& args);
v8::Handle<v8::Value> Version(const v8::Arguments& args);
v8::Handle<v8::String> ReadFile(const char* name);

typedef v8::Handle<v8::ObjectTemplate> V8Object;
typedef v8::Local<v8::Object> V8LObject;
typedef v8::Handle<v8::Context> V8CxH;


using namespace v8;
using namespace ::v8::juice;


int my_tosource( V8CxH & cx )
{
    using namespace v8;
    using namespace v8::juice;
    using namespace v8::juice::convert;

    CERR << ToSource( 43 )
         << '\n' << ToSource( "He's one of us, isn't he?" )
         << '\n' << ToSource( "He said, \"hi!\"" )
         << '\n' << ToSource( "He said, \"she's not home!\"" )
         << '\n';

    typedef std::list<std::string> SL;
    SL li;
    li.push_back( "He's one of us, isn't he?" );
    li.push_back( "He said, \"hi!\"" );
    li.push_back( "He said, \"she's not home!\"" );
    CERR <<  ToSource(li) << '\n';
    std::list<SL> lili;
    lili.push_back(li);
    lili.push_back(li);
    lili.push_back(li);
    CERR << ToSource(lili) << '\n';

    CERR << ToSource( Local<String>( String::New("hi, world") ) ) << '\n';
    CERR << ToSource( Integer::New(17) ) << '\n';
    CERR << ToSource( Null() )  << '\n';
    CERR << ToSource( Undefined() )  << '\n';
    CERR << ToSource( Boolean::New(true) )  << '\n';
    CERR << ToSource( Boolean::New(false) )  << '\n';
    Local<Object> gl = v8::Context::GetCurrent()->Global();
    CERR << ToSource( gl )  << '\n';
    CERR << ToSource( gl->Get(String::New("print")) )  << '\n';
    CERR << ToSource( CastToJS( li ) ) << '\n';
    return 0;
}


int my_test( V8CxH & cx )
{
    using namespace v8::juice::convert;
    using namespace v8;


    v8::HandleScope handle_scope;
    V8LObject gl = cx->Global();
    COUT << "gl.MyVar = ["<<CastFromJS<std::string>( gl->Get( String::New("MyVar") ) )<<"]\n";
    Handle<Value> hv1 = CastToJS<int>( 43 );
    char const * a = 0;
    {
	String::AsciiValue asc( hv1 );
	COUT << "hv1.IsEmpty() ?= "<<hv1.IsEmpty()<<'\n';
	a = *asc;
	COUT << "hv1 : [" << (a ? a : "<IsEmpty()==true>") << "]\n";
    }
    int myInt = CastFromJS<int>( hv1 );
    COUT << "myInt = "<<myInt<<"\n";
    Handle<Value> hv2 = CastToJS( 42.24 );
    //Handle<Value> hv2 = CastToJS( std::cout );
    myInt = CastFromJS<int>( hv2 );
    double myDbl = CastFromJS<double>( hv2 );
    COUT << "myInt = "<<myInt<<", myDbl = " << myDbl<<"\n";
    {
	COUT << "JsToNative<...>(hv2): ["<<JSToStdString(hv2)<<"]\n";
    }
    Local<Value> lvE = Exception::Error( String::New("My error test") );
    COUT << "lvE = ["<<JSToStdString(lvE)<<"]\n";
    return 0;
}

struct bind_tester
{
    std::string str;
    bind_tester() : str("hi, world!")
    {}
};

int my_bind_test2( V8CxH & cx )
{
    using namespace v8::juice::convert;
    using namespace v8::juice::bind;
    using namespace v8;
    v8::HandleScope handle_scope;
    V8LObject gl = cx->Global();
    Local<Value> jv = gl->Get( String::New("MyNative") );
    bind_tester * n = GetBoundNative<bind_tester>( jv );
    if( ! n )
    {
	CERR << "ERROR: Could not fetch MyNative as an External!\n";
	return 1;
    }
    COUT << "MyNative = " << n << " == ["<<(n?n->str:"<NULL>")<<"]\n";
#if 0
    n = CastFromJS<bind_tester>( jv );
    COUT << "MyNative = " << n << " == ["<<(n?n->str:"<NULL>")<<"]\n";
#endif
    return 0;
}

int my_bind_test( V8CxH & cx )
{
    using namespace v8::juice::convert;
    using namespace v8::juice::bind;
    using namespace v8;
    v8::HandleScope handle_scope;
    bind_tester mynat;
    mynat.str = "hi, world?";
    Local<External> ex = External::New( &mynat );
    bool rc = BindNative( ex, &mynat );
    COUT << "bind key@"<<ex->Value() << " to @"<<&mynat<<", rc = " << rc << '\n';
    bind_tester * bs = GetBoundNative<bind_tester>( ex );
    COUT << "bound mynat = " << bs << " == ["<<(bs?bs->str:"<NULL>")<<"]\n";
    V8LObject gl = cx->Global();

//     Local<BoundNative> bn = BoundNative::New( &mynat );
//     COUT << "bn->Value<bind_tester>() == "<<bn->Value<bind_tester>()<<'\n';

    gl->Set( String::New("MyNative"), ex );
    my_bind_test2( cx );
    rc = UnbindNative( ex, &mynat );
    COUT << "unbind rc = " << rc << '\n';
    rc = UnbindNative( ex, &mynat );
    COUT << "unbind rc = " << rc << '\n';
    bs = GetBoundNative<bind_tester>( ex );
    assert( 0 == bs );
    COUT << "unbind bs = " << bs << " == ["<<(bs?bs->str:"<NULL>")<<"]\n";
    return 0;
}




v8::juice::JuiceShell * ShellInstance = 0; 
int main(int argc, char * argv[])
{
#define JSTR(X) v8::String::New(X)
    if(0)
    { /** fuck - SetFlagsFromCommandLine() changes argv such that the
          "--" arg and those following it are stripped!
       */
        typedef std::vector<char *> AV;
        AV vargv(static_cast<size_t>(argc), 0);
        int i;
        for( i = 0; i < argc; ++i )
        {
            vargv[(unsigned int)i] = argv[i];
        }
        v8::V8::SetFlagsFromCommandLine(&i, &vargv[0], true);
    }
    else
    {
        // or we could use the undocumented 3rd arg:
        //v8::V8::SetFlagsFromCommandLine(&argc, argv, false);
    }
    {
        v8::Locker lockerkludge; // work around http://code.google.com/p/v8/issues/detail?id=471
        v8::HandleScope handle_scope;
        v8::juice::cleanup::CleanupSentry cleaner;
        v8::juice::JuiceShell shell("v8juice");
        ShellInstance = &shell;
        shell.ProcessMainArgv(argc,argv,1);
        shell.SetupJuiceEnvironment();
#define FT v8::FunctionTemplate::New
#define BIND(K,V) shell.AddGlobalFunc( K, V )
        BIND("quit", Quit);
        BIND("version", Version);
#undef BIND
#undef FT
        v8::TryCatch jtry;
        bool run_shell = (argc == 1);
        std::string const endofargs("--");
        for (int i = 1; i < argc; i++) {
            /* v8 bug 471: http://code.google.com/p/v8/issues/detail?id=471
               
            If the following Locker is in the next scope up, newer
            v8 versions crash on exit.
            */
            v8::Locker tlocker;
            const char* str = argv[i];
            if( 0 == strcmp(str,"--print-cerr"))
            {
                shell.AddGlobalFunc( "print", v8::juice::JuiceShell::PrintToCerr );
                continue;
            }
            else if( endofargs == str )
            {
                break;
            }
            else if (strcmp(str, "--shell") == 0) {
                run_shell = true;
                continue;
            } else if (strcmp(str, "-f") == 0) {
                // Ignore any -f flags for compatibility with the other stand-
                // alone JavaScript engines.
                continue;
            } else if (strncmp(str, "--", 2) == 0) {
                printf("Warning: unknown flag %s.\nTry --help for options\n", str);
            } else if (strcmp(str, "-e") == 0 && i + 1 < argc) {
                // Execute argument given to -e option directly
                v8::HandleScope handle_scope;
                std::string source(argv[i + 1] ? argv[i + 1] : "");
                if (!shell.ExecuteString(source, "[-e script]", &jtry))
                {
                    return 1;
                }
                i++;
            } else {
                // Use all other arguments as names of files to load and run.
                v8::Handle<v8::Value> rc =
                    shell.Include( str, false, &jtry );
                if(jtry.HasCaught())//rc.IsEmpty())
                {
                    std::cerr << "Exception while including ["<<str<<"]: "
                              << convert::JSToStdString(jtry.Exception())
                              <<'\n';
                    return 1;
                }
            }
        }
        if (run_shell) RunShell( shell, &std::cout );
    }
    return 0;
#undef JSTR
}

// The callback that is invoked by v8 whenever the JavaScript 'quit'
// function is called.  Quits.
v8::Handle<v8::Value> Quit(const v8::Arguments& args) {
  // If not arguments are given args[0] will yield undefined which
  // converts to the integer value 0.
  int exit_code = args[0]->Int32Value();
  exit(exit_code);
  return v8::Undefined(); // won't happen
}


v8::Handle<v8::Value> Version(const v8::Arguments& args) {
  return v8::String::New(v8::V8::GetVersion());
}

// The read-eval-execute loop of the shell.
void RunShell( v8::juice::JuiceShell & shell, std::ostream * out )
{
    v8::TryCatch jtry;
    if( out ) (*out) << "V8 version "<< v8::V8::GetVersion() << '\n';
    shell.InputLoop( v8::juice::JuiceShell::StdinLineFetcher, &jtry, out );
    if( out ) (*out) << std::endl;
}

