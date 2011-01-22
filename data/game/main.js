var f = new Entity(640/2, 480/2, 100, 100, 0, "bullet.png");

var center = { x: 640/2, y: 480/2 }; //Blackpyre defines the screen to be 640x480, but it scales any sprites you specify if the screen is of higher resolution.
var size = { x: 640, y: 480 };

function drawBullet(){
    var bullet = new Entity(center.x, center.y, 100, 100, 0, "bullet.png"); //make a new bullet with those values for posX, posY, sizeX, sizeY, angle, and sprite respectively
    bullet.onUpdate = function(){ //set the onUpdate function, which gets called between each frame
        var time = this.timeSinceSpawn();
        this.angle = (time/2)+f.initialAngle;
        this.posX = this.initialPosX + (time*Math.sin((this.initialAngle+(time/10))*(3.14/180))/17);
        this.posY = this.initialPosY + (time*Math.cos((this.initialAngle+(time/10))*(3.14/180))/17);
        //check to see if we're off the screen, if so, we destroy ourselves, which prevents us from rendering offscreen
        if(this.posX > size.x){ this.destroy(); }
    };

}

setInterval(drawBullet, 300); //call drawBullet every 300 milliseconds
