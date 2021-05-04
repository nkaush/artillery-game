# Artillery

In this game, 2 or more players take turns attempting to hit the other player(s) 
with a tank shell. The objective of the game is to be the last tank standing. 
Players must perfect their aim since tank shells are heavy and are heavily
influenced by gravity. Players must also account for the hilly terrain and may 
need to clear portions of terrain away to get a better shot.

Players may navigate their tank anywhere on the terrain and shoot. Players may
also be moved when a tank shell from an enemy clears terrain below them. Another 
caveat of this game is that tank shells not only take hit points away from 
players, but also destroy pieces of terrain in the vicinity of the blast impact.

## Demo

In this demo, you can see the functionality of aiming with your mouse. The game
provides a laser that points in the direction of the barrel. When a user presses
the SPACE bar, the currently active tank shoots a bullet in the direction the mouse
is pointing at. If the bullet hits a tank, that tank loses an amount of hitpoints 
that is proportional to the magnitude of the bullet's velocity. If the bullet hits
the ground, some terrain is blown up in a crater. The crater's radius is also 
proportional to the magnitude of the bullet's velocity. 

![A demo of the game.](docs/game-demo.gif)

Players also have the option to use aim assistance. Aim assistance predicts the 
parabolic path of the bullet, if fired at any instant. The menu displayed when the
game is paused allows users to configure aim assistance for each of the active players.

![A demo of the aim assistance.](docs/aim-assist.gif)

## Building and Running

To run the game, you must first install cmake. If you have homebrew, you can do
so by simply running `brew install cmake` from a command line. Alternatively,
you can [follow these instructions to install cmake](https://cmake.org/install/).

You must install Cinder for this game. You can find 
[instructions to do so here](https://libcinder.org/download). 
Next, you must clone this repository in a subdirectory of the Cinder directory 
named `my-projects`. 

Then, navigate to the project root directory and create an empty directory, 
ideally named `build` (any name will suffice). I will refer to this directory 
as `<build-dir>`. If you have opened the project in CLion, you will not need to 
do this. CLion will have already created a build directory named 
`cmake-build-debug`. Next, run the following command in a command line: 
`cmake --build <path-to-project-root>/<build-dir> --target artillery-main -- -j 3`.

Next, navigate to the build output directory. If you are on a Mac, this will be 
`<build-dir>/Debug/artillery-main/artillery-main.app/Contents/MacOS/`. Now, 
simply run the executable named `artillery-main`! It will be located in the 
build output directory you found above.

