#ifndef CODE_GOOGLE_COM_V8_JUICE_TIME_H_INCLUDED
#define CODE_GOOGLE_COM_V8_JUICE_TIME_H_INCLUDED

#include <v8.h>

namespace v8 { namespace juice {

    /**
       A setTimeout() implementation which can be bound to v8.

       This implementation is currently identical to that
       of spawnTimeoutThread() except that this function requires
       2 arguments.
    
       This implementation works differently than browser-side
       implementations, because a timeout thread can interrupt (and,
       under the right circumstances, be interrupted by) the main
       thread (or any other thread, for that matter). A browser's
       implementation interrupts the main thread, runs the timeout
       handler to completion, and then continues the main thread
       (or another timeout thread).

       Since only one timeout handler can actually use v8 at a time
       (and locks the VM for that duration), in practice this
       difference shouldn't make _much_ of a difference, but there are
       cases which will behave desastrously (e.g. accessing native objects
       which have specific threading semantics, and those semantics
       might be violated (or cause a deadlock) by a timeout handler).

       The plan is to evenqtually replace this implementation with
       the one from:

       http://github.com/visionmedia/js-mock-timers/

       Which is more browser-compliant than the current
       implementation. On top of that implementation we can use a
       single (additional) thread to control the virtual flow of time
       which that implementation abstracts away (which is the feature
       which makes that impl portable to arbitrary JS engines).
    */
    v8::Handle<v8::Value> setTimeout(const v8::Arguments& argv );
    /**
       Identical to setTimeout() except that the client-supplied
       callback is executed in a loop, ending only when the
       client passes the return value from this function to
       clearInterval() (or setTimeout(), which is the same in this
       implementation).
    */
    v8::Handle<v8::Value> setInterval(const v8::Arguments& argv );

    /**
       A clearTimeout() implementation which can be bound to v8.

       Requires argv[0] to be a timer ID returned from setTimeout().
       If such a timer is found and can be cancelled (has not yet been
       fired) then true is returned, else false.
    */
    v8::Handle<v8::Value> clearTimeout(const v8::Arguments& argv );

    /**
       Identical to clearTimeout(), but intended for cancelling
       timeouts set via setInterval().
    */
    v8::Handle<v8::Value> clearInterval(const v8::Arguments& argv );

    /**
       JS usage: spawnTimeoutThread( Function|string, [int when=1] ),
       where 'when' is a number of milliseconds, after which the given
       function will be called or the given string will be
       eval()'d. Returns a unique timer ID (of an unspecified basic
       data type) which can be passed to clearTimeoutThread() before
       the interval expires in order to cancel the queued function.

       This routine is deceptively similar to the browser-standard
       setTimeout(). However...
       
       This starts up a separate thread (using an unspecified
       threading technique). That thread will briefly lock v8, then
       will unlock it to sleep for argv[1] milliseconds (or some very
       small amount of time if no time is specified). When it wakes
       up, it waits for the v8 lock and then runs the function defined
       by argv[0]. If clearTimeoutThread() has been called while the
       timer was sleeping, the function will not be executed.
       
       During the countdown this routine uses v8::Unlocker to unlock
       the v8 engine for other threads.

    */
    v8::Handle<v8::Value> spawnTimeoutThread(const v8::Arguments& argv );
    /**
       Identical to spawnTimeoutThread() except that:

       1) the client-supplied callback is executed in a loop, ending
       only when the client passes the return value from this function
       to clearIntervalThread() (or clearTimeoutThread(), which is
       actually the same function).

       2) It requires a second parameter.
    */
    v8::Handle<v8::Value> spawnIntervalThread(const v8::Arguments& argv );
    /**
       Unbinds (stops future execution of) a timer thread.

       Requires argv[0] to be a timer ID returned from
       spawnTimeoutThread() or spawnTimeoutInterval(). If such a timer
       is found and can be cancelled (has not yet been fired) then
       true is returned, else false.
    */
    v8::Handle<v8::Value> clearTimeoutThread(const v8::Arguments& argv );
    /**
       Identical to clearTimeoutThread().
    */
    v8::Handle<v8::Value> clearIntervalThread(const v8::Arguments& argv );

    
    /**
       A sleep() implementation which can be bound to v8.
    
       JS usage: sleep(seconds)

       Behaves identically to the POSIX-standard sleep(), but returns
       -1 if argv[0] is not a positive integer.

       This routine uses v8::Unlocker to unlock the v8 engine for
       other threads.
    */
    v8::Handle<v8::Value> sleep(const v8::Arguments & argv);
    /**
       Like sleep(), but naps for the given number of milliseconds
       (thousandths of a second).
       
       JS Usage: msleep( milliseconds )
    */
    v8::Handle<v8::Value> mssleep(const v8::Arguments & argv);
    /**
       Like sleep(), but naps for the given number of microseconds
       (millionths of a second).
    
       JS Usage: usleep( nanoseconds )

       but be aware that you won't get really high resolution via JS
       when sleeping for very small intervals, due to the overhead involved
       in passing around JS params and locking/unlocking the engine.
    */
    v8::Handle<v8::Value> usleep(const v8::Arguments & argv);

    /**
       Identical to sleep(), but it does NOT unlock v8 while it's
       sleeping. Thus other threads cannot run while it is running.
    */
    v8::Handle<v8::Value> wait(const v8::Arguments & argv);
    /**
       Identical to mssleep(), but it does NOT unlock v8 while it's
       sleeping. Thus other threads cannot run while it is running.
    */
    v8::Handle<v8::Value> mswait(const v8::Arguments & argv);
    /**
       Identical to usleep(), but it does NOT unlock v8 while it's
       sleeping. Thus other threads cannot run while it is running.
    */
    v8::Handle<v8::Value> uwait(const v8::Arguments & argv);

    
}} // namespace

#endif // CODE_GOOGLE_COM_V8_JUICE_TIME_H_INCLUDED
