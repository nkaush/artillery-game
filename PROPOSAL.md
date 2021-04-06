# Idea: Artillery Game

## Introduction
___
In this game, 2 or more players take turns attempting to hit the other player(s) with a tank shell. The objective of
the game is to be the last tank standing. Players must perfect their aim since tank shells are heavy and are heavily
influenced by gravity. Players must also account for the hilly terrain and may need to clear portions of terrain away
to get a better shot.

Players may opt to skip their turn to shoot and instead navigate to a better position within a time limit. Players may
also be moved when a tank shell from an enemy clears terrain below them. Another caveat of this game is that tank shells
not only take hit points away from players, but also destroy pieces of terrain in the vicinity of the blast impact.

## Background
___
My experience with this game is limited to some number of hours playing it in arcades when I was younger. I want to do
this project because I think being able to successfully model the physics of the game will be a great challenge. After
the Ideal Gas project, I knew I wanted to create some kind of physics engine, and this project matches fits that.

## Features
___
This section is meant to explain features of the game, so I don't clog up the actual timeline with descriptions. 

I want to create a tank avatar that players can actually drive around. I also want to make the tank such that the gun 
is able to move up and down as the player aims. The only aim assistance I want to give the player is a "laser" assist 
that points in the direction they are aiming. Another thing I want is to model gravity in a way that accelerates the 
tank shells towards the ground to exaggerate gravity.

I want to model the terrain such that the blocks that make up the ground are fairly small. Obviously I am limited by 
the computing power of my own computer, so if I will only scale up the size of the terrain blocks if necessary. 

I also want to be able to load in a map via a json file to configure the terrain, set the locations and game statuses 
of the players, and set any other necessary game rules. As an extension, I also want to be able to save a game and be 
able to load it again another time.

## Timeline
___
### Week 1:
In week 1, I want to have created the tank model and implemented functions to move it, aim, and shoot. I also want to 
have implemented the gravity physics for a tank shell. I also want to start designing a JSON schema to load in a game.

The stretch goal for this week is to begin development of next week's work.

### Week 2: 
In week 2, I want to model the terrain using miniature terrain blocks. I also want to finish the JSON schema so that I 
can create a terrain using the JSON file. I also want to finish implementing the tank shell's interaction with the 
terrain when a shell hits the ground. I also want to ensure that tanks are able to move on the terrain.

The stretch goal for this week is to begin development of next week's work.

### Week 3:
In week 3, I want to complete the multiplayer game logic. This entails implementing players, hit points, interactions 
between tanks, scoreboards, and more. I also want to add in functionality to save the game state and load it another 
time during this week. 

A stretch goal is to create 2 screens to simulate a multiplayer game so that players will not have to share a screen 
when playing. Another stretch goal is to give trajectory predictions so players can see exactly where their shell will 
land when fired. A final stretch goal is to have the terrain particles level out like sand (to accurately model the 
laws of physics).

## Libraries
___
I plan on using the the nlohmann::json library for JSON parsing. I also want to use the gflags library for command line 
argument processing to boot up the game, but this may be a stretch considering Cinder has it's own main method. 