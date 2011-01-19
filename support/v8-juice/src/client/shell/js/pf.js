
function dumpPF(p,list)
{
    if( !(p instanceof PathFinder) ) throw new Error("p is-not-a PathFinder! Type="+(typeof p));
    var li = (list instanceof Array) ? list : ['fossil','who','ls','nope','emacs','gcc'];
    print('vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv');
    print("PathFinder:",p);
    print("\tPath =",p.pathArray);
    print("\tExtensions =",p.extensionsArray );
    for( k in li ) {
        var f = p.find(li[k]);
	print('\tfind("'+li[k]+'") = ['+f+'], isAccessible =',PathFinder.isAccessible(f),' baseName =',PathFinder.baseName(f));
    }
    print('getPathSeparator():',p.getPathSeparator(),'=== pathSeparator:',p.pathSeparator);
    print('getPathArray():',p.getPathArray(),'=== pathArray:',p.pathArray);
    print('getPathString():',p.getPathString()," ==== pathString:",p.pathString);
    print('getExtensionsString():',p.getExtensionsString()," ==== extensionsString:",p.extensionsString);
    print('getExtensionsArray():',p.getExtensionsArray()," ==== extensionsArray:",p.extensionsArray);
    print('dirSeparator ==',p.dirSeparator);
    print('PathFinder.isAccessible("/etc/hosts") ==',PathFinder.isAccessible("/etc/hosts"));
    print('^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^');

}
function tryOne()
{
    var p = new PathFinder();
    p.pathString = "/hi/there:/yo/there";
    print('getPathString():',p.getPathString()," ==== pathString:",p.pathString);
    p.pathString = "/usr/bin:/bin";
    p.pathArray = ["/home/stephan/bin","/usr/bin","/bin"];
    p.extensionsString = ".hs:.lp";
    p.extensionsArray = ['.sh','.pl','.bash'];
    dumpPF(p);
}


tryOne();
print('PathFinder.shared =',PathFinder.shared);
dumpPF(PathFinder.shared.plugins,['v8-juice-whio','v8-juice-sqlite3']);
var inc = PathFinder.shared.include;
var ar = inc.getPathArray();
ar.push('js');
inc.setPathArray(ar);
dumpPF(PathFinder.shared.include,['pf']);
//dumpPF(PathFinder.shared.include);
//dumpPF(new Number(3)); // should throw
//PathFinder.shared.plugins.callMemFunc();
PathFinder.shared.include;
