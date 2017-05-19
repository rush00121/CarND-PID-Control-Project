# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./


# Reflections : 
## Effects of PID params : 

P : The proportional term Kp  affects the steering angle of the car with respect to the Cross Track Error (CTE). A higher Kp will 
result into higher correction towards reduction of the CTE and will result unstable oscillations of the car. A lower Kp
will result into a larger turning radius on sharp turns and will again not work. 
The Kp param should be tuned in proportion that works best at higher speeds, sharp turns and straight roads while having 
minimum instability / oscillations.

I : The Integration term Ki is used to correct the bias of the steering angle. In this simulator, I did not find any bias 
and hence have kept the Ki term to 0 . 

D : The derivative term Kd is used to dampen the oscillation that is caused by the Kp term and allows the car to attain more 
speed. A lower Kd term will result into more oscillations and a higher Kd term will result into more dampning and the car 
will not be able to correct itself faster in cases of sharper turns. 


## Choosing the PID terms 

I have implemented twiddle as a state machine that keeps on getting the CTE and adjusts the PID parameters to get the most 
optimal result. However, in my experience, twiddle can fail to converge / take a long time to converge if the boundaries of 
the parameters are not well defined. 

Hence I first manually tried to find a decent range of lower and upper bound for each of the PID parameters. And then I ran 
twiddle within the parameters limits . That helped me to converge faster . 

I have finally chosen my 
Kp parameter = 0.15 
Ki parameter = 0 
Kd parameter = 6.7 

These parameters yielded me the maximum speed while maintaining road safety.

## Simulation : 

Below is a link of the video of the simulation. 

https://www.youtube.com/watch?v=9hoM2dRIvX0&feature=youtu.be

There are a couple of points to be noted about the simulation. 

The simulation depends on the machine on which it is running / what resolution is being used and the graphics quality i.e Fastest,Fantastic etc. 

This is because the latency between the simulation and the program will vary with all the above parameters. And hence will the performance
of the simulation. I have chosen 1024x768 resolution and the Fastest option for the graphics quality.



