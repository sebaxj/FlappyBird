# Jumper

A mixed version of the "Flappy Bird" and "Jetpack Joyride" mobile games. 

The player will use a capacitive touch sensor integrated into an 8x8 LED array to control a jetpack-wearing main character. On the LED array, the main character is represented by a single LED, and will only have a degree of freedom in the y-direction. The player must manipulate the y-position of the main character to navigate approaching obstacles. The player does so by interacting with the touch sensor, which in turn affects the "thrust" of the jetpack.

The jetpack-wearing main character is implemented in the Jumper.h class, and has been assigned a y-coordinate, a y-velocity, and a gravity parameter. 

The obstacles are implemented in the Pipe.h class.

The main program renders the jetpack-wearing main character and the obstacles, determines whether the player is interacting with the touch sensor, and handles collision detection.
