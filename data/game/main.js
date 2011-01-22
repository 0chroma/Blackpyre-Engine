for(var i=0; i<360; i+=45){
    print("Making entity at angle "+i);
    var f = new Entity(300, 200, 100, 100, i, "bullet.png");
    f.onUpdate = function(){
        var tss = this.timeSinceSpawn();
        var time = tss*2;
        while(time > 6000){
            time -= 6000;
        }
        this.angle = (tss/5)+f.initialAngle;
        this.posX = this.initialPosX + (time*Math.sin((this.initialAngle+(time/10))*(3.14/180))/17);
        this.posY = this.initialPosY + (time*Math.cos((this.initialAngle+(time/10))*(3.14/180))/17);
    };
    if(i==0){
        setTimeout(function(){ f.hide(); }, 2000);
        setTimeout(function(){ f.show(); }, 4000);
    }
}
