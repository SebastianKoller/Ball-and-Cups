# Ball-and-Cups
_Computer Graphics Project (CP 411)_

A simple mini-game where a single ball is hidden under one of the cups.

Click the cups to lift them and see how many you can get in a row!

Current Streak and High Score are kept in the application title bar.

## Video Demo

https://user-images.githubusercontent.com/73850102/226715657-a3d5bc4c-6f15-4e32-849c-310e7f02cb3f.mp4

# Project Proposal

## Introduction
This project aims to make a simple ball and cup game in 3d space. Three cups will be rendered along with a ball hidden inside one of them. The user can then select a cup to lift, guessing which cup hides the ball. You win if you find the ball, fail if you don’t find it.

## Problem Solving and Algorithms
### Main Features
- Rendering a cup with texture and shading (possibly with cup handle)
  - Design method to draw a cylinder shape, which has it’s two circular faces of different sizes and an angular curved surface. With texture and lighting
  - Use a static light that will update shading as the cups are moved in animation
- Creatively animating the cup’s lifting movement
  - Use object translation and rotation methods learned in class
- Menu to selecting cup object to lift
  - Use menu methods learned in class and or an on screen selection menu
- Reset the view after each game with ball in new random location
  - Use random library in conjunction with world class developed in assignments
### Possible Additional Features
- Choose Level Difficulty, user can choose how many cups are rendered in the view
  - Use menu in conjunction with a dynamic objectCount variable in the world class to keep track of number of cups and keep them within the view
## Design Consideration
### Architecture
- MVC Model based on work from SimpleView project. Camera View will be locked in position
- World class will load 3 cup objects and 1 sphere object by default. It will also have a light source.
- User interactions will be accessible through right click menu, keyboard, and any additional on screen clicking options.
### System Design
- World class from the SimpleView project will be used to load objects to the view system.
  - World class must be modified to spawn Cup objects and also track which cup corresponds to the winning location of the hidden ball.
- Cup class (extension of Shape class) must be implemented.
- Game elements will be implemented into the function of the main and menu classes.
