# OpenGL based 3d Engine #
This is an OpenGl based 3d Engine for the Computer Graphics course at Leiden University.

## Features ##
- An ECS based architecture that allows for easy extensions using the component struct.
- Scene scripting using the provided demo.txt.
- Deferred Shading.
- Multitexture terrains using blend maps and height maps.
- Explosion/Disintegration effects
- Simple Collision detection using AA Bounding Boxes

## Installation ##
- install `libglfw3-dev` 
- install `pkg-config` 
- run `pkg-config --libs glfw3` 
- run `make`.

## Usage ##
run `./main [<script_file>]` to execute the program.

## Code borrowed ##

OBJloader:
  https://github.com/Bly7/OBJ-Loader
