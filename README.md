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
* Its fun to play it has some very tight game design.
* Pretty difficult to implement and I like a challenge
* There are randomly generated levels so you can always replay it.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## My version

This section gives a clear and detailed overview of which parts of the original game I planned to make.

### The minimum I will most certainly develop:
* Random Level generation
* Player that can move around
* 

### What I will probably make as well:
* 
*  

### What I plan to create if I have enough time left:
* .. 
* .. 


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

Use this space to show useful examples of how a game can be played. 
Additional screenshots and demos work well in this space. 

### Controls
* keys, .. 
* .. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CLASS STRUCTURE -->
## Class structure 

### Object composition 
If you applied object composition (optional); explain where and how.

### Inheritance 
Explain where you applied inheritance (mandatory).

### ..

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CHECKLIST -->
## Checklist

- [x] Accept / set up github project
- [ ] week 01 topics applied
    - [ ] const keyword applied proactively (variables, functions,..)
    - [ ] static keyword applied proactively (class variables, static functions,..)
    - [ ] object composition (optional)
- [ ] week 02 topics applied
- [ ] week 03 topics applied
- [ ] week 04 topics applied
- [ ] week 05 topics applied
- [ ] week 06 topics applied
- [ ] week 07 topics applied
- [ ] week 08 topics applied
- [ ] week 09 topics applied (optional)
- [ ] week 10 topics applied (optional)


### Features
- [ ] Level genration
	- [ ] 4x4 rooms
	- [ ] 100% goal path (step 1 of book)
	- [ ] Induvatue rooms (step 2 of book)
	- [ ] Obstacles in rooms (step 3 of book) 
	- [ ] Items and enemie placement (unknow for now)
- [ ] World
	- [ ] All "objects" need to have physics.
	- [ ] All "items/monsters" need to be able to be picked up.
	- [ ] All "items/monsters" need to be able to be thrown.
	- [ ] Spiderwebs (slow down any object)
	- [ ] Pots
	- [ ] Level destruction.
	- [ ] Damzels (Can be picked up and used as body shield. When let alone will run away).
	- [ ] Arrow traps(Will shoot an arrow if anything moving is in front of it).
	- [ ] Spikes (If landed on instant death. Can be walked through )
	- [ ] Exit door
	- [ ] Light system
	- [ ] SpriteSheet that connect with each other
- [ ] Physics:
	- [ ] Gravity
	- [ ] Impact damage
	- [ ] Destoryed if impact too large.
	- [ ] Need to rotate when in air.
	- [ ] Collision.
	- [ ] Reaction on collision.
	- [ ] If object hit with enough impact it will get stuned if it can be.
- [ ] Player
	- [ ] Animated spritesheet
	- [ ] Jumping
	- [ ] Moving left right
	- [ ] Failing
	- [ ] Fall damage
	- [ ] Spriting
	- [ ] Crouching
	- [ ] Crouch walking
	- [ ] Hanging off legeds
	- [ ] Pickup objects. / holding objects
	- [ ] Throw object.
	- [ ] Put object back on floor.
	- [ ] Whip (Can damage Objects)
	- [ ] Jump on top of monsters
	- [ ] Ropes that can be thrown up.
	- [ ] Climbing ropes and ladders. 
	- [ ] Rope moving past effect.
	- [ ] Bom's (explode and destory the level after some time)
	- [ ] Player inv's frames if gets hit
- [ ] UI
	- [ ] Start up animation (The walls are shifting)
	- [ ] Money counter
	- [ ] Health, bom's, rope.
	- [ ] Level text.
	- [ ] Death screen
	- [ ] Money gets added animation
- [ ] Particles
	- [ ] Player lands smoke.
	- [ ] Blood particles when something gets hit.
	- [ ] Skeleton head/pot breaks.
	- [ ] Gold pickup particles
	- [ ] Explosion
- [ ] Monsters:
	- [ ] Snake (Moves left and right if found edge or wall)
	- [ ] Bat (When its above the player and close enough it will fly towards the player)
	- [ ] Monsters damages the player if get hit.

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

<p align="right">(<a href="#readme-top">back to top</a>)</p>

