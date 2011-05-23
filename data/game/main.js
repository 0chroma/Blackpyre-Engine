var size = { x: 640, y: 480 }; //Blackpyre defines the screen to be 640x480, but it scales any sprites you specify if the screen is of higher resolution.
var center = { x: (size.x-100)/2, y: (size.y-100)/2 }; // in this example all our sprites will be 100x100, thus the - 100

var boss = new Entity(center.x, center.y, 100, 100, 0, "testTexture.png");

var keyStates = {up: false, down: false, left: false, right: false, upDownFirst: "", leftRightFirst: ""};

boss.onUpdate = function(){
    if(keyStates.right && keyStates.leftRightFirst != "right"){
        this.posX += 2;
    }
    if(keyStates.left && keyStates.leftRightFirst != "left"){
        this.posX -= 2;
    }
    if(keyStates.up && keyStates.upDownFirst != "up"){
        this.posY += 2;
    }
    if(keyStates.down && keyStates.upDownFirst != "down"){
        this.posY -= 2;
    }
};

function onKeyDown(char, key){
    print((char ? "char "+char : "key "+key) + " pressed!");
    if(char == 27){
        quit(); //quit on escape
    }
    if(key == 102){
        keyStates.right = true;
        if(keyStates.left)
            keyStates.leftRightFirst = "left";
    }
    if(key == 100){
        keyStates.left = true;
        if(keyStates.right)
            keyStates.leftRightFirst = "right";
    }
    if(key == 103){
        keyStates.up = true;
        if(keyStates.down)
            keyStates.upDownFirst = "down";
    }
    if(key == 101){
        keyStates.down = true;
        if(keyStates.up)
            keyStates.upDownFirst = "up";
    }
}

function onKeyUp(char, key){
    print((char ? "char "+char : "key "+key) + " released!");
    if(key == 102){
        keyStates.right = false;
    }
    if(key == 100){
        keyStates.left = false;
    }
    if(key == 103){
        keyStates.up = false;
    }
    if(key == 101){
        keyStates.down = false;
    }

    if(key == 102 || key == 100)
        keyStates.leftRightFirst = false;
    if(key == 101 || key == 103)
        keyStates.upDownFirst = false;
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
