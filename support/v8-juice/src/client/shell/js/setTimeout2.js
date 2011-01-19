

function tmout2(key)
{
    print("tmout2("+key+") activated!");
}
function tmout(key)
{
    print("tmout("+key+") activated!");
    setTimeout(function(){tmout2(key);},111);
}


function doTest()
{
    var loops = 6;
    var waitsec = 1;
    var tm = 233;
    for( var i = loops; i > 0; --i )
    {
        var x = i;;
        setTimeout(function(){tmout(''+x);},tm);
        setTimeout("print('timeout from eval');",tm*2);
        setTimeout(function(){tmout(''+x+'/2');},tm/2);
        print("Launcher sleeping breifly...");
        mssleep(100);
    }
    print("Launcher napping...");
    sleep(3);
    print("Launcher done.");
}

function intervalFunc()
{
    print("setInterval() callback.");
}
setInterval( intervalFunc, 1300 );
doTest();
print("done... should exit very shortly...");
