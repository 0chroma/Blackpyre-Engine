#ifndef WANDERINGHORSE_NET_GOOGLE_V8_CLEANUP_H_INCLUDED_
#define WANDERINGHORSE_NET_GOOGLE_V8_CLEANUP_H_INCLUDED_ 1

namespace v8 { namespace juice {
/**
   "Supplemental", client-side garbage collection routines, to work
   around certain deficiencies in v8's GC (namely that it's never
   guaranteed to be called by the time the engine shuts down, and
   there's no way to force it to be called).
*/
namespace cleanup {

    /**
       Typedef for generic destructor functions. They are semantically
       compatible with free(), though whether or not they actually
       deallocate any memory is an internal implementation detail
       (e.g. they may use an object pool).
    */
    typedef void (*Destructor)( void * obj );

#if ! defined(DOXYGEN)
    /**
       Internal implementation details.
    */
    namespace Detail
    {
	/**
	   Helper to generate destructor functions halfway type-safely.
	*/
	template <typename T>
	struct DestructorGen
	{
	    static void dtor( void * obj )
	    {
		T * t = obj ? static_cast<T*>( obj ) : 0;
		if( t )
		{
		    delete t;
		}
	    }
	};
    }
#endif // !DOXYGEN

    /**
       A sentry for cleaning up any mess left by v8's innefectual
       garbage collector.

       Client apps can create one of these in a scope right above the
       scope in which their main (first) JS Context lives. When this
       object goes out of scope, all objects registered via
       AddToCleanup() will be destroyed. The idea is that the context
       is allowed to go out of scope, and only then do we try to
       clean up. This allows us to go through the normal v8 channels
       up until the last dying moments of the context, and if the
       context isn't cleaned up, we can take over where it left off.

       It is never a good idea to have more than one of these active
       at any time, as that will cause unwanted, premature deletions.
       Only use one per application (not per JS context!). This class
       does not enforce that limit because there might be unusual
       cases where we'll want more than one.
    */
    class CleanupSentry
    {
    public:
	/** Does nothing. */
	CleanupSentry();
	/**
	   Calls Cleanup()
	*/
	~CleanupSentry();
    };

    /**
       Adds the given object to "cleanup list", such that
       Cleanup() will destroy obj by calling dtor(obj).

       Normally this should be called from a wrapped class'
       constructor, and RemoveFromCleanup() would be called either
       it's dtor or in its related weak pointer callback (where
       exactly depends on how the code is structured).
    */
    void AddToCleanup( void * obj, Destructor dtor );

    /**
       Convenience overload which adds obj to the cleanup list (see
       the 2-arg overload of this function) using a cleanup function
       which simply calls (delete obj).
    */
    template <typename T>
    void AddToCleanup( T * obj )
    {
	AddToCleanup( obj, Detail::DestructorGen<T>::dtor );
    }

    /**
       Removes the given object from the cleanup list,
       so Cleanup() will not destroy it.
    */
    void RemoveFromCleanup( void const * obj );

    /**
       Destroys all objects which have been added by AddToCleanup()
       and clears the internal cleanup list.
    */
    void Cleanup();

}}} // namespaces

#endif /* WANDERINGHORSE_NET_GOOGLE_V8_CLEANUP_H_INCLUDED_ */
