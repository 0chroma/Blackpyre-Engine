// quick test of setTimeout(), clearTimeout(), and sleep()
var sleeptime = 5; // time to sleep while waiting for loops
var dms = 650; // delay between setTimeout() loops
var count = 0; // loops count
var reps = 20; // max number of loops to run.
function foofunc()
{
    if( ++count <= reps )
    {
        var id = setTimeout( foofunc, dms );
        print("Scheduling foofunc() in",dms," miliseconds. timer ID =",id);
        if(0 && (0 === (id%3)) )
        {
            print('cancel timer',id,' ==',clearTimeout(id));
        }
    }
    else
    {
        print("Loop limit reached. foofunc() not looping.");
    }
}

foofunc();
print("sleeping",sleeptime,"seconds:",new Date());
for( var x = sleeptime; x > 0; --x )
{
    sleep(1);
    print(x,"Zzzzzz....");
}
print("slept",sleeptime,"seconds:",new Date());
print("Calling foofunc() manually once:");
foofunc();

