the query to Google AI:
how to call situation when near and far planes are the same in frustum calculation opengl?

AI Overview

When the near and far clipping planes are set to the exact same value in OpenGL, the view volume becomes infinitely thin.
In 3D graphics, this specific state is called a *degenerate* frustum or a *singular* volume.

In practical terms, this situation leads to several immediate rendering errors and behaviors:

(1) Division by Zero:
    The perspective projection matrix calculates depth mapping using the term 1 / (far-near).
    If the near and far planes are the same, the denominator is 0, leading to a divide-by-zero error that corrupts your projection matrix.
(2) Z-Fighting and Missing Objects:
    All geometry inside the scene collapses into a single 2D plane.
    The depth buffer cannot distinguish between the front and back of your objects, resulting in severe Z-fighting or completely invisible meshes.
(3) Infinite Culling:
    The engine's frustum culling mechanism will flag everything outside this zero-thickness volume as clipped.

To avoid a degenerate frustum, you must ensure that the near plane is always strictly less than the far plane (i.e., near < far).

the query to Google AI:
what coordinates should be sent to glOrtho? In window coordinate system or in normalized device coordinates?

AI Overview

You should use window coordinates (or "world coordinates" representing your specific game/application dimensions).
Do not use Normalized Device Coordinates (NDC) directly in glOrtho.
url: https://stackoverflow.com/questions/59262874/how-can-i-use-screen-space-coordinates-directly-with-opengl ;

The glOrtho function is used to define an orthographic projection matrix.
Its primary job is to act as a transformer - it takes your custom coordinate system and maps it into the standard NDC space,
which spans from [-1.0, 1.0] on the X and Y axes.
url: https://learnopengl.com/Getting-started/Coordinate-Systems ;

Because glOrtho acts as this mathematical bridge, the parameters you send to it define the virtual boundaries of your camera.

How the Coordinates Work

For a window that is 800 × 600 pixels, common ways to configure glOrtho include:

1. Pixel-Perfect Coordinate System (Top-Left Origin)
   Many 2D games and UI elements prefer a coordinate system where (0, 0) is in the top-left corner and the maximum extent is the window resolution.

   glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);

   left   / right:   0.0 and 800.0
   bottom / top  : 600.0 and 0.0 (Note the inversion so Y increases downwards);
   zNear  / zFar :  -1.0 and 1.0

2. Cartesian Coordinate System (Center Origin)
   If you are doing 2D math or graphing and want (0,0) in the dead center of the screen, you would set the parameters relative to that center.

   glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);

   left   / right: -400.0 and 400.0
   bottom / top  : -300.0 and 300.0

A Note on Viewports

It is important to remember that glOrtho sets up the projection, but the actual screen area is mapped via glViewport. 
The dimensions passed into glOrtho should ideally match your glViewport's aspect ratio to prevent your geometry or UI from stretching.


