# RED LIGHT, GREEN LIGHT

## GAME INTRODUCTION
**RED LIGHT, GREEN LIGHT** is a game popularized by *Squid Game* - a South Korean television series. 
The primary logic of the game revolves around the concept that any players moving when the "red light" is called is shot dead on the spot. 
The game requires caution, careful calculation, and precise timing. I've enhanced it with different levels. 

Game demo video: [LINK](https://www.youtube.com/watch?v=WNsVoL7D0uU)


## 0. Download the game
Download the game (compressed into a .zip file) at the following link: [LINK](https://github.com/Ducdung005bn/Red-or-green/releases/tag/releases)

Extract the game into a folder and run game.exe to play.

## 1. Start the game
![](https://github.com/Ducdung005bn/Red-or-green/blob/master/Screenshot%202024-04-26%20011413.png?raw=true)

Click on the "Play" button to start playing the game. If you want to exit immediately, click on the "Exit" button.
After clicking on the "Play" button, the main menu will appear.

![](https://github.com/Ducdung005bn/Picture/blob/main/Screenshot%202024-04-26%20131019.png?raw=true)

+ In the top right-hand corner of the main menu appears the number of coins you have.
  
You can select options here (they will stand out if you move the mouse cursor to them). 

+ If you haven't got access to the game before, select "Instructions" to know how to play the game. Press the arrow keys on your keyboard to scroll up and down the page. 
+ Select "Shop" to enter the shop, where you can buy new clothes to upgrade your level.
+ Select "Start game" or "Last stand" to enter the play area. "Last stand" differs from "Start game" in the fact that if you win the last stand, you are recognized to completely crack this game (it is the last round). 

At the beginning, you have no coins and are at level 1. You need to earn coins and upgrade your level.

## 2. Upgrade your level
### a. There are 4 levels
At levels 1, 2 and 3, the goal is to reach the finish line before time's up without getting eliminated.

#### LEVEL 1
+ When starting playing, you stand on the starting line. 
+ Please press the arrow keys on your keyboard to move. 
+ As the giant doll sings showing her back to you, the light will be green, meaning you are allowed to run towards the finish line. 
+ When she stops singing, the light will turn red, so you will have to stop running. If you are caught moving, you will be shot dead on the spot by a group of masked guards in pink jumpsuits. 
+ Additionally, you are required to cross the finish line within a time limit. If time's up and you haven't reached the finish line, you'll still get shot. Therefore, pay attention to the "Time Remaining" written at the top of the screen.
+ If you reach the finish line before time's up without getting eliminated, the sooner you reach the finish line, the more coins you are given.

#### LEVEL 2
+ The primary logic of level 2 is basically the same as that of level 1.
+ Additionally, there is one character called "Follower". Its duty is to follow you (it can move only when the light is green). Watch out for the follower, because you'll also be shot if at the same position as it.

![](https://github.com/Ducdung005bn/Picture/blob/main/Screenshot%202024-04-26%20182557.png?raw=true) 

The follower is chasing the player.

#### LEVEL 3
+ The only difference between level 2 and level 3 is that there will be two followers instead of one.
+ You need to move extremely carefully to be able to cross the finish line. 

#### LEVEL 4
+ This is the last round, where you are disguised as the giant doll.
+ There are 15 automated players. They will try to reach the finish line without being caught moving. Of cource, they don't know when the light will turn red.
+ You're required to choose when to turn the red light (please press the space key). You just have only 3 times to turn it.
+ If any automated players reach the finish line before time's up without getting eliminated, you will lose. On the contrary, you will win.

![](https://github.com/Ducdung005bn/Picture/blob/main/Screenshot%202024-04-26%20183206.png?raw=true)

### b. Enter the shop to upgrade your level
|Clothes|Price|Level|
| --- | --- | --- |
|![](https://github.com/Ducdung005bn/Picture/blob/main/New%20folder/man.png?raw=true) | FREE | 1 |
|![](https://github.com/Ducdung005bn/Picture/blob/main/New%20folder/worker.png?raw=true)| 25 coins | 2 |
|![](https://github.com/Ducdung005bn/Picture/blob/main/New%20folder/businessman.png?raw=true) | 20 coins | 3 |
|![](https://github.com/Ducdung005bn/Picture/blob/main/New%20folder/doll.png?raw=true) | 15 coins | 4 |

At the beginning, you are at level 1. Earn coins to upgrade your level. 
+ The clothes that you have bought are marked with 'O'.
+ You have to upgrade your level  in sequence.
+ When you have enough money to upgrade to the next level, you are required to upgrade before continuing to play. 

![](https://github.com/Ducdung005bn/Picture/blob/main/Screenshot%202024-04-26%20183811.png?raw=true)

## 3. Earn more coins with the game of chance - SPIN THE WHEEL
After winning at levels 1, 2, or 3, on the screen appears:
  
  ![](https://github.com/Ducdung005bn/Picture/blob/main/New%20folder/Screenshot%202024-04-26%20190210.png?raw=true)

If you've earned at least one coin in this round, you can decide whether to participate in the game of chance or not.
  + If you don't want to participate, select "Return" to move to the main menu.
  + If you don't know the rules of the game, move the mouse cursor to "How?"
  + If you want to participate, just select "Yes"

![](https://github.com/Ducdung005bn/Picture/blob/main/SDL_app%202024-04-26%2020-15-41%20(1).gif)

To stop the wheel, press the space key on your keyboard. The needle will then randomly point to either "Green" or "Red".

If the needle points to "Green", your coins will double. You can also use these coins to play the game of chance again.

On the contrary, your coins in this round will be lost.

## 4. Prize
Start at level 1, earn more coins to upgrade to the next level. If you win the last stand, you are recognized to crack this game. The piggy bank will then be filled with a lot of money.

![](https://github.com/Ducdung005bn/Picture/blob/main/Screenshot%202024-04-26%20212842.png?raw=true)

## 5. The game's source code
+ Source.cpp: main function of the game.
+ Common_Function.cpp: including functions that are used commonly in this project such as LoadImage, ApplySurface, ...
+ BaseObject.cpp: related to the BaseObject class, which is inherited by some objects.
+ Text.cpp: including functions used to show text on the screen, such as SetText, SetColor, ...
+ MainObject.cpp: related to the MainObject class, receiving keyboard events (HandleInputAction) and moving the character (HandleMove), ... 
+ Follower.cpp: related to the Follower class, handling how followers move, checking collision with human, showing followers, ...
+ AutoPlayer.cpp: related to the AutoPlayer class, handling how automated players move, updating automated players' status, ...
+ Instructions.cpp: handling the display of instructions on the screen.
+ Light.cpp: including functions related to red light and green light, the display of "Time Remaining", displaying objects, ...
+ User_Interface.cpp: handling the display of main menu, shop, win notification, lose notification, ...
+ Wheel.cpp: showing and handling the game of chance - spin the wheel (using rotateSurface to rotate the image to form the wheel)



  





















 

