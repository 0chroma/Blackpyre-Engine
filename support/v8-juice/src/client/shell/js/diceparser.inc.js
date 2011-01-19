
/**
   Rolls dice results using conventional dice notation. desc
   must be a string describing the dice. Examples:

   "3d6", "10d3 + (1d4+3)", "100d7 * 34d6 + 3 - (1d97)"

   In principal, any JS code is legal in the string: the XdY references
   are parsed out, replaced with die roll results, and then the whole
   expression is eval()'d to produce the final result.

   If desc is malformed, the resulting eval() might throw an exception
   or (depending on the malformedness) may simply return an incorrect
   result.

   Special dice types supported by this function:

   * Fudge dice: (equivalent to 1d3-2)

   "dF" or "#dF" (where '#' is a number) are treated as Fudge dice, defaulting to
   four dice if no count is given.


   * dHL (High/Low) dice:

   "dHL" or "d#HL" (where '#' is a die face count, defaulting to 6)
   will roll two '#'-sided dice, subtracting the second from the
   first. Used by the Rob's Dungeon Game engine. e.g. dHL is equivalent
   to (1d6-1d6) and d10HL is equivalent to (1d10-1d10).

*/
function rollDice( desc )
{
    var ar;
    // Replace d(\d+)HL with (1dD - 1dD), for Rob's Dungeon Game:
    var rx = /(\d+)?d(\d+)?HL/g;
    while( (ar = rx.exec(desc) ) )
    {
        if( ar[1] )
        {
            throw new Error("dHL dice specification may not have a number prefix (they are always 2 dice).");
        }
        var D = ar[2] ? ar[2] : 6;
        var exp = '(1d'+D+'-1d'+D+')';
        //print("Replacing HL: [",D,"] with [",exp,"]");
        desc = desc.replace( ar[0], exp );
    }
    //print('desc =',desc);

    // Replace (\d+)?dF with Fudge dice...
    var rx = /(\d+)?dF/g;
    while( (ar = rx.exec(desc) ) )
    {
        var n = ar[1] ? ar[1] : 4;
        var li = [];
        for( var i = 0; i < n; ++i )
        {
            li.push( '(1d3-2)' );
        }
        var exp = '('+li.join('+')+')';
        //print("Replacing dF: [",ar[0],"] with [",exp,"]");
        desc = desc.replace( ar[0], exp );
    }
    //print('desc =',desc);


    rx = /-(\d)/g;
    /**
       Kludge to replace '-#' (which JS sees as a unary minus)
       with '- #', to avoid an incorrect value later on...
    */
    while( (ar = rx.exec(desc) ) )
    {
        desc = desc.replace(ar[0], '- '+ar[1]);
    }


    /**
       Internal implementation of dice roller. n=number of dice, d=sides of dice.
       e.g. doRoll(3,6) == results of 3d6
    */
    function doRoll(n,d)
    {
        var res = 0;
        for( var i = 0; i < +n; ++i ) {
            res += Math.floor( (Math.random() * 1000 % +d) ) + 1;
        }
        return res;
    }

    // Replace (#)?d# with results of dice...
    rx = /(\d+)?d(\d+)/g;
    while( (ar = rx.exec(desc)) )
    {
        var r = doRoll(ar[1],ar[2]);
        desc = desc.replace(ar[0],r);
        //print('desc =',desc);
    }

    // Let JS do the hard part:
    return eval( desc );
}


if(1) // test routine...
{
    var ar  = [];
    var n = 20;
    //var d = (1+i)+'d6';
    //var d = 'd'+(1+i)+'HL';
    var d = 'dHL';
    //var d = '1dF';
    print('Rolling',n,'dice:',d);
    for( var i = 0; i < n; ++i )
    {
        //ar.push( rollDice.doRoll(1,6) );
        //ar[d+'#'+i] = rollDice( d );
        ar.push( rollDice(d) );
    }
    var t = 0;
    for( var k in ar )
    {
        //if( n <= 20 ) print(k,'=',ar[k]);
        t += (+ar[k]);
    }
    if( n <= 20 ) print('Rolls: ',ar.join(', '));
    print("Total:",t,'\tAverage of',n,'rolls:',(t/n));
}

