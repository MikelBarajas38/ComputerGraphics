# QDEngine

Simple (quick-and-dirty) 3D graphics engine using C++, OpenGL, and GLUT for my computer graphics course.

## Features

### Importing OBJ files

The project supports .obj file loading. The file is then parsed into an Object3D (class with vertex and face data). The parser supports most .obj formats, but rendering is limited to triangular faces. Included is a demo with some example animations and an example scene workflow.

### Rendering

To display objects on screen, the project uses GLUT for window management and OpenGL's built-in functions glBegin() and glEnd() to render the object's triangular faces.

### Animation

Animations are done using matrix multiplications between transformation matrices (rotation, translation, and scaling) and the model matrix for each object. All the linear algebra operations were implemented from scratch. Transformations can be applied using a functional API (inspired by Unity’s transform component) or by manually performing matrix multiplication and using the Object3D transform method. To create more complex animations, trajectories can be precomputed using cubic Bézier curve splines.

### Lightning

The engine supports both ambient and directional lighting, using surface normal to compute the diffuse and specular reflection components. The project contains a homebrew flat and a Goraud shading implementation.

### User Input

The demo scene has some primitive user (keyboard) input handling, mostly added to show off the other functionalities (and to create the media in this README, lol). You can change the shading technique used ([g]oraud), enable/disable the illumination components ([s]pecular, [d]iffuse), cycle between the different camera objects ([c]amera), replace the current model ([m]odel), pause the animations ([p]ause), and switch on/off each of the sample lights ([1] to [4]).

## How to Install and Run

Open the solution in Visual Studio. I recommend using the freeglut.3.0.0 package from NuGet to get up and running quickly.

## Future Work

I plan on implementing a scene class to handle everything needed to create a 3D scene (basically taking all the demo does into its own class). Also, I plan on adding material support to improve lightning interaction, for example, by allowing objects to have different characteristics such as metallic reflectance. Currently, only face color is used (also, the specular component is intuitively stored in each lighting).
