 
 # 3D Graphics Renderer Using Rasterisation

This is a renderer for displaying 3D graphics written in C++ without external dependencies. A project to learn about 3D graphics and C++. Information on Rendering techniques from the lessons on [Scratchapixel](https://www.scratchapixel.com/index.html).

![shuttle example](https://github.com/mpimblott/rasterization-renderer/blob/main/images/shuttle.png)

## Implementation Specifics

Support for:
 - loading and displaying .obj files
 - arbitrary camera positioning using lookat
 - output to .ppm file

To Do:
 - lighting
 - materials

Properties:
 - Row-major matrices
 - Right-handed coordinate system

## Building and dependencies

Use CMake to build, no external dependencies required.

## License

This project uses the MIT licence.

Example meshes from https://people.sc.fsu.edu/~jburkardt/data/obj/obj.html