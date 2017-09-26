# Wolf3d
Simple multi-threaded raycasting engine
 
Controls:
 - Moves : WASD
 - Strafe : QE
 - Run : SHIFT
 - Shot : (hold) SPACE
 - Recharge : R
 - Revive enemies : F
 - Change weapon : 1 2 3 4
 - Pause : ESCAPE

Menu :

 - With simple options, we have resume game when the game is paused.

![alt text](https://github.com/thchin/Wolf3d/blob/master/screenshots/Menu.png)

UI + Decor + Minimap:

 - For the UI, we have frame per second top left, minimap top right, life bottom left and ammunitions bottom right.
 - The Decor is simply fill with barrels, columns and lights.
 - Wall are textured, they are shadowed on y-side.
 - A fog is apply proportionnal to the distance of the wall.

![alt text](https://github.com/thchin/Wolf3d/blob/master/screenshots/Screenshot1.png)

Enemies :

 - NPC have multidirectionnal sprites for 8 directions views.
 - They have a simple A.I, if they looking a you they'll follow you until they are close enough to shot you.

![alt text](https://github.com/thchin/Wolf3d/blob/master/screenshots/Screenshot2.png)

Objects :

 - Objects can be weapons or life.

![alt text](https://github.com/thchin/Wolf3d/blob/master/screenshots/Screenshot3.png)

![alt text](https://github.com/thchin/Wolf3d/blob/master/screenshots/Screenshot4.png)

Death :

 - Can only paused the game on this screen.

![alt text](https://github.com/thchin/Wolf3d/blob/master/screenshots/Death.png)

Coded in C, with SDL 1.2, SDL_TTF, SDL_Image and pthread.

Check resources directory for the sprite sheet, all wolfenstein related sprite was took on [Sprite Resources](https://www.spriters-resource.com/)
