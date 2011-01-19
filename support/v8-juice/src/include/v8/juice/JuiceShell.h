#if !defined(CODE_GOOGLE_COM_V8_JUICE_JUICESHELL_H_INCLUDED)
#define CODE_GOOGLE_COM_V8_JUICE_JUICESHELL_H_INCLUDED 1

#include <v8/juice/juice.h>

namespace v8 {
namespace juice {

    namespace Detail
    {
        /** Internal impl details for JuiceShell. */
        class JuiceShellImpl;
    }
    /**
       JuiceShell is a very basic wrapper to simplify the
       initialization of the v8 environment at application startup. It
       is used like:

       @code
       int main(int argc, char * argv[])
       {
           v8::V8::SetFlagsFromCommandLine(&argc,argv,false);
           v8::HandleScope handle_scope;
           // OPTIONAL: v8::juice::cleanup::CleanupSentry cleaner;
           v8::juice::JuiceShell shell;
           shell.ProcessMainArgv(argc,argv,1);
           // OPTIONAL: shell.SetupJuiceEnvironment();
           ... use v8 ...
       }
       @endcode

       Not that v8::V8::SetFlagsFromCommandLine(), if used, should come before
       the JuiceShell object and that a HandleScope should be created before the
       JuiceShell is created. The HandleScope is not created as part of the shell
       because the GC/ownership of handles generated from nested instances is not
       clear in this context.

       These objects should not be created on the heap, as this can
       theoretically play havok with handle scoping/lifetime rules.

       Warning: v8::V8::SetFlagsFromCommandLine(), if used, should be called before
       v8 is set up, but it may change the argument list. e.g. it strips out
       all args at or after "--". Thus it cannot be used directly with this
       class unless the arguments vector is first copied (e.g. into a vector<char*>)
       for use with this class or SetFlagsFromCommandLine().

       
       TODOs:

       - Functions for running arbitrary script code or executing
       scripts from files.

       - An input loop mechanism, with a callback for fetching input from
       the user (e.g. for implementing an interactive shell).
    */
    class JuiceShell
    {
    private:
        Detail::JuiceShellImpl * impl;
    public:
        /**
           A callback function signature for reporing JS-side
           exception messages to the native world.
        */
        typedef void (*ErrorMessageReporter)( char const * msg );

        /**
           LineFetcher is an interface for reading JS input
           interactively from the user, for use in an input loop.
           
           Reads a line of input from the user and stores it in dest.
           If it sets breakOut to true then the caller should stop
           accepting input. e.g. this should be set when Ctrl-D is
           tapped on most terminals. It should assume that dest is
           initially empty.
        */
        typedef void (*LineFetcher)( std::string & dest, bool & breakOut );


        /**
           Initialize a v8 context and global object belonging to this object.

           If globalObjectName is not null and not empty then the global object
           is given a refernce to itself using the given name, such that client
           JS code can then refer to it.
        */
        explicit JuiceShell( char const * globalObjectName = 0 );
        /**
           Takes this object's v8 resources out of scope, allowing v8
           to free them (when (or whether or not) it will do so is
           another question entirely).
        */
        ~JuiceShell();

        /** Binds the given function to the global object. */
        void AddGlobalFunc( char const * name, v8::Handle<v8::Function> const & f );
        
        /** Binds the given function to the global object. */
        void AddGlobalFunc( char const * name, v8::Handle<v8::FunctionTemplate> const & f );
        
        /** Binds the given function to the global object. */
        void AddGlobalFunc( char const * name, v8::InvocationCallback f );
        
        /** This object's global object. Owned by this object. */
        v8::Handle<v8::Object> Global();
        
        /** This object's context. Owned by this object. */
        v8::Handle<v8::Context> Context();

        /**
           Intended to be called from main() and passed the argc/argv
           which are passed to main. offset is the number of arguments
           to skip, and defaults to one to skip the argv[0] argument,
           which is conventionally the application name.

           It skips all arguments up to "--". For each argument after
           "--", it adds the argument to a list. At the end of the
           list, the global object is assigned a property named
           "arguments" which contains that list.

           This function does no interpretation of the arguments.
        */
        void ProcessMainArgv( int argc, char const * const * argv, unsigned short offset = 1 );

        /**
           Sets up a collection of v8-juice-pseodostandard properties
           and functions.

           The following functions are added to the global object:

           - include() (v8::juice::IncludeScript())
           - loadPlugin() (v8::juice::plugin::LoadPlugin())
           - sprintf() (v8::juice::sprintf())
           - sleep() (v8::juice::sleep())
           - mssleep() (v8::juice::mssleep())
           - usleep() (v8::juice::usleep())
           - wait() (v8::juice::wait())
           - mswait() (v8::juice::mswait())
           - uwait() (v8::juice::uwait())
           - setTimeout() (v8::juice::setTimeout())
           - setInterval() (v8::juice::setInterval())
           - clearTimeout() (v8::juice::clearTimeout())
           - clearInterval() (v8::juice::clearInterval())
           - print() (see PrintToCout())

           As of version 20100407:

           - spawnTimeoutThread()
           - spawnIntervalThread()
           - clearTimeoutThread()
           - clearIntervalThread()
           
           Those functions use the setTimeout() (and friends)
           implementations described in this documentation, and have
           the same interfaces as their similarly-named counterparts
           (without "Thread" suffix). The other (standard-named)
           functions will eventually be replaced by another
           implementation which behaves identical to browser-side
           implementations (the current one works a bit differently,
           due to threading details). When the standard-named
           implementations are swapped, most clients won't notice the
           difference (only those who try (really hard) to use them
           for concurrency will have to switch).

           The following classes are added to the global object:

           - PathFinder (see v8::juice::SetupPathFinderClass()).

           The following non-function properties are added to the
           global object:

           - 'v8JuiceVersion' = v8_juice_LIBRARY_VERSION (from
           juice-config.h). Added in v. 20100407.
        */
        void SetupJuiceEnvironment();

        /**
           Sets the error reporter function used by
           ExecuteString(). Passing 0 will disable exception
           reporting. The default reporter sends its output to
           std::cerr.
        */
        void SetExecuteErrorReporter( ErrorMessageReporter );
        /**
           Outputs an exception message using the current
           error reporter function.

           If try_catch or the current error reporter are
           null then nothing is done.
           
           @see SetExecuteErrorReporter().
        */
        void ReportException(v8::TryCatch* try_catch);

        /**
           Executes the given source string in the current
           context.

           If resultGoesTo is not null and the result is neither an
           error nor undefined, then the result is converted to a
           string and send to that stream.

           If reportExceptions is not null and the script throws an exception
           then that TryCatch object is used to build an error string, which
           is passed to this object's error reporter function. The default sends
           the output to std::cerr.

           Returns true if execution of the script generates no JS
           errors, else false.
        */
        bool ExecuteString(v8::Handle<v8::String> const & source,
                           v8::Handle<v8::Value> name,
                           v8::TryCatch * reportExceptions = 0,
                           std::ostream * resultGoesTo = 0 );

        /**
           Convenience form of ExecuteString(source,"some default name", reportExceptions, 0).
        */
        bool ExecuteString(v8::Handle<v8::String> source, v8::TryCatch * reportExceptions = 0 );

        /**
           Convenience overload taking input from native strings.
        */
        bool ExecuteString(std::string const & source,
                           std::string const & name,
                           v8::TryCatch * reportExceptions = 0,
                           std::ostream * resultGoesTo = 0
                           );

        /**
           Convenience form of ExecuteString(source,"some default name", 0, reportExceptions).
        */
        bool ExecuteString(std::string const & source, v8::TryCatch * reportExceptions = 0 );

        /**
           Similar to v8::juice::IncludeScript(), except for:

           Due to limitations in v8's native API for
           handling-then-propagating JS exceptions, this function
           cannot use a private TryCatch object to intercept error
           messages for reporting. So... if the reportExceptions
           argument is non-null, and the inclusion of the script
           generated an exception, the error will be reported via this
           object's current error reporter. If reportExceptions is
           null then exception reporting will be surpressed.

           Returns the same as v8::juice::IncludeScript(), which is
           the result of the final expression in the included script.
           It will (theoretically) be IsEmpty() if an exception is
           being propagated.
        */
        v8::Handle<v8::Value> Include( char const * source,
                                      bool useSearchPath = true,
                                      v8::TryCatch * reportExceptions = 0
                                      );

        
        /**
           Runs an interactive shell in a loop. It runs until the
           second argument passed to the input callback is set to true
           by the callback. Each line of input is passed to
           ExecuteString(), and the resultsTo and reportExceptions
           arguments are passed to that function.
        */
        void InputLoop( LineFetcher input,
                        v8::TryCatch * reportExceptions = 0,
                        std::ostream * resultGoesTo = 0 );
        /**
           A LineFetcher() implementation which simply reads a single
           line from stdin and assigns the result (minus the newline
           character) to dest. It sets breakOut to true at EOF
           (normally when Ctrl-D is pressed at the start of input on
           the console).

           This implementation prints a prompt to std::cout before
           reading input from std::cin.
        */
        static void StdinLineFetcher( std::string & dest, bool & breakOut );

        /**
           An v8::InvocationCallback implementation which implements a
           JS-conventional print() routine, sending its output to
           std::cout.
        */
        static Handle<Value> PrintToCout( Arguments const & argv );

        /**
           Identical to PrintToCout(), but sends its output to
           std::cerr instead.
        */
        static Handle<Value> PrintToCerr( Arguments const & argv );

        
    private:
        //!Copying is disabled.
        JuiceShell & operator=(JuiceShell const &);
        //!Copying is disabled.
        JuiceShell( JuiceShell const & );
    };
    

}} // namespaces

#endif /* CODE_GOOGLE_COM_V8_JUICE_JUICESHELL_H_INCLUDED */

