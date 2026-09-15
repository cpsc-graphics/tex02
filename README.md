# Asteroids Game
## Tutorial Exercise 2: Main Character Movement and Control

### Ship Movement

Our ship has two simple controls: moving forward and turning. Pressing the "UP" key (and keeping it pressed) will make it move in the direction it is facing. Pressing the "RIGHT" or "LEFT" keys (and keeping the key held down) will make it turn right (clockwise) or left (counter-clockwise).

How fast should the ship move and how fast should it turn? Additionally, it is a good idea to provide smooth acceleration and deceleration, otherwise the movement can feel abrupt. Some basic physics will give us the motion that we need. 

1. **Rotation (Turning)**<br>
   Let's tackle rotation first as it is simpler since we are not worrying about rotational acceleration. When turning, we'll keep things simple and have the ship turn at a constant angular speed.
   
   - Let $\omega$ denote the current angular velocity of the ship. When the ship is not turning, we'll set $\omega$ to $0$.
   
   - Let $\Omega$ denote the constant rotation speed of the ship. When the "RIGHT" key is held down, we'll set $\omega := -\Omega$, when the "LEFT" key is held down, we'll set $\omega := \Omega$. When either turning key is released, the ship stops turning, and we set $\omega := 0$.

   - We also need to keep track of the _heading_ of the ship. Let $\theta$ denote the current heading of the ship and let $dt$ denote the time interval between frames. The following will update the heading of the ship based on its current angular velocity $\omega$:<br>
   <br>
   $\theta \leftarrow \theta + \omega\,dt$

2. **Forward Motion**<br>
   Let $A$ denote the magnitude of acceleration (deceleration) that the ship experiences when it starts accelerating (decelerating). Let $a$ be the ship's current acceleration and let $u$ be its velocity. 
   
   - Similar to the case of turning (rotation), when the "UP" key is held down we'll set $a := A$, and when it is released, we'll set $a := -A$.

   - The velocity between successive frames seperated by a time interval $dt$ is updated as follows:<br>
   <br>
    $u \leftarrow u + a \, dt$

   - Similar to the rotation case, we need to keep track of the current position of the ship. Let $(x,y)$ denote the current 2D position of the ship. The following will update the position from one frame to the next over a time interval $dt$.<br>
   <br>
   $x \leftarrow x + u\, \cos\theta\, dt + \tfrac{1}{2} a\, \cos\theta\, dt^2$
   <br>
   $y \leftarrow y + u\, \sin\theta\, dt + \tfrac{1}{2} a\, \sin\theta\, dt^2$

   - We also need to ensure that if the user keeps the "UP" button pressed, the ship does not accelerate beyond a maximum speed $u_\mathsf{max}$. Similarly, when the user releases the "UP" button, we need to ensure that the ship decelerates to a stop and does not start moving backwards. These conditions can be handled by setting the acceleration to $0$ and capping the maximum speed to $u_\mathsf{max}$.

### Update and Drawing

The procedure outlined above provides us a way to update the position $(x,y)$ and heading $\theta$ of the ship for every frame. Additionally, we'll also scale the ship to a small size by applying a uniform scale factor. All together, we need to set three transformations for the ship prior to drawing a frame: _position_, _rotation_, _scale_. In this exercise, we'll let [SFML handle this](https://www.sfml-dev.org/tutorials/3.1/graphics/transform/) for us (via the `setPosition`, `setRotation`, and `setScale` functions). In subsequent tutorials, we'll set up our own transformation matrices.

### Tasks

Starter code for this exercise is provided in this repository. The exercise builds on the previous tutorial exercise by adding appropriate variables and functions to the `Ship` class. Additionally, code that handles event callbacks is also provided. Your TA will guide you through the code structure. Your main task is to implement the physics that controls the ship's movement by completing the missing sections in the codebase. Then compile and run your program to verify that the ship is moving as expected. 

Note that if you let the ship move past the end of the window, you will very likely lose it. Do not be concerned about this. We will fix this later.

### Submission

Submit your completed exercise via Gradescope before the end of your scheduled tutorial session under the assignment titled **Tutorial Exercise 2**.

_Submit only the files you have modified; do not upload the entire repository._


