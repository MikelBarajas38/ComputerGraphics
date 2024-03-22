# QDEngine

Simple (quick-and-dirty) 3D graphics engine using C++, OpenGL, and GLUT for my computer graphics course.

https://github.com/MikelBarajas38/ComputerGraphics/assets/72757601/c8aa50a8-07fb-476c-ba21-780dbfd6e4fa

## Features

### Importing OBJ files

The project supports .obj file loading. The file is then parsed into an Object3D (class with vertex and face data). The parser supports most .obj formats, but rendering is limited to triangular faces. Included is a demo with some example animations and an example scene workflow.

### Rendering

To display objects on screen, the project uses GLUT for window management and OpenGL's built-in `glBegin()` and `glEnd()` functions to render the object's triangular faces.

### Animation

Animations are done using matrix multiplications between transformation matrices (rotation, translation, and scaling) and the model matrix for each object. All the linear algebra operations were implemented from scratch. Transformations can be applied using a functional API (inspired by Unity’s transform component) or by manually performing matrix multiplication and using the Object3D `transform` method. To create more complex animations, trajectories can be precomputed using cubic Bézier curve splines.

### Lightning

The engine supports both ambient and directional lighting, using surface normals to compute the diffuse and specular reflection components. The project contains a homebrew flat and a Goraud shading implementation.



https://github.com/MikelBarajas38/ComputerGraphics/assets/72757601/1edb4b08-aa64-4632-84ea-16c8a446d68e



### User Input

The demo scene has some primitive user (keyboard) input handling, mostly added to show off the other functionalities (and to create the media in this README, lol). You can change the shading technique used ([g]oraud), enable/disable the illumination components ([s]pecular, [d]iffuse), cycle between the different camera objects ([c]amera), replace the current model ([m]odel), pause the animations ([p]ause), and switch on/off each of the sample lights ([1] to [4]).

## How to Install and Run

Open the solution in Visual Studio. I recommend using the freeglut.3.0.0 package from NuGet to get up and running quickly.

## Future Work

I plan on implementing a scene class to handle everything needed to create a 3D scene (basically taking all the demo does into its own class). Also, I plan on adding material support to improve lightning interaction, for example, by allowing objects to have different characteristics such as metallic reflectance. Currently, only face color is used (also, the specular component is unintuitively stored in each lighting).

## Extra stuff

Cool "experiments" (bugs) that I faced while developing the project:

> Anchor point was set incorrectly when creating multiple `Object3D`'s

https://github.com/MikelBarajas38/ComputerGraphics/assets/72757601/8f41289c-e605-4228-a3e5-11cdfe90f574


