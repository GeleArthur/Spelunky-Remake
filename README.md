<div name="readme-top"></div>

<!-- GENERAL GAME INFO -->
<br />
<div align="center">

  <h1 align="center">Spelunky</h1>

  <p align="center">
    Spelunky is a cave exploration / treasure-hunting game inspired by classic platform games and roguelikes, where the goal is to grab as much treasure from the cave as possible. Every time you play the cave's layout will be different. Use your wits, your reflexes, and the items available to you to survive and go ever deeper! Perhaps at the end you may find what you're looking for...
    <br />
    <strong>Original game : </strong>
    <a href="https://store.steampowered.com/app/239350/Spelunky/"><strong>General info »</strong></a>
    ·
    <a href="https://youtu.be/N1uiLR6luWo"><strong>Youtube video »<strong></a>
    <br />
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#my-version">My version</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#how-to-play">How To Play</a></li>
    <li><a href="#class-structure">Class structure</a></li>
    <li><a href="#checklist">Checklist</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project
![Game spelunky. Player hits a snake](.github/Example1.png)

Here's why:
* The interaction between you the enemies and the environment are virtual limitless
* because of the randomly generated levels you can always replay it.
* Dynamic physics with destroyable environments. 


<p align="right">(<a href="#readme-top">back to top</a>)</p>


## My version

This section gives a clear and detailed overview of which parts of the original game I planned to make.

### The minimum I will most certainly develop:
- [ ] Level generation
	- [x] 4x4 rooms
	- [x] 100% goal path (step 1 of book)
	- [x] Individual rooms (step 2 of book)
	- [x] Obstacles in rooms (step 3 of book)
	- [x] Items and enemy placement
- [ ] World
	- [x] All "objects" need to have physics.
	- [x] All "items/monsters" need to be able to be picked up.
	- [x] All "items/monsters" need to be able to be thrown.
	- [ ] Spiderwebs (slow down any object)
	- [ ] Pots
	- [x] Level destruction.
	- [ ] Arrow traps.
	- [x] Spikes (If landed on instant death. Can be walked through)
	- [x] Exit door
	- [ ] Tiles that can snap together.
- [ ] Physics:
	- [x] Gravity, velocity, acceleration
	- [x] Impact damage
	- [x] Destroyed item if impact too large.
	- [ ] Objects need to rotate when in air.
	- [x] Collision.
	- [x] Reaction on collision.
	- [x] If object hit with enough impact it will get stunned.
- [ ] Player
	- [x] Animated spritesheet
	- [x] Jumping
	- [x] Moving left right
	- [x] Failing
	- [ ] Fall damage
	- [x] Sprinting
	- [x] Crouching
	- [x] Crouch walking
	- [x] Hanging off ledges 
	- [x] Pickup objects / holding objects.
	- [x] Throw object.
	- [x] Put object back on floor.
	- [x] Whip (Can damage Objects)
	- [ ] Jump on top of monsters.
	- [ ] Ropes that can be thrown up.
	- [x] Climbing on ropes and ladders. 
	- [x] Bombs.
	- [x] Player invisible frames if gets hit.
- [ ] UI
	- [ ] Money counter
	- [x] Health, bombs, rope.
	- [ ] Death screen
- [ ] Particles
	- [ ] Blood particles when something gets hit.
	- [ ] Explosion
- [X] Monsters:
	- [x] AI system thats used by all monsters.
	- [X] Damsel (Can be picked up and will run around if not picked up). 
	- [x] Snake (Moves left and right if found edge or wall)
	- [x] Bat (When its above the player and close enough it will fly towards the player)
	- [x] Some monsters damages the player if get hit.

### What I will probably make as well:
- [ ] UI
	- [ ] Start up animation (The walls are shifting)
	- [ ] Level text.
	- [ ] Money gets added animation
- [ ] Player
	- [ ] Rope moving past effect.
- [ ] Particles
	- [ ] Player lands smoke.
	- [ ] Skeleton head/pot breaks.
	- [ ] Gold pickup particles


### What I plan to create if I have enough time left:
- [ ] World
	- [ ] Light system
	- [ ] Shop
	- [ ] Stealable totem with bolder.
	- [ ] Sacrifice altar.
- [ ] Items:
	- [ ] Shotgun
	- [ ] Jetpack
	- [ ] Jump boots
	- [ ] Grab ledge hand
- [ ] Monsters:
	- [ ] Shop keeper (Will shoot the player if he steals something or his shop breaks).
	- [ ] Small spider (Drops down onto the player)
- [ ] Extra
	- [ ] Web browser support



<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started
Detailed instructions on how to run your game project are in this section.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* Visual Studio 2022

### How to run the project

Explain which project (version) must be run.
* any extra steps if required 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- HOW TO PLAY -->
## How to play
![spelunky game](.github/CheckPoint_02.png)

### Controls
* R: generate new level + reset
* ArrowKeys: move character
* Z: Jump
* Shift: PickUp Item
* E: Throw item

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CLASS STRUCTURE -->
## Class structure 
[Click here for UML](https://mermaid.live/edit#pako:eNqdVMGOmzAQ_RXLp6QNUUIgu6Aoh2YrtYeq0W63lSouDgyNG2Mj27Sl2ey318GwMpL3Ug7BM_P8nnkz8RnnogCc4iAIMq6pZpCihxpYw09txrtszohSd5T8kKTKODLPTjBGC5Bo8xQEBn4ECUPOh7iHXI_r-2OraK4-H36aEgqCLfomJCu-UAaqRzDSmv1B8LQdo_0Eb9BY4KOG6tXNd6RSwOzZdhKIbiTYynsOVesrDNGrnGMXDEz4UK4TPoxFdY47jpxt-vp8NTAhn6_pZ5u9uHusa-eBaFxzpRzKt2hH-DvY0_wExWM9maKDEMyt_6JSN4Shx7ogGnqeF5xHavhER2WzoVyDLEkO261Dfk_anCg9mTq53RHyU8ehqOCTF8OENh5P0QeqKS-FR3fcBEd9PC51H_3mw7iMWNwm_S9Hf0bXZtu6sESdEcpEe2GWPgQXsiJuC0omiEaMVIeCeNSu0-5I-TrSz69_NLqx95fsf8Wt2cX1jWe4AnNSWpgbpNPPsGlRBRlOzbIg8pThjF8MjjRaPLQ8x6mWDcxw041Sf6sMyZrw70KYsCRM2RinZ_wHp6s4mS_iJEzidRyFyTqZ4RanyzCex1GSLJfmZxGuougyw387hsX8ZrVe3UYGurxNbsKF2QEFNfZ-shded-9d_gFUqJY2)


### Object composition 
`PhysicsObject.h` uses a composition to get a collider*. This collder is an interface which can be a rect collider or circle collider.



### Inheritance 
PlayerObject and Rock inherit from PhysicsObject so they have physics and can interact with the world.


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CHECKLIST -->
## Checklist

- [x] Accept / set up github project
- [x] week 01 topics applied
    - [x] const keyword applied proactively (variables, functions,..)
    - [x] static keyword applied proactively (class variables, static functions,..)
    - [x] object composition (optional)
- [x] week 02 topics applied
- [x] week 03 topics applied
- [x] week 04 topics applied
- [x] week 05 topics applied
- [ ] week 06 topics applied
- [ ] week 07 topics applied
- [ ] week 08 topics applied
- [ ] week 09 topics applied (optional)
- [ ] week 10 topics applied (optional)


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Arthur van den Barselaar - arthur.van.den.barselaar@student.howest.be

Project Link: [https://github.com/HowestDAE/dae16-ArthurvandenBarselaar](https://github.com/HowestDAE/dae16-ArthurvandenBarselaar)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. 

* [Example 1: cpp reference on std::vector](https://en.cppreference.com/w/cpp/container/vector)
* [Spelunky by Derek Yu (book)](https://bossfightbooks.com/products/spelunky-by-derek-yu)
* [One Lone Coder Rect vs Rect Collision](https://github.com/OneLoneCoder/Javidx9/blob/master/PixelGameEngine/SmallerProjects/OneLoneCoder_PGE_Rectangles.cpp)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

