# COMP3015 CW1
Created in Visual Studio 2022 on Windows 11

## How it works
Scenebasic_Uniform.cpp is where all the models are loaded. It also links the different vertex and fragment shaders that are used by the different models. A frame buffer is set up in init scene so that post processing effects
can be applied. In Scenebasic_Uniform.h all of the textures used by the models are loaded so they can be used anywhere in the cpp. In the render loop the first pass is used to render all of the models and the second pass
applies any post processing effects onto the frame. <br> <br>

Scenebasic_Uniform.frag is where the lighting, for and edge detection is done. It uses a spotlight by limiting the angle the light can be at and returns a vec3 value for the colour. It is then mixed with the Fog.Color and fogFactor
to add fog to the scene. There are separate shaders for texture mixing as that will stop any issues with using multiple textures in one fragment shader when I only want to use one. There is also a separate shader for the skybox.
This is because it needs to handle a cubemap but works similarly to the previous shaders. <br> <br>

Input controls are handled in scenerunner.h. Each time it iterates through the main loop it updates the camera position and checks for any inputs the user has made.

## Controls
WASD controls to move around <br>
CTRL to move down and SPACE to move up <br>
Hold LEFT SHIFT to increase movement speed in all directions <br>
\+ To increase the fog and - to decrease it (when pressing + after fog completely hides scene it will appear to be removed. Press - to make it return) <br>
Press E to toggle edge detection on or off <br>
Use the mouse to chage the position the camera faces

## Features implemented
BlinnPhong lighting <br>
Spotlight<br>
Texture sampling <br>
Fog <br>
Skybox <br>
Keyboard and mouse controls <br>
Edge detection

## AI Usage Declaration
General debugging <br>
Assisting with broken normal mapping (did not work) <br>
Fixing projection when adding edge detection and fog for skybox
