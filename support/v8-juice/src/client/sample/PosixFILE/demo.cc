#if defined(NDEBUG)
#undef NDEBUG
#endif
#include <cassert>
/************************************************************************
Author: Stephan Beal (http://wanderinghorse.net/home/stephan)

License: Public Domain
************************************************************************/

#include <v8.h>
#include <v8/juice/JuiceShell.h>


#include "PosixFILE.cpp"
int main(int argc, char * argv[])
{
    using namespace ::v8::juice;
    if( 2 != argc )
    {
        std::cerr << "Usage:\n\t"
                  << argv[0] << " filename.js\n";
        return 1;
    }
    v8::Locker threadlockerkludge; // See http://code.google.com/p/v8/issues/detail?id=471
    v8::HandleScope handle_scope;
    try
    {
        v8::juice::JuiceShell shell("v8juice");
        shell.SetupJuiceEnvironment();
        v8::juice::cw::Installer<PosixFILE>::SetupBindings( shell.Global() );
        char const * fname = argv[1];
            v8::Locker tlocker;
            v8::TryCatch jtry;
            shell.Include( fname, false, &jtry );
            if( jtry.HasCaught() )
            {
                std::cerr << "Exception while including ["<<fname<<"]: "
                          << convert::JSToStdString(jtry.Exception())
                          <<'\n';
                return 1;
            }
    }
    catch(std::exception const &ex)
    {
        CERR << "CAUGHT NATIVE EXCEPTION:\n"<<ex.what()<<'\n';
        return 66;
    }
    catch(...)
    {
        CERR << "CAUGHT UNKNOWN EXCEPTION!\n";
        return 66;
    }

    return 0;
}
