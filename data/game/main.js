var size = { x: 640, y: 480 }; //Blackpyre defines the screen to be 640x480, but it scales any sprites you specify if the screen is of higher resolution.
var center = { x: (size.x-100)/2, y: (size.y-100)/2 }; // in this example all our sprites will be 100x100, thus the - 100

var boss = new Entity(center.x, center.y, 100, 100, 0, "testTexture.png");

boss.onUpdate = function(){};

function onKeyDown(char, key){
    print((char ? "char "+char : "key "+key) + " pressed!");
    if(char == 27){
        quit(); //quit on escape
    }
    if(key == 102){
        boss.posX = boss.posX+1;
    }
    if(key == 100){
        boss.posX = boss.posX-1;
    }
    if(key == 103){
        boss.posY = boss.posY+1;
    }
    if(key == 101){
        boss.posY = boss.posY-1;
    }
}

function onKeyUp(char, key){
    print((char ? "char "+char : "key "+key) + " released!");
    print("x:"+boss.posX+" y:"+boss.posY);
}

function drawBullet(){
    var bullet = new Entity(center.x, center.y, 100, 100, 0, "bullet.png"); //make a new bullet with those values for posX, posY, sizeX, sizeY, angle, and sprite respectively
    bullet.onUpdate = function(){ //set the onUpdate function, which gets called between each frame
        var time = this.timeSinceSpawn();
        this.angle = (time/2)+this.initialAngle;
        this.posX = this.initialPosX + (time*Math.sin((this.initialAngle+(time/10))*(3.14/180))/17);
        this.posY = this.initialPosY + (time*Math.cos((this.initialAngle+(time/10))*(3.14/180))/17);
        //check to see if we're off the screen, if so, we destroy ourselves, which prevents us from rendering offscreen
        if(this.posX > size.x){ this.destroy(); }
    };
}

setInterval(drawBullet, 300); //call drawBullet every 300 milliseconds
