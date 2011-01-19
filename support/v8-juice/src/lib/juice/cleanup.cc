#include <v8/juice/cleanup.h>

#include <map>

namespace v8 { namespace juice { namespace cleanup {

    typedef std::pair<void *, Destructor> GCEntry;
    typedef std::map<void const *,GCEntry> GCMap;

    static GCMap & gcList()
    {
	static GCMap bob;
	return bob;
    }

    /**
       A sentry object to call Cleanup() during the static destruction
       phase. This may be called after v8 has already been wiped out.
       We can only hope that gcList()'s object is still valid at this
       point, too.
    */
    // nonono. too risky vis-a-vis post-main() destruction order
    // of shared containers and such.
    // static CleanupSentry cleanupSentry = CleanupSentry();

    CleanupSentry::~CleanupSentry()
    {
	Cleanup();
    }
    CleanupSentry::CleanupSentry()
    {
    }

    void AddToCleanup( void * obj, Destructor dtor )
    {
	gcList().insert( std::make_pair( obj, std::make_pair(obj,dtor) ) );
    }

    void RemoveFromCleanup( void const * obj )
    {
	gcList().erase(obj);
    }

    void Cleanup()
    {
	GCMap cp;
	cp.swap( gcList() );
	GCMap::iterator it = cp.begin();
	GCMap::iterator ed = cp.end();
	for( ; it != ed; ++it )
	{
	    Destructor d = it->second.second;
	    void * v = it->second.first;
	    if(0 != d) d(v);
	}
    }

}}}
