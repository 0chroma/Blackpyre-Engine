for(var i=0; i<360; i+=45){
    print("Making entity at angle "+i);
    var f = new Entity(300, 200, 100, 100, i, "bullet.png");
    f.onUpdate = function(){
        var tss = 2000; //f.timeSinceSpawn();
        var time = tss*2;
        while(time > 6000){
            time -= 6000;
        }
        //f.angle = (tss/5)+f.initialAngle;
        //f.posX = f.initialPosX + (time*Math.sin((f.initialAngle+(time/10))*(3.14/180))/17);
        //f.posY = f.initialPosY + (time*Math.cos((f.initialAngle+(time/10))*(3.14/180))/17);
        //f.posX++;
        //f.posY++;
        f.posX = 300;
        f.posY = 200;
    };
    if(i==0){
        setTimeout(function(){ f.hide(); }, 2000);
        setTimeout(function(){ f.show(); }, 4000);
    }
}
