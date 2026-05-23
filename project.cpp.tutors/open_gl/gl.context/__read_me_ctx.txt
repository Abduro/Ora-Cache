query to Google AI:
can MSAA technique be used in ms windows opengl version 1.1?

AI Overview
Multisample Anti-Aliasing (MSAA) cannot be used in a pure OpenGL 1.1 environment. MSAA requires hardware-level rasterization and multi-sample framebuffers,
which were introduced in later OpenGL versions and hardware extensions. However, you can achieve anti-aliased results through alternative techniques.

Why MSAA Doesn't Work in OpenGL 1.1

(1) Hardware Support: MSAA was not natively supported by graphics hardware when OpenGL 1.1 was released in 1997.
    It requires extensions or frame buffer objects (FBOs) that were developed years later.
(2) Window Creation Constraints: To use MSAA, a pixel format with multisampling must be requested when creating the rendering window.
    This is typically done via the WGL_ARB_multisample extension on Microsoft Windows, which is not part of the core OpenGL 1.1 API.

Alternatives for OpenGL 1.1

(1) Supersampling: You can manually render the scene to a backbuffer that is much larger than the window,
    and then scale it down to the final resolution (downsampling).
(2) Line/Polygon Smooth: For basic rendering, you can enable GL_LINE_SMOOTH and GL_POLYGON_SMOOTH along with GL_BLEND to soften harsh edges.
    https://stackoverflow.com/questions/74870300/custom-manual-implementation-of-msaa-in-vulkan << the author of answer said 'no';
    https://learnopengl.com/Advanced-OpenGL/Anti-Aliasing << just for getting know;