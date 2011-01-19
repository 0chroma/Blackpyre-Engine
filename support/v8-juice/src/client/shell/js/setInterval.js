

function timestamp()
{
    var t =  (new Date()).getTime();
    var rc = t + ' (+'
        +( t - arguments.callee.prev )
        +'): '
        ;
    arguments.callee.prev = t;
    return rc;
}
timestamp.prev = (new Date()).getTime();
function doInterval()
{
    ++this.count;
    if(
       false
       //(this.count == this.id)
       && (this.count > this.id)
        )
    {
        clearInterval( this.id );
        print("de-intervaling #"+this.id);
    }
    print(timestamp(),"Interval #"+this.id,' running (timeout='+this.timeout+').');
}

function main()
{
    
    var timeout = 250;
    var counter = 0 ;
    var ids = {
    };
    var loops = 4;
    var i;
    var sleepTime = 600 * loops;
    var wait = 0;
    function bogo2()
    {
        var y = {count:0};
        function bogo()
        {
            doInterval.call( y );
        }
        y.timeout = 0+timeout;
        y.id = setInterval( bogo, y.timeout );
        print(timestamp(),'Starting interval #'+y.id,'in '+y.timeout+'ms');
        //wait = timeout / 3; mssleep( wait ); sleepTime += wait;
        sleepTime += y.timeout;
        timeout = timeout*2;
    }
    for( i = 0; i < loops; ++i )
    {
        bogo2();
    }
    sleepTime *= 2;
    print(timestamp(),'main() sleeping for',sleepTime+'ms...');
    mssleep
        (sleepTime)
        ;
    print('main() woke up.');
}

main();


