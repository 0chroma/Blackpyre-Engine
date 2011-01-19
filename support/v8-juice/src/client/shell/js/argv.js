/**
   Demonstration of accessing command-line arguments.

   The v8-juice-shell supports a "--" argument, and all
   arguments specified after that are passed on to each
   script it runs.
   The scripts have gobal arguments variable:

   arguments[0] == the shell name (FIXME: should be the script name).

   arguments[1..N] == the args passed after "--"

   Unlike the arguments array available in functions, this object
   is-a Array object.
*/
print("arguments.length ==",arguments.length);
for( var i = 0; i < arguments.length; ++i )
{
    print("\targv["+i+"] =",arguments[i]);
}
