

function tmout2()
{
    print("tmout2()!");
}
function tmout()
{
    print("tmout()!");
    setTimeout(tmout2,311);
}


function doTest()
{
    var loops = 6;
    var waitsec = 1;
    var tm = 233;
    for( var i = loops; i > 0; --i )
    {
        setTimeout(tmout,tm);
        setTimeout("print('timeout from eval');",tm*2);
        setTimeout(tmout,tm/2);
        print("Launcher sleeping...");
        mssleep(500);
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
